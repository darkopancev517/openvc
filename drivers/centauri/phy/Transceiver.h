/*
 *  Copyright (C) 2018, Vertexcom Technologies, Inc. - http://www.vertexcom.com/
 *  All rights reserved.
 */



/*
 *  This file is SHARED with ROM code.
 *  PLEASE DON'T MODIFY THIS FILE!!!
*/


#ifndef TRANSCEIVER_H
#define TRANSCEIVER_H

#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Data type definition */
typedef   unsigned char       U8;
typedef   unsigned char*      PU8;
typedef   signed char         S8;
typedef   signed char*        PS8;
typedef   unsigned short int  U16;
typedef   unsigned short int* PU16;
typedef   signed short int    S16;
typedef   signed short int*   PS16;
typedef   unsigned int        U32;
typedef   unsigned int*       PU32;
typedef   signed int          S32;
typedef   signed int*         PS32;

/* Definition */
#define ENABLE  1
#define DISABLE 0
#define TRUE    1
#define FALSE   0

/* SAR ADC Vin channel type */
#define SARADC_VIN_CHAN_SEL_TSSI_VOUT 0 // differential
#define SARADC_VIN_CHAN_SEL_TSENS1    1
#define SARADC_VIN_CHAN_SEL_TSENS2    2
#define SARADC_VIN_CHAN_SEL_BETDET    3
#define SARADC_VIN_CHAN_SEL_TIP_TIN   4 // differential

#define SARADC_SINGLE_END_MODE   0 // single-ended input
#define SARADC_DIFFERENTIAL_MODE 1 // differential input

//#define SARADC_DATA_READY_WAIT_DELAY_10US 1 // unit in 10 us, DATARDY flag will last for 1 us when data ready, wait at least this delay before polling next data ready
#define SARADC_DATA_READY_WAIT_DELAY_30US 30 // unit in 1 us, DATARDY flag will last for 1 us when data ready, wait at least this delay before polling next data ready

#define RX_ADC_CALIBRATION_WAIT_DELAY_50US 50 // unit in 1 us, the calibration time less than 50us. (~30us)

/* LO RX type selection */
#define LO_RXSEL_RX 1
#define LO_RXSEL_TX 0

/* Definition for calibration */
#define DELTA_C_SCALE 5 // the criterion for activating calibration will be DELTA_C_SCALE*cal_delta_in, which cal_delta_in in PHY_ROM_CODE_RESR1
#define CAL_FLAG_VCO_MASK    0x0001 // if cal_flag[0]=1, then do VCO calibration
#define CAL_FLAG_IQ_MASK     0x0002 // if cal_flag[1]=1, then do IQ calibration
//#define CAL_FLAG_TX_PWR_MASK 0x0004 // if cal_flag[2]=1, then do TX power calibration
#define CAL_FLAG_ADC_MASK 0x0004 // if cal_flag[2]=1, then do TX power calibration
/* Retention register usage */
#define SARADC_RESULT_RET  PMU_CSR__RESR1 // retain the SAR ADC results: VCO calibrated temp, IQ calibrated temp and TX accurate pwr TSSI
#define PHY_ROM_CODE_RESR1 PMU_CSR__RESR2 // retain the delta step for calibration criterion assessment
#define PHY_ROM_CODE_RESR2 PMU_CSR__RESR3 // retain the channel band setting for fCAL, this value should be set by HOST
#define RCO_CAL_PARAM_RET  PMU_CSR__RESR4 // retain the RCO32K & RCO4M timer calibration parameter 

/* fields of SARADC_RESULT_RET */
#define VCO_CALIBRATED_TEMP_POS     0
#define VCO_CALIBRATED_TEMP_MASK    0x000003FF // 10bits
#define IQ_CALIBRATED_TEMP_POS      10
#define IQ_CALIBRATED_TEMP_MASK     0x000FFC00 // 10bits
//#define TX_PWR_ACCURATE_TSSI_POS  20
//#define TX_PWR_ACCURATE_TSSI_MASK 0x3FF00000 // 10bits

#define ADC_CALIBRATED_TEMP_POS  20
#define ADC_CALIBRATED_TEMP_MASK 0x3FF00000 // 10bits
/* fields of PHY_ROM_CODE_RESR1 */
#define VCO_CAL_DELTA_C_POS        0
#define VCO_CAL_DELTA_C_MASK       0x0000001F // 5bits
#define IQ_CAL_DELTA_C_POS         5
#define IQ_CAL_DELTA_C_MASK        0x000001E0 // 4bits
//#define TX_PWR_CAL_DELTA_TSSI_POS  9
//#define TX_PWR_CAL_DELTA_TSSI_MASK 0x00003E00 // 5bits
#define ADC_CAL_DELTA_C_POS  9
#define ADC_CAL_DELTA_C_MASK 0x00003E00 // 5bits
#define TX_PWR_ACCURATE_TPC_POS       14
#define TX_PWR_ACCURATE_TPC_MASK      0x000FC000 // 6bits
#define TX_PWR_TPC_ADJ_STEP_POS       20
#define TX_PWR_TPC_ADJ_STEP_MASK      0x01F00000 // 5bits
#define VCO_CAL_ENABLE_POS            29
#define VCO_CAL_ENABLE_MASK           0x20000000 // 1bit
#define IQ_CAL_ENABLE_POS             30
#define IQ_CAL_ENABLE_MASK            0x40000000 // 1bit
#define TX_PWR_CAL_ENABLE_POS         31
#define TX_PWR_CAL_ENABLE_MASK        0x80000000 // 1bit
/* fields of PHY_ROM_CODE_RESR2 */
#define IQ_CAL_FCAL_CHAN_BAND_POS  0
#define IQ_CAL_FCAL_CHAN_BAND_MASK 0x03FFFFFF // 26bits
#define IQ_CAL_FCAL_PGA_GAIN_POS  26
#define IQ_CAL_FCAL_PGA_GAIN_MASK 0xFC000000 // 26bits

/* fields of RCO_CAL_PARAM_RET */
#define RCO_CAL_PARAM_32K_EN_POS  0  
#define RCO_CAL_PARAM_32K_EN_MASK 0x00000001 // 1 bit  
#define RCO_CAL_PARAM_4M_EN_POS  1  
#define RCO_CAL_PARAM_4M_EN_MASK 0x00000002 // 1 bit  
#define RCO_CAL_PARAM_32K_FSEL_POS  4  
#define RCO_CAL_PARAM_32K_FSEL_MASK 0x00000030 // 2 bit  
#define RCO_CAL_PARAM_32K_WIN_POS  6  
#define RCO_CAL_PARAM_32K_WIN_MASK 0x000000C0 // 2 bit  
#define RCO_CAL_PARAM_4M_WIN_POS  16  
#define RCO_CAL_PARAM_4M_WIN_MASK 0x00C00000 // 2 bit  
#define RCO_CAL_PARAM_BLOCK_BEFORE_IQ_CAL_POS  28  
#define RCO_CAL_PARAM_BLOCK_BEFORE_IQ_CAL_MASK 0x10000000 // 1 bit  
#define RCO_CAL_PARAM_BLOCK_BEFORE_DTUNE_CAL_POS  29  
#define RCO_CAL_PARAM_BLOCK_BEFORE_DTUNE_CAL_MASK 0x20000000 // 1 bit  
#define RCO_CAL_PARAM_AFTER_WAKEUP_ENABLE_POS  30  
#define RCO_CAL_PARAM_AFTER_WAKEUP_ENABLE_MASK 0x40000000 // 1 bit  
#define RCO_CAL_PARAM_BEFORE_SLEEP_ENABLE_POS  31  
#define RCO_CAL_PARAM_BEFORE_SLEEP_ENABLE_MASK 0x80000000 // 1 bit  

#ifdef __cplusplus
}
#endif

#endif /* TRANSCEIVER_H */
