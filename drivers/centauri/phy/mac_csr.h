#ifndef MAC_CSR_H
#define MAC_CSR_H

#ifdef __cplusplus
extern "C" {
#endif

#ifndef CSR_ACCESS
#define CSR_ACCESS(x) (*((volatile unsigned long *)(x)))
#endif

/** Block mac_csr

*/
#define MAC_CSR_BASE 0x40020000

/*****************************************************************************/

/** Reg TXENG_BADDR
TXENG Base Address (RET)
*/
#define MAC_CSR__TXENG_BADDR CSR_ACCESS(MAC_CSR_BASE + 0x00000000)

/** Field csr_txe_baddr
TXENG Base Address
*/
#define TXENG_BADDR__CSR_TXE_BADDR_POS 0
#define TXENG_BADDR__CSR_TXE_BADDR_MASK 0xFFFFFFFF

/*****************************************************************************/

/** Reg TXENG_SADDR
TXENG Start Address
*/
#define MAC_CSR__TXENG_SADDR CSR_ACCESS(MAC_CSR_BASE + 0x00000004)

/** Field csr_txe_saddr
TXENG Start Address
*/
#define TXENG_SADDR__CSR_TXE_SADDR_POS 0
#define TXENG_SADDR__CSR_TXE_SADDR_MASK 0xFFFFFFFF

/*****************************************************************************/

/** Reg TXENG_EADDR
TXENG End Address (RET)
*/
#define MAC_CSR__TXENG_EADDR CSR_ACCESS(MAC_CSR_BASE + 0x00000008)

/** Field csr_txe_eaddr
TXENG End Address
*/
#define TXENG_EADDR__CSR_TXE_EADDR_POS 0
#define TXENG_EADDR__CSR_TXE_EADDR_MASK 0xFFFFFFFF

/*****************************************************************************/

/** Reg TXENG_CADDR
TXENG Current Address
*/
#define MAC_CSR__TXENG_CADDR CSR_ACCESS(MAC_CSR_BASE + 0x0000000C)

/** Field csr_txe_caddr
TXENG Current Address
*/
#define TXENG_CADDR__CSR_TXE_CADDR_POS 0
#define TXENG_CADDR__CSR_TXE_CADDR_MASK 0xFFFFFFFF

/*****************************************************************************/

/** Reg TXENG_CTRL
TXENG Control Register
*/
#define MAC_CSR__TXENG_CTRL CSR_ACCESS(MAC_CSR_BASE + 0x00000010)

/** Field csr_txe_plen
TXENG Packet Length
*/
#define TXENG_CTRL__CSR_TXE_PLEN_POS 0
#define TXENG_CTRL__CSR_TXE_PLEN_MASK 0x000007FF

/** Field csr_txe_kick
TXENG Kick Signals
*/
#define TXENG_CTRL__CSR_TXE_KICK_POS 31
#define TXENG_CTRL__CSR_TXE_KICK_MASK 0x80000000

/*****************************************************************************/

/** Reg RXENG_BADDR
RXENG Base Address (RET)
*/
#define MAC_CSR__RXENG_BADDR CSR_ACCESS(MAC_CSR_BASE + 0x00000020)

/** Field csr_rxe_baddr
RXENG Base Address
*/
#define RXENG_BADDR__CSR_RXE_BADDR_POS 0
#define RXENG_BADDR__CSR_RXE_BADDR_MASK 0xFFFFFFFF

/*****************************************************************************/

/** Reg RXENG_SADDR
RXENG Start Address
*/
#define MAC_CSR__RXENG_SADDR CSR_ACCESS(MAC_CSR_BASE + 0x00000024)

/** Field csr_rxe_saddr
RXENG Start Address
*/
#define RXENG_SADDR__CSR_RXE_SADDR_POS 0
#define RXENG_SADDR__CSR_RXE_SADDR_MASK 0xFFFFFFFF

/*****************************************************************************/

/** Reg RXENG_EADDR
RXENG End Address (RET)
*/
#define MAC_CSR__RXENG_EADDR CSR_ACCESS(MAC_CSR_BASE + 0x00000028)

/** Field csr_rxe_eaddr
RXENG End Address
*/
#define RXENG_EADDR__CSR_RXE_EADDR_POS 0
#define RXENG_EADDR__CSR_RXE_EADDR_MASK 0xFFFFFFFF

/*****************************************************************************/

/** Reg RXENG_CADDR
RXENG Current Address
*/
#define MAC_CSR__RXENG_CADDR CSR_ACCESS(MAC_CSR_BASE + 0x0000002C)

/** Field csr_rxe_caddr
RXENG Current Address
*/
#define RXENG_CADDR__CSR_RXE_CADDR_POS 0
#define RXENG_CADDR__CSR_RXE_CADDR_MASK 0xFFFFFFFF

/*****************************************************************************/

/** Reg RXENG_CTRL
RXENG Control Register
*/
#define MAC_CSR__RXENG_CTRL CSR_ACCESS(MAC_CSR_BASE + 0x00000030)

/** Field csr_rxe_plen
RXENG Packet Length
*/
#define RXENG_CTRL__CSR_RXE_PLEN_POS 0
#define RXENG_CTRL__CSR_RXE_PLEN_MASK 0x000007FF

/** Field csr_rxe_wdmode
Set RXENG in all word access mode. Could speed up the access when the RX memory allocation isl word boundary.
*/
#define RXENG_CTRL__CSR_RXE_WDMODE_POS 16
#define RXENG_CTRL__CSR_RXE_WDMODE_MASK 0x00010000

/*****************************************************************************/

/** Reg IER
IER (RET)
*/
#define MAC_CSR__IER CSR_ACCESS(MAC_CSR_BASE + 0x00000040)

/** Field ier_txe_txcmp
IER TX Complete
*/
#define IER__IER_TXE_TXCMP_POS 0
#define IER__IER_TXE_TXCMP_MASK 0x00000001

/** Field ier_rxe_rxcmp
IER RX Complete
*/
#define IER__IER_RXE_RXCMP_POS 1
#define IER__IER_RXE_RXCMP_MASK 0x00000002

/** Field ier_txb_hithr
IER TX Buffer High Threshold
*/
#define IER__IER_TXB_HITHR_POS 8
#define IER__IER_TXB_HITHR_MASK 0x00000100

/** Field ier_txb_lothr
IER TX Buffer Low Threshold
*/
#define IER__IER_TXB_LOTHR_POS 9
#define IER__IER_TXB_LOTHR_MASK 0x00000200

/** Field ier_txb_alert
IER TX Buffer Alert
*/
#define IER__IER_TXB_ALERT_POS 10
#define IER__IER_TXB_ALERT_MASK 0x00000400

/** Field ier_txb_unflw
IER TX Buffer Underflow
*/
#define IER__IER_TXB_UNFLW_POS 11
#define IER__IER_TXB_UNFLW_MASK 0x00000800

/** Field ier_rxb_hithr
IER RX Buffer High Threshold
*/
#define IER__IER_RXB_HITHR_POS 12
#define IER__IER_RXB_HITHR_MASK 0x00001000

/** Field ier_rxb_lothr
IER RX Buffer Low Threshold
*/
#define IER__IER_RXB_LOTHR_POS 13
#define IER__IER_RXB_LOTHR_MASK 0x00002000

/** Field ier_rxb_alert
IER RX Buffer Alert
*/
#define IER__IER_RXB_ALERT_POS 14
#define IER__IER_RXB_ALERT_MASK 0x00004000

/** Field ier_rxb_ovflw
IER RX Buffer Overflow
*/
#define IER__IER_RXB_OVFLW_POS 15
#define IER__IER_RXB_OVFLW_MASK 0x00008000

/*****************************************************************************/

/** Reg ISR
ISR
*/
#define MAC_CSR__ISR CSR_ACCESS(MAC_CSR_BASE + 0x00000044)

/** Field isr_txe_txcmp
ISR TX Complete
*/
#define ISR__ISR_TXE_TXCMP_POS 0
#define ISR__ISR_TXE_TXCMP_MASK 0x00000001

/** Field isr_rxe_rxcmp
ISR RX Complete
*/
#define ISR__ISR_RXE_RXCMP_POS 1
#define ISR__ISR_RXE_RXCMP_MASK 0x00000002

/** Field isr_txb_hithr
ISR TX Buffer High Threshold
*/
#define ISR__ISR_TXB_HITHR_POS 8
#define ISR__ISR_TXB_HITHR_MASK 0x00000100

/** Field isr_txb_lothr
ISR TX Buffer Low Threshold
*/
#define ISR__ISR_TXB_LOTHR_POS 9
#define ISR__ISR_TXB_LOTHR_MASK 0x00000200

/** Field isr_txb_alert
ISR TX Buffer Alert
*/
#define ISR__ISR_TXB_ALERT_POS 10
#define ISR__ISR_TXB_ALERT_MASK 0x00000400

/** Field isr_txb_unflw
ISR TX Buffer Underflow
*/
#define ISR__ISR_TXB_UNFLW_POS 11
#define ISR__ISR_TXB_UNFLW_MASK 0x00000800

/** Field isr_rxb_hithr
ISR RX Buffer High Threshold
*/
#define ISR__ISR_RXB_HITHR_POS 12
#define ISR__ISR_RXB_HITHR_MASK 0x00001000

/** Field isr_rxb_lothr
ISR RX Buffer Low Threshold
*/
#define ISR__ISR_RXB_LOTHR_POS 13
#define ISR__ISR_RXB_LOTHR_MASK 0x00002000

/** Field isr_rxb_alert
ISR RX Buffer Alert
*/
#define ISR__ISR_RXB_ALERT_POS 14
#define ISR__ISR_RXB_ALERT_MASK 0x00004000

/** Field isr_rxb_ovflw
ISR RX Buffer Overflow
*/
#define ISR__ISR_RXB_OVFLW_POS 15
#define ISR__ISR_RXB_OVFLW_MASK 0x00008000

/*****************************************************************************/

/** Reg DMA_CTRL
DMA_CTRL (RET)
*/
#define MAC_CSR__DMA_CTRL CSR_ACCESS(MAC_CSR_BASE + 0x00000048)

/** Field csr_dma_lb
DMA Loopback (test mode, doesn not need to retent it)
*/
#define DMA_CTRL__CSR_DMA_LB_POS 0
#define DMA_CTRL__CSR_DMA_LB_MASK 0x00000001

/** Field csr_transend
DMA translate endian enable
*/
#define DMA_CTRL__CSR_TRANSEND_POS 1
#define DMA_CTRL__CSR_TRANSEND_MASK 0x00000002

/** Field csr_txe_en
TXENG Enable
*/
#define DMA_CTRL__CSR_TXE_EN_POS 2
#define DMA_CTRL__CSR_TXE_EN_MASK 0x00000004

/** Field csr_rxe_en
RXENG Enable
*/
#define DMA_CTRL__CSR_RXE_EN_POS 3
#define DMA_CTRL__CSR_RXE_EN_MASK 0x00000008

/** Field csr_fixed_txstart
If = 1, TX Start Address = TX Base Address. It's not necessary to configure the TX Start Address when enable.
*/
#define DMA_CTRL__CSR_FIXED_TXSTART_POS 4
#define DMA_CTRL__CSR_FIXED_TXSTART_MASK 0x00000010

/** Field csr_fixed_rxstart
If = 1, RX Start Address = RX Base Address. It's not necessary to configure the RX Start Address when enable.
*/
#define DMA_CTRL__CSR_FIXED_RXSTART_POS 5
#define DMA_CTRL__CSR_FIXED_RXSTART_MASK 0x00000020

/** Field csr_continuous_mode
If = 1, Tx and RX will enter the continuous mode. The length field is no longer be used and will TX/RX until reset.
*/
#define DMA_CTRL__CSR_CONTINUOUS_MODE_POS 6
#define DMA_CTRL__CSR_CONTINUOUS_MODE_MASK 0x00000040

/*****************************************************************************/

/** Reg AHBS_CR
AHB Slave Interface Control Register
*/
#define MAC_CSR__AHBS_CR CSR_ACCESS(MAC_CSR_BASE + 0x0000004C)

/** Field csr_dly_rd
HREADY Delay when READ Command (default: 4)
*/
#define AHBS_CR__CSR_DLY_RD_POS 0
#define AHBS_CR__CSR_DLY_RD_MASK 0x00000007

/** Field csr_dly_wr
HREADY Delay when WRITE Command (default: 3)
*/
#define AHBS_CR__CSR_DLY_WR_POS 4
#define AHBS_CR__CSR_DLY_WR_MASK 0x00000070

/*****************************************************************************/

/** Reg SPC_CTRL
SPC_CTRL
*/
#define MAC_CSR__SPC_CTRL CSR_ACCESS(MAC_CSR_BASE + 0x00000050)

/** Field csr_spc_lb
SPC Loopback
*/
#define SPC_CTRL__CSR_SPC_LB_POS 4
#define SPC_CTRL__CSR_SPC_LB_MASK 0x00000010

/** Field csr_lb_lowspeed
If CSR = 1, the spc loopback will be in the low speed mode.
*/
#define SPC_CTRL__CSR_LB_LOWSPEED_POS 5
#define SPC_CTRL__CSR_LB_LOWSPEED_MASK 0x00000020

/** Field csr_lb_interval
The byte interval when spc loopback is in the low speed mode.
*/
#define SPC_CTRL__CSR_LB_INTERVAL_POS 16
#define SPC_CTRL__CSR_LB_INTERVAL_MASK 0x03FF0000

/*****************************************************************************/

/** Reg SPC_TX_CTRL
SPC_TX_CTRL
*/
#define MAC_CSR__SPC_TX_CTRL CSR_ACCESS(MAC_CSR_BASE + 0x00000054)

/** Field csr_tx_opmode
TX Operation Mode, 0: Bypass. 1: with CRC (by csr_tx_fcstype)
*/
#define SPC_TX_CTRL__CSR_TX_OPMODE_POS 0
#define SPC_TX_CTRL__CSR_TX_OPMODE_MASK 0x0000000F

/** Field csr_tx_fcs_type
The Mode for the TX FCS
0: CRC-32, 1: CRC-16
*/
#define SPC_TX_CTRL__CSR_TX_FCS_TYPE_POS 4
#define SPC_TX_CTRL__CSR_TX_FCS_TYPE_MASK 0x00000010

/** Field csr_tx_mhr_ofst
The start offset of MHR, it can be used to calculate FCS
*/
#define SPC_TX_CTRL__CSR_TX_MHR_OFST_POS 8
#define SPC_TX_CTRL__CSR_TX_MHR_OFST_MASK 0x00000F00

/** Field csr_tx_psdu_len
PSDU Length, FCS is included
*/
#define SPC_TX_CTRL__CSR_TX_PSDU_LEN_POS 16
#define SPC_TX_CTRL__CSR_TX_PSDU_LEN_MASK 0x07FF0000

/*****************************************************************************/

/** Reg SPC_RX_CTRL
SPC_RX_CTRL (RET)
*/
#define MAC_CSR__SPC_RX_CTRL CSR_ACCESS(MAC_CSR_BASE + 0x00000058)

/** Field csr_rx_opmode
RX Operation Mode, 0: Bypass. 1: with CRC (by phy2mac_rx_fcstype).
2: with CRC (by SW CSR)
*/
#define SPC_RX_CTRL__CSR_RX_OPMODE_POS 0
#define SPC_RX_CTRL__CSR_RX_OPMODE_MASK 0x0000000F

/** Field csr_rx_fcs_type
The Mode for the RX FCS (only work when opmode = 2)
0: CRC-32, 1: CRC-16
*/
#define SPC_RX_CTRL__CSR_RX_FCS_TYPE_POS 4
#define SPC_RX_CTRL__CSR_RX_FCS_TYPE_MASK 0x00000010

/** Field csr_rx_mhr_ofst
The start offset of MHR, it can be used to calculate FCS and RX Filter
*/
#define SPC_RX_CTRL__CSR_RX_MHR_OFST_POS 8
#define SPC_RX_CTRL__CSR_RX_MHR_OFST_MASK 0x00000F00

/*****************************************************************************/

/** Reg SPC_RF_CTRL
SPC_RF_CTRL (RET)
*/
#define MAC_CSR__SPC_RF_CTRL CSR_ACCESS(MAC_CSR_BASE + 0x00000060)

/** Field csr_rf_en_bea
RX Filter Beacon Frame Filtering Enable
*/
#define SPC_RF_CTRL__CSR_RF_EN_BEA_POS 0
#define SPC_RF_CTRL__CSR_RF_EN_BEA_MASK 0x00000001

/** Field csr_rf_en_dat
RX Filter Data Frame Filtering Enable
*/
#define SPC_RF_CTRL__CSR_RF_EN_DAT_POS 1
#define SPC_RF_CTRL__CSR_RF_EN_DAT_MASK 0x00000002

/** Field csr_rf_en_ack
RX Filter ACK Frame Filtering Enable
*/
#define SPC_RF_CTRL__CSR_RF_EN_ACK_POS 2
#define SPC_RF_CTRL__CSR_RF_EN_ACK_MASK 0x00000004

/** Field csr_rf_en_cmd
RX Filter MAC Command Filtering Enable
*/
#define SPC_RF_CTRL__CSR_RF_EN_CMD_POS 3
#define SPC_RF_CTRL__CSR_RF_EN_CMD_MASK 0x00000008

/** Field csr_rf_chkspid
SPID Check enable
*/
#define SPC_RF_CTRL__CSR_RF_CHKSPID_POS 4
#define SPC_RF_CTRL__CSR_RF_CHKSPID_MASK 0x00000010

/** Field csr_rf_promismd
macPromiscuousMode
*/
#define SPC_RF_CTRL__CSR_RF_PROMISMD_POS 5
#define SPC_RF_CTRL__CSR_RF_PROMISMD_MASK 0x00000020

/** Field csr_rf_rxonlysa
RX if only Source Information
*/
#define SPC_RF_CTRL__CSR_RF_RXONLYSA_POS 6
#define SPC_RF_CTRL__CSR_RF_RXONLYSA_MASK 0x00000040

/** Field csr_rf_rxonlyda
RX if only Destination Address
*/
#define SPC_RF_CTRL__CSR_RF_RXONLYDA_POS 7
#define SPC_RF_CTRL__CSR_RF_RXONLYDA_MASK 0x00000080

/*****************************************************************************/

/** Reg SPC_RF_SR1
SPC_RF_Setting Register 1 (RET)
*/
#define MAC_CSR__SPC_RF_SR1 CSR_ACCESS(MAC_CSR_BASE + 0x00000064)

/** Field csr_macpanid
macPanID
*/
#define SPC_RF_SR1__CSR_MACPANID_POS 0
#define SPC_RF_SR1__CSR_MACPANID_MASK 0x0000FFFF

/** Field csr_macsimadr
macSimpleAddress
*/
#define SPC_RF_SR1__CSR_MACSIMADR_POS 16
#define SPC_RF_SR1__CSR_MACSIMADR_MASK 0x00FF0000

/** Field csr_rf_acksn
Sequence Number for ACK Frame
*/
#define SPC_RF_SR1__CSR_RF_ACKSN_POS 24
#define SPC_RF_SR1__CSR_RF_ACKSN_MASK 0xFF000000

/*****************************************************************************/

/** Reg SPC_RF_SR2
SPC_RF_Setting Register 2 (RET)
*/
#define MAC_CSR__SPC_RF_SR2 CSR_ACCESS(MAC_CSR_BASE + 0x00000068)

/** Field csr_macshradr
macShortAddress
*/
#define SPC_RF_SR2__CSR_MACSHRADR_POS 0
#define SPC_RF_SR2__CSR_MACSHRADR_MASK 0x0000FFFF

/*****************************************************************************/

/** Reg SPC_RF_SR3
SPC_RF_Setting Register 3 
*/
#define MAC_CSR__SPC_RF_SR3 CSR_ACCESS(MAC_CSR_BASE + 0x0000006C)

/** Field csr_macextadr_h
macExtendedAddress High Word
*/
#define SPC_RF_SR3__CSR_MACEXTADR_H_POS 0
#define SPC_RF_SR3__CSR_MACEXTADR_H_MASK 0xFFFFFFFF

/*****************************************************************************/

/** Reg SPC_RF_SR4
SPC_RF_Setting Register 4 
*/
#define MAC_CSR__SPC_RF_SR4 CSR_ACCESS(MAC_CSR_BASE + 0x00000070)

/** Field csr_macextadr_l
macExtendedAddress Low Word
*/
#define SPC_RF_SR4__CSR_MACEXTADR_L_POS 0
#define SPC_RF_SR4__CSR_MACEXTADR_L_MASK 0xFFFFFFFF

/*****************************************************************************/

/** Reg SPC_FCS_CR1
SPC FCS Control Register 1
*/
#define MAC_CSR__SPC_FCS_CR1 CSR_ACCESS(MAC_CSR_BASE + 0x00000074)

/** Field csr_fcs_clrcr
The clear position (0: start, 1: end)
*/
#define SPC_FCS_CR1__CSR_FCS_CLRCR_POS 0
#define SPC_FCS_CR1__CSR_FCS_CLRCR_MASK 0x00000001

/** Field csr_fcs_endian
The endian output to phy or input from phy
(0: current/default. Low byte first. As 802.15.4; 1: High byte first, Swap)
*/
#define SPC_FCS_CR1__CSR_FCS_ENDIAN_POS 1
#define SPC_FCS_CR1__CSR_FCS_ENDIAN_MASK 0x00000002

/** Field csr_fcs_match_method
The method to match FCS. (0: by magic pattern. 1: by content)
*/
#define SPC_FCS_CR1__CSR_FCS_MATCH_METHOD_POS 2
#define SPC_FCS_CR1__CSR_FCS_MATCH_METHOD_MASK 0x00000004

/** Field csr_fcs16_init
0: 0x0, 1: 0xFFFFFFFF 
(802.15.4 : 0; china: 1)
*/
#define SPC_FCS_CR1__CSR_FCS16_INIT_POS 8
#define SPC_FCS_CR1__CSR_FCS16_INIT_MASK 0x00000100

/** Field csr_fcs16_input
0: as input, 1: reverse input  
(802.15.4 : 1; china: 1)
*/
#define SPC_FCS_CR1__CSR_FCS16_INPUT_POS 9
#define SPC_FCS_CR1__CSR_FCS16_INPUT_MASK 0x00000200

/** Field csr_fcs16_output
0: as ouput, 1 : reverse output  
(802.15.4 : 1; china: 1)
*/
#define SPC_FCS_CR1__CSR_FCS16_OUTPUT_POS 10
#define SPC_FCS_CR1__CSR_FCS16_OUTPUT_MASK 0x00000400

/** Field csr_fcs16_1com
0: no 1's complement, 1: need 1's complete before output  
(802.15.4 : 0; china: 1)
*/
#define SPC_FCS_CR1__CSR_FCS16_1COM_POS 11
#define SPC_FCS_CR1__CSR_FCS16_1COM_MASK 0x00000800

/** Field csr_fcs32_init
0: 0x0, 1: 0xFFFFFFFF
*/
#define SPC_FCS_CR1__CSR_FCS32_INIT_POS 12
#define SPC_FCS_CR1__CSR_FCS32_INIT_MASK 0x00001000

/** Field csr_fcs32_input
0: as input, 1: reverse input
*/
#define SPC_FCS_CR1__CSR_FCS32_INPUT_POS 13
#define SPC_FCS_CR1__CSR_FCS32_INPUT_MASK 0x00002000

/** Field csr_fcs32_output
0: as ouput, 1 : reverse output
*/
#define SPC_FCS_CR1__CSR_FCS32_OUTPUT_POS 14
#define SPC_FCS_CR1__CSR_FCS32_OUTPUT_MASK 0x00004000

/** Field csr_fcs32_1com
0: no 1's complement, 1: need 1's complete before output
*/
#define SPC_FCS_CR1__CSR_FCS32_1COM_POS 15
#define SPC_FCS_CR1__CSR_FCS32_1COM_MASK 0x00008000

/** Field csr_fcs16_pattern
The match pattern for FCS16
(802.15.4: 0; china: 470F)
*/
#define SPC_FCS_CR1__CSR_FCS16_PATTERN_POS 16
#define SPC_FCS_CR1__CSR_FCS16_PATTERN_MASK 0xFFFF0000

/*****************************************************************************/

/** Reg SPC_FCS_CR2
SPC FCS Control Register 2
*/
#define MAC_CSR__SPC_FCS_CR2 CSR_ACCESS(MAC_CSR_BASE + 0x00000078)

/** Field csr_fcs32_pattern
The match pattern for FCS32
*/
#define SPC_FCS_CR2__CSR_FCS32_PATTERN_POS 0
#define SPC_FCS_CR2__CSR_FCS32_PATTERN_MASK 0xFFFFFFFF

/*****************************************************************************/

/** Reg SPC_FCS_IR
SPC TX FCS Information Register
*/
#define MAC_CSR__SPC_FCS_IR CSR_ACCESS(MAC_CSR_BASE + 0x0000007C)

/** Field csr_txfcs_result
The result of TXP FCS
*/
#define SPC_FCS_IR__CSR_TXFCS_RESULT_POS 0
#define SPC_FCS_IR__CSR_TXFCS_RESULT_MASK 0xFFFFFFFF

/*****************************************************************************/

/** Reg SPC_PKT_SR
SPC Packet Status Register
*/
#define MAC_CSR__SPC_PKT_SR CSR_ACCESS(MAC_CSR_BASE + 0x00000080)

/** Field csr_rf_match
CSR = 1, If pass the rx_filter. (or rx_filter is disabled)
*/
#define SPC_PKT_SR__CSR_RF_MATCH_POS 0
#define SPC_PKT_SR__CSR_RF_MATCH_MASK 0x00000001

/** Field csr_fcs_match
CSR = 1, If pass the CRC validation.
*/
#define SPC_PKT_SR__CSR_FCS_MATCH_POS 1
#define SPC_PKT_SR__CSR_FCS_MATCH_MASK 0x00000002

/** Field csr_is_fcs16
the current rx packet is fcs16
*/
#define SPC_PKT_SR__CSR_IS_FCS16_POS 2
#define SPC_PKT_SR__CSR_IS_FCS16_MASK 0x00000004

/** Field csr_is_fcs32
the current rx packet is fcs32
*/
#define SPC_PKT_SR__CSR_IS_FCS32_POS 3
#define SPC_PKT_SR__CSR_IS_FCS32_MASK 0x00000008

/** Field csr_rxp_overflow
RXP module detects an overflow event.
*/
#define SPC_PKT_SR__CSR_RXP_OVERFLOW_POS 4
#define SPC_PKT_SR__CSR_RXP_OVERFLOW_MASK 0x00000010

/** Field csr_phr_error
CSR = 1, If PHDR is wrong. (Header CRC Fail).
HW auto clear this field when receiving the next packet.
*/
#define SPC_PKT_SR__CSR_PHR_ERROR_POS 8
#define SPC_PKT_SR__CSR_PHR_ERROR_MASK 0x00000100

/*****************************************************************************/

/** Reg BM_THSR
Buffer Monitor Setting Threshold (RET)
*/
#define MAC_CSR__BM_THSR CSR_ACCESS(MAC_CSR_BASE + 0x00000090)

/** Field csr_txb_hithr
High threshold for the TX buffer.
*/
#define BM_THSR__CSR_TXB_HITHR_POS 0
#define BM_THSR__CSR_TXB_HITHR_MASK 0x000000FF

/** Field csr_txb_lothr
Low threshold for the TX buffer.
*/
#define BM_THSR__CSR_TXB_LOTHR_POS 8
#define BM_THSR__CSR_TXB_LOTHR_MASK 0x0000FF00

/** Field csr_rxb_hithr
High threshold for the RX buffer.
*/
#define BM_THSR__CSR_RXB_HITHR_POS 16
#define BM_THSR__CSR_RXB_HITHR_MASK 0x00FF0000

/** Field csr_rxb_lothr
Low threshold for the RX buffer.
*/
#define BM_THSR__CSR_RXB_LOTHR_POS 24
#define BM_THSR__CSR_RXB_LOTHR_MASK 0xFF000000

/*****************************************************************************/

/** Reg BM_CR
Buffer Monitor Control Register
*/
#define MAC_CSR__BM_CR CSR_ACCESS(MAC_CSR_BASE + 0x00000094)

/** Field csr_txb_hithr_en
High threshold enable for the TX buffer.
*/
#define BM_CR__CSR_TXB_HITHR_EN_POS 0
#define BM_CR__CSR_TXB_HITHR_EN_MASK 0x00000001

/** Field csr_txb_lothr_en
Low threshold enable for the TX buffer.
*/
#define BM_CR__CSR_TXB_LOTHR_EN_POS 1
#define BM_CR__CSR_TXB_LOTHR_EN_MASK 0x00000002

/** Field csr_txb_unflw_en
Underflow enable for the TX buffer.
*/
#define BM_CR__CSR_TXB_UNFLW_EN_POS 2
#define BM_CR__CSR_TXB_UNFLW_EN_MASK 0x00000004

/** Field csr_rxb_hithr_en
High threshold enable for the RX buffer.
*/
#define BM_CR__CSR_RXB_HITHR_EN_POS 3
#define BM_CR__CSR_RXB_HITHR_EN_MASK 0x00000008

/** Field csr_rxb_lothr_en
Low threshold enable for the RX buffer.
*/
#define BM_CR__CSR_RXB_LOTHR_EN_POS 4
#define BM_CR__CSR_RXB_LOTHR_EN_MASK 0x00000010

/** Field csr_rxb_ovflw_en
Overflow enable for the TX buffer.
*/
#define BM_CR__CSR_RXB_OVFLW_EN_POS 5
#define BM_CR__CSR_RXB_OVFLW_EN_MASK 0x00000020

/** Field csr_txb_hwclr_en
TX Buffer counter is cleared by HW.TX Complete
*/
#define BM_CR__CSR_TXB_HWCLR_EN_POS 8
#define BM_CR__CSR_TXB_HWCLR_EN_MASK 0x00000100

/*****************************************************************************/

/** Reg BM_TXBSR
Buffer Monitor SW Size Update Setting Register
*/
#define MAC_CSR__BM_TXBSR CSR_ACCESS(MAC_CSR_BASE + 0x00000098)

/** Field csr_txb_swsize
SW TX buffer Size update
*/
#define BM_TXBSR__CSR_TXB_SWSIZE_POS 16
#define BM_TXBSR__CSR_TXB_SWSIZE_MASK 0x03FF0000

/** Field csr_txb_swsize_kick
SW TX buffer Size update trigger signal
*/
#define BM_TXBSR__CSR_TXB_SWSIZE_KICK_POS 30
#define BM_TXBSR__CSR_TXB_SWSIZE_KICK_MASK 0x40000000

/** Field csr_txb_swclr_kick
SW-MAC force to clear the TX Buffer
*/
#define BM_TXBSR__CSR_TXB_SWCLR_KICK_POS 31
#define BM_TXBSR__CSR_TXB_SWCLR_KICK_MASK 0x80000000

/*****************************************************************************/

/** Reg BM_RXBSR
Buffer Monitor RX Setting Register
*/
#define MAC_CSR__BM_RXBSR CSR_ACCESS(MAC_CSR_BASE + 0x0000009C)

/** Field csr_rxb_bufsize
Total size of RX Buffer, to compute RX Overflow
*/
#define BM_RXBSR__CSR_RXB_BUFSIZE_POS 0
#define BM_RXBSR__CSR_RXB_BUFSIZE_MASK 0x000003FF

/** Field csr_rxb_swsize
SW RX buffer Size update
*/
#define BM_RXBSR__CSR_RXB_SWSIZE_POS 16
#define BM_RXBSR__CSR_RXB_SWSIZE_MASK 0x03FF0000

/** Field csr_rxb_swsize_kick
SW RX buffer Size update trigger signal
*/
#define BM_RXBSR__CSR_RXB_SWSIZE_KICK_POS 30
#define BM_RXBSR__CSR_RXB_SWSIZE_KICK_MASK 0x40000000

/** Field csr_rxb_swclr_kick
SW-MAC got all data from the buffer, clear the assertion.
*/
#define BM_RXBSR__CSR_RXB_SWCLR_KICK_POS 31
#define BM_RXBSR__CSR_RXB_SWCLR_KICK_MASK 0x80000000

/*****************************************************************************/

/** Reg PBE_SEL
Probe Select
*/
#define MAC_CSR__PBE_SEL CSR_ACCESS(MAC_CSR_BASE + 0x000000A0)

/** Field csr_probe_sel
select probe pin is from MAC(2), PHY(1) or PMU(0)
*/
#define PBE_SEL__CSR_PROBE_SEL_POS 0
#define PBE_SEL__CSR_PROBE_SEL_MASK 0x00000003

/** Field csr_mac_probe_sel
select mac probe pin sub group.
*/
#define PBE_SEL__CSR_MAC_PROBE_SEL_POS 8
#define PBE_SEL__CSR_MAC_PROBE_SEL_MASK 0x00003F00

/*****************************************************************************/

/** Reg PHY_CR1
PHY Control Register 1 (RET)
*/
#define MAC_CSR__PHY_CR1 CSR_ACCESS(MAC_CSR_BASE + 0x000000A4)

/** Field csr_phy_cr1
PHY Control Register
*/
#define PHY_CR1__CSR_PHY_CR1_POS 0
#define PHY_CR1__CSR_PHY_CR1_MASK 0xFFFFFFFF

/*****************************************************************************/

/** Reg MAC_PROBE
MAC Probe Signals
*/
#define MAC_CSR__MAC_PROBE CSR_ACCESS(MAC_CSR_BASE + 0x000000A8)

/** Field csr_mac_probe
MAC Probe Signals
*/
#define MAC_PROBE__CSR_MAC_PROBE_POS 0
#define MAC_PROBE__CSR_MAC_PROBE_MASK 0x0FFFFFFF

/*****************************************************************************/

/** Reg BM_IR
Buffer Monitor Information Register
*/
#define MAC_CSR__BM_IR CSR_ACCESS(MAC_CSR_BASE + 0x000000AC)

/** Field csr_rxb_bcnt
RX Buffer Byte Counter
*/
#define BM_IR__CSR_RXB_BCNT_POS 0
#define BM_IR__CSR_RXB_BCNT_MASK 0x000003FF

/** Field csr_txb_bcnt
TX Buffer Byte Counter
*/
#define BM_IR__CSR_TXB_BCNT_POS 16
#define BM_IR__CSR_TXB_BCNT_MASK 0x03FF0000

/*****************************************************************************/

/** Reg MAC_AHB_DR
MAC AHBIF Debug Register
*/
#define MAC_CSR__MAC_AHB_DR CSR_ACCESS(MAC_CSR_BASE + 0x000000B0)

/** Field csr_mst_cs
AHB Master FSM
*/
#define MAC_AHB_DR__CSR_MST_CS_POS 0
#define MAC_AHB_DR__CSR_MST_CS_MASK 0x00000007

/** Field csr_slv_cs
AHB Slave FSM
*/
#define MAC_AHB_DR__CSR_SLV_CS_POS 4
#define MAC_AHB_DR__CSR_SLV_CS_MASK 0x00000030

/** Field csr_arb_cs
AHB Arbiter FSM
*/
#define MAC_AHB_DR__CSR_ARB_CS_POS 8
#define MAC_AHB_DR__CSR_ARB_CS_MASK 0x00000700

/*****************************************************************************/

/** Reg MAC_TXE_DR
MAC TX Engine Debug Register
*/
#define MAC_CSR__MAC_TXE_DR CSR_ACCESS(MAC_CSR_BASE + 0x000000B4)

/** Field csr_txe_bcnt
TX Engine Byte Counter
*/
#define MAC_TXE_DR__CSR_TXE_BCNT_POS 0
#define MAC_TXE_DR__CSR_TXE_BCNT_MASK 0x000007FF

/** Field csr_txe_cs
TX Engine FSM
*/
#define MAC_TXE_DR__CSR_TXE_CS_POS 16
#define MAC_TXE_DR__CSR_TXE_CS_MASK 0x00070000

/*****************************************************************************/

/** Reg MAC_RXE_DR
MAC RX Engine Debug Register
*/
#define MAC_CSR__MAC_RXE_DR CSR_ACCESS(MAC_CSR_BASE + 0x000000B8)

/** Field csr_rxe_bcnt
RX Engine Byte Counter
*/
#define MAC_RXE_DR__CSR_RXE_BCNT_POS 0
#define MAC_RXE_DR__CSR_RXE_BCNT_MASK 0x000007FF

/** Field csr_rxe_cs
RX Engine FSM
*/
#define MAC_RXE_DR__CSR_RXE_CS_POS 16
#define MAC_RXE_DR__CSR_RXE_CS_MASK 0x00070000

/*****************************************************************************/

/** Reg MAC_TXP_DR
MAC TX Protocol Debug Register
*/
#define MAC_CSR__MAC_TXP_DR CSR_ACCESS(MAC_CSR_BASE + 0x000000C0)

/** Field csr_txp_bcnt
TX Protocol Byte Counter
*/
#define MAC_TXP_DR__CSR_TXP_BCNT_POS 0
#define MAC_TXP_DR__CSR_TXP_BCNT_MASK 0x000007FF

/** Field csr_txp_cs
TX Protocol FSM
*/
#define MAC_TXP_DR__CSR_TXP_CS_POS 16
#define MAC_TXP_DR__CSR_TXP_CS_MASK 0x00070000

/*****************************************************************************/

/** Reg MAC_RXP_DR
MAC RX Protocol Debug Register
*/
#define MAC_CSR__MAC_RXP_DR CSR_ACCESS(MAC_CSR_BASE + 0x000000C4)

/** Field csr_rxp_bcnt
RX Protocol Byte Counter
*/
#define MAC_RXP_DR__CSR_RXP_BCNT_POS 0
#define MAC_RXP_DR__CSR_RXP_BCNT_MASK 0x000007FF

/** Field csr_rxp_cs
RX Protocol FSM
*/
#define MAC_RXP_DR__CSR_RXP_CS_POS 16
#define MAC_RXP_DR__CSR_RXP_CS_MASK 0x00070000

/*****************************************************************************/

/** Reg MAC_RF_DR
MAC RX Filter Debug Register
*/
#define MAC_CSR__MAC_RF_DR CSR_ACCESS(MAC_CSR_BASE + 0x000000C8)

/** Field csr_rf_cs
RX Filter FSM
*/
#define MAC_RF_DR__CSR_RF_CS_POS 0
#define MAC_RF_DR__CSR_RF_CS_MASK 0x0000001F

/*****************************************************************************/

/** Reg MAC_TXCNT_DR
MAC TX Counter Debug Register (Read Clear)
*/
#define MAC_CSR__MAC_TXCNT_DR CSR_ACCESS(MAC_CSR_BASE + 0x000000D0)

/** Field d2s_txcnt
DMA2SPC TX Counter
*/
#define MAC_TXCNT_DR__D2S_TXCNT_POS 0
#define MAC_TXCNT_DR__D2S_TXCNT_MASK 0x000000FF

/** Field m2p_txcnt
MAC2PHY TX Counter
*/
#define MAC_TXCNT_DR__M2P_TXCNT_POS 8
#define MAC_TXCNT_DR__M2P_TXCNT_MASK 0x0000FF00

/*****************************************************************************/

/** Reg MAC_RXCNT_DR
MAC RX Counter Debug Register (Read Clear)
*/
#define MAC_CSR__MAC_RXCNT_DR CSR_ACCESS(MAC_CSR_BASE + 0x000000D4)

/** Field p2m_rxcnt
PHY2MAC RX Counter
*/
#define MAC_RXCNT_DR__P2M_RXCNT_POS 0
#define MAC_RXCNT_DR__P2M_RXCNT_MASK 0x000000FF

/** Field s2d_rxcnt
SPC2DMA RX Counter
*/
#define MAC_RXCNT_DR__S2D_RXCNT_POS 8
#define MAC_RXCNT_DR__S2D_RXCNT_MASK 0x0000FF00

/*****************************************************************************/

/** Reg MAC_MIB1
MAC MIB Counter 1 (Read Clear)
*/
#define MAC_CSR__MAC_MIB1 CSR_ACCESS(MAC_CSR_BASE + 0x000000D8)

/** Field mib_tx_ok
TX OK Counter
*/
#define MAC_MIB1__MIB_TX_OK_POS 0
#define MAC_MIB1__MIB_TX_OK_MASK 0x000000FF

/*****************************************************************************/

/** Reg MAC_MIB2
MAC MIB Counter 2 (Read Clear)
*/
#define MAC_CSR__MAC_MIB2 CSR_ACCESS(MAC_CSR_BASE + 0x000000DC)

/** Field mib_rx_ok
RX OK Counter
*/
#define MAC_MIB2__MIB_RX_OK_POS 0
#define MAC_MIB2__MIB_RX_OK_MASK 0x000000FF

/** Field mib_fcs_ok
FCS OK Counter
*/
#define MAC_MIB2__MIB_FCS_OK_POS 16
#define MAC_MIB2__MIB_FCS_OK_MASK 0x00FF0000

/** Field mib_fcs_fail
FCS Fail Counter
*/
#define MAC_MIB2__MIB_FCS_FAIL_POS 24
#define MAC_MIB2__MIB_FCS_FAIL_MASK 0xFF000000

/*****************************************************************************/

/** Reg GC_CR
Gated Clock Control Register (RET)
*/
#define MAC_CSR__GC_CR CSR_ACCESS(MAC_CSR_BASE + 0x000000E0)

/** Field csr_cg_dma_en
DMA Clock Gated Enable
*/
#define GC_CR__CSR_CG_DMA_EN_POS 0
#define GC_CR__CSR_CG_DMA_EN_MASK 0x00000001

/*****************************************************************************/

/** Reg ASIC_VER
Gated Clock Control Register (RET)
*/
#define MAC_CSR__ASIC_VER CSR_ACCESS(MAC_CSR_BASE + 0x000000FC)

/** Field csr_asic_ver
ASIC Version
*/
#define ASIC_VER__CSR_ASIC_VER_POS 0
#define ASIC_VER__CSR_ASIC_VER_MASK 0x00FFFFFF

#ifdef __cplusplus
}
#endif

#endif /* MAC_CSR_H */
