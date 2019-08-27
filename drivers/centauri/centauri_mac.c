#include "vtprober.h"
#include "centauri_host.h"
#include "centauri_prober.h"
#include "centauri_mac.h"
#include "phy_csr.h"
#include "mac_csr.h"
#include "TransceiverMain.h"

static uint32_t Tx_loThr = (MAC_BUF_SIZE / 2);
static uint32_t Rx_HiThr = (MAC_BUF_SIZE / 2);

uint32_t bm_write_next;
uint32_t bm_read_next;

uint8_t cent_is_ack(void)
{
    uint32_t mhr;
    cent_spi_readW(MAC_RX_BUF_ADDR, &mhr);
    if ((mhr & 0x7) == 0x2) {
        return 1;
    } else {
        return 0;
    }
}

uint32_t cent_mac_tx_prefill(uint8_t *data, uint32_t length)
{
    if (length > MAC_TXBUF_LEN) {
        length = MAC_TXBUF_LEN;
    }

    vtprober_write_w_burst(length, MAC_TX_BUF_ADDR, data, (length+3)&0xfffc);

    bm_write_next = length;

    if (bm_write_next >= MAC_TXBUF_LEN) {
        bm_write_next = 0;
    }

    return length;
}

uint32_t cent_txlo_transfer(uint8_t *data, uint32_t length)
{
    uint32_t write_len;
    uint32_t buf_empty_size;

    buf_empty_size = MAC_TXBUF_LEN - Tx_loThr;

    if (length > buf_empty_size) {
        write_len = buf_empty_size;
    } else {
        write_len = length;
    }

    vtprober_write_w_burst(write_len, MAC_TX_BUF_ADDR+bm_write_next, data, (write_len+3)&0xfffc);

    bm_write_next += write_len;
    if (bm_write_next >= MAC_TXBUF_LEN) {
        bm_write_next -= MAC_TXBUF_LEN;
    }

    // update tx buffer size
    if (write_len){
        cent_spi_writeW(MAC_BM_TXBSR, (BM_TXBSR_SWSIZE_KICK_MASK | (write_len << BM_TXBS_SWSIZE_POS)));
    }

    return write_len;
}

extern uint32_t rx_complete;

uint32_t cent_rxHi_receive(uint8_t *data, uint32_t len)
{
    uint32_t *pData = (uint32_t*)data;
    uint32_t read_len;

    if (len > Rx_HiThr) {
        read_len = Rx_HiThr;
    } else {
        read_len = len;
    }

    vtprober_read_w_burst(read_len, MAC_RX_BUF_ADDR+bm_read_next, pData, (read_len+3)&0xfffc);

    bm_read_next += read_len;
    if (bm_read_next >= MAC_RXBUF_LEN) {
        bm_read_next = 0;
    }

    if (rx_complete == 0) {
    	vtprober_write_w(MAC_BM_RXBSR, (BM_RXBSR_SWSIZE_KICK_MASK | (read_len << BM_RXBSR_SWSIZE_POS) | MAC_RXBUF_LEN));
    } else {
		rx_complete = 0;
    }

    return read_len;
}

uint8_t cent_is_fcs_match(void)
{
    uint32_t packet_status;
    packet_status = cent_get_pkt_sr();
    if (packet_status & SPC_PKT_SR__CSR_FCS_MATCH_MASK) {
        return 1;
    } else {
        return 0;
    }
}

uint8_t cent_fcs_type(void)
{
    uint32_t packet_status;
	packet_status = cent_get_pkt_sr();
    if (packet_status & SPC_PKT_SR__CSR_IS_FCS32_MASK) {
        return FCS_32;
    } else {
        return FCS_16;
    }
}
