#ifndef TRANSCEIVERCSR_H
#define TRANSCEIVERCSR_H

#include "Transceiver.h"

#ifdef __cplusplus
extern "C" {
#endif

/*
Since RX I-ch and Q-ch are inverse after observing IQ waveform via Logic Analyzer,
we set 'rg_mc_inv_edge=1' (0 mapping 1-to-0) to inverse TX IQ.
*/
#define RX_IQ_INVERSE_SETTING 0

/*
* Since AGC will train to maximum gain automatically, we have to disable rx_en then enable rx_en that RF/IF AGC auto train gain.
*/
#define RF_IF_AGC_AUTO_TRAIN_GAIN_SETTING 0

/*
* test VC mux bug in Test Chip. 0x4002802C  RG_ATEST_VTST_VMUX[8:5] must config to 1.
*/
#define VTEST_SETTING 0

/*
* Since PLL may not work which was caused by analog test mode problem, set RG_ATEST_EN_33=1'b1 and 
* RG_ATEST_VTST_EN_33=1'b1 (analog TEST module power and voltage test control).
*/
#define ANA_TEST_MODULE_SETTING 0


/* IQ Calibration */
#define IQC_FLAG 1

#define Centauri_B2 0

/* 
* Since RX 16MHz mode bug, The 16M mode is working under 24M mode 
* setting except the PLL core frequency which is set by RG_PLL_FBDIV. 
*/
#define RX_LOW_POWER_16MHZ_MODE_SETTING 1


#define FIX_PT_FRACTION_BIT_NUM 10
#define MINUSONE (-1)

//#define PI 3.14159265359
//#define PI_FIXED_PT ((U32)(PI*(0x1 << FIX_PT_FRACTION_BIT_NUM)+0.5))

#if (10 == FIX_PT_FRACTION_BIT_NUM)
#define PI_FIXED_PT 3217 // for FIX_PT_FRACTION_BIT_NUM = 10
#else
#define PI_FIXED_PT 0 // for un-match FIX_PT_FRACTION_BIT_NUM
#endif



/* ------------------- ----------- */
/* ----------- MAC --------------- */
/* ------------------- ----------- */
// PHY control from MAC register csr_phy_cr1[31:0] (0x400200A4)
/* Field definition for MAC_CSR__PHY_CR1 */
#define PHY_CR1__PHY_TOP_POWER_ON_RESET_POS 0 // PHY_TOP power on reset
#define PHY_CR1__PHY_TOP_POWER_ON_RESET_MASK 0x00000001
#define PHY_CR1__PHY_TX_RX_RESET_POS 1 // PHY_TX, PHY_RX reset
#define PHY_CR1__PHY_TX_RX_RESET_MASK 0x00000002
#define PHY_CR1__PHY_CSR_RESET_POS 2 // PHY_CSR reset
#define PHY_CR1__PHY_CSR_RESET_MASK 0x00000004
#define PHY_CR1__PHY_DDSM_RESET_POS 3 // DDSM Synchronizer reset of RF Synthesizer side
#define PHY_CR1__PHY_DDSM_RESET_MASK 0x00000008

#define PHY_CR1__CLK_PHY_SEL_POS 4 // clk_phy select => 0: use clk_soc, 1: use PLL clock (AD_BBP_CLK) from FE
#define PHY_CR1__CLK_PHY_SEL_MASK 0x00000010
#define PHY_CR1__CLK_PHY_CSR_SEL_POS 5 // clk_phy_csr select => 0: use clk_soc, 1: use PLL clock (AD_BBP_CLK) from FE
#define PHY_CR1__CLK_PHY_CSR_SEL_MASK 0x00000020
#define PHY_CR1__CLK_PHY_CSR_RX_CLK_DIV2_SEL_POS 6
#define PHY_CR1__CLK_PHY_CSR_RX_CLK_DIV2_SEL_MASK 0x00000040

#define PHY_CR1__PHY_TX_CLK_ENABLE_POS 8 // PHY_TX clock enable. Set 1 to enable
#define PHY_CR1__PHY_TX_CLK_ENABLE_MASK 0x00000100
#define PHY_CR1__PHY_RX_CLK_ENABLE_POS 9 // PHY_RX clock enable. Set 1 to enable
#define PHY_CR1__PHY_RX_CLK_ENABLE_MASK 0x00000200
#define PHY_CR1__PHY_CSR_CLK_ENABLE_POS 10 // PHY_CSR clock enable. Set 1 to enable
#define PHY_CR1__PHY_CSR_CLK_ENABLE_MASK 0x00000400

#define PHY_CR1__PHY_CSR_SYNC_WAIT_CYCLE_SEL_POS 12    // PHY_CSR sync wait cycle => 5,6,7,8T of clk_soc (32MHz)
#define PHY_CR1__PHY_CSR_SYNC_WAIT_CYCLE_SEL_MASK 0x00003000


#define PHY_CLK_SEL_SOC     0 // clk_phy select => 0: use clk_soc
#define PHY_CLK_SEL_PLL     1 // clk_phy select => 1: use PLL clock (AD_BBP_CLK) from FE
#define PHY_CSR_CLK_SEL_SOC 0 // clk_phy_csr select => 0: use clk_soc
#define PHY_CSR_CLK_SEL_PLL 1 // clk_phy_csr select => 1: use PLL clock (AD_BBP_CLK) from FE


/* PHY_CSR sync wait cycle */
#define PHY_CSR_SYNC_WAIT_CYCLE_5T 0
#define PHY_CSR_SYNC_WAIT_CYCLE_6T 1
#define PHY_CSR_SYNC_WAIT_CYCLE_7T 2
#define PHY_CSR_SYNC_WAIT_CYCLE_8T 3




/* ------------------- ----------- */
/* ----------- Digital PHY ----------- */
/* ------------------- ----------- */
#define RX_IQC_DDC_CTRL__RX_IQC_DCB_DDC_EN_MASK (RX_IQC_DDC_CTRL__RG_RX_IQC_EN_MASK \
	                                               | RX_IQC_DDC_CTRL__RG_RX_DCB_EN_MASK \
	                                               | RX_IQC_DDC_CTRL__RG_RX_DDC_EN_MASK)

/* Convolutional code type definition */
#define PHY_FEC_TYPE_NRNSC 0
#define PHY_FEC_TYPE_RSC   1
/* MR-FSK type definition */
#define PHY_MRFSK_TYPE_2FSK 0
#define PHY_MRFSK_TYPE_4FSK 1
/* Bit-to-Symbol reverse mapping control */
#define PHY_BIT2SYM_MAPPING_NORMAL  0
#define PHY_BIT2SYM_MAPPING_REVERSE 1



/* Frame mode select */
#define IEEE_802_15_4G 0
#define TRANSPARENT    1
#define HAC            2

#define CHANNEL_BAND_868M 868000000		//868MHz
#define CHANNEL_BAND_900M 900000000     //900MHz
#define IF_BAND_500K 500000


/*
SFD type select
2'b 00 : {phyMRFSKSFD=0, SFD-uncoded} , 2FSK=16'h904E  , 4FSK=32'hD75575FD
2'b 01 : {phyMRFSKSFD=0, SFD-coded}     , 2FSK=16'h6F4E  , 4FSK=32'h7DFF75FD
2'b 10 : {phyMRFSKSFD=1, SFD-uncoded} , 2FSK=16'h7A0E  , 4FSK=32'h7FDD55FD
2'b 11 : {phyMRFSKSFD=1, SFD-coded}     , 2FSK=16'h632D  , 4FSK=32'h7D5F5DF7
*/
#define SFD_MRFSKSFD_TYPE0_UNCODED 0
#define SFD_MRFSKSFD_TYPE0_CODED   1
#define SFD_MRFSKSFD_TYPE1_UNCODED 2
#define SFD_MRFSKSFD_TYPE1_CODED   3

/* PHR length select */		//Do NOT support 0
#define PHR_LEN_2OCTETS 1
#define PHR_LEN_3OCTETS 2
#define PHR_LEN_4OCTETS 3

//#define HW_CSS_H_0P75 0		//h=0.75      //A1 didn't support!!
#define HW_CSS_H_1    1		//h=1

/* h controls BW */
#define H_COEFF_0P33 (0.33*(0x1 << FIX_PT_FRACTION_BIT_NUM))
#define H_COEFF_0P5  (0.5*(0x1 << FIX_PT_FRACTION_BIT_NUM))
#define H_COEFF_0P75 (0.75*(0x1 << FIX_PT_FRACTION_BIT_NUM))
#define H_COEFF_1    (1*(0x1 << FIX_PT_FRACTION_BIT_NUM))
#define H_COEFF_2    (2*(0x1 << FIX_PT_FRACTION_BIT_NUM))


/* FCS type */
#define FCS_TYPE_4_OCTETS 0
#define FCS_TYPE_2_OCTETS 1

/* Symbol Rate */	// (bsp)
#define SYMBOL_RATE_4P8K     4800
#define SYMBOL_RATE_10K      10000
#define SYMBOL_RATE_20K      20000
#define SYMBOL_RATE_25K      25000
#define SYMBOL_RATE_40K      40000
#define SYMBOL_RATE_50K      50000
#define SYMBOL_RATE_100K     100000
#define SYMBOL_RATE_150K     150000
#define SYMBOL_RATE_200K     200000
#define SYMBOL_RATE_250K     250000
#define SYMBOL_RATE_400K     400000
#define SYMBOL_RATE_500K     500000
//#define SYMBOL_RATE_32P6531K 32653.1		//For wM-Bus
/*
#define SYMBOL_RATE_48P83	 48.83
#define SYMBOL_RATE_61P04	 61.04
#define SYMBOL_RATE_97P66	 97.66
#define SYMBOL_RATE_122P07	 122.07
#define SYMBOL_RATE_195P31	 195.31
#define SYMBOL_RATE_244P14	 244.14
#define SYMBOL_RATE_390P63	 390.63
#define SYMBOL_RATE_488P28	 488.28
#define SYMBOL_RATE_781P25	 781.25
#define SYMBOL_RATE_976P56	 976.56
#define SYMBOL_RATE_1562P5	 1562.5
#define SYMBOL_RATE_1953P13	 1953.13
#define SYMBOL_RATE_3125	 3125
#define SYMBOL_RATE_3906P25	 3906.25
#define SYMBOL_RATE_6250	 6250
#define SYMBOL_RATE_7812P5	 7812.5
#define SYMBOL_RATE_15625	 15625
*/


/* CSS mode bandwidth select */ //(bps)
#define CSS_BANDWIDTH_18P75K	 18750
#define CSS_BANDWIDTH_25K		 25000
#define CSS_BANDWIDTH_31P25K	 31250
#define CSS_BANDWIDTH_37P5K	     37500
#define CSS_BANDWIDTH_50K		 50000
#define CSS_BANDWIDTH_62P5K	     62500
#define CSS_BANDWIDTH_75K		 75000
#define CSS_BANDWIDTH_100K		100000
#define CSS_BANDWIDTH_125K		125000
#define CSS_BANDWIDTH_150K		150000
#define CSS_BANDWIDTH_200K		200000
#define CSS_BANDWIDTH_250K		250000
#define CSS_BANDWIDTH_300K		300000
#define CSS_BANDWIDTH_400K		400000
#define CSS_BANDWIDTH_500K		500000

/* SS Factor */
#define SS_FACTOR_5  0
#define SS_FACTOR_6  1
#define SS_FACTOR_7  2
#define SS_FACTOR_8  3
#define SS_FACTOR_9  4
#define SS_FACTOR_10 5
#define SS_FACTOR_11 6
#define SS_FACTOR_12 7

/* For CSS/Turbo CSS tx_chan_gain configuration */
#define TX_CSS_OSR_TIMES_OF_64 0x1000
#define TX_CSS_OSR_TIMES_OF_80 0x0A3D

/* PHR Error Check Code */
#define PHR_EC_CODE_BCH 0
#define PHR_EC_CODE_CRC 1

/* HAC wake-up code select */
#define HAC_WAKEUP_CODE_BROADCAST  0
#define HAC_WAKEUP_CODE_GROUP      1
#define HAC_WAKEUP_CODE_INDIVIDUAL 2

/* Menchester code edge detect select */
#define MENCHESTER_CODE_EDGE_DET_MAPPING_0_TO_1 0
#define MENCHESTER_CODE_EDGE_DET_MAPPING_1_TO_0 1

/* Modulation */
#define MOD_TYPE_MFSK    0
#define MOD_TYPE_CSS     1
#define MOD_TYPE_OOK     2
//#define MOD_TYPE_GFILTER 3    //Configure by PHY rg_gfilter_en

/* TX Gaussian filter BT */
#define GAUSSIAN_FILTER_BT_0P5 0	//BT=0.5
#define GAUSSIAN_FILTER_BT_1   1

/* Baseband clock */
#define SAMPLE_FREQ_32M     0				//Fs = 32MHz, for HW register (rg_24M_en)
#define SAMPLE_FREQ_24M     1				//Fs = 24MHz, for HW register (rg_24M_en)
#define CLOCK_VALUE_32M     32000000		//32MHz
#define CLOCK_VALUE_24M     24000000		//24MHz


/* Phase Differentiator scale control */
#define PHASE_DIFF_SCALE_X1 0
#define PHASE_DIFF_SCALE_X2 1
#define PHASE_DIFF_SCALE_X4 2


/* Timing Recovery Detector */
#define TIMING_RCVY_EDGE_DET 0
#define TIMING_RCVY_ZC_DET   1

/* Timing Recovery Edge Detection Threshold (Format: <0,2,1>) */
#define TIMING_RCVY_EDGE_DET_THRESH_1P5 3

/* Timing Recovery PN acquisition window size */
#define TIMING_RCVY_PN_ACQ_WIN_SIZE_1     0
#define TIMING_RCVY_PN_ACQ_WIN_SIZE_2     1 
#define TIMING_RCVY_PN_ACQ_WIN_SIZE_4     2
#define TIMING_RCVY_PN_ACQ_WIN_SIZE_8     3
#define TIMING_RCVY_PN_ACQ_WIN_SIZE_16    4
#define TIMING_RCVY_PN_ACQ_WIN_SIZE_32    5
#define TIMING_RCVY_PN_ACQ_WIN_SIZE_64    6
#define TIMING_RCVY_PN_ACQ_WIN_SIZE_128   7
#define TIMING_RCVY_PN_ACQ_WIN_SIZE_256   8
#define TIMING_RCVY_PN_ACQ_WIN_SIZE_512   9
#define TIMING_RCVY_PN_ACQ_WIN_SIZE_1024 10

/* Time constant in timing recovery loop, in the range of [1/32~1/4], power of 1/2 */
#define TIMING_RCVY_PLL_K_SEL_1_PER_4 0
#define TIMING_RCVY_PLL_K_SEL_1_PER_8 1
#define TIMING_RCVY_PLL_K_SEL_1_PER_16 2
#define TIMING_RCVY_PLL_K_SEL_1_PER_32 3

/* Timing Recovery Extra scaling factor of PLL_K after SFD detected */
#define TIMING_RCVY_PLL_K_EXTRA_SCALE_FACTOR_1 0
#define TIMING_RCVY_PLL_K_EXTRA_SCALE_FACTOR_1_PER_2 1
#define TIMING_RCVY_PLL_K_EXTRA_SCALE_FACTOR_1_PER_4 2

/* PHY RX HW automatic-latch PHR DW bit (just support FEC OFF) */
#define RX_DATA_WHITENING_LATCH_MODE_SW_CTRL 0
#define RX_DATA_WHITENING_LATCH_MODE_AUTO_CTRL 1  //Only support FEC disable


/* FEC decode control (HW or SW) */
#define HW_DECODE_CONTROL 0
#define SW_DECODE_CONTROL 1

/* Viterbi trace-back length, in the range of [8,16]*/
#define VITERBI_TRACE_BACK_LEN_8   8 
#define VITERBI_TRACE_BACK_LEN_9   9 
#define VITERBI_TRACE_BACK_LEN_10 10
#define VITERBI_TRACE_BACK_LEN_11 11
#define VITERBI_TRACE_BACK_LEN_12 12
#define VITERBI_TRACE_BACK_LEN_13 13
#define VITERBI_TRACE_BACK_LEN_14 14
#define VITERBI_TRACE_BACK_LEN_15 15
#define VITERBI_TRACE_BACK_LEN_16 16

/* Manual DAGC gain setting if rg_dagc_man_en=1 */
#define DAGC_MANUAL_GAIN_SETTING_1   0
#define DAGC_MANUAL_GAIN_SETTING_2   1 
#define DAGC_MANUAL_GAIN_SETTING_3   2
#define DAGC_MANUAL_GAIN_SETTING_4   3
#define DAGC_MANUAL_GAIN_SETTING_5   4
#define DAGC_MANUAL_GAIN_SETTING_6   5
#define DAGC_MANUAL_GAIN_SETTING_7   6
#define DAGC_MANUAL_GAIN_SETTING_8   7
#define DAGC_MANUAL_GAIN_SETTING_9   8
#define DAGC_MANUAL_GAIN_SETTING_10  9
#define DAGC_MANUAL_GAIN_SETTING_11  10
#define DAGC_MANUAL_GAIN_SETTING_12  11
#define DAGC_MANUAL_GAIN_SETTING_13  12
#define DAGC_MANUAL_GAIN_SETTING_14  13
#define DAGC_MANUAL_GAIN_SETTING_15  14
#define DAGC_MANUAL_GAIN_SETTING_16  15

/* DAGC gain update period select: It will update RSSI and DAGC for every N samples of pre-decimation filter output. */
#define DAGC_UPDATE_PERIOD_SEL_2_SAMPLES  1 
#define DAGC_UPDATE_PERIOD_SEL_4_SAMPLES  2
#define DAGC_UPDATE_PERIOD_SEL_6_SAMPLES  3
#define DAGC_UPDATE_PERIOD_SEL_8_SAMPLES  4
#define DAGC_UPDATE_PERIOD_SEL_10_SAMPLES 5
#define DAGC_UPDATE_PERIOD_SEL_12_SAMPLES 6
#define DAGC_UPDATE_PERIOD_SEL_14_SAMPLES 7
#define DAGC_UPDATE_PERIOD_SEL_16_SAMPLES 8
#define DAGC_UPDATE_PERIOD_SEL_18_SAMPLES 9
#define DAGC_UPDATE_PERIOD_SEL_20_SAMPLES 10
#define DAGC_UPDATE_PERIOD_SEL_22_SAMPLES 11
#define DAGC_UPDATE_PERIOD_SEL_24_SAMPLES 12
#define DAGC_UPDATE_PERIOD_SEL_26_SAMPLES 13
#define DAGC_UPDATE_PERIOD_SEL_28_SAMPLES 14
#define DAGC_UPDATE_PERIOD_SEL_30_SAMPLES 15



/* MF AGC Target Level */
#define MFAGC_TGT_LV_1 0
#define MFAGC_TGT_LV_2 1
#define MFAGC_TGT_LV_3 2
#define MFAGC_TGT_LV_4 3

/* MF AGC Output Adaptation */
#define MFAGC_ADAPT_1_PER_4  0
#define MFAGC_ADAPT_1_PER_8  1
#define MFAGC_ADAPT_1_PER_16 2
#define MFAGC_ADAPT_1_PER_32 3
#define MFAGC_ADAPT_1_PER_64 4

/* MF AGC Output Average Level */
#define MFAGC_AVG_LV_1_PER_4  0
#define MFAGC_AVG_LV_1_PER_8  1
#define MFAGC_AVG_LV_1_PER_16 2
#define MFAGC_AVG_LV_1_PER_32 3
#define MFAGC_AVG_LV_1_PER_64 4

/* MF AGC Lock Count */
#define MFAGC_LOCK_CNT_1  0
#define MFAGC_LOCK_CNT_2  1
#define MFAGC_LOCK_CNT_3  2
#define MFAGC_LOCK_CNT_4  3
#define MFAGC_LOCK_CNT_5  4
#define MFAGC_LOCK_CNT_6  5
#define MFAGC_LOCK_CNT_7  6
#define MFAGC_LOCK_CNT_8  7
#define MFAGC_LOCK_CNT_9  8
#define MFAGC_LOCK_CNT_10 9
#define MFAGC_LOCK_CNT_11 10
#define MFAGC_LOCK_CNT_12 11
#define MFAGC_LOCK_CNT_13 12
#define MFAGC_LOCK_CNT_14 13
#define MFAGC_LOCK_CNT_15 14
#define MFAGC_LOCK_CNT_16 15

/* MF AGC Threshold Scale */
#define MFAGC_THRESH_SCALE_1_PER_2  0
#define MFAGC_THRESH_SCALE_1_PER_4  1
#define MFAGC_THRESH_SCALE_1_PER_8  2
#define MFAGC_THRESH_SCALE_1_PER_16 3

/* MF AGC gain initial value (format: <0,2,8>) */
#define MFAGC_GAIN_INIT_VALUE_1 256

/* Frequency Recovery Direct path (Kp) */
#define FREQ_RCVY_DIR_PATH_2_PWR_OF_NEG4 0
#define FREQ_RCVY_DIR_PATH_2_PWR_OF_NEG5 1
#define FREQ_RCVY_DIR_PATH_2_PWR_OF_NEG6 2
#define FREQ_RCVY_DIR_PATH_2_PWR_OF_NEG7 3
#define FREQ_RCVY_DIR_PATH_2_PWR_OF_NEG8 4

/* Frequency Recovery Integration path (Ki) */
#define FREQ_RCVY_INT_PATH_2_PWR_OF_NEG4 0
#define FREQ_RCVY_INT_PATH_2_PWR_OF_NEG5 1
#define FREQ_RCVY_INT_PATH_2_PWR_OF_NEG6 2
#define FREQ_RCVY_INT_PATH_2_PWR_OF_NEG7 3
#define FREQ_RCVY_INT_PATH_2_PWR_OF_NEG8 4

/* RF AFC Frequency Adjustment Gain */
#define FREQ_RCVY_RF_AFC_ADJ_GAIN_2_PWR_OF_NEG4 0
#define FREQ_RCVY_RF_AFC_ADJ_GAIN_2_PWR_OF_NEG5 1
#define FREQ_RCVY_RF_AFC_ADJ_GAIN_2_PWR_OF_NEG6 2
#define FREQ_RCVY_RF_AFC_ADJ_GAIN_2_PWR_OF_NEG7 3
#define FREQ_RCVY_RF_AFC_ADJ_GAIN_2_PWR_OF_NEG8 4
#define FREQ_RCVY_RF_AFC_ADJ_GAIN_0             7	//5, 6: reserved

/* Frequency Recovery Lock Threshold */
#define FREQ_RCVY_LOCK_THRESH_1_PER_4  0
#define FREQ_RCVY_LOCK_THRESH_1_PER_8  1
#define FREQ_RCVY_LOCK_THRESH_1_PER_16 2

/* Frequency Recovery scaling factor of Kp/Ki after SFD detected */
#define FREQ_RCVY_SACALING_FACTOR_1 0
#define FREQ_RCVY_SACALING_FACTOR_1_PER_2 1
#define FREQ_RCVY_SACALING_FACTOR_1_PER_4 2




/* Time constant for Digital Down-Converstion frequency adjustment */
#define RX_DDC_FREQ_SEL_X1 0
#define RX_DDC_FREQ_SEL_X1_PER_2 1

/* RX preamble acquisition control */
#define PREAMBLE_MODE_8_BITS  0
#define PREAMBLE_MODE_16_BITS 1
#define PREAMBLE_MODE_24_BITS 2
#define PREAMBLE_MODE_32_BITS 3

/* Preamble acquisition threshold, in the range of [1,32] */
#define PREAMBLE_ACQ_THRESHOLD_1_BITS  0
#define PREAMBLE_ACQ_THRESHOLD_2_BITS  1 
#define PREAMBLE_ACQ_THRESHOLD_3_BITS  2 
#define PREAMBLE_ACQ_THRESHOLD_4_BITS  3 
#define PREAMBLE_ACQ_THRESHOLD_5_BITS  4 
#define PREAMBLE_ACQ_THRESHOLD_6_BITS  5 
#define PREAMBLE_ACQ_THRESHOLD_7_BITS  6 
#define PREAMBLE_ACQ_THRESHOLD_8_BITS  7 
#define PREAMBLE_ACQ_THRESHOLD_9_BITS  8 
#define PREAMBLE_ACQ_THRESHOLD_10_BITS 9 
#define PREAMBLE_ACQ_THRESHOLD_11_BITS 10
#define PREAMBLE_ACQ_THRESHOLD_12_BITS 11
#define PREAMBLE_ACQ_THRESHOLD_13_BITS 12
#define PREAMBLE_ACQ_THRESHOLD_14_BITS 13
#define PREAMBLE_ACQ_THRESHOLD_15_BITS 14
#define PREAMBLE_ACQ_THRESHOLD_16_BITS 15
#define PREAMBLE_ACQ_THRESHOLD_17_BITS 16
#define PREAMBLE_ACQ_THRESHOLD_18_BITS 17
#define PREAMBLE_ACQ_THRESHOLD_19_BITS 18
#define PREAMBLE_ACQ_THRESHOLD_20_BITS 19
#define PREAMBLE_ACQ_THRESHOLD_21_BITS 20
#define PREAMBLE_ACQ_THRESHOLD_22_BITS 21
#define PREAMBLE_ACQ_THRESHOLD_23_BITS 22
#define PREAMBLE_ACQ_THRESHOLD_24_BITS 23
#define PREAMBLE_ACQ_THRESHOLD_25_BITS 24
#define PREAMBLE_ACQ_THRESHOLD_26_BITS 25
#define PREAMBLE_ACQ_THRESHOLD_27_BITS 26
#define PREAMBLE_ACQ_THRESHOLD_28_BITS 27
#define PREAMBLE_ACQ_THRESHOLD_29_BITS 28
#define PREAMBLE_ACQ_THRESHOLD_30_BITS 29
#define PREAMBLE_ACQ_THRESHOLD_31_BITS 30
#define PREAMBLE_ACQ_THRESHOLD_32_BITS 31


/* Start-of-Frame (SFD) detection threshold, in the range of [1,32] */
#define SFD_DET_THRESHOLD_1_BITS  0
#define SFD_DET_THRESHOLD_2_BITS  1 
#define SFD_DET_THRESHOLD_3_BITS  2 
#define SFD_DET_THRESHOLD_4_BITS  3 
#define SFD_DET_THRESHOLD_5_BITS  4 
#define SFD_DET_THRESHOLD_6_BITS  5 
#define SFD_DET_THRESHOLD_7_BITS  6 
#define SFD_DET_THRESHOLD_8_BITS  7 
#define SFD_DET_THRESHOLD_9_BITS  8 
#define SFD_DET_THRESHOLD_10_BITS 9 
#define SFD_DET_THRESHOLD_11_BITS 10
#define SFD_DET_THRESHOLD_12_BITS 11
#define SFD_DET_THRESHOLD_13_BITS 12
#define SFD_DET_THRESHOLD_14_BITS 13
#define SFD_DET_THRESHOLD_15_BITS 14
#define SFD_DET_THRESHOLD_16_BITS 15
#define SFD_DET_THRESHOLD_17_BITS 16
#define SFD_DET_THRESHOLD_18_BITS 17
#define SFD_DET_THRESHOLD_19_BITS 18
#define SFD_DET_THRESHOLD_20_BITS 19
#define SFD_DET_THRESHOLD_21_BITS 20
#define SFD_DET_THRESHOLD_22_BITS 21
#define SFD_DET_THRESHOLD_23_BITS 22
#define SFD_DET_THRESHOLD_24_BITS 23
#define SFD_DET_THRESHOLD_25_BITS 24
#define SFD_DET_THRESHOLD_26_BITS 25
#define SFD_DET_THRESHOLD_27_BITS 26
#define SFD_DET_THRESHOLD_28_BITS 27
#define SFD_DET_THRESHOLD_29_BITS 28
#define SFD_DET_THRESHOLD_30_BITS 29
#define SFD_DET_THRESHOLD_31_BITS 30
#define SFD_DET_THRESHOLD_32_BITS 31


/* SFD mode */
#define RX_SFD_8_BITS_MODE  0              // 8 bits, use rg_sfd_pat0/1[7:0]
#define RX_SFD_16_BITS_MODE 1 //Default      //16 bits, use rg_sfd_pat0/1[15:0]
#define RX_SFD_24_BITS_MODE 2            //24 bits, use {rg_sfd_pat0/1_h16b[7:0], rg_sfd_pat0/1[15:0]}
#define RX_SFD_32_BITS_MODE 3            //32 bits, use {rg_sfd_pat0/1_h16b[15:0], rg_sfd_pat0/1[15:0]}

/* SFD indication control */
#define RX_SFD_IND_SFD_OR_PMB  0               //sfd_ind will be asserted only if sfd_pattern is matched.
#define RX_SFD_IND_SFD_AND_PMB 1  //Default       //sfd_ind will be asserted if both pmb_ind=1 and sfd_pattern is matched.


/* CSS signal confirm detection count.  The confirm count will be 2*N. N=0~15. */
#define CSS_CONFIRM_DETECT_COUNT_0   0
#define CSS_CONFIRM_DETECT_COUNT_2   1
#define CSS_CONFIRM_DETECT_COUNT_4   2
#define CSS_CONFIRM_DETECT_COUNT_6   3
#define CSS_CONFIRM_DETECT_COUNT_8   4
#define CSS_CONFIRM_DETECT_COUNT_10  5 
#define CSS_CONFIRM_DETECT_COUNT_12  6 
#define CSS_CONFIRM_DETECT_COUNT_14  7 
#define CSS_CONFIRM_DETECT_COUNT_16  8 
#define CSS_CONFIRM_DETECT_COUNT_18  9 
#define CSS_CONFIRM_DETECT_COUNT_20 10
#define CSS_CONFIRM_DETECT_COUNT_22 11
#define CSS_CONFIRM_DETECT_COUNT_24 12
#define CSS_CONFIRM_DETECT_COUNT_26 13
#define CSS_CONFIRM_DETECT_COUNT_28 14
#define CSS_CONFIRM_DETECT_COUNT_30 15


/* PHR field definition */
#define PHR_RESERVED_FIELD 0x0
#define PHR_MS_POS 31
#define PHR_MS_MASK 0x80000000
#define RESERVED_BIT_POS 29
#define RESERVED_BIT_MASK 0x60000000
#define PHR_FCS_TYPE_POS 28
#define PHR_FCS_TYPE_MASK 0x10000000
#define PHR_DW_EN_POS 27
#define PHR_DW_EN_MASK 0x08000000
#define PHR_FRAME_LEN_POS 16
#define PHR_FRAME_LEN_MASK 0x07FF0000


/* Decimation factor index */
#define PRE_DECIM_FACTOR_BY_7  0
#define PRE_DECIM_FACTOR_BY_8  1
#define PRE_DECIM_FACTOR_BY_10 2

#define CIC1_DECIM_FACTOR_BY_1 0
#define CIC1_DECIM_FACTOR_BY_2 1
#define CIC1_DECIM_FACTOR_BY_5 2
#define CIC1_DECIM_FACTOR_BY_7 3
#define CIC1_DECIM_FACTOR_BY_8 4

#define CIC2_DECIM_FACTOR_BY_1 0
#define CIC2_DECIM_FACTOR_BY_2 1
#define CIC2_DECIM_FACTOR_BY_4 2
#define CIC2_DECIM_FACTOR_BY_5 3

#define RX_FILT_CTRL__FSK_DECIM_FACTOR_OSR_64    0x9001
#define RX_FILT_CTRL__FSK_DECIM_FACTOR_OSR_128   0x1001
#define RX_FILT_CTRL__FSK_DECIM_FACTOR_OSR_80    0x9001
#define RX_FILT_CTRL__FSK_DECIM_FACTOR_OSR_160   0xC011 //0x1001
#define RX_FILT_CTRL__FSK_DECIM_FACTOR_OSR_320   0x0001
#define RX_FILT_CTRL__FSK_DECIM_FACTOR_OSR_640   0x0011
#define RX_FILT_CTRL__FSK_DECIM_FACTOR_OSR_800   0x1021
#define RX_FILT_CTRL__FSK_DECIM_FACTOR_OSR_1280  0x0201
#define RX_FILT_CTRL__FSK_DECIM_FACTOR_OSR_1600  0x0021
#define RX_FILT_CTRL__FSK_DECIM_FACTOR_OSR_3200  0x0121
#define RX_FILT_CTRL__FSK_DECIM_FACTOR_OSR_5000  0x1322
#define RX_FILT_CTRL__FSK_DECIM_FACTOR_OSR_10000 0x0322
#define RX_FILT_CTRL__FSK_DECIM_FACTOR_OSR_980   0x1030
#define RX_FILT_CTRL__FSK_DECIM_FACTOR_OSR_6400  0x0221
#define RX_FILT_CTRL__FSK_DECIM_FACTOR_OSR_12800 0x0341

#define RX_FILT_CTRL__CSS_DECIM_FACTOR_OSR_64  0x0001
#define RX_FILT_CTRL__CSS_DECIM_FACTOR_OSR_128 0x0011
#define RX_FILT_CTRL__CSS_DECIM_FACTOR_OSR_256 0x0111
#define RX_FILT_CTRL__CSS_DECIM_FACTOR_OSR_512 0x0041
#define RX_FILT_CTRL__CSS_DECIM_FACTOR_OSR_80  0x5021
#define RX_FILT_CTRL__CSS_DECIM_FACTOR_OSR_160 0x1021
#define RX_FILT_CTRL__CSS_DECIM_FACTOR_OSR_320 0x0021
#define RX_FILT_CTRL__CSS_DECIM_FACTOR_OSR_640 0x0121

/* RX decimation factor for rx_filt_ctrl */


#define RX_FILT_CTRL__DECIM_FACTOR_MASK (RX_FILT_CTRL__RG_RX_PREDECIM_FACTOR_MASK \
	          | RX_FILT_CTRL__RG_RX_CIC1_DF_MASK | RX_FILT_CTRL__RG_RX_CIC2_DF_MASK \
	          | RX_FILT_CTRL__RG_RX_D2_FILT_BYPASS_MASK | RX_FILT_CTRL__RG_RX_COMP_FIR_SEL_MASK \
	          | RX_FILT_CTRL__RG_RX_DECIM_FIR_SEL_P_MASK | RX_FILT_CTRL__RG_RX_DECIM_FIR_SEL_D_MASK \
	          | RX_FILT_CTRL__RG_RX_DECIM_FIR_X1_EN_MASK)

#define RX_FO_DCR__DCR_FACTOR_MASK (RX_FO_DCR__RG_FO_DCR_DIS_MASK | RX_FO_DCR__RG_FO_DDC_UNTIL_PD_MASK \
			  | RX_FO_DCR__RG_FO_DCR_KEEP_ON_MASK | RX_FO_DCR__RG_FO_DCR_CLIP_EN_MASK \
			  | RX_FO_DCR__RG_FO_DCR_UPD_DLY_MASK | RX_FO_DCR__RG_RX_FLTR_OSR1_SEL_MASK \
			  | RX_FO_DCR__RG_FO_DCR_METHOD_MASK | RX_FO_DCR__RG_RX_FLTR_OSR2_SEL_MASK \
			  | RX_FO_DCR__RG_FO_DCR_CLIP_VAL_MASK)


/* PHY TX Framer output data control */
#define TX_PACKET_OUT_PRMB_SFD_PHR_PSDU 0  //normal packet (Preamble->SFD->PHR->PSDU)
#define TX_PACKET_OUT_SFD_PHR_PSDU      1  //send data from SFD (SFD->PHR->PSDU)
#define TX_PACKET_OUT_PHR_PSDU          2  //send data from PHR (PHR->PSDU); HW auto-set 2 when rg_phy_lpbk_en=1
#define TX_PACKET_OUT_PSDU              3  //send data just PSDU

#define LP33_CTRL1__RG_RXADCI_RXADCQ_PWD_MASK  (LP33_CTRL1__RG_RXADCI_PWD_MASK \
                                                        | LP33_CTRL1__RG_RXADCQ_PWD_MASK)


/* ------------------- ----------- */
/* ----------- Front-End ----------- */
/* ------------------- ----------- */

/* TX PA control */
#define TX_PA_POWER_CONTROL_AUTO 0
#define TX_PA_POWER_CONTROL_MANUAL 1

/* TX power max gain value (in dBm) */
#define TX_MAX_OUTPUT_POWER 20


/* Field definition for FE_CSR_VCORE__LP_CTRL */
#define LP_CTRL__LPF_DCOC_CAPSIZE_POS 8
#define LP_CTRL__LPF_DCOC_CAPSIZE_MASK 0x00000100
#define LP_CTRL__PGA_DCOC_CAPSIZE_POS 9
#define LP_CTRL__PGA_DCOC_CAPSIZE_MASK 0x00000200


/* Field definition for FE33_CSR__LP_CTRL */
#define LP_CTRL__RG_IFIBREF_PWD_33_POS  0 // RG_LPCTRL_33[0] = RG_IFIBREF_PWD_33 = 1'b1
#define LP_CTRL__RG_IFIBREF_PWD_33_MASK 0x00000001
#define LP_CTRL__RG_ATEST_VTST_VMUX_33_POS  4 // RG_LPCTRL_33[7:4] = RG_ATEST_VTST_VMUX_33[3:0] = 4'b0000
#define LP_CTRL__RG_ATEST_VTST_VMUX_33_MASK 0x000000F0
#define LP_CTRL__RG_RXADCI_PWD_33_POS  14 // RG_LPCTRL_33[14] = RG_RXADCI_PWD_33 = 1'b1
#define LP_CTRL__RG_RXADCI_PWD_33_MASK 0x00004000
#define LP_CTRL__RG_RXADCQ_PWD_33_POS  15 // RG_LPCTRL_33[15] = RG_RXADCQ_PWD_33 = 1'b1
#define LP_CTRL__RG_RXADCQ_PWD_33_MASK 0x00008000
#define LP_CTRL__RG_RXADC_DACBUF_HP_33_POS  16 // RG_LPCTRL_33[16] = RG_RXADC_DACBUF_HP_33 = 1'b0
#define LP_CTRL__RG_RXADC_DACBUF_HP_33_MASK 0x00010000
#define LP_CTRL__RG_RXADC_DACBUF_PWD_33_POS  17 // RG_LPCTRL_33[17] = RG_RXADC_DACBUF_PWD_33 = 1'b1
#define LP_CTRL__RG_RXADC_DACBUF_PWD_33_MASK 0x00020000
#define LP_CTRL__RG_RXADC_RXADC_DACVCM_33_POS  18 // RG_LPCTRL_33[19:18] = RG_RXADC_DACVCM_33[1:0] = 2'b10
#define LP_CTRL__RG_RXADC_RXADC_DACVCM_33_MASK 0x000C0000
#define LP_CTRL__RG_RXADC_DACREF_33_POS  20 // RG_LPCTRL_33[23:20] = RG_RXADC_DACREF_33[3:0] = 4'b1000
#define LP_CTRL__RG_RXADC_DACREF_33_MASK 0x00F00000
#define LP_CTRL__RG_RXADC_DACREF_LF_33_POS  24 // RG_LPCTRL_33[24] = RG_RXADC_DACREF_LF_33 = 1'b0
#define LP_CTRL__RG_RXADC_DACREF_LF_33_MASK 0x01000000
#define LP_CTRL__RG_RXADC_IBGEN_PWD_33_POS  25 // RG_LPCTRL_33[25] = RG_RXADC_IBGEN_PWD_33 = 1'b1
#define LP_CTRL__RG_RXADC_IBGEN_PWD_33_MASK 0x02000000
#define LP_CTRL__RG_RXADC_LPBYPS_33_POS  26 // RG_LPCTRL_33[26] = RG_RXADC_LPBYPS_33 = 1'b0
#define LP_CTRL__RG_RXADC_LPBYPS_33_MASK 0x04000000
#define LP_CTRL__RG_RXADC_LPRES_33_POS  27 // RG_LPCTRL_33[27] = RG_RXADC_LPRES_33 = 1'b1
#define LP_CTRL__RG_RXADC_LPRES_33_MASK 0x08000000
#define LP_CTRL__RG_RXADC_TUNE_MAN_33_POS  28 // RG_LPCTRL_33[28] = RG_RXADC_TUNE_MAN_33 = 1'b1
#define LP_CTRL__RG_RXADC_TUNE_MAN_33_MASK 0x10000000
#define LP_CTRL__RG_RXADC_VRDAC_TUNE_33_POS  29 // RG_LPCTRL_33[31:29] = RG_RXADC_VRDAC_TUNE_33[2:0] = 3'b000
#define LP_CTRL__RG_RXADC_VRDAC_TUNE_33_MASK 0xE0000000

#define LP_CTRL__RG_RXADCI_RXADCQ_PWD_33_MASK (LP_CTRL__RG_RXADCI_PWD_33_MASK \
	                                             | LP_CTRL__RG_RXADCQ_PWD_33_MASK)
#define IFRX_CTRL__RG_RXIFI_RXIFQ_PWD_MASK (IFRX_CTRL__RG_RXIFI_PWD_MASK \
	                                          | IFRX_CTRL__RG_RXIFQ_PWD_MASK)

/* Field definition for FE_CSR_VCORE__RFRXFE_CTRL */
#define RFRXFE_CTRL__RG_VCO_NOISE_FILTER_EN_POS  16
#define RFRXFE_CTRL__RG_VCO_NOISE_FILTER_EN_MASK 0x00010000
#define RFRXFE_CTRL__RG_VCO_NOISE_FILTER_FREQ_SEL_POS  17
#define RFRXFE_CTRL__RG_VCO_NOISE_FILTER_FREQ_SEL_MASK 0x00060000

/* VCO noise filter frequency corner */
#define VCO_NOISE_FILTER_FREQ_CORNER_10K  0 // 00: 10 kHz, default
#define VCO_NOISE_FILTER_FREQ_CORNER_5K   1 // 01: 5 kHz
#define VCO_NOISE_FILTER_FREQ_CORNER_3P5K 2 // 10, 3.5 kHz
#define VCO_NOISE_FILTER_FREQ_CORNER_2P5K 3 // 11, 2.5 kHz

/* VCO frequency selection */
#define SYNTH_CTRL0_VCO_SEL_VCO1 1  // for VCO1, higher oscillation frequency, 1700~2100MHz for Band1 (860 ~ 950MHz) and Band3 (430 ~ 510 MHz)
#define SYNTH_CTRL0_VCO_SEL_VCO2 0  // for VCO2, lower oscillation frequency, 1200~1600MHz for Band2 (600~800MHz) and Band4 (315Mhz)

/* RG_SYNTH_DCBSEL: programmable bits for bypass cap of loop filter */
#define SYNTH_CTRL0__SYNTH_DCBSEL_6PF   0
#define SYNTH_CTRL0__SYNTH_DCBSEL_8PF   1
#define SYNTH_CTRL0__SYNTH_DCBSEL_10PF  2
#define SYNTH_CTRL0__SYNTH_DCBSEL_12PF  3
#define SYNTH_CTRL0__SYNTH_DCBSEL_14PF  4
#define SYNTH_CTRL0__SYNTH_DCBSEL_16PF  5
#define SYNTH_CTRL0__SYNTH_DCBSEL_18PF  6
#define SYNTH_CTRL0__SYNTH_DCBSEL_20PF  7

/* RG_SYNTH_DCZSEL: programmable bits for ZERO cap of loop filter */
#define SYNTH_CTRL0__SYNTH_DCZSEL_120PF 0
#define SYNTH_CTRL0__SYNTH_DCZSEL_136PF 1
#define SYNTH_CTRL0__SYNTH_DCZSEL_152PF 2
#define SYNTH_CTRL0__SYNTH_DCZSEL_168PF 3
#define SYNTH_CTRL0__SYNTH_DCZSEL_184PF 4
#define SYNTH_CTRL0__SYNTH_DCZSEL_200PF 5
#define SYNTH_CTRL0__SYNTH_DCZSEL_216PF 6
#define SYNTH_CTRL0__SYNTH_DCZSEL_232PF 7

/* RG_SYNTH_DLSEL: selection of PFD's feedback loop delay */
#define SYNTH_CTRL0__SYNTH_DLSEL_4NS 0
#define SYNTH_CTRL0__SYNTH_DLSEL_5NS 1 // default for VCO1
#define SYNTH_CTRL0__SYNTH_DLSEL_6NS 2 // default for VCO2
#define SYNTH_CTRL0__SYNTH_DLSEL_7NS 3

/* RG_SYNTH_DPIVCO: Selection of VCO gm-device current bias control */
#define SYNTH_CTRL0__SYNTH_DPIVCO_10UA 0
#define SYNTH_CTRL0__SYNTH_DPIVCO_15UA 1
#define SYNTH_CTRL0__SYNTH_DPIVCO_20UA 2
#define SYNTH_CTRL0__SYNTH_DPIVCO_25UA 3
#define SYNTH_CTRL0__SYNTH_DPIVCO_30UA 4
#define SYNTH_CTRL0__SYNTH_DPIVCO_35UA 5
#define SYNTH_CTRL0__SYNTH_DPIVCO_40UA 6
#define SYNTH_CTRL0__SYNTH_DPIVCO_45UA 7

/* RG_SYNTH_DRSEL: programmable bits for resistance of loop filter */
#define SYNTH_CTRL0__SYNTH_DRSEL_15K 0
#define SYNTH_CTRL0__SYNTH_DRSEL_18K 1
#define SYNTH_CTRL0__SYNTH_DRSEL_21K 2
#define SYNTH_CTRL0__SYNTH_DRSEL_24K 3
#define SYNTH_CTRL0__SYNTH_DRSEL_27K 4
#define SYNTH_CTRL0__SYNTH_DRSEL_30K 5
#define SYNTH_CTRL0__SYNTH_DRSEL_33K 6
#define SYNTH_CTRL0__SYNTH_DRSEL_36K 7

/* RF TX PA selection */
#define RF_TX_PA_PWR_MID  0  //Mid power PA
#define RF_TX_PA_PWR_HIGH 1  //High power PA

/* RX T/R Switch */
#define RF_FE_TR_SWITCH_RX 1
#define RF_FE_TR_SWITCH_TX 0

/* Band selection for RG_LO_BSEL */
#define LO_CTRL_LO_BSEL_BAND1      0  //RF band selection: 00, Band1 (860 ~ 950MHz)
#define LO_CTRL_LO_BSEL_BAND1_HIGH 950000000
#define LO_CTRL_LO_BSEL_BAND1_LOW  860000000
#define LO_CTRL_LO_BSEL_BAND2      1  //RF band selection: 01, Band2 (600~800MHz)
#define LO_CTRL_LO_BSEL_BAND2_HIGH 800000000
#define LO_CTRL_LO_BSEL_BAND2_LOW  600000000
#define LO_CTRL_LO_BSEL_BAND3      2  //RF band selection: 10, Band3 (430 ~ 510 MHz)
#define LO_CTRL_LO_BSEL_BAND3_HIGH 510000000
#define LO_CTRL_LO_BSEL_BAND3_LOW  430000000
#define LO_CTRL_LO_BSEL_BAND4      3  //RF band selection: 11, Band4 (315Mhz)
#define LO_CTRL_LO_BSEL_BAND4_FREQ      315000000

/*LO mode selection for RG_LO_RXSEL */
#define LO_MODE_SEL_TX 0
#define LO_MODE_SEL_RX 1

/* RG_LDOA12IQ_VREF: LDOA12IQ output voltage level */
#define LDO_CTRL1__LDOA12IQ_VREF_0P95V 0
#define LDO_CTRL1__LDOA12IQ_VREF_1V    1
#define LDO_CTRL1__LDOA12IQ_VREF_1P05V 2
#define LDO_CTRL1__LDOA12IQ_VREF_1P1V  3
#define LDO_CTRL1__LDOA12IQ_VREF_1P15V 4
#define LDO_CTRL1__LDOA12IQ_VREF_1P2V  5
#define LDO_CTRL1__LDOA12IQ_VREF_1P25V 6
#define LDO_CTRL1__LDOA12IQ_VREF_1P3V  7

/* RG_LDOA12DIG_VREF: LDOA12DIG output voltage level */
#define LDO_CTRL1__LDOA12DIG_VREF_0P95V 0
#define LDO_CTRL1__LDOA12DIG_VREF_1V    1
#define LDO_CTRL1__LDOA12DIG_VREF_1P05V 2
#define LDO_CTRL1__LDOA12DIG_VREF_1P1V  3
#define LDO_CTRL1__LDOA12DIG_VREF_1P15V 4
#define LDO_CTRL1__LDOA12DIG_VREF_1P2V  5
#define LDO_CTRL1__LDOA12DIG_VREF_1P25V 6
#define LDO_CTRL1__LDOA12DIG_VREF_1P3V  7

/* RG_LDOA12DADC_VREF: LDOA12DADC output voltage level */
#define LDO_CTRL2__LDOA12DADC_VREF_0P95V 0
#define LDO_CTRL2__LDOA12DADC_VREF_1V    1
#define LDO_CTRL2__LDOA12DADC_VREF_1P05V 2
#define LDO_CTRL2__LDOA12DADC_VREF_1P1V  3
#define LDO_CTRL2__LDOA12DADC_VREF_1P15V 4
#define LDO_CTRL2__LDOA12DADC_VREF_1P2V  5
#define LDO_CTRL2__LDOA12DADC_VREF_1P25V 6
#define LDO_CTRL2__LDOA12DADC_VREF_1P3V  7



/* IF RX LPF DC Offset Cancellation High Pass Gm-Rdg options */
#define IFRX_LPF_DOC_HP_GM_RDG_OPT_NON    0
#define IFRX_LPF_DOC_HP_GM_RDG_OPT_1M_OHM 1
#define IFRX_LPF_DOC_HP_GM_RDG_OPT_3M_OHM 2
#define IFRX_LPF_DOC_HP_GM_RDG_OPT_4M_OHM 3

/* IF RX PGA DC Offset Cancellation High Pass Gm-Rdg options */
#define IFRX_PGA_DOC_HP_GM_RDG_OPT_NON    0
#define IFRX_PGA_DOC_HP_GM_RDG_OPT_1M_OHM 1
#define IFRX_PGA_DOC_HP_GM_RDG_OPT_3M_OHM 2
#define IFRX_PGA_DOC_HP_GM_RDG_OPT_4M_OHM 3

/* RG_RXLPF_CC_SEL: RXIF LPF DCOC Charge Current options */
#define MISC_CTRL0__RXLPF_CC_26UA 0
#define MISC_CTRL0__RXLPF_CC_18UA 1
#define MISC_CTRL0__RXLPF_CC_10UA 2
#define MISC_CTRL0__RXLPF_CC_2UA  3

/* RG_RXPGA_CC_SEL: RXIF PGA DCOC Charge Current options */
#define MISC_CTRL0__RXPGA_CC_26UA 0
#define MISC_CTRL0__RXPGA_CC_18UA 1
#define MISC_CTRL0__RXPGA_CC_10UA 2
#define MISC_CTRL0__RXPGA_CC_2UA  3

/* RG_RXPGA_DCOC_BIAS_SEL: RXIF PGA DCOC Ro BIAS current options */
#define MISC_CTRL0__RXPGA_DCOC_BIAS_1UA    0
#define MISC_CTRL0__RXPGA_DCOC_BIAS_0P5UA  1
#define MISC_CTRL0__RXPGA_DCOC_BIAS_0P34UA 2
#define MISC_CTRL0__RXPGA_DCOC_BIAS_0P17UA 3

/* (fe_csr_vcore) LP_CTRL LPF/PGA Cap Size options */
#define LPCTRL__LPF_DCOC_CAPSIZE_5PF 0
#define LPCTRL__LPF_DCOC_CAPSIZE_18PF 1
#define LPCTRL__PGA_DCOC_CAPSIZE_18PF 0
#define LPCTRL__PGA_DCOC_CAPSIZE_36PF 1

/* RG_RXLPF_BAND: IF RX LPF low-pass band frequecny selection (-1dB) */
#define IFRX_LPF_BAND_SEL_220K 0
#define IFRX_LPF_BAND_SEL_330K 1
#define IFRX_LPF_BAND_SEL_440K 2
#define IFRX_LPF_BAND_SEL_550K 3
#define IFRX_LPF_BAND_SEL_600K 4
#define IFRX_LPF_BAND_SEL_660K 5
#define IFRX_LPF_BAND_SEL_770K 6
#define IFRX_LPF_BAND_SEL_880K 7

/* RF PLL digital clock selection */
#define PLL_DIGI_CLOCK_64M  0
#define PLL_DIGI_CLOCK_32M  1
#define PLL_DIGI_CLOCK_24M  2
#define PLL_DIGI_CLOCK_GND  3

/* RX ADC sample clock */
#define ADC_SAMPLE_CLOCK_24M   0
#define ADC_SAMPLE_CLOCK_32M   1
#define ADC_SAMPLE_CLOCK_38P4M 2
#define ADC_SAMPLE_CLOCK_16M   3

/* ADC OPINT Power Down Control */
#define ADC_RX_OPINT_PWR_ALL_ENABLE          0
#define ADC_RX_OPINT_PWR_STAGE_1_DISABLE     1
#define ADC_RX_OPINT_PWR_STAGE_1_2_DISABLE   2
#define ADC_RX_OPINT_PWR_STAGE_1_2_3_DISABLE 3

/* ADC 1st OPAMP bias current select */
#define ADC_RX_OPINT_BIAS_SEL_5UA   0
#define ADC_RX_OPINT_BIAS_SEL_6P5UA 1
#define ADC_RX_OPINT_BIAS_SEL_8P5UA 2
#define ADC_RX_OPINT_BIAS_SEL_10UA  3


/* ADC REF range select */
#define ADC_RX_IQCH_DAC_REF_0P5_V  0
#define ADC_RX_IQCH_DAC_REF_0P55_V 1
#define ADC_RX_IQCH_DAC_REF_0P6_V  2
#define ADC_RX_IQCH_DAC_REF_0P65_V 3

/* Tune ADC feedback resistor */
#define ADC_RX_IQCH_RDAC_TUNE_10K 0
#define ADC_RX_IQCH_RDAC_TUNE_15K 1
#define ADC_RX_IQCH_RDAC_TUNE_20K 2
#define ADC_RX_IQCH_RDAC_TUNE_25K 3

/* ADC TUNE DAC reference selection */
#define ADC_RX_IQCH_TUNE_DAC_VOLT_REF_0P5  0
#define ADC_RX_IQCH_TUNE_DAC_VOLT_REF_0P55 1
#define ADC_RX_IQCH_TUNE_DAC_VOLT_REF_0P6  2
#define ADC_RX_IQCH_TUNE_DAC_VOLT_REF_0P65 3
#define ADC_RX_IQCH_TUNE_DAC_VOLT_REF_0P7  4
#define ADC_RX_IQCH_TUNE_DAC_VOLT_REF_0P75 5
#define ADC_RX_IQCH_TUNE_DAC_VOLT_REF_0P8  6
#define ADC_RX_IQCH_TUNE_DAC_VOLT_REF_0P85 7

/* ADC OPINT POWER DOWN, STAGE1~3 */
#define ADC_RX_OPINT_PWD_STAGE_0 0 // all opamp enable
#define ADC_RX_OPINT_PWD_STAGE_1 1 // 1st opamp disable
#define ADC_RX_OPINT_PWD_STAGE_2 2 // 1st and 2nd opamp disable
#define ADC_RX_OPINT_PWD_STAGE_3 3 // all opamp disable

/* Testmode control, test VC mux */
#define PLL_V12MON      0
#define PLL_VCMON       1
#define BISTPLL_V12MON  2
#define BISTPLL_VCMON   3
#define BGREF_LPVBG12   4
#define BGREF_NMVBG12   5
#define AVDD15_IF       6
#define AVDD12_IF       7

/* Test out type selection */
#define TEST_MODULE_MIXER_OUT 0
#define TEST_MODULE_PGA_OUT   1
#define TEST_MODULE_LPF_OUT   2
//#define TEST_MODULE_ADC_OUT   3        //A1 didn't support
#define TEST_MODULE_ALL_OFF   4

/* RG_RFRXFE_LNA_DBC: Digital control of LNA bias current */
#define RFRXFE_LNA_DBC_40UA 0
#define RFRXFE_LNA_DBC_45UA 1 // low-power mode
#define RFRXFE_LNA_DBC_50UA 2 // default
#define RFRXFE_LNA_DBC_55UA 3

/* Bist PLL mode select */
#define BISTPLL_MODE_MASK 0x01C00000
#define BISTPLL_MODE_768M 0
#define BISTPLL_MODE_864M 1
#define BISTPLL_MODE_960M 2
#define BISTPLL_MODE_640M 3
#define BISTPLL_FREQ_320M 320000000
#define BISTPLL_FREQ_432M 432000000
#define BISTPLL_FREQ_480M 480000000
#define BISTPLL_FREQ_768M 768000000
#define BISTPLL_FREQ_864M 864000000
#define BISTPLL_FREQ_928M 928000000
#define BISTPLL_FREQ_960M 960000000


/*BistPLL selection for RF*/

#define BISTPLL_320M 0
#define BISTPLL_432M 1
#define BISTPLL_480M 2
#define BISTPLL_768M 3
#define BISTPLL_864M 4
#define BISTPLL_928M 5
#define BISTPLL_960M 6
#define BISTPLL_LOWER_BOUND	315000000
#define BISTPLL_432M_GATE 	376000000
#define BISTPLL_480M_GATE 	456000000
#define BISTPLL_768M_GATE 	624000000
#define BISTPLL_864M_GATE 	816000000
#define BISTPLL_928M_GATE 	896000000
#define BISTPLL_960M_GATE 	944000000
#define BISTPLL_UPPER_BOUND	1100000000



/* RG_BISTPLL_POSDIV: BISTPLL post-divider control */
#define BISTPLL_CTRL1__BISTPLL_POSDIV_DIV1 0
#define BISTPLL_CTRL1__BISTPLL_POSDIV_DIV2 1
#define BISTPLL_CTRL1__BISTPLL_POSDIV_DIV4 3

/* RG_XTAL_DCKO_DRV: XO external driving capability control */
#define BG_XTAL_RCO4M_CTRL__XTAL_DCKO_DRV_2PF  0
#define BG_XTAL_RCO4M_CTRL__XTAL_DCKO_DRV_20PF 3

/* RG_TSENSE_PWD: temperature sensor enable control */
#define MISC_CTRL0__TSENSE_DISABLE_BOTH  0
#define MISC_CTRL0__TSENSE_ENABLE_TSENS1 1
#define MISC_CTRL0__TSENSE_ENABLE_TSENS2 2
#define MISC_CTRL0__TSENSE_ENABLE_BOTH   3


/*RSSI Report Mode*/
#define RSSI_REPORT_MODE_THRESHOLD 2240  //  thresh = 70 dB , req = 5  -> 70*32 = 2304
#define RSSI_REPORT_REQ 5
#define SNR_REPORT_REQ 2

#define RSSI_CSR_FRACTION 12
#define DAGC_CSR_FRACTION 5

#define RSSI_REPORT_OFFSET 544 //  17*32
#define DECI_MAX_OUT_REPORT_OFFSET 256 //  8*32

/*LNA and PGA  Max gain*/
#define LNA_GAIN_MAX 42
#define PGA_GAIN_MAX 31

/* LNA gain control*/
#define LNA_GAIN_6_DB  12
#define LNA_GAIN_9_DB  11
#define LNA_GAIN_12_DB 10
#define LNA_GAIN_15_DB 9
#define LNA_GAIN_18_DB 8
#define LNA_GAIN_21_DB 7
#define LNA_GAIN_24_DB 6
#define LNA_GAIN_27_DB 5
#define LNA_GAIN_30_DB 4
#define LNA_GAIN_33_DB 3
#define LNA_GAIN_36_DB 2
#define LNA_GAIN_39_DB 1
#define LNA_GAIN_42_DB 0



/* PGA gain control*/
#define PGA_GAIN_0_DB  31
#define PGA_GAIN_1_DB  30
#define PGA_GAIN_2_DB  29
#define PGA_GAIN_3_DB  28
#define PGA_GAIN_4_DB  27
#define PGA_GAIN_5_DB  26
#define PGA_GAIN_6_DB  25
#define PGA_GAIN_7_DB  24
#define PGA_GAIN_8_DB  23
#define PGA_GAIN_9_DB  22
#define PGA_GAIN_10_DB 21
#define PGA_GAIN_11_DB 20
#define PGA_GAIN_12_DB 19
#define PGA_GAIN_13_DB 18
#define PGA_GAIN_14_DB 17
#define PGA_GAIN_15_DB 16
#define PGA_GAIN_16_DB 15
#define PGA_GAIN_17_DB 14
#define PGA_GAIN_18_DB 13
#define PGA_GAIN_19_DB 12
#define PGA_GAIN_20_DB 11
#define PGA_GAIN_21_DB 10
#define PGA_GAIN_22_DB 9
#define PGA_GAIN_23_DB 8
#define PGA_GAIN_24_DB 7
#define PGA_GAIN_25_DB 6
#define PGA_GAIN_26_DB 5
#define PGA_GAIN_27_DB 4
#define PGA_GAIN_28_DB 3
#define PGA_GAIN_29_DB 2
#define PGA_GAIN_30_DB 1
#define PGA_GAIN_31_DB 0

/* IF AGC search option*/
#define IF_AGC_BINARY_SEARCH 0
#define IF_AGC_DECREMENTAL_SEARCH 1

/* IF AGC decremental search gain step*/
#define IF_AGC_DECREMENTAL_SEARCH_GAIN_STEP_1_DB 0
#define IF_AGC_DECREMENTAL_SEARCH_GAIN_STEP_2_DB 1

/* Mixer out Attack point config */
#define MIXER_OUT_DATCK_ATTCK_MIN_MINIMUM   0
#define MIXER_OUT_DATCK_ATTCK_MIN_PLUS_1_DB 1
#define MIXER_OUT_DATCK_ATTCK_MIN_PLUS_2_DB 2
#define MIXER_OUT_DATCK_ATTCK_MIN_PLUS_3_DB 3    //default (3 or 5dBm)
#define MIXER_OUT_DATCK_ATTCK_MIN_PLUS_4_DB 4
#define MIXER_OUT_DATCK_ATTCK_MIN_PLUS_5_DB 5
#define MIXER_OUT_DATCK_ATTCK_MIN_PLUS_6_DB 6
#define MIXER_OUT_DATCK_ATTCK_MIN_PLUS_7_DB 7

/* PGA out Attack point config */
#define PGA_OUT_DATCK_ATTCK_MIN_MINIMUM   0
#define PGA_OUT_DATCK_ATTCK_MIN_PLUS_1_DB 1
#define PGA_OUT_DATCK_ATTCK_MIN_PLUS_2_DB 2
#define PGA_OUT_DATCK_ATTCK_MIN_PLUS_3_DB 3    //default (3 or 5dBm)
#define PGA_OUT_DATCK_ATTCK_MIN_PLUS_4_DB 4
#define PGA_OUT_DATCK_ATTCK_MIN_PLUS_5_DB 5
#define PGA_OUT_DATCK_ATTCK_MIN_PLUS_6_DB 6
#define PGA_OUT_DATCK_ATTCK_MIN_PLUS_7_DB 7

/* RXIF LPF VCM option  */
#define RXIF_LPF_VCM_OPTION_0P75_V 0
#define RXIF_LPF_VCM_OPTION_0P60_V 1

/* RXIF PGA VCM option  */
#define RXIF_PGA_VCM_OPTION_0P75_V 0
#define RXIF_PGA_VCM_OPTION_0P60_V 1


/* Field definition for ADC Loop filter */
#define MISC_CTRL0__RG_RXADC_LP24M_LP32M_EN_POS 23
#define MISC_CTRL0__RG_RXADC_LP24M_LP32M_EN_MASK (MISC_CTRL0__RG_RXADC_LP24M_EN_MASK \
	                                          | MISC_CTRL0__RG_RXADC_LP32M_EN_MASK)

/* ADC Loop filter setting ([RG_RXADC_LP32M_EN, RG_RXADC_LP24M_EN] =  00: 16M / 01: 24M / 10: 32M / 11:XX) */
#define ADC_LOOP_FILTER_16M 0
#define ADC_LOOP_FILTER_24M 1
#define ADC_LOOP_FILTER_32M 2


/*fields of PHY_AGC_CSR*/
#define PHY_AGC_LNA_MASK 0x000000FF
#define PHY_AGC_LNA_POS 0
#define PHY_AGC_PGA_MASK 0x0000FF00
#define PHY_AGC_PGA_POS 8
#define PHY_AGC_DAGC_MASK 0xFFFF0000
#define PHY_AGC_DAGC_POS 16


/*fields of _PHY_RSSI_CSR*/
#define PHY_RSSI_MASK 0x0000FFFF
#define PHY_RSSI_POS 0


/* RX ADC RCTUNE to Loop Filter */
#define FE_RX_ADC_RCTUNE_LOOP_FILTER_520KHz  0
#define FE_RX_ADC_RCTUNE_LOOP_FILTER_560KHz  1
#define FE_RX_ADC_RCTUNE_LOOP_FILTER_600kHz  2
#define FE_RX_ADC_RCTUNE_LOOP_FILTER_640kHz  3
#define FE_RX_ADC_RCTUNE_LOOP_FILTER_680kHz  4
#define FE_RX_ADC_RCTUNE_LOOP_FILTER_720kHz  5
#define FE_RX_ADC_RCTUNE_LOOP_FILTER_760kHz  6
#define FE_RX_ADC_RCTUNE_LOOP_FILTER_800kHz  7
#define FE_RX_ADC_RCTUNE_LOOP_FILTER_840kHz  8
#define FE_RX_ADC_RCTUNE_LOOP_FILTER_880kHz  9
#define FE_RX_ADC_RCTUNE_LOOP_FILTER_920kHz  10
#define FE_RX_ADC_RCTUNE_LOOP_FILTER_960kHz  11
#define FE_RX_ADC_RCTUNE_LOOP_FILTER_1000kHz 12
#define FE_RX_ADC_RCTUNE_LOOP_FILTER_1040kHz 13
#define FE_RX_ADC_RCTUNE_LOOP_FILTER_1080kHz 14
#define FE_RX_ADC_RCTUNE_LOOP_FILTER_1120kHz 15


/** Reg RESR16
Reserved Register 16
*/
#define PMU_CSR__ROM_RG5 PMU_CSR__RESR5

#define ROM_RG5__RX_SYNTH_ICPSEL_POS 0
#define ROM_RG5__RX_SYNTH_ICPSEL_MASK 0x0000001F

#define ROM_RG5__TX_SYNTH_ICPSEL_POS 5
#define ROM_RG5__TX_SYNTH_ICPSEL_MASK 0x000003E0

#define ROM_RG5__GEARSHIFT_EN_POS 10
#define ROM_RG5__GEARSHIFT_EN_MASK 0x00000400


#define ROM_RG5__ERR_PWR_EN_POS 11
#define ROM_RG5__ERR_PWR_EN_MASK 0x00000800

#define ROM_RG5__SLICER_ERR_THRESH_POS 12
#define ROM_RG5__SLICER_ERR_THRESH_MASK 0x00007000

#define ROM_RG5__SARADC_WAIT_TIME_POS 15
#define ROM_RG5__SARADC_WAIT_TIME_MASK 0x000F8000

#define ROM_RG5__ADC_CURSEL_OPINT_32M_POS 20
#define ROM_RG5__ADC_CURSEL_OPINT_32M_MASK 0x00300000

#define ROM_RG5__ADC_CURSEL_OPINT_16M_POS 22
#define ROM_RG5__ADC_CURSEL_OPINT_16M_MASK 0x00C00000

#define ROM_RG5__ADC_LGMODE_INT1_32M_POS 24
#define ROM_RG5__ADC_LGMODE_INT1_32M_MASK 0x01000000

#define ROM_RG5__ADC_LGMODE_INT1_16M_POS 25
#define ROM_RG5__ADC_LGMODE_INT1_16M_MASK 0x02000000

#define ROM_RG5__ADC_LPMODE_OPINT1_32M_POS 26
#define ROM_RG5__ADC_LPMODE_OPINT1_32M_MASK 0x04000000

#define ROM_RG5__ADC_LPMODE_OPINT1_16M_POS 27
#define ROM_RG5__ADC_LPMODE_OPINT1_16M_MASK 0x08000000

#define ROM_RG5__RXIF_BYP_32M_POS 28
#define ROM_RG5__RXIF_BYP_32M_MASK 0x10000000

#define ROM_RG5__RXIF_BYP_16M_POS 29
#define ROM_RG5__RXIF_BYP_16M_MASK 0x20000000

#define ROM_RG5__RXLPF_BYP_32M_POS 30
#define ROM_RG5__RXLPF_BYP_32M_MASK 0x40000000

#define ROM_RG5__RXLPF_BYP_16M_POS 31
#define ROM_RG5__RXLPF_BYP_16M_MASK 0x80000000



/*****************************************************************************/

/** Reg RESR19
Reserved Register 19
use for init rom code test
RG4
*/
#define PMU_CSR__ROM_RG4 PMU_CSR__RESR8

#define ROM_RG4__SYMBOL_RATE_POS 0
#define ROM_RG4__SYMBOL_RATE_MASK 0x0007FFFF

#define ROM_RG4__TX_H_COEFF_POS 19
#define ROM_RG4__TX_H_COEFF_MASK 0xFFF80000


/** Field csr_rsvd19

*/
#define RESR19__CSR_RSVD19_POS 0
#define RESR19__CSR_RSVD19_MASK 0xFFFFFFFF

/*****************************************************************************/
/** Reg RESR20
Reserved Register 20
use for init rom code test
RG3
*/
#define PMU_CSR__ROM_RG3 PMU_CSR__RESR9

#define ROM_RG3__TX_PA_MODE_CTRL_POS 0
#define ROM_RG3__TX_PA_MODE_CTRL_MASK 0x00000001

#define ROM_RG3__PMB_LEN_POS 1
#define ROM_RG3__PMB_LEN_MASK 0x00000FFE

#define ROM_RG3__ERR_CHK_POS 12
#define ROM_RG3__ERR_CHK_MASK 0x00001000

#define ROM_RG3__PHR_ERR_CHK_CODE_MODE_POS 13
#define ROM_RG3__PHR_ERR_CHK_CODE_MODE_MASK 0x00002000

#define ROM_RG3__GFILTER_BT_POS 14
#define ROM_RG3__GFILTER_BT_MASK 0x00004000

#define ROM_RG3__HAC_WAKE_UP_CODE_POS 15
#define ROM_RG3__HAC_WAKE_UP_CODE_MASK 0x000018000

#define ROM_RG3__PHY_CLOCK_POS 17
#define ROM_RG3__PHY_CLOCK_MASK 0x000020000

#define ROM_RG3__PRE_EMP_POS 18
#define ROM_RG3__PRE_EMP_MASK 0x000040000

#define ROM_RG3__PMB_MANUAL_CTRL_POS 19
#define ROM_RG3__PMB_MANUAL_CTRL_MASK 0x000080000

#define ROM_RG3__TX_FRAMER_DATA_OUT_CTRL_POS 20
#define ROM_RG3__TX_FRAMER_DATA_OUT_CTRL_MASK 0x00300000

#define ROM_RG3__HAC_TX_FRAMER_ONLY_WUC_POS 22
#define ROM_RG3__HAC_TX_FRAMER_ONLY_WUC_MASK 0x00400000

#define ROM_RG3__VTB_SOFT_DECISION_POS 23
#define ROM_RG3__VTB_SOFT_DECISION_MASK 0x00800000

#define ROM_RG3__TEMP_CHECK_TSEN_SEL_POS 24
#define ROM_RG3__TEMP_CHECK_TSEN_SEL_MASK 0x01000000

#define ROM_RG3__SYNTH_TXHIDATA_RET_POS 25
#define ROM_RG3__SYNTH_TXHIDATA_RET_MASK 0x02000000

#define ROM_RG3__RX_SYNTH_DRSEL_POS 26
#define ROM_RG3__RX_SYNTH_DRSEL_MASK 0x1C000000

#define ROM_RG3__TX_SYNTH_DRSEL_POS 29
#define ROM_RG3__TX_SYNTH_DRSEL_MASK 0xE0000000



/** Reg RESR22
Reserved Register 22
use for init rom code test
RG1
*/
#define PMU_CSR__ROM_RG1 PMU_CSR__RESR11


#define ROM_RG1__DECIM_FIR_P_SEL_POS 0
#define ROM_RG1__DECIM_FIR_P_SEL_MASK 0x0000000F

#define ROM_RG1__DECIM_FIR_D_SEL_POS 4
#define ROM_RG1__DECIM_FIR_D_SEL_MASK 0x000000F0

#define ROM_RG1__MS_EN_POS 8
#define ROM_RG1__MS_EN_MASK 0x00000100

#define ROM_RG1__WMBUS_MODE_SEL_POS 9
#define ROM_RG1__WMBUS_MODE_SEL_MASK 0x00000E00

//WMBUS_FORMAT: for WMBUS C mode,0=>format A 1=>format B
#define ROM_RG1__WMBUS_FORMAT_POS 12
#define ROM_RG1__WMBUS_FORMAT_MASK 0x00001000

#define ROM_RG1__WMBUS_DEVICE_POS 13
#define ROM_RG1__WMBUS_DEVICE_MASK 0x00002000

#define ROM_RG1__MFAGC_DOUBLE_POS 14
#define ROM_RG1__MFAGC_DOUBLE_MASK 0x00004000

#define ROM_RG1__PMB_LEN_BIT_PART_POS 15
#define ROM_RG1__PMB_LEN_BIT_PART_MASK 0x00038000

#define ROM_RG1__IQC_BISTPLL_OFFSET_STEP_POS 18
#define ROM_RG1__IQC_BISTPLL_OFFSET_STEP_MASK 0x000C0000


#define ROM_RG1__MODULATION_POS 20
#define ROM_RG1__MODULATION_MASK 0x00300000

#if Centauri_B2
#define ROM_RG1__LO_SIDE_INJ_POS 22
#define ROM_RG1__LO_SIDE_INJ_MASK 0x00400000

#define ROM_RG1__RX_16MHZ_EN_POS 23
#define ROM_RG1__RX_16MHZ_EN_MASK 0x00800000

#define ROM_RG1__FEC_DECODE_CTRL_POS 24
#define ROM_RG1__FEC_DECODE_CTRL_MASK 0x01000000

#define ROM_RG1__MRFSK_SEL_POS 25
#define ROM_RG1__MRFSK_SEL_MASK 0x02000000

#else

#define ROM_RG1__eLNA_THRESH_POS 22
#define ROM_RG1__eLNA_THRESH_MASK 0x03C00000

#define ROM_RG1__MRFSK_SEL_POS 31
#define ROM_RG1__MRFSK_SEL_MASK 0x80000000


#endif

//#define ROM_RG1__LO_SIDE_INJ_POS 22
//#define ROM_RG1__LO_SIDE_INJ_MASK 0x00400000

//#define ROM_RG1__RX_16MHZ_EN_POS 23
//#define ROM_RG1__RX_16MHZ_EN_MASK 0x00800000

//#define ROM_RG1__FEC_DECODE_CTRL_POS 24
//#define ROM_RG1__FEC_DECODE_CTRL_MASK 0x01000000

#define ROM_RG1__RX_SYNTH_DCBSEL_POS 26
#define ROM_RG1__RX_SYNTH_DCBSEL_MASK 0x7C000000


/** Reg RESR25
Reserved Register 25
Note : Use for RX-ADC and adc delay time
*/

#define PMU_CSR__RXADC_DACREFIQ PMU_CSR__RESR14

#define ROM_ADC__RXADC_DACREF_I_32M_POS 0
#define ROM_ADC__RXADC_DACREF_I_32M_MASK 0x0000000F

#define ROM_ADC__RXADC_DACREF_Q_32M_POS 4
#define ROM_ADC__RXADC_DACREF_Q_32M_MASK 0x000000F0

#define ROM_ADC__RXADC_DACREF_I_24M_POS 8
#define ROM_ADC__RXADC_DACREF_I_24M_MASK 0x00000F00

#define ROM_ADC__RXADC_DACREF_Q_24M_POS 12
#define ROM_ADC__RXADC_DACREF_Q_24M_MASK 0x0000F000

#define ROM_ADC__RXADC_DACREF_I_16M_POS 16
#define ROM_ADC__RXADC_DACREF_I_16M_MASK 0x000F0000

#define ROM_ADC__RXADC_DACREF_Q_16M_POS 20
#define ROM_ADC__RXADC_DACREF_Q_16M_MASK 0x00F00000

#define ROM_ADC__ADC_CLK_DELAY_POS 24
#define ROM_ADC__ADC_CLK_DELAY_MASK 0x0F000000

#define ROM_ADC__CHANNEL_INVALID_POS 28
#define ROM_ADC__CHANNEL_INVALID_MASK 0x10000000

#define ROM_ADC__WMBUS_EN_POS 29
#define ROM_ADC__WMBUS_EN_MASK 0x20000000

#define ROM_ADC__HAC_INVALID_POS 30
#define ROM_ADC__HAC_INVALID_MASK 0x40000000

#define ROM_ADC__600M_700M_DIS_POS 31
#define ROM_ADC__600M_700M_DIS_MASK 0x80000000


/*****************************************************************************/

/** Reg RESR21
Reserved Register 21
use for init rom code test
RG2
*/
#define PMU_CSR__ROM_RG2 PMU_CSR__RESR10

#define ROM_RG2__RF_IF_BAND_POS 0
#define ROM_RG2__RF_IF_BAND_MASK 0x0007FFFF

#define ROM_RG2__TX_PWR_GAIN_CODE_POS 19
#define ROM_RG2__TX_PWR_GAIN_CODE_MASK 0x00F80000

#define ROM_RG2__TX_PA_SEL_POS 24
#define ROM_RG2__TX_PA_SEL_MASK 0x01000000

#define ROM_RG2__SYNTH_DF3RDHI_RET_POS 25
#define ROM_RG2__SYNTH_DF3RDHI_RET_MASK 0x02000000

#define ROM_RG2__RX_SYNTH_DCZSEL_POS 26
#define ROM_RG2__RX_SYNTH_DCZSEL_MASK 0x1C000000

#define ROM_RG2__TX_SYNTH_DCZSEL_POS 29
#define ROM_RG2__TX_SYNTH_DCZSEL_MASK 0xE0000000




/** Reg RESR24
Reserved Register 24
 Note : Use for save iqc_coeffcient_C and Bist-PLL settle
*/

#define PMU_CSR__ROM_IQC2 PMU_CSR__RESR13

/* Field csr_rsvd24 */

#define ROM_IQC2_COEF_C_POS 0
#define ROM_IQC2_COEF_C_MASK 0x00007FFF

#define ROM_IQC2_LO_SIDE_INJ_POS 15
#define ROM_IQC2_LO_SIDE_INJ_MASK 0x00008000

#define ROM_IQC2_PGA_MAN_GAIN_VAL_POS 16
#define ROM_IQC2_PGA_MAN_GAIN_VAL_MASK 0x001F0000

#define ROM_IQC2_PGA_AUTO_DONE_POS 21
#define ROM_IQC2_PGA_AUTO_DONE_MASK 0x00200000

#define ROM_IQC2_CAL_EXTRA_WAIT_TIME_POS 22
#define ROM_IQC2_CAL_EXTRA_WAIT_TIME_MASK 0x00C00000

#define ROM_IQC2_CAL_WAIT_TIME1_POS 24
#define ROM_IQC2_CAL_WAIT_TIME1_MASK 0x01000000

#define ROM_IQC2_CAL_WAIT_TIME2_POS 25
#define ROM_IQC2_CAL_WAIT_TIME2_MASK 0x02000000

#define ROM_IQC2_CAL_STEP2_ALPHA_POS 26
#define ROM_IQC2_CAL_STEP2_ALPHA_MASK 0x04000000

/* Add here (for B2 ROM code) */
#define ROM_IQC2__TX_SYNTH_DCBSEL_POS 27
#define ROM_IQC2__TX_SYNTH_DCBSEL_MASK 0xF8000000



/*****************************************************************************/

/** Reg RESR3
Reserved Register 3
Note : Use for RF frequency
*/

#define PMU_CSR__RF_CHANNEL PMU_CSR__RESR3

#define RF_CHANNEL__RF_CHANNEL_FREQ_POS 0
#define RF_CHANNEL__RF_CHANNEL_FREQ_MASK 0x3FFFFFFF

#define RF_CHANNEL__FEC_DECODE_CTRL_POS 30
#define RF_CHANNEL__FEC_DECODE_CTRL_MASK 0x40000000

#define RF_CHANNEL__RX_16MHZ_EN_POS 31
#define RF_CHANNEL__RX_16MHZ_EN_MASK 0x80000000

/*****************/


extern void RfRxFeCalDigiGainCtrl(U8 digital_gain_ctrl);
extern void RfTxPaPwrOn(void);
extern void PhyRxAgcRestart(void);

extern void FePgaOutAttackPoint(U8 ifn_datck);
extern void FeRxLpfRctManual(void);
extern U8 RomTxPaModeRead(void);
extern void RomPmbLenSet(U16 pmb_len_set);
extern U32 RomSymRateRead(void);
extern void PhyRssiOffsetVal(U32 rssi_offset);
extern void IfRxDcocCapRgMode(void);
extern void FeRxIfDcocInBiasConfig(U8 val);
extern void FeRxIfDcocRoBiasConfig(U8 val);
extern void AdcReleaseReset(void);
extern void AdcReset(void);
extern void FeRxAdcIchQchDisable(void);
extern void FeRxAdcIchQchEnable(void);
extern void FeAdcClkEnable(void);
extern void IfRxIchQchEnable(void);
extern void RfRxFeTxRxSwitch(U8 tr_switch);
extern void FeLoPwrOn(void);
extern void RfRxPkDetIfwIfnPwrOnFeRxEnableFePwrOn(void);
extern U32 RomChannelInvalidRead(void);
extern void RomChannelInvalidSet(U32 input);
extern void RomPmbLenBitPartSet(U16 pmb_len_bit_set);
extern void RomTxPaModeSet(U8 txpa_mode_set);
extern void RomSynthTxHiDataRetSet(U32 input);
extern void PhyTxPreempEnable(void);
extern void RomPreEmpSet(U8 preemp_set);
extern U32 RomTxHcoeffRead(void);
extern void PhyTxPreempDisable(void);
extern U32 RomRx16MhzEnRead(void);
extern U32 RomMrfskSelRead(void);
extern U32 PhyRxMfAgcKdiffScValRead(void);
extern void PhyGaussianFilterBtSel(U8 bt);
extern void PhyBT05CompSet(U8 BT05Comp);
extern void PhyZcBlkTh(U32 input);
extern void PhyMfagcTapSel(U32 input);
extern U32 RomRfIfBandRead(void);
extern void IfRxLpfBandSel(U8 lpf_band_sel);
extern void PhyRxDecimFactorCtrl(U32 decim_factor_ctrl);
extern void PhyRxSamplePerSymbolConfig(U16 sps_val);
extern void PhyRxSpsSampleTimeSel(U16 sps_k_sel);
extern U32 RomMfagcDoubleRead(void);
extern void PhyRxMfAgcKdiffScVal(U32 kdiff_val);
extern void PhyRxMfAgcGainInitVal(U32 init_val);
extern void PhyRxFoDcrFactorSet(U32 dcr_factor);
extern U32 RomLowSideInjRead(void);
extern void PhyRxDigitalIfFreqOffsetConfig(U32 Digi_if_freq);
extern U32 RomPhyClockRead(void);
extern void Phy4fskThreshSet(U8 input);
extern void RomTxSynthDcbSelSet(U32 input);
extern void RomTxSynthDczSelSet(U32 input);
extern void RomTxSynthDrSelSet(U32 input);
extern void RomTxSynthIcPSelSet(U32 input);
extern void RomSynthDf3rdHiRetSet(U32 input);
extern void RfTxPaPwrDownCtrlAuto(void);
extern void RfTxPaDtpcCtrlManual(void);
extern void RfTxPaGainCtrl(U32 gain_val);
extern void RomTxPwrGainCodeSet(U32 tx_pwr_gain_code);
extern void PhyTxPreambleLenFraBitConfig(U16 len);
extern void PhyTxPreambleLenConfig(U16 len);
extern U32 RomTxPaPwrSelRead(void);
extern void RfTxPaPwrDown(void);
extern void PhySfdPattern0Config(U16 cfg);
extern void PhyPhrLenConfig(U16 tmp);
extern void PhyPhrRevConfig(U16 tmp);
extern void PhyPhrSkipFiledConfig(U16 tmp);
extern void PhyPhrDataWhiteningPN9SeqConfig(U16 tmp);
extern void PhyPhrDataWhiteningPN9ApplyConfig(U16 tmp);
extern void PhyPhrPsduOrderConfig(U16 tmp);
extern void PhyPhrCECStandardConfig(U16 tmp);
extern void PhyGaussianFilterConfig(U16 tmp);
extern void PhyDataWhiteningConfig(U16 tmp);
extern void PhyExtraPsduConfig(U16 tmp);
extern void PhyChannelBandConfig(U32 new_chan_band);
extern U32 RomRfChannelRead(void);
extern void PhyFecEnable(void);
extern void PhyFecDisable(void);
extern void PhyFecTypeSel(U8 fec_type);
extern void PhyRxFecDecodeCtrlMode(U8 ctrl_mode);
extern void PhyInterleaverEnable(void);
extern void PhyInterleaverDisable(void);
extern void PhyRxVtbDecodeSoftEnable(void);
extern void PhyRxVtbDecodeSoftDisable(void);
extern void RomFecDecodeCtrlSet(U32 fec_decode_ctrl);
extern U32 PhyInterleaverRead(void);
extern U32 PhyDataWhiteningRead(void);
extern void RfLdo12vCOvREF(U32 vref);
extern void PhyInBandRssiCalcuShift(U32 rssi_cal_sh);
extern U32 PhyRssiOffsetRead(void);

#ifdef __cplusplus
}
#endif

#endif /* TRANSCEIVERCSR_H */
