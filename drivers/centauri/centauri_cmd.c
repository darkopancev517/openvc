#include "vtprober.h"
#include "centauri_cmd.h"
#include "centauri_prober.h"
#include "centauri_cfg.h"
#include "centauri_queue.h"
#include "centauri_pmu_csr.h"
#include "centauri_timer.h"

#include "fe_csr_vcore.h"
#include "TransceiverCsr.h"
#include "phy_csr.h"
#include "TransceiverInit.h"

uint32_t iqc_a_b_pmu = 0,iqc_c_pmu = 0;

#if HOST_IF_ON
extern uint32_t rx16m_en;
extern uint32_t rx_rf_channel_read;
#endif

int cent_send_cmd(RF_HCMD_CMD_T cmd, uint16_t param, uint16_t ack)
{
    RF_CMD_T hcmd;

    hcmd.cmd = cmd;
    hcmd.ack = ack;
    hcmd.param = param;

    cent_spi_writeW(CENT_COMM_INFO_ADDR + offsetof(COMM_INFO_T, cmd_status), 0x0);
    cent_spi_writeW(CENT_PMU_ADDR(HCMD_ITCR1), *((uint32_t *)&hcmd));

    return 0;
}

void cent_cmd_status(void)
{
    cent_send_cmd(RF_HCMD_SYSTEM_STATUS, 0, 0);
}

#define MS2TICK     32

#define TICK_1MS    (MS2TICK)
#define TICK_500US  (MS2TICK / 2)
#define TICK_250US  (MS2TICK / 4)
#define TICK_125US  (MS2TICK / 8)

uint8_t time2tick[SLP_RES_ALL] = { TICK_1MS, TICK_500US, TICK_250US, TICK_125US };

void cent_sleep_time_setting(uint32_t period)
{
    uint32_t target_tick;

    volatile TIMER_32K_FIELDS_T timer_setting;

    cent_spi_readW(CENT_RTN_32K_CTRL_ADDR, (uint32_t*)&timer_setting);

    /* sleep time = period * timer_setting.resl */

    if ((timer_setting.resl >= SLP_RES_1ms) && (timer_setting.resl < SLP_RES_ALL)) {
        target_tick = period * time2tick[timer_setting.resl - SLP_RES_1ms];
    } else {
        target_tick = period * time2tick[0];
    }

    if (target_tick > TIMER32K_TICK_MAX) {
        target_tick = TIMER32K_TICK_MAX;
    }

    timer_setting.target = target_tick;

    cent_spi_writeW(CENT_RTN_32K_CTRL_ADDR, *((uint32_t*)&timer_setting));
}

void cent_cmd_idle(void)
{
    cent_send_cmd(RF_HCMD_IDLE, 0, 0);
    TransceiverDcocSetting();
}

void cent_cmd_sleep(uint32_t period)
{
    cent_sleep_time_setting(period);
    cent_send_cmd(RF_HCMD_SLEEP, 0, 0);
}

void cent_cmd_shutdown(void)
{
    cent_send_cmd(RF_HCMD_SHUTDOWN, 0, 0);
}

void cent_cmd_cal_32k(void)
{
    cent_send_cmd(RF_HCMD_CALIB_32K, 1, 0);
    cent_busy_wait(20000);
}

void cent_cmd_cal_4m(void)
{
    cent_send_cmd(RF_HCMD_CALIB_4M, 1, 0);
    cent_busy_wait(2000);
}

void cent_cmd_cal_vco(void)
{
    cent_send_cmd(RF_HCMD_CALIB_VCO, 0, 0);
}           

void cent_cmd_cal_iq(void)
{
    cent_send_cmd(RF_HCMD_CALIB_IQ, 0, 0);

    if (cent_get_version() == 0x7000B3) {
        /* Gear shift bias setting */
        GearShiftBiasSetForIqCal();
        /* TBD IQ no hand shake */
        cent_busy_wait(6000);
        iqc_a_b_pmu = (CentauriCsrRead(0x4002c0cc)&0x7fff7fff);
        iqc_c_pmu = (CentauriCsrRead(0x4002c0d0)&0x7fff);
		/* Gear shfit  DCOC setting  */
        TransceiverDcocSetting();
        cent_spi_writeW(0x20010074, 0x0);
    } else {
        cent_busy_wait(6000);
    }
}

void cent_cmd_cal_rxadc(void)
{
    cent_send_cmd(RF_HCMD_CALIB_RX_ADC, 0, 0);
    cent_busy_wait(2000);
}

void cent_cmd_period_config(uint32_t period, uint32_t tolerance)
{
    cent_spi_writeW(CENT_RTN_PERIOD_TOLERANCE, tolerance);
    cent_spi_writeW(CENT_RTN_PERIOD_TIME, period);
    cent_send_cmd(RF_HCMD_CALIB_PERIOD_CHG, 0, 0);
}

void cent_cmd_init(void)
{
    cent_spi_writeW(CENT_RTN_CMD_ACK_PARAM, 0);
    cent_send_cmd(RF_HCMD_INIT, 0x2, 0);

    if (cent_get_version() == 0x7000B3) {
        uint32_t csr_tmp;
        csr_tmp = CentauriCsrRead(0x4002417c);
        csr_tmp = (csr_tmp & 0xffcfffff);
        csr_tmp |= (3 << 20);
        CentauriCsrWrite(0x4002417c, csr_tmp);
    }

    uint32_t tmp;
    do {
        cent_spi_readW(CENT_RTN_CMD_ACK_PARAM, &tmp);
    } while (tmp == 0);
}

void cent_cmd_tx(uint32_t fcs, uint32_t packet_len)
{
    uint32_t param;

    param = (fcs & 0x3) << 1;
    param |= packet_len & 0x7ff;

    cent_send_cmd(RF_HCMD_TX, param, 0);

#if	DLT_698p44_FLAG
    PhyExtraPsduConfig(0);
#endif
}

void cent_cmd_tx_refilled(uint32_t write_len)
{
    uint32_t param;
    param = write_len & 0xff;
    cent_send_cmd(RF_HCMD_TX_REFILLED, param, 0);
}

void cent_cmd_rx(uint32_t next_state)
{
    uint32_t param;

    if (next_state >= SYS_STATE_ALL) {
        next_state = SYS_IDLE;
    }

    param = next_state << 2;

    cent_send_cmd(RF_HCMD_RX, param, 0);

    if (cent_get_version() == 0x7000B3) {
        TransceiverB3Setting();
    }
    HostIfSetting();
#if	DLT_698p44_FLAG
	PhyExtraPsduConfig(3);
#endif
}

void cent_cmd_rx_read(uint32_t read_len)
{
    uint32_t param;
    param = read_len & 0xff;
    cent_send_cmd(RF_HCMD_RX_READED, param, 0);
}

void cent_cmd_txpwr(int16_t txpwr)
{
    if (txpwr < 0) {
        txpwr = (txpwr * -1) + 0x80;
    }
    cent_busy_wait(100);
    cent_send_cmd(RF_HCMD_TXPWR, (uint16_t)txpwr, 0);
}

int32_t cent_cmd_rssi(void)
{
    cent_send_cmd(RF_HCMD_RSSI, 0, 0);
    cent_busy_wait(CCA_DELAY*20+20);
    return cent_get_rssi();
}

void cent_cmd_rssi_offset(int16_t offset)
{
    if (offset > 15) {
        offset = 15;
    } else {
        if (offset < -15) {
            offset = -15;
        }
    }
    offset = (offset * 8) & 0xff;
    cent_send_cmd(RF_HCMD_RSSI_OFFSET, (uint16_t)offset, 0);
    cent_busy_wait(100);
}

uint32_t cent_cmd_set_channel(uint32_t chn_band)
{
    uint32_t status;
    cent_spi_writeW(CENT_RTN_CMD_ACK_PARAM, chn_band);
    status = cent_send_cmd(RF_HCMD_BAND, 0x8, 0);
#if HOST_IF_ON
    rx_rf_channel_read = chn_band;
#endif
    cent_busy_wait(400);
    return status;
}

uint32_t cent_cmd_read_channel(void)
{
    return (uint32_t)RomRfChannelRead();
}

void cent_cmd_set_modi(uint32_t modi)
{
    cent_send_cmd(RF_HCMD_MODI, modi, 0);
    cent_busy_wait(200);
    cent_cmd_rx(SYS_RX);
    FilterIfSetting();
}

void cent_cmd_set_rate(uint32_t rate, uint32_t clk_set)
{
    if (clk_set >= 2) {
        if (rate == 150000 || rate == 300000 || rate == 9600 || rate == 4800 || rate == 2400) {
            clk_set = 1;
        } else {
            clk_set = 0;
        }
    }
    cent_spi_writeW(CENT_RTN_CMD_ACK_PARAM, rate);
    cent_send_cmd(RF_HCMD_RATE, clk_set, 0);
    cent_busy_wait(200);
    FilterIfSetting();
    cent_set_adc_status(CentauriCsrRead(0x4002800c));
 	//Fan
#if AUTO_SET_PMB_LEN
	TransceiverPmeLenSetByRate(rate);
#endif
	//Han
	//TransceiverPmeLenSetByRateHan(rate);
}

void cent_cmd_txcw(uint16_t enable)
{
    cent_send_cmd(RF_HCMD_TXCW, enable, 0);
}

void cent_cmd_txcm(uint16_t enable)
{
    cent_send_cmd(RF_HCMD_TXCM, 0x2 | enable, 0);
}

void cent_cmd_gfilter(uint16_t sw, uint16_t bt)
{
	uint16_t param;
	param = ((sw&0x1) << 1) + (bt & 0x1);
    cent_send_cmd(RF_HCMD_GFILTER, param, 0);
}

void cent_cmd_psdu_order(uint16_t order)
{
    cent_send_cmd(RF_HCMD_PSDU_ORDER, order, 0);
}

void cent_cmd_data_whitening(uint16_t dw)
{
    cent_send_cmd(RF_HCMD_DW, dw, 0);
}

uint16_t pmb_len = 8;

void cent_cmd_pmb_length(uint16_t length)
{
    pmb_len = length / 8;
    cent_send_cmd(RF_HCMD_PMB, length, 0);
}

void cent_cmd_rx16mhz(uint16_t rx16m)
{
    cent_send_cmd(RF_HCMD_RXLP, rx16m, 0);
 	FilterIfSetting();
}

void cent_cmd_pa_select(uint16_t pa)
{
    cent_send_cmd(RF_HCMD_PASEL, pa, 0);
    cent_busy_wait(100);
}

void cent_cmd_dctune(uint16_t dctune)
{
    cent_send_cmd(RF_HCMD_DCTUNE, dctune, 0);
    cent_busy_wait(100);
}

uint16_t cent_cmd_read_dctune(void)
{
	uint32_t dctune;
    cent_send_cmd(RF_HCMD_DCTUNE, 0x80, 0);
    cent_busy_wait(1000);
	cent_spi_readW(CENT_RTN_CMD_ACK_PARAM, &dctune);
	return (uint16_t)(dctune&0xffff);
}

uint16_t cent_cmd_saradc(uint16_t vin_sel)
{
	uint32_t value;
    cent_send_cmd(RF_HCMD_ADC, vin_sel, 0);
    cent_busy_wait(1000);
	cent_spi_readW(CENT_RTN_CMD_ACK_PARAM, &value);
	return (uint16_t)(value&0xffff);
}

void cent_cmd_elna_enable(uint16_t sw)
{
    cent_send_cmd(RF_HCMD_ELNA, sw, 0);
}


void cent_cmd_switch_test(uint16_t sw)
{
    cent_send_cmd(RF_HCMD_SW_CTRL_TEST, sw, 0);
}

void cent_cmd_mac_loopback(uint32_t fcs, uint32_t packet_len)
{
	uint32_t param;
	param = (fcs & 0x3) << 11;
	param |= packet_len & 0x7ff;
	cent_send_cmd(RF_HCMD_MAC_LOOPBACK, param, 0);
}

void cent_cmd_state_change(uint32_t state)
{
	cent_send_cmd(RF_HCMD_STATE_CHANGE, state, 0);
}

void cent_cmd_statistic_clear(void)
{
	cent_send_cmd(RF_HCMD_STAT_CLEAR, 0, 0);
}

void cent_wakeup(void)
{
    cent_cmd_statistic_clear();
}
