#ifndef CENTAURI_H
#define CENTAURI_H

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

#define CENTAURI_BUFFER_SIZE    (256)
#define CENTAURI_PAYLOAD_SIZE   (128)

typedef void (*cent_rxcmp_cb_t)(void *arg);

typedef struct {
    unsigned alivestatus;
    uint32_t timestamp;
    int pktrssi;
    int ccathreshold;
    uint32_t pktlqi;
    uint8_t *rxdata;
    uint16_t rxindex;
    uint8_t *txdata;
    uint16_t txlen;
    uint16_t txindex;
    unsigned mactxcmp;
    unsigned phytxcmp;
    int16_t txpwr;
    uint32_t txfcs;
    uint32_t phrlen;
    unsigned irqlisten;
    unsigned rftest;
    union {
        cent_rxcmp_cb_t app;
        cent_rxcmp_cb_t rftest;
    } rxcmp;
} cent_dataset_t;

cent_dataset_t *centauri_init(void);

void centauri_reset(void);

void centauri_rx(void);

void centauri_idle(void);

void centauri_tx(uint8_t *data, uint16_t length);

uint32_t centauri_get_freq(void);

void centauri_set_freq(uint32_t freq);

int centauri_get_cca_rssi(void);

int centauri_is_receiving(void);

cent_dataset_t *centauri_get_data(void);

#ifdef __cplusplus
}
#endif

#endif /* CENTAURI_H */
