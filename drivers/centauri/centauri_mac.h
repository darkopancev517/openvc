#ifndef CENTAURI_MAC_H
#define CENTAURI_MAC_H

#ifdef __cplusplus
extern "C" {
#endif

/* IER Interrupt Enable Register */
#define  TXE_TXCMP_POS      0   // R/W DEFAULT:0 , IER TX COMPLETE
#define  TXE_TXCMP_EN       (0x01ul << TXE_TXCMP_POS)
#define  TXE_TXCMP_DIS      ~TXE_TXCMP_EN
#define  RXE_RXCMP_POS      1   // R/W DEFAULT:0 , IER RX COMPLETE
#define  RXE_RXCMP_EN       (0x01ul << RXE_RXCMP_POS)
#define  TXB_HITHR_POS      8   // R/W DEFAULT:0 , IER TX BUFFER HIGH THRESHOLD
#define  TXB_HITHR_EN       (0x01ul << TXB_HITHR_POS)
#define  TXB_LOTHR_POS      9   // R/W DEFAULT:0 , IER TX BUFFER LOW THRESHOLD
#define  TXB_LOTHR_EN       (0x01ul << TXB_LOTHR_POS)
#define  TXB_LOTHR_DIS      ~TXB_LOTHR_EN
#define  TXB_ALERT_POS      10  // R/W DEFAULT:0 , IER TX BUFFER ALERT
#define  TXB_ALERT_EN       (0x01ul << TXB_ALERT_POS)
#define  TXB_UNFLW_POS      11  // R/W DEFAULT:0 , IER TX BUFFER UNDERFLOW
#define  TXB_UNFLW_EN       (0x01ul << TXB_UNFLW_POS)
#define  RXB_HITHR_POS      12  // R/W DEFAULT:0 , IER RX BUFFER HIGH THRESHOLD
#define  RXB_HITHR_EN       (0x01ul << RXB_HITHR_POS)
#define  RXB_LOTHR_POS      13  // R/W DEFAULT:0 , IER RX BUFFER LOW THRESHOLD
#define  RXB_LOTHR_EN       (0x01ul << RXB_LOTHR_POS)
#define  RXB_ALERT_POS      14  // R/W DEFAULT:0 , IER RX BUFFER ALERT
#define  RXB_ALERT_EN       (0x01ul << RXB_ALERT_POS)
#define  RXB_OVFLW_POS      15  // R/W DEFAULT:0 , IER RX BUFFER OVERFLOW
#define  RXB_OVFLW_EN       (0x01ul << RXB_OVFLW_POS)

/* ISR Interrupr Status Register , W1C */
#define TXE_TXCMP_CLR       (0x01ul << TXE_TXCMP_POS)
#define RXE_RXCMP_CLR       (0x01ul << RXE_RXCMP_POS)
#define TXB_HITHR_CLR       (0x01ul << TXB_HITHR_POS)
#define TXB_LOTHR_CLR       (0x01ul << TXB_LOTHR_POS)
#define TXB_ALERT_CLR       (0x01ul << TXB_ALERT_POS)
#define TXB_UNFLW_CLR       (0x01ul << TXB_UNFLW_POS)
#define RXB_HITHR_CLR       (0x01ul << RXB_HITHR_POS)
#define RXB_LOTHR_CLR       (0x01ul << RXB_LOTHR_POS)
#define RXB_ALERT_CLR       (0x01ul << RXB_ALERT_POS)
#define RXB_OVFLW_CLR       (0x01ul << RXB_OVFLW_POS)

#define ISR_TXE_TXCMP       TXE_TXCMP_CLR
#define ISR_RXE_RXCMP       RXE_RXCMP_CLR
#define ISR_TXB_HITHR       TXB_HITHR_CLR
#define ISR_TXB_LOTHR       TXB_LOTHR_CLR
#define ISR_TXB_ALERT       TXB_ALERT_CLR
#define ISR_TXB_UNFLW       TXB_UNFLW_CLR
#define ISR_RXB_HITHR       RXB_HITHR_CLR
#define ISR_RXB_LOTHR       RXB_LOTHR_CLR
#define ISR_RXB_ALERT       RXB_ALERT_CLR
#define ISR_RXB_OVFLW       RXB_OVFLW_CLR

#define MAC_RX_BUF_ADDR     0x20010600
#define MAC_TX_BUF_ADDR     0x20010700
#define MAC_BM_TXBSR        0x40020098
#define MAC_BM_RXBSR        0x4002009C

#define MAC_RXBUF_LEN       256
#define MAC_TXBUF_LEN       256
#define MAC_BUF_SIZE        256

#define BM_TXBSR_SWSIZE_KICK_POS 30
#define BM_TXBSR_SWSIZE_KICK_MASK 0x40000000ul
#define BM_TXBS_SWSIZE_POS 16
#define BM_TXBSR_SWSIZE_MASK 0x03FF0000ul
#define BM_TXBSR_SWSIZE_CLEAR ~BM_TXBSR_SWSIZE_MASK
#define BM_RXBSR_SWSIZE_KICK_POS 30
#define BM_RXBSR_SWSIZE_KICK_MASK 0x40000000ul
#define BM_RXBSR_SWSIZE_POS 16
#define BM_RXBSR_SWSIZE_MASK 0x03FF0000ul

uint32_t cent_txlo_transfer(uint8_t *data, uint32_t length);

uint32_t cent_rxHi_receive(uint8_t *data, uint32_t len);

uint8_t cent_is_fcs_match(void);

uint8_t cent_fcs_type(void);

uint32_t cent_get_pkt_sr(void);

uint32_t cent_get_pkt_len(void);

uint8_t cent_is_ack(void);

uint32_t cent_mac_tx_prefill(uint8_t *data, uint32_t length);

#ifdef __cplusplus
}
#endif

#endif /* CENTAURI_MAC_H */
