#include <assert.h>
#include <stdbool.h>

#include "contiki.h"
#include "sys/rtimer.h"
#include "sys/node-id.h"
#include "dev/radio.h"
#include "net/packetbuf.h"
#include "net/queuebuf.h"
#include "net/netstack.h"
#include "net/mac/csma/csma.h"
#include "lib/ringbufindex.h"

#include "centauri.h"

#include "sys/log.h"
#define LOG_MODULE "RADIO"
#define LOG_LEVEL LOG_LEVEL_RADIO

#define RADIO_ACK_TIMEOUT_VALUE (1 * CLOCK_SECOND)
#define RADIO_BUFFER_SIZE       CENTAURI_PAYLOAD_SIZE
#define RADIO_PKT_MAX           (8)
#define RADIO_FREQ_MAX          (928000000)
#define RADIO_FREQ_MIN          (868000000)
#define RADIO_FREQ_SPACING      (200000)
#define RADIO_CHAN_MAX          (((RADIO_FREQ_MAX - RADIO_FREQ_MIN) / RADIO_FREQ_SPACING) - 1)

enum {
    RADIO_TX_BROADCAST = 0x1,
    RADIO_ACK_RECEIVED = 0x2,
    RADIO_ACK_WAIT     = 0x4,
    RADIO_ACK_TIMEOUT  = 0x8,
};

typedef enum {
    RADIO_STATE_DISABLED = 0,
    RADIO_STATE_SLEEP = 1,
    RADIO_STATE_RECEIVE = 2,
    RADIO_STATE_TRANSMIT = 3,
} radio_state_t;

typedef struct {
    uint8_t data[RADIO_BUFFER_SIZE];
    uint16_t datalen;
    uint32_t timestamp;
} radio_pkt_t;

PROCESS(centauri_process, "Centauri process");

static radio_value_t radio_txmode;
static radio_value_t radio_rxmode;
static uint8_t radio_channel;
static int8_t radio_txpower;
static uint8_t radio_txlen;
static int radio_cca_rssi;
static int radio_cca_threshold;
static uint8_t radio_txbuf[RADIO_BUFFER_SIZE];
static uint32_t radio_status;
static uint32_t radio_last_packet_timestamp; /* last readed packet timestamp */
static radio_state_t radio_state = RADIO_STATE_DISABLED;
static int8_t radio_pktcount;
static struct ringbufindex radio_pktrb;
static radio_pkt_t radio_pkt[RADIO_PKT_MAX];

// contiki radio api
static int radio_init(void);
static int radio_prepare(const void *data, unsigned short len);
static int radio_transmit(unsigned short len);
static int radio_send(const void *data, unsigned short len);
static int radio_read(void *buf, unsigned short size);
static int radio_channel_clear(void);
static int radio_receiving_packet(void);
static int radio_pending_packet(void);
static int radio_on(void);
static int radio_off(void);
static radio_result_t radio_get_value(radio_param_t param, radio_value_t *value);
static radio_result_t radio_set_value(radio_param_t param, radio_value_t value);
static radio_result_t radio_get_object(radio_param_t param, void *dest, size_t size);
static radio_result_t radio_set_object(radio_param_t param, const void *src, size_t size);
static void centauri_rxcmp_cb(void *arg);

const struct radio_driver centauri_driver = {
    radio_init,
    radio_prepare,
    radio_transmit,
    radio_send,
    radio_read,
    radio_channel_clear,
    radio_receiving_packet,
    radio_pending_packet,
    radio_on,
    radio_off,
    radio_get_value,
    radio_set_value,
    radio_get_object,
    radio_set_object
};

PROCESS_THREAD(centauri_process, ev, data)
{
    PROCESS_BEGIN();

    while (1) {
        PROCESS_WAIT_EVENT_UNTIL(ev == PROCESS_EVENT_POLL);
        while (radio_pktcount != 0) {
            packetbuf_clear();
            int len = radio_read(packetbuf_dataptr(), PACKETBUF_SIZE);
            packetbuf_set_datalen(len);
            NETSTACK_MAC.input();
            radio_pktcount -= 1;
        }
    }

    PROCESS_END();
}

static void radio_set_channel(uint8_t channel)
{
    assert(channel <= RADIO_CHAN_MAX);
    uint32_t freq = (channel * RADIO_FREQ_SPACING) + RADIO_FREQ_MIN;
    radio_channel = channel;
    centauri_set_freq(freq);
}

static int radio_init(void)
{
    cent_dataset_t *cent = centauri_init();

    for (uint8_t i = 0; i < RADIO_PKT_MAX; i++) {
        memset(radio_pkt[i].data, 0, RADIO_BUFFER_SIZE);
        radio_pkt[i].datalen = 0;
    }
    memset(radio_txbuf, 0, sizeof(radio_txbuf));

    radio_channel = 0;
    radio_txmode |= RADIO_TX_MODE_SEND_ON_CCA;
    radio_rxmode = 0;
    radio_txpower = cent->txpwr;
    radio_cca_threshold = cent->ccathreshold;
    radio_pktcount = 0;

    radio_status = 0;
    radio_last_packet_timestamp = 0;
    radio_state = RADIO_STATE_RECEIVE;

    ringbufindex_init(&radio_pktrb, RADIO_PKT_MAX);

    process_start(&centauri_process, NULL);

    cent->rxcmp.app = centauri_rxcmp_cb;

    return 1;
}

static int radio_prepare(const void *data, unsigned short len)
{
    radio_txlen = len;
    memcpy((uint8_t *)&radio_txbuf, (void *)data, MIN(len, RADIO_BUFFER_SIZE));
    return RADIO_TX_OK;
}

static int radio_transmit(unsigned short len)
{
    int ret = RADIO_TX_OK;

    assert(radio_txlen == len && radio_txlen >= CSMA_ACK_LEN);

    assert(!(radio_status & RADIO_ACK_WAIT));
    assert(!(radio_status & RADIO_ACK_RECEIVED));

    radio_status &= ~RADIO_TX_BROADCAST;

    /* perfor cca if was set and ignore cca if we send an ack */
    if ((radio_txmode & RADIO_TX_MODE_SEND_ON_CCA) && (radio_txlen > CSMA_ACK_LEN)) {
        if (!radio_channel_clear()) {
            LOG_WARN("transmit collision (%d)\n", radio_cca_rssi);
            ret = RADIO_TX_COLLISION;
            goto exit;
        }
    }

    /* check the packet is broadcast or not */
    if (radio_txlen > CSMA_ACK_LEN) {
        if (packetbuf_holds_broadcast()) {
            radio_status |= RADIO_TX_BROADCAST;
        }
    }

    /* change the radio state */
    radio_state = RADIO_STATE_TRANSMIT;

    /* transmit the packet */
    if (centauri_tx(radio_txbuf, radio_txlen) != 0) {
        /* low level driver transmit failed */
        LOG_WARN("transmit failed\n");
        ret = RADIO_TX_ERR;
        goto exit;
    }

    /* check whether we need to wait for ack of not */
    if (!(radio_status & RADIO_TX_BROADCAST) && radio_txlen > CSMA_ACK_LEN) {

        /* not a broadcast packet, wait for ack */
        radio_status |= RADIO_ACK_WAIT;

        radio_on();

        uint32_t ack_timeout = clock_time() + RADIO_ACK_TIMEOUT_VALUE;
        while (!(radio_status & RADIO_ACK_RECEIVED) && ack_timeout > clock_time());

        radio_status &= ~RADIO_ACK_WAIT;

        if (!(radio_status & RADIO_ACK_RECEIVED)) {
            LOG_WARN("transmit noack\n");
            ret = RADIO_TX_NOACK;
        }

        goto exit;
    }

    radio_on();

exit:
    if (ret == RADIO_TX_ERR) {
        radio_on();
    }
    return ret;
}

static int radio_send(const void *data, unsigned short len)
{
    radio_prepare(data, len);
    return radio_transmit(len);
}

static int radio_read(void *buf, unsigned short size)
{
    int rbindex = ringbufindex_peek_get(&radio_pktrb);
    assert(rbindex != -1);

    ringbufindex_get(&radio_pktrb);

    int len = MIN(size, radio_pkt[rbindex].datalen);

    memcpy(buf, radio_pkt[rbindex].data, len);

    if ((radio_pkt[rbindex].datalen == CSMA_ACK_LEN) && (radio_status & RADIO_ACK_RECEIVED)) {
        radio_status &= ~RADIO_ACK_RECEIVED;
    }

    radio_last_packet_timestamp = radio_pkt[rbindex].timestamp;

    radio_pkt[rbindex].datalen = 0;
    radio_pkt[rbindex].timestamp = 0;

    return len;
}

static int radio_channel_clear(void)
{
    assert(radio_state == RADIO_STATE_RECEIVE);
    radio_cca_rssi = centauri_get_cca_rssi();
    return (radio_cca_rssi > radio_cca_threshold) ? 0 : 1;
}

static int radio_receiving_packet(void)
{
    return centauri_is_receiving();
}

static int radio_pending_packet(void)
{
    return ((radio_pktcount != 0) || (radio_status & RADIO_ACK_RECEIVED)) ? 1 : 0;
}

static int radio_on(void)
{
    centauri_rx();
    radio_state = RADIO_STATE_RECEIVE;
    return 1;
}

static int radio_off(void)
{
    centauri_idle();
    radio_state = RADIO_STATE_DISABLED;
    return 1;
}

static radio_result_t radio_get_value(radio_param_t param, radio_value_t *value)
{
    if (!value) return RADIO_RESULT_INVALID_VALUE;

    switch (param) {
    case RADIO_PARAM_POWER_MODE:
        if (radio_state == RADIO_STATE_RECEIVE) {
            *value = (radio_value_t)RADIO_POWER_MODE_ON;
        } else {
            *value = (radio_value_t)RADIO_POWER_MODE_OFF;
        }
        return RADIO_RESULT_OK;

    case RADIO_PARAM_CHANNEL:
        *value = (radio_value_t)radio_channel;
        return RADIO_RESULT_OK;

    case RADIO_PARAM_PAN_ID:
    case RADIO_PARAM_16BIT_ADDR:
        return RADIO_RESULT_NOT_SUPPORTED;

    case RADIO_PARAM_RX_MODE:
        *value = (radio_value_t)radio_rxmode;
        return RADIO_RESULT_OK;

    case RADIO_PARAM_TX_MODE:
        *value = (radio_value_t)radio_txmode;
        return RADIO_RESULT_OK;

    case RADIO_PARAM_TXPOWER:
        *value = (radio_value_t)radio_txpower;
        return RADIO_RESULT_OK;

    case RADIO_CONST_CHANNEL_MIN:
        *value = 0;
        return RADIO_RESULT_OK;

    case RADIO_CONST_CHANNEL_MAX:
        *value = (radio_value_t)RADIO_CHAN_MAX;
        return RADIO_RESULT_OK;

    case RADIO_CONST_TXPOWER_MIN:
        *value = 0;
        return RADIO_RESULT_OK;

    case RADIO_CONST_TXPOWER_MAX:
        *value = 20;
        return RADIO_RESULT_OK;

    default:
        return RADIO_RESULT_NOT_SUPPORTED;
    }
}

static radio_result_t radio_set_value(radio_param_t param, radio_value_t value)
{
    switch (param) {
    case RADIO_PARAM_POWER_MODE:
        if (value == RADIO_POWER_MODE_ON || value == RADIO_POWER_MODE_OFF) {
            value == RADIO_POWER_MODE_ON ? radio_on() : radio_off();
        } else {
            return RADIO_RESULT_NOT_SUPPORTED;
        }
        return RADIO_RESULT_OK;

    case RADIO_PARAM_CHANNEL:
        if (value < RADIO_CHAN_MAX) {
            radio_set_channel(value);
        } else {
            return RADIO_RESULT_NOT_SUPPORTED;
        }
        return RADIO_RESULT_OK;

    case RADIO_PARAM_PAN_ID:
    case RADIO_PARAM_16BIT_ADDR:
        return RADIO_RESULT_NOT_SUPPORTED;

    case RADIO_PARAM_RX_MODE:
        radio_rxmode = value;
        return RADIO_RESULT_OK;

    case RADIO_PARAM_TX_MODE:
        radio_txmode = value;
        return RADIO_RESULT_OK;

    case RADIO_PARAM_TXPOWER:
        centauri_set_txpwr(value);
        radio_txpower = ((cent_dataset_t *)centauri_get_data())->txpwr;
        return RADIO_RESULT_OK;

    default:
        return RADIO_RESULT_NOT_SUPPORTED;
    }
}

static radio_result_t radio_get_object(radio_param_t param, void *dest, size_t size)
{
    if (param == RADIO_PARAM_LAST_PACKET_TIMESTAMP) {
        if (size != sizeof(rtimer_clock_t) || !dest) {
            return RADIO_RESULT_INVALID_VALUE;
        }
        *(rtimer_clock_t *)dest = radio_last_packet_timestamp;
        return RADIO_RESULT_OK;
    }

    return RADIO_RESULT_NOT_SUPPORTED;
}

static radio_result_t radio_set_object(radio_param_t param, const void *src, size_t size)
{
    (void)param;
    (void)src;
    (void)size;
    return RADIO_RESULT_NOT_SUPPORTED;
}

static void centauri_rxcmp_cb(void *arg)
{
    cent_dataset_t *cent = (cent_dataset_t *)arg;

    /* make sure low level driver state is the same with high level driver */
    assert(radio_state == RADIO_STATE_RECEIVE);

    int rbindex = ringbufindex_peek_put(&radio_pktrb);
    assert(rbindex != -1);

    memcpy(radio_pkt[rbindex].data, cent->rxdata, MIN(RADIO_BUFFER_SIZE, cent->rxindex));
    radio_pkt[rbindex].datalen = MIN(RADIO_BUFFER_SIZE, cent->rxindex);
    radio_pkt[rbindex].timestamp = RTIMER_NOW();

    ringbufindex_put(&radio_pktrb);

    if ((radio_status & RADIO_ACK_WAIT) && cent->rxindex == CSMA_ACK_LEN) {
        radio_status |= RADIO_ACK_RECEIVED;
    } else {
        radio_pktcount++;
        process_poll(&centauri_process);
    }
}
