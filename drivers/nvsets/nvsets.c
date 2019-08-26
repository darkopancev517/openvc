#include "nvsets.h"

/* default nvram sets value */

nvsets_t nvsets = {
    .cent.frequency = 868000000,
    .cent.xtal_offset = 58,
    .cent.pa_sel = 1,
    .cent.tx_power = 20,
    .cent.tx_power_calib_offset = 0,
    .cent.rssi_offset = 0,
    .cent.elna_rssi_offset = 0,
    .cent.front_end_state_bits = 0,
};
