
//#include <FreeRTOS.h>


#include "vtprober.h"
//#include "ftgpio.h"
//#include <ftssp.h>
#include <stdio.h>


#include "centauri_host.h"
//#include "centauri_if_prober.h"
#include "centauri_cfg.h"
//#include "centauri_if_queue.h"
#include "centauri_pmu_csr.h"
//#include "centauri_timer.h"

#include "fe_csr_vcore.h"
#include "phy_csr.h"
#include "mac_csr.h"
#include "centauri_host.h"
#include "centauri_mac.h"
//#include "centauri_phy.h"
//#include "centauri_usr.h"
//#include "centauri_host_cfg.h"
//#include "centauri_cmd.h"
//#include "centauri_bm.h"
#include "TransceiverCsr.h"
#include "TransceiverMain.h"
#include "TransceiverInit.h"
#include "pmu_csr.h"
#include "centauri_prober.h"


uint32_t g_sps, iqc_a_b_pmu, iqc_c_pmu;

uint32_t rx_sys_clk ;


uint32_t adc_staus;
uint32_t misc_ctrl0_tmp;

#if HOST_IF_ON
extern uint32_t rx16m_en;
extern uint32_t lowsideinj;
extern uint32_t rx_rf_channel_read;

#endif


void TransceiverCalSetting(void)
{

	/* DIGC = 0 */
	RfRxFeCalDigiGainCtrl(1);
	/* PGA Attack Point = 0 */
	FePgaOutAttackPoint(0);	


}

void TransceiverRssiOffsetSetting(U32 SymRate)
{

	U32 rssi_offset;


	if(50000 == SymRate)
		rssi_offset = 0x0;
	else if(100000 == SymRate)
		rssi_offset = 0x0;
	else if(200000 == SymRate)
		rssi_offset = 0x0;
	else if(250000 == SymRate)
		rssi_offset = 0x0;
	else
		rssi_offset = 0x0;

	PhyRssiOffsetVal(rssi_offset);
}

void TransceiverRssiSetting(void)
{
	CentauriCsrWrite(0x400241a8, 0x3135DC30);
}

void TransceiverDcocSetting(void)
{
	
if(cent_get_version() == 0x7000B3)
{

	/* Read ADC status for ADC reset  */
		adc_staus = CentauriCsrRead(0x4002800c);
	CentauriCsrWrite(FE_CSR_VCORE__RXDCOC_ACC, 0xB1);
#if 1

	U32 csr_val;


	/* DCOC Bias 3 */
	misc_ctrl0_tmp = CentauriCsrRead(FE_CSR_VCORE__MISC_CTRL0);
	csr_val = misc_ctrl0_tmp &(~(MISC_CTRL0__RG_RXPGA_DCOCRO_BIAS_SEL_MASK|MISC_CTRL0__RG_RXPGA_DCOCIN_BIAS_SEL_MASK));
	csr_val |= (((U32)3 << MISC_CTRL0__RG_RXPGA_DCOCRO_BIAS_SEL_POS)&MISC_CTRL0__RG_RXPGA_DCOCRO_BIAS_SEL_MASK);
	csr_val |= (((U32)3 << MISC_CTRL0__RG_RXPGA_DCOCIN_BIAS_SEL_POS)&MISC_CTRL0__RG_RXPGA_DCOCIN_BIAS_SEL_MASK);
	CentauriCsrWrite(FE_CSR_VCORE__MISC_CTRL0, csr_val);

#else

	// DCOC workaround
	// set dcoc setting without using gear shift
	IfRxDcocCapRgMode(); //RG_DCOC_CAP=1;
	CentauriCsrWrite(0x40028030, 0x00000000);
	FeRxIfDcocInBiasConfig(3);
	FeRxIfDcocRoBiasConfig(3);
	CentauriCsrWrite(0x4002804c, 0x000000B1);
	FeRxLpfRctManual();

#endif
}
}

void TransceiverPmeLenSetByRateHan(U32 SymRate)
{
	if(50000 == SymRate)
	{
		RomPmbLenSet(8);
		PhyTxPreambleLenConfig(8);
	}
	else
	{
		RomPmbLenSet(15);
		PhyTxPreambleLenConfig(15);
	}
	
}

void TransceiverPmeLenSetByRate(U32 SymRate)
{

	if(50000 == SymRate || 100000 == SymRate)
		{
		
			RomPmbLenSet(8);
			PhyTxPreambleLenConfig(8);
			
			
#if ROM_VER_B1
			PhyTxPreambleLenFraBitConfig(0);
#else
			RomPmbLenBitPartSet(0); //avalible after B2
		    PhyTxPreambleLenFraBitConfig(0);
#endif
		}
	else if(150000 == SymRate)
		{
			RomPmbLenSet(12);
			PhyTxPreambleLenConfig(12);
			
#if ROM_VER_B1
			PhyTxPreambleLenFraBitConfig(0);
#else
			RomPmbLenBitPartSet(0); //avalible after B2
			PhyTxPreambleLenFraBitConfig(0);
#endif
		}
	else if(200000 == SymRate)
		{
			RomPmbLenSet(16);
			PhyTxPreambleLenConfig(16);
				
#if ROM_VER_B1
			PhyTxPreambleLenFraBitConfig(0);
#else
			RomPmbLenBitPartSet(0); //avalible after B2
			PhyTxPreambleLenFraBitConfig(0);
#endif
		}
	else if(300000 == SymRate)
		{
			RomPmbLenSet(24);
			PhyTxPreambleLenConfig(24);
					
#if ROM_VER_B1
			PhyTxPreambleLenFraBitConfig(0);
#else
			RomPmbLenBitPartSet(0); //avalible after B2
			PhyTxPreambleLenFraBitConfig(0);
#endif
		}

	
}

void GearShiftBiasSet(void)
{
	U32 csr_val;
	//cent_busy_wait(gs_wr_dly);
	//CentauriCsrWrite(0x4002c230,0x0100003B);

	csr_val = misc_ctrl0_tmp &(~(MISC_CTRL0__RG_RXPGA_DCOCRO_BIAS_SEL_MASK|MISC_CTRL0__RG_RXPGA_DCOCIN_BIAS_SEL_MASK));
	csr_val |= (((U32)1 << MISC_CTRL0__RG_RXPGA_DCOCRO_BIAS_SEL_POS)&MISC_CTRL0__RG_RXPGA_DCOCRO_BIAS_SEL_MASK);
	csr_val |= (((U32)1 << MISC_CTRL0__RG_RXPGA_DCOCIN_BIAS_SEL_POS)&MISC_CTRL0__RG_RXPGA_DCOCIN_BIAS_SEL_MASK);
	CentauriCsrWrite(FE_CSR_VCORE__MISC_CTRL0, csr_val);
	

}

void GearShiftBiasSetForIqCal(void)
{

	U32 csr_val;
	while(0 == (CentauriCsrRead(0x4002c238)&0x4000)){}
	//cent_busy_wait(gs_wr_dly);
	//CentauriCsrWrite(0x4002c230,0x0100003B);
	csr_val = misc_ctrl0_tmp &(~(MISC_CTRL0__RG_RXPGA_DCOCRO_BIAS_SEL_MASK|MISC_CTRL0__RG_RXPGA_DCOCIN_BIAS_SEL_MASK));
	csr_val |= (((U32)1 << MISC_CTRL0__RG_RXPGA_DCOCRO_BIAS_SEL_POS)&MISC_CTRL0__RG_RXPGA_DCOCRO_BIAS_SEL_MASK);
	csr_val |= (((U32)1 << MISC_CTRL0__RG_RXPGA_DCOCIN_BIAS_SEL_POS)&MISC_CTRL0__RG_RXPGA_DCOCIN_BIAS_SEL_MASK);
	CentauriCsrWrite(FE_CSR_VCORE__MISC_CTRL0, csr_val);
	

}

void PhyRxDcbIqcLoad (void)
{
	CentauriCsrWrite(PHY_CSR__PHY_RX_IQC_COEF_A_B,iqc_a_b_pmu);
	CentauriCsrWrite(PHY_CSR__PHY_RX_IQC_COEF_C,iqc_c_pmu);
	

}

void EnableErrorPower(void)
{
	U32 csr_tmp;
	csr_tmp = CentauriCsrRead(0x4002417c);
	csr_tmp = (csr_tmp | 0x40 );
	CentauriCsrWrite(0x4002417c,csr_tmp);

}

void DisableErrorPower(void)
{
	U32 csr_tmp;
	csr_tmp = CentauriCsrRead(0x4002417c);
	csr_tmp = (csr_tmp & 0xFFFFFFBF );
	CentauriCsrWrite(0x4002417c,csr_tmp);

}
void ResetErrorPower(void)
{
	U32 csr_tmp;
	csr_tmp = CentauriCsrRead(0x4002417c);
	csr_tmp = (csr_tmp | 0x40 );
	CentauriCsrWrite(0x4002417c,csr_tmp);
	csr_tmp = (csr_tmp & 0xFFFFFFBF );
	CentauriCsrWrite(0x4002417c,csr_tmp);
}


void TransceiverB3Setting(void)
{
#ifndef HCMD_BLOCK
        while(0 == (CentauriCsrRead(0x40028000)&0x10000000)){}
#endif
        /* 1. Rx Phy CLK Enable */
        if(0 == rx_sys_clk)
                CentauriCsrWrite(0x400200a4,0x63F);
        else
                CentauriCsrWrite(0x400200a4,0x67F);

        /* 2. Gear Shift Bias set */
        GearShiftBiasSet();

        /* 3. ADC reset toggle */
        CentauriCsrWrite(0x4002800c,(adc_staus | 0x04000000));
        CentauriCsrWrite(0x4002800c,(adc_staus & 0xFBFFFFFF));
          
        /* 4. IQC param reload*/
        PhyRxDcbIqcLoad();
}

void HostIfSetting(void)
{
#if HOST_IF_ON
	U32 rx_if_band;
	U32 rx_channel;
	U32 rx_rf_channel_read_rx = rx_rf_channel_read;
	rx_if_band = HOST_CTRL_IF;  
	
    if (TRUE == lowsideinj) // low side injection: fLO=fRF-fIF
    {
        if (DISABLE == rx16m_en)
        {
            //phy_param.rx_channel_band_cfg = PhyChannelBandCalculate((sys_param.rf_channel_freq-sys_param.rf_if_band), sys_param.xtal_clock);
    		rx_rf_channel_read_rx -= rx_if_band;
        }
    	else if (ENABLE == rx16m_en)
    	{
    	    //phy_param.rx_channel_band_cfg = PhyChannelBandCalculate((sys_param.rf_channel_freq-(sys_param.rf_if_band/2)), sys_param.xtal_clock);
    		rx_rf_channel_read_rx -= rx_if_band/2;
    	}
    }
    else // high side injection: fLO=fRF+fIF
    {
    	if (DISABLE == rx16m_en)
        {
            //phy_param.rx_channel_band_cfg = PhyChannelBandCalculate((sys_param.rf_channel_freq+sys_param.rf_if_band), sys_param.xtal_clock);
    		rx_rf_channel_read_rx += rx_if_band;
    	}
    	else if (ENABLE == rx16m_en)
    	{
    	    //phy_param.rx_channel_band_cfg = PhyChannelBandCalculate((sys_param.rf_channel_freq+(sys_param.rf_if_band/2)), sys_param.xtal_clock);
    		rx_rf_channel_read_rx += rx_if_band/2;
    	}
    }
    
    rx_channel = PhyChannelBandCalculate(rx_rf_channel_read_rx, 32000000);
    PhyChannelBandConfig(rx_channel);



#endif

}

/*
 * Name: PhyChannelBandCalculate
 * Purpose: Calculate Channel Band
 * Input:
 *	p_phy_param: system related parameters
 * Output:
 * 	band: Result of calculating channel band
 * Note:
 *   format (0, 6, 20) 
 * 	 For Band1(830 ¡V1000 MHz) and Band2 (550 ¡V 800 MHz) : rg_channel_band[25:0] = round (¡§    Wanted RF channel frequency¡¨ / F_xtal*(2^20))
 * 	 For Band3(415 ¡V  510 MHz) and Band4 (275 ¡V 400 MHz) : rg_channel_band[25:0] = round (¡§2*Wanted RF channel frequency¡¨ / F_xtal*(2^20))
 * 	 For Band3(208 ¡V  250 MHz) and Band4 (138 ¡V 200 MHz) : rg_channel_band[25:0] = round (¡§4*Wanted RF channel frequency¡¨ / F_xtal*(2^20))
 */
U32 PhyChannelBandCalculate(U32 channel_freq, U32 clock_val)
{
    //(XTAL clock=32MHz)
    //Formula: Channel Band = "Wanted RF channel freq"/clock*(2^20)
	U32 band, band_rou ,band_acc;
    U32 clock_val_tmp, channel_freq_tmp;

	if ((channel_freq >= 275000000) && (channel_freq <= LO_CTRL_LO_BSEL_BAND3_HIGH))
		channel_freq *= 2;
	else if ((channel_freq >= 138000000) && (channel_freq <= 250000000))
		channel_freq *= 4;

    /* Separate Calculating
         * Example:  868010990 = 868010000 + 990
         *     band_rou: calculate 868010000 roughly
         *     band_acc: calculate 990 accurately
         * Output: 
         *     band = band_rou + band_acc
         */	
    
	// calculate roughly frequency
    clock_val_tmp = clock_val/1000;    //in KHz
    channel_freq_tmp = channel_freq/1000;    //in KHz
	band_rou = (channel_freq_tmp << 12)/(clock_val_tmp>>8) ;

    // Increasing accuracy, calculate less than 1KHz frequency
	band_acc = ((channel_freq%1000) << 20)/clock_val;

	band = band_rou + band_acc;

	return (band);
}

void B2RxSetting(void)
{
	
	AdcReleaseReset();
	
	
	if (10 == g_sps)
	CentauriCsrWrite(PHY_CSR__RX_TIME_RCVY_CTRL,0x43f18033);
	else if (4 == g_sps)
	CentauriCsrWrite(PHY_CSR__RX_TIME_RCVY_CTRL,0x13f18033);
	else
	CentauriCsrWrite(PHY_CSR__RX_TIME_RCVY_CTRL,0x23f18033);

}
void ProfileSetInHost(void)
{
	if(0x1000c350 == CentauriCsrRead(PMU_CSR__ROM_RG4))
		{
			CentauriCsrWrite(0x40024090, 0x23a00111);
			CentauriCsrWrite(0x40024100, 0x00630005);
			CentauriCsrWrite(0x400240f4, 0x32f28311);
			CentauriCsrWrite(0x4002419c, 0x1ecd2058);
		}
}

void TxPreempSetting(U32 SymRate)
{
	//////set preemp coef here 
		
		RomSynthTxHiDataRetSet(DISABLE);
		PhyTxPreempDisable();
		RomPreEmpSet(DISABLE);
		if ( 100000 <= SymRate)
		{
			RomSynthTxHiDataRetSet(ENABLE);
			PhyTxPreempEnable();
			RomPreEmpSet(ENABLE);
            if (100000 == SymRate)
				{
					CentauriCsrWrite(PHY_CSR__PHYTX_PREEMP_COEF1, 0x46F59075);
					CentauriCsrWrite(PHY_CSR__PHYTX_PREEMP_COEF2, 0x0035FF70);
                    RomTxSynthDcbSelSet(5);
                    RomTxSynthDczSelSet(7);
                    RomTxSynthDrSelSet(5);
                    RomTxSynthIcPSelSet(7);
				}
			else if (150000 == SymRate)
				{
					CentauriCsrWrite(PHY_CSR__PHYTX_PREEMP_COEF1, 0x85EFC09C);
					CentauriCsrWrite(PHY_CSR__PHYTX_PREEMP_COEF2, 0x0038FEB0);
                    RomTxSynthDcbSelSet(0);
                    RomTxSynthDczSelSet(1);
                    RomTxSynthDrSelSet(3);
                    RomTxSynthIcPSelSet(20);
				}
			else if (200000 == SymRate)
				{
					CentauriCsrWrite(PHY_CSR__PHYTX_PREEMP_COEF1, 0xD3E910C8);
				    CentauriCsrWrite(PHY_CSR__PHYTX_PREEMP_COEF2, 0x003AFDA0);
                    RomTxSynthDcbSelSet(0);
                    RomTxSynthDczSelSet(1);
                    RomTxSynthDrSelSet(3);
                    RomTxSynthIcPSelSet(20);
				}
			else if (250000 == SymRate)
				{
					CentauriCsrWrite(PHY_CSR__PHYTX_PREEMP_COEF1, 0x32E170F9);
				    CentauriCsrWrite(PHY_CSR__PHYTX_PREEMP_COEF2, 0x003AFC41);		
				}
			else if (300000 == SymRate)
				{
					CentauriCsrWrite(PHY_CSR__PHYTX_PREEMP_COEF1, 0x86DB0121);
				    CentauriCsrWrite(PHY_CSR__PHYTX_PREEMP_COEF2, 0x003BFAE1);			
                    RomTxSynthDcbSelSet(0);
                    RomTxSynthDczSelSet(1);
                    RomSynthDf3rdHiRetSet(1);
                    RomTxSynthDrSelSet(2);
                    RomTxSynthIcPSelSet(24);
				}
			else if (400000 == SymRate)
				{
					CentauriCsrWrite(PHY_CSR__PHYTX_PREEMP_COEF1, 0xABC4A1AD);
				    CentauriCsrWrite(PHY_CSR__PHYTX_PREEMP_COEF2, 0x003DF612);			
				}
		
		}
        else if(50000 == SymRate)
        {
            RomTxSynthDcbSelSet(5);
            RomTxSynthDczSelSet(7);
            RomTxSynthDrSelSet(5);
            RomTxSynthIcPSelSet(7);
        }

}



/*
 * Name: PhyRxDecimationFactorAndSpsFillMfagcInitFeLpfBandSelConfig
 * Purpose: Decide rx decimation filter coefficients and SPS. Config in hardware here.
 * Input:
 *     phy_clock_value: use for calculating OSR
 * Output:
 *     decimation_factor_ctrl: use for find out pre_decimation_factor which will be used to calculate digital IF freq in hexadecimal.
 * Note:
 *     
 */
U32 PhyRxDecimationFactorAndSpsFillMfagcInitFeLpfBandSelConfig(U32 phy_clock_value)
{
	U32 mfgain_tmp, osr;
    U8 sps_temp, sps_sample_sel_temp;

	U32 decimation_factor_ctrl = 0;
	U32 mfagc_ini_input = 0x0;
	U32 dcr_rg_val = 0x0;
	U32 SymRate = RomSymRateRead();
    U32 ModIdx = RomTxHcoeffRead();
	U32 rx_16m_en = RomRx16MhzEnRead();
	U32 MrFsk = RomMrfskSelRead();
    U32 mfagc_kdiff_scal = PhyRxMfAgcKdiffScValRead();

	U32 bypass_sps = 0 ;			//if hard coding 0x4100,by pass set sps
	U32 pmb_acq_ctrl = 0x00F0E070;	 //set default value here
	U32 time_rcvy_ctrl = 0x23F18033; //set default value here
	U32 sfd_ctrl = 0x00000013;		 //set default value here
	U32 deframer_ctrl = 0x007FF000;  //set default value here
	//U32 sfd_ptn = 0x6F4E904E;		 //set default value here
	//U32 sfd_ptn_h = 0x55555555; 	 //set default value here
	U32 phr_crc_coef = 0x40700301;	 //set default value here
	U32 hac_det_ctrl = 0x24100F10;	 //set default value here

    rx_sys_clk = rx_16m_en;
	PhyGaussianFilterBtSel(GAUSSIAN_FILTER_BT_0P5); // Set default value
	PhyBT05CompSet(DISABLE);
	//Phy4fskThreshSet(5);

	CentauriCsrWrite(PHY_CSR__RX_TIME_RCVY_CTRL2, 0x00630005); // write default value
	
    if ((rx_16m_en == 1) && (32000000 == phy_clock_value))
        phy_clock_value = 16000000; //16MHz

    osr = phy_clock_value / SymRate ;

    
    // calculate pre_decimation_factor from osr
    sps_temp = 5;
    sps_sample_sel_temp = 3;

    //switch (osr)
    //{
        if(64 == osr)
        	{
            decimation_factor_ctrl = 0x77d00401;
            sps_temp = 4;
        	}
        else if(80 == osr)
        	{
            decimation_factor_ctrl = 0x00800401;
			pmb_acq_ctrl = 0x0150E070;
        	}  
        else if(128 == osr)
        	{
            decimation_factor_ctrl = 0x01900401;
			bypass_sps = 1 ;
            sps_temp = 8;
			CentauriCsrWrite(PHY_CSR__RX_TIME_RCVY_CTRL2, 0x650008);
			PhyZcBlkTh(3);
			PhyMfagcTapSel(1);
        	}
        else if(160 == osr)
        	{
            if (ModIdx == 0x200) //h=0.5
			{       
                if (SymRate == 200000)
				{
                    decimation_factor_ctrl = 0x12800411;
                }
				else if (SymRate == 100000)
				{
                    decimation_factor_ctrl = 0x23a00411;    //16MHz
                }
				else if (SymRate == 150000)
				{
                    decimation_factor_ctrl = 0x01900411;
					pmb_acq_ctrl = 0x0130E070;
                }
            }
			else if (ModIdx == 0x400) //h=1
			{  
                if (SymRate == 200000)
				{
                    decimation_factor_ctrl = 0x23900411;
                }
				else //rate 100000
				{  
                    decimation_factor_ctrl = 0x34A00411;    //16MHz
                }
            }
			else //h=0.333
			{
                if (SymRate == 200000)
				{
                    decimation_factor_ctrl = 0x24980411;
					/*
						set this 0x4090 value, need to config Decim Fir
						set PMU of Decim Fir P and D to 1
					*/
					sps_temp = 10;
					bypass_sps = 1 ;
					PhyBT05CompSet(ENABLE);
					Phy4fskThreshSet(6);
					CentauriCsrWrite(PHY_CSR__RX_TIME_RCVY_CTRL2, 0x68000A);
					
					
                }
				else //rate 100000
				{  
                    decimation_factor_ctrl = 0x34A00411;	//16MHz
                }
            }
        	}
        else if(320 == osr)
        	{
            if (rx_16m_en == 1)
			{
				if (ModIdx == 0x400) //h=1
				{
                decimation_factor_ctrl = 0x34a00011;
				}
				else  // h=0.5
				{
				decimation_factor_ctrl = 0x23a00011;
				}
			}
			else
			{
                if (ModIdx == 0x200) //h=0.5
				{       
                   	decimation_factor_ctrl = 0x23a00511;                
	            }
				else if (ModIdx == 0x400) //h=1
				{  
    	            decimation_factor_ctrl = 0x34a00511;
        	    }
				else //h=0.333
				{                      
				
            	    decimation_factor_ctrl = 0x12900411;
					bypass_sps = 1 ;
                	sps_temp = 10;    
					CentauriCsrWrite(PHY_CSR__RX_TIME_RCVY_CTRL2, 0x68000A);
                }
            }
        	}
        else if(400 == osr)
        	{
            decimation_factor_ctrl = 0x12a00012;    //16MHz
        	}         
        else if(640 == osr)
        	{
            if (rx_16m_en == 1)
			{
                decimation_factor_ctrl = 0x02900111;    //16MHz
            }
			else
			{
			 if (ModIdx == 0x400) //h=1
				{
                decimation_factor_ctrl = 0x34a00111;
			 	}
			 else  // h = 0.5
			 	{
				decimation_factor_ctrl = 0x23a00111;
			 	}
				
            }
        	}
        else if(800 == osr)
        	{
            if (rx_16m_en == 1)
			{
                decimation_factor_ctrl = 0x13a00021;    //16MHz
            }
			else
            {
                decimation_factor_ctrl = 0x12a00112;
            }           
        	}
        else if(976 == osr)
        	{
			decimation_factor_ctrl = 0x56c00430;
        	}
		else if(1250 == osr) 
			{
			decimation_factor_ctrl = 0x56e80722;  //check again
			}
		else if(1600 == osr) 
			{
			 if (rx_16m_en == 1)
			{
				if(ModIdx == 0x1400) //h=5
				{
					sps_temp = 10;
					decimation_factor_ctrl = 0x77d00021;
			 	}
				else
				{
                	decimation_factor_ctrl = 0x00800021;    //16MHz
                	bypass_sps = 1 ;
                	sps_temp = 10;    
					CentauriCsrWrite(PHY_CSR__RX_TIME_RCVY_CTRL2, 0x67000A);
			 	}
            }
			else
            {
				decimation_factor_ctrl = 0x13a00121;
			}
			}	
        else if(2500 == osr)
        	{

			if(ModIdx == 0x200) //h=0.5
				{
				decimation_factor_ctrl = 0x23b00722;
				}
			else  //h=0.333
				{
				decimation_factor_ctrl = 0x24980722;
				/*
					set this 0x4090 value, need to config Decim Fir
					set PMU of Decim Fir P and D to 2	
				*/
				sps_temp = 10;
				bypass_sps = 1 ;
				CentauriCsrWrite(PHY_CSR__RX_TIME_RCVY_CTRL2, 0x68000A);
				PhyBT05CompSet(ENABLE);
				Phy4fskThreshSet(6);
				}
			
        	}
        else if(3200 == osr)
        	{
            if (rx_16m_en == 1)
			{
                decimation_factor_ctrl = 0x23a00121;    //16MHz
                sps_temp = 10;
            }
			else
			{
				if(ModIdx == 0x1400) //h=5
				{
					sps_temp = 10;
					decimation_factor_ctrl = 0x77d00121;
			 	}
				else
				{
                	decimation_factor_ctrl = 0x00800121;
					bypass_sps = 1 ;
                	sps_temp = 10;    
					CentauriCsrWrite(PHY_CSR__RX_TIME_RCVY_CTRL2, 0x67000A);
				}
            }               
        	}
        else if(5000 == osr)
        	{
            decimation_factor_ctrl = 0x24a00722;
            sps_temp = 10;
			    
			bypass_sps = 1 ;
			PhyBT05CompSet(ENABLE);
			Phy4fskThreshSet(6);
			CentauriCsrWrite(PHY_CSR__RX_TIME_RCVY_CTRL2, 0x68000A);
					
					
        	}
        else if(6400 == osr) 
        	{
            if (rx_16m_en == 1)
			{
                decimation_factor_ctrl = 0x46700121;    //16MHz
                sps_temp = 10;
            }
			else
			{
                decimation_factor_ctrl = 0x23a00221;
                sps_temp = 10;              
            }       
        	}          
        else if(10000 == osr)
        	{
            decimation_factor_ctrl = 0x57c00322;
            sps_temp = 10;
        	} 
        else if(12800 == osr)
        	{
            decimation_factor_ctrl = 0x46700221;
            sps_temp = 10;  
        	}  
        else
        	{
            decimation_factor_ctrl = 0;
        	}
   // }

	//TransceiverDecimFirSet();

    //decide LPF here, accroding to IF, Rate and h
    U32 desire_LPF;
    U8 ifrx_lpf_band_sel;

	/* LPF = IF+BW = IF+ ((1+(2*(MrFsk+1)-1)*h)*sym_rate)/2 */
	/* Note: 512 for more resolution; (ModIdx>>1) before multiplication with sym_rate to avoid overflow */

#if HOST_IF_ON
	desire_LPF = HOST_CTRL_IF + ((((512+((2*(MrFsk+1)-1))*(ModIdx>>1))*SymRate)>>1))/512; 
#else
    desire_LPF = RomRfIfBandRead() + ((((512+((2*(MrFsk+1)-1))*(ModIdx>>1))*SymRate)>>1))/512; 
#endif
    
    desire_LPF = (desire_LPF*11)/10; // margin range 10%
    
    if (desire_LPF <= 220000)
    {
        ifrx_lpf_band_sel = IFRX_LPF_BAND_SEL_220K;
    }
    else if (desire_LPF <= 330000)
    {
        ifrx_lpf_band_sel = IFRX_LPF_BAND_SEL_330K;
    }
    else if (desire_LPF <= 440000)
    {
        ifrx_lpf_band_sel = IFRX_LPF_BAND_SEL_440K;
    }
    else if (desire_LPF <= 550000)
    {
        ifrx_lpf_band_sel = IFRX_LPF_BAND_SEL_550K;
    }
    else if (desire_LPF <= 600000)
    {
        ifrx_lpf_band_sel = IFRX_LPF_BAND_SEL_600K;
    }
    else if (desire_LPF <= 660000)
    {
        ifrx_lpf_band_sel = IFRX_LPF_BAND_SEL_660K;
    }
    else if (desire_LPF <= 770000)
    {
        ifrx_lpf_band_sel = IFRX_LPF_BAND_SEL_770K;
    }
    else
    {
        ifrx_lpf_band_sel = IFRX_LPF_BAND_SEL_880K;
    }
    
    IfRxLpfBandSel(ifrx_lpf_band_sel);

    
    /*********** DCR setting ***********/
    if (SymRate == 2400)
    {
        if(ModIdx == 0x800) // h=2
		{  
            dcr_rg_val = 0x0ecd3238;
        }
    }
	else if (SymRate == 2500)
	{
        if(ModIdx == 0x800) // h=2
		{  
            if (rx_16m_en == 1)
			{
                dcr_rg_val = 0x11cd513a;  //16MHz
            }
            else
			{
                dcr_rg_val = 0x08cd613a;
            }
        }
    }
	else if (SymRate == 4800)
	{
       	if (ModIdx == 0x400)  //h=1
       	{
           	dcr_rg_val = 0x08cd3238;
       	}
		else if(ModIdx == 0x200) //h=0.5
		{  
           	dcr_rg_val = 0x07cd3238;
       	}
		else // h=0.333
		{  
           	dcr_rg_val = 0x08cd3238;
       	}
    }
	else if (SymRate == 5000)
	{
        if (ModIdx == 0x400)  //h=1
        {
            if (rx_16m_en == 1)
			{
               dcr_rg_val = 0x12cd413a;  //16MHz
            }
            else
			{
                dcr_rg_val = 0x09cd513a;
            }
        }
    }
	else if (SymRate == 9600)
	{
        if(ModIdx == 0x200) //h=0.5
		{  
            dcr_rg_val = 0x07cd3238;
        }
		else // h=0.333
		{  
            dcr_rg_val = 0x07cd2238;
        }

    }
	else if (SymRate == 10000)
	{
        if(ModIdx == 0x200)//h=0.5
		{  
            if (rx_16m_en == 1)
			{
                dcr_rg_val = 0x12cd313a;  //16MHz
            }
            else
			{
                dcr_rg_val = 0x09cd413a;
            }
        }
		else if(ModIdx == 0x1400)//h=5
		{
            if (rx_16m_en == 1)
			{
                dcr_rg_val = 0x18cd313a;  //16MHz
            }
            else
			{
                dcr_rg_val = 0x0ccd413a;
            }

		}
    }
	else if (SymRate == 19200) // for HAC only
	{  
        dcr_rg_val = 0x0acd2238;
    }
	else if (SymRate == 20000)
	{
        if(ModIdx == 0x200) //h=0.5
		{  
            if (rx_16m_en == 1)
			{        
                dcr_rg_val = 0x14cd3158; //16MHz
            }
            else
			{
                dcr_rg_val = 0x0acd4158;
            }
        }

    }
	else if (SymRate == 25000)
	{
        if(ModIdx == 0x200) //h=0.5
		{  
            if (rx_16m_en == 1)
			{    
                dcr_rg_val = 0x10cd2058; //16MHz
            }
            else
			{
                dcr_rg_val = 0x08cd3058; 
            }
        }
    }
	else if (SymRate == 40000)
	{
    
        if(ModIdx == 0x200) //h=0.5
		{  
            if (rx_16m_en == 1)
			{            
                dcr_rg_val = 0x24cd1058; //16MHz
            }
            else
			{
                dcr_rg_val = 0x12cd2058;
            }
        }
    }
	else if (SymRate == 50000)
	{
       	if (ModIdx == 0x400)  //h=1
       	{
           	if (rx_16m_en == 1)
			{        
           	    dcr_rg_val = 0x3dcd1058; //16MHz
            }
            else
			{
                dcr_rg_val = 0x1ecd2058;
           	}
        }
		else
		{
           	if (rx_16m_en == 1)
			{        
           	    dcr_rg_val = 0x3dcd1058; //16MHz
            }
            else
			{
                dcr_rg_val = 0x1ecd2058;
           	}

		}
    }
	else if (SymRate == 100000)
	{
       	if (ModIdx == 0x400)  //h=1
   		{
       	    if (rx_16m_en == 1)
			{
       	        dcr_rg_val = 0x20cd1058;  //16MHz
         	}
         	else
			{
           	    dcr_rg_val = 0x10cd2058;
            }
     	}
		else if(ModIdx == 0x200) //h=0.5
		{  
        	   	if (rx_16m_en == 1)
				{
          	      dcr_rg_val = 0x20cd1058;  //16MHz
         	    }
         	    else
				{
           	      dcr_rg_val = 0x10cd2058;
            	}
       	    }
			else
			{  // h=0.333
    	        if (rx_16m_en == 1)
				{
          	      dcr_rg_val = 0x20cd1058;  //16MHz
         	    }
         	    else
				{
           	      dcr_rg_val = 0x10cd1058;
            	}
       	 	}
    }
	else if (SymRate == 150000)
	{
        if(ModIdx == 0x200)
		{  //h=0.5
            dcr_rg_val = 0x15cd1058;
        }
    }
	else if (SymRate == 200000)
	{
        if (ModIdx == 0x400)  //h=1
        {
            dcr_rg_val = 0x10cd1058;
        }
		else if(ModIdx == 0x200)
		{  //h=0.5
            dcr_rg_val = 0x10cd1058;
        }
		else
		{  // h=0.333
            dcr_rg_val = 0x10cd0058;
        }
    }
	else if (SymRate == 250000)
	{
        if(ModIdx == 0x200)
		{  //h=0.5
            dcr_rg_val = 0x10800058;
        }
    }
	else if (SymRate == 300000)
	{
        if(ModIdx == 0x200)
		{  //h=0.5
            dcr_rg_val = 0x15cd0058;
        }
    }
	else if (SymRate == 400000)
	{
        if(ModIdx == 0x200)
		{  //h=0.5
            dcr_rg_val = 0x10cd0058;
        }
    }
	else if (SymRate == 500000)
	{
		dcr_rg_val = 0x10cd0058;
	}
	
		sps_sample_sel_temp = (sps_temp + 1)>>1;

		PhyRxDecimFactorCtrl(decimation_factor_ctrl);
		
		if (bypass_sps == 0)
			{
			PhyRxSamplePerSymbolConfig(sps_temp);
			PhyRxSpsSampleTimeSel(sps_sample_sel_temp);
			}
		//Formula: RX mfgain_tmp = round( 2 x rg_sps / h / (2xPI) x 2^8)
		if ((MrFsk == PHY_MRFSK_TYPE_2FSK)&&(0 == (hac_det_ctrl&0x00010000))&&(ENABLE == RomMfagcDoubleRead()))
		mfgain_tmp = ((((sps_temp<<9)<<FIX_PT_FRACTION_BIT_NUM)/ModIdx)<<FIX_PT_FRACTION_BIT_NUM)/(PI_FIXED_PT);  //ModIdx: format <0,3,10>
		else
		mfgain_tmp = ((((sps_temp<<8)<<FIX_PT_FRACTION_BIT_NUM)/ModIdx)<<FIX_PT_FRACTION_BIT_NUM)/(PI_FIXED_PT);  //ModIdx: format <0,3,10>
	
	
		//rg_rx_kdiff_sc : if (mfgain_tmp<1024) set 0 , else if (mfgain_tmp<2048) set 1, else set 2
		if (mfgain_tmp < 1024)
		{
			PhyRxMfAgcKdiffScVal(PHASE_DIFF_SCALE_X1);
		}
		else if ((mfgain_tmp >= 1024) && (mfgain_tmp < 2048))
		{
			PhyRxMfAgcKdiffScVal(PHASE_DIFF_SCALE_X2);
		}
		else
		{
			PhyRxMfAgcKdiffScVal(PHASE_DIFF_SCALE_X4);
		}

		mfagc_kdiff_scal = PhyRxMfAgcKdiffScValRead();
	
		//Formula: rg_mfagc_ini = round( 2 x rg_sps / (1+rg_rx_kdiff_sc) / h / (2xPI) x 2^8)
		if ((MrFsk == PHY_MRFSK_TYPE_2FSK)&&(0 == (hac_det_ctrl&0x00010000))&&(ENABLE == RomMfagcDoubleRead()))
			mfagc_ini_input = ((((sps_temp<<9)<<(FIX_PT_FRACTION_BIT_NUM-mfagc_kdiff_scal))/ModIdx)<<FIX_PT_FRACTION_BIT_NUM)/(PI_FIXED_PT);
		else
			mfagc_ini_input = ((((sps_temp<<8)<<(FIX_PT_FRACTION_BIT_NUM-mfagc_kdiff_scal))/ModIdx)<<FIX_PT_FRACTION_BIT_NUM)/(PI_FIXED_PT); 
			
		PhyRxMfAgcGainInitVal(mfagc_ini_input);
	

    PhyRxFoDcrFactorSet(dcr_rg_val);
	CentauriCsrWrite(PHY_CSR__RX_TIME_RCVY_CTRL,time_rcvy_ctrl);
	CentauriCsrWrite(PHY_CSR__RX_PREAMBLE_ACQ_CTRL,pmb_acq_ctrl);
	CentauriCsrWrite(PHY_CSR__RX_SFD_CTRL,sfd_ctrl);
	CentauriCsrWrite(PHY_CSR__RX_DEFRAMER_CTRL,deframer_ctrl & (~(RX_DEFRAMER_CTRL__RG_RX_PHR_DOUT_RDY_MASK|RX_DEFRAMER_CTRL__RG_PSDU_START_FLAG_MASK)) );
	//CentauriCsrWrite(PHY_CSR__SFD_PATTERN,sfd_ptn);
	//CentauriCsrWrite(PHY_CSR__SFD_PATTERN_HIGH_16BIT,sfd_ptn_h);
	CentauriCsrWrite(PHY_CSR__PHY_PHR_CRC_COEF,phr_crc_coef);
	CentauriCsrWrite(PHY_CSR__HAC_DET_CTRL,hac_det_ctrl );

		if(sps_temp == 10)
			{
			PhyMfagcTapSel(1);
			PhyZcBlkTh(4);
			}
		else if(sps_temp == 4)
			{
			PhyZcBlkTh(1);
			PhyMfagcTapSel(0);

			}
		else if(sps_temp == 5)
			{
			PhyZcBlkTh(2);
			PhyMfagcTapSel(0);
			}

  //////set preemp coef here 
		
		if ( 100000 <= SymRate)
		{
			RomSynthTxHiDataRetSet(ENABLE);
			PhyTxPreempEnable();
			RomPreEmpSet(ENABLE);
            if (100000 == SymRate)
				{
					CentauriCsrWrite(PHY_CSR__PHYTX_PREEMP_COEF1, 0x46F59075);
					CentauriCsrWrite(PHY_CSR__PHYTX_PREEMP_COEF2, 0x0035FF70);
                    RomTxSynthDcbSelSet(5);
                    RomTxSynthDczSelSet(7);
                    RomTxSynthDrSelSet(5);
                    RomTxSynthIcPSelSet(7);
				}
			else if (150000 == SymRate)
				{
					CentauriCsrWrite(PHY_CSR__PHYTX_PREEMP_COEF1, 0x85EFC09C);
					CentauriCsrWrite(PHY_CSR__PHYTX_PREEMP_COEF2, 0x0038FEB0);
		            RomTxSynthDcbSelSet(0);
                    RomTxSynthDczSelSet(1);
                    RomTxSynthDrSelSet(3);
                    RomTxSynthIcPSelSet(20);
				}
			else if (200000 == SymRate)
				{
					CentauriCsrWrite(PHY_CSR__PHYTX_PREEMP_COEF1, 0xD3E910C8);
				    CentauriCsrWrite(PHY_CSR__PHYTX_PREEMP_COEF2, 0x003AFDA0);
                    RomTxSynthDcbSelSet(0);
                    RomTxSynthDczSelSet(1);
                    RomTxSynthDrSelSet(3);
                    RomTxSynthIcPSelSet(20);
				}
			else if (250000 == SymRate)
				{
					CentauriCsrWrite(PHY_CSR__PHYTX_PREEMP_COEF1, 0x32E170F9);
				    CentauriCsrWrite(PHY_CSR__PHYTX_PREEMP_COEF2, 0x003AFC41);		
				}
			else if (300000 == SymRate)
				{
					CentauriCsrWrite(PHY_CSR__PHYTX_PREEMP_COEF1, 0x86DB0121);
				    CentauriCsrWrite(PHY_CSR__PHYTX_PREEMP_COEF2, 0x003BFAE1);			
                    RomTxSynthDcbSelSet(0);
                    RomTxSynthDczSelSet(1);
                    RomSynthDf3rdHiRetSet(1);
                    RomTxSynthDrSelSet(2);
                    RomTxSynthIcPSelSet(24);
				}
			else if (400000 == SymRate)
				{
					CentauriCsrWrite(PHY_CSR__PHYTX_PREEMP_COEF1, 0xABC4A1AD);
				    CentauriCsrWrite(PHY_CSR__PHYTX_PREEMP_COEF2, 0x003DF612);			
				}
		
		}
		else
		{
    		if (50000 == SymRate)
            {
                RomTxSynthDcbSelSet(5);
                RomTxSynthDczSelSet(7);
                RomTxSynthDrSelSet(5);
                RomTxSynthIcPSelSet(7);
            }
			RomSynthTxHiDataRetSet(DISABLE);
		    PhyTxPreempDisable();
		    RomPreEmpSet(DISABLE);
		}

		
    return (decimation_factor_ctrl);

}

void TransceiverIfFreqOffsetSet(U32 decimation_factor_ctrl,U32 phy_clock_value)
{
	U32 pre_decim_idx, pre_decimation_factor, freq_offset, digital_if_freq;
	uint32_t pre_decimation_factor_ary[3] = {7, 8 ,10};
    pre_decim_idx = (U8)((decimation_factor_ctrl&RX_FILT_CTRL__RG_RX_PREDECIM_FACTOR_MASK)>>RX_FILT_CTRL__RG_RX_PREDECIM_FACTOR_POS);
    pre_decimation_factor = pre_decimation_factor_ary[pre_decim_idx];
	
	//calculate digital_if_freq
#if HOST_IF_ON
    freq_offset = HOST_CTRL_IF;
#else
    freq_offset = RomRfIfBandRead();   //in Hz
#endif

    
#if 0	 //TBD TBD . After checked, this part can be removed.
    // take pre_decimation_factor to be m1p
    digital_if_freq = (((((freq_offset)*2*3217*pre_decimation_factor) << 2)+(phy_clock_value/1000/2))/(phy_clock_value/1000)); // add (phy_clk/1000/2) for rounding to the nearest interger

    if (ENABLE == RomLowSideInjRead()) // for low side injection, digital frequency offset = -fIF
        digital_if_freq = ((~digital_if_freq)+1); // unsigned representation for negative value
#endif
    
    digital_if_freq = PhyRxDigitalIfFreqCalculate(freq_offset, phy_clock_value, pre_decimation_factor);
    PhyRxDigitalIfFreqOffsetConfig(digital_if_freq);

}

/*
 * Name: PhyRxDigitalIfFreqCalculate
 * Purpose: Calculate digital IF frequency offset
 * Input:
 *	if_band_freq: IF band
 *	phy_clk: phy clock value
 *	m1p: pre-decimation factor
 * Output:
 *	digital_if_freq
 * Note:
 *	Local IF frequency in <1,1,12> format.
 *     - rg_if_freq_offset = -1 x (freq_offset/PHY_CLK) x 2xPi x M1p
 * 	
 */
U32 PhyRxDigitalIfFreqCalculate(S32 if_band_freq, U32 phy_clk, U32 m1p)
{
    /* This function is updated for B1 chip */
    
    U32 freq_offset, digital_if_freq_rou, digital_if_freq;

    if (ENABLE == RomRx16MhzEnRead())
    {
        phy_clk = 16000000;
		if_band_freq = if_band_freq/2;
    }

    freq_offset = (if_band_freq > 0 ? if_band_freq:(-if_band_freq));

	// Format <1,1,12>
    digital_if_freq_rou = (((((freq_offset/1000)*2*PI_FIXED_PT*m1p) << (12-FIX_PT_FRACTION_BIT_NUM))+(phy_clk/1000/2))/(phy_clk/1000)); // add (phy_clk/1000/2) for rounding to the nearest interger
	
    //digital_if_freq_acc = ((((freq_offset%1000)*2*PI_FIXED_PT*m1p) << (12-FIX_PT_FRACTION_BIT_NUM))+phy_clk/2)/phy_clk;

    digital_if_freq = digital_if_freq_rou;


    if (ENABLE == RomLowSideInjRead()) // for low side injection, digital frequency offset = -fIF
        digital_if_freq = ((~digital_if_freq)+1); // unsigned representation for negative value


    //RF_LOG_PHY("if_freq_offset 0x%x"LF, digital_if_freq);

	return (digital_if_freq);
}


/*
*	Name: TransceiverTxPowerSetByCode
*	Purpose: To change Tx power by gain code
*	input: gain code DTPC from 0 to 31
*	Output:  None 
*/
void TransceiverTxPowerSetByCode(U32 gain_code_temp)
{

		RfTxPaDtpcCtrlManual();
		RomTxPaModeSet(TX_PA_POWER_CONTROL_MANUAL);
    // value validation check 
   //    if (0 <= tx_power_att && 31 >= tx_power_att)
	if ((0 <= gain_code_temp) && (31 >= gain_code_temp))
    	{
		RfTxPaGainCtrl(gain_code_temp);   
		//printf("Set tx power gain code = %d \n", gain_code_temp);
   	 	}
    else
    	{
		//printf("Not supported!\n");
    	}

	
	
	RomTxPwrGainCodeSet(gain_code_temp);

	
}



/*
 * Name: PhyProfileConfig
 * Purpose: Reduce code size for general profile setting.
 * Input:
 * Output:
 *     decimation_factor_ctrl: use for find out pre_decimation_factor which will be used to calculate digital IF freq in hexadecimal.
 * Note:
 *     
 */
U32 PhyProfileConfig(void)
{
    U32 SymRate = RomSymRateRead();
    U32 ModIdx = RomTxHcoeffRead();
    U32 rx_16m_en = RomRx16MhzEnRead();
    U32 MrFsk = RomMrfskSelRead();
    U32 hac_det_ctrl = 0x24100F10;
    U32 decimation_factor_ctrl = 0x0;
    U32 dcr_rg_val = 0x0;
    U32 tx_synth_dcb = 0x0;
    U32 tx_synth_dcz = 0x0;
    U32 tx_synth_dr = 0x0;
    U32 tx_synth_icp = 0x0;

    //decide LPF here, accroding to IF, Rate and h
    U32 desire_LPF;
    U8 ifrx_lpf_band_sel;

    /* LPF = IF+BW = IF+ ((1+(2*(MrFsk+1)-1)*h)*sym_rate)/2 */
    /* Note: 512 for more resolution; (ModIdx>>1) before multiplication with sym_rate to avoid overflow */

#if HOST_IF_ON
	desire_LPF = HOST_CTRL_IF + ((((512+((2*(MrFsk+1)-1))*(ModIdx>>1))*SymRate)>>1))/512; 
#else
    desire_LPF = RomRfIfBandRead() + ((((512+((2*(MrFsk+1)-1))*(ModIdx>>1))*SymRate)>>1))/512; 
#endif

    
    desire_LPF = (desire_LPF*11)/10; // margin range 10%
    
    if (desire_LPF <= 220000)
    {
        ifrx_lpf_band_sel = IFRX_LPF_BAND_SEL_220K;
    }
    else if (desire_LPF <= 330000)
    {
        ifrx_lpf_band_sel = IFRX_LPF_BAND_SEL_330K;
    }
    else if (desire_LPF <= 440000)
    {
        ifrx_lpf_band_sel = IFRX_LPF_BAND_SEL_440K;
    }
    else if (desire_LPF <= 550000)
    {
        ifrx_lpf_band_sel = IFRX_LPF_BAND_SEL_550K;
    }
    else if (desire_LPF <= 600000)
    {
        ifrx_lpf_band_sel = IFRX_LPF_BAND_SEL_600K;
    }
    else if (desire_LPF <= 660000)
    {
        ifrx_lpf_band_sel = IFRX_LPF_BAND_SEL_660K;
    }
    else if (desire_LPF <= 770000)
    {
        ifrx_lpf_band_sel = IFRX_LPF_BAND_SEL_770K;
    }
    else
    {
        ifrx_lpf_band_sel = IFRX_LPF_BAND_SEL_880K;
    }
    
    IfRxLpfBandSel(ifrx_lpf_band_sel);


    /* WiSUN Profile: 
         *    Rs: 50k, 100k, 150, 300     (kbps)
         *    h  : 1, 0.5
         */
    //PHY Rx setting: Filter, DCR,  TX pre-emphasis coefficients,  TX synth coefficients, MFAGC, SPS=5, sps_sample_sel=3
    
    switch (SymRate)
    {
        case (300000):           //300kbps, h=0.5  (OSR=80)
            decimation_factor_ctrl = 0x00800401;
            dcr_rg_val = 0x15cd0058;
            tx_synth_dcb = 0;
            tx_synth_dcz = 1;
            tx_synth_dr = 2;
            tx_synth_icp = 24;
            RomSynthDf3rdHiRetSet(1);
			CentauriCsrWrite(PHY_CSR__RX_PREAMBLE_ACQ_CTRL, 0x0150E070);
            CentauriCsrWrite(PHY_CSR__PHYTX_PREEMP_COEF1, 0x86DB0121);
            CentauriCsrWrite(PHY_CSR__PHYTX_PREEMP_COEF2, 0x003BFAE1);
            break;

        case (150000):           //150kbps, h=0.5  (OSR=160)
            decimation_factor_ctrl = 0x01900411;
            dcr_rg_val = 0x15cd1058;           
            tx_synth_dcb = 0;
            tx_synth_dcz = 1;
            tx_synth_dr = 3;
            tx_synth_icp = 20;
			CentauriCsrWrite(PHY_CSR__RX_PREAMBLE_ACQ_CTRL, 0x0130E070);
            CentauriCsrWrite(PHY_CSR__PHYTX_PREEMP_COEF1, 0x85EFC09C);
            CentauriCsrWrite(PHY_CSR__PHYTX_PREEMP_COEF2, 0x0038FEB0);
            break;

        case (100000):
            if (rx_16m_en == 1)
            {
                switch(ModIdx)
                {
                    case (0x200):    //100kbps, h=0.5  (OSR=160)  (16MHz)
                        decimation_factor_ctrl = 0x23a00411;
                        break;

                    case (0x400):    //100kbps, h=1    (OSR=160)  (16MHz)
                        decimation_factor_ctrl = 0x34A00411;
                        break;
                }
                dcr_rg_val = 0x20cd1058;
            }
            else //(rx_16m_en == 0)
            {
                switch(ModIdx)
                {
                    case (0x200):    //100kbps, h=0.5  (OSR=320)  (32MHz)
                        decimation_factor_ctrl = 0x23a00511;
                        break;

                    case (0x400):    //100kbps, h=1    (OSR=320)  (32MHz)
                        decimation_factor_ctrl = 0x34a00511;
                        break;
                }
                dcr_rg_val = 0x1ecd2058;
            }

            tx_synth_dcb = 5;
            tx_synth_dcz = 7;
            tx_synth_dr = 5;
            tx_synth_icp = 7;
			CentauriCsrWrite(PHY_CSR__RX_PREAMBLE_ACQ_CTRL, 0x00F0E070);
            CentauriCsrWrite(PHY_CSR__PHYTX_PREEMP_COEF1, 0x46F59075);
            CentauriCsrWrite(PHY_CSR__PHYTX_PREEMP_COEF2, 0x0035FF70);
            break;

        case (50000):
            if (rx_16m_en == 1)
            {
                switch(ModIdx)
                {
                    case (0x200):    //50kbps, h=0.5  (OSR=320)  (16MHz)
                        decimation_factor_ctrl = 0x23a00011;
                        break;

                    case (0x400):    //50kbps, h=1    (OSR=320)  (16MHz)
                        decimation_factor_ctrl = 0x34a00011;
                        break;
                }
                dcr_rg_val = 0x3dcd1058;
            }
            else //(rx_16m_en == 0)
            {
                switch(ModIdx)
                {
                    case (0x200):    //50kbps, h=0.5  (OSR=640)  (32MHz)
                        decimation_factor_ctrl = 0x23a00111;
                        break;

                    case (0x400):    //50kbps, h=1    (OSR=640)  (32MHz)
                        decimation_factor_ctrl = 0x34a00111;
                        break;
                }
                dcr_rg_val = 0x1ecd2058;
            }

            tx_synth_dcb = 5;
            tx_synth_dcz = 7;
            tx_synth_dr = 5;
            tx_synth_icp = 7;
			CentauriCsrWrite(PHY_CSR__RX_PREAMBLE_ACQ_CTRL, 0x00F0E070);
            break;

        default:
            break;
    }

    PhyRxDecimFactorCtrl(decimation_factor_ctrl);
    PhyRxFoDcrFactorSet(dcr_rg_val);
    PhyZcBlkTh(2);
    PhyMfagcTapSel(0);

    PhyGaussianFilterBtSel(GAUSSIAN_FILTER_BT_0P5); // Set default value
    PhyBT05CompSet(DISABLE);


    RomTxSynthDcbSelSet(tx_synth_dcb);
    RomTxSynthDczSelSet(tx_synth_dcz);
    RomTxSynthDrSelSet(tx_synth_dr);
    RomTxSynthIcPSelSet(tx_synth_icp);

    if (100000 <= SymRate)
    {
        RomSynthTxHiDataRetSet(ENABLE);
        PhyTxPreempEnable();
        RomPreEmpSet(ENABLE);
    }
    else
    {
        RomSynthTxHiDataRetSet(DISABLE);
        PhyTxPreempDisable();
        RomPreEmpSet(DISABLE);
    }

    CentauriCsrWrite(PHY_CSR__RX_TIME_RCVY_CTRL, 0x23F18033);
    CentauriCsrWrite(PHY_CSR__RX_TIME_RCVY_CTRL2, 0x00630005);
    CentauriCsrWrite(PHY_CSR__RX_SFD_CTRL, 0x00000013);
    CentauriCsrWrite(PHY_CSR__RX_DEFRAMER_CTRL, 0x007FF000 & (~(RX_DEFRAMER_CTRL__RG_RX_PHR_DOUT_RDY_MASK|RX_DEFRAMER_CTRL__RG_PSDU_START_FLAG_MASK)) );
    CentauriCsrWrite(PHY_CSR__SFD_PATTERN, 0x6F4E904E);
    CentauriCsrWrite(PHY_CSR__SFD_PATTERN_HIGH_16BIT, 0x55555555);
    CentauriCsrWrite(PHY_CSR__PHY_PHR_CRC_COEF, 0x40700301);
    CentauriCsrWrite(PHY_CSR__HAC_DET_CTRL, 0x24100F10 );
    CentauriCsrWrite(PHY_CSR__HAC_DET_CTRL, hac_det_ctrl);


    U32 mfgain_tmp;
    U8 sps_temp;
    U32 mfagc_ini_input = 0x0;
    U32 mfagc_kdiff_scal = PhyRxMfAgcKdiffScValRead(); 
    
    // calculate pre_decimation_factor from osr
    sps_temp = 5;
    
    //Formula: RX mfgain_tmp = round( 2 x rg_sps / h / (2xPI) x 2^8)
    if ((MrFsk == PHY_MRFSK_TYPE_2FSK)&&(0 == (hac_det_ctrl&0x00010000))&&(ENABLE == RomMfagcDoubleRead()))
        mfgain_tmp = ((((sps_temp<<9)<<FIX_PT_FRACTION_BIT_NUM)/ModIdx)<<FIX_PT_FRACTION_BIT_NUM)/(PI_FIXED_PT);  //ModIdx: format <0,3,10>
    else
        mfgain_tmp = ((((sps_temp<<8)<<FIX_PT_FRACTION_BIT_NUM)/ModIdx)<<FIX_PT_FRACTION_BIT_NUM)/(PI_FIXED_PT);  //ModIdx: format <0,3,10>


    //rg_rx_kdiff_sc : if (mfgain_tmp<1024) set 0 , else if (mfgain_tmp<2048) set 1, else set 2
    if (mfgain_tmp < 1024)
    {
        PhyRxMfAgcKdiffScVal(PHASE_DIFF_SCALE_X1);
    }
    else if ((mfgain_tmp >= 1024) && (mfgain_tmp < 2048))
    {
        PhyRxMfAgcKdiffScVal(PHASE_DIFF_SCALE_X2);
    }
    else
    {
        PhyRxMfAgcKdiffScVal(PHASE_DIFF_SCALE_X4);
    }

    mfagc_kdiff_scal = PhyRxMfAgcKdiffScValRead();

    //Formula: rg_mfagc_ini = round( 2 x rg_sps / (1+rg_rx_kdiff_sc) / h / (2xPI) x 2^8)
    if ((MrFsk == PHY_MRFSK_TYPE_2FSK)&&(0 == (hac_det_ctrl&0x00010000))&&(ENABLE == RomMfagcDoubleRead()))
        mfagc_ini_input = ((((sps_temp<<9)<<(FIX_PT_FRACTION_BIT_NUM-mfagc_kdiff_scal))/ModIdx)<<FIX_PT_FRACTION_BIT_NUM)/(PI_FIXED_PT);
    else
        mfagc_ini_input = ((((sps_temp<<8)<<(FIX_PT_FRACTION_BIT_NUM-mfagc_kdiff_scal))/ModIdx)<<FIX_PT_FRACTION_BIT_NUM)/(PI_FIXED_PT); 
        
    PhyRxMfAgcGainInitVal(mfagc_ini_input);


    return (decimation_factor_ctrl);

}


/*
 * B3 rom don't config Rx filter and IF setting anymore
 * do if on host
 *
 */
void FilterIfSetting(void)
{
    U32 phy_clock_value,decimation_factor_ctrl;   //rex, 20180830
	if (0 == RomPhyClockRead())
		phy_clock_value = 32000000;
	else
		phy_clock_value = 24000000;

	decimation_factor_ctrl = PhyRxDecimationFactorAndSpsFillMfagcInitFeLpfBandSelConfig(phy_clock_value);
	TransceiverIfFreqOffsetSet(decimation_factor_ctrl,phy_clock_value);
	
}


/*
 * Name: FilterIfSettingOptimiz
 * Purpose: Only support 50kbps, 100kbps, 150kbps, 300kbps  &  h=1, 0.5
 * Input: None
 * Output:  None 
 * Note:
 *     (50k, 1)
 *     (50k, 0.5)
 *     (100k, 1)
 *     (100k, 0.5)
 *     (150k, 0.5)
 *     (300k, 0.5)
 */
void FilterIfSettingOptimiz(void)
{
    U32 phy_clock_value, decimation_factor_ctrl;
    
    if (0 == RomPhyClockRead())
        phy_clock_value = 32000000;
    else
        phy_clock_value = 24000000;

    decimation_factor_ctrl = PhyProfileConfig();
    TransceiverIfFreqOffsetSet(decimation_factor_ctrl,phy_clock_value);

}


  

void DLT_698p44_profile(void)
{
#if DLT_698p44_FLAG


/* profile setting */
	// freq = 480.1M
	// h = 5
	// rate = 10

/* Preamble config */
PhyTxPreambleLenConfig(10);
/* SFD config */
PhySfdPattern0Config(0x19CF);

/* PHR config */
PhyPhrLenConfig(3);
PhyPhrRevConfig(1);
PhyPhrSkipFiledConfig(1);
PhyPhrDataWhiteningPN9SeqConfig(1);
PhyPhrDataWhiteningPN9ApplyConfig(1);
PhyPhrPsduOrderConfig(1);
PhyPhrCECStandardConfig(1);

/* Enable Gaussian Filter */
PhyGaussianFilterConfig(1);

/* Enable Datwa Whitening */
PhyDataWhiteningConfig(1);

/* Extra PSDU */
PhyExtraPsduConfig(3);


#endif
}

/*
 * Name: TransceiverFecCtrl
 * Purpose: 
 * Input:
 *     fec_en:   0: disable , 1: enable
 *     fec_type:  0: PHY_FEC_TYPE_NRNSC
 *                     1: PHY_FEC_TYPE_RSC
 *     rx_decode_mode:
 *                     0: HW decoder 
 *                     1: SW decoder (control by rg_fec_en)
 * Output:
 * Note:
 *     phyMRFSKSFD=0 : SFD-uncoded value = 16'h904E
 *     phyMRFSKSFD=1 : SFD-uncoded value = 16'h7A0E
 *     PhyMRFSKSFD=0 : SFD-coded value = 16'h6F4E
 *     PhyMRFSKSFD=1 : SFD-coded value = 16'h632D
 */
void TransceiverFecCtrl(U32 fec_en, U32 fec_type, U32 rx_decode_mode)
{
	
    if (ENABLE == fec_en)
    {
        PhyFecEnable();
        PhyFecTypeSel(fec_type);
        PhyRxFecDecodeCtrlMode(rx_decode_mode);
        RomFecDecodeCtrlSet(rx_decode_mode);
		
		if(0 == fec_type)  // fec type = NRNSC, interleaver MUST turn on
			{
			 PhyInterleaverEnable();	
			}
		
		// interleaver on or data whitening on, VTB soft decode MUST turn off
		if((1 == PhyInterleaverRead())||(1 == PhyDataWhiteningRead()))
			{
			 PhyRxVtbDecodeSoftDisable(); 
			}
		else
			{
  			 PhyRxVtbDecodeSoftEnable();
			}
    }
    else
    {
        PhyFecDisable();
        PhyRxFecDecodeCtrlMode(rx_decode_mode);
        RomFecDecodeCtrlSet(rx_decode_mode);
        PhyInterleaverDisable();
        
    }
}

/*
 * Name: TransceiverFecCtrl
 * Purpose: 
 * Input:
 *     fec_en:   0: disable , 1: enable
 *     fec_type:  0: PHY_FEC_TYPE_NRNSC
 *                     1: PHY_FEC_TYPE_RSC

 * Output:

 */
void TransceiverFecCtrlSwMode(U32 fec_en, U32 fec_type)
{
	
    if (ENABLE == fec_en)
    {
        PhyFecEnable();
        PhyFecTypeSel(fec_type);
        PhyRxFecDecodeCtrlMode(ENABLE);
        RomFecDecodeCtrlSet(ENABLE);
		
		if(0 == fec_type)  // fec type = NRNSC, interleaver MUST turn on
			{
			 PhyInterleaverEnable();	
			}
		
		// interleaver on or data whitening on, VTB soft decode MUST turn off
		if((1 == PhyInterleaverRead())||(1 == PhyDataWhiteningRead()))
			{
			 PhyRxVtbDecodeSoftDisable(); 
			}
		else
			{
  			 PhyRxVtbDecodeSoftEnable();
			}
    }
    else
    {
        PhyFecDisable();
        PhyRxFecDecodeCtrlMode(ENABLE);
        RomFecDecodeCtrlSet(ENABLE);
        PhyInterleaverDisable();
        
    }
}

