/**
 * Copyright (c) 2018 Vertexcom Technologies, Inc. All rights reserved
 * Vertexcom Confidential Proprietary
 *
*/

#ifndef __VC_ANA_H
#define __VC_ANA_H

#include <stdint.h>
#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif

#define ADC_CLKSEL_HFRCO 0
#define ADC_CLKSEL_RTCLK 1

#define ADC_DATA_ALIGN_LSB 0
#define ADC_DATA_ALIGN_MSB 1

#define ADC_AUTOTRIGGER_OFF       0
#define ADC_AUTOTRIGGER_TIMER0_OV 4
#define ADC_AUTOTRIGGER_TIMER1_OV 5
#define ADC_AUTOTRIGGER_TIMER2_OV 6
#define ADC_AUTOTRIGGER_TIMER3_OV 7

#define ADC_VREF_INTERNAL_LDO 0
#define ADC_VREF_EXTERNAL_LDO 1

#define ADC_DIFFMODE_SINGLE_END  0
#define ADC_DIFFMODE_DIFF_ENABLE 1

#define ADC_CH0  0
#define ADC_CH1  1
#define ADC_CH2  2
#define ADC_CH3  3
#define ADC_CH4  4
#define ADC_CH5  5
#define ADC_CH6  6
#define ADC_CH7  7
#define ADC_CH8  8
#define ADC_CH9  9
#define ADC_CH10 10
#define ADC_CH11 11
#define ADC_CH12 12
#define ADC_CH13 13
#define ADC_CH14 14
#define ADC_CH15 15

/* ADC channel note:
 * .---------.--------------.
 * | Channel | Source       |
 * .---------.--------------.
 * | 0       | IOA8         |
 * | 1       | IOA9         |
 * | 2       | IOA10        |
 * | 3       | IOA11        |
 * | 4       | IOE4         |
 * | 5       | IOE5         |
 * | 6       | IOE6         |
 * | 7       | IOE7         |
 * | 8       | VDD1         |
 * | 9       | AVDD33       |
 * | 10      | Temperature  |
 * | 11      | VSS          |
 * | 12      | VDD2         |
 * | 13      | VDD3         |
 * | 14      | Reserved     |
 * | 15      | Reserved     |
 * .---------.--------------.
*/

void vcana_config_vdd3_fon(int bHigh);

void vcana_config_lpldo_vsel(int vSel);

void vcana_config_lfxo_cursel(int bHigh);

void vcana_config_lfxo_capsel(int capsel);

void vcana_config_lfrco_pwr(int bHigh);

void vcana_config_hfrco_hf(uint32_t clk);

int vcana_auto_calib_lock(void);


// ADC functions

void vcana_adc_enable(void);

void vcana_adc_disable(void);

void vcana_adc_clk_source_select(uint8_t clksel);

void vcana_adc_force_enable(bool state);

void vcana_adc_config_delay(uint8_t n_adc_clocks);

void vcana_adc_config_data_align(uint8_t adc_data_align);

void vcana_adc_config_continous_mode(bool state);

void vcana_adc_config_clkdiv(uint8_t clkdiv);

void vcana_adc_manual_conversion_start(void);

int vcana_adc_get_manual_conversion_start_status(void);

void vcana_adc_manual_conversion_stop(void);

int vcana_adc_get_manual_conversion_stop_status(void);

void vcana_adc_auto_trigger_source_sel(uint8_t adc_trigger);

void vcana_adc_vref_sel(uint8_t adc_vref);

void vcana_adc_config_differential_mode(uint8_t adc_diff_mode);

void vcana_adc_config_channel_division_enable(uint8_t adc_channel, bool state);

void vcana_adc_config_channel_manual_conversion_enable(uint8_t adc_channel, bool state);

void vcana_adc_config_channel_auto_conversion_enable(uint8_t adc_channel, bool state);

uint32_t vcana_adc_manual_read_data(uint8_t adc_channel);

// Analog low voltage detection functions
#define ANA_LVD_TRIGSEL_2_9_V 0
#define ANA_LVD_TRIGSEL_2_7_V 1
#define ANA_LVD_TRIGSEL_2_5_V 2
#define ANA_LVD_TRIGSEL_2_3_V 3

#define ANA_LVD_DEBSEL_NO      0
#define ANA_LVD_DEBSEL_2_32KHZ 1
#define ANA_LVD_DEBSEL_3_32KHZ 2
#define ANA_LVD_DEBSEL_4_32KHZ 3

#define ANA_LVD_SAMPLE_ALWAYS           0
#define ANA_LVD_SAMPLE_8_RTCLK_CYCLES   1
#define ANA_LVD_SAMPLE_16_RTCLK_CYCLES  2
#define ANA_LVD_SAMPLE_32_RTCLK_CYCLES  3

void vcana_lvd_enable(void);

void vcana_lvd_disable(void);

void vcana_lvd_trigger_sel(uint8_t trigsel);

void vcana_lvd_config_debounce(uint8_t debsel);

void vcana_lvd_config_sample_cycles(uint8_t sample);

void vcana_lvd_int_enable(void);

int vcana_lvd_get_int_sts(void);

void vcana_lvd_clear_int_sts(void);

#ifdef __cplusplus
}
#endif

#endif // __VC_ANA_H

