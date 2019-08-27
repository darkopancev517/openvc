#ifndef CENTAURI_CMD_H
#define CENTAURI_CMD_H

#include <stdint.h>

#include "centauri_host.h"

#ifdef __cplusplus
extern "C" {
#endif

int cent_send_cmd(RF_HCMD_CMD_T cmd, uint16_t param, uint16_t ack);

uint32_t cent_cmd_read_channel(void);

void cent_cmd_status(void);

void cent_cmd_idle(void);

void cent_cmd_sleep(uint32_t period);

void cent_cmd_shutdown(void);

void cent_cmd_cal_32k(void);

void cent_cmd_cal_4m(void);

void cent_cmd_cal_vco(void);

void cent_cmd_cal_iq(void);

void cent_cmd_cal_rxadc(void);

void cent_cmd_period_config(uint32_t period, uint32_t tolerance);

void cent_cmd_init(void);

void cent_cmd_tx(uint32_t fcs, uint32_t packet_len);

void cent_cmd_tx_refilled(uint32_t write_len);

void cent_cmd_rx(uint32_t next_state);

void cent_cmd_rx_read(uint32_t read_len);

void cent_cmd_txpwr(int16_t txpwr);

int32_t cent_cmd_rssi(void);

void cent_cmd_mac_loopback(uint32_t fcs, uint32_t packet_len);

void cent_cmd_state_change(uint32_t state);

void cent_wakeup(void);

uint32_t cent_cmd_set_channel(uint32_t chn_band);

void cent_cmd_set_modi(uint32_t modi);

void cent_cmd_set_rate(uint32_t rate, uint32_t clk_set);

void cent_cmd_data_whitening(uint16_t dw);

void cent_cmd_pmb_length(uint16_t length);

void cent_cmd_rx16mhz(uint16_t rx16m);

void cent_cmd_txcw(uint16_t enable);

void cent_cmd_txcm(uint16_t enable);

void cent_cmd_statistic_clear(void);

void cent_cmd_pa_select(uint16_t pa);

void cent_cmd_dctune(uint16_t dctune);

uint16_t cent_cmd_read_dctune(void);

void cent_cmd_rssi_offset(int16_t offset);

void cent_cmd_elna_enable(uint16_t sw);

#ifdef __cplusplus
}
#endif

#endif /* CENTAURI_CMD_H */
