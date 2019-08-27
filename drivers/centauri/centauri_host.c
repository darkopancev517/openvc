#include "vtprober.h"
#include "centauri_prober.h"
#include "centauri_queue.h"
#include "centauri_cmd.h"
#include "centauri_mac.h"
#include "centauri_cfg.h"
#include "nvsets.h"

static uint32_t cent_ic_version = 0;
static uint32_t cent_adc_status = 0;

uint32_t cent_nv_get_front_end(void)
{
    if (nvsets.cent.front_end_state_bits == 0xffffffff) {
        nvsets.cent.front_end_state_bits = 0;
    }
    return nvsets.cent.front_end_state_bits;
}

void cent_nv_set_front_end(uint32_t febs)
{
    nvsets.cent.front_end_state_bits = (febs & (FRONT_END_STATE_ELNA_EN |
                                                FRONT_END_STATE_EPA_EN |
                                                FRONT_END_STATE_ANT_DIVERSITY_EN));
    if (febs & FRONT_END_STATE_ELNA_EN) {
        nvsets.cent.pa_sel = 0;
        cent_cmd_pa_select(nvsets.cent.pa_sel);
    }
}

void cent_nv_set_pa_select(int on)
{
    if (cent_nv_get_front_end() & FRONT_END_STATE_EPA_EN) {
        nvsets.cent.pa_sel = 0;
    } else {
        nvsets.cent.pa_sel = on ? 1 : 0;
    }
    cent_cmd_pa_select(nvsets.cent.pa_sel);
}

int32_t cent_nv_get_elna_rssi_offset(void)
{
    return nvsets.cent.elna_rssi_offset;
}

void cent_cal_load(void)
{
    if (nvsets.cent.frequency != 0) {
        cent_cmd_set_channel((uint32_t)nvsets.cent.frequency);
    }

    if (nvsets.cent.xtal_offset != 0) {
        cent_cmd_dctune((uint16_t)nvsets.cent.xtal_offset);
    }

    if (cent_nv_get_front_end() & FRONT_END_STATE_EPA_EN) {
        nvsets.cent.pa_sel = 0; /* ensure it is set to MPA to protect ePA */
    }

    cent_cmd_pa_select(nvsets.cent.pa_sel);
    cent_cmd_txpwr((int16_t)nvsets.cent.tx_power);

    if (cent_nv_get_front_end() & FRONT_END_STATE_ELNA_EN) {
        cent_cmd_rssi_offset(0);
        cent_elna_enable(2);
    } else {
        cent_cmd_rssi_offset((int16_t)nvsets.cent.rssi_offset);
        cent_elna_enable(0);
    }
}

void cent_get_statistic(struct STAT_INFO_T *info)
{
	cent_spi_readW(CENT_STAT_INFO_ADDR + offsetof(STAT_INFO_T, pmb), (uint32_t*)&info->pmb);
	cent_spi_readW(CENT_STAT_INFO_ADDR + offsetof(STAT_INFO_T, sfd), (uint32_t*)&info->sfd);
	cent_spi_readW(CENT_STAT_INFO_ADDR + offsetof(STAT_INFO_T, phr), (uint32_t*)&info->phr);
	cent_spi_readW(CENT_STAT_INFO_ADDR + offsetof(STAT_INFO_T, antenna), (uint32_t*)&info->antenna);
	cent_spi_readW(CENT_STAT_INFO_ADDR + offsetof(STAT_INFO_T, rx_pkt), (uint32_t*)&info->rx_pkt);
	cent_spi_readW(CENT_STAT_INFO_ADDR + offsetof(STAT_INFO_T, tc1), (uint32_t*)&info->tc1);
	cent_spi_readW(CENT_STAT_INFO_ADDR + offsetof(STAT_INFO_T, rssi_less), (uint32_t*)&info->rssi_less);
	cent_spi_readW(CENT_STAT_INFO_ADDR + offsetof(STAT_INFO_T, rssi_over), (uint32_t*)&info->rssi_over);
	cent_spi_readW(CENT_STAT_INFO_ADDR + offsetof(STAT_INFO_T, rx_drop_by_len), (uint32_t*)&info->rx_drop_by_len);
	cent_spi_readW(CENT_STAT_INFO_ADDR + offsetof(STAT_INFO_T, tx_pkt), (uint32_t*)&info->tx_pkt);
	cent_spi_readW(CENT_STAT_INFO_ADDR + offsetof(STAT_INFO_T, txcmp), (uint32_t*)&info->txcmp);
	cent_spi_readW(CENT_STAT_INFO_ADDR + offsetof(STAT_INFO_T, rxcmp), (uint32_t*)&info->rxcmp);
	cent_spi_readW(CENT_STAT_INFO_ADDR + offsetof(STAT_INFO_T, fcs_err), (uint32_t*)&info->fcs_err);
	cent_spi_readW(CENT_STAT_INFO_ADDR + offsetof(STAT_INFO_T, rx_drop_by_addr), (uint32_t*)&info->rx_drop_by_addr);
}

uint32_t cent_get_cmd_status(void)
{
	uint32_t cmd_status;
	cent_spi_readW(CENT_COMM_INFO_ADDR + offsetof(COMM_INFO_T, cmd_status), (uint32_t*)&cmd_status);
	return cmd_status;
}

uint32_t cent_get_state(void)
{
	uint32_t state;
	cent_spi_readW(CENT_COMM_INFO_ADDR + offsetof(COMM_INFO_T, state), (uint32_t*)&state);
	return state;
}

uint32_t cent_get_pkt_len(void)
{
	uint32_t packet_len;
	cent_spi_readW(CENT_COMM_INFO_ADDR + offsetof(COMM_INFO_T, packet_len), (uint32_t*)&packet_len);
	return packet_len;
}

uint32_t cent_get_pkt_sr(void)
{
	uint32_t packet_sr;
	cent_spi_readW(CENT_COMM_INFO_ADDR + offsetof(COMM_INFO_T, pkt_sr), (uint32_t*)&packet_sr);
	return packet_sr;
}

uint32_t cent_get_pkt_lqi(void)
{
	uint32_t lqi;
	cent_spi_readW(CENT_COMM_INFO_ADDR + offsetof(COMM_INFO_T, lqi), (uint32_t*)&lqi);
	return lqi;
}

int32_t cent_get_pkt_rssi(void)
{
    int32_t pkt_rssi, elna;

    cent_spi_readW(CENT_COMM_INFO_ADDR + offsetof(COMM_INFO_T, pkt_rssi), (uint32_t*)&pkt_rssi);

    elna = (pkt_rssi >> 15) & 0x1;
    pkt_rssi &= 0x3FFF;
    
    if (pkt_rssi & 0x2000) {
        pkt_rssi = (pkt_rssi >> 6) * -1 + 256;
    } else {
        pkt_rssi = (pkt_rssi >> 6) * -1;
    }

    if (pkt_rssi > 100) {
        pkt_rssi = -115;
    }

    if (cent_nv_get_front_end() & FRONT_END_STATE_ELNA_EN) {
        if (elna) {
            pkt_rssi -= nvsets.cent.elna_rssi_offset;
        } else {
            pkt_rssi -= nvsets.cent.rssi_offset;
        }
    }else {
        pkt_rssi -= nvsets.cent.rssi_offset;
    }
    
	return pkt_rssi;
}

int cent_get_receiving_status(void)
{
    uint32_t packet_receiving = 0;
    if (CentauriCsrRead(0x40024008) & 0x1) {
        cent_spi_readW(CENT_COMM_INFO_ADDR + offsetof(COMM_INFO_T, packet_receiving), (uint32_t*)&packet_receiving);
    }
    return (packet_receiving == 1) ? 1 : 0;
}

int32_t cent_get_rssi(void)
{
	int32_t rssi, elna;

	cent_spi_readW(CENT_COMM_INFO_ADDR + offsetof(COMM_INFO_T, cca_rssi), (uint32_t*)&rssi);

    elna = (rssi >> 15) & 0x1;

    rssi &= 0x3FFF;

	if (rssi & 0x2000) {
		rssi = (rssi >> 6) * -1 + 256;
    } else {
		rssi = (rssi >> 6) * -1;
    }

    if (rssi > 100) {
        rssi = -115;
    }

    if (cent_nv_get_front_end() & FRONT_END_STATE_ELNA_EN) {
        if (elna) {
            rssi -= nvsets.cent.elna_rssi_offset;
        } else {
            rssi -= nvsets.cent.rssi_offset;
        }
    } else {
        rssi -= nvsets.cent.rssi_offset;
    }
    
	return rssi;
}

uint32_t cent_get_cca(void)
{
	uint32_t cca;
	cent_spi_readW(CENT_COMM_INFO_ADDR + offsetof(COMM_INFO_T, cca), (uint32_t*)&cca);
	return cca;
}

uint32_t cent_get_version(void)
{
    if (cent_ic_version == 0) {
        cent_spi_readW(0x7ffc, &cent_ic_version);
    }
    return cent_ic_version;
}

uint32_t cent_get_adc_status(void)
{
    return cent_adc_status;
}

void cent_set_adc_status(uint32_t status)
{
    cent_adc_status = status;
}
