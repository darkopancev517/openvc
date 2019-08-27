#ifndef TRANSCEIVERINIT_H
#define TRANSCEIVERINIT_H

#include "Transceiver.h"

#ifdef __cplusplus
extern "C" {
#endif

#define ROM_VER_B1  0
#define HOST_IF_ON  0 
#define HOST_CTRL_IF 373000
#define AUTO_SET_PMB_LEN 1

extern void TransceiverCalSetting(void);
extern void TransceiverRssiOffsetSetting(U32 SymRate);
extern void TransceiverRssiSetting(void);
extern void TransceiverDcocSetting(void);
extern void TransceiverPmeLenSetByRate(U32 SymRate);
extern void B2RxSetting(void);
extern void ProfileSetInHost(void);
extern void TxPreempSetting(U32 SymRate);
extern U32 PhyRxDecimationFactorAndSpsFillMfagcInitFeLpfBandSelConfig(U32 phy_clock_value);
extern void TransceiverIfFreqOffsetSet(U32 decimation_factor_ctrl,U32 phy_clock_value);
extern U32 PhyRxDigitalIfFreqCalculate(S32 if_band_freq, U32 phy_clk, U32 m1p);
extern U32 PhyProfileConfig(void);
extern void FilterIfSetting(void);
extern void FilterIfSettingOptimiz(void);
extern void TransceiverB3Setting(void);
extern void PhyRxDcbIqcLoad (void);
extern void GearShiftBiasSet(void);
extern void GearShiftBiasSetForIqCal(void);
extern void TransceiverPmeLenSetByRateHan(U32 SymRate);
extern void EnableErrorPower(void);
extern void DisableErrorPower(void);
extern void ResetErrorPower(void);
extern void DLT_698p44_profile(void);
extern void HostIfSetting(void);
extern U32 PhyChannelBandCalculate(U32 channel_freq, U32 clock_val);
extern void TransceiverFecCtrl(U32 fec_en, U32 fec_type, U32 rx_decode_mode);
extern void TransceiverFecCtrlSwMode(U32 fec_en, U32 fec_type);

#ifdef __cplusplus
}
#endif

#endif /* TRANSCEIVERINIT_H */
