/**
 * non-volatile parameter settings.
 */

#ifndef NVSETS_H
#define NVSETS_H

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct centauri_nvset {
    uint32_t frequency;
    uint32_t xtal_offset;
    uint32_t pa_sel;
    int32_t tx_power;
    int32_t tx_power_calib_offset;
    int32_t rssi_offset;
    int32_t elna_rssi_offset;
    uint32_t front_end_state_bits;
    int32_t cca_threshold;
} centauri_nvset_t;

typedef struct {
    centauri_nvset_t cent;  /* centauri non-volatile param */
} nvsets_t;

extern nvsets_t nvsets;

#ifdef __cplusplus
}
#endif

#endif /* NVSETS_H */
