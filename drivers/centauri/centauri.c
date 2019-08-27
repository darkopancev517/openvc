#include <assert.h>
#include <stdint.h>
#include <string.h>

#include "centauri.h"
#include "centauri_prober.h"
#include "centauri_cfg.h"
#include "centauri_host.h"
#include "centauri_queue.h"
#include "centauri_cmd.h"
#include "centauri_mac.h"
#include "centauri_pmu_csr.h"

#include "phy_csr.h"
#include "TransceiverInit.h"
#include "TransceiverCsr.h"

#include "thread.h"
#include "xtimer.h"
#include "board.h"
#include "periph/gpio.h"
#include "periph/spi.h"
#include "nvsets.h"

#define CENT_MSG_EVENT_IRQ (0x10)

static uint8_t cent_rxbuf[CENTAURI_BUFFER_SIZE];
static cent_dataset_t cent_data;

/* variable used globaly by centauri */
uint32_t rx_complete;
extern uint32_t bm_read_next;

static void cent_spi_acquire(void);
static void cent_spi_release(void);
static uint32_t cent_tx_prefill(uint8_t *data, uint16_t length);
static void cent_gpio_int_cb(void *arg);

extern kernel_pid_t centauri_thread_pid;

cent_dataset_t *centauri_init(void)
{
    /* centauri dataset */
    memset(&cent_data, 0, sizeof(cent_data));
    cent_data.rxdata = (uint8_t *)&cent_rxbuf[0];
    cent_data.txfcs = FCS_MODE;
    cent_data.ccathreshold = -100; /* default cca threshold */

    /* centauri reset gpio */
    gpio_init(BOARD_CENTAURI_RESET_PIN, GPIO_OUT);
    gpio_set(BOARD_CENTAURI_RESET_PIN);

    /* centauri interrupt gpio */
    gpio_init_int(BOARD_CENTAURI_INT_PIN, GPIO_IN, GPIO_BOTH, &cent_gpio_int_cb, NULL);

    /* trigger centauri reset */
    centauri_reset();

    /* initialize centauri spi interface */
    cent_spi_prober_init();

    /* start listening to centauri gpio interrupt */
    cent_data.irqlisten = 1;

    /* stage 1 -------------------------------------------------------------- */

    cent_spi_acquire();

    msg_queue_init();   /* initialize centauri msg queue interface */
    cent_if_config();   /* config spi delay & centauri side interrupt io */
    cent_cmd_status();  /* check centauri status */

    cent_spi_release();

    /* stage 2 -------------------------------------------------------------- */

    cent_spi_acquire();

    cent_misc_config(CENTAURI_PAYLOAD_SIZE + 4); /* payload + fcs */
    cent_radio_config(nvsets.cent.frequency);
    cent_cmd_init();
	RfLdo12vCOvREF(7);  //LDO output 1.3V
	FilterIfSetting();
    cent_cal_load();
    cent_data.txpwr = nvsets.cent.tx_power;
	/* set rssi config to avoid rx_rssi_ib_lvl transfer to dB-domain siturate */
	PhyInBandRssiCalcuShift(4); /* rx_rssi_ib_lvl[21:4] */
	cent_cmd_rssi_offset(6);
	CentauriCsrWrite(0x40028030, 0x00000000 | (3 << 8) );  /* CAP=3 */
	TransceiverDcocSetting();
    cent_cmd_cal_iq();
    cent_cmd_cal_32k();
    cent_cmd_cal_4m();
    cent_spi_writeW(CENT_PMU_ADDR(PMU_4M_TIMER_SR), 1012); /* (4.6Mhz*1.1*200us)=1012 */
    cent_spi_writeW(CENT_PMU_ADDR(PMU_CGCR), PMU_CGCR_IDLE);

    cent_cmd_set_rate(50000, 2);
    cent_cmd_set_modi(1000);
    cent_cmd_data_whitening(1);

    cent_spi_release();

    /* stage 3 -------------------------------------------------------------- */

    centauri_set_freq(nvsets.cent.frequency);
    centauri_rx();

    BOARD_RXLED_OFF();
    BOARD_TXLED_OFF();

    return (cent_dataset_t *)&cent_data;
}

void centauri_reset(void)
{
    gpio_clear(BOARD_CENTAURI_RESET_PIN);
    xtimer_msleep(2);
    gpio_set(BOARD_CENTAURI_RESET_PIN);
    xtimer_msleep(10);
}

void centauri_rx(void)
{
    cent_spi_acquire();
    if (cent_get_state() != SYS_RX) {
        msg_queue_clear();
        cent_data.rxindex = 0;
        cent_cmd_rx(SYS_RX);
    }
    cent_spi_release();
}

void centauri_idle(void)
{
    cent_spi_acquire();
    if (cent_get_state() != SYS_IDLE) {
        cent_cmd_idle();
    }
    cent_spi_release();
}

void centauri_tx(uint8_t *data, uint16_t length)
{
    assert(length <= CENTAURI_PAYLOAD_SIZE);

    cent_spi_acquire();

    if (cent_get_state() != SYS_IDLE) {
        cent_cmd_idle();
    }

    cent_data.txdata = data;
    cent_data.txlen = length;
    cent_data.txindex = 0;

    cent_data.txindex = cent_tx_prefill(cent_data.txdata, cent_data.txlen);
    cent_data.mactxcmp = 0;
    cent_data.phytxcmp = 0;

    BOARD_TXLED_ON();

    msg_queue_clear();

    cent_cmd_tx(cent_data.txfcs, cent_data.txlen);

    cent_spi_release();

    uint32_t timeout = xtimer_now().ticks32 + 100;
    while (!cent_data.phytxcmp && timeout > xtimer_now().ticks32);

    if (cent_data.phytxcmp != 1 && timeout < xtimer_now().ticks32) {
        /* Note: for some reason the phytxcmp event is not generated but we
         * must get mactxcmp event instead */
        assert(cent_data.mactxcmp == 1);
    }

    BOARD_TXLED_OFF();
}

uint32_t centauri_get_freq(void)
{
    cent_spi_acquire();
    uint32_t freq = cent_cmd_read_channel();
    cent_spi_release();
    return freq;
}

void centauri_set_freq(uint32_t freq)
{
    cent_spi_acquire();
    if (cent_get_version() == 0x7000b3) {
        RomChannelInvalidSet(0); /* workaround the invalid bit not getting back issue */
        cent_cmd_set_channel(freq);
        assert(!RomChannelInvalidRead());
    }
    cent_spi_release();
}

int centauri_get_cca_rssi(void)
{
    cent_spi_acquire();
    assert(cent_get_state() == SYS_RX);
    int rssi = (int)cent_cmd_rssi();
    cent_spi_release();
    return rssi;
}

int centauri_is_receiving(void)
{
    cent_spi_acquire();
    int status = cent_get_receiving_status();
    cent_spi_release();
    return status;
}

cent_dataset_t *centauri_get_data(void)
{
    return (cent_dataset_t *)&cent_data;
}

void centauri_reg_ww(uint32_t addr, uint32_t word)
{
    cent_spi_acquire();
    cent_spi_writeW(addr, word);
    cent_spi_release();
}

void centauri_reg_rw(uint32_t addr, uint32_t *word)
{
    cent_spi_acquire();
    cent_spi_readW(addr, word);
    cent_spi_release();
}

/* private functions implementation ----------------------------------------- */

static void cent_spi_acquire(void)
{
    spi_acquire(BOARD_CENTAURI_SPI_DEV, BOARD_CENTAURI_SPI_CS_PIN, SPI_MODE_0, SPI_CLK_1MHZ);
}

static void cent_spi_release(void)
{
    spi_release(BOARD_CENTAURI_SPI_DEV);
}

static uint32_t cent_tx_prefill(uint8_t *data, uint16_t length)
{
    return cent_mac_tx_prefill(data, length);
}

static void cent_rxcmp_packet_process(void)
{
    if (cent_data.rxindex == 3) {
        if (!cent_is_ack()) {
            return;
        }
    }
    if (cent_data.rftest) {
        if (cent_data.rxcmp.rftest != NULL) {
            cent_data.rxcmp.rftest((void *)&cent_data);
        }
    } else {
        if (cent_data.rxcmp.app != NULL) {
            cent_data.rxcmp.app((void *)&cent_data);
        }
    }
}

static void cent_handle_event_mac_rxcmp(void)
{
    /* fcs should match */
    if (!cent_is_fcs_match()) {
        goto exit;
    }

    uint8_t fcs_size = (cent_fcs_type() == FCS_32) ? 4 : 2;
    uint32_t packet_len = cent_get_pkt_len();
    uint32_t rxindex = cent_data.rxindex;

    /* phr length originaly should always equal with packet length */
    if (cent_data.phrlen != packet_len) {
        /* for some reason we miss phr interrupt especially in small packet, so
         * make sure the phr_len was 0 instead */
        assert(cent_data.phrlen == 0);
    }

    /* exclude fcs byte in received length */
    if ((packet_len - rxindex) < fcs_size) {
        uint32_t offset;
        offset = packet_len - rxindex;
        rxindex -= fcs_size - offset;
        cent_data.rxindex = rxindex;
    }

    /* make sure packet length is always bigger than fcs size */
    if (packet_len < fcs_size) {
        goto exit;
    }

    uint32_t remain_len = packet_len - rxindex - fcs_size;

    if (remain_len == 0) {
        cent_rxcmp_packet_process();
        goto exit;
    }

    /* make sure received packet is less than the max buffer size */
    assert((remain_len + rxindex) < CENTAURI_BUFFER_SIZE);

    /* receive remain frame */
    if (remain_len >= (MAC_BUF_SIZE / 2)) {
        if (remain_len == (MAC_BUF_SIZE / 2)) {
            rx_complete = 1;
        }
        uint8_t received_frame = (packet_len - rxindex) / (MAC_BUF_SIZE / 2);
        for (uint8_t i = 0; i < received_frame; i++) {
            rxindex += cent_rxHi_receive((uint8_t *)&cent_data.rxdata[rxindex], (MAC_BUF_SIZE / 2));
            remain_len = packet_len - rxindex - fcs_size;
        }
    }

    /* make sure rxindex is correct */
    assert((packet_len - fcs_size) == (rxindex + remain_len));

    /* get the rest of the bytes */
    if ((remain_len != 0) && (remain_len < (MAC_BUF_SIZE / 2))) {
        rx_complete = 1;
        rxindex += cent_rxHi_receive((uint8_t *)&cent_data.rxdata[rxindex], remain_len);
        remain_len = packet_len - rxindex - fcs_size;
    }

    /* update received index */
    cent_data.rxindex = rxindex;

    if (remain_len == 0) {
        cent_rxcmp_packet_process();
    }

exit:
    /* reset rx parameter */
    bm_read_next = 0;
    rx_complete = 0;
    cent_data.rxindex = 0;
    cent_data.phrlen = 0;

    msg_queue_clear();
}

static void cent_handle_event_mac(RF_CMD_T *event)
{
    if (event->param & ISR_TXB_LOTHR) {
        uint32_t txindex = cent_data.txindex;
        assert(txindex <= cent_data.txlen);
        if (txindex < cent_data.txlen) {
            txindex += cent_txlo_transfer((uint8_t *)&cent_data.txdata[txindex], (cent_data.txlen - txindex));
            cent_data.txindex = txindex;
        }
    }

    if (event->param & ISR_TXE_TXCMP) {
        cent_data.mactxcmp = 1;
    }

    if (event->param & ISR_RXB_HITHR) {
        uint32_t rxindex = cent_data.rxindex;
        assert(rxindex < CENTAURI_BUFFER_SIZE);
        rxindex += cent_rxHi_receive((uint8_t *)&cent_data.rxdata[rxindex], (MAC_BUF_SIZE / 2));
        cent_data.rxindex = rxindex;
    }

    if (event->param & ISR_RXE_RXCMP) {
        cent_handle_event_mac_rxcmp();
        BOARD_RXLED_OFF();
    }
}

static void cent_handle_event_phy(RF_CMD_T *event)
{
    if (event->param & PHY_IRQ_STATUS__RG_PHY_TX_IRQ_MASK) {
        cent_data.phytxcmp = 1;
    }

    if (event->param & PHY_IRQ_STATUS__RG_PHY_RX_PMB_IRQ_MASK) {
        BOARD_RXLED_ON();
    }

    if (event->param & PHY_IRQ_STATUS__RG_PHY_RX_PHR_IRQ_MASK) {
        cent_data.phrlen = (CentauriCsrRead(PHY_CSR__RX_DEFRAMER_PHR_DATA) & 0x07ff0000) >> 16;
    }
}

static void cent_handle_event_status(RF_CMD_T *event)
{
    assert(event->param & 0x5a5a);
    cent_data.alivestatus = 1;
}

static void cent_handle_event_irq(void)
{
    cent_spi_acquire();

    if (!have_cent_event()) {
        get_msg_queue();
        if (!have_cent_event()) {
            goto exit;
        }
    }

    RF_CMD_T *event = (RF_CMD_T *)get_cent_event();
    assert(event != NULL);

    switch (event->cmd) {
    case RF_EVENT_MAC_IRQn:
        cent_handle_event_mac(event);
        break;
    case RF_EVENT_PHY_IRQn:
        cent_handle_event_phy(event);
        break;
    case RF_EVENT_STATUS:
        cent_handle_event_status(event);
        break;
    default:
        break;
    }

exit:
    cent_spi_release();
}

static void cent_gpio_int_cb(void *arg)
{
    if (cent_data.irqlisten) {
        msg_t msg;
        msg.type = CENT_MSG_EVENT_IRQ;
        msg.content.ptr = NULL;
        msg_try_send(&msg, centauri_thread_pid);
    }
}

void *centauri_thread(void *arg)
{
    (void) arg;

    msg_t msg;
    while (1) {
        if (msg_receive(&msg)) {
            if (msg.type == CENT_MSG_EVENT_IRQ) {
                cent_handle_event_irq();
            }
        }
    }

    return NULL;
}
