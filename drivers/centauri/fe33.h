#ifndef CENTAURI_FE33_H
#define CENTAURI_FE33_H

#ifdef __cplusplus
extern "C" {
#endif

#ifndef CSR_ACCESS
#define CSR_ACCESS(x) (*((volatile unsigned long *)(x)))
#endif


/** Block fe33_csr

*/
#define FE33_CSR_BASE 0x4002C200

/*****************************************************************************/

/** Reg rco32k_ctrl
LPLDO and RCO32K function control
*/
#define FE33_CSR__RCO32K_CTRL CSR_ACCESS(FE33_CSR_BASE + 0x00000020)

/** Field RG_RCO32K_BGCLP_PWD
RCO32K reference power down control
0: power on
1: power down
*/
#define RCO32K_CTRL__RG_RCO32K_BGCLP_PWD_POS 0
#define RCO32K_CTRL__RG_RCO32K_BGCLP_PWD_MASK 0x00000001

/** Field RG_RCO32K_PWD
RCO32K power down control
0: power on
1: power down
*/
#define RCO32K_CTRL__RG_RCO32K_PWD_POS 1
#define RCO32K_CTRL__RG_RCO32K_PWD_MASK 0x00000002

/** Field RG_RCO32K_RCT_MAN
transmit power control
0 : auto (PHY)
1 : manual (CSR, default)
*/
#define RCO32K_CTRL__RG_RCO32K_RCT_MAN_POS 2
#define RCO32K_CTRL__RG_RCO32K_RCT_MAN_MASK 0x00000004

/** Field RG_RCO32K_RCT_CCODE
RCO32K cap code manual input
*/
#define RCO32K_CTRL__RG_RCO32K_RCT_CCODE_POS 3
#define RCO32K_CTRL__RG_RCO32K_RCT_CCODE_MASK 0x000001F8

/** Field RG_RCO32K_RCT_RCODE
RCO32K res code manual input
*/
#define RCO32K_CTRL__RG_RCO32K_RCT_RCODE_POS 9
#define RCO32K_CTRL__RG_RCO32K_RCT_RCODE_MASK 0x00003E00

/*****************************************************************************/

/** Reg bg_xtal_rco4m_ctrl
Bandgap/XTAL/RCO4M function control
*/
#define FE33_CSR__BG_XTAL_RCO4M_CTRL CSR_ACCESS(FE33_CSR_BASE + 0x00000024)

/** Field RG_BGREF_BGCLP_PWD
BGREF Low power BG core power down
0: power on
1: power down
*/
#define BG_XTAL_RCO4M_CTRL__RG_BGREF_BGCLP_PWD_POS 0
#define BG_XTAL_RCO4M_CTRL__RG_BGREF_BGCLP_PWD_MASK 0x00000001

/** Field RG_BGREF_BGCNM_PWD
BGREF Normal BG core power down
0: power on
1: power down
*/
#define BG_XTAL_RCO4M_CTRL__RG_BGREF_BGCNM_PWD_POS 1
#define BG_XTAL_RCO4M_CTRL__RG_BGREF_BGCNM_PWD_MASK 0x00000002

/** Field RG_BGREF_V2I_IBSEL
BGREF V2I bias current source
0: BGLP
1: BGNM
*/
#define BG_XTAL_RCO4M_CTRL__RG_BGREF_V2I_IBSEL_POS 2
#define BG_XTAL_RCO4M_CTRL__RG_BGREF_V2I_IBSEL_MASK 0x00000004

/** Field RG_BGREF_V2I_PWD
BGREF V2I power down
0: power on
1: power down
*/
#define BG_XTAL_RCO4M_CTRL__RG_BGREF_V2I_PWD_POS 3
#define BG_XTAL_RCO4M_CTRL__RG_BGREF_V2I_PWD_MASK 0x00000008

/** Field RG_BGREF_V2I_VBSEL
BGREF V2I Vref source
0: BGLP
1: BGNM
*/
#define BG_XTAL_RCO4M_CTRL__RG_BGREF_V2I_VBSEL_POS 4
#define BG_XTAL_RCO4M_CTRL__RG_BGREF_V2I_VBSEL_MASK 0x00000010

/** Field RG_XTAL_PWD
Power down control for XO
*/
#define BG_XTAL_RCO4M_CTRL__RG_XTAL_PWD_POS 5
#define BG_XTAL_RCO4M_CTRL__RG_XTAL_PWD_MASK 0x00000020

/** Field RG_XTAL_DAMPC
Selection of XO's oscillation amplitude
*/
#define BG_XTAL_RCO4M_CTRL__RG_XTAL_DAMPC_POS 6
#define BG_XTAL_RCO4M_CTRL__RG_XTAL_DAMPC_MASK 0x000001C0

/** Field RG_XTAL_DCTUN
Programmable XO load capactance for XO frequency tuning
*/
#define BG_XTAL_RCO4M_CTRL__RG_XTAL_DCTUN_POS 9
#define BG_XTAL_RCO4M_CTRL__RG_XTAL_DCTUN_MASK 0x0000FE00

/** Field RG_XTAL_FO_SEL
Selection of frequency of clock signal driven out of chip: 00 for 32MHz; 01 for 4MHz; 10/11 for 2MHz
*/
#define BG_XTAL_RCO4M_CTRL__RG_XTAL_FO_SEL_POS 16
#define BG_XTAL_RCO4M_CTRL__RG_XTAL_FO_SEL_MASK 0x00030000

/** Field RG_XTAL_TCXO_SEL
Choose external TCXO, powering down internal XO driver circuit
*/
#define BG_XTAL_RCO4M_CTRL__RG_XTAL_TCXO_SEL_POS 18
#define BG_XTAL_RCO4M_CTRL__RG_XTAL_TCXO_SEL_MASK 0x00040000

/** Field RG_XTAL_DCKO_DRV
XO external driving capability control
00 : 
01 : 
10 : 
11: 
*/
#define BG_XTAL_RCO4M_CTRL__RG_XTAL_DCKO_DRV_POS 19
#define BG_XTAL_RCO4M_CTRL__RG_XTAL_DCKO_DRV_MASK 0x00180000

/** Field RG_RCO4M_PWD
RCO4M power down
*/
#define BG_XTAL_RCO4M_CTRL__RG_RCO4M_PWD_POS 21
#define BG_XTAL_RCO4M_CTRL__RG_RCO4M_PWD_MASK 0x00200000

/** Field RG_RCO4M_RCT_MAN
transmit power control
0 : auto (PHY)
1 : manual (CSR, default)
*/
#define BG_XTAL_RCO4M_CTRL__RG_RCO4M_RCT_MAN_POS 22
#define BG_XTAL_RCO4M_CTRL__RG_RCO4M_RCT_MAN_MASK 0x00400000

/** Field RG_RCO4M_RCT_RCODE
RCO4M RTUNE code 4bit
*/
#define BG_XTAL_RCO4M_CTRL__RG_RCO4M_RCT_RCODE_POS 23
#define BG_XTAL_RCO4M_CTRL__RG_RCO4M_RCT_RCODE_MASK 0x07800000

/** Field RG_XTAL_DCKO_EN
Enable control for XO signal driven out of chip [MCU Control]
0: Disable, default
1: Enable
*/
#define BG_XTAL_RCO4M_CTRL__RG_XTAL_DCKO_EN_POS 27
#define BG_XTAL_RCO4M_CTRL__RG_XTAL_DCKO_EN_MASK 0x08000000

/** Field RG_XTAL_DNRB_DL
Select the delay time for negative resistance boost
00: 150us
01: 200us, default
10: 250us
11: 300us
*/
#define BG_XTAL_RCO4M_CTRL__RG_XTAL_DNRB_DL_POS 28
#define BG_XTAL_RCO4M_CTRL__RG_XTAL_DNRB_DL_MASK 0x30000000

/** Field RG_XTAL_NRBOOST_EN
Enable the negative resistance boost during oscillator start-up
0: Disable
1: Enable, default
*/
#define BG_XTAL_RCO4M_CTRL__RG_XTAL_NRBOOST_EN_POS 30
#define BG_XTAL_RCO4M_CTRL__RG_XTAL_NRBOOST_EN_MASK 0x40000000

/*****************************************************************************/

/** Reg ldo_ctrl0
LDOA1512RFIF/LDOA1512VCOCPSZ control
*/
#define FE33_CSR__LDO_CTRL0 CSR_ACCESS(FE33_CSR_BASE + 0x00000028)

/** Field RG_LDOA15RFMX_CC
LDOA15 Compensation cap
*/
#define LDO_CTRL0__RG_LDOA15RFMX_CC_POS 0
#define LDO_CTRL0__RG_LDOA15RFMX_CC_MASK 0x00000001

/** Field RG_LDOA15RFMX_IB
LDOA15 internal bias current
*/
#define LDO_CTRL0__RG_LDOA15RFMX_IB_POS 1
#define LDO_CTRL0__RG_LDOA15RFMX_IB_MASK 0x00000002

/** Field RG_LDOA15RFMX_VREF
LDOA15 output voltage level
000: 1.41V
111: 1.625V step:30mV
*/
#define LDO_CTRL0__RG_LDOA15RFMX_VREF_POS 2
#define LDO_CTRL0__RG_LDOA15RFMX_VREF_MASK 0x0000001C

/** Field RG_LDOA12RFMX_CC
LDOA12 Compensation cap
*/
#define LDO_CTRL0__RG_LDOA12RFMX_CC_POS 5
#define LDO_CTRL0__RG_LDOA12RFMX_CC_MASK 0x00000020

/** Field RG_LDOA12RFMX_IB
LDOA12 internal bias current
*/
#define LDO_CTRL0__RG_LDOA12RFMX_IB_POS 6
#define LDO_CTRL0__RG_LDOA12RFMX_IB_MASK 0x000000C0

/** Field RG_LDOA12RFMX_VREF
LDOA12 output voltage level
000: 0.95V
111: 1.3V step:50mV
*/
#define LDO_CTRL0__RG_LDOA12RFMX_VREF_POS 8
#define LDO_CTRL0__RG_LDOA12RFMX_VREF_MASK 0x00000700

/** Field RG_LDOAMX2X_PWD
IF LDOA power down control
0: power on
1: power down
*/
#define LDO_CTRL0__RG_LDOAMX2X_PWD_POS 11
#define LDO_CTRL0__RG_LDOAMX2X_PWD_MASK 0x00000800

/** Field RG_LDOA15VCOCP_CC
LDOA15 Compensation cap
*/
#define LDO_CTRL0__RG_LDOA15VCOCP_CC_POS 12
#define LDO_CTRL0__RG_LDOA15VCOCP_CC_MASK 0x00001000

/** Field RG_LDOA15VCOCP_IB
LDOA15 internal bias current
*/
#define LDO_CTRL0__RG_LDOA15VCOCP_IB_POS 13
#define LDO_CTRL0__RG_LDOA15VCOCP_IB_MASK 0x00002000

/** Field RG_LDOA15VCOCP_VREF
LDOA15 output voltage level
000: 1.41V
111: 1.625V step:30mV
*/
#define LDO_CTRL0__RG_LDOA15VCOCP_VREF_POS 14
#define LDO_CTRL0__RG_LDOA15VCOCP_VREF_MASK 0x0001C000

/** Field RG_LDOA12VCOSZ_CC
LDOA12 Compensation cap
*/
#define LDO_CTRL0__RG_LDOA12VCOSZ_CC_POS 17
#define LDO_CTRL0__RG_LDOA12VCOSZ_CC_MASK 0x00020000

/** Field RG_LDOA12VCOSZ_IB
LDOA12 internal bias current
*/
#define LDO_CTRL0__RG_LDOA12VCOSZ_IB_POS 18
#define LDO_CTRL0__RG_LDOA12VCOSZ_IB_MASK 0x000C0000

/** Field RG_LDOA12VCOSZ_VREF
LDOA12 output voltage level
000: 0.95V
111: 1.3V step:50mV
*/
#define LDO_CTRL0__RG_LDOA12VCOSZ_VREF_POS 20
#define LDO_CTRL0__RG_LDOA12VCOSZ_VREF_MASK 0x00700000

/** Field RG_LDOASZ4_PWD
VCO/CP/SZ LDOA power down control
0: power on
1: power down
*/
#define LDO_CTRL0__RG_LDOASZ4_PWD_POS 23
#define LDO_CTRL0__RG_LDOASZ4_PWD_MASK 0x00800000

/** Field RG_LDOARF2X_PWD
RF LDOA power down control
0: power on
1: power down
*/
#define LDO_CTRL0__RG_LDOARF2X_PWD_POS 24
#define LDO_CTRL0__RG_LDOARF2X_PWD_MASK 0x01000000

/** Field RG_LDOA12XTAL_PWD
XTAL 12 power down control
0: power on
1: power down
*/
#define LDO_CTRL0__RG_LDOA12XTAL_PWD_POS 25
#define LDO_CTRL0__RG_LDOA12XTAL_PWD_MASK 0x02000000

/** Field RG_LDOA12XTAL_CC
LDOA12 Compensation cap
*/
#define LDO_CTRL0__RG_LDOA12XTAL_CC_POS 26
#define LDO_CTRL0__RG_LDOA12XTAL_CC_MASK 0x04000000

/** Field RG_LDOA12XTAL_IB
LDOA12 internal bias current
*/
#define LDO_CTRL0__RG_LDOA12XTAL_IB_POS 27
#define LDO_CTRL0__RG_LDOA12XTAL_IB_MASK 0x18000000

/** Field RG_LDOA12XTAL_VREF
LDOA12 output voltage level
000: 0.95V
111: 1.3V step:50mV
*/
#define LDO_CTRL0__RG_LDOA12XTAL_VREF_POS 29
#define LDO_CTRL0__RG_LDOA12XTAL_VREF_MASK 0xE0000000

/*****************************************************************************/

/** Reg ldo_ctrl1
LDOA12LOIQ/LDOA15ADC/LDOA12DIG control
*/
#define FE33_CSR__LDO_CTRL1 CSR_ACCESS(FE33_CSR_BASE + 0x0000002C)

/** Field RG_LDOA12IQ_VREF
LDOA12 output voltage level
000: 0.95V
111: 1.3V step:50mV
*/
#define LDO_CTRL1__RG_LDOA12IQ_VREF_POS 0
#define LDO_CTRL1__RG_LDOA12IQ_VREF_MASK 0x00000007

/** Field RG_LDOA12LO_VREF
LDOA12 output voltage level
000: 0.95V
111: 1.3V step:50mV
*/
#define LDO_CTRL1__RG_LDOA12LO_VREF_POS 3
#define LDO_CTRL1__RG_LDOA12LO_VREF_MASK 0x00000038

/** Field RG_LDOA12LOIQ_CC
LDOA12 Compensation cap
*/
#define LDO_CTRL1__RG_LDOA12LOIQ_CC_POS 6
#define LDO_CTRL1__RG_LDOA12LOIQ_CC_MASK 0x00000040

/** Field RG_LDOA12LOIQ_IB
LDOA12 internal bias current
*/
#define LDO_CTRL1__RG_LDOA12LOIQ_IB_POS 7
#define LDO_CTRL1__RG_LDOA12LOIQ_IB_MASK 0x00000180

/** Field RG_LDOA12LOIQ_PWD
LO/IQ LDOA12 power down control
0: power on
1: power down
*/
#define LDO_CTRL1__RG_LDOA12LOIQ_PWD_POS 9
#define LDO_CTRL1__RG_LDOA12LOIQ_PWD_MASK 0x00000200

/** Field RG_LDOA15ADC_CC
LDOA15 Compensation cap
*/
#define LDO_CTRL1__RG_LDOA15ADC_CC_POS 10
#define LDO_CTRL1__RG_LDOA15ADC_CC_MASK 0x00000400

/** Field RG_LDOA15ADC_IB
LDOA15 internal bias current
*/
#define LDO_CTRL1__RG_LDOA15ADC_IB_POS 11
#define LDO_CTRL1__RG_LDOA15ADC_IB_MASK 0x00000800

/** Field RG_LDOA15_RBYP
LDOA15 Internal LP bypass
*/
#define LDO_CTRL1__RG_LDOA15_RBYP_POS 12
#define LDO_CTRL1__RG_LDOA15_RBYP_MASK 0x00001000

/** Field RG_LDOA15ADC_PWD
ADC LDOA15 power down control
0: power on
1: power down
*/
#define LDO_CTRL1__RG_LDOA15ADC_PWD_POS 13
#define LDO_CTRL1__RG_LDOA15ADC_PWD_MASK 0x00002000

/** Field RG_LDOA15ADC_VREF
LDOA15 output voltage level
000: 1.41V
111: 1.625V step:30mV
*/
#define LDO_CTRL1__RG_LDOA15ADC_VREF_POS 14
#define LDO_CTRL1__RG_LDOA15ADC_VREF_MASK 0x0001C000

/** Field RG_LDOA12DIG_CC
LDOA12 Compensation cap
*/
#define LDO_CTRL1__RG_LDOA12DIG_CC_POS 17
#define LDO_CTRL1__RG_LDOA12DIG_CC_MASK 0x00020000

/** Field RG_LDOA12DIG_IB
LDOA12 internal bias current
*/
#define LDO_CTRL1__RG_LDOA12DIG_IB_POS 18
#define LDO_CTRL1__RG_LDOA12DIG_IB_MASK 0x000C0000

/** Field RG_LDOA12DIG_PWD
DIG LDOA12 power down control
0: power on
1: power down
*/
#define LDO_CTRL1__RG_LDOA12DIG_PWD_POS 20
#define LDO_CTRL1__RG_LDOA12DIG_PWD_MASK 0x00100000

/** Field RG_LDOA12DIG_VREF
LDOA12 output voltage level
000: 0.95V
111: 1.3V step:50mV
*/
#define LDO_CTRL1__RG_LDOA12DIG_VREF_POS 21
#define LDO_CTRL1__RG_LDOA12DIG_VREF_MASK 0x00E00000

/** Field RG_LDOD12CORE_RSV
reserved
*/
#define LDO_CTRL1__RG_LDOD12CORE_RSV_POS 24
#define LDO_CTRL1__RG_LDOD12CORE_RSV_MASK 0x01000000

/** Field RG_LDOD12CORE_IB
LDOD12 internal bias current
*/
#define LDO_CTRL1__RG_LDOD12CORE_IB_POS 25
#define LDO_CTRL1__RG_LDOD12CORE_IB_MASK 0x06000000

/** Field RG_LDOD12CORE_PWD
LDOD12 output power down control
0: power on
1: power down
*/
#define LDO_CTRL1__RG_LDOD12CORE_PWD_POS 27
#define LDO_CTRL1__RG_LDOD12CORE_PWD_MASK 0x08000000

/** Field RG_LDOD12CORE_VREF
LDOD12 output voltage level
000: 0.95V
111: 1.3V step:50mV
*/
#define LDO_CTRL1__RG_LDOD12CORE_VREF_POS 28
#define LDO_CTRL1__RG_LDOD12CORE_VREF_MASK 0x70000000

/** Field RG_LDOA12_RBYP
LDOA12 Internal LP bypass
*/
#define LDO_CTRL1__RG_LDOA12_RBYP_POS 31
#define LDO_CTRL1__RG_LDOA12_RBYP_MASK 0x80000000

/*****************************************************************************/

/** Reg misc_ctrl0
PLL control/TEST
*/
#define FE33_CSR__MISC_CTRL0 CSR_ACCESS(FE33_CSR_BASE + 0x00000030)

/** Field RG_PLL_EN
PLL power on control [MCU Control]
0: disable
1: enable
*/
#define MISC_CTRL0__RG_PLL_EN_POS 0
#define MISC_CTRL0__RG_PLL_EN_MASK 0x00000001

/** Field RG_RFRXFE_RX_RFSW_EN
T/R switch
*/
#define MISC_CTRL0__RG_RFRXFE_RX_RFSW_EN_POS 1
#define MISC_CTRL0__RG_RFRXFE_RX_RFSW_EN_MASK 0x00000002

/** Field RG_BISTPLL_EN
BISTPLL power on control
0: disable
1: enable
*/
#define MISC_CTRL0__RG_BISTPLL_EN_POS 2
#define MISC_CTRL0__RG_BISTPLL_EN_MASK 0x00000004

/** Field RG_TSENSE_PWD
Temp sensor enable control
00 : both disable
01 : enable TSENS1
10 : enable TSENS2
11 : enable both
*/
#define MISC_CTRL0__RG_TSENSE_PWD_POS 3
#define MISC_CTRL0__RG_TSENSE_PWD_MASK 0x00000018

/** Field RG_BATDET_PWD
battary detection control
*/
#define MISC_CTRL0__RG_BATDET_PWD_POS 5
#define MISC_CTRL0__RG_BATDET_PWD_MASK 0x00000020

/** Field RG_ATEST_CKTST_EN
analog TEST module Clock test control
0: disable
1: enable
*/
#define MISC_CTRL0__RG_ATEST_CKTST_EN_POS 6
#define MISC_CTRL0__RG_ATEST_CKTST_EN_MASK 0x00000040

/** Field RG_ATEST_EN
analog TEST module power on control
0: disable
1: enable
*/
#define MISC_CTRL0__RG_ATEST_EN_POS 7
#define MISC_CTRL0__RG_ATEST_EN_MASK 0x00000080

/** Field RG_ATEST_VTST_EN
analog TEST module Voltage test control
0: disable
1: enable
*/
#define MISC_CTRL0__RG_ATEST_VTST_EN_POS 8
#define MISC_CTRL0__RG_ATEST_VTST_EN_MASK 0x00000100

/** Field RG_POR12_PWD
POR12 power down control
0 : power on
1 : power down
*/
#define MISC_CTRL0__RG_POR12_PWD_POS 9
#define MISC_CTRL0__RG_POR12_PWD_MASK 0x00000200

/** Field RG_POR33_DET_EN
POR33 detection test mode
0 : power down
1 : power on
*/
#define MISC_CTRL0__RG_POR33_DET_EN_POS 10
#define MISC_CTRL0__RG_POR33_DET_EN_MASK 0x00000400

/** Field RG_RFMXR_TESTOUT_EN
MIXER test mode output enable
0: disable 
1: enable
*/
#define MISC_CTRL0__RG_RFMXR_TESTOUT_EN_POS 11
#define MISC_CTRL0__RG_RFMXR_TESTOUT_EN_MASK 0x00000800

/** Field RG_RXPGA_TESTIN_EN
RXPGA test mode input enable
0: disable 
1: enable
*/
#define MISC_CTRL0__RG_RXPGA_TESTIN_EN_POS 12
#define MISC_CTRL0__RG_RXPGA_TESTIN_EN_MASK 0x00001000

/** Field RG_RXLPF_TESTIN_EN
RXLPF test mode input enable
0: disable 
1: enable
*/
#define MISC_CTRL0__RG_RXLPF_TESTIN_EN_POS 13
#define MISC_CTRL0__RG_RXLPF_TESTIN_EN_MASK 0x00002000

/** Field RG_RXADC_TESTIN_EN
RXADC test mode input enable
*/
#define MISC_CTRL0__RG_RXADC_TESTIN_EN_POS 14
#define MISC_CTRL0__RG_RXADC_TESTIN_EN_MASK 0x00004000

/** Field RG_POR12_VT
00 : 0.7V
01 : 0.8V
10 : 0.9V
11 : 1.0V
*/
#define MISC_CTRL0__RG_POR12_VT_POS 15
#define MISC_CTRL0__RG_POR12_VT_MASK 0x00018000

/** Field RG_ATEST_CKTST_R50_EN
50ohm termination control
*/
#define MISC_CTRL0__RG_ATEST_CKTST_R50_EN_POS 17
#define MISC_CTRL0__RG_ATEST_CKTST_R50_EN_MASK 0x00020000

/** Field RG_RXLPF_TESTOUT_EN
RXLPF test mode output enable
0: disable 
1: enable
*/
#define MISC_CTRL0__RG_RXLPF_TESTOUT_EN_POS 18
#define MISC_CTRL0__RG_RXLPF_TESTOUT_EN_MASK 0x00040000

/** Field RG_RXPGA_TESTOUT_EN
RXGA test mode output enable
0: disable 
1: enable
*/
#define MISC_CTRL0__RG_RXPGA_TESTOUT_EN_POS 19
#define MISC_CTRL0__RG_RXPGA_TESTOUT_EN_MASK 0x00080000

/** Field RG_RXIF_BYP
RXIF IQ-ch LPF, and PGA Bypass (RF_Mixer--> IF_ADC path is selected)
1: bypass LPF, PGA,
Let RG_RXIFI_PWD=RG_RXIFQ_PWD=1 to turn off LPF and PGA
0: normal path
*/
#define MISC_CTRL0__RG_RXIF_BYP_POS 20
#define MISC_CTRL0__RG_RXIF_BYP_MASK 0x00100000

/** Field RG_RXLPF_BYP
RXIF IQ-ch LPF Bypass (RF_Mixer--> IF_PGA path is selected)
1: bypass LPF & turn off LPF
0: normal path
*/
#define MISC_CTRL0__RG_RXLPF_BYP_POS 21
#define MISC_CTRL0__RG_RXLPF_BYP_MASK 0x00200000

/** Field RG_RXPGA_GAIN_6DB
RXIF PGA max. GAIN setting
0: max. gain=31dB
1: max. gain=37dB
*/
#define MISC_CTRL0__RG_RXPGA_GAIN_6DB_POS 22
#define MISC_CTRL0__RG_RXPGA_GAIN_6DB_MASK 0x00400000

/** Field RG_RXADC_LP24M_EN
ADC Loop filter setting
0: 16M/32M
1: 24M
*/
#define MISC_CTRL0__RG_RXADC_LP24M_EN_POS 23
#define MISC_CTRL0__RG_RXADC_LP24M_EN_MASK 0x00800000

/** Field RG_RXADC_LP32M_EN
ADC Loop filter setting
0: 16M/24M
1: 32M
*/
#define MISC_CTRL0__RG_RXADC_LP32M_EN_POS 24
#define MISC_CTRL0__RG_RXADC_LP32M_EN_MASK 0x01000000

/*****************************************************************************/

/** Reg tx_ctrl

*/
#define FE33_CSR__TX_CTRL CSR_ACCESS(FE33_CSR_BASE + 0x00000034)

/** Field RG_RFTXPA_DCTUNCAS
Selection of by-pass cap for cascode biasing in PA2
*/
#define TX_CTRL__RG_RFTXPA_DCTUNCAS_POS 0
#define TX_CTRL__RG_RFTXPA_DCTUNCAS_MASK 0x00000007

/** Field RG_RFTXPA_DCTUNO
Programmable PA output cap for RF band tuning: 00 high-band; 01 mid-band; 10/11 low-band
*/
#define TX_CTRL__RG_RFTXPA_DCTUNO_POS 3
#define TX_CTRL__RG_RFTXPA_DCTUNO_MASK 0x00000018

/** Field RG_RFTXPA_DICASPA2
Selection of cascode bias current in PA2
*/
#define TX_CTRL__RG_RFTXPA_DICASPA2_POS 5
#define TX_CTRL__RG_RFTXPA_DICASPA2_MASK 0x000000E0

/** Field RG_RFTXPA_DIPA1
Selection of main bias current for PA1
*/
#define TX_CTRL__RG_RFTXPA_DIPA1_POS 8
#define TX_CTRL__RG_RFTXPA_DIPA1_MASK 0x00000700

/** Field RG_RFTXPA_DIPA2
Selection of main bias current for PA2
*/
#define TX_CTRL__RG_RFTXPA_DIPA2_POS 11
#define TX_CTRL__RG_RFTXPA_DIPA2_MASK 0x00003800

/** Field RG_RFTXPA_DTPC
Programmable PA variable gain control; 1dB/step
*/
#define TX_CTRL__RG_RFTXPA_DTPC_POS 14
#define TX_CTRL__RG_RFTXPA_DTPC_MASK 0x000FC000

/** Field RG_RFTXPA_HPASEL
Progammable PA selection: 1 for HPA; 0 for MPA
*/
#define TX_CTRL__RG_RFTXPA_HPASEL_POS 20
#define TX_CTRL__RG_RFTXPA_HPASEL_MASK 0x00100000

/** Field RG_RFTXPA_PWD
Power down control for PA
*/
#define TX_CTRL__RG_RFTXPA_PWD_POS 21
#define TX_CTRL__RG_RFTXPA_PWD_MASK 0x00200000

/** Field RG_RFTXPA_DTPC_MAN
transmit power control
0 : auto (PHY)
1 : manual (CSR, default)
*/
#define TX_CTRL__RG_RFTXPA_DTPC_MAN_POS 22
#define TX_CTRL__RG_RFTXPA_DTPC_MAN_MASK 0x00400000

/** Field RG_RFTXPA_PWD_MAN
Power down control for PA
0 : auto (PHY)
1 : manual (CSR, default)
*/
#define TX_CTRL__RG_RFTXPA_PWD_MAN_POS 23
#define TX_CTRL__RG_RFTXPA_PWD_MAN_MASK 0x00800000

/*****************************************************************************/

/** Reg LP33_CTRL1
Low Power Control
*/
#define FE33_CSR__LP33_CTRL1 CSR_ACCESS(FE33_CSR_BASE + 0x00000038)

/** Field RG_IFIBREF_PWD
RG_LPCTRL_33[0] = RG_IFIBREF_PWD_33 = 1'b1
*/
#define LP33_CTRL1__RG_IFIBREF_PWD_POS 0
#define LP33_CTRL1__RG_IFIBREF_PWD_MASK 0x00000001

/** Field RG_RFMXR_TESTOUTQ_EN
RG_LPCTRL_33[1] = RG_RFMXR_TESTOUTQ_EN_33 = 1'b0
*/
#define LP33_CTRL1__RG_RFMXR_TESTOUTQ_EN_POS 1
#define LP33_CTRL1__RG_RFMXR_TESTOUTQ_EN_MASK 0x00000002

/** Field RG_RXLPF_TESTOUTQ_EN
RG_LPCTRL_33[2] = RG_RXLPF_TESTOUTQ_EN_33 = 1'b0
*/
#define LP33_CTRL1__RG_RXLPF_TESTOUTQ_EN_POS 2
#define LP33_CTRL1__RG_RXLPF_TESTOUTQ_EN_MASK 0x00000004

/** Field RG_RXPGA_TESTOUTQ_EN
RG_LPCTRL_33[3] = RG_RXPGA_TESTOUTQ_EN_33 = 1'b0
*/
#define LP33_CTRL1__RG_RXPGA_TESTOUTQ_EN_POS 3
#define LP33_CTRL1__RG_RXPGA_TESTOUTQ_EN_MASK 0x00000008

/** Field RG_ATEST_VTST_VMUX
RG_LPCTRL_33[7:4] = 4'b0000
*/
#define LP33_CTRL1__RG_ATEST_VTST_VMUX_POS 4
#define LP33_CTRL1__RG_ATEST_VTST_VMUX_MASK 0x000000F0

/** Field RG_RXADC_DACREFI
RXADCI DACBUF VREF 
0000: +37.5mV
1111: -50mV (6.25mV/step)
*/
#define LP33_CTRL1__RG_RXADC_DACREFI_POS 8
#define LP33_CTRL1__RG_RXADC_DACREFI_MASK 0x00000F00

/** Field RG_RXADCI_PWD
RG_LPCTRL_33[14] = 1'b1
*/
#define LP33_CTRL1__RG_RXADCI_PWD_POS 14
#define LP33_CTRL1__RG_RXADCI_PWD_MASK 0x00004000

/** Field RG_RXADCQ_PWD
RG_LPCTRL_33[15]  = 1'b1
*/
#define LP33_CTRL1__RG_RXADCQ_PWD_POS 15
#define LP33_CTRL1__RG_RXADCQ_PWD_MASK 0x00008000

/** Field RG_RXADC_DACBUF_HP
RXADC DACBUF high performance mode
0: 16M
1: 24M/32M
*/
#define LP33_CTRL1__RG_RXADC_DACBUF_HP_POS 16
#define LP33_CTRL1__RG_RXADC_DACBUF_HP_MASK 0x00010000

/** Field RG_RXADC_DACBUF_PWD
RXADC DACBUF power down
*/
#define LP33_CTRL1__RG_RXADC_DACBUF_PWD_POS 17
#define LP33_CTRL1__RG_RXADC_DACBUF_PWD_MASK 0x00020000

/** Field RG_RXADC_DACVCM
RXADC DACBUF VCM level
*/
#define LP33_CTRL1__RG_RXADC_DACVCM_POS 18
#define LP33_CTRL1__RG_RXADC_DACVCM_MASK 0x000C0000

/** Field RG_RXADC_DACREFQ
RXADCQ DACBUF VREF 
0000: +37.5mV
1111: -50mV (6.25mV/step)
*/
#define LP33_CTRL1__RG_RXADC_DACREFQ_POS 20
#define LP33_CTRL1__RG_RXADC_DACREFQ_MASK 0x00F00000

/** Field RG_RXADC_DACREF_LF
RXADC DACBUF VREF low freq level
0: 32M
1: 16M/24M
*/
#define LP33_CTRL1__RG_RXADC_DACREF_LF_POS 24
#define LP33_CTRL1__RG_RXADC_DACREF_LF_MASK 0x01000000

/** Field RG_RXADC_IBGEN_PWD
RXADC IBGEN power down
*/
#define LP33_CTRL1__RG_RXADC_IBGEN_PWD_POS 25
#define LP33_CTRL1__RG_RXADC_IBGEN_PWD_MASK 0x02000000

/** Field RG_RXADC_LPBYPS
RXADC low pass bypass
*/
#define LP33_CTRL1__RG_RXADC_LPBYPS_POS 26
#define LP33_CTRL1__RG_RXADC_LPBYPS_MASK 0x04000000

/** Field RG_RXADC_LPRES
RXADC low pass resistor enable
*/
#define LP33_CTRL1__RG_RXADC_LPRES_POS 27
#define LP33_CTRL1__RG_RXADC_LPRES_MASK 0x08000000

/** Field RG_RXADC_TUNE_MAN
RXADC RCTUNE manual control enable
*/
#define LP33_CTRL1__RG_RXADC_TUNE_MAN_POS 28
#define LP33_CTRL1__RG_RXADC_TUNE_MAN_MASK 0x10000000

/** Field RG_RXADC_VRDAC_TUNE
RXADC VREF DAC TUNE manual code
*/
#define LP33_CTRL1__RG_RXADC_VRDAC_TUNE_POS 29
#define LP33_CTRL1__RG_RXADC_VRDAC_TUNE_MASK 0xE0000000

/*****************************************************************************/

/** Reg misc_ctrl1
Low Power Control
*/
#define FE33_CSR__MISC_CTRL1 CSR_ACCESS(FE33_CSR_BASE + 0x0000003C)

/** Field RG_XTAL_DCAPLPF
Select LPF's capacitance
00: 2pF
01: 4pF, default
10: 6pF
11: 8pF
*/
#define MISC_CTRL1__RG_XTAL_DCAPLPF_POS 0
#define MISC_CTRL1__RG_XTAL_DCAPLPF_MASK 0x00000003

/** Field RG_XTAL_DSEL_IBXO
Select bias current for XO amplifier core
000: 160uA
001: 240uA
010: 320uA
011: 400uA, default
100: 480uA
101: 560uA
110: 640uA
111: 720uA
*/
#define MISC_CTRL1__RG_XTAL_DSEL_IBXO_POS 2
#define MISC_CTRL1__RG_XTAL_DSEL_IBXO_MASK 0x0000001C

/*****************************************************************************/

/** Reg ldo_ctrl2
Low Power Control
*/
#define FE33_CSR__LDO_CTRL2 CSR_ACCESS(FE33_CSR_BASE + 0x00000040)

/** Field RG_LDOA12ADC_CC
ADC LDOA12 Compensation cap
*/
#define LDO_CTRL2__RG_LDOA12ADC_CC_POS 0
#define LDO_CTRL2__RG_LDOA12ADC_CC_MASK 0x00000001

/** Field RG_LDOA12ADC_IB
ADC LDOA12 internal bias current
*/
#define LDO_CTRL2__RG_LDOA12ADC_IB_POS 1
#define LDO_CTRL2__RG_LDOA12ADC_IB_MASK 0x00000006

/** Field RG_LDOA12ADC_PWD
ADC LDOA12 power down control
0: power on
1: power down
*/
#define LDO_CTRL2__RG_LDOA12ADC_PWD_POS 3
#define LDO_CTRL2__RG_LDOA12ADC_PWD_MASK 0x00000008

/** Field RG_LDOA12ADC_VREF
ADC LDOA12 output voltage level
000: 0.95V
111: 1.3V step:50mV
*/
#define LDO_CTRL2__RG_LDOA12ADC_VREF_POS 4
#define LDO_CTRL2__RG_LDOA12ADC_VREF_MASK 0x00000070

/** Field RG_LDOA12DADC_CC
ADC LDOD12 Compensation cap
*/
#define LDO_CTRL2__RG_LDOA12DADC_CC_POS 7
#define LDO_CTRL2__RG_LDOA12DADC_CC_MASK 0x00000080

/** Field RG_LDOA12DADC_IB
ADC LDOD12 internal bias current
*/
#define LDO_CTRL2__RG_LDOA12DADC_IB_POS 8
#define LDO_CTRL2__RG_LDOA12DADC_IB_MASK 0x00000300

/** Field RG_LDOA12DADC_PWD
ADC LDOD12 power down control
0: power on
1: power down
*/
#define LDO_CTRL2__RG_LDOA12DADC_PWD_POS 10
#define LDO_CTRL2__RG_LDOA12DADC_PWD_MASK 0x00000400

/** Field RG_LDOA12DADC_VREF
ADC LDOD12 output voltage level
000: 0.95V
111: 1.3V step:50mV
*/
#define LDO_CTRL2__RG_LDOA12DADC_VREF_POS 11
#define LDO_CTRL2__RG_LDOA12DADC_VREF_MASK 0x00003800

/** Field RG_LDOA12IF_CC
LDOA12 Compensation cap
*/
#define LDO_CTRL2__RG_LDOA12IF_CC_POS 14
#define LDO_CTRL2__RG_LDOA12IF_CC_MASK 0x00004000

/** Field RG_LDOA12IF_IB
LDOA12 internal bias current
*/
#define LDO_CTRL2__RG_LDOA12IF_IB_POS 15
#define LDO_CTRL2__RG_LDOA12IF_IB_MASK 0x00018000

/** Field RG_LDOA12IF_PWD
LDOA12 power down control
0: power on
1: power down
*/
#define LDO_CTRL2__RG_LDOA12IF_PWD_POS 17
#define LDO_CTRL2__RG_LDOA12IF_PWD_MASK 0x00020000

/** Field RG_LDOA12IF_VREF
LDOA12 output voltage level
000: 0.95V
111: 1.3V step:50mV
*/
#define LDO_CTRL2__RG_LDOA12IF_VREF_POS 18
#define LDO_CTRL2__RG_LDOA12IF_VREF_MASK 0x001C0000

/** Field RG_LDOA15IF_CC
LDOA15 Compensation cap
*/
#define LDO_CTRL2__RG_LDOA15IF_CC_POS 21
#define LDO_CTRL2__RG_LDOA15IF_CC_MASK 0x00200000

/** Field RG_LDOA15IF_IB
LDOA15 internal bias current
*/
#define LDO_CTRL2__RG_LDOA15IF_IB_POS 22
#define LDO_CTRL2__RG_LDOA15IF_IB_MASK 0x00400000

/** Field RG_LDOA15IF_PWD
ADC LDOA15 power down control
0: power on
1: power down
*/
#define LDO_CTRL2__RG_LDOA15IF_PWD_POS 23
#define LDO_CTRL2__RG_LDOA15IF_PWD_MASK 0x00800000

/** Field RG_LDOA15IF_VREF
LDOA15 output voltage level
000: 1.41V
111: 1.625V step:30mV
*/
#define LDO_CTRL2__RG_LDOA15IF_VREF_POS 24
#define LDO_CTRL2__RG_LDOA15IF_VREF_MASK 0x07000000

/*****************************************************************************/

/** Reg LP33_CTRL2
Low Power Control
*/
#define FE33_CSR__LP33_CTRL2 CSR_ACCESS(FE33_CSR_BASE + 0x00000044)

/** Field RG_LP33_CTRL
resvered
*/
#define LP33_CTRL2__RG_LP33_CTRL_POS 0
#define LP33_CTRL2__RG_LP33_CTRL_MASK 0xFFFFFFFF

#ifdef __cplusplus
}
#endif

#endif /* CENTAURI_FE33_H */
