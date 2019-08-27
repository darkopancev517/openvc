/*
 *  Copyright (C) 2018, Vertexcom Technologies, Inc. - http://www.vertexcom.com/
 *  All rights reserved.
 */


#include <stdint.h>
#include <stdbool.h>
//#include "driver.h"
#include "fe_csr_vcore.h"
#include "fe33.h"
#include "mac_csr.h"
#include "phy_csr.h"
#include "pmu_csr.h"
#include "Transceiver.h"
#include "centauri_prober.h"
#include "TransceiverCsr.h"

/*
 * Name: RfRxFeCalDigiGainCtrl
 * Purpose: Digital gain control of on-chip generated calibration signal for I/Q-cal loop 
 * Method:
 * Input:
 *    None 
 * Output:
 *    None
 * Note:
 *    default: 3
 */
void RfRxFeCalDigiGainCtrl(U8 digital_gain_ctrl)
{
	U32 csr_val;

	csr_val = CentauriCsrRead(FE_CSR_VCORE__RFRX_CTRL0)&(~RFRX_CTRL0__RG_RFRXFE_CAL_DIGC_MASK);
	csr_val |= (((U32)digital_gain_ctrl << RFRX_CTRL0__RG_RFRXFE_CAL_DIGC_POS)&RFRX_CTRL0__RG_RFRXFE_CAL_DIGC_MASK);
	CentauriCsrWrite(FE_CSR_VCORE__RFRX_CTRL0, csr_val);
}
/*
 * Name: IfRxDcocCapRgMode
 * Purpose: Turn Dcoc Cap Mode to RG control mode
 * Method:
 * Input:
 *    None 
 * Output:
 *    None
 * Note:
 *    
 */
void IfRxDcocCapRgMode(void)
{
	//FE_CSR_VCORE__IFRX_CTRL |= IFRX_CTRL__RG_IFRXI_PWD_MASK;
	U32 csr_val;

	csr_val = CentauriCsrRead(FE_CSR_VCORE__IFRX_CTRL)|IFRX_CTRL__RG_RXIF_RSV_MASK;
	CentauriCsrWrite(FE_CSR_VCORE__IFRX_CTRL, csr_val);
}
/*
 * Name: FePgaOutAttackPoint
 * Purpose: Digital attack point setting at PGA output. 1dB/step.
 * Input: 
 *    ifn_datck
 * Output:
 * Note: 
 *     
 */
void FePgaOutAttackPoint(U8 ifn_datck)
{
	U32 csr_val;

	csr_val = CentauriCsrRead(FE_CSR_VCORE__RFRX_CTRL0)&(~RFRX_CTRL0__RG_PKDETIFN_DATCK_MASK);
	csr_val |= (((U32)ifn_datck << RFRX_CTRL0__RG_PKDETIFN_DATCK_POS)&RFRX_CTRL0__RG_PKDETIFN_DATCK_MASK);
	CentauriCsrWrite(FE_CSR_VCORE__RFRX_CTRL0, csr_val);
}
/*
 * Name: FeRxIfDcocRoBiasConfig
 * Purpose: TBD
 * Input: 
 *     val
 * Output:
 * Note: 
 *     
 */
void FeRxIfDcocRoBiasConfig(U8 val)
{
	U32 csr_val;

	csr_val = CentauriCsrRead(FE_CSR_VCORE__MISC_CTRL0)&(~MISC_CTRL0__RG_RXPGA_DCOCRO_BIAS_SEL_MASK);
	csr_val |= (((U32)val << MISC_CTRL0__RG_RXPGA_DCOCRO_BIAS_SEL_POS)&MISC_CTRL0__RG_RXPGA_DCOCRO_BIAS_SEL_MASK);
	CentauriCsrWrite(FE_CSR_VCORE__MISC_CTRL0, csr_val);
}
/*
 * Name: FeRxIfDcocInBiasConfig
 * Purpose: TBD
 * Input: 
 *     val
 * Output:
 * Note: 
 *     
 */
void FeRxIfDcocInBiasConfig(U8 val)
{
	U32 csr_val;

	csr_val = CentauriCsrRead(FE_CSR_VCORE__MISC_CTRL0)&(~MISC_CTRL0__RG_RXPGA_DCOCIN_BIAS_SEL_MASK);
	csr_val |= (((U32)val << MISC_CTRL0__RG_RXPGA_DCOCIN_BIAS_SEL_POS)&MISC_CTRL0__RG_RXPGA_DCOCIN_BIAS_SEL_MASK);
	CentauriCsrWrite(FE_CSR_VCORE__MISC_CTRL0, csr_val);
}
/*
 * Name: FeRxLpfRctManual
 * Purpose: Lpf Rct manual
 * Method:
 * Input:
 *    None 
 * Output:
 *    None
 * Note:
 *     0: auto
 *     1: manual
 */

void FeRxLpfRctManual(void)
{
    U32 csr_val;

    csr_val = CentauriCsrRead(FE_CSR_VCORE__RXADC_CTRL0)|RXADC_CTRL0__RG_RXLPF_RCT_MAN_MASK;
    CentauriCsrWrite(FE_CSR_VCORE__RXADC_CTRL0, csr_val);

}
/*
 * Name: RomTxPaModeRead
 * Purpose: [For ROM code] Read TX PA mode from retention RG
 * Input: 
 * Output: 
 * Note: 
 *     return 0: Auto
 *     return 1: Manual
 */
U8 RomTxPaModeRead(void)
{
	U8 csr_val;
	
	csr_val = (U8)((CentauriCsrRead(PMU_CSR__ROM_RG3)&ROM_RG3__TX_PA_MODE_CTRL_MASK) >> ROM_RG3__TX_PA_MODE_CTRL_POS);

	return (csr_val);
}
/*
 * Name: RomPmbLenSet
 * Purpose: [For ROM code] Write preamble length to retention RG
 * Input: 
 * Output: 
 * Note: 
 *     0: MAX preamble length (2048 bytes)
 */
void RomPmbLenSet(U16 pmb_len_set)
{
	U32 csr_val;
	
	csr_val = (CentauriCsrRead(PMU_CSR__ROM_RG3)&(~ROM_RG3__PMB_LEN_MASK));
	csr_val |= (((U32)pmb_len_set << ROM_RG3__PMB_LEN_POS)&ROM_RG3__PMB_LEN_MASK);
	CentauriCsrWrite(PMU_CSR__ROM_RG3, csr_val);
}

/*
 * Name: PhyRssiOffsetVal
 * Purpose: RSSI offset value, format <1,4,3>
 *                 - default set 36 (=4.5x8)
 * Input: 
 * Output: 
 * Note: 
 *     
 */
void PhyRssiOffsetVal(U32 rssi_offset)
{
	U32 csr_val;
	
	csr_val = (CentauriCsrRead(PHY_CSR__RX_RSSI_DIF_CTRL)&(~RX_RSSI_DIF_CTRL__RG_RSSI_OFFSET_MASK));
	csr_val |= ((rssi_offset << RX_RSSI_DIF_CTRL__RG_RSSI_OFFSET_POS) & RX_RSSI_DIF_CTRL__RG_RSSI_OFFSET_MASK);
	CentauriCsrWrite(PHY_CSR__RX_RSSI_DIF_CTRL, csr_val);
}

/*
 * Name: PhyRssiOffsetRead
 * Purpose: read out the rssi offset value
 * Input: 
 * Output: 
 * Note: 
 */
U32 PhyRssiOffsetRead(void)
{
	U32 csr_val;
	
	csr_val = ((CentauriCsrRead(PHY_CSR__RX_RSSI_DIF_CTRL)&RX_RSSI_DIF_CTRL__RG_RSSI_OFFSET_MASK) >> RX_RSSI_DIF_CTRL__RG_RSSI_OFFSET_POS);

	return (csr_val);
}

/*
 * Name: RfTxPaPwrOn 
 * Purpose: Power down control for PA
 * Input: 
 * Output:
 * Note: 
 */
void RfTxPaPwrOn(void)
{
	U32 csr_val;

	csr_val = CentauriCsrRead(FE33_CSR__TX_CTRL)&(~TX_CTRL__RG_RFTXPA_PWD_MASK);
    CentauriCsrWrite(FE33_CSR__TX_CTRL, csr_val);
}

/*
 * Name: RfTxPaPwrDown 
 * Purpose: Power down control for PA
 * Input: 
 * Output:
 * Note: 
 *     default: 1
 */
void RfTxPaPwrDown(void)
{
	U32 csr_val;

	csr_val = CentauriCsrRead(FE33_CSR__TX_CTRL)|TX_CTRL__RG_RFTXPA_PWD_MASK;
    CentauriCsrWrite(FE33_CSR__TX_CTRL, csr_val);
}

/*
 * Name: PhyRxAgcRestart
 * Purpose:Restart RF/IF AGC while already in receiving state (rg_rx_en=1). Hardware will auto clear this bit after AGC is restarted.
 * Method:
 * Input:
 *    None 
 * Output:
 *    None
 * Note:
 *    
 *     
 */
void PhyRxAgcRestart(void)
{
    U32 csr_val;

    csr_val = CentauriCsrRead(PHY_CSR__RX_RFAGC_CTRL)|RX_RFAGC_CTRL__RG_FE_AGC_RESTART_MASK;
    CentauriCsrWrite(PHY_CSR__RX_RFAGC_CTRL, csr_val);
}


/*
 * Name: RomSymRateRead
 * Purpose: [For ROM code] Read symbol rate from retention RG
 * Input: 
 * Output: 
 * Note: 
 */
U32 RomSymRateRead(void)
{
	U32 csr_val;
	
	csr_val = ((CentauriCsrRead(PMU_CSR__ROM_RG4)&ROM_RG4__SYMBOL_RATE_MASK) >> ROM_RG4__SYMBOL_RATE_POS);

	return (csr_val);
}
void AdcReset(void)
{
	U32 csr_val;
	csr_val = (CentauriCsrRead(FE_CSR_VCORE__RXADC_CTRL0)|(RXADC_CTRL0__RG_RXADC_RST_INT_MASK));

	CentauriCsrWrite(FE_CSR_VCORE__RXADC_CTRL0, csr_val);
}

void AdcReleaseReset(void)
{
	U32 csr_val;
	csr_val = (CentauriCsrRead(FE_CSR_VCORE__RXADC_CTRL0)&(~RXADC_CTRL0__RG_RXADC_RST_INT_MASK));

	CentauriCsrWrite(FE_CSR_VCORE__RXADC_CTRL0, csr_val);

}

void FeRxAdcIchQchEnable(void)
{
    U32 csr_val;

    csr_val = (CentauriCsrRead(FE33_CSR__LP33_CTRL1)&(~LP33_CTRL1__RG_RXADCI_RXADCQ_PWD_MASK));
    CentauriCsrWrite(FE33_CSR__LP33_CTRL1, csr_val);
}

void FeRxAdcIchQchDisable(void)
{
    U32 csr_val;

    csr_val = (CentauriCsrRead(FE33_CSR__LP33_CTRL1)|LP33_CTRL1__RG_RXADCI_RXADCQ_PWD_MASK);
    CentauriCsrWrite(FE33_CSR__LP33_CTRL1, csr_val);
}
void FeAdcClkEnable(void)
{
    U32 csr_val;

    csr_val = (CentauriCsrRead(FE_CSR_VCORE__PLL_CTRL)|PLL_CTRL__RG_PLL_ADCK_EN_MASK);
	CentauriCsrWrite(FE_CSR_VCORE__PLL_CTRL, csr_val);
}

void IfRxIchQchEnable(void)
{
	//FE_CSR_VCORE__IFRX_CTRL &= (~IFRX_CTRL__RG_IFRXI_PWD_MASK);
	U32 csr_val;

	csr_val = CentauriCsrRead(FE_CSR_VCORE__IFRX_CTRL)&(~IFRX_CTRL__RG_RXIFI_RXIFQ_PWD_MASK);
	CentauriCsrWrite(FE_CSR_VCORE__IFRX_CTRL, csr_val);
}
 
void RfRxFeTxRxSwitch(U8 tr_switch)
{
	//PMU_CSR__MISC_CTRL |= MISC_CTRL__RG_RFRXFE_RX_RFSW_33_MASK;
	U32 csr_val;

	csr_val = CentauriCsrRead(FE33_CSR__MISC_CTRL0)&(~MISC_CTRL0__RG_RFRXFE_RX_RFSW_EN_MASK);
	csr_val |= (((U32)tr_switch << MISC_CTRL0__RG_RFRXFE_RX_RFSW_EN_POS)&MISC_CTRL0__RG_RFRXFE_RX_RFSW_EN_MASK);
	CentauriCsrWrite(FE33_CSR__MISC_CTRL0, csr_val);
}

 
 void FeLoPwrOn(void)
 {
	 U32 csr_val;
 
	 csr_val = CentauriCsrRead(FE_CSR_VCORE__LO_CTRL)&(~LO_CTRL__RG_LO_PWD_MASK);
	 CentauriCsrWrite(FE_CSR_VCORE__LO_CTRL, csr_val);
 }
 void RfRxPkDetIfwIfnPwrOnFeRxEnableFePwrOn(void)
 {
	 U32 csr_val;
 
	 csr_val = (CentauriCsrRead(FE_CSR_VCORE__RFRX_CTRL0)&(~((RFRX_CTRL0__RG_PKDETIFW_PWD_MASK)|(RFRX_CTRL0__RG_PKDETIFN_PWD_MASK)|(RFRX_CTRL0__RG_RFRXFE_PWD_MASK))))|(RFRX_CTRL0__RG_RFRXFE_RX_EN_MASK);
	 CentauriCsrWrite(FE_CSR_VCORE__RFRX_CTRL0, csr_val);
 }
/*
 * Name: RomPmbLenBitPartSet
 * Purpose: [For ROM code] Write preamble length to retention RG (Bit part)
 * Input: 
 * Output: 
 * Note: 
 *     
 */
void RomPmbLenBitPartSet(U16 pmb_len_bit_set)
{
    U32 csr_val;
	
	csr_val = (CentauriCsrRead(PMU_CSR__ROM_RG1)&(~ROM_RG1__PMB_LEN_BIT_PART_MASK));
	csr_val |= (((U32)pmb_len_bit_set << ROM_RG1__PMB_LEN_BIT_PART_POS)&ROM_RG1__PMB_LEN_BIT_PART_MASK);
	CentauriCsrWrite(PMU_CSR__ROM_RG1, csr_val);
}

/*
 * Name: RomChannelInvalidRead
 * Purpose:  
 * Input: 
 * Output: 
 * Note:
 */
U32 RomChannelInvalidRead(void)
{
	U32 csr_val;
	
	csr_val = ((CentauriCsrRead(PMU_CSR__RXADC_DACREFIQ)&ROM_ADC__CHANNEL_INVALID_MASK) >> ROM_ADC__CHANNEL_INVALID_POS);

	return (csr_val);
}


/*
 * Name: RomChannelInvalidSet
 * Purpose:  
 * Input: 
 * Output: 
 * Note: 
 */
void RomChannelInvalidSet(U32 input)
{
	U32 csr_val;
	
	csr_val = (CentauriCsrRead(PMU_CSR__RXADC_DACREFIQ)&(~ROM_ADC__CHANNEL_INVALID_MASK));
	csr_val |= ((input << ROM_ADC__CHANNEL_INVALID_POS)&ROM_ADC__CHANNEL_INVALID_MASK);
	CentauriCsrWrite(PMU_CSR__RXADC_DACREFIQ, csr_val);
}

/*
 * Name: RomSymRateSet
 * Purpose: [For ROM code] Write TX PA mode to retention RG
 * Input: 
 * Output: 
 * Note: 
 *     return 0: Auto
 *     return 1: Manual
 */
void RomTxPaModeSet(U8 txpa_mode_set)
{
	U32 csr_val;
	
	csr_val = (CentauriCsrRead(PMU_CSR__ROM_RG3)&(~ROM_RG3__TX_PA_MODE_CTRL_MASK));
	csr_val |= (((U32)txpa_mode_set << ROM_RG3__TX_PA_MODE_CTRL_POS)&ROM_RG3__TX_PA_MODE_CTRL_MASK);
	CentauriCsrWrite(PMU_CSR__ROM_RG3, csr_val);
}

/*
 * Name: RomSynthTxHiDataRetSet
 * Purpose: 
 * Input: 
 * Output: 
 * Note: 
 */
void RomSynthTxHiDataRetSet(U32 input)
{
	U32 csr_val;
	
	csr_val = (CentauriCsrRead(PMU_CSR__ROM_RG3)&(~ROM_RG3__SYNTH_TXHIDATA_RET_MASK));
	csr_val |= ((input << ROM_RG3__SYNTH_TXHIDATA_RET_POS)&ROM_RG3__SYNTH_TXHIDATA_RET_MASK);
	CentauriCsrWrite(PMU_CSR__ROM_RG3, csr_val);
}
/*
 * Name: PhyTxPreempEnable
 * Purpose: Enable PHY TX Pre-emphasis configuration
 * Input:
 * Output:
 * Note:
 *    
 */
void PhyTxPreempEnable(void)
{
    //PHY_CSR__PHY_TX_CTRL |= PHY_TX_CTRL__RG_PREEMP_EN_MASK;
	U32 csr_val;

	csr_val = CentauriCsrRead(PHY_CSR__PHY_TX_CTRL)|PHY_TX_CTRL__RG_PREEMP_EN_MASK;
	CentauriCsrWrite(PHY_CSR__PHY_TX_CTRL, csr_val);
}
/*
 * Name: RomPreEmpSet
 * Purpose: [For ROM code] Write Pre-emphasis control to retention RG
 * Input: 
 * Output: 
 * Note: 
 */
void RomPreEmpSet(U8 preemp_set)
{
	U32 csr_val;
	
	csr_val = (CentauriCsrRead(PMU_CSR__ROM_RG3)&(~ROM_RG3__PRE_EMP_MASK));
	csr_val |= (((U32)preemp_set << ROM_RG3__PRE_EMP_POS)&ROM_RG3__PRE_EMP_MASK);
	CentauriCsrWrite(PMU_CSR__ROM_RG3, csr_val);
}
/*
 * Name: RomTxHcoeffRead
 * Purpose: [For ROM code] Read Tx channel gain (h: modulation index) from retention RG
 * Input: 
 * Output: 
 * Note: 
 *     Format <0,3,10>
 */
U32 RomTxHcoeffRead(void)
{
	U32 csr_val;
	
	csr_val = ((CentauriCsrRead(PMU_CSR__ROM_RG4)&ROM_RG4__TX_H_COEFF_MASK) >> ROM_RG4__TX_H_COEFF_POS);

	return (csr_val);
}
/*
 * Name: PhyTxPreempDisable
 * Purpose: Disable PHY TX Pre-emphasis configuration
 * Input:
 * Output:
 * Note:
 *    
 */
void PhyTxPreempDisable(void)
{
    //PHY_CSR__PHY_TX_CTRL &= (~PHY_TX_CTRL__RG_PREEMP_EN_MASK);
	U32 csr_val;

	csr_val = CentauriCsrRead(PHY_CSR__PHY_TX_CTRL)&(~PHY_TX_CTRL__RG_PREEMP_EN_MASK);
	CentauriCsrWrite(PHY_CSR__PHY_TX_CTRL, csr_val);
}

#if Centauri_B2
U32 RomRx16MhzEnRead(void)
{
		U32 csr_val;
		csr_val = (CentauriCsrRead(PMU_CSR__ROM_RG1) & ROM_RG1__RX_16MHZ_EN_MASK) >> ROM_RG1__RX_16MHZ_EN_POS; 
		return (csr_val);
}

#else
/*
 * Name: RomRx16MhzEnRead
 * Purpose: Read rx_16mhz_en RG
 * Input: 
 * Output:
 * Note: 
 *    
 */
U32 RomRx16MhzEnRead(void)
{
		U32 csr_val;
		csr_val = (CentauriCsrRead(PMU_CSR__RF_CHANNEL) & RF_CHANNEL__RX_16MHZ_EN_MASK) >> RF_CHANNEL__RX_16MHZ_EN_POS; 
		return (csr_val);
}
#endif
/*
 * Name: RomMrfskSelRead
 * Purpose: Read Rom mrfsk_sel RG
 * Input: 
 * Output:
 * Note: 
 *      mrfsk_sel: 0 => 2fsk ; 1 => 4fsk ; 
 */
U32 RomMrfskSelRead(void)
{
	U32 csr_val;
	csr_val = (CentauriCsrRead(PMU_CSR__ROM_RG1)&(ROM_RG1__MRFSK_SEL_MASK)) >> ROM_RG1__MRFSK_SEL_POS;

	return csr_val;
		
}
/*
* Name: PhyRxMfAgcKdiffScValRead
* Purpose: Gain initial value
* Input:
*	kdiff_val: MF AGC kdiff value
* Output:
* Note:
*	   
*/
U32 PhyRxMfAgcKdiffScValRead(void)
{
	U32 csr_val;
	csr_val = ((CentauriCsrRead(PHY_CSR__RX_MFAGC_CTRL)&RX_MFAGC_CTRL__RG_RX_KDIFF_SC_MASK) >> RX_MFAGC_CTRL__RG_RX_KDIFF_SC_POS);
	return (csr_val);
}
/*
 * Name: PhyGaussianFilterBtSel
 * Purpose: PHY TX Gaussian filter BT
 * Input:
 * 	bt: BT select
 * Output:
 * Note:
 *    0: BT=0.5
 *    1: BT=1
 */
void PhyGaussianFilterBtSel(U8 bt)
{
	U32 csr_val;

	csr_val = CentauriCsrRead(PHY_CSR__PHY_TX_CTRL)&(~PHY_TX_CTRL__RG_GMSK_BT_SEL_MASK);
	csr_val |= ((U32)(bt << PHY_TX_CTRL__RG_GMSK_BT_SEL_POS)&PHY_TX_CTRL__RG_GMSK_BT_SEL_MASK);
	CentauriCsrWrite(PHY_CSR__PHY_TX_CTRL, csr_val);
}
/*
 * Name: PhyBT05CompSet
 * Purpose: Set BT05 Comp
 * Input:
 * Output:
 */

void PhyBT05CompSet(U8 BT05Comp)
{
	U32 csr_val;
	csr_val = CentauriCsrRead(PHY_CSR__RX_MISC_CTRL)&(~RX_MISC_CTRL__RG_RX_BT05_COMP_MASK);
	csr_val |= (((U32)BT05Comp << RX_MISC_CTRL__RG_RX_BT05_COMP_POS)&RX_MISC_CTRL__RG_RX_BT05_COMP_MASK);
	CentauriCsrWrite(PHY_CSR__RX_MISC_CTRL, csr_val);
}
/*
 * Name: PhyZcBlkTh
 * Purpose:  
 * Input: 
 * Output: 
 * Note:PhyZcBlkTh
 *
 */
void PhyZcBlkTh(U32 input)
{
	U32 csr_val;
	
	csr_val = (CentauriCsrRead(PHY_CSR__RX_TIME_RCVY_CTRL)&(~RX_TIME_RCVY_CTRL__RG_ZC_BLOCK_TH_MASK));
	csr_val |= ((input << RX_TIME_RCVY_CTRL__RG_ZC_BLOCK_TH_POS) & RX_TIME_RCVY_CTRL__RG_ZC_BLOCK_TH_MASK);
	CentauriCsrWrite(PHY_CSR__RX_TIME_RCVY_CTRL, csr_val);
}
/*
 * Name: PhyMfagcTapSel
 * Purpose:  
 * Input: 
 * Output: 
 * Note: MF taps selction
 * 0: 3 taps for rg_sps=4 or 5
 * 1: 7 taps for rg_sps=10
 */
void PhyMfagcTapSel(U32 input)
{
	U32 csr_val;
	
	csr_val = (CentauriCsrRead(PHY_CSR__RX_MFAGC_CTRL)&(~RX_MFAGC_CTRL__RG_MF_TAPS_SEL_MASK));
	csr_val |= ((input << RX_MFAGC_CTRL__RG_MF_TAPS_SEL_POS) & RX_MFAGC_CTRL__RG_MF_TAPS_SEL_MASK);
	CentauriCsrWrite(PHY_CSR__RX_MFAGC_CTRL, csr_val);
}
/*
 * Name: RomRfIfBandRead
 * Purpose: Read rf if band RG
 * Input: 
 * Output:
 * Note: 
 *       rf if band store in hz, this value support from 0 Hz to 524287 Hz
 */
U32 RomRfIfBandRead(void)
{
		U32 csr_val;
		csr_val = (CentauriCsrRead(PMU_CSR__ROM_RG2) & ROM_RG2__RF_IF_BAND_MASK) >> ROM_RG2__RF_IF_BAND_POS; 
		return (csr_val);
}
/*
 * Name: IfRxLpfBandSel 
 * Purpose: RXIF LPF low-pass band frequecny selection 
 * Input: lpf_band_sel 
 * Output:
 * Note: 
 */
void IfRxLpfBandSel(U8 lpf_band_sel)
{
	U32 csr_val;

	csr_val = CentauriCsrRead(FE_CSR_VCORE__IFRX_CTRL)&(~IFRX_CTRL__RG_RXLPF_BAND_MASK);
	csr_val |= (((U32)lpf_band_sel << IFRX_CTRL__RG_RXLPF_BAND_POS)&IFRX_CTRL__RG_RXLPF_BAND_MASK);
	CentauriCsrWrite(FE_CSR_VCORE__IFRX_CTRL, csr_val);
}
/*
 * Name: PhyRxDecimFactorCtrl
 * Purpose: Config the corresponding decimation factor
 * Input:
 * 	decim_factor_ctrl: final decimation factor
 * Output:
 * Note:
 *    Config following fileds for decimation factor:
 *      RX_FILT_CTRL__RG_RX_PREDECIM_FACTOR_MASK
 *      RX_FILT_CTRL__RG_RX_CIC1_DF_MASK
 *      RX_FILT_CTRL__RG_RX_CIC2_DF_MASK
 *      RX_FILT_CTRL__RG_RX_COMP_BYPASS_MASK
 *      RX_FILT_CTRL__RG_RX_DECIM_BYPASS_MASK
 *      RX_FILT_CTRL__RG_RX_D2_FILT_BYPASS_MASK
 *      RX_FILT_CTRL__RG_RX_DECIM_D1_FILT_EN_MASK
 */
void PhyRxDecimFactorCtrl(U32 decim_factor_ctrl)
{
	U32 csr_val;

	csr_val = CentauriCsrRead(PHY_CSR__RX_FILT_CTRL)&(~RX_FILT_CTRL__DECIM_FACTOR_MASK);
	csr_val |= (decim_factor_ctrl&RX_FILT_CTRL__DECIM_FACTOR_MASK);
	CentauriCsrWrite(PHY_CSR__RX_FILT_CTRL, csr_val);
}
/*
 * Name: PhyRxSamplePerSymbolConfig 
 * Purpose: Sample per symbol.
 * Input:
 * 	sps_val
 * Output:
 * Note: 
 */
void PhyRxSamplePerSymbolConfig(U16 sps_val)
{
	U32 csr_val;

	csr_val = CentauriCsrRead(PHY_CSR__RX_TIME_RCVY_CTRL2)&(~RX_TIME_RCVY_CTRL2__RG_SPS_MASK);
	csr_val |= ((U32)(sps_val << RX_TIME_RCVY_CTRL2__RG_SPS_POS)&RX_TIME_RCVY_CTRL2__RG_SPS_MASK);
	CentauriCsrWrite(PHY_CSR__RX_TIME_RCVY_CTRL2, csr_val);
}
/*
 * Name: PhyRxSpsSampleTimeSel 
 * Purpose: Sampling sample time select: 
 *        Select which sample in symbol for data sampling.
 * Input:
 * 	sps_k_sel
 * Output:
 * Note: 
 *     For SubGHz mode, the legal setting will be 1 to Sps2TR.
 *     For CSS mode, the legal setting will be 1 to ss_gain.
 */
void PhyRxSpsSampleTimeSel(U16 sps_k_sel)
{
	U32 csr_val;

	csr_val = CentauriCsrRead(PHY_CSR__RX_TIME_RCVY_CTRL2)&(~RX_TIME_RCVY_CTRL2__RG_SAMPLING_K_SEL_MASK);
	csr_val |= ((U32)(sps_k_sel << RX_TIME_RCVY_CTRL2__RG_SAMPLING_K_SEL_POS)&RX_TIME_RCVY_CTRL2__RG_SAMPLING_K_SEL_MASK);
	CentauriCsrWrite(PHY_CSR__RX_TIME_RCVY_CTRL2, csr_val);
}
/*
 * Name: RomMfagcDoubleRead
 * Purpose:  
 * Input: 
 * Output: 
 * Note:
 */
U32 RomMfagcDoubleRead(void)
{
	U32 csr_val;
	
	csr_val = ((CentauriCsrRead(PMU_CSR__ROM_RG1)&ROM_RG1__MFAGC_DOUBLE_MASK) >> ROM_RG1__MFAGC_DOUBLE_POS);

	return (csr_val);
}
/*
* Name: PhyRxMfAgcKdiffScVal
* Purpose: Gain initial value
* Input:
*	kdiff_val: MF AGC kdiff value
* Output:
* Note:
*	   
*/
void PhyRxMfAgcKdiffScVal(U32 kdiff_val)
{
		U32 csr_val;
	
		csr_val = CentauriCsrRead(PHY_CSR__RX_MFAGC_CTRL)&(~RX_MFAGC_CTRL__RG_RX_KDIFF_SC_MASK);
		csr_val |= ((kdiff_val << RX_MFAGC_CTRL__RG_RX_KDIFF_SC_POS)&RX_MFAGC_CTRL__RG_RX_KDIFF_SC_MASK);
		CentauriCsrWrite(PHY_CSR__RX_MFAGC_CTRL, csr_val);
}
/*
 * Name: PhyRxMfAgcGainInitVal
 * Purpose: Gain initial value
 * Input:
 * 	init_val: MF AGC gain inital value
 * Output:
 * Note:
 *    10 bits unsigned. <0,2,8> format. 
 *	Default = 1.
 */
void PhyRxMfAgcGainInitVal(U32 init_val)
{
	U32 csr_val;

	csr_val = CentauriCsrRead(PHY_CSR__RX_MFAGC_CTRL)&(~RX_MFAGC_CTRL__RG_MFAGC_INI_MASK);
	csr_val |= ((init_val << RX_MFAGC_CTRL__RG_MFAGC_INI_POS)&RX_MFAGC_CTRL__RG_MFAGC_INI_MASK);
	CentauriCsrWrite(PHY_CSR__RX_MFAGC_CTRL, csr_val);
}
/*
 * Name: PhyRxFoDcrFactorSet
 * Purpose: set Fo Dcr RG
 * Input: 
 * Output: 
 * Note: 
 *    set all field except sps_inv
 */
void PhyRxFoDcrFactorSet(U32 dcr_factor)
{
	U32 csr_val;
	
	csr_val = (CentauriCsrRead(PHY_CSR__RX_FO_DCR)&(~RX_FO_DCR__DCR_FACTOR_MASK));
	csr_val |= (((U32)dcr_factor ) & RX_FO_DCR__DCR_FACTOR_MASK);
	CentauriCsrWrite(PHY_CSR__RX_FO_DCR, csr_val);
}
#if Centauri_B2
U32 RomLowSideInjRead(void)
{
		U32 csr_val;
		csr_val = (CentauriCsrRead(PMU_CSR__ROM_RG1) & ROM_RG1__LO_SIDE_INJ_MASK) >> ROM_RG1__LO_SIDE_INJ_POS; 
		return (csr_val);
}

#else
/*
 * Name: RomLowSideInjRead
 * Purpose: Read LowSideInj RG
 * Input: 
 * Output:
 * Note: 
 *     low_side_injection: 0 => High_side_injection ; 1 => low_side_injection
 */
U32 RomLowSideInjRead(void)
{
		U32 csr_val;
		csr_val = (CentauriCsrRead(PMU_CSR__ROM_IQC2) & ROM_IQC2_LO_SIDE_INJ_MASK) >> ROM_IQC2_LO_SIDE_INJ_POS; 
		return (csr_val);
}
#endif
/*
 * Name: PhyLocalIfFreqOffsetConfig
 * Purpose: Local IF frequency
 * Input:
 * Output:
 * Note:
 *    format: <1,0,12>
 */
void PhyRxDigitalIfFreqOffsetConfig(U32 Digi_if_freq)
{
	U32 csr_val;

	csr_val = CentauriCsrRead(PHY_CSR__RX_IQC_DDC_CTRL)&(~RX_IQC_DDC_CTRL__RG_IF_FREQ_OFFSET_MASK);
	csr_val |= ((Digi_if_freq << RX_IQC_DDC_CTRL__RG_IF_FREQ_OFFSET_POS)&RX_IQC_DDC_CTRL__RG_IF_FREQ_OFFSET_MASK);
	CentauriCsrWrite(PHY_CSR__RX_IQC_DDC_CTRL, csr_val);
}
/*
 * Name: RomPhyClockRead
 * Purpose: [For ROM code] Read PHY clock selection from retention RG
 * Input: 
 * Output: 
 * Note: 
 *     0: 32MHz
 *     1: 24MHz
 */
U32 RomPhyClockRead(void)
{
	U32 csr_val;
	
	csr_val = ((CentauriCsrRead(PMU_CSR__ROM_RG3)&ROM_RG3__PHY_CLOCK_MASK) >> ROM_RG3__PHY_CLOCK_POS);

	return (csr_val);
}
/*
 * Name: Phy4fskThreshSet
 * Purpose: Set 4fsk threshold
 * Input:
 * Output:
 */

void Phy4fskThreshSet(U8 input)
{
	U32 csr_val;
	csr_val = CentauriCsrRead(PHY_CSR__RX_MISC_CTRL)&(~RX_MISC_CTRL__RG_SH_FSK4_THRESHOLD_MASK);
	csr_val |= (((U32)input << RX_MISC_CTRL__RG_SH_FSK4_THRESHOLD_POS)&RX_MISC_CTRL__RG_SH_FSK4_THRESHOLD_MASK);
	CentauriCsrWrite(PHY_CSR__RX_MISC_CTRL, csr_val);
}

/*
 * Name: RomTxSynthDcbSelSet
 * Purpose: 
 * Input: 
 * Output: 
 * Note: default set 0
 */
void RomTxSynthDcbSelSet(U32 input)
{
	U32 csr_val;
	
	csr_val = (CentauriCsrRead(PMU_CSR__ROM_IQC2)&(~ROM_IQC2__TX_SYNTH_DCBSEL_MASK));
	csr_val |= ((input << ROM_IQC2__TX_SYNTH_DCBSEL_POS)&ROM_IQC2__TX_SYNTH_DCBSEL_MASK);
	CentauriCsrWrite(PMU_CSR__ROM_IQC2, csr_val);
}

/*
 * Name: RomTxSynthDczSelSet
 * Purpose: RX_SYNTH_DCBSEL
 * Input: 
 * Output: 
 * Note: default set 7
 */
void RomTxSynthDczSelSet(U32 input)
{
	U32 csr_val;
	
	csr_val = (CentauriCsrRead(PMU_CSR__ROM_RG2)&(~ROM_RG2__TX_SYNTH_DCZSEL_MASK));
	csr_val |= ((input << ROM_RG2__TX_SYNTH_DCZSEL_POS)&ROM_RG2__TX_SYNTH_DCZSEL_MASK);
	CentauriCsrWrite(PMU_CSR__ROM_RG2, csr_val);
}

/*
 * Name: RomTxSynthDrSelSet
 * Purpose: 
 * Input: 
 * Output: 
 * Note: default set 2
 */
void RomTxSynthDrSelSet(U32 input)
{
	U32 csr_val;
	
	csr_val = (CentauriCsrRead(PMU_CSR__ROM_RG3)&(~ROM_RG3__TX_SYNTH_DRSEL_MASK));
	csr_val |= ((input << ROM_RG3__TX_SYNTH_DRSEL_POS)&ROM_RG3__TX_SYNTH_DRSEL_MASK);
	CentauriCsrWrite(PMU_CSR__ROM_RG3, csr_val);
}

/*
 * Name: RomTxSynthIcPSelSet
 * Purpose: 
 * Input: 
 * Output: 
 * Note: default 24
 */
void RomTxSynthIcPSelSet(U32 input)
{
	U32 csr_val;
	
	csr_val = (CentauriCsrRead(PMU_CSR__ROM_RG5)&(~ROM_RG5__TX_SYNTH_ICPSEL_MASK));
	csr_val |= ((input << ROM_RG5__TX_SYNTH_ICPSEL_POS)&ROM_RG5__TX_SYNTH_ICPSEL_MASK);
	CentauriCsrWrite(PMU_CSR__ROM_RG5, csr_val);
}

/*
 * Name: RomSynthDf3rdHiRetSet
 * Purpose: SYNTH_DF3RDHI_RET
 * Input: 
 * Output: 
 * Note: 
 */
void RomSynthDf3rdHiRetSet(U32 input)
{
	U32 csr_val;
	
	csr_val = (CentauriCsrRead(PMU_CSR__ROM_RG2)&(~ROM_RG2__SYNTH_DF3RDHI_RET_MASK));
	csr_val |= ((input << ROM_RG2__SYNTH_DF3RDHI_RET_POS)&ROM_RG2__SYNTH_DF3RDHI_RET_MASK);
	CentauriCsrWrite(PMU_CSR__ROM_RG2, csr_val);
}

void RfTxPaPwrDownCtrlAuto(void)
{   
    U32 csr_val;    
    csr_val = CentauriCsrRead(FE33_CSR__TX_CTRL)&(~TX_CTRL__RG_RFTXPA_PWD_MAN_MASK);    
    CentauriCsrWrite(FE33_CSR__TX_CTRL, csr_val);
}

/*
 * Name: RfTxPaDtpcCtrlManual 
 * Purpose: digital transmit power control
 * Input: 
 * Output:
 * Note: 
 *     0 : auto (PHY)
 *     1 : manual (CSR, default)
 */
void RfTxPaDtpcCtrlManual(void)
{
	U32 csr_val;

	csr_val = CentauriCsrRead(FE33_CSR__TX_CTRL)|(TX_CTRL__RG_RFTXPA_DTPC_MAN_MASK);
	CentauriCsrWrite(FE33_CSR__TX_CTRL, csr_val);
}

/*
 * Name: RfTxPaGainCtrl 
 * Purpose: Programmable PA variable gain control; 1dB/step
 * Input: 
 *     gain_val: TX PA gain control. (default: 31)
 * Output:
 * Note: 
 */
void RfTxPaGainCtrl(U32 gain_val)
{
	U32 csr_val;

	csr_val = CentauriCsrRead(FE33_CSR__TX_CTRL)&(~TX_CTRL__RG_RFTXPA_DTPC_MASK);
	csr_val |= ((gain_val << TX_CTRL__RG_RFTXPA_DTPC_POS)&TX_CTRL__RG_RFTXPA_DTPC_MASK);
	CentauriCsrWrite(FE33_CSR__TX_CTRL, csr_val);
}

/*
 * Name: RomTxPwrGainCodeSet
 * Purpose: Set Rom tx_power_gain_code RG
 * Input: 
 * Output:
 * Note: 
 *       tx_power_gain_code_config: value from 0 to 20
 */
void RomTxPwrGainCodeSet(U32 tx_pwr_gain_code)
{
		U32 csr_val;
		csr_val = (CentauriCsrRead(PMU_CSR__ROM_RG2)&(~ROM_RG2__TX_PWR_GAIN_CODE_MASK));
		csr_val |= (((U32)tx_pwr_gain_code << ROM_RG2__TX_PWR_GAIN_CODE_POS)&ROM_RG2__TX_PWR_GAIN_CODE_MASK);
		CentauriCsrWrite(PMU_CSR__ROM_RG2, csr_val);
		
}
/*
 * Name: PhyTxPreambleLenFraBitConfig
 * Purpose: Preamble Length , bit part 
 * Input:
 * 	MIN Preamble length is ONE octet when rg_tx_preamble_len=1
 *	MAX Preamble length is 2048 octets when rg_tx_preamble_len=0
 * Output:
 * Note:
 *    
 */
void PhyTxPreambleLenFraBitConfig(U16 len)
{
	U32 csr_val;

	csr_val = CentauriCsrRead(PHY_CSR__PHYTX_CFG0)&(~PHYTX_CFG0__RG_TX_PREAMBLE_FRABIT_MASK);
	csr_val |= ((U32)(len << PHYTX_CFG0__RG_TX_PREAMBLE_FRABIT_POS)&PHYTX_CFG0__RG_TX_PREAMBLE_FRABIT_MASK);
	CentauriCsrWrite(PHY_CSR__PHYTX_CFG0, csr_val);
}
/*
 * Name: PhyTxPreambleLenConfig
 * Purpose: Preamble Length of octet
 * Input:
 * 	MIN Preamble length is ONE octet when rg_tx_preamble_len=1
 *	MAX Preamble length is 2048 octets when rg_tx_preamble_len=0
 * Output:
 * Note:
 *    
 */
void PhyTxPreambleLenConfig(U16 len)
{
	U32 csr_val;

	csr_val = CentauriCsrRead(PHY_CSR__PHYTX_CFG0)&(~PHYTX_CFG0__RG_TX_PREAMBLE_LEN_MASK);
	csr_val |= ((U32)(len << PHYTX_CFG0__RG_TX_PREAMBLE_LEN_POS)&PHYTX_CFG0__RG_TX_PREAMBLE_LEN_MASK);
	CentauriCsrWrite(PHY_CSR__PHYTX_CFG0, csr_val);
}

/*
 * Name: RomTxPaPwrSelRead
 * Purpose: Read tx_pa_power_sel RG
 * Input: 
 * Output:
 * Note: 
 *        tx_pa_power_sel: 0 => MPA ; 1 => HPA
 */
U32 RomTxPaPwrSelRead(void)
{
		U32 csr_val;
		csr_val = (CentauriCsrRead(PMU_CSR__ROM_RG2) & ROM_RG2__TX_PA_SEL_MASK) >> ROM_RG2__TX_PA_SEL_POS; 
		return (csr_val);
}


void PhySfdPattern0Config(U16 tmp)
{
	U32 csr_val;

	csr_val = CentauriCsrRead(PHY_CSR__SFD_PATTERN)&(~SFD_PATTERN__RG_SFD_PAT0_MASK);
	csr_val |= ((U32)(tmp << SFD_PATTERN__RG_SFD_PAT0_POS)&SFD_PATTERN__RG_SFD_PAT0_MASK);
	CentauriCsrWrite(PHY_CSR__SFD_PATTERN, csr_val);
}
void PhyPhrLenConfig(U16 tmp)
{
	U32 csr_val;

	csr_val = CentauriCsrRead(PHY_CSR__PHY_PHR_CRC_COEF)&(~PHY_PHR_CRC_COEF__RG_PHR_LEN_MASK);
	csr_val |= ((U32)(tmp << PHY_PHR_CRC_COEF__RG_PHR_LEN_POS)&PHY_PHR_CRC_COEF__RG_PHR_LEN_MASK);
	CentauriCsrWrite(PHY_CSR__PHY_PHR_CRC_COEF, csr_val);
}

void PhyPhrRevConfig(U16 tmp)
{
	U32 csr_val;

	csr_val = CentauriCsrRead(PHY_CSR__PHY_PHR_CRC_COEF)&(~PHY_PHR_CRC_COEF__RG_PHY_PHR_REV_MASK);
	csr_val |= ((U32)(tmp << PHY_PHR_CRC_COEF__RG_PHY_PHR_REV_POS)&PHY_PHR_CRC_COEF__RG_PHY_PHR_REV_MASK);
	CentauriCsrWrite(PHY_CSR__PHY_PHR_CRC_COEF, csr_val);
}


void PhyPhrSkipFiledConfig(U16 tmp)
{
	U32 csr_val;

	csr_val = CentauriCsrRead(PHY_CSR__PHY_PHR_CRC_COEF)&(~PHY_PHR_CRC_COEF__RG_PHY_PHR_IN_PSDU_MASK);
	csr_val |= ((U32)(tmp << PHY_PHR_CRC_COEF__RG_PHY_PHR_IN_PSDU_POS)&PHY_PHR_CRC_COEF__RG_PHY_PHR_IN_PSDU_MASK);
	CentauriCsrWrite(PHY_CSR__PHY_PHR_CRC_COEF, csr_val);
}

void PhyPhrDataWhiteningPN9SeqConfig(U16 tmp)
{
	U32 csr_val;

	csr_val = CentauriCsrRead(PHY_CSR__PHY_PHR_CRC_COEF)&(~PHY_PHR_CRC_COEF__RG_PN9_SEQ_SEL_MASK);
	csr_val |= ((U32)(tmp << PHY_PHR_CRC_COEF__RG_PN9_SEQ_SEL_POS)&PHY_PHR_CRC_COEF__RG_PN9_SEQ_SEL_MASK);
	CentauriCsrWrite(PHY_CSR__PHY_PHR_CRC_COEF, csr_val);
}

void PhyPhrDataWhiteningPN9ApplyConfig(U16 tmp)
{
	U32 csr_val;

	csr_val = CentauriCsrRead(PHY_CSR__PHY_PHR_CRC_COEF)&(~PHY_PHR_CRC_COEF__RG_PN9_BYP_PHR_DIS_MASK);
	csr_val |= ((U32)(tmp << PHY_PHR_CRC_COEF__RG_PN9_BYP_PHR_DIS_POS)&PHY_PHR_CRC_COEF__RG_PN9_BYP_PHR_DIS_MASK);
	CentauriCsrWrite(PHY_CSR__PHY_PHR_CRC_COEF, csr_val);
}


void PhyPhrPsduOrderConfig(U16 tmp)
{
	U32 csr_val;

	csr_val = CentauriCsrRead(PHY_CSR__PHY_PHR_CRC_COEF)&(~PHY_PHR_CRC_COEF__RG_PHY_PSDU_REV_MASK);
	csr_val |= ((U32)(tmp << PHY_PHR_CRC_COEF__RG_PHY_PSDU_REV_POS)&PHY_PHR_CRC_COEF__RG_PHY_PSDU_REV_MASK);
	CentauriCsrWrite(PHY_CSR__PHY_PHR_CRC_COEF, csr_val);
}

void PhyPhrCECStandardConfig(U16 tmp)
{
	U32 csr_val;

	csr_val = CentauriCsrRead(PHY_CSR__PHY_PHR_CRC_COEF)&(~PHY_PHR_CRC_COEF__RG_RX_CEC_FRAME_EN_MASK);
	csr_val |= ((U32)(tmp << PHY_PHR_CRC_COEF__RG_RX_CEC_FRAME_EN_POS)&PHY_PHR_CRC_COEF__RG_RX_CEC_FRAME_EN_MASK);
	CentauriCsrWrite(PHY_CSR__PHY_PHR_CRC_COEF, csr_val);
}

void PhyGaussianFilterConfig(U16 tmp)
{
	U32 csr_val;

	csr_val = CentauriCsrRead(PHY_CSR__PHY_TOP_CTRL)&(~PHY_TOP_CTRL__RG_GFILTER_EN_MASK);
	csr_val |= ((U32)(tmp << PHY_TOP_CTRL__RG_GFILTER_EN_POS)&PHY_TOP_CTRL__RG_GFILTER_EN_MASK);
	CentauriCsrWrite(PHY_CSR__PHY_TOP_CTRL, csr_val);
}
void PhyDataWhiteningConfig(U16 tmp)
{
	U32 csr_val;

	csr_val = CentauriCsrRead(PHY_CSR__PHY_TOP_CTRL)&(~PHY_TOP_CTRL__RG_PN9_EN_MASK);
	csr_val |= ((U32)(tmp << PHY_TOP_CTRL__RG_PN9_EN_POS)&PHY_TOP_CTRL__RG_PN9_EN_MASK);
	CentauriCsrWrite(PHY_CSR__PHY_TOP_CTRL, csr_val);
}

void PhyExtraPsduConfig(U16 tmp)
{
	U32 csr_val;

	csr_val = CentauriCsrRead(PHY_CSR__PHY_RX_CTRL)&(~PHY_RX_CTRL__RG_RX_PSDU_ADD_LEN_MASK);
	csr_val |= ((U32)(tmp << PHY_RX_CTRL__RG_RX_PSDU_ADD_LEN_POS)&PHY_RX_CTRL__RG_RX_PSDU_ADD_LEN_MASK);
	CentauriCsrWrite(PHY_CSR__PHY_RX_CTRL, csr_val);
}
/*
 * Name: PhyChannelBandConfig
 * Purpose: Configure RF Frequency Band
 * Method:
 * Input:
 *    None 
 * Output:
 *    None
 * Note:
 *    
 */
void PhyChannelBandConfig(U32 new_chan_band)
{
	//U32 reg_val;
	//reg_val = (PHY_CSR__RF_FREQ_BAND&(~RF_FREQ_BAND__RG_CHANNEL_BAND_MASK));
	//PHY_CSR__RF_FREQ_BAND = (reg_val | ((new_chan_band&RF_FREQ_BAND__RG_CHANNEL_BAND_MASK)<<RF_FREQ_BAND__RG_CHANNEL_BAND_POS));
	U32 csr_val;

	csr_val = CentauriCsrRead(PHY_CSR__RF_FREQ_BAND)&(~RF_FREQ_BAND__RG_CHANNEL_BAND_MASK);
	csr_val |= (((U32)new_chan_band<<RF_FREQ_BAND__RG_CHANNEL_BAND_POS)&RF_FREQ_BAND__RG_CHANNEL_BAND_MASK);
	CentauriCsrWrite(PHY_CSR__RF_FREQ_BAND, csr_val);
}
/*
 * Name: RomRfChannelRead
 * Purpose: read out Rom Rf channel RG
 * Input:
 * Output:
 * 	rf channel in hz, this value support from 0 kHz to 1048575 kHz
 * 	
 */

U32 RomRfChannelRead(void)
{
    U32 csr_val;
    csr_val = (CentauriCsrRead(PMU_CSR__RF_CHANNEL) & RF_CHANNEL__RF_CHANNEL_FREQ_MASK) >> RF_CHANNEL__RF_CHANNEL_FREQ_POS;	
	

	return (csr_val);
}

/*
 * Name: PhyFecEnable
 * Purpose: Enable FEC control
 * Input:
 * Output:
 * Note:
 *    
 */
void PhyFecEnable(void)
{
    //PHY_CSR__PHY_RX_CTRL |= PHY_TOP_CTRL__RG_FEC_EN_MASK;
	U32 csr_val;

	csr_val = CentauriCsrRead(PHY_CSR__PHY_TOP_CTRL)|PHY_TOP_CTRL__RG_FEC_EN_MASK;
	CentauriCsrWrite(PHY_CSR__PHY_TOP_CTRL, csr_val);
}

/*
 * Name: PhyFecTypeSel
 * Purpose: Select Convolutional code type
 * Input:
 *    fec_type
 *       PHY_FEC_TYPE_NRNSC  0
 *       PHY_FEC_TYPE_RSC      1
 * Output:
 * Note:
 *    
 */
void PhyFecTypeSel(U8 fec_type)
{
    //PHY_CSR__PHY_RX_CTRL |= PHY_TOP_CTRL__RG_NRNSC_RSC_SEL_MASK;
	U32 csr_val;

	csr_val = CentauriCsrRead(PHY_CSR__PHY_TOP_CTRL)&(~PHY_TOP_CTRL__RG_NRNSC_RSC_SEL_MASK);
	csr_val |= (((U32)fec_type<<PHY_TOP_CTRL__RG_NRNSC_RSC_SEL_POS)&PHY_TOP_CTRL__RG_NRNSC_RSC_SEL_MASK);
	CentauriCsrWrite(PHY_CSR__PHY_TOP_CTRL, csr_val);
}


/*
 * Name: PhyRxFecDecodeCtrlMode
 * Purpose: RX FEC software control mode
 * Input:
 * 	ctrl_mode: HW detect automatically or SW control
 * Output:
 * Note:
 *    0: Hardware will automatically detect SFD type to enable FEC Decoder.
 *    1: FEC Decoder is controlled by software control bit "rg_fec_en".
 */
void PhyRxFecDecodeCtrlMode(U8 ctrl_mode)
{
	U32 csr_val;

	csr_val = CentauriCsrRead(PHY_CSR__PHY_RX_CTRL)&(~PHY_RX_CTRL__RG_RX_FEC_SW_MODE_MASK);
	csr_val |= ((U32)(ctrl_mode << PHY_RX_CTRL__RG_RX_FEC_SW_MODE_POS)&PHY_RX_CTRL__RG_RX_FEC_SW_MODE_MASK);
	CentauriCsrWrite(PHY_CSR__PHY_RX_CTRL, csr_val);
}

/*
 * Name: PhyInterleaverEnable
 * Purpose: Enable Interleaver/De-interleaver control
 * Input:
 * Output:
 * Note:
 *    
 */
void PhyInterleaverEnable(void)
{
    //PHY_CSR__PHY_TOP_CTRL |= PHY_TOP_CTRL__RG_INTERLEAVE_EN_MASK;
	U32 csr_val;

	csr_val = CentauriCsrRead(PHY_CSR__PHY_TOP_CTRL)|PHY_TOP_CTRL__RG_INTERLEAVE_EN_MASK;
	CentauriCsrWrite(PHY_CSR__PHY_TOP_CTRL, csr_val);
}

/*
 * Name:PhyInterleaverDisable
 * Purpose: Disable Interleaver/De-interleaver control
 * Input:
 * Output:
 * Note:
 *    
 */
void PhyInterleaverDisable(void)
{
    //PHY_CSR__PHY_TOP_CTRL &= (~PHY_TOP_CTRL__RG_INTERLEAVE_EN_MASK);
	U32 csr_val;

	csr_val = CentauriCsrRead(PHY_CSR__PHY_TOP_CTRL)&(~PHY_TOP_CTRL__RG_INTERLEAVE_EN_MASK);
	CentauriCsrWrite(PHY_CSR__PHY_TOP_CTRL, csr_val);
}

/*
 * Name: PhyRxVtbDecodeSoftEnable
 * Purpose: Enable Viterbi Decoding soft decision
 * Input:
 * Output:
 * Note:
 *    
 */
void PhyRxVtbDecodeSoftEnable(void)
{
	U32 csr_val;

	csr_val = CentauriCsrRead(PHY_CSR__RX_VTDEC_CTRL)|RX_VTDEC_CTRL__RG_VTDEC_SOFT_EN_MASK;
	CentauriCsrWrite(PHY_CSR__RX_VTDEC_CTRL, csr_val);
}

/*
 * Name: PhyRxVtbDecodeSoftDisable
 * Purpose: Disable Viterbi Decoding soft decision
 * Input:
 * Output:
 * Note:
 *    
 */
void PhyRxVtbDecodeSoftDisable(void)
{
	U32 csr_val;

	csr_val = CentauriCsrRead(PHY_CSR__RX_VTDEC_CTRL)&(~RX_VTDEC_CTRL__RG_VTDEC_SOFT_EN_MASK);
	CentauriCsrWrite(PHY_CSR__RX_VTDEC_CTRL, csr_val);
}
/*
 * Name: PhyFecDisable
 * Purpose: Disable FEC control
 * Input:
 * Output:
 * Note:
 *    
 */
void PhyFecDisable(void)
{
    //PHY_CSR__PHY_RX_CTRL &= (~PHY_TOP_CTRL__RG_FEC_EN_MASK);
	U32 csr_val;

	csr_val = CentauriCsrRead(PHY_CSR__PHY_TOP_CTRL)&(~PHY_TOP_CTRL__RG_FEC_EN_MASK);
	CentauriCsrWrite(PHY_CSR__PHY_TOP_CTRL, csr_val);
}
/*
 * Name: RomFecDecodeCtrlSet
 * Purpose: Set Rom fec_decode_ctrl RG
 * Input: 
 * Output:
 * Note: 
 *     fec_decode_ctrl: 0 => HW decoder ; 1 => SW decoder (control by rg_fec_en)
 */
void RomFecDecodeCtrlSet(U32 fec_decode_ctrl)
{
		U32 csr_val;
		csr_val = (CentauriCsrRead(PMU_CSR__RF_CHANNEL)&(~RF_CHANNEL__FEC_DECODE_CTRL_MASK));
		csr_val |= (((U32)fec_decode_ctrl << RF_CHANNEL__FEC_DECODE_CTRL_POS)&RF_CHANNEL__FEC_DECODE_CTRL_MASK);
		CentauriCsrWrite(PMU_CSR__RF_CHANNEL, csr_val);
		
}

U32 PhyInterleaverRead(void)
{
	U32 csr_val;
	
	csr_val = ((CentauriCsrRead(PHY_CSR__PHY_TOP_CTRL)&PHY_TOP_CTRL__RG_INTERLEAVE_EN_MASK) >> PHY_TOP_CTRL__RG_INTERLEAVE_EN_POS);

	return (csr_val);

}

U32 PhyDataWhiteningRead(void)
{
	U32 csr_val;
	
	csr_val = ((CentauriCsrRead(PHY_CSR__PHY_TOP_CTRL)&PHY_TOP_CTRL__RG_PN9_EN_MASK) >> PHY_TOP_CTRL__RG_PN9_EN_POS);

	return (csr_val);

}


/*
 * Name: RfLdo12vCOvREF
 * Purpose: set LDO 1.2V Vref
 * Input: 
 * Output:
 * Note: 
 *     
 */
void RfLdo12vCOvREF(U32 vref)
{
		U32 csr_val;
		csr_val = (CentauriCsrRead(FE33_CSR__LDO_CTRL0)&(~LDO_CTRL0__RG_LDOA12VCOSZ_VREF_MASK));
		csr_val |= (((U32)vref << LDO_CTRL0__RG_LDOA12VCOSZ_VREF_POS)&LDO_CTRL0__RG_LDOA12VCOSZ_VREF_MASK);
		CentauriCsrWrite(FE33_CSR__LDO_CTRL0, csr_val);
		
}

/*
 * Name: PhyInBandRssiCalcuShift
 * Purpose: Shift RSSI value "rx_rssi_ib_lvl" before calculate RSSI to dB
 * Input: 
 * Output: 
 * Note: 
 *       Use 18-bit <0,6,12> In-Band RSSI to calculate dB value
 *       0: rx_rssi_ib_lvl[25:8], set if rg_rssi_ib_method=0
 *       1: rx_rssi_ib_lvl[24:7]
 *       2: rx_rssi_ib_lvl[23:6]
 *       3: rx_rssi_ib_lvl[22:5], set if rg_rssi_ib_method=1
 *       4: rx_rssi_ib_lvl[21:4]
 *       5: rx_rssi_ib_lvl[20:3]
 *       6: rx_rssi_ib_lvl[19:2]
 *       7: rx_rssi_ib_lvl[18:1]
 */
void PhyInBandRssiCalcuShift(U32 rssi_cal_sh)
{
	U32 csr_val;
	
	csr_val = (CentauriCsrRead(PHY_CSR__RX_RSSI_IB)&(~RX_RSSI_IB__RG_RSSI_IB_CAL_SH_MASK));
	csr_val |= ((rssi_cal_sh << RX_RSSI_IB__RG_RSSI_IB_CAL_SH_POS) & RX_RSSI_IB__RG_RSSI_IB_CAL_SH_MASK);
	CentauriCsrWrite(PHY_CSR__RX_RSSI_IB, csr_val);
}

