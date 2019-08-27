#ifndef PHY_CSR_H
#define PHY_CSR_H

#ifdef __cplusplus
extern "C" {
#endif

#ifndef CSR_ACCESS
#define CSR_ACCESS(x) (*((volatile unsigned long *)(x)))
#endif

/** Block phy_csr

*/
#define PHY_CSR_BASE 0x40024000

/*****************************************************************************/

/** Reg phy_top_ctrl
PHY TOP Control Register
*/
#define PHY_CSR__PHY_TOP_CTRL CSR_ACCESS(PHY_CSR_BASE + 0x00000000)

/** Field rg_frame_mode
Frame mode select:
0: IEEE802.15.4g MR-FSK framing
1: User defined (Transparent) framing
2: HAC (preamble with ID) mode
*/
#define PHY_TOP_CTRL__RG_FRAME_MODE_POS 0
#define PHY_TOP_CTRL__RG_FRAME_MODE_MASK 0x00000003

/** Field rg_4fsk_en
MR-FSK select:
0: 2FSK
1: 4FSK
*/
#define PHY_TOP_CTRL__RG_4FSK_EN_POS 4
#define PHY_TOP_CTRL__RG_4FSK_EN_MASK 0x00000010

/** Field rg_gfilter_en
Gaussian filter enable control:
Supported OSR=80, 128, 160, 320, 640, 800, 1280, 1600, 3200 
0: disable
1: enable, supported OSR is multiples of 16 (minimun=80)
*/
#define PHY_TOP_CTRL__RG_GFILTER_EN_POS 5
#define PHY_TOP_CTRL__RG_GFILTER_EN_MASK 0x00000020

/** Field rg_ook_en
OOK enable control:
0: disable
1: enable
*/
#define PHY_TOP_CTRL__RG_OOK_EN_POS 7
#define PHY_TOP_CTRL__RG_OOK_EN_MASK 0x00000080

/** Field rg_fec_en
FEC enable control:
0: disable
1: enable
*/
#define PHY_TOP_CTRL__RG_FEC_EN_POS 8
#define PHY_TOP_CTRL__RG_FEC_EN_MASK 0x00000100

/** Field rg_nrnsc_rsc_sel
Convolutional code select:
0: NRNSC
1: RSC
*/
#define PHY_TOP_CTRL__RG_NRNSC_RSC_SEL_POS 9
#define PHY_TOP_CTRL__RG_NRNSC_RSC_SEL_MASK 0x00000200

/** Field rg_interleave_en
Interleaver/De-interleaver control:
0: disable
1: enable, (Note) Interleaving is employed with FEC coding (rg_fec_en = 1)
*/
#define PHY_TOP_CTRL__RG_INTERLEAVE_EN_POS 10
#define PHY_TOP_CTRL__RG_INTERLEAVE_EN_MASK 0x00000400

/** Field rg_pn9_en
Data Whitening enable control: 0: disable 1: enable
*/
#define PHY_TOP_CTRL__RG_PN9_EN_POS 11
#define PHY_TOP_CTRL__RG_PN9_EN_MASK 0x00000800

/** Field rg_dm_en
Dynamic Message enable control:
0: DM code disable and WDC code enable
1: DM code enable and WDC code disable
*/
#define PHY_TOP_CTRL__RG_DM_EN_POS 12
#define PHY_TOP_CTRL__RG_DM_EN_MASK 0x00001000

/** Field rg_mc_en
Manchester code enable control:
0: disable
1: enable. Note: it should be set to zero when rg_frame_mode != 2.
*/
#define PHY_TOP_CTRL__RG_MC_EN_POS 13
#define PHY_TOP_CTRL__RG_MC_EN_MASK 0x00002000

/** Field rg_mc_inv_edge
Manchester code control:
0: 0 mapping 0-to-1
1: 0 mapping 1-to-0
*/
#define PHY_TOP_CTRL__RG_MC_INV_EDGE_POS 14
#define PHY_TOP_CTRL__RG_MC_INV_EDGE_MASK 0x00004000

/** Field rg_clk_trans_period
CLK transition period for GPIO CLK output
*/
#define PHY_TOP_CTRL__RG_CLK_TRANS_PERIOD_POS 20
#define PHY_TOP_CTRL__RG_CLK_TRANS_PERIOD_MASK 0x0FF00000

/*****************************************************************************/

/** Reg phy_tx_ctrl
PHY TX Control Register
*/
#define PHY_CSR__PHY_TX_CTRL CSR_ACCESS(PHY_CSR_BASE + 0x00000004)

/** Field rg_tx_en
TX enable control:
0: disable
1: enable
*/
#define PHY_TX_CTRL__RG_TX_EN_POS 0
#define PHY_TX_CTRL__RG_TX_EN_MASK 0x00000001

/** Field rg_b2s_rev_en
Bit-to-Symbol reverse mapping control for 4FSK:
0: Normal, (u1, u0)
1: Reversed, (u0, u1)

It is also used to control RX Manchester Decoder:
0: No-reverse Manchester output
1: Reverse Manchester output
*/
#define PHY_TX_CTRL__RG_B2S_REV_EN_POS 4
#define PHY_TX_CTRL__RG_B2S_REV_EN_MASK 0x00000010

/** Field rg_phr_ec_en
PHR TX Error Check Mechanism enable control:
0: disable 
1: enable, select BCH or CRC if rg_phr_ec_sel is 0 or 1
*/
#define PHY_TX_CTRL__RG_PHR_EC_EN_POS 5
#define PHY_TX_CTRL__RG_PHR_EC_EN_MASK 0x00000020

/** Field rg_phr_ec_sel
PHR Error Check Mechanism select:
(For PHY TX)
0: BCH code
1: CRC code  (rg_phr_len >=2)

(PHY RX will distinguish 1st bit of RX PHR)
PHR 1st bit = 0, and rg_phr_ec_sel=0 : normal Packet (without BCH or CRC)
PHR 1st bit = 0, and rg_phr_ec_sel=1 : normal Packet with CRC (rg_phr_len >=2)
PHR 1st bit = 1, and rg_phr_ec_sel=0 : Mode Switch Packet with BCH code
PHR 1st bit = 1, and rg_phr_ec_sel=1 : Mode Switch Packet with CRC code (rg_phr_len >=2)
*/
#define PHY_TX_CTRL__RG_PHR_EC_SEL_POS 6
#define PHY_TX_CTRL__RG_PHR_EC_SEL_MASK 0x00000040

/** Field rg_gmsk_bt_sel
PHY TX Gaussian filter BT:
0: BT=0.5
1: BT=1
*/
#define PHY_TX_CTRL__RG_GMSK_BT_SEL_POS 8
#define PHY_TX_CTRL__RG_GMSK_BT_SEL_MASK 0x00000100

/** Field rg_preemp_en
PHY TX Pre-emphasis control:
0: disable, 1: enable
*/
#define PHY_TX_CTRL__RG_PREEMP_EN_POS 12
#define PHY_TX_CTRL__RG_PREEMP_EN_MASK 0x00001000

/** Field rg_tx_framer_only_wuc
PHY TX Frame only WUC(WDC) data control in rg_frame_mode=0 :
0: Frame mode 0 (rg_frame_mode=0) Frame data, control by rg_tx_framer_dout_ctrl
1: send only WUC Frame in Frame mode 0, length control by rg_tx_wuc_length
*/
#define PHY_TX_CTRL__RG_TX_FRAMER_ONLY_WUC_POS 15
#define PHY_TX_CTRL__RG_TX_FRAMER_ONLY_WUC_MASK 0x00008000

/** Field rg_hac_wakeup_sel
PHY TX HAC Wake-Up code select:
0: Broadcast (use rg_hac_bc_poly RG)
1: Group (use rg_hac_gp_poly RG)
2: Individual (use rg_hac_id_poly RG)
*/
#define PHY_TX_CTRL__RG_HAC_WAKEUP_SEL_POS 16
#define PHY_TX_CTRL__RG_HAC_WAKEUP_SEL_MASK 0x00030000

/** Field rg_tx_ext_1sym
PHY TX extend 1 symbol data at frame end
0: disable
1: enable to extend 1 symbol at frame end

Note: If rg_gfilter_en=1, HW auto-enable extend 1 symbol data for the last gaussian
*/
#define PHY_TX_CTRL__RG_TX_EXT_1SYM_POS 18
#define PHY_TX_CTRL__RG_TX_EXT_1SYM_MASK 0x00040000

/** Field rg_tx_ext_1sym_data_keep
PHY TX extend 1 symbol data keep
0: extend data by rg_tx_ext_1sym_data (SW control)
1: extend the data which is the last data (HW keep)
*/
#define PHY_TX_CTRL__RG_TX_EXT_1SYM_DATA_KEEP_POS 19
#define PHY_TX_CTRL__RG_TX_EXT_1SYM_DATA_KEEP_MASK 0x00080000

/** Field rg_tx_ext_1sym_data
(1) PHY TX extend data value, format 2's complement
  - Sym  0 = 3'b000 = 0, return channel band
  - Sym -1 = 3'b111 = 7, minimum of 2FSK
  - Sym -3 = 3'b101 = 5, minimum of 4FSK
  - Sym  1 = 3'b001 = 1, maximum of 2FSK
  - Sym  3 = 3'b011 = 3, maximum of 4FSK

(2) Note : This RG also control RF PA Ramp Up and Down data for FSK or Gfilter.
*/
#define PHY_TX_CTRL__RG_TX_EXT_1SYM_DATA_POS 20
#define PHY_TX_CTRL__RG_TX_EXT_1SYM_DATA_MASK 0x00700000

/** Field rg_clk_en_framer
PHY TX clock enable control for Framer:
0: HW auto-gating TX Framer for low-power
1: always enable TX Framer clock
*/
#define PHY_TX_CTRL__RG_CLK_EN_FRAMER_POS 28
#define PHY_TX_CTRL__RG_CLK_EN_FRAMER_MASK 0x10000000

/*****************************************************************************/

/** Reg phy_rx_ctrl
PHY RX Control Register
*/
#define PHY_CSR__PHY_RX_CTRL CSR_ACCESS(PHY_CSR_BASE + 0x00000008)

/** Field rg_rx_en
RX enable control:
0: disable
1: enable, which is clear by HW until received packet done

Note: If (rg_frame_mode==0) case, you can write-1-clear rg_psdu_start_flag to force received packet end
*/
#define PHY_RX_CTRL__RG_RX_EN_POS 0
#define PHY_RX_CTRL__RG_RX_EN_MASK 0x00000001

/** Field rg_rx_fec_sw_mode
RX FEC software control mode:
0: Hardware will automatically detect SFD type to enable FEC Decoder.
1: FEC Decoder is controlled by software control bit "rg_fec_en".
*/
#define PHY_RX_CTRL__RG_RX_FEC_SW_MODE_POS 1
#define PHY_RX_CTRL__RG_RX_FEC_SW_MODE_MASK 0x00000002

/** Field rg_rx_all_en
RX all module enable. This bit is higher priority than "rg_rx_en" and will automatically enable all RX modules and also "rg_rx_en".
0: disable
1: enable
*/
#define PHY_RX_CTRL__RG_RX_ALL_EN_POS 2
#define PHY_RX_CTRL__RG_RX_ALL_EN_MASK 0x00000004

/** Field rg_rx_ms_phr_en
RX Mode Switch PHR control for IEEE 802.15.4g
0: disable
1: enable
*/
#define PHY_RX_CTRL__RG_RX_MS_PHR_EN_POS 4
#define PHY_RX_CTRL__RG_RX_MS_PHR_EN_MASK 0x00000010

/** Field rg_rx_psdu_add_len
RX extra add PSDU byte number
  - extra add to set 3 for CEC of CHINA (PHR 1st byte + FCS 2 bytes) if rg_rx_cec_frame_en=1
*/
#define PHY_RX_CTRL__RG_RX_PSDU_ADD_LEN_POS 8
#define PHY_RX_CTRL__RG_RX_PSDU_ADD_LEN_MASK 0x00000F00

/** Field rg_iq_swap_en
I/Q swap control
0: default
1: ADC I/Q channel connection to base-band is swapped.
*/
#define PHY_RX_CTRL__RG_IQ_SWAP_EN_POS 12
#define PHY_RX_CTRL__RG_IQ_SWAP_EN_MASK 0x00001000

/*****************************************************************************/

/** Reg RF_FREQ_BAND_RX_IF
RX IF Frequency
*/
#define PHY_CSR__RF_FREQ_BAND_RX_IF CSR_ACCESS(PHY_CSR_BASE + 0x0000000C)

/** Field rg_rx_if_freq
RX IF Frequency for rg_channel_band, format <0, 5,15>
 - rg_rx_if_freq[14:0] = "Wanted RX IF frequency" / F_xtal * (2^20)
 - e.g. rg_rx_if_freq[14:0] = 500K/32M * (2^20) = 0x4000
 - For F_xtal = 32MHz
   - IF=500K => rg_rx_if_freq[14:0]=0x4000
   - IF=375K => rg_rx_if_freq[14:0]=0x3000
   - IF=300K => rg_rx_if_freq[14:0]=0x2666
   - IF=250K => rg_rx_if_freq[14:0]=0x2000
   - IF=200K => rg_rx_if_freq[14:0]=0x199A

Note : For band3 or band4 RF freq, "Wanted RX IF frequency" must be double value.
*/
#define RF_FREQ_BAND_RX_IF__RG_RX_IF_FREQ_POS 0
#define RF_FREQ_BAND_RX_IF__RG_RX_IF_FREQ_MASK 0x00007FFF

/** Field rg_rx_if_ctrl
RX IF Frequency control
0: low side injection, F(synthesizer) = F(rg_channel_band) - F(rg_rx_if_freq)
1: high side injection, F(synthesizer) = F(rg_channel_band) + F(rg_rx_if_freq)
*/
#define RF_FREQ_BAND_RX_IF__RG_RX_IF_CTRL_POS 15
#define RF_FREQ_BAND_RX_IF__RG_RX_IF_CTRL_MASK 0x00008000

/*****************************************************************************/

/** Reg RF_FREQ_BAND
RF Frequency Band
*/
#define PHY_CSR__RF_FREQ_BAND CSR_ACCESS(PHY_CSR_BASE + 0x00000010)

/** Field rg_channel_band
RF Channel Band, format <0, 6, 20>
 - rg_channel_band[25:0] = round("Wanted RF channel frequency" / F_xtal * (2^20))
 - e.g. rg_channel_band[25:0] = round(868M / 32M * 2^20) = 0x1B2_0000

Note : For band3 or band4 RF freq, "Wanted RF channel frequency" must be double value.
*/
#define RF_FREQ_BAND__RG_CHANNEL_BAND_POS 0
#define RF_FREQ_BAND__RG_CHANNEL_BAND_MASK 0x03FFFFFF

/*****************************************************************************/

/** Reg PHY_PHR_CRC_COEF
PHY PHR BCH or CRC code coef
*/
#define PHY_CSR__PHY_PHR_CRC_COEF CSR_ACCESS(PHY_CSR_BASE + 0x00000014)

/** Field rg_phr_len
PHY PHR length selection:
00: Do NOT support !!!
01: 2 octets; Do NOT support PHR with CRC code (rg_phr_ec_sel=1)
10: 3 octets; odd byte PHR cannot set rg_interleave_en=1
11: 4 octets
*/
#define PHY_PHR_CRC_COEF__RG_PHR_LEN_POS 0
#define PHY_PHR_CRC_COEF__RG_PHR_LEN_MASK 0x00000003

/** Field rg_phy_phr_rev
PHR send order control
0: Big-Endian
1: Little-Endian, for China Electricity Council(CEC) standard
*/
#define PHY_PHR_CRC_COEF__RG_PHY_PHR_REV_POS 2
#define PHY_PHR_CRC_COEF__RG_PHY_PHR_REV_MASK 0x00000004

/** Field rg_phy_phr_in_psdu
PHY skip PHR filed
0: PHY Frame PPDU with PHR filed
1: PHY Frame PPDU will skip PHR field, for China Electricity Council(CEC) standard
    - PHY TX : PHR in PSDU from MAC TX
    - PHY RX : PHR send to MAC RX
*/
#define PHY_PHR_CRC_COEF__RG_PHY_PHR_IN_PSDU_POS 3
#define PHY_PHR_CRC_COEF__RG_PHY_PHR_IN_PSDU_MASK 0x00000008

/** Field rg_phr_bch_init
BCH RG initial values
*/
#define PHY_PHR_CRC_COEF__RG_PHR_BCH_INIT_POS 4
#define PHY_PHR_CRC_COEF__RG_PHR_BCH_INIT_MASK 0x000000F0

/** Field rg_phr_bch_poly
BCH polynomial
(only support for PHY TX)
*/
#define PHY_PHR_CRC_COEF__RG_PHR_BCH_POLY_POS 8
#define PHY_PHR_CRC_COEF__RG_PHR_BCH_POLY_MASK 0x00000F00

/** Field rg_phr_crc_init
PHR CRC-8 initial values
*/
#define PHY_PHR_CRC_COEF__RG_PHR_CRC_INIT_POS 12
#define PHY_PHR_CRC_COEF__RG_PHR_CRC_INIT_MASK 0x000FF000

/** Field rg_phr_crc_poly
PHR CRC-8 polynomial representations
(0x07 --> polynomial is X^8 + X^2 + X + 1)
*/
#define PHY_PHR_CRC_COEF__RG_PHR_CRC_POLY_POS 20
#define PHY_PHR_CRC_COEF__RG_PHR_CRC_POLY_MASK 0x0FF00000

/** Field rg_pn9_seq_sel
Data Whitening PN9 sequences output point
0: PN9 output point from X9 for IEEE 802.15.4g
1: PN9 output point from X0 fro CEC standard
*/
#define PHY_PHR_CRC_COEF__RG_PN9_SEQ_SEL_POS 28
#define PHY_PHR_CRC_COEF__RG_PN9_SEQ_SEL_MASK 0x10000000

/** Field rg_pn9_byp_phr_dis
Data whitening PN9 is applied to PHR field
0: PN9 from bypass PHR bits length (PSDU only) if rg_phy_phr_in_psdu=0
1: PN9 for all PHR+PSDU if rg_phy_phr_in_psdu=1. (for CEC standard)
*/
#define PHY_PHR_CRC_COEF__RG_PN9_BYP_PHR_DIS_POS 29
#define PHY_PHR_CRC_COEF__RG_PN9_BYP_PHR_DIS_MASK 0x20000000

/** Field rg_phy_psdu_rev
PSDU send order control
0: Big-Endian
1: Little-Endian
*/
#define PHY_PHR_CRC_COEF__RG_PHY_PSDU_REV_POS 30
#define PHY_PHR_CRC_COEF__RG_PHY_PSDU_REV_MASK 0x40000000

/** Field rg_rx_cec_frame_en
PHY RX Frame of CEC standard enable
0: disable, for IEEE 802.15.4g
1: enable, for CEC standard, set rg_rx_psdu_add_len=3
*/
#define PHY_PHR_CRC_COEF__RG_RX_CEC_FRAME_EN_POS 31
#define PHY_PHR_CRC_COEF__RG_RX_CEC_FRAME_EN_MASK 0x80000000

/*****************************************************************************/

/** Reg preamble_pattern
Preamble Pattern Register
*/
#define PHY_CSR__PREAMBLE_PATTERN CSR_ACCESS(PHY_CSR_BASE + 0x00000018)

/** Field rg_preamble_pat
Preamble Pattern:
-IEEE802.15.4g 2FSK : 32'h5555_5555 (8'b01010101)
-IEEE802.15.4g 4FSK : 32'h7777_7777 (16'b01110111_01110111)
-wMbus : 

(Note : set rg_tx_preamble_man_en = 1 for PHY TX manual mode)
*/
#define PREAMBLE_PATTERN__RG_PREAMBLE_PAT_POS 0
#define PREAMBLE_PATTERN__RG_PREAMBLE_PAT_MASK 0x000000FF

/*****************************************************************************/

/** Reg sfd_pattern
SFD Pattern Register
*/
#define PHY_CSR__SFD_PATTERN CSR_ACCESS(PHY_CSR_BASE + 0x0000001C)

/** Field rg_sfd_pat0
RX SFD Pattern0 for uncoded (PHR+PSDU) frame.:
Default = [-1     1     1    -1     1     1     1     1    -1     1    -1    -1     1     1     1    -1]
It should be set as "0110111101001110".

If rg_fec_en=0, PHY TX use the SFD pattern.

(IEEE 802.15.4g standard)
phyMRFSKSFD=0 : SFD-uncoded value = 16'h904E
phyMRFSKSFD=1 : SFD-uncoded value = 16'h7A0E
*/
#define SFD_PATTERN__RG_SFD_PAT0_POS 0
#define SFD_PATTERN__RG_SFD_PAT0_MASK 0x0000FFFF

/** Field rg_sfd_pat1
RX SFD Pattern1 for coded (PHR+PSDU) frame.:
Default = [-1     1     1    -1     1     1     1     1    -1     1    -1    -1     1     1     1    -1]
It should be set as "0110111101001110".

If rg_fec_en=1, PHY TX use the SFD pattern.

(IEEE 802.15.4g standard)
PhyMRFSKSFD=0 : SFD-coded value = 16'h6F4E
PhyMRFSKSFD=1 : SFD-coded value = 16'h632D
*/
#define SFD_PATTERN__RG_SFD_PAT1_POS 16
#define SFD_PATTERN__RG_SFD_PAT1_MASK 0xFFFF0000

/*****************************************************************************/

/** Reg hac_bc_poly
HAC Detection Broadcast type polynomial
*/
#define PHY_CSR__HAC_BC_POLY CSR_ACCESS(PHY_CSR_BASE + 0x00000020)

/** Field rg_hac_bc_poly
Broadcast type
 - default 0xE801 -> (reverse) 0x8017 : X^15 + X^4 + X^2 +X^1 + X^0
*/
#define HAC_BC_POLY__RG_HAC_BC_POLY_POS 0
#define HAC_BC_POLY__RG_HAC_BC_POLY_MASK 0xFFFFFFFF

/*****************************************************************************/

/** Reg hac_gp_poly
HAC Detection Group type polynomial
*/
#define PHY_CSR__HAC_GP_POLY CSR_ACCESS(PHY_CSR_BASE + 0x00000024)

/** Field rg_hac_gp_poly
Group type
*/
#define HAC_GP_POLY__RG_HAC_GP_POLY_POS 0
#define HAC_GP_POLY__RG_HAC_GP_POLY_MASK 0xFFFFFFFF

/*****************************************************************************/

/** Reg hac_id_poly
HAC Detection Individual polynomial
*/
#define PHY_CSR__HAC_ID_POLY CSR_ACCESS(PHY_CSR_BASE + 0x00000028)

/** Field rg_hac_id_poly
Individual type
*/
#define HAC_ID_POLY__RG_HAC_ID_POLY_POS 0
#define HAC_ID_POLY__RG_HAC_ID_POLY_MASK 0xFFFFFFFF

/*****************************************************************************/

/** Reg hac_init_pat
HAC Detection Init Pattern
*/
#define PHY_CSR__HAC_INIT_PAT CSR_ACCESS(PHY_CSR_BASE + 0x0000002C)

/** Field rg_hac_init_pat
Init pattern
*/
#define HAC_INIT_PAT__RG_HAC_INIT_PAT_POS 0
#define HAC_INIT_PAT__RG_HAC_INIT_PAT_MASK 0x7FFFFFFF

/*****************************************************************************/

/** Reg PHYTX_CFG0
IEEE802.15.4g MR-FSK Framing control0
*/
#define PHY_CSR__PHYTX_CFG0 CSR_ACCESS(PHY_CSR_BASE + 0x00000030)

/** Field rg_tx_framer_en
Set 1 to transmit packet.
In rg_frame_mode=0, HW will be auto clear to 0 if TX frame send finish. You can set rg_framer_continuous=1 to disable auto-clear function to send a consecutive test pattern.
*/
#define PHYTX_CFG0__RG_TX_FRAMER_EN_POS 0
#define PHYTX_CFG0__RG_TX_FRAMER_EN_MASK 0x00000001

/** Field rg_tx_preamble_frabit
Preamble fractional bit number length
  - Preamble bit length = {rg_tx_preamble_len[10:0], rg_tx_preamble_frabit[2:0]}
  - By default, set 0 for integer Preamble bytes
*/
#define PHYTX_CFG0__RG_TX_PREAMBLE_FRABIT_POS 1
#define PHYTX_CFG0__RG_TX_PREAMBLE_FRABIT_MASK 0x0000000E

/** Field rg_tx_preamble_len
Preamble Length of octet
MIN Preamble length is ONE octet when rg_tx_preamble_len=1
MAX Preamble length is 2048 octets when rg_tx_preamble_len=0
*/
#define PHYTX_CFG0__RG_TX_PREAMBLE_LEN_POS 4
#define PHYTX_CFG0__RG_TX_PREAMBLE_LEN_MASK 0x00007FF0

/** Field rg_tx_preamble_man_en
0: HW default Preamble octet value
    (IEEE802.15.4g 2FSK=8'b01010101, 4FSK=8'b01110111)
1: manual Preamble  Enable, cyclically send Preamble by rg_preamble_pat RG (MSB first)
*/
#define PHYTX_CFG0__RG_TX_PREAMBLE_MAN_EN_POS 15
#define PHYTX_CFG0__RG_TX_PREAMBLE_MAN_EN_MASK 0x00008000

/** Field rg_tx_chan_gain
TX channel gain, unsigned format <0,  -6, 20>
  - TX Chan_gain = delta_f / 32M = (Symbol-Rate x h ) / 2 / 32M x (2^20)
     = (PHY_CLK/OSR x h ) / 2 / 32 x (2^20) = (PHY_CLK/OSR x h ) x (2^14)
  - e.g. Rs=50K, 2FSK, h=1.0 : (50K x 1.0) / 2 / 32M x (2^20) = 819 = 0x0333
*/
#define PHYTX_CFG0__RG_TX_CHAN_GAIN_POS 16
#define PHYTX_CFG0__RG_TX_CHAN_GAIN_MASK 0x3FFF0000

/** Field rg_tx_framer_dout_ctrl
PHY TX Framer output data control
0: normal packet (Preamble->SFD->PHR->PSDU)
1: send data from SFD (SFD->PHR->PSDU)
2: send data from PHR (PHR->PSDU); HW auto-set 2 when rg_phy_lpbk_en=1
3: send data just PSDU
*/
#define PHYTX_CFG0__RG_TX_FRAMER_DOUT_CTRL_POS 30
#define PHYTX_CFG0__RG_TX_FRAMER_DOUT_CTRL_MASK 0xC0000000

/*****************************************************************************/

/** Reg PHYTX_CFG1
IEEE802.15.4g MR-FSK Framing control1
*/
#define PHY_CSR__PHYTX_CFG1 CSR_ACCESS(PHY_CSR_BASE + 0x00000034)

/** Field rg_tx_psdu_len
PSDU byte length
IF rg_tx_psdu_len set ZERO, the TX packet is no PSDU (i.e. Ended after PHR)
*/
#define PHYTX_CFG1__RG_TX_PSDU_LEN_POS 0
#define PHYTX_CFG1__RG_TX_PSDU_LEN_MASK 0x00000FFF

/** Field rg_tick_period
Clock cycle period for setting Bit-Rate 
 - rg_tick_period = F_xtal / symbol-rate / (1+rg_4fsk_en)
 - mininum is 80 for Symbol-Rate 400Kbps
 - Default is 640 ( =32M/50K/(1+0) ) for 2(G)FSK 50Kbps
*/
#define PHYTX_CFG1__RG_TICK_PERIOD_POS 12
#define PHYTX_CFG1__RG_TICK_PERIOD_MASK 0x07FFF000

/*****************************************************************************/

/** Reg PHYTX_CFG2

*/
#define PHY_CSR__PHYTX_CFG2 CSR_ACCESS(PHY_CSR_BASE + 0x00000038)

/** Field rg_tx_tailpad_val
rg_tx_tailpad_val[15:13] is Tail bits if rg_tx_tail_by_sw set 1
rg_tx_tailpad_val[12:0] is Padding bits
*/
#define PHYTX_CFG2__RG_TX_TAILPAD_VAL_POS 0
#define PHYTX_CFG2__RG_TX_TAILPAD_VAL_MASK 0x0000FFFF

/** Field rg_tx_tail_by_sw
0: FEC Tail bits by HW mode
1: FEC Tail bits by SW RG mode (rg_tx_tailpad_val[15:13])
*/
#define PHYTX_CFG2__RG_TX_TAIL_BY_SW_POS 16
#define PHYTX_CFG2__RG_TX_TAIL_BY_SW_MASK 0x00010000

/*****************************************************************************/

/** Reg PHYTX_CFG3
IEEE802.15.4g MR-FSK Framing PHR value
*/
#define PHY_CSR__PHYTX_CFG3 CSR_ACCESS(PHY_CSR_BASE + 0x0000003C)

/** Field rg_tx_phr_val
PHY TX PHY values
*/
#define PHYTX_CFG3__RG_TX_PHR_VAL_POS 0
#define PHYTX_CFG3__RG_TX_PHR_VAL_MASK 0xFFFFFFFF

/*****************************************************************************/

/** Reg PHYTX_CFG6
PHY TX Power Shaping control
*/
#define PHY_CSR__PHYTX_CFG6 CSR_ACCESS(PHY_CSR_BASE + 0x00000048)

/** Field rg_tx_pwr_rampsetp
Rampstep per XTAL cycle, unsigned format (0, 0, 8)

(1) PA code ramp time per step = PA_ts
      = (256 / rg_tx_pwr_rampsetp) x PHY_CLK_cycle
    (PHY_CLK_cycle = 31.25 (ns) for 32MHz, 41.67 (ns) for 24MHz)
  So, PA_ts for PHY_CLK=32M :
 - set 0x01 : PA_ts = 8 (us)
 - set 0x02 : PA_ts = 4 (us)
 - set 0x04 : PA_ts = 2 (us)
 - set 0x08 : PA_ts = 1 (us)
 - set 0x10 : PA_ts = 500 (ns)
 - set 0x20 : PA_ts = 250 (ns)
 - set 0x40 : PA_ts = 125 (ns)

(2) Total PA code ramp time = PA_ts x (rg_tx_pwr_init - rg_tx_pwr_thr)
     So, default is 0.25(us) x 44 = 11 (us)
*/
#define PHYTX_CFG6__RG_TX_PWR_RAMPSETP_POS 0
#define PHYTX_CFG6__RG_TX_PWR_RAMPSETP_MASK 0x000000FF

/** Field rg_tx_pwr_init
Starting index of RG Code (rg_tx_pwr_xx_code) of Lowest bound Power level
*/
#define PHYTX_CFG6__RG_TX_PWR_INIT_POS 8
#define PHYTX_CFG6__RG_TX_PWR_INIT_MASK 0x00003F00

/** Field rg_tx_pwr_thr
Ended index of RG Code (rg_tx_pwr_xx_code) of Upper bound Power level
*/
#define PHYTX_CFG6__RG_TX_PWR_THR_POS 14
#define PHYTX_CFG6__RG_TX_PWR_THR_MASK 0x000FC000

/*****************************************************************************/

/** Reg PHY_TEST
PHY Test RG
*/
#define PHY_CSR__PHY_TEST CSR_ACCESS(PHY_CSR_BASE + 0x0000004C)

/** Field rg_phy_test_mode
PHY test mode control
0: normal packet, send PHY TX data from MAC
1: send PHY TX data from rg_hac_id_poly RG, not MAC. And PHY RX receive data to compare with rg_hac_id_poly RG, the error bit count log in rg_phy_test_err_cnt[7:0]
*/
#define PHY_TEST__RG_PHY_TEST_MODE_POS 0
#define PHY_TEST__RG_PHY_TEST_MODE_MASK 0x00000001

/** Field rg_phy_lpbk_en
PHY digital loopback control
0: disable
1: enable loopback from PHY TX Bit2Sym output to RX Sym2Bit input, and RX  Viterbi will force into Hard-Decision path.
*/
#define PHY_TEST__RG_PHY_LPBK_EN_POS 4
#define PHY_TEST__RG_PHY_LPBK_EN_MASK 0x00000010

/** Field rg_tx_insert_err_fec
PHY TX Frame inserts a error at 7th output bit of 32-bit interleaving block
0: disable
1: enable
(note: Do NOT use for 4FSK mode, because 4FSK is 2-bit as a symbol.)
*/
#define PHY_TEST__RG_TX_INSERT_ERR_FEC_POS 8
#define PHY_TEST__RG_TX_INSERT_ERR_FEC_MASK 0x00000100

/** Field rg_tx_insert_err_phr
PHY TX Frame inserts a error at 7th PHR bit (ro_tx_phr_encode[25]) for BCH test
0: disable
1: enable
*/
#define PHY_TEST__RG_TX_INSERT_ERR_PHR_POS 12
#define PHY_TEST__RG_TX_INSERT_ERR_PHR_MASK 0x00001000

/** Field rg_framer_continuous
PHY Frame with continuous mode for "rg_frame_mode=0"
(1) to PHY TX Framer : 
  - 0: default by HW (auto clear rg_tx_framer_en if packet send done)
  - 1: control by SW to set rg_tx_framer_en to start and stop Frame packet. And suggest to enable rg_clk_en_framer=1
(2) to PHY RX Framer :
  - 0: default by HW (auto clear rg_rx_en if packet receieve done)
  - 1: control by SW to W1C rg_psdu_start_flag to stop Frame packet.
*/
#define PHY_TEST__RG_FRAMER_CONTINUOUS_POS 16
#define PHY_TEST__RG_FRAMER_CONTINUOUS_MASK 0x00010000

/** Field rg_tx_trans2RF_en
PHY TX transparent to RF mode
0: disable
1: enable TX transparent to RF mode
  - The Pre-emphasis din is from PSDU data, format <s,2,12>
  - if set rg_phy_psdu_rev=0, fill mac_data = 0x0070 mean -1;  mac_data = 0x0010 mean +1
  - need to set rg_frame_mode=0 
  - need to set rg_tx_framer_dout_ctrl=3 to fill whole packet data from MAC
  - need to set rg_tx_tailpad_val=0 for the last tail data
  - the minimum of rg_tick_period is 0xA (It's about the TX symbol rate)
*/
#define PHY_TEST__RG_TX_TRANS2RF_EN_POS 20
#define PHY_TEST__RG_TX_TRANS2RF_EN_MASK 0x00100000

/** Field rg_icg_on_s2b
clock gating control for PHY RX S2B
0: control by HW for saving-power
1: always ON
*/
#define PHY_TEST__RG_ICG_ON_S2B_POS 28
#define PHY_TEST__RG_ICG_ON_S2B_MASK 0x10000000

/** Field rg_icg_on_vtdec
clock gating control for PHY RX Viterbi
0: control by HW for saving-power
1: always ON
*/
#define PHY_TEST__RG_ICG_ON_VTDEC_POS 29
#define PHY_TEST__RG_ICG_ON_VTDEC_MASK 0x20000000

/*****************************************************************************/

/** Reg PHY_TEST_LOG
PHY test result RG
*/
#define PHY_CSR__PHY_TEST_LOG CSR_ACCESS(PHY_CSR_BASE + 0x00000050)

/** Field rg_phy_test_err_cnt
bit error counter of PHY RX De-Framer output data (compare with rg_hac_id_poly) if rg_phy_test_mode=1
*/
#define PHY_TEST_LOG__RG_PHY_TEST_ERR_CNT_POS 0
#define PHY_TEST_LOG__RG_PHY_TEST_ERR_CNT_MASK 0x000000FF

/*****************************************************************************/

/** Reg PHY_Probe
PHY Probe data
*/
#define PHY_CSR__PHY_PROBE CSR_ACCESS(PHY_CSR_BASE + 0x00000054)

/** Field phy_probe_pin
PHY Probe pin data to RG which is selected by csr_phy_cr1[29:24] of MAC CSR
The detail probe mux in the reference path :
 - X:\Project\Centauri\Design specifications\BBP\Centauri_MP_A1_PHY_Probe.xlsx
*/
#define PHY_PROBE__PHY_PROBE_PIN_POS 8
#define PHY_PROBE__PHY_PROBE_PIN_MASK 0xFFFFFF00

/*****************************************************************************/

/** Reg PHYTX_PHR_ENC
PHY TX PHR after Error Check code
*/
#define PHY_CSR__PHYTX_PHR_ENC CSR_ACCESS(PHY_CSR_BASE + 0x0000005C)

/** Field ro_tx_phr_encode
PHY TX PHR data after BCH or CRC encode before FEC encode,
(If rg_phr_ec_en=0, the value is rg_tx_phr_val)
*/
#define PHYTX_PHR_ENC__RO_TX_PHR_ENCODE_POS 0
#define PHYTX_PHR_ENC__RO_TX_PHR_ENCODE_MASK 0xFFFFFFFF

/*****************************************************************************/

/** Reg PHYTX_FRAME_WUC
PHY TX PHR Frame with prefix WakeUp Code filed 
*/
#define PHY_CSR__PHYTX_FRAME_WUC CSR_ACCESS(PHY_CSR_BASE + 0x00000060)

/** Field rg_tx_wuc_length
PHY TX WakeUp code length (number of bytes)
 - default 0x20000 for the degree of 17)
*/
#define PHYTX_FRAME_WUC__RG_TX_WUC_LENGTH_POS 0
#define PHYTX_FRAME_WUC__RG_TX_WUC_LENGTH_MASK 0x3FFFFFFF

/** Field rg_tx_wuc_en
PHY TX Frame with Prefix WakeUp Code filed
0: disable
1: enable, for downstream of China Electricity Council(CEC) standard
*/
#define PHYTX_FRAME_WUC__RG_TX_WUC_EN_POS 31
#define PHYTX_FRAME_WUC__RG_TX_WUC_EN_MASK 0x80000000

/*****************************************************************************/

/** Reg PHYTX_PREEMP_COEF1
PHY TX Pre-emphasis coef 1
*/
#define PHY_CSR__PHYTX_PREEMP_COEF1 CSR_ACCESS(PHY_CSR_BASE + 0x00000064)

/** Field rg_preemp_coef_b0
Pre-emphasis coef, format <1,5,6>
*/
#define PHYTX_PREEMP_COEF1__RG_PREEMP_COEF_B0_POS 0
#define PHYTX_PREEMP_COEF1__RG_PREEMP_COEF_B0_MASK 0x00000FFF

/** Field rg_preemp_coef_b1
Pre-emphasis coef, format <1,5,6>
*/
#define PHYTX_PREEMP_COEF1__RG_PREEMP_COEF_B1_POS 12
#define PHYTX_PREEMP_COEF1__RG_PREEMP_COEF_B1_MASK 0x00FFF000

/** Field rg_preemp_coef_b2l
Pre-emphasis coef b2 low 8-bit
*/
#define PHYTX_PREEMP_COEF1__RG_PREEMP_COEF_B2L_POS 24
#define PHYTX_PREEMP_COEF1__RG_PREEMP_COEF_B2L_MASK 0xFF000000

/*****************************************************************************/

/** Reg PHYTX_PREEMP_COEF2
PHY TX Pre-emphasis coef 2
*/
#define PHY_CSR__PHYTX_PREEMP_COEF2 CSR_ACCESS(PHY_CSR_BASE + 0x00000068)

/** Field rg_preemp_coef_b2h
Pre-emphasis coef b2 high 4-bit
*/
#define PHYTX_PREEMP_COEF2__RG_PREEMP_COEF_B2H_POS 0
#define PHYTX_PREEMP_COEF2__RG_PREEMP_COEF_B2H_MASK 0x0000000F

/** Field rg_preemp_coef_b3
Pre-emphasis coef, format <1,5,6>
*/
#define PHYTX_PREEMP_COEF2__RG_PREEMP_COEF_B3_POS 4
#define PHYTX_PREEMP_COEF2__RG_PREEMP_COEF_B3_MASK 0x0000FFF0

/** Field rg_preemp_coef_a1
Pre-emphasis coef, format <1,5,6>
*/
#define PHYTX_PREEMP_COEF2__RG_PREEMP_COEF_A1_POS 16
#define PHYTX_PREEMP_COEF2__RG_PREEMP_COEF_A1_MASK 0x0FFF0000

/*****************************************************************************/

/** Reg PHYTX_PWR_SHAPE6
PHY TX Power Shape Code 
*/
#define PHY_CSR__PHYTX_PWR_SHAPE6 CSR_ACCESS(PHY_CSR_BASE + 0x0000007C)

/** Field rg_tx_pwr_30_code
HW internal value to reduce HW : 
rg_tx_pwr_0~9_code = 0
rg_tx_pwr_10_code = 1 
rg_tx_pwr_11_code = 1
rg_tx_pwr_12_code = 1
rg_tx_pwr_13_code = 1
rg_tx_pwr_14_code = 1
rg_tx_pwr_15_code = 1
rg_tx_pwr_16_code = 2
rg_tx_pwr_17_code = 2
rg_tx_pwr_18_code = 2
rg_tx_pwr_19_code = 2
rg_tx_pwr_20_code = 2
rg_tx_pwr_21_code = 2
rg_tx_pwr_22_code = 3
rg_tx_pwr_23_code = 3
rg_tx_pwr_24_code = 3
rg_tx_pwr_25_code = 3
rg_tx_pwr_26_code = 3
rg_tx_pwr_27_code = 3
rg_tx_pwr_28_code = 4
rg_tx_pwr_29_code = 4
......
rg_tx_pwr_54~63_code = 53 (default)
*/
#define PHYTX_PWR_SHAPE6__RG_TX_PWR_30_CODE_POS 0
#define PHYTX_PWR_SHAPE6__RG_TX_PWR_30_CODE_MASK 0x0000003F

/** Field rg_tx_pwr_31_code

*/
#define PHYTX_PWR_SHAPE6__RG_TX_PWR_31_CODE_POS 6
#define PHYTX_PWR_SHAPE6__RG_TX_PWR_31_CODE_MASK 0x00000FC0

/** Field rg_tx_pwr_32_code

*/
#define PHYTX_PWR_SHAPE6__RG_TX_PWR_32_CODE_POS 12
#define PHYTX_PWR_SHAPE6__RG_TX_PWR_32_CODE_MASK 0x0003F000

/** Field rg_tx_pwr_33_code

*/
#define PHYTX_PWR_SHAPE6__RG_TX_PWR_33_CODE_POS 18
#define PHYTX_PWR_SHAPE6__RG_TX_PWR_33_CODE_MASK 0x00FC0000

/** Field rg_tx_pwr_34_code

*/
#define PHYTX_PWR_SHAPE6__RG_TX_PWR_34_CODE_POS 24
#define PHYTX_PWR_SHAPE6__RG_TX_PWR_34_CODE_MASK 0x3F000000

/*****************************************************************************/

/** Reg PHYTX_PWR_SHAPE7
PHY TX Power Shape Code 
*/
#define PHY_CSR__PHYTX_PWR_SHAPE7 CSR_ACCESS(PHY_CSR_BASE + 0x00000080)

/** Field rg_tx_pwr_35_code

*/
#define PHYTX_PWR_SHAPE7__RG_TX_PWR_35_CODE_POS 0
#define PHYTX_PWR_SHAPE7__RG_TX_PWR_35_CODE_MASK 0x0000003F

/** Field rg_tx_pwr_36_code

*/
#define PHYTX_PWR_SHAPE7__RG_TX_PWR_36_CODE_POS 6
#define PHYTX_PWR_SHAPE7__RG_TX_PWR_36_CODE_MASK 0x00000FC0

/** Field rg_tx_pwr_37_code

*/
#define PHYTX_PWR_SHAPE7__RG_TX_PWR_37_CODE_POS 12
#define PHYTX_PWR_SHAPE7__RG_TX_PWR_37_CODE_MASK 0x0003F000

/** Field rg_tx_pwr_38_code

*/
#define PHYTX_PWR_SHAPE7__RG_TX_PWR_38_CODE_POS 18
#define PHYTX_PWR_SHAPE7__RG_TX_PWR_38_CODE_MASK 0x00FC0000

/** Field rg_tx_pwr_39_code

*/
#define PHYTX_PWR_SHAPE7__RG_TX_PWR_39_CODE_POS 24
#define PHYTX_PWR_SHAPE7__RG_TX_PWR_39_CODE_MASK 0x3F000000

/*****************************************************************************/

/** Reg PHYTX_PWR_SHAPE8
PHY TX Power Shape Code 
*/
#define PHY_CSR__PHYTX_PWR_SHAPE8 CSR_ACCESS(PHY_CSR_BASE + 0x00000084)

/** Field rg_tx_pwr_40_code

*/
#define PHYTX_PWR_SHAPE8__RG_TX_PWR_40_CODE_POS 0
#define PHYTX_PWR_SHAPE8__RG_TX_PWR_40_CODE_MASK 0x0000003F

/** Field rg_tx_pwr_41_code

*/
#define PHYTX_PWR_SHAPE8__RG_TX_PWR_41_CODE_POS 6
#define PHYTX_PWR_SHAPE8__RG_TX_PWR_41_CODE_MASK 0x00000FC0

/** Field rg_tx_pwr_42_code

*/
#define PHYTX_PWR_SHAPE8__RG_TX_PWR_42_CODE_POS 12
#define PHYTX_PWR_SHAPE8__RG_TX_PWR_42_CODE_MASK 0x0003F000

/** Field rg_tx_pwr_43_code

*/
#define PHYTX_PWR_SHAPE8__RG_TX_PWR_43_CODE_POS 18
#define PHYTX_PWR_SHAPE8__RG_TX_PWR_43_CODE_MASK 0x00FC0000

/** Field rg_tx_pwr_44_code

*/
#define PHYTX_PWR_SHAPE8__RG_TX_PWR_44_CODE_POS 24
#define PHYTX_PWR_SHAPE8__RG_TX_PWR_44_CODE_MASK 0x3F000000

/*****************************************************************************/

/** Reg PHYTX_PWR_SHAPE9
PHY TX Power Shape Code 
*/
#define PHY_CSR__PHYTX_PWR_SHAPE9 CSR_ACCESS(PHY_CSR_BASE + 0x00000088)

/** Field rg_tx_pwr_45_code

*/
#define PHYTX_PWR_SHAPE9__RG_TX_PWR_45_CODE_POS 0
#define PHYTX_PWR_SHAPE9__RG_TX_PWR_45_CODE_MASK 0x0000003F

/** Field rg_tx_pwr_46_code

*/
#define PHYTX_PWR_SHAPE9__RG_TX_PWR_46_CODE_POS 6
#define PHYTX_PWR_SHAPE9__RG_TX_PWR_46_CODE_MASK 0x00000FC0

/** Field rg_tx_pwr_47_code

*/
#define PHYTX_PWR_SHAPE9__RG_TX_PWR_47_CODE_POS 12
#define PHYTX_PWR_SHAPE9__RG_TX_PWR_47_CODE_MASK 0x0003F000

/** Field rg_tx_pwr_48_code

*/
#define PHYTX_PWR_SHAPE9__RG_TX_PWR_48_CODE_POS 18
#define PHYTX_PWR_SHAPE9__RG_TX_PWR_48_CODE_MASK 0x00FC0000

/** Field rg_tx_pwr_49_code

*/
#define PHYTX_PWR_SHAPE9__RG_TX_PWR_49_CODE_POS 24
#define PHYTX_PWR_SHAPE9__RG_TX_PWR_49_CODE_MASK 0x3F000000

/*****************************************************************************/

/** Reg PHYTX_PWR_SHAPEA
PHY TX Power Shape Code 
*/
#define PHY_CSR__PHYTX_PWR_SHAPEA CSR_ACCESS(PHY_CSR_BASE + 0x0000008C)

/** Field rg_tx_pwr_50_code

*/
#define PHYTX_PWR_SHAPEA__RG_TX_PWR_50_CODE_POS 0
#define PHYTX_PWR_SHAPEA__RG_TX_PWR_50_CODE_MASK 0x0000003F

/** Field rg_tx_pwr_51_code

*/
#define PHYTX_PWR_SHAPEA__RG_TX_PWR_51_CODE_POS 6
#define PHYTX_PWR_SHAPEA__RG_TX_PWR_51_CODE_MASK 0x00000FC0

/** Field rg_tx_pwr_52_code

*/
#define PHYTX_PWR_SHAPEA__RG_TX_PWR_52_CODE_POS 12
#define PHYTX_PWR_SHAPEA__RG_TX_PWR_52_CODE_MASK 0x0003F000

/** Field rg_tx_pwr_53_code

*/
#define PHYTX_PWR_SHAPEA__RG_TX_PWR_53_CODE_POS 18
#define PHYTX_PWR_SHAPEA__RG_TX_PWR_53_CODE_MASK 0x00FC0000

/*****************************************************************************/

/** Reg rx_filt_ctrl
RX Filter Control
*/
#define PHY_CSR__RX_FILT_CTRL CSR_ACCESS(PHY_CSR_BASE + 0x00000090)

/** Field rg_rx_predecim_factor
RX Pre-decimation filter decimation factor
0: down-sampling by 7
1: down-sampling by 8
2: down-sampling by 10
3: down-sampling by 5
*/
#define RX_FILT_CTRL__RG_RX_PREDECIM_FACTOR_POS 0
#define RX_FILT_CTRL__RG_RX_PREDECIM_FACTOR_MASK 0x00000003

/** Field rg_rx_predecim_shift
RX Pre-decimation filter output scaling 
0: scaling = x1 (default)
1: scaling = x2
*/
#define RX_FILT_CTRL__RG_RX_PREDECIM_SHIFT_POS 3
#define RX_FILT_CTRL__RG_RX_PREDECIM_SHIFT_MASK 0x00000008

/** Field rg_rx_cic1_df
RX CIC1 filter decimation factor
0: bypass
1: down-sampling by 2
2: down-sampling by 5
3: down-sampling by 7
4: down-sampling by 8

5: down-sampling by 3, suggest set rg_rx_cic1_out_shift=2 (x4)
6: down-sampling by 4, suggest set rg_rx_cic1_out_shift=1 (x2)
7: down-sampling by 6, suggest set rg_rx_cic1_out_shift=1 (x2)
*/
#define RX_FILT_CTRL__RG_RX_CIC1_DF_POS 4
#define RX_FILT_CTRL__RG_RX_CIC1_DF_MASK 0x00000070

/** Field rg_rx_cic2_df
RX CIC2 filter decimation factor
0: bypass
1: down-sampling by 2
2: down-sampling by 4
3: down-sampling by 5
*/
#define RX_FILT_CTRL__RG_RX_CIC2_DF_POS 8
#define RX_FILT_CTRL__RG_RX_CIC2_DF_MASK 0x00000300

/** Field rg_rx_d2_filt_bypass
Bypass control of RX D2 Filter
0: normal mode, down-sampling by 2 (default)
1: bypass and no down-sampling
*/
#define RX_FILT_CTRL__RG_RX_D2_FILT_BYPASS_POS 10
#define RX_FILT_CTRL__RG_RX_D2_FILT_BYPASS_MASK 0x00000400

/** Field rg_rx_d2_out_shift
RX D2 filter output scaling if enable D2 filter (rg_rx_d2_filt_bypass=0)
0: scaling = x1 (default)
1: scaling = x2
*/
#define RX_FILT_CTRL__RG_RX_D2_OUT_SHIFT_POS 11
#define RX_FILT_CTRL__RG_RX_D2_OUT_SHIFT_MASK 0x00000800

/** Field rg_rx_cic1_out_shift
RX CIC1 filter output scaling
0: scaling = x1 (default)
1: scaling = x2
2: scaling = x4
Others: reserved and is invalid
*/
#define RX_FILT_CTRL__RG_RX_CIC1_OUT_SHIFT_POS 12
#define RX_FILT_CTRL__RG_RX_CIC1_OUT_SHIFT_MASK 0x00003000

/** Field rg_rx_cic2_out_shift
RX CIC2 filter output scaling
0: scaling = x1 (default)
1: scaling = x2
2: scaling = x4
Others: reserved and is invalid
*/
#define RX_FILT_CTRL__RG_RX_CIC2_OUT_SHIFT_POS 14
#define RX_FILT_CTRL__RG_RX_CIC2_OUT_SHIFT_MASK 0x0000C000

/** Field rg_rx_comp_fir_out_2x_en
RX compensation filter output scaling
0: scaling = x1 (default)
1: scaling = x2
*/
#define RX_FILT_CTRL__RG_RX_COMP_FIR_OUT_2X_EN_POS 16
#define RX_FILT_CTRL__RG_RX_COMP_FIR_OUT_2X_EN_MASK 0x00010000

/** Field rg_rx_decim_fir_out_2x_en
RX decimation filter output scaling
0: scaling = x1 (default)
1: scaling = x2
*/
#define RX_FILT_CTRL__RG_RX_DECIM_FIR_OUT_2X_EN_POS 17
#define RX_FILT_CTRL__RG_RX_DECIM_FIR_OUT_2X_EN_MASK 0x00020000

/** Field rg_rx_decim_fir_bypass
Bypass control of RX RX decimation filter 
0: normal mode
1: bypass and no down-sampling
*/
#define RX_FILT_CTRL__RG_RX_DECIM_FIR_BYPASS_POS 18
#define RX_FILT_CTRL__RG_RX_DECIM_FIR_BYPASS_MASK 0x00040000

/** Field rg_rx_decim_fir_x1_en
RX decimation down-sample 1x filter
0: disable
1: coef for down-sample by 1, config by rg_rx_decim_fir_xxx
*/
#define RX_FILT_CTRL__RG_RX_DECIM_FIR_X1_EN_POS 19
#define RX_FILT_CTRL__RG_RX_DECIM_FIR_X1_EN_MASK 0x00080000

/** Field rg_rx_comp_fir_sel
RX Compensation Filter select
-  0: Wn=0.10, down-sample by 2 
-  1: Wn=0.15, down-sample by 2, for otherwise, HW auto config coefs
-  2: Wn=0.20, down-sample by 2
-  3: Wn=0.25, down-sample by 2
-  4: Wn=0.30, down-sample by 2
-  5: Wn=0.35, down-sample by 2
-  6: Wn=0.40, down-sample by 2, for rg_sps=10 or h>1.8, HW auto config coefs
-  7: down-sample by 2, re-fill default filter coefs config by rg_rx_comp_fir_1fxx
-  8: Wn=0.15, down-sample by 1
-  9: Wn=0.20, down-sample by 1, for otherwise, filter coefs config by rg_rx_comp_fir_1fxx
- 10: Wn=0.30, down-sample by 1
- 11: Wn=0.40, down-sample by 1
- 12: Wn=0.50, down-sample by 1
- 13: Wn=0.60, down-sample by 1, for rg_sps=10 or h>1.8, HW auto config coefs
- 14: Wn=0.70, down-sample by 1
- 15: bypass mode, no down-sampling and no filtering
*/
#define RX_FILT_CTRL__RG_RX_COMP_FIR_SEL_POS 20
#define RX_FILT_CTRL__RG_RX_COMP_FIR_SEL_MASK 0x00F00000

/** Field rg_rx_decim_fir_sel_p
RX decimation filter coef select before Preamble indication
 - Only for down-sample by 2
0: Wn=0.10
1: Wn=0.13
2: Wn=0.15, config by rg_rx_decim_fir_xxx_d default
3: Wn=0.20
4: Wn=0.25, for h<=1.8 & rg_sps<=5, config by rg_rx_decim_fir_xxx_p default
5: Wn=0.30
6: Wn=0.35
7: Wn=0.40, for h>1.8 or otherwise, HW auto config coefs
*/
#define RX_FILT_CTRL__RG_RX_DECIM_FIR_SEL_P_POS 24
#define RX_FILT_CTRL__RG_RX_DECIM_FIR_SEL_P_MASK 0x07000000

/** Field rg_rx_decim_fir_sel_d
RX decimation filter coef select after Preamble indication
 - Only for down-sample by 2
0: Wn=0.10, for otherwise, HW auto config coefs
1: Wn=0.13
2: Wn=0.15, for h<=1.8 & rg_sps<=5, config by rg_rx_decim_fir_xxx_d default
3: Wn=0.20
4: Wn=0.25, for h>1.8, config by rg_rx_decim_fir_xxx_p default
5: Wn=0.30
6: Wn=0.35
7: Wn=0.40
*/
#define RX_FILT_CTRL__RG_RX_DECIM_FIR_SEL_D_POS 28
#define RX_FILT_CTRL__RG_RX_DECIM_FIR_SEL_D_MASK 0x70000000

/*****************************************************************************/

/** Reg rx_decim_fir_p1_p0
RX Decimation Filter 2F0 & 2F1 coefficient for 2FD
*/
#define PHY_CSR__RX_DECIM_FIR_P1_P0 CSR_ACCESS(PHY_CSR_BASE + 0x00000094)

/** Field rg_rx_decim_fir_p0
Format is <1,0,12> in 2's complement format
*/
#define RX_DECIM_FIR_P1_P0__RG_RX_DECIM_FIR_P0_POS 0
#define RX_DECIM_FIR_P1_P0__RG_RX_DECIM_FIR_P0_MASK 0x00001FFF

/** Field rg_rx_decim_fir_p1
Format is <1,0,12> in 2's complement format
*/
#define RX_DECIM_FIR_P1_P0__RG_RX_DECIM_FIR_P1_POS 16
#define RX_DECIM_FIR_P1_P0__RG_RX_DECIM_FIR_P1_MASK 0x1FFF0000

/*****************************************************************************/

/** Reg rx_decim_fir_p3_p2
RX Decimation Filter 2F2 & 2F3 coefficient for 2FD
*/
#define PHY_CSR__RX_DECIM_FIR_P3_P2 CSR_ACCESS(PHY_CSR_BASE + 0x00000098)

/** Field rg_rx_decim_fir_p2
Format is <1,0,12> in 2's complement format
*/
#define RX_DECIM_FIR_P3_P2__RG_RX_DECIM_FIR_P2_POS 0
#define RX_DECIM_FIR_P3_P2__RG_RX_DECIM_FIR_P2_MASK 0x00001FFF

/** Field rg_rx_decim_fir_p3
Format is <1,0,12> in 2's complement format
*/
#define RX_DECIM_FIR_P3_P2__RG_RX_DECIM_FIR_P3_POS 16
#define RX_DECIM_FIR_P3_P2__RG_RX_DECIM_FIR_P3_MASK 0x1FFF0000

/*****************************************************************************/

/** Reg rx_decim_fir_p5_p4
RX Decimation Filter 2F4 & 2F5 coefficient for 2FD
*/
#define PHY_CSR__RX_DECIM_FIR_P5_P4 CSR_ACCESS(PHY_CSR_BASE + 0x0000009C)

/** Field rg_rx_decim_fir_p4
Format is <1,0,12> in 2's complement format
*/
#define RX_DECIM_FIR_P5_P4__RG_RX_DECIM_FIR_P4_POS 0
#define RX_DECIM_FIR_P5_P4__RG_RX_DECIM_FIR_P4_MASK 0x00001FFF

/** Field rg_rx_decim_fir_p5
Format is <1,0,12> in 2's complement format
*/
#define RX_DECIM_FIR_P5_P4__RG_RX_DECIM_FIR_P5_POS 16
#define RX_DECIM_FIR_P5_P4__RG_RX_DECIM_FIR_P5_MASK 0x1FFF0000

/*****************************************************************************/

/** Reg rx_decim_fir_p7_p6
RX Decimation Filter 2F6 & 2F7 coefficient for 2FD
*/
#define PHY_CSR__RX_DECIM_FIR_P7_P6 CSR_ACCESS(PHY_CSR_BASE + 0x000000A0)

/** Field rg_rx_decim_fir_p6
Format is <1,0,12> in 2's complement format
*/
#define RX_DECIM_FIR_P7_P6__RG_RX_DECIM_FIR_P6_POS 0
#define RX_DECIM_FIR_P7_P6__RG_RX_DECIM_FIR_P6_MASK 0x00001FFF

/** Field rg_rx_decim_fir_p7
Format is <1,0,12> in 2's complement format
*/
#define RX_DECIM_FIR_P7_P6__RG_RX_DECIM_FIR_P7_POS 16
#define RX_DECIM_FIR_P7_P6__RG_RX_DECIM_FIR_P7_MASK 0x1FFF0000

/*****************************************************************************/

/** Reg rx_decim_fir_p9_p8
RX Decimation Filter 2F8 & 2F9 coefficient for 2FD
*/
#define PHY_CSR__RX_DECIM_FIR_P9_P8 CSR_ACCESS(PHY_CSR_BASE + 0x000000A4)

/** Field rg_rx_decim_fir_p8
Format is <1,0,12> in 2's complement format
*/
#define RX_DECIM_FIR_P9_P8__RG_RX_DECIM_FIR_P8_POS 0
#define RX_DECIM_FIR_P9_P8__RG_RX_DECIM_FIR_P8_MASK 0x00001FFF

/** Field rg_rx_decim_fir_p9
Format is <1,0,12> in 2's complement format
*/
#define RX_DECIM_FIR_P9_P8__RG_RX_DECIM_FIR_P9_POS 16
#define RX_DECIM_FIR_P9_P8__RG_RX_DECIM_FIR_P9_MASK 0x1FFF0000

/*****************************************************************************/

/** Reg rx_decim_fir_p11_p10
RX Decimation Filter 2F10 & 2F11 coefficient for 2FD
*/
#define PHY_CSR__RX_DECIM_FIR_P11_P10 CSR_ACCESS(PHY_CSR_BASE + 0x000000A8)

/** Field rg_rx_decim_fir_p10
Format is <1,0,12> in 2's complement format
*/
#define RX_DECIM_FIR_P11_P10__RG_RX_DECIM_FIR_P10_POS 0
#define RX_DECIM_FIR_P11_P10__RG_RX_DECIM_FIR_P10_MASK 0x00001FFF

/** Field rg_rx_decim_fir_p11
Format is <1,0,12> in 2's complement format
*/
#define RX_DECIM_FIR_P11_P10__RG_RX_DECIM_FIR_P11_POS 16
#define RX_DECIM_FIR_P11_P10__RG_RX_DECIM_FIR_P11_MASK 0x1FFF0000

/*****************************************************************************/

/** Reg rx_decim_fir_p13_p12
RX Decimation Filter 2F12 & 2F13 coefficient for 2FD
*/
#define PHY_CSR__RX_DECIM_FIR_P13_P12 CSR_ACCESS(PHY_CSR_BASE + 0x000000AC)

/** Field rg_rx_decim_fir_p12
Format is <1,0,12> in 2's complement format
*/
#define RX_DECIM_FIR_P13_P12__RG_RX_DECIM_FIR_P12_POS 0
#define RX_DECIM_FIR_P13_P12__RG_RX_DECIM_FIR_P12_MASK 0x00001FFF

/** Field rg_rx_decim_fir_p13
Format is <1,0,12> in 2's complement format
*/
#define RX_DECIM_FIR_P13_P12__RG_RX_DECIM_FIR_P13_POS 16
#define RX_DECIM_FIR_P13_P12__RG_RX_DECIM_FIR_P13_MASK 0x1FFF0000

/*****************************************************************************/

/** Reg rx_decim_fir_p15_p14
RX Decimation Filter 2F14 & 2F15 coefficient for 2FD
*/
#define PHY_CSR__RX_DECIM_FIR_P15_P14 CSR_ACCESS(PHY_CSR_BASE + 0x000000B0)

/** Field rg_rx_decim_fir_p14
Format is <1,0,12> in 2's complement format
*/
#define RX_DECIM_FIR_P15_P14__RG_RX_DECIM_FIR_P14_POS 0
#define RX_DECIM_FIR_P15_P14__RG_RX_DECIM_FIR_P14_MASK 0x00001FFF

/** Field rg_rx_decim_fir_p15
Format is <1,0,12> in 2's complement format
*/
#define RX_DECIM_FIR_P15_P14__RG_RX_DECIM_FIR_P15_POS 16
#define RX_DECIM_FIR_P15_P14__RG_RX_DECIM_FIR_P15_MASK 0x1FFF0000

/*****************************************************************************/

/** Reg rx_decim_fir_d1_d0
RX Decimation Filter D0 & D1 coefficient after 2FD hit (Data)
*/
#define PHY_CSR__RX_DECIM_FIR_D1_D0 CSR_ACCESS(PHY_CSR_BASE + 0x000000B4)

/** Field rg_rx_decim_fir_d0
Format is <1,0,12> in 2's complement format
*/
#define RX_DECIM_FIR_D1_D0__RG_RX_DECIM_FIR_D0_POS 0
#define RX_DECIM_FIR_D1_D0__RG_RX_DECIM_FIR_D0_MASK 0x00001FFF

/** Field rg_rx_decim_fir_d1
Format is <1,0,12> in 2's complement format
*/
#define RX_DECIM_FIR_D1_D0__RG_RX_DECIM_FIR_D1_POS 16
#define RX_DECIM_FIR_D1_D0__RG_RX_DECIM_FIR_D1_MASK 0x1FFF0000

/*****************************************************************************/

/** Reg rx_decim_fir_d3_d2
RX Decimation Filter D2 & D3 coefficient after 2FD hit (Data)
*/
#define PHY_CSR__RX_DECIM_FIR_D3_D2 CSR_ACCESS(PHY_CSR_BASE + 0x000000B8)

/** Field rg_rx_decim_fir_d2
Format is <1,0,12> in 2's complement format
*/
#define RX_DECIM_FIR_D3_D2__RG_RX_DECIM_FIR_D2_POS 0
#define RX_DECIM_FIR_D3_D2__RG_RX_DECIM_FIR_D2_MASK 0x00001FFF

/** Field rg_rx_decim_fir_d3
Format is <1,0,12> in 2's complement format
*/
#define RX_DECIM_FIR_D3_D2__RG_RX_DECIM_FIR_D3_POS 16
#define RX_DECIM_FIR_D3_D2__RG_RX_DECIM_FIR_D3_MASK 0x1FFF0000

/*****************************************************************************/

/** Reg rx_decim_fir_d5_d4
RX Decimation Filter D4 & D5 coefficient after 2FD hit (Data)
*/
#define PHY_CSR__RX_DECIM_FIR_D5_D4 CSR_ACCESS(PHY_CSR_BASE + 0x000000BC)

/** Field rg_rx_decim_fir_d4
Format is <1,0,12> in 2's complement format
*/
#define RX_DECIM_FIR_D5_D4__RG_RX_DECIM_FIR_D4_POS 0
#define RX_DECIM_FIR_D5_D4__RG_RX_DECIM_FIR_D4_MASK 0x00001FFF

/** Field rg_rx_decim_fir_d5
Format is <1,0,12> in 2's complement format
*/
#define RX_DECIM_FIR_D5_D4__RG_RX_DECIM_FIR_D5_POS 16
#define RX_DECIM_FIR_D5_D4__RG_RX_DECIM_FIR_D5_MASK 0x1FFF0000

/*****************************************************************************/

/** Reg rx_decim_fir_d7_d6
RX Decimation Filter D6 & D7 coefficient after 2FD hit (Data)
*/
#define PHY_CSR__RX_DECIM_FIR_D7_D6 CSR_ACCESS(PHY_CSR_BASE + 0x000000C0)

/** Field rg_rx_decim_fir_d6
Format is <1,0,12> in 2's complement format
*/
#define RX_DECIM_FIR_D7_D6__RG_RX_DECIM_FIR_D6_POS 0
#define RX_DECIM_FIR_D7_D6__RG_RX_DECIM_FIR_D6_MASK 0x00001FFF

/** Field rg_rx_decim_fir_d7
Format is <1,0,12> in 2's complement format
*/
#define RX_DECIM_FIR_D7_D6__RG_RX_DECIM_FIR_D7_POS 16
#define RX_DECIM_FIR_D7_D6__RG_RX_DECIM_FIR_D7_MASK 0x1FFF0000

/*****************************************************************************/

/** Reg rx_decim_fir_d9_d8
RX Decimation Filter D8 & D9 coefficient after 2FD hit (Data)
*/
#define PHY_CSR__RX_DECIM_FIR_D9_D8 CSR_ACCESS(PHY_CSR_BASE + 0x000000C4)

/** Field rg_rx_decim_fir_d8
Format is <1,0,12> in 2's complement format
*/
#define RX_DECIM_FIR_D9_D8__RG_RX_DECIM_FIR_D8_POS 0
#define RX_DECIM_FIR_D9_D8__RG_RX_DECIM_FIR_D8_MASK 0x00001FFF

/** Field rg_rx_decim_fir_d9
Format is <1,0,12> in 2's complement format
*/
#define RX_DECIM_FIR_D9_D8__RG_RX_DECIM_FIR_D9_POS 16
#define RX_DECIM_FIR_D9_D8__RG_RX_DECIM_FIR_D9_MASK 0x1FFF0000

/*****************************************************************************/

/** Reg rx_decim_fir_d11_d10
RX Decimation Filter D10 & D11 coefficient after 2FD hit (Data)
*/
#define PHY_CSR__RX_DECIM_FIR_D11_D10 CSR_ACCESS(PHY_CSR_BASE + 0x000000C8)

/** Field rg_rx_decim_fir_d10
Format is <1,0,12> in 2's complement format
*/
#define RX_DECIM_FIR_D11_D10__RG_RX_DECIM_FIR_D10_POS 0
#define RX_DECIM_FIR_D11_D10__RG_RX_DECIM_FIR_D10_MASK 0x00001FFF

/** Field rg_rx_decim_fir_d11
Format is <1,0,12> in 2's complement format
*/
#define RX_DECIM_FIR_D11_D10__RG_RX_DECIM_FIR_D11_POS 16
#define RX_DECIM_FIR_D11_D10__RG_RX_DECIM_FIR_D11_MASK 0x1FFF0000

/*****************************************************************************/

/** Reg rx_decim_fir_d13_d12
RX Decimation Filter D12 & D13 coefficient after 2FD hit (Data)
*/
#define PHY_CSR__RX_DECIM_FIR_D13_D12 CSR_ACCESS(PHY_CSR_BASE + 0x000000CC)

/** Field rg_rx_decim_fir_d12
Format is <1,0,12> in 2's complement format
*/
#define RX_DECIM_FIR_D13_D12__RG_RX_DECIM_FIR_D12_POS 0
#define RX_DECIM_FIR_D13_D12__RG_RX_DECIM_FIR_D12_MASK 0x00001FFF

/** Field rg_rx_decim_fir_d13
Format is <1,0,12> in 2's complement format
*/
#define RX_DECIM_FIR_D13_D12__RG_RX_DECIM_FIR_D13_POS 16
#define RX_DECIM_FIR_D13_D12__RG_RX_DECIM_FIR_D13_MASK 0x1FFF0000

/*****************************************************************************/

/** Reg rx_decim_fir_d15_d14
RX Decimation Filter D14 & D15 coefficient after 2FD hit (Data)
*/
#define PHY_CSR__RX_DECIM_FIR_D15_D14 CSR_ACCESS(PHY_CSR_BASE + 0x000000D0)

/** Field rg_rx_decim_fir_d14
Format is <1,0,12> in 2's complement format
*/
#define RX_DECIM_FIR_D15_D14__RG_RX_DECIM_FIR_D14_POS 0
#define RX_DECIM_FIR_D15_D14__RG_RX_DECIM_FIR_D14_MASK 0x00001FFF

/** Field rg_rx_decim_fir_d15
Format is <1,0,12> in 2's complement format
*/
#define RX_DECIM_FIR_D15_D14__RG_RX_DECIM_FIR_D15_POS 16
#define RX_DECIM_FIR_D15_D14__RG_RX_DECIM_FIR_D15_MASK 0x1FFF0000

/*****************************************************************************/

/** Reg rx_rssi_ctrl
RX RSSI Control Register
*/
#define PHY_CSR__RX_RSSI_CTRL CSR_ACCESS(PHY_CSR_BASE + 0x000000E0)

/** Field rg_rssi_listen_en
RX RSSI listen enable. 
0: default
1: RX path will be activated only if RSSI level is larger than rg_rssi_th. 
*/
#define RX_RSSI_CTRL__RG_RSSI_LISTEN_EN_POS 0
#define RX_RSSI_CTRL__RG_RSSI_LISTEN_EN_MASK 0x00000001

/** Field rg_rssi_ki_sel
RSSI Ki select:
0: 2^-2
1: 2^-3
2: 2^-4
3: 2^-5
4: 2^-6
5: 2^-7
6: 2^-8
*/
#define RX_RSSI_CTRL__RG_RSSI_KI_SEL_POS 4
#define RX_RSSI_CTRL__RG_RSSI_KI_SEL_MASK 0x00000070

/** Field rg_rssi_listen_th_sel
RSSI threshold to activate RX path if rg_rssi_listen_en=1.
RSSI threshold format is <1,2,12>.
It represents 8-bits in decimal part. <0.xxxxxxxx0000> in binary format.
*/
#define RX_RSSI_CTRL__RG_RSSI_LISTEN_TH_SEL_POS 8
#define RX_RSSI_CTRL__RG_RSSI_LISTEN_TH_SEL_MASK 0x0000FF00

/** Field rg_rssi_listen_cnfm_cnt
RSSI over threshold confirm count. Each check period is the same as DAGC gain update period. If RSSI is over threshold continuously for this confirm count, RX path will then be activated.
The confirm count will be 2*N. N=0~15.
*/
#define RX_RSSI_CTRL__RG_RSSI_LISTEN_CNFM_CNT_POS 16
#define RX_RSSI_CTRL__RG_RSSI_LISTEN_CNFM_CNT_MASK 0x000F0000

/** Field rg_rssi_stop_ctrl
RSSI stop by 
0: SFD
1: PMD
*/
#define RX_RSSI_CTRL__RG_RSSI_STOP_CTRL_POS 20
#define RX_RSSI_CTRL__RG_RSSI_STOP_CTRL_MASK 0x00100000

/*****************************************************************************/

/** Reg rx_rfagc_ctrl
RX RF and IF AGC Control Register
*/
#define PHY_CSR__RX_RFAGC_CTRL CSR_ACCESS(PHY_CSR_BASE + 0x000000E4)

/** Field rg_rx_rfagc_en
RF AGC enable
*/
#define RX_RFAGC_CTRL__RG_RX_RFAGC_EN_POS 0
#define RX_RFAGC_CTRL__RG_RX_RFAGC_EN_MASK 0x00000001

/** Field rg_rx_ifagc_en
IF AGC enable
*/
#define RX_RFAGC_CTRL__RG_RX_IFAGC_EN_POS 1
#define RX_RFAGC_CTRL__RG_RX_IFAGC_EN_MASK 0x00000002

/** Field rg_rx_rfagc_force_lk_en
RF AGC force lock enable
*/
#define RX_RFAGC_CTRL__RG_RX_RFAGC_FORCE_LK_EN_POS 2
#define RX_RFAGC_CTRL__RG_RX_RFAGC_FORCE_LK_EN_MASK 0x00000004

/** Field rg_rx_ifagc_force_lk_en
IF AGC force lock enable
*/
#define RX_RFAGC_CTRL__RG_RX_IFAGC_FORCE_LK_EN_POS 3
#define RX_RFAGC_CTRL__RG_RX_IFAGC_FORCE_LK_EN_MASK 0x00000008

/** Field rg_rf_pkdet_ck_sel
RF peak detection cycle period select. 
0: 0.5us
1: 1us
2: 1.5us
3: 2us
4: 2.5us
5: 3us
6: 3.5us
7: 4us
*/
#define RX_RFAGC_CTRL__RG_RF_PKDET_CK_SEL_POS 4
#define RX_RFAGC_CTRL__RG_RF_PKDET_CK_SEL_MASK 0x00000070

/** Field rg_if_pkdet_ck_sel
IF peak detection cycle period select. 
0: 1us
1: 2us
2: 3us
3: 4us
4: 5us
5: 6us
6: 7us
7: 8us
*/
#define RX_RFAGC_CTRL__RG_IF_PKDET_CK_SEL_POS 8
#define RX_RFAGC_CTRL__RG_IF_PKDET_CK_SEL_MASK 0x00000700

/** Field rg_fe_agc_restart
Restart RF/IF AGC while already in receiving state (rg_rx_en=1). Hardware will auto clear this bit after AGC is restarted.
*/
#define RX_RFAGC_CTRL__RG_FE_AGC_RESTART_POS 12
#define RX_RFAGC_CTRL__RG_FE_AGC_RESTART_MASK 0x00001000

/** Field rg_rx_ifagc_option2
IF AGC Option2 Algorithm enable.
0: Use Option1 Binary Search method to tune IF PGA gain.
1: Use Option2 Decremental Search method to tune IF PGA gain.
*/
#define RX_RFAGC_CTRL__RG_RX_IFAGC_OPTION2_POS 13
#define RX_RFAGC_CTRL__RG_RX_IFAGC_OPTION2_MASK 0x00002000

/** Field rg_rx_ifagc2_step_size_sel
IF AGC Option2 Algorithm gain step select.
0: 1dB
1: 2dB
*/
#define RX_RFAGC_CTRL__RG_RX_IFAGC2_STEP_SIZE_SEL_POS 14
#define RX_RFAGC_CTRL__RG_RX_IFAGC2_STEP_SIZE_SEL_MASK 0x00004000

/*****************************************************************************/

/** Reg rx_dagc_ctrl
RX Digital AGC Control Register
*/
#define PHY_CSR__RX_DAGC_CTRL CSR_ACCESS(PHY_CSR_BASE + 0x000000E8)

/** Field rg_rx_dagc_en
RX DAGC enable
*/
#define RX_DAGC_CTRL__RG_RX_DAGC_EN_POS 0
#define RX_DAGC_CTRL__RG_RX_DAGC_EN_MASK 0x00000001

/** Field rg_dagc_stop_by_pmb_ind_en
Stop DAGC training by (dagc_lk && pmb_ind) but not sfd_ind. 
0: disable (default)
1: enable
*/
#define RX_DAGC_CTRL__RG_DAGC_STOP_BY_PMB_IND_EN_POS 1
#define RX_DAGC_CTRL__RG_DAGC_STOP_BY_PMB_IND_EN_MASK 0x00000002

/** Field rg_dagc_fbdly_ook_mode
DAGC gain update period is the same as RX Filter (compensation filter) output rate. (This option is for OOK mode only)
0: disable (default)
1: enable
*/
#define RX_DAGC_CTRL__RG_DAGC_FBDLY_OOK_MODE_POS 2
#define RX_DAGC_CTRL__RG_DAGC_FBDLY_OOK_MODE_MASK 0x00000004

/** Field rg_dagc_man_en
DAGC manual mode to set dagc_gain manually.
0: disable (default)
1: enable
*/
#define RX_DAGC_CTRL__RG_DAGC_MAN_EN_POS 3
#define RX_DAGC_CTRL__RG_DAGC_MAN_EN_MASK 0x00000008

/** Field rg_dagc_tgt
DAGC target reference level. 
The format is <0,0,5>. It specify the 5-bit decimal part.
Ex. 0.11010 is 0.8125
Ex. set 0x1d (0.11101) is 0.9062
*/
#define RX_DAGC_CTRL__RG_DAGC_TGT_POS 4
#define RX_DAGC_CTRL__RG_DAGC_TGT_MASK 0x000001F0

/** Field rg_dagc_lk_ctrl
DAGC lock control for B1 
0: training by RSSI threshold
1: stop after DAGC peak detected lock
*/
#define RX_DAGC_CTRL__RG_DAGC_LK_CTRL_POS 10
#define RX_DAGC_CTRL__RG_DAGC_LK_CTRL_MASK 0x00000400

/** Field rg_dagc_lk_thresh
DAGC lock threshold level.
The format is <0,0,6>. It specify the LSB 5-bit decimal part (0.0xxxxx).
Ex. 0.010000 is 0.25
*/
#define RX_DAGC_CTRL__RG_DAGC_LK_THRESH_POS 12
#define RX_DAGC_CTRL__RG_DAGC_LK_THRESH_MASK 0x0001F000

/** Field rg_dagc_lk_cnt_num
DAGC lock count number. N=rg_dagc_lk_cnt_num*4.
The format is 4-bits. It specify how many DAGC gain update periods for which signal level minus DAGC target level is smaller than DAGC lock threshold level. It means DAGC gain is stable.
*/
#define RX_DAGC_CTRL__RG_DAGC_LK_CNT_NUM_POS 20
#define RX_DAGC_CTRL__RG_DAGC_LK_CNT_NUM_MASK 0x00F00000

/** Field rg_dagc_fbdly_sel
DAGC gain update period select:
It will update RSSI and DAGC for every N samples of pre-decimation filter output. N=rg_dagc_fbdly_sel*4.
0: not valid 
1: N = 4 samples
2: N = 8 samples
3: N = 12 samples
        :
15: N = 60 samples
*/
#define RX_DAGC_CTRL__RG_DAGC_FBDLY_SEL_POS 28
#define RX_DAGC_CTRL__RG_DAGC_FBDLY_SEL_MASK 0xF0000000

/*****************************************************************************/

/** Reg rx_iqc_ddc_ctrl
RX IQC and DDC Control Register
*/
#define PHY_CSR__RX_IQC_DDC_CTRL CSR_ACCESS(PHY_CSR_BASE + 0x000000EC)

/** Field rg_rx_iqc_en
RX IQC (IQ Imbalance Compensation) enable
*/
#define RX_IQC_DDC_CTRL__RG_RX_IQC_EN_POS 0
#define RX_IQC_DDC_CTRL__RG_RX_IQC_EN_MASK 0x00000001

/** Field rg_rx_dcb_en
RX DCB (DC Blocking) enable
*/
#define RX_IQC_DDC_CTRL__RG_RX_DCB_EN_POS 1
#define RX_IQC_DDC_CTRL__RG_RX_DCB_EN_MASK 0x00000002

/** Field rg_rx_ddc_en
RX DDC (Digital Down Conversion) enable
*/
#define RX_IQC_DDC_CTRL__RG_RX_DDC_EN_POS 2
#define RX_IQC_DDC_CTRL__RG_RX_DDC_EN_MASK 0x00000004

/** Field rg_rx_iqc_alpha_sel
IQC Alpha select:
0: 2^-4
1: 2^-5
2: 2^-6
3: 2^-7
*/
#define RX_IQC_DDC_CTRL__RG_RX_IQC_ALPHA_SEL_POS 4
#define RX_IQC_DDC_CTRL__RG_RX_IQC_ALPHA_SEL_MASK 0x00000030

/** Field rg_rx_dcb_k_sel
DCB K select:
0: 2^-6
1: 2^-7
2: 2^-8
3: 2^-9
*/
#define RX_IQC_DDC_CTRL__RG_RX_DCB_K_SEL_POS 6
#define RX_IQC_DDC_CTRL__RG_RX_DCB_K_SEL_MASK 0x000000C0

/** Field rg_rx_ddc_delta_f_k_sel
Time constant for Digital Down-Conversion frequency adjustment:
0: x1 (4FSK)
1: x1/2 (2FSK or CSS)
*/
#define RX_IQC_DDC_CTRL__RG_RX_DDC_DELTA_F_K_SEL_POS 8
#define RX_IQC_DDC_CTRL__RG_RX_DDC_DELTA_F_K_SEL_MASK 0x00000100

/** Field rg_rx_iqc_coe_sel
iqc coe c  shift
0: 1
1: 2
2: 4
3: 8
*/
#define RX_IQC_DDC_CTRL__RG_RX_IQC_COE_SEL_POS 12
#define RX_IQC_DDC_CTRL__RG_RX_IQC_COE_SEL_MASK 0x00003000

/** Field rg_if_freq_offset
Local IF frequency in <1,1,12> format.
 - rg_if_freq_offset = -1 x (freq_offset/PHY_CLK) x 2xPi x M1p
 - (default) rg_if_freq_offset = -1 x (500K/32M) x 2xPi x 8 = -0.7854 = 0x336F
 - For freqency offset 500 Khz
 (1) PHY CLK=32M, M1p=8,   offset=500K : rg_if_freq_offset = -0.78540= 0x336F
 (2) PHY CLK=32M, M1p=10, offset=500K : rg_if_freq_offset = -0.98175= 0x304B
 (3) PHY CLK=32M, M1p=7,   offset=500K : rg_if_freq_offset = -0.68722= 0x3501
 (4) PHY CLK=24M, M1p=8,   offset=500K : rg_if_freq_offset = -1.04720= 0x2F3F
 (5) PHY CLK=24M, M1p=10, offset=500K : rg_if_freq_offset = -1.30900= 0x2B0E
*/
#define RX_IQC_DDC_CTRL__RG_IF_FREQ_OFFSET_POS 16
#define RX_IQC_DDC_CTRL__RG_IF_FREQ_OFFSET_MASK 0x3FFF0000

/*****************************************************************************/

/** Reg rx_rssi_dif_ctrl
RX RSSI different control
*/
#define PHY_CSR__RX_RSSI_DIF_CTRL CSR_ACCESS(PHY_CSR_BASE + 0x000000F0)

/** Field rg_rssi_over_thr
RSSI different over threshold select
0 : rssi_dif_over_thr =  0 dB
1 : rssi_dif_over_thr =  3 dB
2 : rssi_dif_over_thr =  6 dB
3 : rssi_dif_over_thr =  9 dB
4 : rssi_dif_over_thr = 12 dB
5 : rssi_dif_over_thr = 15 dB
6 : rssi_dif_over_thr = 18 dB
7 : rssi_dif_over_thr = 21 dB
*/
#define RX_RSSI_DIF_CTRL__RG_RSSI_OVER_THR_POS 0
#define RX_RSSI_DIF_CTRL__RG_RSSI_OVER_THR_MASK 0x00000007

/** Field rg_rssi_dif_over_cnfm
RSSI different over threshold confirm symbol number
*/
#define RX_RSSI_DIF_CTRL__RG_RSSI_DIF_OVER_CNFM_POS 4
#define RX_RSSI_DIF_CTRL__RG_RSSI_DIF_OVER_CNFM_MASK 0x000000F0

/** Field rg_rssi_less_thr
RSSI different less threshold select
0 : rssi_dif_less_thr =  -1 dB
1 : rssi_dif_less_thr =  -3 dB
2 : rssi_dif_less_thr =  -6 dB
3 : rssi_dif_less_thr =  -9 dB
4 : rssi_dif_less_thr = -12 dB
5 : rssi_dif_less_thr = -15 dB
6 : rssi_dif_less_thr = -18 dB
7 : rssi_dif_less_thr = -21 dB
*/
#define RX_RSSI_DIF_CTRL__RG_RSSI_LESS_THR_POS 8
#define RX_RSSI_DIF_CTRL__RG_RSSI_LESS_THR_MASK 0x00000700

/** Field rg_rssi_dif_less_cnfm
RSSI different less threshold confirm symbol number
*/
#define RX_RSSI_DIF_CTRL__RG_RSSI_DIF_LESS_CNFM_POS 12
#define RX_RSSI_DIF_CTRL__RG_RSSI_DIF_LESS_CNFM_MASK 0x0000F000

/** Field rg_rssi_over_auto_restart
HW auto restart rg_rx_en if rg_phy_rx_rssi_over_irq happen
*/
#define RX_RSSI_DIF_CTRL__RG_RSSI_OVER_AUTO_RESTART_POS 16
#define RX_RSSI_DIF_CTRL__RG_RSSI_OVER_AUTO_RESTART_MASK 0x00010000

/** Field rg_rssi_over_auto_clr
HW auto clear rg_rx_en if rg_phy_rx_rssi_over_irq happen
*/
#define RX_RSSI_DIF_CTRL__RG_RSSI_OVER_AUTO_CLR_POS 17
#define RX_RSSI_DIF_CTRL__RG_RSSI_OVER_AUTO_CLR_MASK 0x00020000

/** Field rg_rssi_less_auto_clr
HW auto clear rg_rx_en if rg_phy_rx_rssi_less_irq happen
*/
#define RX_RSSI_DIF_CTRL__RG_RSSI_LESS_AUTO_CLR_POS 18
#define RX_RSSI_DIF_CTRL__RG_RSSI_LESS_AUTO_CLR_MASK 0x00040000

/** Field rg_rssi_diff_thr_sel
RSSI different threshold (RSSI_diff_thr) select:
0: HW latch RSSI value at Preamle or MC indication 
1: use the "rg_rssi_ib_lsn_thr" as threshold value, format <0,7,1>
*/
#define RX_RSSI_DIF_CTRL__RG_RSSI_DIFF_THR_SEL_POS 20
#define RX_RSSI_DIF_CTRL__RG_RSSI_DIFF_THR_SEL_MASK 0x00100000

/** Field rg_rssi_diff_start_ctrl
RSSI different start control:
0: from Preamle indication, for monitor Packet RSSI 
1: from rx_en, for CCA, RSSI listening
*/
#define RX_RSSI_DIF_CTRL__RG_RSSI_DIFF_START_CTRL_POS 21
#define RX_RSSI_DIF_CTRL__RG_RSSI_DIFF_START_CTRL_MASK 0x00200000

/** Field rg_rssi_offset
RSSI offset value, format <1,4,3>
 - default set 36 (=4.5x8)
*/
#define RX_RSSI_DIF_CTRL__RG_RSSI_OFFSET_POS 24
#define RX_RSSI_DIF_CTRL__RG_RSSI_OFFSET_MASK 0xFF000000

/*****************************************************************************/

/** Reg rx_mfagc_ctrl
RX Match Filter Output AGC Control Register
*/
#define PHY_CSR__RX_MFAGC_CTRL CSR_ACCESS(PHY_CSR_BASE + 0x000000F4)

/** Field rg_mfagc_en
MF Output AGC enable
*/
#define RX_MFAGC_CTRL__RG_MFAGC_EN_POS 0
#define RX_MFAGC_CTRL__RG_MFAGC_EN_MASK 0x00000001

/** Field rg_mfagc_stop_by_pmb_ind_en
Stop MFAGC training by (mfagc_lk && pmb_ind) but not sfd_ind. It can be used in case the SFD pattern may cause MFAGC gain change dramatically in some cases (ex. 4FSK + Gaussian Filtering enable)
0: disable (default)
1: enable
*/
#define RX_MFAGC_CTRL__RG_MFAGC_STOP_BY_PMB_IND_EN_POS 1
#define RX_MFAGC_CTRL__RG_MFAGC_STOP_BY_PMB_IND_EN_MASK 0x00000002

/** Field rg_mfagc_gain_ctrl
MF AGC gain control :
(1) rg_mfagc_en=0 : MF gain set by rg_mfagc_ini
(2) rg_mfagc_en=1 :
    (2-1) rg_mfagc_gain_ctrl=0 : MF gain caculated by HW MFAGC, 
                                                   Then set rg_mfagc_ini after rx_dcr_done
    (2-2) rg_mfagc_gain_ctrl=1 : MF gain caculated by HW MFAGC
*/
#define RX_MFAGC_CTRL__RG_MFAGC_GAIN_CTRL_POS 2
#define RX_MFAGC_CTRL__RG_MFAGC_GAIN_CTRL_MASK 0x00000004

/** Field rg_mf_taps_sel
MF taps selction
0: 3 taps for rg_sps=4 or 5
1: 7 taps for rg_sps=10
*/
#define RX_MFAGC_CTRL__RG_MF_TAPS_SEL_POS 3
#define RX_MFAGC_CTRL__RG_MF_TAPS_SEL_MASK 0x00000008

/** Field rg_mfagc_k
Time-constant for Match Filter Output AGC adaptation, in the range of [1/64,..,1/4]
0: 1/4
1: 1/8
2: 1/16
3: 1/32
4: 1/64
*/
#define RX_MFAGC_CTRL__RG_MFAGC_K_POS 4
#define RX_MFAGC_CTRL__RG_MFAGC_K_MASK 0x00000070

/** Field rg_mfagc_ampk
Time-constant for Match Filter output average level evaluation
0: 1/4
1: 1/8
2: 1/16
3: 1/32
4: 1/64
*/
#define RX_MFAGC_CTRL__RG_MFAGC_AMPK_POS 8
#define RX_MFAGC_CTRL__RG_MFAGC_AMPK_MASK 0x00000700

/** Field rg_mfagc_tgt
mfagc target:
0: 1 (for 2FSK)
1: 2
2: 3 (for 4FSK)
3: 4
*/
#define RX_MFAGC_CTRL__RG_MFAGC_TGT_POS 12
#define RX_MFAGC_CTRL__RG_MFAGC_TGT_MASK 0x00003000

/** Field rg_mfagc_thsc
mfagc threshold scaling:
0: 1/2
1: 1/4
2: 1/8
3: 1/16
*/
#define RX_MFAGC_CTRL__RG_MFAGC_THSC_POS 14
#define RX_MFAGC_CTRL__RG_MFAGC_THSC_MASK 0x0000C000

/** Field rg_mfagc_lkcnt
mfagc lock count:
0: 1
1: 2
2: 3
 ....
15: 16
*/
#define RX_MFAGC_CTRL__RG_MFAGC_LKCNT_POS 16
#define RX_MFAGC_CTRL__RG_MFAGC_LKCNT_MASK 0x000F0000

/** Field rg_mfagc_ini
Gain initial value. 10 bits unsigned format <0,2,8>
 - rg_mfagc_ini = round( 2 x rg_sps / (1+rg_rx_kdiff_sc) / h / (2xPI) x 2^8)
 - default h=1, rg_mfagc_ini =  round( 2x5 / (1+0) /1/(2xPI) x 2^8) = 407 = 0x197
 - h=0.5, rg_mfagc_ini =  round( 2x5 / (1+0) /0.5/(2xPI) x 2^8) = 815 = 0x32F
 - h=2.0, rg_mfagc_ini =  round( 2x5 / (1+0) /2.0/(2xPI) x 2^8) = 204 = 0x0CC
 - h=2.5, rg_mfagc_ini =  round( 2x10 / (1+0) /2.5/(2xPI) x 2^8) = 326 = 0x146
For 4FSK : set rg_rx_kdiff_sc=1
 - h=1/3, rg_mfagc_ini =  round( 2x5 / (1+1) /(1/3)/(2xPI) x 2^8) = 611 = 0x263
*/
#define RX_MFAGC_CTRL__RG_MFAGC_INI_POS 20
#define RX_MFAGC_CTRL__RG_MFAGC_INI_MASK 0x3FF00000

/** Field rg_rx_kdiff_sc
Phase Differentiator output scaling
0: x1
1: x2, setting relative rg_mfagc_ini RG
2: x4, setting relative rg_mfagc_ini RG
*/
#define RX_MFAGC_CTRL__RG_RX_KDIFF_SC_POS 30
#define RX_MFAGC_CTRL__RG_RX_KDIFF_SC_MASK 0xC0000000

/*****************************************************************************/

/** Reg rx_mfagc_ctrl2
RX Match Filter Output AGC Control Register 2
*/
#define PHY_CSR__RX_MFAGC_CTRL2 CSR_ACCESS(PHY_CSR_BASE + 0x000000F8)

/** Field rg_ook_th
OOK Signal DC Level Evaluation Time Constant, in the range of [1/64 ~ 1/4]
0: 1/4
1: 1/8
2: 1/16
3: 1/32
4: 1/64
*/
#define RX_MFAGC_CTRL2__RG_OOK_TH_POS 0
#define RX_MFAGC_CTRL2__RG_OOK_TH_MASK 0x00000007

/*****************************************************************************/

/** Reg rx_time_rcvy_ctrl
RX Timing Recovery Control Register
*/
#define PHY_CSR__RX_TIME_RCVY_CTRL CSR_ACCESS(PHY_CSR_BASE + 0x000000FC)

/** Field rg_rx_tr_en
RX Timing Recovery enable
*/
#define RX_TIME_RCVY_CTRL__RG_RX_TR_EN_POS 0
#define RX_TIME_RCVY_CTRL__RG_RX_TR_EN_MASK 0x00000001

/** Field rg_zc_det_en
Zero crossing detection enable
*/
#define RX_TIME_RCVY_CTRL__RG_ZC_DET_EN_POS 1
#define RX_TIME_RCVY_CTRL__RG_ZC_DET_EN_MASK 0x00000002

/** Field rg_tr_forced_en
Timing Recovery force enable. Originally timing recovery will only enable after RF/IF AGC lock. This control bit force timing recovery always enable.
0: disable
1: enable
*/
#define RX_TIME_RCVY_CTRL__RG_TR_FORCED_EN_POS 2
#define RX_TIME_RCVY_CTRL__RG_TR_FORCED_EN_MASK 0x00000004

/** Field rg_edge_det_th
Edge detection threshold
Format <0,2,1>. Default = 1.5 (binary format 3'b011)
*/
#define RX_TIME_RCVY_CTRL__RG_EDGE_DET_TH_POS 4
#define RX_TIME_RCVY_CTRL__RG_EDGE_DET_TH_MASK 0x00000070

/** Field rg_time_pll_k_sel
Time constant in timing recovery loop, in the range of [1/32~1/4], power of 1/2
0: 1/4
1: 1/8
2: 1/16
3: 1/32
*/
#define RX_TIME_RCVY_CTRL__RG_TIME_PLL_K_SEL_POS 12
#define RX_TIME_RCVY_CTRL__RG_TIME_PLL_K_SEL_MASK 0x00003000

/** Field rg_time_pll_k_sc
Extra scaling factor of PLL_K after SFD detected:
0: 1
1: 1/4
2: 1/8
3: 0
*/
#define RX_TIME_RCVY_CTRL__RG_TIME_PLL_K_SC_POS 14
#define RX_TIME_RCVY_CTRL__RG_TIME_PLL_K_SC_MASK 0x0000C000

/** Field rg_tlock_th
Timing lock detection threshould, in the range of [1,16]
*/
#define RX_TIME_RCVY_CTRL__RG_TLOCK_TH_POS 16
#define RX_TIME_RCVY_CTRL__RG_TLOCK_TH_MASK 0x000F0000

/** Field rg_tlock_cnt
Timing lock detection per consecutive 0s, in the range of [1,127]
*/
#define RX_TIME_RCVY_CTRL__RG_TLOCK_CNT_POS 20
#define RX_TIME_RCVY_CTRL__RG_TLOCK_CNT_MASK 0x07F00000

/** Field rg_zc_block_th
Timing recovery zcd (zero-crossing detection) block sample count. It sets a blocking sample window after a zcd event in which any new zcd event will be ignored. It can avoid false zcd event to adjust timing recovery abnormally. 
Note: in hardware, block window is (rg_zc_block_th+1) samples actually.
*/
#define RX_TIME_RCVY_CTRL__RG_ZC_BLOCK_TH_POS 28
#define RX_TIME_RCVY_CTRL__RG_ZC_BLOCK_TH_MASK 0x70000000

/*****************************************************************************/

/** Reg rx_time_rcvy_ctrl2
RX Timing Recovery Control Register 2
*/
#define PHY_CSR__RX_TIME_RCVY_CTRL2 CSR_ACCESS(PHY_CSR_BASE + 0x00000100)

/** Field rg_sps
Sample per symbol. It is Sps2TR*ss_gain. 
Sps2TR=OSR/(M1p*M1*M2*M3*M4), ex: Sps2TR=80/(8*1*1*1*2)=5
Sps2TR = 3/4/5 for SubGHz mode; 1 for CSS mode
*/
#define RX_TIME_RCVY_CTRL2__RG_SPS_POS 0
#define RX_TIME_RCVY_CTRL2__RG_SPS_MASK 0x0000001F

/** Field rg_sampling_k_sel
Sampling sample time select:
Select which sample in symbol for data sampling.
For SubGHz mode, the legal setting will be 1 to Sps2TR.
For CSS mode, the legal setting will be 1 to ss_gain.
*/
#define RX_TIME_RCVY_CTRL2__RG_SAMPLING_K_SEL_POS 16
#define RX_TIME_RCVY_CTRL2__RG_SAMPLING_K_SEL_MASK 0x000F0000

/** Field rg_time_pll_k_avg
timing recovery for T1 after alpha filter coe
*/
#define RX_TIME_RCVY_CTRL2__RG_TIME_PLL_K_AVG_POS 20
#define RX_TIME_RCVY_CTRL2__RG_TIME_PLL_K_AVG_MASK 0x00300000

/** Field rg_time_pll_alpha
timing recovery for T1 alpha filter coe
*/
#define RX_TIME_RCVY_CTRL2__RG_TIME_PLL_ALPHA_POS 22
#define RX_TIME_RCVY_CTRL2__RG_TIME_PLL_ALPHA_MASK 0x00400000

/** Field rg_tr_wm_tgt
timing recovery for T1 compensation count
*/
#define RX_TIME_RCVY_CTRL2__RG_TR_WM_TGT_POS 24
#define RX_TIME_RCVY_CTRL2__RG_TR_WM_TGT_MASK 0x01000000

/** Field rg_tr_wm_en
timing recovery for T1 alpha filter coe
*/
#define RX_TIME_RCVY_CTRL2__RG_TR_WM_EN_POS 28
#define RX_TIME_RCVY_CTRL2__RG_TR_WM_EN_MASK 0x10000000

/*****************************************************************************/

/** Reg rx_freq_rcvy_ctrl
RX Frequency Recovery Control Register
*/
#define PHY_CSR__RX_FREQ_RCVY_CTRL CSR_ACCESS(PHY_CSR_BASE + 0x00000104)

/** Field rg_rx_fr_en
RX Frequency Recovery enable
*/
#define RX_FREQ_RCVY_CTRL__RG_RX_FR_EN_POS 0
#define RX_FREQ_RCVY_CTRL__RG_RX_FR_EN_MASK 0x00000001

/** Field rg_fr_adj_neg_en
Negate the frequency adjustment value to DDC.
0: disable
1: enable
*/
#define RX_FREQ_RCVY_CTRL__RG_FR_ADJ_NEG_EN_POS 1
#define RX_FREQ_RCVY_CTRL__RG_FR_ADJ_NEG_EN_MASK 0x00000002

/** Field rg_fr_kp
Frequency Recovery PLL Kp:
0: 2^-4
1: 2^-5
2: 2^-6
3: 2^-7
4: 2^-8
5: 2^-9
6: 2^-10
Others: reserved
*/
#define RX_FREQ_RCVY_CTRL__RG_FR_KP_POS 4
#define RX_FREQ_RCVY_CTRL__RG_FR_KP_MASK 0x00000070

/** Field rg_fr_ki
Frequency Recovery PLL Ki:
0: 2^-4
1: 2^-5
2: 2^-6
3: 2^-7
4: 2^-8
5: 2^-9
6: 2^-10
Others: reserved
*/
#define RX_FREQ_RCVY_CTRL__RG_FR_KI_POS 8
#define RX_FREQ_RCVY_CTRL__RG_FR_KI_MASK 0x00000700

/** Field rg_fr_lock_th_sel
Frequency Recovery Lock threshold
0: 1/4
1: 1/8
2: 1/16
*/
#define RX_FREQ_RCVY_CTRL__RG_FR_LOCK_TH_SEL_POS 12
#define RX_FREQ_RCVY_CTRL__RG_FR_LOCK_TH_SEL_MASK 0x00003000

/** Field rg_fr_lock_cnt
Frequency Recovery Lock count: 1~15
*/
#define RX_FREQ_RCVY_CTRL__RG_FR_LOCK_CNT_POS 16
#define RX_FREQ_RCVY_CTRL__RG_FR_LOCK_CNT_MASK 0x000F0000

/** Field rg_fr_kpki_sc
Scaling factor of Kp/Ki after SFD detected:
0: 1
1: 1/2
2: 1/4
*/
#define RX_FREQ_RCVY_CTRL__RG_FR_KPKI_SC_POS 24
#define RX_FREQ_RCVY_CTRL__RG_FR_KPKI_SC_MASK 0x03000000

/*****************************************************************************/

/** Reg rx_preamble_acq_ctrl
RX Preamble Acq Control Register
*/
#define PHY_CSR__RX_PREAMBLE_ACQ_CTRL CSR_ACCESS(PHY_CSR_BASE + 0x00000108)

/** Field rg_pmb_mode
Preamble mode:
0: 8 bits
1: 16 bits
2: 24 bits
3: 32 bits
*/
#define RX_PREAMBLE_ACQ_CTRL__RG_PMB_MODE_POS 0
#define RX_PREAMBLE_ACQ_CTRL__RG_PMB_MODE_MASK 0x00000003

/** Field rg_pmb_th
Preamble acquisition threshold, in the range of [1,32].
0: 1
1: 2
  :
31: 32
*/
#define RX_PREAMBLE_ACQ_CTRL__RG_PMB_TH_POS 4
#define RX_PREAMBLE_ACQ_CTRL__RG_PMB_TH_MASK 0x000001F0

/** Field rg_sfd_th
Start-of-Frame (SFD) detection threshold, in the range of [1,31].
*/
#define RX_PREAMBLE_ACQ_CTRL__RG_SFD_TH_POS 12
#define RX_PREAMBLE_ACQ_CTRL__RG_SFD_TH_MASK 0x0001F000

/** Field rg_pmb_nacq
Number of acquired preamble to confirm.

Preamble Detection setting:
 - (rg_pmb_mode,rg_pmb_th,rg_pmb_nacq) = (0, 8-1, 15) for otherwise
 - (rg_pmb_mode,rg_pmb_th,rg_pmb_nacq) = (0, 8-1, 12) for 32.768kcps
*/
#define RX_PREAMBLE_ACQ_CTRL__RG_PMB_NACQ_POS 20
#define RX_PREAMBLE_ACQ_CTRL__RG_PMB_NACQ_MASK 0x01F00000

/*****************************************************************************/

/** Reg rx_vtdec_ctrl
RX Viterbi Decoder Control Register
*/
#define PHY_CSR__RX_VTDEC_CTRL CSR_ACCESS(PHY_CSR_BASE + 0x0000010C)

/** Field rg_vtdec_bit_rev
RX Viterbi bit reverse control
*/
#define RX_VTDEC_CTRL__RG_VTDEC_BIT_REV_POS 0
#define RX_VTDEC_CTRL__RG_VTDEC_BIT_REV_MASK 0x00000001

/** Field rg_vtdec_soft_en
Viterbi Decoding soft decision enable control:
0: disabled
1: enabled
Note: Soft decision should be forced to disabled when Data Whitening.
*/
#define RX_VTDEC_CTRL__RG_VTDEC_SOFT_EN_POS 1
#define RX_VTDEC_CTRL__RG_VTDEC_SOFT_EN_MASK 0x00000002

/** Field rg_vtdec_auto_zero_en
Force back to zero at the end of packet:
0: disabled
1: enable, trace back from 0
*/
#define RX_VTDEC_CTRL__RG_VTDEC_AUTO_ZERO_EN_POS 2
#define RX_VTDEC_CTRL__RG_VTDEC_AUTO_ZERO_EN_MASK 0x00000004

/** Field rg_vtdec_tb_len
Trace-back length, in the range of [8,16]
   - HW trace back depth = rg_vtdec_tb_len + 9
   - Default set 12, equivalent to traceback (12+9)=21 length
   - Viterbi output 8 bits/burst

   - Because short packet (Mode Switch) limit, the best setting is 
     (1) rg_vtdec_tb_len = 12 (max) for NRNSC with rg_phr_len=0~2
     (2) rg_vtdec_tb_len = 15 (max) for the others
*/
#define RX_VTDEC_CTRL__RG_VTDEC_TB_LEN_POS 4
#define RX_VTDEC_CTRL__RG_VTDEC_TB_LEN_MASK 0x000001F0

/** Field rg_vtdec_min_state
report final minimun state of Viterbi decoder.
 - The right final state is zero.
*/
#define RX_VTDEC_CTRL__RG_VTDEC_MIN_STATE_POS 9
#define RX_VTDEC_CTRL__RG_VTDEC_MIN_STATE_MASK 0x00000E00

/** Field rg_vtdec_pkt_len
(1) If rg_rx_psdu_len_man=0 (default), HW auto calculate the packet length. In the case, Viterbi need a more than length of PHR decoder (ex: 40) before HW update the RG, so HW set 16932 value at the initial state.

(2) If rg_rx_psdu_len_man=1, the decoded packet bit length formula is : 
Packet bit length rg_vtdec_pkt_len 
= (rg_rx_psdu_len_man_val + rg_phr_len + 1) * 8 + rg_vtdec_pkt_len_add
*/
#define RX_VTDEC_CTRL__RG_VTDEC_PKT_LEN_POS 12
#define RX_VTDEC_CTRL__RG_VTDEC_PKT_LEN_MASK 0x07FFF000

/** Field rg_vtdec_pkt_len_add
Extra Viterbi package length add value
  - default add 3 bits for tail bits
*/
#define RX_VTDEC_CTRL__RG_VTDEC_PKT_LEN_ADD_POS 28
#define RX_VTDEC_CTRL__RG_VTDEC_PKT_LEN_ADD_MASK 0x70000000

/*****************************************************************************/

/** Reg hac_det_ctrl
HAC Detection Control Register
*/
#define PHY_CSR__HAC_DET_CTRL CSR_ACCESS(PHY_CSR_BASE + 0x00000110)

/** Field rg_hacdet_cnt
Consecutive 0s length detection threshold: 1~63
*/
#define HAC_DET_CTRL__RG_HACDET_CNT_POS 0
#define HAC_DET_CTRL__RG_HACDET_CNT_MASK 0x0000003F

/** Field rg_mcdet_cnt
Manchester Code detection threshold: 1~63
*/
#define HAC_DET_CTRL__RG_MCDET_CNT_POS 8
#define HAC_DET_CTRL__RG_MCDET_CNT_MASK 0x00003F00

/** Field rg_mc_en_af_sfd
RX Manchester Code enable after SFD indication
0: disable
1: enable, for WMBUS
*/
#define HAC_DET_CTRL__RG_MC_EN_AF_SFD_POS 16
#define HAC_DET_CTRL__RG_MC_EN_AF_SFD_MASK 0x00010000

/** Field rg_mc_method
RX Manchester Code method in MC module
0: 0 (1) mapping 0-to-1 (1-to-0)
1: 0 (1) mapping 1-to-0 (0-to-1), for WMBUS
*/
#define HAC_DET_CTRL__RG_MC_METHOD_POS 17
#define HAC_DET_CTRL__RG_MC_METHOD_MASK 0x00020000

/** Field rg_hac_wdc_chk_en
PHR RX HAC WDC check indication
0: disable
1: enable
*/
#define HAC_DET_CTRL__RG_HAC_WDC_CHK_EN_POS 20
#define HAC_DET_CTRL__RG_HAC_WDC_CHK_EN_MASK 0x00100000

/** Field rg_hac_wdc_chk_ind
PHR RX HAC WDC check indication (if rg_hac_wdc_chk_en=1)
This register is clear next rg_rx_en enable
*/
#define HAC_DET_CTRL__RG_HAC_WDC_CHK_IND_POS 23
#define HAC_DET_CTRL__RG_HAC_WDC_CHK_IND_MASK 0x00800000

/** Field rg_rx_sniffer_en
PHY RX sniffer enable
0: disable
1: enable

SW control sniffer flow:
(1) rg_rx_sniffer_en=1
(2) rg_rx_en=1, start to receiver data
(3) until SW receiver finish, set rg_rx_sniffer_en=0 to end PKT 
     and HW auto-clear rg_rx_en=0
*/
#define HAC_DET_CTRL__RG_RX_SNIFFER_EN_POS 24
#define HAC_DET_CTRL__RG_RX_SNIFFER_EN_MASK 0x01000000

/** Field rg_rx_sniffer_sel
PHY RX sniffer select
0: sniffer source data at Sample_n_Hold output, format <1,2,7>
1: sniffer source data at Sample_n_Hold input, format <1,2,7>
*/
#define HAC_DET_CTRL__RG_RX_SNIFFER_SEL_POS 25
#define HAC_DET_CTRL__RG_RX_SNIFFER_SEL_MASK 0x02000000

/** Field rg_rx_sniffer_sc
PHY RX sniffer scaling source data, then output sniffer data format <1,1,6>
0: sniffer source data <1,2,7> / 2, then output <1,0,7>
1: sniffer source data <1,2,> / 4, then output <1,0,7>, for 2(G)FSK
2: sniffer source data <1,2,7> / 8, then output <1,0,7>, for 4(G)FSK
3: sniffer source data <1,2,7> / 16, then output <1,0,7>
*/
#define HAC_DET_CTRL__RG_RX_SNIFFER_SC_POS 26
#define HAC_DET_CTRL__RG_RX_SNIFFER_SC_MASK 0x0C000000

/** Field rg_rx_sniffer_ctrl
PHY RX sniffer control, start to send sniffer data to RX MAC
0: from rx_en
1: from Preamble hit
2: from SFD hit (default)
3: from mc_ind hit
4: from (dm_ind | wdc_ind) hit
*/
#define HAC_DET_CTRL__RG_RX_SNIFFER_CTRL_POS 28
#define HAC_DET_CTRL__RG_RX_SNIFFER_CTRL_MASK 0x70000000

/*****************************************************************************/

/** Reg rx_deframer_ctrl
RX Deframer Control Register
*/
#define PHY_CSR__RX_DEFRAMER_CTRL CSR_ACCESS(PHY_CSR_BASE + 0x00000114)

/** Field rg_rx_hw_dw_en
PHY RX HW automatic-latch PHR DW bit (just support FEC OFF)
0: disable, SW control Data-Whitening by rg_pn9_en
1: enable, HW automatic-latch PHR DW bit (just support FEC OFF)
*/
#define RX_DEFRAMER_CTRL__RG_RX_HW_DW_EN_POS 0
#define RX_DEFRAMER_CTRL__RG_RX_HW_DW_EN_MASK 0x00000001

/** Field ro_rx_dw_value
PHY RX final Data-Whitening value to control HW
If rg_rx_hw_dw_en=1, the HW latch-DW is active on this Packet (i.e. During rg_rx_en=1).
If rg_rx_hw_dw_en=0 or rg_rx_en=0, the value is from rg_pn9_en
*/
#define RX_DEFRAMER_CTRL__RO_RX_DW_VALUE_POS 1
#define RX_DEFRAMER_CTRL__RO_RX_DW_VALUE_MASK 0x00000002

/** Field rg_rx_phr_bch_nofix
If rg_phr_ec_sel set 0 (BCH code), HW will fix PHR of Mode Switch with BCH checksum, you can set this RG to HIGH for disable auto-fixing PHR.
*/
#define RX_DEFRAMER_CTRL__RG_RX_PHR_BCH_NOFIX_POS 4
#define RX_DEFRAMER_CTRL__RG_RX_PHR_BCH_NOFIX_MASK 0x00000010

/** Field rg_rx_psdu_len_man
RX PSDU length manual setting:
0: normal
1: use manual setting from "rg_rx_psdu_len_man_val"
*/
#define RX_DEFRAMER_CTRL__RG_RX_PSDU_LEN_MAN_POS 8
#define RX_DEFRAMER_CTRL__RG_RX_PSDU_LEN_MAN_MASK 0x00000100

/** Field rg_rx_psdu_len_limit
RX PSDU length limit for IEEE 802.15.4g standard:
0: normal
1: if PHR length of received packet > "rg_rx_psdu_len_man_val", then limit PSDU length with "rg_rx_psdu_len_man_val"
*/
#define RX_DEFRAMER_CTRL__RG_RX_PSDU_LEN_LIMIT_POS 9
#define RX_DEFRAMER_CTRL__RG_RX_PSDU_LEN_LIMIT_MASK 0x00000200

/** Field rg_rx_psdu_len_man_val
RX PSDU length manual setting
*/
#define RX_DEFRAMER_CTRL__RG_RX_PSDU_LEN_MAN_VAL_POS 12
#define RX_DEFRAMER_CTRL__RG_RX_PSDU_LEN_MAN_VAL_MASK 0x007FF000

/** Field rg_rx_phr_dout_rdy
It's tie HIGH if RX deframer received PHY done, HW will automatically clear next start of packet. 
This register is write 1 clear (W1C) for itself, ro_rx_phr_ec_err, ro_rx_phr_dout, and rg_vtdec_pkt_len.
*/
#define RX_DEFRAMER_CTRL__RG_RX_PHR_DOUT_RDY_POS 24
#define RX_DEFRAMER_CTRL__RG_RX_PHR_DOUT_RDY_MASK 0x01000000

/** Field rg_psdu_start_flag
RX PSDU start flag (HIGH during PSDU data)
This register is write 1 clear (W1C) to force received packet end. 
It will send the last PSDU  data to RX MAC again.
*/
#define RX_DEFRAMER_CTRL__RG_PSDU_START_FLAG_POS 25
#define RX_DEFRAMER_CTRL__RG_PSDU_START_FLAG_MASK 0x02000000

/** Field ro_rx_phr_ec_err
It's tie HIGH if BCH or CRC check error, HW will update every packet. 
(This register can be clear by writing rg_rx_phr_dout_rdy=1)
*/
#define RX_DEFRAMER_CTRL__RO_RX_PHR_EC_ERR_POS 26
#define RX_DEFRAMER_CTRL__RO_RX_PHR_EC_ERR_MASK 0x04000000

/*****************************************************************************/

/** Reg rx_deframer_phr_data
RX PHR Data Register
*/
#define PHY_CSR__RX_DEFRAMER_PHR_DATA CSR_ACCESS(PHY_CSR_BASE + 0x00000118)

/** Field ro_rx_phr_dout
This register hold PHR data after receiving a packet, HW will update every packet. 
If BCH code is enabled, and ro_rx_phr_dout[31:17] is fixed by BCH checksum, you can set rg_rx_phr_bch_nofix = 1 to get original received PHR.
(This register can be clear by writing rg_rx_phr_dout_rdy=1)
*/
#define RX_DEFRAMER_PHR_DATA__RO_RX_PHR_DOUT_POS 0
#define RX_DEFRAMER_PHR_DATA__RO_RX_PHR_DOUT_MASK 0xFFFFFFFF

/*****************************************************************************/

/** Reg rx_cic1_dout_max
RX CIC1 output max value
*/
#define PHY_CSR__RX_CIC1_DOUT_MAX CSR_ACCESS(PHY_CSR_BASE + 0x0000011C)

/** Field rx_cic1_dout_max
This register will hold max value ever happened. Format is <1,2,12> in 2's complement format. This register is write 1 clear (W1C).
*/
#define RX_CIC1_DOUT_MAX__RX_CIC1_DOUT_MAX_POS 0
#define RX_CIC1_DOUT_MAX__RX_CIC1_DOUT_MAX_MASK 0x0000FFFF

/*****************************************************************************/

/** Reg rx_cic2_dout_max
RX CIC2 output max value
*/
#define PHY_CSR__RX_CIC2_DOUT_MAX CSR_ACCESS(PHY_CSR_BASE + 0x00000120)

/** Field rx_cic2_dout_max
This register will hold max value ever happened. Format is <1,2,12> in 2's complement format. This register is write 1 clear (W1C).
*/
#define RX_CIC2_DOUT_MAX__RX_CIC2_DOUT_MAX_POS 0
#define RX_CIC2_DOUT_MAX__RX_CIC2_DOUT_MAX_MASK 0x0000FFFF

/*****************************************************************************/

/** Reg rx_comp_dout_max
RX compensation filter output max value
*/
#define PHY_CSR__RX_COMP_DOUT_MAX CSR_ACCESS(PHY_CSR_BASE + 0x00000124)

/** Field rx_comp_dout_max
This register will hold max value ever happened. Format is <1,2,15> in 2's complement format. This register is write 1 clear (W1C).
*/
#define RX_COMP_DOUT_MAX__RX_COMP_DOUT_MAX_POS 0
#define RX_COMP_DOUT_MAX__RX_COMP_DOUT_MAX_MASK 0x0003FFFF

/*****************************************************************************/

/** Reg rx_decim_dout_max
RX decimation filter output max value
*/
#define PHY_CSR__RX_DECIM_DOUT_MAX CSR_ACCESS(PHY_CSR_BASE + 0x00000128)

/** Field rx_decim_dout_max
This register will hold max value ever happened. Format is <1,2,15> in 2's complement format. This register is write 1 clear (W1C).
*/
#define RX_DECIM_DOUT_MAX__RX_DECIM_DOUT_MAX_POS 0
#define RX_DECIM_DOUT_MAX__RX_DECIM_DOUT_MAX_MASK 0x0003FFFF

/*****************************************************************************/

/** Reg filter_status
Filter operation status
*/
#define PHY_CSR__FILTER_STATUS CSR_ACCESS(PHY_CSR_BASE + 0x0000012C)

/** Field rx_predecim_fout_sat
This register records Pre-decimation Filter output saturation event.
This register is write 1 clear (W1C).
*/
#define FILTER_STATUS__RX_PREDECIM_FOUT_SAT_POS 0
#define FILTER_STATUS__RX_PREDECIM_FOUT_SAT_MASK 0x00000001

/** Field rx_comp_fir_add_sat
This register records Compensation Filter internal adder saturation event.
This register is write 1 clear (W1C).
*/
#define FILTER_STATUS__RX_COMP_FIR_ADD_SAT_POS 1
#define FILTER_STATUS__RX_COMP_FIR_ADD_SAT_MASK 0x00000002

/** Field rx_comp_fir_out_sat
This register records Compensation Filter output truncation saturation event.
This register is write 1 clear (W1C).
*/
#define FILTER_STATUS__RX_COMP_FIR_OUT_SAT_POS 2
#define FILTER_STATUS__RX_COMP_FIR_OUT_SAT_MASK 0x00000004

/** Field rx_decim_fir_add_sat
This register records Decimation Filter internal adder saturation event.
This register is write 1 clear (W1C).
*/
#define FILTER_STATUS__RX_DECIM_FIR_ADD_SAT_POS 3
#define FILTER_STATUS__RX_DECIM_FIR_ADD_SAT_MASK 0x00000008

/** Field rx_decim_fir_out_sat
This register records Decimation Filter output truncation saturation event.
This register is write 1 clear (W1C).
*/
#define FILTER_STATUS__RX_DECIM_FIR_OUT_SAT_POS 4
#define FILTER_STATUS__RX_DECIM_FIR_OUT_SAT_MASK 0x00000010

/** Field rx_iqc_add_sat_flag
This register records IQC internal adder saturation event after sfd_detected.
This register is write 1 clear (W1C).
*/
#define FILTER_STATUS__RX_IQC_ADD_SAT_FLAG_POS 5
#define FILTER_STATUS__RX_IQC_ADD_SAT_FLAG_MASK 0x00000020

/** Field rx_dcb_add_sat_flag
This register records DCB internal adder saturation event after sfd_detected.
This register is write 1 clear (W1C).
*/
#define FILTER_STATUS__RX_DCB_ADD_SAT_FLAG_POS 6
#define FILTER_STATUS__RX_DCB_ADD_SAT_FLAG_MASK 0x00000040

/** Field rx_c2p_cordic_add_sat_flag
This register records C2P CORDIC internal adder saturation event after sfd_detected.
This register is write 1 clear (W1C).
*/
#define FILTER_STATUS__RX_C2P_CORDIC_ADD_SAT_FLAG_POS 7
#define FILTER_STATUS__RX_C2P_CORDIC_ADD_SAT_FLAG_MASK 0x00000080

/*****************************************************************************/

/** Reg rx_status
RX detection status
*/
#define PHY_CSR__RX_STATUS CSR_ACCESS(PHY_CSR_BASE + 0x00000130)

/** Field pmb_detected_flag
This register records Preamble detected event.
This register is write 1 clear (W1C).
*/
#define RX_STATUS__PMB_DETECTED_FLAG_POS 0
#define RX_STATUS__PMB_DETECTED_FLAG_MASK 0x00000001

/** Field sfd_detected_flag
This register records SFD detected event.
This register is write 1 clear (W1C).
*/
#define RX_STATUS__SFD_DETECTED_FLAG_POS 1
#define RX_STATUS__SFD_DETECTED_FLAG_MASK 0x00000002

/** Field hac_detected_flag
This register records HAC code detected event.
This register is write 1 clear (W1C).
*/
#define RX_STATUS__HAC_DETECTED_FLAG_POS 2
#define RX_STATUS__HAC_DETECTED_FLAG_MASK 0x00000004

/** Field rssi_over_flag
This flag indicates rssi_lvl is larger than RSSI threshold (rg_rssi_listen_th_sel) for a stable count (rg_rssi_listen_cnfm_cnt)
*/
#define RX_STATUS__RSSI_OVER_FLAG_POS 3
#define RX_STATUS__RSSI_OVER_FLAG_MASK 0x00000008

/** Field sfd_type
This register records SFD type.
sfd_type[0]=1 indicates non-FEC type SFD is matched.
sfd_type[1]=1 indicates FEC type SFD is matched.
*/
#define RX_STATUS__SFD_TYPE_POS 4
#define RX_STATUS__SFD_TYPE_MASK 0x00000030

/** Field fe_agc_lock
RF+IF AGC lock indication.
*/
#define RX_STATUS__FE_AGC_LOCK_POS 8
#define RX_STATUS__FE_AGC_LOCK_MASK 0x00000100

/** Field dagc_lock
Digital AGC lock indication.
*/
#define RX_STATUS__DAGC_LOCK_POS 9
#define RX_STATUS__DAGC_LOCK_MASK 0x00000200

/** Field mfagc_lock
Match Filter output AGC lock indication.
*/
#define RX_STATUS__MFAGC_LOCK_POS 10
#define RX_STATUS__MFAGC_LOCK_MASK 0x00000400

/** Field time_rcvy_lock
Timing recovery lock indication.
*/
#define RX_STATUS__TIME_RCVY_LOCK_POS 11
#define RX_STATUS__TIME_RCVY_LOCK_MASK 0x00000800

/** Field freq_rcvy_lock
RFAGC (LNA gain) lock indication. (B1 ECO)
*/
#define RX_STATUS__FREQ_RCVY_LOCK_POS 12
#define RX_STATUS__FREQ_RCVY_LOCK_MASK 0x00001000

/** Field mc_ind
RX Manchester code indication.
*/
#define RX_STATUS__MC_IND_POS 13
#define RX_STATUS__MC_IND_MASK 0x00002000

/** Field vt_done
Viterbi Decoding done indication flag.
*/
#define RX_STATUS__VT_DONE_POS 14
#define RX_STATUS__VT_DONE_MASK 0x00004000

/** Field wdc_type
PHY RX HAC Wake-Up interrupt detected type:
bit0: Broadcast 
bit1: Group 
bit2: Individual 
*/
#define RX_STATUS__WDC_TYPE_POS 16
#define RX_STATUS__WDC_TYPE_MASK 0x00070000

/** Field rx_rssi_ib_over_flag

*/
#define RX_STATUS__RX_RSSI_IB_OVER_FLAG_POS 20
#define RX_STATUS__RX_RSSI_IB_OVER_FLAG_MASK 0x00100000

/** Field rx_rssi_dif_over_flag

*/
#define RX_STATUS__RX_RSSI_DIF_OVER_FLAG_POS 21
#define RX_STATUS__RX_RSSI_DIF_OVER_FLAG_MASK 0x00200000

/** Field rx_rssi_dif_less_flag

*/
#define RX_STATUS__RX_RSSI_DIF_LESS_FLAG_POS 22
#define RX_STATUS__RX_RSSI_DIF_LESS_FLAG_MASK 0x00400000

/*****************************************************************************/

/** Reg rx_rssi_data
RX RSSI Data Register
*/
#define PHY_CSR__RX_RSSI_DATA CSR_ACCESS(PHY_CSR_BASE + 0x00000134)

/** Field rx_sig_lvl
RX signal level
*/
#define RX_RSSI_DATA__RX_SIG_LVL_POS 0
#define RX_RSSI_DATA__RX_SIG_LVL_MASK 0x00007FFF

/** Field rx_rssi_lvl
RX RSSI level
*/
#define RX_RSSI_DATA__RX_RSSI_LVL_POS 16
#define RX_RSSI_DATA__RX_RSSI_LVL_MASK 0x7FFF0000

/*****************************************************************************/

/** Reg phy_rx_iqc_coef_a_b
RX IQC coefficient A and B
*/
#define PHY_CSR__PHY_RX_IQC_COEF_A_B CSR_ACCESS(PHY_CSR_BASE + 0x00000138)

/** Field rx_iqc_coef_a
IQC coefficient A
*/
#define PHY_RX_IQC_COEF_A_B__RX_IQC_COEF_A_POS 0
#define PHY_RX_IQC_COEF_A_B__RX_IQC_COEF_A_MASK 0x00007FFF

/** Field rx_iqc_coef_b
IQC coefficient B
*/
#define PHY_RX_IQC_COEF_A_B__RX_IQC_COEF_B_POS 16
#define PHY_RX_IQC_COEF_A_B__RX_IQC_COEF_B_MASK 0x7FFF0000

/*****************************************************************************/

/** Reg phy_rx_iqc_coef_c
RX IQC Coefficient C
*/
#define PHY_CSR__PHY_RX_IQC_COEF_C CSR_ACCESS(PHY_CSR_BASE + 0x0000013C)

/** Field rx_iqc_coef_c
IQC coefficient C
*/
#define PHY_RX_IQC_COEF_C__RX_IQC_COEF_C_POS 0
#define PHY_RX_IQC_COEF_C__RX_IQC_COEF_C_MASK 0x00007FFF

/*****************************************************************************/

/** Reg phy_rx_dcb_accum_i
RX DCB accumulator I-Channel
*/
#define PHY_CSR__PHY_RX_DCB_ACCUM_I CSR_ACCESS(PHY_CSR_BASE + 0x00000140)

/** Field rx_dcb_accum_i
DCB accumulator register (I-Channel)
*/
#define PHY_RX_DCB_ACCUM_I__RX_DCB_ACCUM_I_POS 0
#define PHY_RX_DCB_ACCUM_I__RX_DCB_ACCUM_I_MASK 0x001FFFFF

/*****************************************************************************/

/** Reg phy_rx_dcb_accum_q
RX DCB accumulator Q-Channel
*/
#define PHY_CSR__PHY_RX_DCB_ACCUM_Q CSR_ACCESS(PHY_CSR_BASE + 0x00000144)

/** Field rx_dcb_accum_q
DCB accumulator register (Q-Channel)
*/
#define PHY_RX_DCB_ACCUM_Q__RX_DCB_ACCUM_Q_POS 0
#define PHY_RX_DCB_ACCUM_Q__RX_DCB_ACCUM_Q_MASK 0x001FFFFF

/*****************************************************************************/

/** Reg phy_irq_status
PHY interrupt status
*/
#define PHY_CSR__PHY_IRQ_STATUS CSR_ACCESS(PHY_CSR_BASE + 0x00000148)

/** Field rg_phy_tx_irq
PHR TX packet finish interrupt
This register is write 1 clear (W1C).
*/
#define PHY_IRQ_STATUS__RG_PHY_TX_IRQ_POS 0
#define PHY_IRQ_STATUS__RG_PHY_TX_IRQ_MASK 0x00000001

/** Field rg_phy_rx_pkt_irq
PHR RX packet interrupt tie HIGH when received packet end
This register is write 1 clear (W1C).
*/
#define PHY_IRQ_STATUS__RG_PHY_RX_PKT_IRQ_POS 1
#define PHY_IRQ_STATUS__RG_PHY_RX_PKT_IRQ_MASK 0x00000002

/** Field rg_phy_rx_ms_irq
PHR RX Mode Switch interrupt tie HIGH when received Mode Switch PHR, then wait rg_rx_phr_dout_rdy to HIGH, and read related PHR report RG.
This register is write 1 clear (W1C).
*/
#define PHY_IRQ_STATUS__RG_PHY_RX_MS_IRQ_POS 2
#define PHY_IRQ_STATUS__RG_PHY_RX_MS_IRQ_MASK 0x00000004

/** Field rg_phy_rx_pmb_irq
PHR RX Preamble detected interrupt
This register is write 1 clear (W1C).
*/
#define PHY_IRQ_STATUS__RG_PHY_RX_PMB_IRQ_POS 3
#define PHY_IRQ_STATUS__RG_PHY_RX_PMB_IRQ_MASK 0x00000008

/** Field rg_phy_rx_sfd_irq
PHR RX SFD detected interrupt
This register is write 1 clear (W1C).
*/
#define PHY_IRQ_STATUS__RG_PHY_RX_SFD_IRQ_POS 4
#define PHY_IRQ_STATUS__RG_PHY_RX_SFD_IRQ_MASK 0x00000010

/** Field rg_phy_rx_mc_irq
PHR RX Manchester code detected interrupt
This register is write 1 clear (W1C).
*/
#define PHY_IRQ_STATUS__RG_PHY_RX_MC_IRQ_POS 5
#define PHY_IRQ_STATUS__RG_PHY_RX_MC_IRQ_MASK 0x00000020

/** Field rg_phy_rx_hac_irq
PHR RX HAC code detected interrupt
(1) rg_dm_en = 0 --> HAC WDC interrupt, read rg_phy_rx_wdc_type
(2) rg_dm_en = 1 --> HAC DM interrupt
This register is write 1 clear (W1C), and also clear rg_phy_rx_wdc_type.
*/
#define PHY_IRQ_STATUS__RG_PHY_RX_HAC_IRQ_POS 6
#define PHY_IRQ_STATUS__RG_PHY_RX_HAC_IRQ_MASK 0x00000040

/** Field rg_phy_tx_en_irq
PHY TX enable to transmit data interrupt
This register is write 1 clear (W1C).
*/
#define PHY_IRQ_STATUS__RG_PHY_TX_EN_IRQ_POS 7
#define PHY_IRQ_STATUS__RG_PHY_TX_EN_IRQ_MASK 0x00000080

/** Field rg_phy_rx_en_irq
PHY RX enable to receieve interrupt
This register is write 1 clear (W1C).
*/
#define PHY_IRQ_STATUS__RG_PHY_RX_EN_IRQ_POS 8
#define PHY_IRQ_STATUS__RG_PHY_RX_EN_IRQ_MASK 0x00000100

/** Field rg_phy_timecnt1_irq
PHY time cnt 1 interrupt
This register is write 1 clear (W1C).
*/
#define PHY_IRQ_STATUS__RG_PHY_TIMECNT1_IRQ_POS 9
#define PHY_IRQ_STATUS__RG_PHY_TIMECNT1_IRQ_MASK 0x00000200

/** Field rg_phy_timecnt2_irq
PHY time cnt 2 interrupt
This register is write 1 clear (W1C).
*/
#define PHY_IRQ_STATUS__RG_PHY_TIMECNT2_IRQ_POS 10
#define PHY_IRQ_STATUS__RG_PHY_TIMECNT2_IRQ_MASK 0x00000400

/** Field rg_phy_rx_wdc_chk_irq
PHY RX WDC check detected interrupt
This register is write 1 clear (W1C).

(B1 ECO)
If hac_detected_flag = 0, the interrupt for RFAGC lock 
If hac_detected_flag = 1, the interrupt for  PHY RX WDC check
*/
#define PHY_IRQ_STATUS__RG_PHY_RX_WDC_CHK_IRQ_POS 11
#define PHY_IRQ_STATUS__RG_PHY_RX_WDC_CHK_IRQ_MASK 0x00000800

/** Field rg_phy_rx_phr_irq
PHY RX PHR detected interrupt
This register is write 1 clear (W1C).
*/
#define PHY_IRQ_STATUS__RG_PHY_RX_PHR_IRQ_POS 12
#define PHY_IRQ_STATUS__RG_PHY_RX_PHR_IRQ_MASK 0x00001000

/** Field rg_phy_rx_rssi_irq
PHY RX signal RSSI over threshold interrupt
 - If RSSI absolute dB value "rx_rssi_db_val" is less threshold(rg_rssi_ib_lsn_thr) continuously confirm count (rg_rssi_ib_lsn_cnfm_cnt) , it will report to "rx_rssi_ib_over_flag" and "rg_phy_rx_rssi_irq"
 - This register is write 1 clear (W1C).
*/
#define PHY_IRQ_STATUS__RG_PHY_RX_RSSI_IRQ_POS 13
#define PHY_IRQ_STATUS__RG_PHY_RX_RSSI_IRQ_MASK 0x00002000

/** Field rg_phy_rx_rssi_over_irq
PHY RX signal RSSI over RSSI_pmb_mc_hit threshold interrupt
  - The IRQ for packet power increase (Packet over Packet)
  - rx_rssi_diff = abs(RSSI_diff_thr) - abs(RSSI_now)
  - rx_rssi_diff > rg_rssi_over_thr and continuously confirm count (rg_rssi_dif_over_cnfm) , it will report to "rg_phy_rx_rssi_over_flag" and "rg_phy_rx_rssi_over_irq"
 - This register is write 1 clear (W1C).
*/
#define PHY_IRQ_STATUS__RG_PHY_RX_RSSI_OVER_IRQ_POS 14
#define PHY_IRQ_STATUS__RG_PHY_RX_RSSI_OVER_IRQ_MASK 0x00004000

/** Field rg_phy_rx_rssi_less_irq
PHY RX signal RSSI less RSSI_pmb_mc_hit threshold interrupt
  - The IRQ for packet power drop (Packet weak signal, e.g. Error long length PHR)
  - rx_rssi_diff = abs(RSSI_diff_thr) - abs(RSSI_now)
  - rx_rssi_diff < rg_rssi_less_thr and continuously confirm count (rg_rssi_dif_less_cnfm) , it will report to "rg_phy_rx_rssi_less_flag" and "rg_phy_rx_rssi_less_irq"
 - This register is write 1 clear (W1C).
*/
#define PHY_IRQ_STATUS__RG_PHY_RX_RSSI_LESS_IRQ_POS 15
#define PHY_IRQ_STATUS__RG_PHY_RX_RSSI_LESS_IRQ_MASK 0x00008000

/** Field rg_phy_tx_irq_dis
PHY TX interrupt control
0: enable
1: disable
*/
#define PHY_IRQ_STATUS__RG_PHY_TX_IRQ_DIS_POS 16
#define PHY_IRQ_STATUS__RG_PHY_TX_IRQ_DIS_MASK 0x00010000

/** Field rg_phy_rx_pkt_irq_dis
PHY RX Deframer normal packet end interrupt control
0: enable, note: HW auto-enable if rg_phy_test_mode = 1
1: disable
*/
#define PHY_IRQ_STATUS__RG_PHY_RX_PKT_IRQ_DIS_POS 17
#define PHY_IRQ_STATUS__RG_PHY_RX_PKT_IRQ_DIS_MASK 0x00020000

/** Field rg_phy_rx_ms_irq_dis
PHY RX Deframer detect mode-switch packet interrupt control
0: enable
1: disable
*/
#define PHY_IRQ_STATUS__RG_PHY_RX_MS_IRQ_DIS_POS 18
#define PHY_IRQ_STATUS__RG_PHY_RX_MS_IRQ_DIS_MASK 0x00040000

/** Field rg_phy_rx_pmb_irq_dis
PHY RX Preamble detected interrupt control
0: enable
1: disable
*/
#define PHY_IRQ_STATUS__RG_PHY_RX_PMB_IRQ_DIS_POS 19
#define PHY_IRQ_STATUS__RG_PHY_RX_PMB_IRQ_DIS_MASK 0x00080000

/** Field rg_phy_rx_sfd_irq_dis
PHY RX SFD detected interrupt control
0: enable
1: disable
*/
#define PHY_IRQ_STATUS__RG_PHY_RX_SFD_IRQ_DIS_POS 20
#define PHY_IRQ_STATUS__RG_PHY_RX_SFD_IRQ_DIS_MASK 0x00100000

/** Field rg_phy_rx_mc_irq_dis
PHY RX Manchester code detected interrupt control
0: enable
1: disable
*/
#define PHY_IRQ_STATUS__RG_PHY_RX_MC_IRQ_DIS_POS 21
#define PHY_IRQ_STATUS__RG_PHY_RX_MC_IRQ_DIS_MASK 0x00200000

/** Field rg_phy_rx_hac_irq_dis
PHY RX HAC code detected interrupt control
0: enable
1: disable
*/
#define PHY_IRQ_STATUS__RG_PHY_RX_HAC_IRQ_DIS_POS 22
#define PHY_IRQ_STATUS__RG_PHY_RX_HAC_IRQ_DIS_MASK 0x00400000

/** Field rg_phy_tx_en_irq_dis
PHY TX enable interrupt control
0: enable
1: disable
*/
#define PHY_IRQ_STATUS__RG_PHY_TX_EN_IRQ_DIS_POS 23
#define PHY_IRQ_STATUS__RG_PHY_TX_EN_IRQ_DIS_MASK 0x00800000

/** Field rg_phy_rx_en_irq_dis
PHY RX enable interrupt control
0: enable
1: disable
*/
#define PHY_IRQ_STATUS__RG_PHY_RX_EN_IRQ_DIS_POS 24
#define PHY_IRQ_STATUS__RG_PHY_RX_EN_IRQ_DIS_MASK 0x01000000

/** Field rg_phy_timecnt1_irq_dis
PHY time cnt 1 interrupt control
0: enable
1: disable
This register is write 1 clear (W1C).
*/
#define PHY_IRQ_STATUS__RG_PHY_TIMECNT1_IRQ_DIS_POS 25
#define PHY_IRQ_STATUS__RG_PHY_TIMECNT1_IRQ_DIS_MASK 0x02000000

/** Field rg_phy_timecnt2_irq_dis
PHY time cnt 2 interrupt control
0: enable
1: disable
This register is write 1 clear (W1C).
*/
#define PHY_IRQ_STATUS__RG_PHY_TIMECNT2_IRQ_DIS_POS 26
#define PHY_IRQ_STATUS__RG_PHY_TIMECNT2_IRQ_DIS_MASK 0x04000000

/** Field rg_phy_rx_wdc_chk_irq_dis
PHY RX HAC detected interrupt control
0: enable
1: disable
*/
#define PHY_IRQ_STATUS__RG_PHY_RX_WDC_CHK_IRQ_DIS_POS 27
#define PHY_IRQ_STATUS__RG_PHY_RX_WDC_CHK_IRQ_DIS_MASK 0x08000000

/** Field rg_phy_rx_phr_irq_dis
PHY RX PHR detected interrupt control
0: enable
1: disable
*/
#define PHY_IRQ_STATUS__RG_PHY_RX_PHR_IRQ_DIS_POS 28
#define PHY_IRQ_STATUS__RG_PHY_RX_PHR_IRQ_DIS_MASK 0x10000000

/** Field rg_phy_rx_rssi_irq_dis
PHY RX RSSI over threshold interrupt control
0: enable
1: disable
*/
#define PHY_IRQ_STATUS__RG_PHY_RX_RSSI_IRQ_DIS_POS 29
#define PHY_IRQ_STATUS__RG_PHY_RX_RSSI_IRQ_DIS_MASK 0x20000000

/** Field rg_phy_rx_rssi_over_dis
PHY RX signal RSSI over RSSI_pmb_mc_hit threshold interrupt control
0: enable
1: disable
*/
#define PHY_IRQ_STATUS__RG_PHY_RX_RSSI_OVER_DIS_POS 30
#define PHY_IRQ_STATUS__RG_PHY_RX_RSSI_OVER_DIS_MASK 0x40000000

/** Field rg_phy_rx_rssi_less_dis
PHY RX signal RSSI less RSSI_pmb_mc_hit threshold interrupt control
0: enable
1: disable
*/
#define PHY_IRQ_STATUS__RG_PHY_RX_RSSI_LESS_DIS_POS 31
#define PHY_IRQ_STATUS__RG_PHY_RX_RSSI_LESS_DIS_MASK 0x80000000

/*****************************************************************************/

/** Reg rx_agc_gain_status
RX RF/IF/Digital AGC Gain Status
*/
#define PHY_CSR__RX_AGC_GAIN_STATUS CSR_ACCESS(PHY_CSR_BASE + 0x0000014C)

/** Field rf_lna_gain
RF LNA gain read back.
0: 45dB
1: 42dB
     :
12: 9dB
*/
#define RX_AGC_GAIN_STATUS__RF_LNA_GAIN_POS 0
#define RX_AGC_GAIN_STATUS__RF_LNA_GAIN_MASK 0x0000000F

/** Field if_pga_gain
IF PGA gain read back.
0: Gmax (30 or 36dB)
1: Gmax-1 dB
     :
31: Gmax-31 dB
*/
#define RX_AGC_GAIN_STATUS__IF_PGA_GAIN_POS 8
#define RX_AGC_GAIN_STATUS__IF_PGA_GAIN_MASK 0x00001F00

/** Field dagc_gain
Digital AGC gain read back. Its format is <1,9,5> in 2's complement format.
*/
#define RX_AGC_GAIN_STATUS__DAGC_GAIN_POS 16
#define RX_AGC_GAIN_STATUS__DAGC_GAIN_MASK 0x7FFF0000

/*****************************************************************************/

/** Reg timecnt
RX Time Count control
*/
#define PHY_CSR__TIMECNT CSR_ACCESS(PHY_CSR_BASE + 0x00000150)

/** Field rg_rx_timecnt1_tgt
Time counter1 target 
 - count by slicer output ready, i.e. If Manchester Code is chip-rate, else symbol-rate
 - default 70 for Manchester encoding data of 35 symbols
*/
#define TIMECNT__RG_RX_TIMECNT1_TGT_POS 0
#define TIMECNT__RG_RX_TIMECNT1_TGT_MASK 0x000000FF

/** Field rg_rx_timecnt1_start
Time counter1 start from :
0: rx_en
1: dagc_lock
2: rx_rssi_ib_over_flag
3: pmb_ind 
4: sfd_ind
5: mc_ind
6: wdc_ind or dm_ind
7: phy2mac_rx_end
*/
#define TIMECNT__RG_RX_TIMECNT1_START_POS 8
#define TIMECNT__RG_RX_TIMECNT1_START_MASK 0x00000700

/** Field rg_rx_timecnt1_end
Time counter1 report to the rg_phy_timecnt1_irq end-condition
0: if (symbol number of timecnt1 == rg_rx_timecnt1_tgt)
1: if (symbol number of timecnt1 == rg_rx_timecnt1_tgt), and (pmb_ind==0)
2: if (symbol number of timecnt1 == rg_rx_timecnt1_tgt), and (sfd_ind==0)
3: if (symbol number of timecnt1 == rg_rx_timecnt1_tgt), and (mc_ind==0)
*/
#define TIMECNT__RG_RX_TIMECNT1_END_POS 12
#define TIMECNT__RG_RX_TIMECNT1_END_MASK 0x00003000

/** Field rg_rx_timecnt2_tgt
Time counter2 target 
 - count by bit-rate

 If (rg_rx_timecnt2_end==3)
 - 4-bit, rg_rx_timecnt2_tgt[17:14] x2 for polynomial check start-symbol number,
   Default 4 for 8 symbols
 - 6-bit, rg_rx_timecnt2_tgt[23:18] x2 for  polynomial check end-symbol number,
   Default 16 for 32 symbols
*/
#define TIMECNT__RG_RX_TIMECNT2_TGT_POS 14
#define TIMECNT__RG_RX_TIMECNT2_TGT_MASK 0x00FFC000

/** Field rg_rx_timecnt2_start
Time counter1 start from :
0: rx_en
1: dagc_lock
2: rx_rssi_ib_over_flag
3: pmb_ind 
4: sfd_ind
5: mc_ind
6: wdc_ind or dm_ind
7: phy2mac_rx_end
*/
#define TIMECNT__RG_RX_TIMECNT2_START_POS 24
#define TIMECNT__RG_RX_TIMECNT2_START_MASK 0x07000000

/** Field rg_rx_timecnt2_end
Time counter2 report to the rg_phy_timecnt1_irq end-condition
0: if (symbol number of timecnt2 == rg_rx_timecnt2_tgt)
1: if (symbol number of timecnt2 == rg_rx_timecnt2_tgt), and (pmb_ind==0)
2: if (symbol number of timecnt2 == rg_rx_timecnt2_tgt), and (sfd_ind==0)
3: if (mc_ind==1), and (HAC polynomial check Error) &&
       and (symbol number of timecnt2 > rg_rx_timecnt2_tgt[17:14] x2, then reset timecnt2), and (symbol number of timecnt2 < rg_rx_timecnt2_tgt[23:18] x2)
*/
#define TIMECNT__RG_RX_TIMECNT2_END_POS 28
#define TIMECNT__RG_RX_TIMECNT2_END_MASK 0x30000000

/** Field rg_rx_timecnt1_auto_clr
HW auto clear rx_en if rg_phy_timecnt1_irq happen
0: disable, you can write-1-clear rg_psdu_start_flag to force received packet end
1: enable for HAC(WUC) use
*/
#define TIMECNT__RG_RX_TIMECNT1_AUTO_CLR_POS 30
#define TIMECNT__RG_RX_TIMECNT1_AUTO_CLR_MASK 0x40000000

/** Field rg_rx_timecnt2_auto_clr
HW auto clear rx_en if rg_phy_timecnt2_irq happen
0: disable, you can write-1-clear rg_psdu_start_flag to force received packet end
1: enable for HAC(WUC) use
*/
#define TIMECNT__RG_RX_TIMECNT2_AUTO_CLR_POS 31
#define TIMECNT__RG_RX_TIMECNT2_AUTO_CLR_MASK 0x80000000

/*****************************************************************************/

/** Reg phy_noret_spare
Turbo CSS Control
*/
#define PHY_CSR__PHY_NORET_SPARE CSR_ACCESS(PHY_CSR_BASE + 0x00000154)

/** Field rg_phy_noret_spare_a
PHY spare RG
*/
#define PHY_NORET_SPARE__RG_PHY_NORET_SPARE_A_POS 0
#define PHY_NORET_SPARE__RG_PHY_NORET_SPARE_A_MASK 0x0000FFFF

/** Field rg_phy_noret_spare_b
PHY spare RG
*/
#define PHY_NORET_SPARE__RG_PHY_NORET_SPARE_B_POS 16
#define PHY_NORET_SPARE__RG_PHY_NORET_SPARE_B_MASK 0xFFFF0000

/*****************************************************************************/

/** Reg channel_freq_max
Channel Frequency max 
*/
#define PHY_CSR__CHANNEL_FREQ_MAX CSR_ACCESS(PHY_CSR_BASE + 0x00000158)

/** Field rg_chan_freq_max
Channel Frequency max value, unsigned format (0, 6, 20)
 - It logs the max value of rg_channel_band[25:0].
 - This register is write 1 clear (W1C).
e.g. 2FSK, Frequency deviation = 250K, rg_channel_band = 868M = 0x1B2_0000
 - rg_chan_freq_max = (868M + 250K) / 32M * 2^20 = 0x1B2_2000
*/
#define CHANNEL_FREQ_MAX__RG_CHAN_FREQ_MAX_POS 0
#define CHANNEL_FREQ_MAX__RG_CHAN_FREQ_MAX_MASK 0x03FFFFFF

/** Field rg_chan_freq_max_en
Channel Frequency max value control
0: (default) disabled to log rg_chan_freq_max (always 0)
1: enable rg_chan_freq_max log
*/
#define CHANNEL_FREQ_MAX__RG_CHAN_FREQ_MAX_EN_POS 28
#define CHANNEL_FREQ_MAX__RG_CHAN_FREQ_MAX_EN_MASK 0x10000000

/*****************************************************************************/

/** Reg mf_out_max_pmb_phase
RX MF output max at Preamble phase
*/
#define PHY_CSR__MF_OUT_MAX_PMB_PHASE CSR_ACCESS(PHY_CSR_BASE + 0x0000015C)

/** Field mf_out_max_pmb_phase
This register will hold max value ever happened. Format is <1,2,8> in 2's complement format. 
This register will be clear at the beginning of rx_en=1.
*/
#define MF_OUT_MAX_PMB_PHASE__MF_OUT_MAX_PMB_PHASE_POS 0
#define MF_OUT_MAX_PMB_PHASE__MF_OUT_MAX_PMB_PHASE_MASK 0x000007FF

/*****************************************************************************/

/** Reg mf_out_max_data_phase
RX MF output max at Data phase
*/
#define PHY_CSR__MF_OUT_MAX_DATA_PHASE CSR_ACCESS(PHY_CSR_BASE + 0x00000160)

/** Field mf_out_max_data_phase
This register will hold max value ever happened. Format is <1,2,8> in 2's complement format. 
This register will be clear at the beginning of rx_en=1.
*/
#define MF_OUT_MAX_DATA_PHASE__MF_OUT_MAX_DATA_PHASE_POS 0
#define MF_OUT_MAX_DATA_PHASE__MF_OUT_MAX_DATA_PHASE_MASK 0x000007FF

/*****************************************************************************/

/** Reg rx_mfagc_gain
RX Match Filter Output AGC Gain log register
*/
#define PHY_CSR__RX_MFAGC_GAIN CSR_ACCESS(PHY_CSR_BASE + 0x00000164)

/** Field mfagc_gain_max_pmb_phase
The max mfagc_gain ever happened in Preamble & SFD phase. Format is <0,2,8>.
This register will be clear at the beginning of rx_en=1.
*/
#define RX_MFAGC_GAIN__MFAGC_GAIN_MAX_PMB_PHASE_POS 0
#define RX_MFAGC_GAIN__MFAGC_GAIN_MAX_PMB_PHASE_MASK 0x000003FF

/** Field mfagc_gain
The mfagc_gain read back. It will be fixed after SFD detected. Format is <0,2,8>.
This register will be clear at the beginning of rx_en=1.
*/
#define RX_MFAGC_GAIN__MFAGC_GAIN_POS 16
#define RX_MFAGC_GAIN__MFAGC_GAIN_MASK 0x03FF0000

/*****************************************************************************/

/** Reg rx_sfd_ctrl
RX SFD control register
*/
#define PHY_CSR__RX_SFD_CTRL CSR_ACCESS(PHY_CSR_BASE + 0x00000168)

/** Field rg_sfd_mode
SFD mode:
0: 4 bits, use rg_sfd_pat0/1[3:0]
1: 8 bits, use rg_sfd_pat0/1[7:0]
2: 12 bits, use rg_sfd_pat0/1[11:0], for 10-bit sync of WMBUS T-mode
3: 16 bits, use rg_sfd_pat0/1[15:0]
4: 20 bits, use {rg_sfd_pat0/1_h16b[3:0], rg_sfd_pat0/1[15:0]}, for 18-bit sync of WMBUS {S,R,T}-mode
5: 24 bits, use {rg_sfd_pat0/1_h16b[7:0], rg_sfd_pat0/1[15:0]}
6: 28 bits, use {rg_sfd_pat0/1_h16b[11:0], rg_sfd_pat0/1[15:0]}, , for 32-bit sync of WMBUS C-mode, 4-bit(0101) use for preamble pattern
7: 32 bits, use {rg_sfd_pat0/1_h16b[15:0], rg_sfd_pat0/1[15:0]}
*/
#define RX_SFD_CTRL__RG_SFD_MODE_POS 0
#define RX_SFD_CTRL__RG_SFD_MODE_MASK 0x00000007

/** Field rg_sfd_chk_pmb_en
SFD indication control:
0: sfd_ind will be asserted only if sfd_pattern is matched.
1: sfd_ind will be asserted if both pmb_ind=1 and sfd_pattern is matched.
*/
#define RX_SFD_CTRL__RG_SFD_CHK_PMB_EN_POS 4
#define RX_SFD_CTRL__RG_SFD_CHK_PMB_EN_MASK 0x00000010

/*****************************************************************************/

/** Reg sfd_pattern_high_16bit
SFD Pattern Register
*/
#define PHY_CSR__SFD_PATTERN_HIGH_16BIT CSR_ACCESS(PHY_CSR_BASE + 0x0000016C)

/** Field rg_sfd_pat0_h16b
RX SFD Pattern0 high-byte (bit[31:16]) for uncoded (PHR+PSDU) frame. It will be used when sfd_mode is 24 or 32 bits mode.

If rg_fec_en=0, PHY TX use the SFD pattern.
*/
#define SFD_PATTERN_HIGH_16BIT__RG_SFD_PAT0_H16B_POS 0
#define SFD_PATTERN_HIGH_16BIT__RG_SFD_PAT0_H16B_MASK 0x0000FFFF

/** Field rg_sfd_pat1_h16b
RX SFD Pattern1 high-byte (bit[31:16]) for coded (PHR+PSDU) frame. It will be used when sfd_mode is 24 or 32 bits mode.

If rg_fec_en=1, PHY TX use the SFD pattern.
*/
#define SFD_PATTERN_HIGH_16BIT__RG_SFD_PAT1_H16B_POS 16
#define SFD_PATTERN_HIGH_16BIT__RG_SFD_PAT1_H16B_MASK 0xFFFF0000

/*****************************************************************************/

/** Reg rx_predecim_dout_max
RX Pre-decimation filter output max value
*/
#define PHY_CSR__RX_PREDECIM_DOUT_MAX CSR_ACCESS(PHY_CSR_BASE + 0x00000170)

/** Field rx_predecim_dout_max
This register will hold max value ever happened. Format is <1,0,12> in 2's complement format. This register is write 1 clear (W1C).
*/
#define RX_PREDECIM_DOUT_MAX__RX_PREDECIM_DOUT_MAX_POS 0
#define RX_PREDECIM_DOUT_MAX__RX_PREDECIM_DOUT_MAX_MASK 0x00007FFF

/*****************************************************************************/

/** Reg fr_adj_out
RX frequency recovery adjustment value after lock
*/
#define PHY_CSR__FR_ADJ_OUT CSR_ACCESS(PHY_CSR_BASE + 0x00000174)

/** Field fr_adj_out_1st_value
This register will hold fr_adj_out first value after frequency recovery lock. Format is <1,0,12> in 2's complement format. 
This register will be clear at the beginning of rx_en=1.
*/
#define FR_ADJ_OUT__FR_ADJ_OUT_1ST_VALUE_POS 0
#define FR_ADJ_OUT__FR_ADJ_OUT_1ST_VALUE_MASK 0x00001FFF

/** Field fr_adj_out_2nd_value
This register will hold fr_adj_out second value after frequency recovery lock. Format is <1,0,12> in 2's complement format. 
This register will be clear at the beginning of rx_en=1.
*/
#define FR_ADJ_OUT__FR_ADJ_OUT_2ND_VALUE_POS 16
#define FR_ADJ_OUT__FR_ADJ_OUT_2ND_VALUE_MASK 0x1FFF0000

/*****************************************************************************/

/** Reg rx_misc_ctrl
RX MISC control register
*/
#define PHY_CSR__RX_MISC_CTRL CSR_ACCESS(PHY_CSR_BASE + 0x0000017C)

/** Field rg_filt_dout_max_log_en
Log register control including rx_predecim_dout_max, rx_cic1_dout_max, rx_cic2_dout_max, rx_comp_dout_max, rx_decim_dout_max
0: disable
1: enable
*/
#define RX_MISC_CTRL__RG_FILT_DOUT_MAX_LOG_EN_POS 1
#define RX_MISC_CTRL__RG_FILT_DOUT_MAX_LOG_EN_MASK 0x00000002

/** Field rg_mf_out_max_log_en
Log register control including mf_out_max_pmb_phase, mf_out_max_data_phase, mfagc_gain_max_pmb_phase, cssig_th_lvl_max_pmb_phase
0: disable
1: enable
*/
#define RX_MISC_CTRL__RG_MF_OUT_MAX_LOG_EN_POS 3
#define RX_MISC_CTRL__RG_MF_OUT_MAX_LOG_EN_MASK 0x00000008

/** Field rg_fr_adj_log_en
Log register control including fr_adj_out_1st_value, fr_adj_out_2nd_value
0: disable
1: enable
*/
#define RX_MISC_CTRL__RG_FR_ADJ_LOG_EN_POS 4
#define RX_MISC_CTRL__RG_FR_ADJ_LOG_EN_MASK 0x00000010

/** Field rg_errpwr_calc_en
Slicer output error power calculation control
0: disable
1: enable
*/
#define RX_MISC_CTRL__RG_ERRPWR_CALC_EN_POS 6
#define RX_MISC_CTRL__RG_ERRPWR_CALC_EN_MASK 0x00000040

/** Field rg_slicer_err_th
Slicer output error threshold to stop error power calculation. It represents 2nd to 4th bit after decimal point. The value in binary format is 0.1xxx. The threshold value can be set as 0.5 ~ 0.9375 in decimal format.
*/
#define RX_MISC_CTRL__RG_SLICER_ERR_TH_POS 16
#define RX_MISC_CTRL__RG_SLICER_ERR_TH_MASK 0x00070000

/** Field rg_errpwr_k_sc
Extra scaling factor of ErrPwr_K after Preamble/SFD detected. (ErrPwr_K = rg_mfagc_k)
0: 1
1: 1/2
2: 1/4
*/
#define RX_MISC_CTRL__RG_ERRPWR_K_SC_POS 20
#define RX_MISC_CTRL__RG_ERRPWR_K_SC_MASK 0x00300000

/** Field rg_tr_cnt_adj_sat_en
Timing recovery internal count adjustment value will be constrained between -1 and +1. This is a new feature in B1.
0: disable
1: enable
*/
#define RX_MISC_CTRL__RG_TR_CNT_ADJ_SAT_EN_POS 24
#define RX_MISC_CTRL__RG_TR_CNT_ADJ_SAT_EN_MASK 0x01000000

/** Field rg_rx_bt05_comp
RX 4GFSK BT=0.5 compensator
0: disable
1: enable, if 4GFSK with BT=0.5
*/
#define RX_MISC_CTRL__RG_RX_BT05_COMP_POS 27
#define RX_MISC_CTRL__RG_RX_BT05_COMP_MASK 0x08000000

/** Field rg_sh_fsk4_threshold
RX 4fsk threshold
*/
#define RX_MISC_CTRL__RG_SH_FSK4_THRESHOLD_POS 28
#define RX_MISC_CTRL__RG_SH_FSK4_THRESHOLD_MASK 0x70000000

/*****************************************************************************/

/** Reg slicer_out_errpwr
Slicer output error power
*/
#define PHY_CSR__SLICER_OUT_ERRPWR CSR_ACCESS(PHY_CSR_BASE + 0x00000180)

/** Field slicer_out_errpwr
This register will record the error power calculated by average of absolute value of slicer input delta error. Format is <0,2,12>
This register will be clear at the beginning of rx_en=1.
*/
#define SLICER_OUT_ERRPWR__SLICER_OUT_ERRPWR_POS 0
#define SLICER_OUT_ERRPWR__SLICER_OUT_ERRPWR_MASK 0x00003FFF

/*****************************************************************************/

/** Reg HAC_WDC_IND_LAT
RX HAC WDC IND Latch
*/
#define PHY_CSR__HAC_WDC_IND_LAT CSR_ACCESS(PHY_CSR_BASE + 0x00000184)

/** Field rg_hac_wdc_ind_lat
Latch data at RX HAC WDC indication
*/
#define HAC_WDC_IND_LAT__RG_HAC_WDC_IND_LAT_POS 0
#define HAC_WDC_IND_LAT__RG_HAC_WDC_IND_LAT_MASK 0xFFFFFFFF

/*****************************************************************************/

/** Reg HAC_WDC_BD_PAT
RX HAC WDC Broadcast check pattern
*/
#define PHY_CSR__HAC_WDC_BD_PAT CSR_ACCESS(PHY_CSR_BASE + 0x00000188)

/** Field rg_hac_wdc_bc_pat
RX HAC WDC Broadcast target pattern (if rg_hac_wdc_chk_en=1)
*/
#define HAC_WDC_BD_PAT__RG_HAC_WDC_BC_PAT_POS 0
#define HAC_WDC_BD_PAT__RG_HAC_WDC_BC_PAT_MASK 0xFFFFFFFF

/*****************************************************************************/

/** Reg HAC_WDC_GP_PAT
RX HAC WDC Group check pattern
*/
#define PHY_CSR__HAC_WDC_GP_PAT CSR_ACCESS(PHY_CSR_BASE + 0x0000018C)

/** Field rg_hac_wdc_gp_pat
RX HAC WDC Group target pattern (if rg_hac_wdc_chk_en=1)
*/
#define HAC_WDC_GP_PAT__RG_HAC_WDC_GP_PAT_POS 0
#define HAC_WDC_GP_PAT__RG_HAC_WDC_GP_PAT_MASK 0xFFFFFFFF

/*****************************************************************************/

/** Reg HAC_WDC_ID_PAT
RX HAC WDC Individual check pattern
*/
#define PHY_CSR__HAC_WDC_ID_PAT CSR_ACCESS(PHY_CSR_BASE + 0x00000190)

/** Field rg_hac_wdc_id_pat
RX HAC WDC Individual target pattern (if rg_hac_wdc_chk_en=1)
*/
#define HAC_WDC_ID_PAT__RG_HAC_WDC_ID_PAT_POS 0
#define HAC_WDC_ID_PAT__RG_HAC_WDC_ID_PAT_MASK 0xFFFFFFFF

/*****************************************************************************/

/** Reg HAC_WDC_CHK_CNT
RX HAC WDC check counter
*/
#define PHY_CSR__HAC_WDC_CHK_CNT CSR_ACCESS(PHY_CSR_BASE + 0x00000194)

/** Field rg_hac_wdc_chk_cnt
RX HAC WDC target pattern counter (if rg_hac_wdc_chk_en=1)
 (1) work if rg_hac_wdc_chk_en=1, and it's done unitl rg_hac_wdc_chk_ind=1
 (2) count to target rg_hac_wdc_chk_pat from rg_hac_wdc_ind_lat 
      = it's the remaining amount of WDC(WUC) bits
 (3) RX sleep time followed by Frame = rg_hac_wdc_chk_cnt x symbol_time
*/
#define HAC_WDC_CHK_CNT__RG_HAC_WDC_CHK_CNT_POS 0
#define HAC_WDC_CHK_CNT__RG_HAC_WDC_CHK_CNT_MASK 0xFFFFFFFF

/*****************************************************************************/

/** Reg PN9_COEF
PN9 COEF
*/
#define PHY_CSR__PN9_COEF CSR_ACCESS(PHY_CSR_BASE + 0x00000198)

/** Field rg_pn9_init
PN9 initial values
*/
#define PN9_COEF__RG_PN9_INIT_POS 0
#define PN9_COEF__RG_PN9_INIT_MASK 0x000001FF

/** Field rg_pn9_poly
PN9 polynomial
 - from X0(C9) to X8(C1), default set 0x108 is "X0(C9) xor X5(C4)"
*/
#define PN9_COEF__RG_PN9_POLY_POS 12
#define PN9_COEF__RG_PN9_POLY_MASK 0x001FF000

/*****************************************************************************/

/** Reg RX_FO_DCR
RX Frequency offset DC Removal
*/
#define PHY_CSR__RX_FO_DCR CSR_ACCESS(PHY_CSR_BASE + 0x0000019C)

/** Field rg_fo_dcr_dis
RX DCR contorl
0: enable
1: disable
*/
#define RX_FO_DCR__RG_FO_DCR_DIS_POS 0
#define RX_FO_DCR__RG_FO_DCR_DIS_MASK 0x00000001

/** Field rg_fo_ddc_until_pd
FO_DCR update DDC per "rg_fo_drc_upd_dly" until PD hit
0: disable
1: enable
*/
#define RX_FO_DCR__RG_FO_DDC_UNTIL_PD_POS 1
#define RX_FO_DCR__RG_FO_DDC_UNTIL_PD_MASK 0x00000002

/** Field rg_fo_dcr_keep_on
DCR keep to subtract DC value after pmb_ind
0: disable
1: enable
*/
#define RX_FO_DCR__RG_FO_DCR_KEEP_ON_POS 2
#define RX_FO_DCR__RG_FO_DCR_KEEP_ON_MASK 0x00000004

/** Field rg_fo_dcr_clip_en
FO_DCR update DDC value with clipping by rg_fo_dcr_clip_val
0: disable
1: enable
*/
#define RX_FO_DCR__RG_FO_DCR_CLIP_EN_POS 3
#define RX_FO_DCR__RG_FO_DCR_CLIP_EN_MASK 0x00000008

/** Field rg_fo_dcr_upd_dly
If DCR updates, set the delay time for DDC to MF
 - the delay time is rg_fo_drc_upd_dly x 2 (symbols)
*/
#define RX_FO_DCR__RG_FO_DCR_UPD_DLY_POS 4
#define RX_FO_DCR__RG_FO_DCR_UPD_DLY_MASK 0x000000F0

/** Field rg_rx_fltr_osr1_sel
RX filter down-sample rate inverse factor1
0: 1/8
1: 1/5
2: 1/25
3: 1/7
*/
#define RX_FO_DCR__RG_RX_FLTR_OSR1_SEL_POS 8
#define RX_FO_DCR__RG_RX_FLTR_OSR1_SEL_MASK 0x00000300

/** Field rg_fo_dcr_method
DCR method
0: caculating DC values of 4 symbols
1: average max value and min value in 4 symbols period, the function is enabled by HW if rg_mc_en set HIGH.
*/
#define RX_FO_DCR__RG_FO_DCR_METHOD_POS 11
#define RX_FO_DCR__RG_FO_DCR_METHOD_MASK 0x00000800

/** Field rg_rx_fltr_osr2_sel
RX filter down-sample rate inverse factor2
0: x4
1: x2
2: x1
3: x1/2
4: x1/4
5: x1/8
6: x1/16
7: 1/32

e.g. RX filter down-sample rate [2x1x2x2] = 8 --> inserse is 1/8
 - rg_rx_fltr_osr1_sel = 0 --> x1/8
 - rg_rx_fltr_osr2_sel = 2 --> x1
*/
#define RX_FO_DCR__RG_RX_FLTR_OSR2_SEL_POS 12
#define RX_FO_DCR__RG_RX_FLTR_OSR2_SEL_MASK 0x00007000

/** Field rg_sps_inv
The value is 1/rg_sps, format <0,-2,10>
 - (default) 1/5 = 8'b1100_1101=0xCD, <0,-2,10>
 - HW will fill setting the vaule if rg_sps[3:0]= 4, 5, or 10
   - rg_sps[3:0]=4'd4  : auot-set  1/rg_sps=1/4=8'b1111_1111 by HW
   - rg_sps[3:0]=4'd5  : auot-set  1/rg_sps=1/5=8'b1100_1101 by HW
   - rg_sps[3:0]=4'd10 : auot-set 1/rg_sps=1/10=8'b0110_0110 by HW
   - otherwise : set rg_sps_inv by SW
*/
#define RX_FO_DCR__RG_SPS_INV_POS 16
#define RX_FO_DCR__RG_SPS_INV_MASK 0x00FF0000

/** Field rg_fo_dcr_clip_val
DCR frequency offset clipping value, format <0,0,8>
 - if rg_fo_dcr_clip_en=1, the frequency offset DCR value "rx_dcr_offset" will clip by this RG. 
 - abs(rx_dcr_offset) > {1'b0, rg_fo_dcr_clip_val, 11'b0} will clip by this RG
 - rg_fo_dcr_clip_val = dec2hex(floor(max_FO/PHY_CLK *2*pi *M1p*D2 *2^19/2^11)) 
 - e.g. Support max=30K frequency offset @ PHY_CLK=16M, M1p=8, D2=2
   rg_fo_dcr_clip_val = dec2hex(floor(30/16000 *2*pi *8*2 *2^19/2^11)) = 0x30
*/
#define RX_FO_DCR__RG_FO_DCR_CLIP_VAL_POS 24
#define RX_FO_DCR__RG_FO_DCR_CLIP_VAL_MASK 0xFF000000

/*****************************************************************************/

/** Reg RX_FO_DCR_RESULT
RX Frequency offset DC Removal
*/
#define PHY_CSR__RX_FO_DCR_RESULT CSR_ACCESS(PHY_CSR_BASE + 0x000001A0)

/** Field rx_dcr_offset
DCR frequency offset value to DDC, format <1,0,19>
*/
#define RX_FO_DCR_RESULT__RX_DCR_OFFSET_POS 0
#define RX_FO_DCR_RESULT__RX_DCR_OFFSET_MASK 0x000FFFFF

/** Field rx_dcr_4sym_dc
DCR 4-symbol average DC value, format <1,2,8>
*/
#define RX_FO_DCR_RESULT__RX_DCR_4SYM_DC_POS 20
#define RX_FO_DCR_RESULT__RX_DCR_4SYM_DC_MASK 0x7FF00000

/** Field rx_dcr_done
DCR done flag
*/
#define RX_FO_DCR_RESULT__RX_DCR_DONE_POS 31
#define RX_FO_DCR_RESULT__RX_DCR_DONE_MASK 0x80000000

/*****************************************************************************/

/** Reg RX_DAGC_TEST
RX DAGC manual gain
*/
#define PHY_CSR__RX_DAGC_TEST CSR_ACCESS(PHY_CSR_BASE + 0x000001A4)

/** Field rg_dagc_gain_manual
Manual DAGC gain setting if rg_dagc_man_en=1.

*/
#define RX_DAGC_TEST__RG_DAGC_GAIN_MANUAL_POS 0
#define RX_DAGC_TEST__RG_DAGC_GAIN_MANUAL_MASK 0x00003FFF

/** Field rg_rf_rst_count_tgt
DAGC restart count if rf_restart_en = 1

*/
#define RX_DAGC_TEST__RG_RF_RST_COUNT_TGT_POS 16
#define RX_DAGC_TEST__RG_RF_RST_COUNT_TGT_MASK 0x001F0000

/** Field rg_rf_restart_en
DAGC restart control
0:disable
1:enable
*/
#define RX_DAGC_TEST__RG_RF_RESTART_EN_POS 24
#define RX_DAGC_TEST__RG_RF_RESTART_EN_MASK 0x01000000

/** Field rg_dagc_rssi_restart
RFAGC restart and DAGC RSSI restart control
0:disable
1:enable
*/
#define RX_DAGC_TEST__RG_DAGC_RSSI_RESTART_POS 28
#define RX_DAGC_TEST__RG_DAGC_RSSI_RESTART_MASK 0x10000000

/*****************************************************************************/

/** Reg RX_RSSI_IB
RX RSSI In-Band control
*/
#define PHY_CSR__RX_RSSI_IB CSR_ACCESS(PHY_CSR_BASE + 0x000001A8)

/** Field rg_rssi_ib_lsn_en
RX In-Band RSSI listen enable. 
0: disable
1: enable, 
*/
#define RX_RSSI_IB__RG_RSSI_IB_LSN_EN_POS 0
#define RX_RSSI_IB__RG_RSSI_IB_LSN_EN_MASK 0x00000001

/** Field rg_rssi_ib_ki_init
In-Band RSSI Ki select before pmb_ind:
 - control factor by rg_rssi_ib_method
0 : ib_method=0: 2^-4 , ib_method=1: 2^0 (default)
1 : ib_method=0: 2^-5 (default) , ib_method=1: 2^-1 
2 : ib_method=0: 2^-6 , ib_method=1: 2^-2
3 : ib_method=0: 2^-7 , ib_method=1: 2^-3 
4 : ib_method=0: 2^-8 , ib_method=1: 2^-4
5 : ib_method=0: 2^-9 , ib_method=1: 2^-5
6 : ib_method=0: 2^-10, ib_method=1: 2^-6
7 : ib_method=0: 2^-11, ib_method=1: 2^-7

(2) default set rg_rssi_ib_ki_init = 1, fast (corse) RSSI accuracy +/-2

(3) if rg_rssi_ib_method=1, keep to use rg_rssi_ib_ki_init after pmb_ind, 
 - set rg_rssi_ib_ki_init = 0
 - set rg_rssi_ib_cal_sh = 3
 - set rg_rssi_offset = 36 = 0x24

(4) For calculating the high RSSI accuracy (small than +/-1)
 - set rg_rssi_ib_ki_init = 3
 - set rg_rssi_ib_method = 0
 - may set rg_rssi_ib_stop_ctrl to calculate RSSI for a long time
*/
#define RX_RSSI_IB__RG_RSSI_IB_KI_INIT_POS 1
#define RX_RSSI_IB__RG_RSSI_IB_KI_INIT_MASK 0x0000000E

/** Field rg_rssi_ib_ki_apmd
In-Band RSSI Ki select after pmb_ind: (rg_rssi_ib_method=0)
0: 2^-4
1: 2^-5
2: 2^-6
3: 2^-7
4: 2^-8
5: 2^-9
6: 2^-10
7: 2^-11
*/
#define RX_RSSI_IB__RG_RSSI_IB_KI_APMD_POS 4
#define RX_RSSI_IB__RG_RSSI_IB_KI_APMD_MASK 0x00000070

/** Field rg_rssi_ib_lsn_thr
In-Band RSSI threshold to activate RX path if rg_rssi_ib_lsn_en=1.
RSSI threshold format is <0,7,1>, unit is dB, default 220=110x2
It will use to compare with RSSI value "rx_rssi_db_val"
*/
#define RX_RSSI_IB__RG_RSSI_IB_LSN_THR_POS 8
#define RX_RSSI_IB__RG_RSSI_IB_LSN_THR_MASK 0x0000FF00

/** Field rg_rssi_ib_lsn_cnfm_cnt
RSSI value over threshold confirm count. 
 - If RSSI absolute dB value "rx_rssi_db_val" is less threshold(rg_rssi_ib_lsn_thr) continuously for this confirm count (rg_rssi_ib_lsn_cnfm_cnt) , it will report to "rx_rssi_ib_over_flag" and "rg_phy_rx_rssi_irq"
*/
#define RX_RSSI_IB__RG_RSSI_IB_LSN_CNFM_CNT_POS 16
#define RX_RSSI_IB__RG_RSSI_IB_LSN_CNFM_CNT_MASK 0x000F0000

/** Field rg_rssi_ib_stop_ctrl
In-Band RSSI stop to caculate timing
0: PMB or MC indicate
1: SFD or HAC indicate
2: PHR indicate
3: until rx_en = 0
*/
#define RX_RSSI_IB__RG_RSSI_IB_STOP_CTRL_POS 20
#define RX_RSSI_IB__RG_RSSI_IB_STOP_CTRL_MASK 0x00300000

/** Field rg_rssi_ib_method
In-Band RSSI method
0: Alpha filter
1: window average of 8-symbol periods, control RSSI scaling by rg_rssi_ib_ki_apmd
*/
#define RX_RSSI_IB__RG_RSSI_IB_METHOD_POS 24
#define RX_RSSI_IB__RG_RSSI_IB_METHOD_MASK 0x01000000

/** Field rg_rssi_ib_cal_sh
Shift RSSI value "rx_rssi_ib_lvl" before calculate RSSI to dB
Use 18-bit <0,6,12> In-Band RSSI to calculate dB value
0: rx_rssi_ib_lvl[25:8], set if rg_rssi_ib_method=0
1: rx_rssi_ib_lvl[24:7]
2: rx_rssi_ib_lvl[23:6]
3: rx_rssi_ib_lvl[22:5], set if rg_rssi_ib_method=1
4: rx_rssi_ib_lvl[21:4]
5: rx_rssi_ib_lvl[20:3]
6: rx_rssi_ib_lvl[19:2]
7: rx_rssi_ib_lvl[18:1]
*/
#define RX_RSSI_IB__RG_RSSI_IB_CAL_SH_POS 28
#define RX_RSSI_IB__RG_RSSI_IB_CAL_SH_MASK 0x70000000

/*****************************************************************************/

/** Reg RX_RSSI_VAL
RX RSSI values
*/
#define PHY_CSR__RX_RSSI_VAL CSR_ACCESS(PHY_CSR_BASE + 0x000001AC)

/** Field rx_rssi_ib_lvl
RX In-Band RSSI level, format is <1,2,23>
*/
#define RX_RSSI_VAL__RX_RSSI_IB_LVL_POS 0
#define RX_RSSI_VAL__RX_RSSI_IB_LVL_MASK 0x03FFFFFF

/*****************************************************************************/

/** Reg rx_rssi_db_value
RX RSSI dB values
*/
#define PHY_CSR__RX_RSSI_DB_VALUE CSR_ACCESS(PHY_CSR_BASE + 0x000001B0)

/** Field rx_rssi_db_val
RX RSSI absolute value report, unit dB, format <1,7,6>
 - It is valid with a postive value
 - rx_rssi_db_val = (42-3xDA_RFRXFE_LNA_DIGC) + (31-DA_RXPGA_GAIN) 
                              + 20xlog10(dagc_gain) - 20xlog10(rx_rssi_ib_lvl) + rg_rssi_offset
*/
#define RX_RSSI_DB_VALUE__RX_RSSI_DB_VAL_POS 0
#define RX_RSSI_DB_VALUE__RX_RSSI_DB_VAL_MASK 0x00003FFF

/** Field rx_rssi_db_pmb_mc
RX RSSI absolute value report at pmb_hit or mc_hit, <1,7,6>
*/
#define RX_RSSI_DB_VALUE__RX_RSSI_DB_PMB_MC_POS 16
#define RX_RSSI_DB_VALUE__RX_RSSI_DB_PMB_MC_MASK 0x3FFF0000

/** Field rx_dagc_lock
status of digital AGC lock indication. The same with 0x130[9]=dagc_lock
*/
#define RX_RSSI_DB_VALUE__RX_DAGC_LOCK_POS 30
#define RX_RSSI_DB_VALUE__RX_DAGC_LOCK_MASK 0x40000000

/** Field pmb_ind
status of Preamble indicattion
*/
#define RX_RSSI_DB_VALUE__PMB_IND_POS 31
#define RX_RSSI_DB_VALUE__PMB_IND_MASK 0x80000000

/*****************************************************************************/

/** Reg phy_ret_spare
PHY Control Register Retention Spare
*/
#define PHY_CSR__PHY_RET_SPARE CSR_ACCESS(PHY_CSR_BASE + 0x000001B4)

/** Field rg_phy_ret_spare_a
PHY retention spare RG
*/
#define PHY_RET_SPARE__RG_PHY_RET_SPARE_A_POS 0
#define PHY_RET_SPARE__RG_PHY_RET_SPARE_A_MASK 0x0000FFFF

/** Field rg_phy_ret_spare_b
PHY retention spare RG
*/
#define PHY_RET_SPARE__RG_PHY_RET_SPARE_B_POS 16
#define PHY_RET_SPARE__RG_PHY_RET_SPARE_B_MASK 0xFFFF0000

/*****************************************************************************/

/** Reg rx_comp_fir_1f1_1f0
RX Compesation Filter 1F0 & 1F1 coefficient for down-sample 1
*/
#define PHY_CSR__RX_COMP_FIR_1F1_1F0 CSR_ACCESS(PHY_CSR_BASE + 0x000001D8)

/** Field rg_rx_comp_fir_1f0
Format is <1,0,12> in 2's complement format
*/
#define RX_COMP_FIR_1F1_1F0__RG_RX_COMP_FIR_1F0_POS 0
#define RX_COMP_FIR_1F1_1F0__RG_RX_COMP_FIR_1F0_MASK 0x00001FFF

/** Field rg_rx_comp_fir_1f1
Format is <1,0,12> in 2's complement format
*/
#define RX_COMP_FIR_1F1_1F0__RG_RX_COMP_FIR_1F1_POS 16
#define RX_COMP_FIR_1F1_1F0__RG_RX_COMP_FIR_1F1_MASK 0x1FFF0000

/*****************************************************************************/

/** Reg rx_comp_fir_1f3_1f2
RX Compesation Filter 1F2 & 1F3 coefficient for down-sample 1
*/
#define PHY_CSR__RX_COMP_FIR_1F3_1F2 CSR_ACCESS(PHY_CSR_BASE + 0x000001DC)

/** Field rg_rx_comp_fir_1f2
Format is <1,0,12> in 2's complement format
*/
#define RX_COMP_FIR_1F3_1F2__RG_RX_COMP_FIR_1F2_POS 0
#define RX_COMP_FIR_1F3_1F2__RG_RX_COMP_FIR_1F2_MASK 0x00001FFF

/** Field rg_rx_comp_fir_1f3
Format is <1,0,12> in 2's complement format
*/
#define RX_COMP_FIR_1F3_1F2__RG_RX_COMP_FIR_1F3_POS 16
#define RX_COMP_FIR_1F3_1F2__RG_RX_COMP_FIR_1F3_MASK 0x1FFF0000

/*****************************************************************************/

/** Reg rx_comp_fir_1f5_1f4
RX Compesation Filter 1F4 & 1F5 coefficient for down-sample 1
*/
#define PHY_CSR__RX_COMP_FIR_1F5_1F4 CSR_ACCESS(PHY_CSR_BASE + 0x000001E0)

/** Field rg_rx_comp_fir_1f4
Format is <1,0,12> in 2's complement format
*/
#define RX_COMP_FIR_1F5_1F4__RG_RX_COMP_FIR_1F4_POS 0
#define RX_COMP_FIR_1F5_1F4__RG_RX_COMP_FIR_1F4_MASK 0x00001FFF

/** Field rg_rx_comp_fir_1f5
Format is <1,0,12> in 2's complement format
*/
#define RX_COMP_FIR_1F5_1F4__RG_RX_COMP_FIR_1F5_POS 16
#define RX_COMP_FIR_1F5_1F4__RG_RX_COMP_FIR_1F5_MASK 0x1FFF0000

/*****************************************************************************/

/** Reg rx_comp_fir_1f7_1f6
RX Compesation Filter 1F6 & 1F7 coefficient for down-sample 1
*/
#define PHY_CSR__RX_COMP_FIR_1F7_1F6 CSR_ACCESS(PHY_CSR_BASE + 0x000001E4)

/** Field rg_rx_comp_fir_1f6
Format is <1,0,12> in 2's complement format
*/
#define RX_COMP_FIR_1F7_1F6__RG_RX_COMP_FIR_1F6_POS 0
#define RX_COMP_FIR_1F7_1F6__RG_RX_COMP_FIR_1F6_MASK 0x00001FFF

/** Field rg_rx_comp_fir_1f7
Format is <1,0,12> in 2's complement format
*/
#define RX_COMP_FIR_1F7_1F6__RG_RX_COMP_FIR_1F7_POS 16
#define RX_COMP_FIR_1F7_1F6__RG_RX_COMP_FIR_1F7_MASK 0x1FFF0000

/*****************************************************************************/

/** Reg rx_comp_fir_1f9_1f8
RX Compesation Filter 1F8 & 1F9 coefficient for down-sample 1
*/
#define PHY_CSR__RX_COMP_FIR_1F9_1F8 CSR_ACCESS(PHY_CSR_BASE + 0x000001E8)

/** Field rg_rx_comp_fir_1f8
Format is <1,0,12> in 2's complement format
*/
#define RX_COMP_FIR_1F9_1F8__RG_RX_COMP_FIR_1F8_POS 0
#define RX_COMP_FIR_1F9_1F8__RG_RX_COMP_FIR_1F8_MASK 0x00001FFF

/** Field rg_rx_comp_fir_1f9
Format is <1,0,12> in 2's complement format
*/
#define RX_COMP_FIR_1F9_1F8__RG_RX_COMP_FIR_1F9_POS 16
#define RX_COMP_FIR_1F9_1F8__RG_RX_COMP_FIR_1F9_MASK 0x1FFF0000

/*****************************************************************************/

/** Reg rx_comp_fir_1f11_1f10
RX Compesation Filter 1F10 & 1F11 coefficient for down-sample 1
*/
#define PHY_CSR__RX_COMP_FIR_1F11_1F10 CSR_ACCESS(PHY_CSR_BASE + 0x000001EC)

/** Field rg_rx_comp_fir_1f10
Format is <1,0,12> in 2's complement format
*/
#define RX_COMP_FIR_1F11_1F10__RG_RX_COMP_FIR_1F10_POS 0
#define RX_COMP_FIR_1F11_1F10__RG_RX_COMP_FIR_1F10_MASK 0x00001FFF

/** Field rg_rx_comp_fir_1f11
Format is <1,0,12> in 2's complement format
*/
#define RX_COMP_FIR_1F11_1F10__RG_RX_COMP_FIR_1F11_POS 16
#define RX_COMP_FIR_1F11_1F10__RG_RX_COMP_FIR_1F11_MASK 0x1FFF0000

/*****************************************************************************/

/** Reg rx_comp_fir_1f13_1f12
RX Compesation Filter 1F12 & 1F13 coefficient for down-sample 1
*/
#define PHY_CSR__RX_COMP_FIR_1F13_1F12 CSR_ACCESS(PHY_CSR_BASE + 0x000001F0)

/** Field rg_rx_comp_fir_1f12
Format is <1,0,12> in 2's complement format
*/
#define RX_COMP_FIR_1F13_1F12__RG_RX_COMP_FIR_1F12_POS 0
#define RX_COMP_FIR_1F13_1F12__RG_RX_COMP_FIR_1F12_MASK 0x00001FFF

/** Field rg_rx_comp_fir_1f13
Format is <1,0,12> in 2's complement format
*/
#define RX_COMP_FIR_1F13_1F12__RG_RX_COMP_FIR_1F13_POS 16
#define RX_COMP_FIR_1F13_1F12__RG_RX_COMP_FIR_1F13_MASK 0x1FFF0000

/*****************************************************************************/

/** Reg rx_comp_fir_1f15_1f14
RX Compesation Filter 1F14 & 1F15 coefficient for down-sample 1
*/
#define PHY_CSR__RX_COMP_FIR_1F15_1F14 CSR_ACCESS(PHY_CSR_BASE + 0x000001F4)

/** Field rg_rx_comp_fir_1f14
Format is <1,0,12> in 2's complement format
*/
#define RX_COMP_FIR_1F15_1F14__RG_RX_COMP_FIR_1F14_POS 0
#define RX_COMP_FIR_1F15_1F14__RG_RX_COMP_FIR_1F14_MASK 0x00001FFF

/** Field rg_rx_comp_fir_1f15
Format is <1,0,12> in 2's complement format
*/
#define RX_COMP_FIR_1F15_1F14__RG_RX_COMP_FIR_1F15_POS 16
#define RX_COMP_FIR_1F15_1F14__RG_RX_COMP_FIR_1F15_MASK 0x1FFF0000

/*****************************************************************************/

/** Reg PHY_HWLA_CTRL
PHY HWLA control
*/
#define PHY_CSR__PHY_HWLA_CTRL CSR_ACCESS(PHY_CSR_BASE + 0x000001F8)

/** Field phy_dump_sel
PHY HWLA dump select
0: disable
1: Pre-deciamtion dout
2: D2 filter dout
3: IQC dout
4: RX filter dout
5: C2P dout
6: DCR dout
7: Wide-band RSSI dout
8: ADC FIFO 5-bit dout
else : phy_probe_pin
*/
#define PHY_HWLA_CTRL__PHY_DUMP_SEL_POS 0
#define PHY_HWLA_CTRL__PHY_DUMP_SEL_MASK 0x0000000F

/** Field phy_dump_stop_sel
PHY HWLA stop trigger select
0: pmb_ind
1: sfd_ind
2: phy_dump_sw_stop (RG control by SW)
3: Wide-band rssi_over_flag
*/
#define PHY_HWLA_CTRL__PHY_DUMP_STOP_SEL_POS 4
#define PHY_HWLA_CTRL__PHY_DUMP_STOP_SEL_MASK 0x00000030

/** Field phy_dump_sw_stop

*/
#define PHY_HWLA_CTRL__PHY_DUMP_SW_STOP_POS 8
#define PHY_HWLA_CTRL__PHY_DUMP_SW_STOP_MASK 0x00000100

/** Field rx_sw_rst_rawdata

*/
#define PHY_HWLA_CTRL__RX_SW_RST_RAWDATA_POS 9
#define PHY_HWLA_CTRL__RX_SW_RST_RAWDATA_MASK 0x00000200

/** Field phy_dump_triggler_offset

*/
#define PHY_HWLA_CTRL__PHY_DUMP_TRIGGLER_OFFSET_POS 12
#define PHY_HWLA_CTRL__PHY_DUMP_TRIGGLER_OFFSET_MASK 0x07FFF000

/** Field phy_dump_stop_flag

*/
#define PHY_HWLA_CTRL__PHY_DUMP_STOP_FLAG_POS 28
#define PHY_HWLA_CTRL__PHY_DUMP_STOP_FLAG_MASK 0x10000000

/** Field phy_ram_control
DATA RAM control (when boot from ROM)
0: (default) 10K DRAM for SW
1: 2K DRAM for SW, split 2K DRAM for PHY HWLA log
*/
#define PHY_HWLA_CTRL__PHY_RAM_CONTROL_POS 31
#define PHY_HWLA_CTRL__PHY_RAM_CONTROL_MASK 0x80000000

/*****************************************************************************/

/** Reg PHY_DEBUG_READ_DATA
PHY DEBUG READ DATA
*/
#define PHY_CSR__PHY_DEBUG_READ_DATA CSR_ACCESS(PHY_CSR_BASE + 0x000001FC)

/** Field phy_dump_data

*/
#define PHY_DEBUG_READ_DATA__PHY_DUMP_DATA_POS 0
#define PHY_DEBUG_READ_DATA__PHY_DUMP_DATA_MASK 0xFFFFFFFF

#ifdef __cplusplus
}
#endif

#endif /* PHY_CSR_H */
