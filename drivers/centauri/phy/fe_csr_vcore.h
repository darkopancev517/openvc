#ifndef FE_CSR_VCORE_H
#define FE_CSR_VCORE_H

#ifdef __cplusplus
extern "C" {
#endif

#ifndef CSR_ACCESS
#define CSR_ACCESS(x) (*((volatile unsigned long *)(x)))
#endif

/** Block fe_csr_vcore

*/
#define FE_CSR_VCORE_BASE 0x40028000

/*****************************************************************************/

/** Reg pll_ctrl
PLL control
*/
#define FE_CSR_VCORE__PLL_CTRL CSR_ACCESS(FE_CSR_VCORE_BASE + 0x00000000)

/** Field RG_PLL_CKMON_EN
PLL montior clock
0: disable
1: enable
*/
#define PLL_CTRL__RG_PLL_CKMON_EN_POS 0
#define PLL_CTRL__RG_PLL_CKMON_EN_MASK 0x00000001

/** Field RG_PLL_DIGCK_SEL
00 : 64MHz
01 : 32MHz
10 : 24MHz
11 : 16MHz
*/
#define PLL_CTRL__RG_PLL_DIGCK_SEL_POS 1
#define PLL_CTRL__RG_PLL_DIGCK_SEL_MASK 0x00000006

/** Field RG_PLL_FBKDIV
PLL feedback divider: 8 ~ 63
001000: /8
001001: /9
     .
     .
111111: /63
*/
#define PLL_CTRL__RG_PLL_FBKDIV_POS 3
#define PLL_CTRL__RG_PLL_FBKDIV_MASK 0x000001F8

/** Field RG_PLL_IC
PLL CP IC current sel
00: forbiden
01: 2.5uA
10: 5uA
11: 7.5uA
(default value: 01)
*/
#define PLL_CTRL__RG_PLL_IC_POS 9
#define PLL_CTRL__RG_PLL_IC_MASK 0x00000600

/** Field RG_PLL_INJ_EN
No use
*/
#define PLL_CTRL__RG_PLL_INJ_EN_POS 11
#define PLL_CTRL__RG_PLL_INJ_EN_MASK 0x00000800

/** Field RG_PLL_IR
PLL CP IR current sel
00: forbiden
01: 12.5uA
10: 25uA
11: 37.5uA
(default value: 10)
*/
#define PLL_CTRL__RG_PLL_IR_POS 12
#define PLL_CTRL__RG_PLL_IR_MASK 0x00003000

/** Field RG_PLL_MOSLPF_EN
MOS resistor LPF enable
0: disable
1: enable
*/
#define PLL_CTRL__RG_PLL_MOSLPF_EN_POS 14
#define PLL_CTRL__RG_PLL_MOSLPF_EN_MASK 0x00004000

/** Field RG_PLL_OP_RSTB
MOS resistor LPF in Opamp  enable
0: disable
1: enable
*/
#define PLL_CTRL__RG_PLL_OP_RSTB_POS 15
#define PLL_CTRL__RG_PLL_OP_RSTB_MASK 0x00008000

/** Field RG_PLL_PC
PLL pole cap sel
0000: forbiden
0001: 100f
0010: 200f
0011: 300f
       :
1110: 1.4pf
1111: 1.5pf
(default value: 1010)
*/
#define PLL_CTRL__RG_PLL_PC_POS 16
#define PLL_CTRL__RG_PLL_PC_MASK 0x000F0000

/** Field RG_PLL_PR
PLL pole res sel
00: 15K
01: 14K
10: 13K
11: 12K
(default value: 00)
*/
#define PLL_CTRL__RG_PLL_PR_POS 20
#define PLL_CTRL__RG_PLL_PR_MASK 0x00300000

/** Field RG_PLL_PREDIV
PLL pre-divider control
00: /1
01: /2
10: forbiden
11: /4
(default value: 00)
*/
#define PLL_CTRL__RG_PLL_PREDIV_POS 22
#define PLL_CTRL__RG_PLL_PREDIV_MASK 0x00C00000

/** Field RG_PLL_VCMON_EN
PLL Vctrl voltage monitor enable
0: disable
1: enable
(default value: 0)
*/
#define PLL_CTRL__RG_PLL_VCMON_EN_POS 24
#define PLL_CTRL__RG_PLL_VCMON_EN_MASK 0x01000000

/** Field RG_PLL_ZC
PLL zero cap sel
000: forbiden
001: 0.6pf
010: 1.2pf 
011: 1.8pf
100: 2pf
101: 2.6pf
110: 3.2pf
111: 3.8pf
(default value: 101)
*/
#define PLL_CTRL__RG_PLL_ZC_POS 25
#define PLL_CTRL__RG_PLL_ZC_MASK 0x0E000000

/** Field RG_PLL_ADCK_EN
ADC clock output control
0 : disable clock to ADC
1 : enable clock to ADC
*/
#define PLL_CTRL__RG_PLL_ADCK_EN_POS 28
#define PLL_CTRL__RG_PLL_ADCK_EN_MASK 0x10000000

/** Field RG_PLL_BBPCK_EN
BBP clock output control
0 : disable clock to BBP
1 : enable clock to BBP
*/
#define PLL_CTRL__RG_PLL_BBPCK_EN_POS 29
#define PLL_CTRL__RG_PLL_BBPCK_EN_MASK 0x20000000

/*****************************************************************************/

/** Reg rfrx_ctrl0
RX RF front-end and IF control
*/
#define FE_CSR_VCORE__RFRX_CTRL0 CSR_ACCESS(FE_CSR_VCORE_BASE + 0x00000004)

/** Field RG_RFRXFE_CAL_DIGC
Digital gain control of on-chip generated calibration signal for I/Q-cal loop 
*/
#define RFRX_CTRL0__RG_RFRXFE_CAL_DIGC_POS 0
#define RFRX_CTRL0__RG_RFRXFE_CAL_DIGC_MASK 0x00000003

/** Field RG_RFRXFE_CAL_EN
Enable control for RXFE of I/Q calibration loop, active high
*/
#define RFRX_CTRL0__RG_RFRXFE_CAL_EN_POS 2
#define RFRX_CTRL0__RG_RFRXFE_CAL_EN_MASK 0x00000004

/** Field RG_RFRXFE_LNA_DBC
Digital control of LNA bias current 
*/
#define RFRX_CTRL0__RG_RFRXFE_LNA_DBC_POS 3
#define RFRX_CTRL0__RG_RFRXFE_LNA_DBC_MASK 0x00000018

/** Field RG_RFRXFE_LNA_DIGC
Digital gain control of variable gain LNA with gain step=3dB in total of 13 steps. Max gain=0000
*/
#define RFRX_CTRL0__RG_RFRXFE_LNA_DIGC_POS 5
#define RFRX_CTRL0__RG_RFRXFE_LNA_DIGC_MASK 0x000001E0

/** Field RG_RFRXFE_MXR_DIGC
Digital gain control of mixer. This setting is used for tuning performance only. Not used in AGC loop.
*/
#define RFRX_CTRL0__RG_RFRXFE_MXR_DIGC_POS 9
#define RFRX_CTRL0__RG_RFRXFE_MXR_DIGC_MASK 0x00000600

/** Field RG_RFRXFE_PWD
Power down control. Active high.
*/
#define RFRX_CTRL0__RG_RFRXFE_PWD_POS 11
#define RFRX_CTRL0__RG_RFRXFE_PWD_MASK 0x00000800

/** Field RG_RFRXFE_RX_EN
RX RF front-end enable control. Active high
*/
#define RFRX_CTRL0__RG_RFRXFE_RX_EN_POS 12
#define RFRX_CTRL0__RG_RFRXFE_RX_EN_MASK 0x00001000

/** Field RG_PKDETIFN_DATCK
Digital attack point setting at PGA output. 1dB/step.
*/
#define RFRX_CTRL0__RG_PKDETIFN_DATCK_POS 13
#define RFRX_CTRL0__RG_PKDETIFN_DATCK_MASK 0x0000E000

/** Field RG_PKDETIFN_DVTHRSEL
Value setting for lowest attack point at 000. 0 for 0dBm; 1 for 2dBm
*/
#define RFRX_CTRL0__RG_PKDETIFN_DVTHRSEL_POS 16
#define RFRX_CTRL0__RG_PKDETIFN_DVTHRSEL_MASK 0x00010000

/** Field RG_PKDETIFN_PWD
Power down control. Active high.
*/
#define RFRX_CTRL0__RG_PKDETIFN_PWD_POS 17
#define RFRX_CTRL0__RG_PKDETIFN_PWD_MASK 0x00020000

/** Field RG_PKDETIFW_DATCK
Digital attack point settting at mixer output. 1dB/step
*/
#define RFRX_CTRL0__RG_PKDETIFW_DATCK_POS 18
#define RFRX_CTRL0__RG_PKDETIFW_DATCK_MASK 0x001C0000

/** Field RG_PKDETIFW_DVTHRSEL
Value setting for lowest attack point at 000. 0 for 0dBm; 1 for 2dBm
*/
#define RFRX_CTRL0__RG_PKDETIFW_DVTHRSEL_POS 21
#define RFRX_CTRL0__RG_PKDETIFW_DVTHRSEL_MASK 0x00200000

/** Field RG_PKDETIFW_PWD
Power down control. Active high.
*/
#define RFRX_CTRL0__RG_PKDETIFW_PWD_POS 22
#define RFRX_CTRL0__RG_PKDETIFW_PWD_MASK 0x00400000

/** Field RGR_PKDETIFN_FLAG
Flag high for PGA output signal level exceeding a selected threshold voltage
*/
#define RFRX_CTRL0__RGR_PKDETIFN_FLAG_POS 23
#define RFRX_CTRL0__RGR_PKDETIFN_FLAG_MASK 0x00800000

/** Field RGR_PKDETIFW_FLAG
Flag high for RF mixer output signal level exceeding a selected threshold voltage
*/
#define RFRX_CTRL0__RGR_PKDETIFW_FLAG_POS 24
#define RFRX_CTRL0__RGR_PKDETIFW_FLAG_MASK 0x01000000

/** Field RG_RFRXFE_LNA_DIGC_MAN
LNA gain control from auto AGC or manual
0 : auto(default)
1 : manual
*/
#define RFRX_CTRL0__RG_RFRXFE_LNA_DIGC_MAN_POS 25
#define RFRX_CTRL0__RG_RFRXFE_LNA_DIGC_MAN_MASK 0x02000000

/** Field RG_RXPGA_GAIN_MAN
PGA gain control from auto AGC or manual
0 : auto(default)
1 : manual
*/
#define RFRX_CTRL0__RG_RXPGA_GAIN_MAN_POS 26
#define RFRX_CTRL0__RG_RXPGA_GAIN_MAN_MASK 0x04000000

/*****************************************************************************/

/** Reg ifrx_ctrl
RX IF I/Q control
*/
#define FE_CSR_VCORE__IFRX_CTRL CSR_ACCESS(FE_CSR_VCORE_BASE + 0x00000008)

/** Field RG_RXIFI_PWD
RXIF I-ch path power down 
0: enable RXIF I-ch
1: power down RXIF  I-ch
*/
#define IFRX_CTRL__RG_RXIFI_PWD_POS 0
#define IFRX_CTRL__RG_RXIFI_PWD_MASK 0x00000001

/** Field RG_RXIFQ_PWD
RXIF Q-ch path power down
0: enable RXIF Q-ch
1: power down RXIF Q-ch 
*/
#define IFRX_CTRL__RG_RXIFQ_PWD_POS 1
#define IFRX_CTRL__RG_RXIFQ_PWD_MASK 0x00000002

/** Field RG_RXIF_RSV
RXIF PGA DCOC Cap Control Mode
0: Gain dependent mode
1: RG control mode
*/
#define IFRX_CTRL__RG_RXIF_RSV_POS 2
#define IFRX_CTRL__RG_RXIF_RSV_MASK 0x00000004

/** Field RG_RXPGA_DCOC_PWD
RXIFPGA DC offset cancellation power down 
0: enable DCOC
1: disable DCOC 
*/
#define IFRX_CTRL__RG_RXPGA_DCOC_PWD_POS 8
#define IFRX_CTRL__RG_RXPGA_DCOC_PWD_MASK 0x00000100

/** Field RG_RXPGA_GAIN
RXIF PGA GAIN setting
00000:31dB
00001:30dB
00010:29dB
*
*
11111:0dB
*/
#define IFRX_CTRL__RG_RXPGA_GAIN_POS 9
#define IFRX_CTRL__RG_RXPGA_GAIN_MASK 0x00003E00

/** Field RG_RXLPF_BAND
RXIF LPF low-pass band frequecny selection (-1dB)
000: 220kHz
001: 330kHz
010: 440kHz
011: 550kHz
100: 600kHz
101: 660kHz
110: 770kHz
111: 880kHz
*/
#define IFRX_CTRL__RG_RXLPF_BAND_POS 26
#define IFRX_CTRL__RG_RXLPF_BAND_MASK 0x1C000000

/*****************************************************************************/

/** Reg rxadc_ctrl0
RX ADCI control
*/
#define FE_CSR_VCORE__RXADC_CTRL0 CSR_ACCESS(FE_CSR_VCORE_BASE + 0x0000000C)

/** Field RG_RXADC_CKSEL
ADC sample clock select
00: 24MHz
01: 32MHz
10: No use
11: 16MHz
*/
#define RXADC_CTRL0__RG_RXADC_CKSEL_POS 0
#define RXADC_CTRL0__RG_RXADC_CKSEL_MASK 0x00000003

/** Field RG_RXADC_CURSEL_OPINT
1st OPAMP bias current
00: -30%
01: -15%
10: Default
11: +15% 
*/
#define RXADC_CTRL0__RG_RXADC_CURSEL_OPINT_POS 2
#define RXADC_CTRL0__RG_RXADC_CURSEL_OPINT_MASK 0x0000000C

/** Field RG_RXLPF_RCT_MAN
low pass filter RCT manual mode
0: Auto mode 
1: manual mode
*/
#define RXADC_CTRL0__RG_RXLPF_RCT_MAN_POS 4
#define RXADC_CTRL0__RG_RXLPF_RCT_MAN_MASK 0x00000010

/** Field RG_RXLPF_RCT

*/
#define RXADC_CTRL0__RG_RXLPF_RCT_POS 5
#define RXADC_CTRL0__RG_RXLPF_RCT_MASK 0x000001E0

/** Field RG_RXADC_LGMODE_INT1
ADC INT1 Low-GM mode
0: disable
1: enable
*/
#define RXADC_CTRL0__RG_RXADC_LGMODE_INT1_POS 11
#define RXADC_CTRL0__RG_RXADC_LGMODE_INT1_MASK 0x00000800

/** Field RG_RXADC_LPMODE_OPINT1
ADC INT1 Low-power mode
0: disable
1: enable
*/
#define RXADC_CTRL0__RG_RXADC_LPMODE_OPINT1_POS 13
#define RXADC_CTRL0__RG_RXADC_LPMODE_OPINT1_MASK 0x00002000

/** Field RG_RXADC_OPINT_PWD
ADC OPINT POWER DOWN,STAGE1~3
000: all opamp enable
001: Stage3 opamp power down
010: Stage2 opamp power down
100: Stage1 opamp power down
111: Stage1 ~3 opamp power down
*/
#define RXADC_CTRL0__RG_RXADC_OPINT_PWD_POS 15
#define RXADC_CTRL0__RG_RXADC_OPINT_PWD_MASK 0x00038000

/** Field RG_RXADC_QTZ_DOMINO_EN
Quantizer domino function enable
0: disable
1: enable
*/
#define RXADC_CTRL0__RG_RXADC_QTZ_DOMINO_EN_POS 18
#define RXADC_CTRL0__RG_RXADC_QTZ_DOMINO_EN_MASK 0x00040000

/** Field RG_RXADC_RCT_PWD
RCTUNE power down
0: enable (default) shut down before normal work
1: power down
*/
#define RXADC_CTRL0__RG_RXADC_RCT_PWD_POS 19
#define RXADC_CTRL0__RG_RXADC_RCT_PWD_MASK 0x00080000

/** Field RG_RXADC_RCT_LF
RCTUNE to loop filter
0000: 560kHz
0001: 600kHz
0010: 640kHz
0011: 680kHz
0100: 720kHz
0101: 760kHz
0111: 800kHz
1000: 840kHz
1001: 880kHz
1010: 920kHz
1011: 960kHz
1100: 1000kHz
1101: 1040kHz
1110: 1080kHz
1111: 1120kHz
*/
#define RXADC_CTRL0__RG_RXADC_RCT_LF_POS 20
#define RXADC_CTRL0__RG_RXADC_RCT_LF_MASK 0x00F00000

/** Field RG_RXADC_RDAC_TUNE
TUNE DAC feedback resistor
00: 10k
01: 15k
10: 20k
11: 25k
*/
#define RXADC_CTRL0__RG_RXADC_RDAC_TUNE_POS 24
#define RXADC_CTRL0__RG_RXADC_RDAC_TUNE_MASK 0x03000000

/** Field RG_RXADC_RST_INT
Loop filter reset
0: no reset
1: reset
*/
#define RXADC_CTRL0__RG_RXADC_RST_INT_POS 26
#define RXADC_CTRL0__RG_RXADC_RST_INT_MASK 0x04000000

/** Field RG_RXADC_VCM_PWD
ADC VCM BUFFER power down
0: enable
1: power down
*/
#define RXADC_CTRL0__RG_RXADC_VCM_PWD_POS 28
#define RXADC_CTRL0__RG_RXADC_VCM_PWD_MASK 0x10000000

/*****************************************************************************/

/** Reg 
RX ADCQ control
*/
#define FE_CSR_VCORE__ CSR_ACCESS(FE_CSR_VCORE_BASE + 0x00000010)

/*****************************************************************************/

/** Reg synth_ctrl0

*/
#define FE_CSR_VCORE__SYNTH_CTRL0 CSR_ACCESS(FE_CSR_VCORE_BASE + 0x00000014)

/** Field RG_SYNTH_PWD
Power down control for RF synthesizer, active high
*/
#define SYNTH_CTRL0__RG_SYNTH_PWD_POS 0
#define SYNTH_CTRL0__RG_SYNTH_PWD_MASK 0x00000001

/** Field RG_SYNTH_DCBSEL
Programmable bits for bypass cap of loop filter
*/
#define SYNTH_CTRL0__RG_SYNTH_DCBSEL_POS 1
#define SYNTH_CTRL0__RG_SYNTH_DCBSEL_MASK 0x0000003E

/** Field RG_SYNTH_DCZSEL
Programmable bits for ZERO cap of loop filter
*/
#define SYNTH_CTRL0__RG_SYNTH_DCZSEL_POS 6
#define SYNTH_CTRL0__RG_SYNTH_DCZSEL_MASK 0x000007C0

/** Field RG_SYNTH_DF3RDHI_EN
Selection of 3rd-order pole frequency of loop filter: 1 for higher pole frequency; 0 for lower freq
*/
#define SYNTH_CTRL0__RG_SYNTH_DF3RDHI_EN_POS 11
#define SYNTH_CTRL0__RG_SYNTH_DF3RDHI_EN_MASK 0x00000800

/** Field RG_SYNTH_DLSEL
Selection of PFD's feedback loop delay. Default value: 1 for VCO1 and 2 for VCO2
*/
#define SYNTH_CTRL0__RG_SYNTH_DLSEL_POS 12
#define SYNTH_CTRL0__RG_SYNTH_DLSEL_MASK 0x00007000

/** Field RG_SYNTH_DPIVCO
Selection of VCO gm-device current bias control
*/
#define SYNTH_CTRL0__RG_SYNTH_DPIVCO_POS 15
#define SYNTH_CTRL0__RG_SYNTH_DPIVCO_MASK 0x00038000

/** Field RG_SYNTH_DRSEL
Programmable bits for resistance of loop filter
*/
#define SYNTH_CTRL0__RG_SYNTH_DRSEL_POS 18
#define SYNTH_CTRL0__RG_SYNTH_DRSEL_MASK 0x001C0000

/** Field RG_SYNTH_TXHIDATA_EN
Tx high data rate enable
*/
#define SYNTH_CTRL0__RG_SYNTH_TXHIDATA_EN_POS 21
#define SYNTH_CTRL0__RG_SYNTH_TXHIDATA_EN_MASK 0x00200000

/** Field RG_SYNTH_VBUF_EN
Measure Kvco buffer enable
*/
#define SYNTH_CTRL0__RG_SYNTH_VBUF_EN_POS 22
#define SYNTH_CTRL0__RG_SYNTH_VBUF_EN_MASK 0x00400000

/** Field RG_SYNTH_DVREFSEL
Selection of reference voltage for VCO voltage bias
*/
#define SYNTH_CTRL0__RG_SYNTH_DVREFSEL_POS 23
#define SYNTH_CTRL0__RG_SYNTH_DVREFSEL_MASK 0x01800000

/** Field RG_SYNTH_HFVCOSEL_EN
Program one of 2 VCOs; 1 for VCO1, higher oscillation frequency; 0 for VCO2, lower oscillation frequency
*/
#define SYNTH_CTRL0__RG_SYNTH_HFVCOSEL_EN_POS 25
#define SYNTH_CTRL0__RG_SYNTH_HFVCOSEL_EN_MASK 0x02000000

/** Field RG_SYNTH_ICPSEL
Programmable control bits for charge pump current
*/
#define SYNTH_CTRL0__RG_SYNTH_ICPSEL_POS 26
#define SYNTH_CTRL0__RG_SYNTH_ICPSEL_MASK 0xFC000000

/*****************************************************************************/

/** Reg synth_ctrl1

*/
#define FE_CSR_VCORE__SYNTH_CTRL1 CSR_ACCESS(FE_CSR_VCORE_BASE + 0x00000018)

/** Field RG_DDSM_EN
Enable control for DDSM, active high
*/
#define SYNTH_CTRL1__RG_DDSM_EN_POS 0
#define SYNTH_CTRL1__RG_DDSM_EN_MASK 0x00000001

/** Field RG_DDSM_TEST
Enable control for entering DDSM test mode, active high
*/
#define SYNTH_CTRL1__RG_DDSM_TEST_POS 1
#define SYNTH_CTRL1__RG_DDSM_TEST_MASK 0x00000002

/** Field RG_DDSM_TESTI
Input value to be written into DDSM during test mode
*/
#define SYNTH_CTRL1__RG_DDSM_TESTI_POS 2
#define SYNTH_CTRL1__RG_DDSM_TESTI_MASK 0x000000FC

/** Field RG_VCOCAL_EN
Enable control for VCO calibration function
*/
#define SYNTH_CTRL1__RG_VCOCAL_EN_POS 8
#define SYNTH_CTRL1__RG_VCOCAL_EN_MASK 0x00000100

/** Field RG_VCOCAL_DTUNE
VCO digital tuning bits to select one out of 64 VCO transfer curves
*/
#define SYNTH_CTRL1__RG_VCOCAL_DTUNE_POS 9
#define SYNTH_CTRL1__RG_VCOCAL_DTUNE_MASK 0x00007E00

/** Field RG_VCOCAL_DTUNE_MAN
Input value to be written to over-write VCO calibration output value when in manual mode
*/
#define SYNTH_CTRL1__RG_VCOCAL_DTUNE_MAN_POS 15
#define SYNTH_CTRL1__RG_VCOCAL_DTUNE_MAN_MASK 0x00008000

/** Field RG_VCOCAL_I3DELTA
Selection of convergent accuracy of VCO calibration
*/
#define SYNTH_CTRL1__RG_VCOCAL_I3DELTA_POS 16
#define SYNTH_CTRL1__RG_VCOCAL_I3DELTA_MASK 0x00070000

/** Field RG_VCOCAL_TEST
Enable control for entering VCO calibration test mode, active high
*/
#define SYNTH_CTRL1__RG_VCOCAL_TEST_POS 19
#define SYNTH_CTRL1__RG_VCOCAL_TEST_MASK 0x00080000

/** Field RGR_VCOCAL_DONE
Flag indicating whether RF synthesizer VCO calibration is done
*/
#define SYNTH_CTRL1__RGR_VCOCAL_DONE_POS 20
#define SYNTH_CTRL1__RGR_VCOCAL_DONE_MASK 0x00100000

/** Field RGR_VCOCAL_DTUNE
DTUNE value reported 
*/
#define SYNTH_CTRL1__RGR_VCOCAL_DTUNE_POS 21
#define SYNTH_CTRL1__RGR_VCOCAL_DTUNE_MASK 0x07E00000

/** Field RGR_VCOCAL_FAIL
Flag indicating whether VCO calibration meets the target calibration accuracy
*/
#define SYNTH_CTRL1__RGR_VCOCAL_FAIL_POS 27
#define SYNTH_CTRL1__RGR_VCOCAL_FAIL_MASK 0x08000000

/** Field RG_DDSMVCOCAL_RSTB
Reset for digital VCO calibration block; active low
*/
#define SYNTH_CTRL1__RG_DDSMVCOCAL_RSTB_POS 28
#define SYNTH_CTRL1__RG_DDSMVCOCAL_RSTB_MASK 0x10000000

/*****************************************************************************/

/** Reg lo_ctrl

*/
#define FE_CSR_VCORE__LO_CTRL CSR_ACCESS(FE_CSR_VCORE_BASE + 0x0000001C)

/** Field RG_LO_PWD
Power down control for LO path
*/
#define LO_CTRL__RG_LO_PWD_POS 0
#define LO_CTRL__RG_LO_PWD_MASK 0x00000001

/** Field RG_LO_BSEL
Progammable RF band selection: 00, high-band; 01 mid-band; 10 low band; 11 none 
*/
#define LO_CTRL__RG_LO_BSEL_POS 1
#define LO_CTRL__RG_LO_BSEL_MASK 0x00000006

/** Field RG_LO_RXSEL
Programmble mode control. 1 for RX; 0 TX
*/
#define LO_CTRL__RG_LO_RXSEL_POS 3
#define LO_CTRL__RG_LO_RXSEL_MASK 0x00000008

/*****************************************************************************/

/** Reg bistpll_ctrl0

*/
#define FE_CSR_VCORE__BISTPLL_CTRL0 CSR_ACCESS(FE_CSR_VCORE_BASE + 0x00000020)

/** Field RG_BISTPLL_CKMON_EN
BISTPLL montior clock
0: disable
1: enable
*/
#define BISTPLL_CTRL0__RG_BISTPLL_CKMON_EN_POS 0
#define BISTPLL_CTRL0__RG_BISTPLL_CKMON_EN_MASK 0x00000001

/** Field RG_BISTPLL_PR
BISTPLL pole res sel
00: 17K
01: 16K
10: 15K
11: 14K
(default value: 10)
*/
#define BISTPLL_CTRL0__RG_BISTPLL_PR_POS 1
#define BISTPLL_CTRL0__RG_BISTPLL_PR_MASK 0x00000006

/** Field RG_BISTPLL_ZC
BISTPLL zero cap sel
000: forbiden
001: 0.6pf
010: 1.2pf 
011: 1.8pf
100: 2pf
101: 2.6pf
110: 3.2pf
111: 3.8pf
(default value: 101)
*/
#define BISTPLL_CTRL0__RG_BISTPLL_ZC_POS 3
#define BISTPLL_CTRL0__RG_BISTPLL_ZC_MASK 0x00000038

/** Field RG_BISTPLL_VCMON_EN
BISTPLL Vctrl voltage monitor enable
0: disable
1: enable
(default value: 0)
*/
#define BISTPLL_CTRL0__RG_BISTPLL_VCMON_EN_POS 6
#define BISTPLL_CTRL0__RG_BISTPLL_VCMON_EN_MASK 0x00000040

/** Field RG_BISTPLL_FM_WIN
BISTPLL calibration resolution:
000: 0.25MHz
001: 0.5MHz
010: 0.75MHz
011: 1MHz
100: 1.25MHz
101: 1.5MHz
110: 1.75MHz
111: 2MHz
*/
#define BISTPLL_CTRL0__RG_BISTPLL_FM_WIN_POS 7
#define BISTPLL_CTRL0__RG_BISTPLL_FM_WIN_MASK 0x00000380

/** Field RG_BISTPLL_IBAND
BISTPLL IBAND code input
*/
#define BISTPLL_CTRL0__RG_BISTPLL_IBAND_POS 10
#define BISTPLL_CTRL0__RG_BISTPLL_IBAND_MASK 0x00007C00

/** Field RG_BISTPLL_IBAND_BINARY
BISTPLL IBAND cal method
0: thermal search
1: binary search
*/
#define BISTPLL_CTRL0__RG_BISTPLL_IBAND_BINARY_POS 15
#define BISTPLL_CTRL0__RG_BISTPLL_IBAND_BINARY_MASK 0x00008000

/** Field RG_BISTPLL_IBAND_MANUAL
BISTPLL IBAND code select
0: from digital cal
1: manual input
*/
#define BISTPLL_CTRL0__RG_BISTPLL_IBAND_MANUAL_POS 16
#define BISTPLL_CTRL0__RG_BISTPLL_IBAND_MANUAL_MASK 0x00010000

/** Field RG_BISTPLL_IC
BISTPLL CP IC current sel
00: forbiden
01: 7.5uA
10: 10uA
11: 17.5uA
(default value: 10)
*/
#define BISTPLL_CTRL0__RG_BISTPLL_IC_POS 17
#define BISTPLL_CTRL0__RG_BISTPLL_IC_MASK 0x00060000

/** Field RG_BISTPLL_INJ_EN
no use
*/
#define BISTPLL_CTRL0__RG_BISTPLL_INJ_EN_POS 19
#define BISTPLL_CTRL0__RG_BISTPLL_INJ_EN_MASK 0x00080000

/** Field RG_BISTPLL_IR
BISTPLL CP IR current sel
00: forbiden
01: 50uA
10: 100uA
11: 150uA
(default value: 10)
*/
#define BISTPLL_CTRL0__RG_BISTPLL_IR_POS 20
#define BISTPLL_CTRL0__RG_BISTPLL_IR_MASK 0x00300000

/** Field RG_BISTPLL_MODE768M_SEL
BISTPLL freq mode sel:
0: dis
1: sel
*/
#define BISTPLL_CTRL0__RG_BISTPLL_MODE768M_SEL_POS 22
#define BISTPLL_CTRL0__RG_BISTPLL_MODE768M_SEL_MASK 0x00400000

/** Field RG_BISTPLL_MODE864M_SEL
BISTPLL freq mode sel:
0: dis
1: sel
*/
#define BISTPLL_CTRL0__RG_BISTPLL_MODE864M_SEL_POS 23
#define BISTPLL_CTRL0__RG_BISTPLL_MODE864M_SEL_MASK 0x00800000

/** Field RG_BISTPLL_MODE960M_SEL
BISTPLL freq mode sel:
0: dis
1: sel
*/
#define BISTPLL_CTRL0__RG_BISTPLL_MODE960M_SEL_POS 24
#define BISTPLL_CTRL0__RG_BISTPLL_MODE960M_SEL_MASK 0x01000000

/** Field RG_BISTPLL_MOSLPF_EN
MOS resistor LPF enable
0: disable
1: enable
*/
#define BISTPLL_CTRL0__RG_BISTPLL_MOSLPF_EN_POS 25
#define BISTPLL_CTRL0__RG_BISTPLL_MOSLPF_EN_MASK 0x02000000

/** Field RG_BISTPLL_OP_RSTB
MOS resistor LPF in Opamp  enable
0: disable
1: enable
*/
#define BISTPLL_CTRL0__RG_BISTPLL_OP_RSTB_POS 26
#define BISTPLL_CTRL0__RG_BISTPLL_OP_RSTB_MASK 0x04000000

/** Field RG_BISTPLL_PC
BISTPLL pole cap sel
0000: forbiden
0001: 100f
0010: 200f
0011: 300f
       :
1110: 1.4pf
1111: 1.5pf
(default value: 1010)
*/
#define BISTPLL_CTRL0__RG_BISTPLL_PC_POS 27
#define BISTPLL_CTRL0__RG_BISTPLL_PC_MASK 0x78000000

/*****************************************************************************/

/** Reg bistpll_ctrl1

*/
#define FE_CSR_VCORE__BISTPLL_CTRL1 CSR_ACCESS(FE_CSR_VCORE_BASE + 0x00000024)

/** Field RG_BISTPLL_POSDIV
BISTPLL post-divider control
00: /1
01: /2
10: /4
11: forbiden
(default value: 00)
*/
#define BISTPLL_CTRL1__RG_BISTPLL_POSDIV_POS 0
#define BISTPLL_CTRL1__RG_BISTPLL_POSDIV_MASK 0x00000003

/** Field RG_BISTPLL_PREDIV
BISTPLL pre-divider control
00: /1
01: /2
10: forbiden
11: /4
(default value: 00)
*/
#define BISTPLL_CTRL1__RG_BISTPLL_PREDIV_POS 2
#define BISTPLL_CTRL1__RG_BISTPLL_PREDIV_MASK 0x0000000C

/** Field RG_BISTPLL_FBKDIV
BISTPLL feedback divider: 8 ~ 63
001000: /8
001001: /9
     .
     .
111111: /63
*/
#define BISTPLL_CTRL1__RG_BISTPLL_FBKDIV_POS 4
#define BISTPLL_CTRL1__RG_BISTPLL_FBKDIV_MASK 0x000003F0

/** Field RGR_BISTPLL_IBAND

*/
#define BISTPLL_CTRL1__RGR_BISTPLL_IBAND_POS 10
#define BISTPLL_CTRL1__RGR_BISTPLL_IBAND_MASK 0x00007C00

/*****************************************************************************/

/** Reg auxsar_ctrl

*/
#define FE_CSR_VCORE__AUXSAR_CTRL CSR_ACCESS(FE_CSR_VCORE_BASE + 0x00000028)

/** Field RG_AUXSAR_AINSEL
SARADC AIN selection
0 : 1/4 input 
1 : normal input (default)
*/
#define AUXSAR_CTRL__RG_AUXSAR_AINSEL_POS 0
#define AUXSAR_CTRL__RG_AUXSAR_AINSEL_MASK 0x00000001

/** Field RG_AUXSAR_CKSEL
SARADC output clock rate=sys_clk/2^RG_AUXSAR_CKSEL
*/
#define AUXSAR_CTRL__RG_AUXSAR_CKSEL_POS 1
#define AUXSAR_CTRL__RG_AUXSAR_CKSEL_MASK 0x0000000E

/** Field RG_AUXSAR_IBT
SARADC bias current selection 
*/
#define AUXSAR_CTRL__RG_AUXSAR_IBT_POS 4
#define AUXSAR_CTRL__RG_AUXSAR_IBT_MASK 0x00000FF0

/** Field RG_AUXSAR_PWD
SARADC power down
*/
#define AUXSAR_CTRL__RG_AUXSAR_PWD_POS 12
#define AUXSAR_CTRL__RG_AUXSAR_PWD_MASK 0x00001000

/** Field RG_AUXSAR_VSEL
SARADC VREF selection
00 : VDD<2.5 (default)
01 :
10 :
11 :
*/
#define AUXSAR_CTRL__RG_AUXSAR_VSEL_POS 13
#define AUXSAR_CTRL__RG_AUXSAR_VSEL_MASK 0x00006000

/** Field AD_AUXSAR_D0
SARADC output data
*/
#define AUXSAR_CTRL__AD_AUXSAR_D0_POS 16
#define AUXSAR_CTRL__AD_AUXSAR_D0_MASK 0x03FF0000

/** Field AD_AUXSAR_DATARDY
SARADC output data clock
*/
#define AUXSAR_CTRL__AD_AUXSAR_DATARDY_POS 26
#define AUXSAR_CTRL__AD_AUXSAR_DATARDY_MASK 0x04000000

/** Field RG_AUXSAR_DIFFMODE_EN
SARADC differential input enable
*/
#define AUXSAR_CTRL__RG_AUXSAR_DIFFMODE_EN_POS 27
#define AUXSAR_CTRL__RG_AUXSAR_DIFFMODE_EN_MASK 0x08000000

/** Field RG_AUXSAR_VIN_SEL
SARADC Vin channel selection
000 : TSSI_VOUTP/TSSI_VOUTN
001 : TSENS1
010 : TSENS2
011 : BATDET
100 : TIP/TIN
101 : SYNTH_LPFVOUT
110 : gnd
111 : gnd
*/
#define AUXSAR_CTRL__RG_AUXSAR_VIN_SEL_POS 28
#define AUXSAR_CTRL__RG_AUXSAR_VIN_SEL_MASK 0xF0000000

/*****************************************************************************/

/** Reg testmode_ctrl

*/
#define FE_CSR_VCORE__TESTMODE_CTRL CSR_ACCESS(FE_CSR_VCORE_BASE + 0x0000002C)

/** Field RG_ATEST_CKTST_CKMUX
test ck mux
000 : PLL_CLK384M
001 : BISTPLL_CLK
010: 
011:  
100:
101:
110:
111:
*/
#define TESTMODE_CTRL__RG_ATEST_CKTST_CKMUX_POS 0
#define TESTMODE_CTRL__RG_ATEST_CKTST_CKMUX_MASK 0x00000007

/** Field RG_ATEST_CKTST_CUR
Open drain current
00:  5mA
11:  20mA
*/
#define TESTMODE_CTRL__RG_ATEST_CKTST_CUR_POS 3
#define TESTMODE_CTRL__RG_ATEST_CKTST_CUR_MASK 0x00000018

/** Field RG_ATEST_VTST_VMUX
test VC mux
000 : PLL_V12MON
001 : PLL_VCMON
010 : BISTPLL_V12MON
011 : BISTPLL_VCMON
100 : BGREF_LPVBG12
101 : BGREF_NMVBG12
110 : AVDD15_IF
111 : AVDD12_IF
*/
#define TESTMODE_CTRL__RG_ATEST_VTST_VMUX_POS 5
#define TESTMODE_CTRL__RG_ATEST_VTST_VMUX_MASK 0x000001E0

/*****************************************************************************/

/** Reg lp_ctrl

*/
#define FE_CSR_VCORE__LP_CTRL CSR_ACCESS(FE_CSR_VCORE_BASE + 0x00000030)

/** Field RG_RXPGA_DCOC_C
RXIF PGA DCOC CapSize options
000 : 13pF
001 : 19pF
::::::
111 : 77pF
*/
#define LP_CTRL__RG_RXPGA_DCOC_C_POS 8
#define LP_CTRL__RG_RXPGA_DCOC_C_MASK 0x00000700

/*****************************************************************************/

/** Reg rco32k_cal_ctrl

*/
#define FE_CSR_VCORE__RCO32K_CAL_CTRL CSR_ACCESS(FE_CSR_VCORE_BASE + 0x00000034)

/** Field rg_fm32k_en
32K frequency meter enable.
*/
#define RCO32K_CAL_CTRL__RG_FM32K_EN_POS 0
#define RCO32K_CAL_CTRL__RG_FM32K_EN_MASK 0x00000001

/** Field rg_fm32k_binary_mode
1:Binary searching mode. 0:Thermal code searching mode.
*/
#define RCO32K_CAL_CTRL__RG_FM32K_BINARY_MODE_POS 1
#define RCO32K_CAL_CTRL__RG_FM32K_BINARY_MODE_MASK 0x00000002

/** Field rg_fm32k_fsel
Compared freq:
00:31K 01: 32K 10:33K 11:34K, default 32K
*/
#define RCO32K_CAL_CTRL__RG_FM32K_FSEL_POS 4
#define RCO32K_CAL_CTRL__RG_FM32K_FSEL_MASK 0x00000030

/** Field rg_fm32k_win
Window number used to control freq resolution:
00:1000ppm, 01:900ppm, 10:800ppm, 11:700ppm
*/
#define RCO32K_CAL_CTRL__RG_FM32K_WIN_POS 6
#define RCO32K_CAL_CTRL__RG_FM32K_WIN_MASK 0x000000C0

/** Field rg_fm32k_rc_code_man
Manual mode to set R and C code
*/
#define RCO32K_CAL_CTRL__RG_FM32K_RC_CODE_MAN_POS 8
#define RCO32K_CAL_CTRL__RG_FM32K_RC_CODE_MAN_MASK 0x00000100

/** Field rg_fm32k_rcode
Manual R code
*/
#define RCO32K_CAL_CTRL__RG_FM32K_RCODE_POS 16
#define RCO32K_CAL_CTRL__RG_FM32K_RCODE_MASK 0x001F0000

/** Field rg_fm32k_ccode
Manual C code
*/
#define RCO32K_CAL_CTRL__RG_FM32K_CCODE_POS 24
#define RCO32K_CAL_CTRL__RG_FM32K_CCODE_MASK 0x3F000000

/*****************************************************************************/

/** Reg rco32k_cal_result

*/
#define FE_CSR_VCORE__RCO32K_CAL_RESULT CSR_ACCESS(FE_CSR_VCORE_BASE + 0x00000038)

/** Field fm32k_cal_done
Notification flag for completion of 32K frequency meter
*/
#define RCO32K_CAL_RESULT__FM32K_CAL_DONE_POS 0
#define RCO32K_CAL_RESULT__FM32K_CAL_DONE_MASK 0x00000001

/** Field da_fm32k_rcode
Calibrated R code
*/
#define RCO32K_CAL_RESULT__DA_FM32K_RCODE_POS 16
#define RCO32K_CAL_RESULT__DA_FM32K_RCODE_MASK 0x001F0000

/** Field da_fm32k_ccode
Calibrated C code
*/
#define RCO32K_CAL_RESULT__DA_FM32K_CCODE_POS 24
#define RCO32K_CAL_RESULT__DA_FM32K_CCODE_MASK 0x3F000000

/*****************************************************************************/

/** Reg rco4m_cal_ctrl

*/
#define FE_CSR_VCORE__RCO4M_CAL_CTRL CSR_ACCESS(FE_CSR_VCORE_BASE + 0x0000003C)

/** Field rg_fm4m_en
4M frequency meter enable.
*/
#define RCO4M_CAL_CTRL__RG_FM4M_EN_POS 0
#define RCO4M_CAL_CTRL__RG_FM4M_EN_MASK 0x00000001

/** Field rg_fm4m_binary_mode
1:Binary searching mode. 0:Thermal code searching mode.
*/
#define RCO4M_CAL_CTRL__RG_FM4M_BINARY_MODE_POS 1
#define RCO4M_CAL_CTRL__RG_FM4M_BINARY_MODE_MASK 0x00000002

/** Field rg_fm4m_win
Window number used to control freq resolution:
00: 6000ppm, 01:8000ppm, 10:10000ppm, 11:12000ppm
*/
#define RCO4M_CAL_CTRL__RG_FM4M_WIN_POS 4
#define RCO4M_CAL_CTRL__RG_FM4M_WIN_MASK 0x00000030

/** Field rg_fm4m_r_code_man
Manual mode to set R code
*/
#define RCO4M_CAL_CTRL__RG_FM4M_R_CODE_MAN_POS 8
#define RCO4M_CAL_CTRL__RG_FM4M_R_CODE_MAN_MASK 0x00000100

/** Field rg_fm4m_rcode
Manual R code
*/
#define RCO4M_CAL_CTRL__RG_FM4M_RCODE_POS 12
#define RCO4M_CAL_CTRL__RG_FM4M_RCODE_MASK 0x0000F000

/** Field fm4m_cal_done
Notification flag for completion of 4M frequency meter
*/
#define RCO4M_CAL_CTRL__FM4M_CAL_DONE_POS 16
#define RCO4M_CAL_CTRL__FM4M_CAL_DONE_MASK 0x00010000

/** Field da_fm4m_rcode
Calibrated R code
*/
#define RCO4M_CAL_CTRL__DA_FM4M_RCODE_POS 20
#define RCO4M_CAL_CTRL__DA_FM4M_RCODE_MASK 0x00F00000

/*****************************************************************************/

/** Reg rfrxfe_ctrl

*/
#define FE_CSR_VCORE__RFRXFE_CTRL CSR_ACCESS(FE_CSR_VCORE_BASE + 0x00000040)

/** Field RG_SYNTH_DNOIFLTR_EN
VCO noise filter enable
*/
#define RFRXFE_CTRL__RG_SYNTH_DNOIFLTR_EN_POS 16
#define RFRXFE_CTRL__RG_SYNTH_DNOIFLTR_EN_MASK 0x00010000

/** Field RG_SYNTH_DNOIFC_SEL
VCO noise filter frequency corner selection
00: 10 kHz, default
01: 5 kHz
10: 3.5 kHz
11: 2.5kHz
*/
#define RFRXFE_CTRL__RG_SYNTH_DNOIFC_SEL_POS 17
#define RFRXFE_CTRL__RG_SYNTH_DNOIFC_SEL_MASK 0x00060000

/** Field RG_RFRXFE_IBTIA_SEL
Programmable control bits for TIA bias current
00: 08uA
01: 09uA
10: 10uA, default
11: 11uA
*/
#define RFRXFE_CTRL__RG_RFRXFE_IBTIA_SEL_POS 19
#define RFRXFE_CTRL__RG_RFRXFE_IBTIA_SEL_MASK 0x00180000

/*****************************************************************************/

/** Reg rxadc_ctrl1

*/
#define FE_CSR_VCORE__RXADC_CTRL1 CSR_ACCESS(FE_CSR_VCORE_BASE + 0x00000044)

/** Field RG_RXADC_QTZ_IBSEL
ADC quantizer bias current selection 
0: 2.5uA
1: 3.75uA
*/
#define RXADC_CTRL1__RG_RXADC_QTZ_IBSEL_POS 3
#define RXADC_CTRL1__RG_RXADC_QTZ_IBSEL_MASK 0x00000008

/** Field RG_RXADC_QTZ_PWD
ADC Quantizer power down control
0: power on
1: power down
*/
#define RXADC_CTRL1__RG_RXADC_QTZ_PWD_POS 4
#define RXADC_CTRL1__RG_RXADC_QTZ_PWD_MASK 0x00000010

/** Field RG_RXADC_OP2_IB
ADC OP2 Bias current selection 
00: -30%
01: -15%
10: Default
11: +15% 
*/
#define RXADC_CTRL1__RG_RXADC_OP2_IB_POS 5
#define RXADC_CTRL1__RG_RXADC_OP2_IB_MASK 0x00000060

/** Field RG_RXADC_OP3_IB
ADC OP3 Bias current selection 
00: -30%
01: -15%
10: Default
11: +15% 
*/
#define RXADC_CTRL1__RG_RXADC_OP3_IB_POS 7
#define RXADC_CTRL1__RG_RXADC_OP3_IB_MASK 0x00000180

/** Field RG_RXADC_VCM_IBSEL
Q channel data sync
0: default (same edge)
1: reverse edge
*/
#define RXADC_CTRL1__RG_RXADC_VCM_IBSEL_POS 9
#define RXADC_CTRL1__RG_RXADC_VCM_IBSEL_MASK 0x00000200

/** Field AD_RXADC_RCT
RXADC RCTUNE value
*/
#define RXADC_CTRL1__AD_RXADC_RCT_POS 10
#define RXADC_CTRL1__AD_RXADC_RCT_MASK 0x00007C00

/*****************************************************************************/

/** Reg misc_ctrl0

*/
#define FE_CSR_VCORE__MISC_CTRL0 CSR_ACCESS(FE_CSR_VCORE_BASE + 0x00000048)

/** Field RG_RXIF_OPASTUP_SHD
RXIF LPF and PGA opamp start-up Vth option
0: Vth=1~1.2V
1: Vth=1.1 ~ 1.3V
*/
#define MISC_CTRL0__RG_RXIF_OPASTUP_SHD_POS 0
#define MISC_CTRL0__RG_RXIF_OPASTUP_SHD_MASK 0x00000001

/** Field RG_RXIF_RSV3
NC
*/
#define MISC_CTRL0__RG_RXIF_RSV3_POS 1
#define MISC_CTRL0__RG_RXIF_RSV3_MASK 0x00000002

/** Field RG_RXLPF_BIAS_SEL
RXIF LPF BIAS current options
00: 1.25 * Ib  
01: 1.00 * Ib  (5uA, A1 design)
10: 0.83 * Ib
11: 0.71 * Ib
*/
#define MISC_CTRL0__RG_RXLPF_BIAS_SEL_POS 2
#define MISC_CTRL0__RG_RXLPF_BIAS_SEL_MASK 0x0000000C

/** Field RG_RXPGA_DCOCRO_BIAS_SEL
RXIF LPF DCOC Ro BIAS current options
00: 10nA
01: 20nA
10: 30nA
11: 40nA
*/
#define MISC_CTRL0__RG_RXPGA_DCOCRO_BIAS_SEL_POS 6
#define MISC_CTRL0__RG_RXPGA_DCOCRO_BIAS_SEL_MASK 0x000000C0

/** Field RG_RXLPF_VCM_SEL
RXIF LPF VCM option
0: 0.75V
1: 0.60V
*/
#define MISC_CTRL0__RG_RXLPF_VCM_SEL_POS 8
#define MISC_CTRL0__RG_RXLPF_VCM_SEL_MASK 0x00000100

/** Field RG_RXPGA_BIAS_SEL
RXIF PGA BIAS current options
00: 1.25 * Ib  
01: 1.00 * Ib  (5uA, Test Chip design)
10: 0.83 * Ib
11: 0.71 * Ib
*/
#define MISC_CTRL0__RG_RXPGA_BIAS_SEL_POS 9
#define MISC_CTRL0__RG_RXPGA_BIAS_SEL_MASK 0x00000600

/** Field RG_RXPGA_DCOCIN_BIAS_SEL
RXIF LPF DCOC In BIAS current options
00: 40nA
01: 80nA
10: 120nA
11: 160nA
*/
#define MISC_CTRL0__RG_RXPGA_DCOCIN_BIAS_SEL_POS 13
#define MISC_CTRL0__RG_RXPGA_DCOCIN_BIAS_SEL_MASK 0x00006000

/** Field RG_RXPGA_VCM_SEL
RXIF PGA VCM option
0: 0.75V
1: 0.60V
*/
#define MISC_CTRL0__RG_RXPGA_VCM_SEL_POS 15
#define MISC_CTRL0__RG_RXPGA_VCM_SEL_MASK 0x00008000

/** Field RG_SYNTH_SEL_OL_EN
Select synthesizer open-loop configuration to test VCO
0: Disable, default
1: Enable 
*/
#define MISC_CTRL0__RG_SYNTH_SEL_OL_EN_POS 16
#define MISC_CTRL0__RG_SYNTH_SEL_OL_EN_MASK 0x00010000

/** Field RG_RCO32K_CKMON_EN
RCO32K clock test output to PLL_TST_TOP
0 : disable monitor clock
1 : enable monitor clock
*/
#define MISC_CTRL0__RG_RCO32K_CKMON_EN_POS 17
#define MISC_CTRL0__RG_RCO32K_CKMON_EN_MASK 0x00020000

/** Field RG_RCO4M_CKMON_EN
RCO4M clock test output to PLL_TST_TOP
0 : disable monitor clock
1 : enable monitor clock
*/
#define MISC_CTRL0__RG_RCO4M_CKMON_EN_POS 18
#define MISC_CTRL0__RG_RCO4M_CKMON_EN_MASK 0x00040000

/*****************************************************************************/

/** Reg rxdcoc_acc

*/
#define FE_CSR_VCORE__RXDCOC_ACC CSR_ACCESS(FE_CSR_VCORE_BASE + 0x0000004C)

/** Field RG_RXPGA_DCOC_HP
RXIF PGA DCOC Gm-Rdg options
0000: 0 ohm
x: X*300K ohm
1111: 4.5M ohm
*/
#define RXDCOC_ACC__RG_RXPGA_DCOC_HP_POS 0
#define RXDCOC_ACC__RG_RXPGA_DCOC_HP_MASK 0x0000000F

/** Field RG_RXPGA_ACCB_SEL
RXIF PGA DCOC Charge Current 2nd-level options
00: 10x
01: 2.5x
10: 1.4x      
11: 1x
*/
#define RXDCOC_ACC__RG_RXPGA_ACCB_SEL_POS 4
#define RXDCOC_ACC__RG_RXPGA_ACCB_SEL_MASK 0x00000030

/** Field RG_RXPGA_ACCA_SEL
RXIF PGA DCOC Charge Current options
00: 37uA 
01: 29uA
10: 9uA       
11: 1uA
*/
#define RXDCOC_ACC__RG_RXPGA_ACCA_SEL_POS 6
#define RXDCOC_ACC__RG_RXPGA_ACCA_SEL_MASK 0x000000C0

/*****************************************************************************/

/** Reg rfrxfe_ctrl2

*/
#define FE_CSR_VCORE__RFRXFE_CTRL2 CSR_ACCESS(FE_CSR_VCORE_BASE + 0x00000050)

/** Field RG_RFRXFE_RSV
resvered
*/
#define RFRXFE_CTRL2__RG_RFRXFE_RSV_POS 0
#define RFRXFE_CTRL2__RG_RFRXFE_RSV_MASK 0x00000FFF

/** Field RG_RFRXFE_RSV_NORET
resvered, no retention
*/
#define RFRXFE_CTRL2__RG_RFRXFE_RSV_NORET_POS 12
#define RFRXFE_CTRL2__RG_RFRXFE_RSV_NORET_MASK 0xFFFFF000

/*****************************************************************************/

/** Reg Product ID 

*/
#define FE_CSR_VCORE__PRODUCTID  CSR_ACCESS(FE_CSR_VCORE_BASE + 0x00000054)

/** Field AD_VCPID
Product ID code
000 : VC7000
001 : VC7001
010 : VC7002
*/
#define PRODUCTID__AD_VCPID_POS 0
#define PRODUCTID__AD_VCPID_MASK 0x00000007

#ifdef __cplusplus
}
#endif

#endif /* FE_CSR_VCORE_H */
