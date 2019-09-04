/**
 * Copyright (c) 2018 Vertexcom Technologies, Inc. All rights reserved
 * Vertexcom Confidential Proprietary
 *
*/

#ifndef __VC_PWM_H
#define __VC_PWM_H

#include <stdint.h>
#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif

// pwm io pin
#ifndef PWM_IO0
#define PWM_IO0 0 // IOB0
#endif
#ifndef PWM_IO1
#define PWM_IO1 1 // IOB6
#endif
#ifndef PWM_IO2
#define PWM_IO2 2 // IOB13
#endif
#ifndef PWM_IO3
#define PWM_IO3 3 // IOB14
#endif

// pwm channel
#ifndef PWM_CH0
#define PWM_CH0 0
#endif
#ifndef PWM_CH1
#define PWM_CH1 1
#endif
#ifndef PWM_CH2
#define PWM_CH2 2
#endif
#ifndef PWM_CH3
#define PWM_CH3 3
#endif

// pwm ccr (capture/compare register) number
#ifndef PWM_CCR0
#define PWM_CCR0 0
#endif
#ifndef PWM_CCR1
#define PWM_CCR1 1
#endif
#ifndef PWM_CCR2
#define PWM_CCR2 2
#endif

#ifndef PWM_CLKDIV1
#define PWM_CLKDIV1    0
#endif
#ifndef PWM_CLKDIV2
#define PWM_CLKDIV2    1
#endif
#ifndef PWM_CLKDIV4
#define PWM_CLKDIV4    2
#endif
#ifndef PWM_CLKDIV8
#define PWM_CLKDIV8    3
#endif
#ifndef PWM_CLKDIV16
#define PWM_CLKDIV16   4
#endif
#ifndef PWM_CLKDIV32
#define PWM_CLKDIV32   5
#endif
#ifndef PWM_CLKDIV64
#define PWM_CLKDIV64   6
#endif
#ifndef PWM_CLKDIV128
#define PWM_CLKDIV128  7
#endif

#ifndef PWM_MODE_STOP
#define PWM_MODE_STOP       0
#endif
#ifndef PWM_MODE_UPCOUNT
#define PWM_MODE_UPCOUNT    1
#endif
#ifndef PWM_MODE_CONTINOUS
#define PWM_MODE_CONTINOUS  2
#endif
#ifndef PWM_MODE_UPDOWN
#define PWM_MODE_UPDOWN     3
#endif

#ifndef PWM_CLKSRC_APBDIV128
#define PWM_CLKSRC_APBDIV128   0
#endif
#ifndef PWM_CLKSRC_APB
#define PWM_CLKSRC_APB         1
#endif

#ifndef PWM_OUTMODE_CONST
#define PWM_OUTMODE_CONST           0
#endif
#ifndef PWM_OUTMODE_SET
#define PWM_OUTMODE_SET             1
#endif
#ifndef PWM_OUTMODE_TOGGLE_RESET
#define PWM_OUTMODE_TOGGLE_RESET    2
#endif
#ifndef PWM_OUTMODE_SET_RESET
#define PWM_OUTMODE_SET_RESET       3
#endif
#ifndef PWM_OUTMODE_TOGGLE
#define PWM_OUTMODE_TOGGLE          4
#endif
#ifndef PWM_OUTMODE_RESET
#define PWM_OUTMODE_RESET           5
#endif
#ifndef PWM_OUTMODE_TOGGLE_SET
#define PWM_OUTMODE_TOGGLE_SET      6
#endif
#ifndef PWM_OUTMODE_RESET_SET
#define PWM_OUTMODE_RESET_SET       7
#endif

#ifndef PWM_OUTLEVEL_LOW
#define PWM_OUTLEVEL_LOW   0
#endif
#ifndef PWM_OUTLEVEL_HIGH
#define PWM_OUTLEVEL_HIGH  1
#endif

#ifndef PWM_CAPTUREMODE_DISABLE
#define PWM_CAPTUREMODE_DISABLE 0
#endif
#ifndef PWM_CAPTUREMODE_RISING
#define PWM_CAPTUREMODE_RISING  1
#endif
#ifndef PWM_CAPTUREMODE_FALLING
#define PWM_CAPTUREMODE_FALLING 2
#endif
#ifndef PWM_CAPTUREMODE_BOTH
#define PWM_CAPTUREMODE_BOTH    3
#endif

#define PWM_CCINT_CCIFG 0
#define PWM_CCINT_COV   1

#ifndef PWM_OUTSEL0
#define PWM_OUTSEL0 0
#endif
#ifndef PWM_OUTSEL1
#define PWM_OUTSEL1 1
#endif
#ifndef PWM_OUTSEL2
#define PWM_OUTSEL2 2
#endif

#ifndef PWM_CCR0
#define PWM_CCR0 0
#endif

#ifndef PWM_CCR1
#define PWM_CCR1 1
#endif

#ifndef PWM_CCR2
#define PWM_CCR2 2
#endif

void vcpwm_config_reset(uint8_t pwm_ch);

void vcpwm_config_clock_division(uint8_t pwm_ch, uint8_t clk_div);

void vcpwm_config_mode(uint8_t pwm_ch, uint8_t mode);

void vcpwm_config_clock_source(uint8_t pwm_ch, uint8_t clk_src);

void vcpwm_config_enable_int(uint8_t pwm_ch);

void vcpwm_config_disable_int(uint8_t pwm_ch);

int vcpwm_get_int_status(uint8_t pwm_ch);

void vcpwm_clear_int_status(uint8_t pwm_ch);

void vcpwm_config_ccr_period(uint8_t pwm_ch, uint8_t ccr_num, uint16_t period);

uint32_t vcpwm_get_ccr_val(uint8_t pwm_ch, uint8_t ccr_num);

void vcpwm_config_cc_out_mode(uint8_t pwm_ch, uint8_t ccr_num, uint8_t out_mode);

void vcpwm_config_out_level(uint8_t pwm_ch, uint8_t ccr_num, uint8_t level);

void vcpwm_config_out_enable(uint8_t pwm_ch, uint8_t ccr_num, bool state);

void vcpwm_config_out_compare_enable(uint8_t pwm_ch, uint8_t ccr_num);

void vcpwm_config_input_capture_enable(uint8_t pwm_ch, uint8_t ccr_num);

void vcpwm_config_input_capture_mode(uint8_t pwm_ch, uint8_t ccr_num, uint8_t capture_mode);

void vcpwm_config_enable_cc_int(uint8_t pwm_ch, uint8_t ccr_num);

void vcpwm_config_disable_cc_int(uint8_t pwm_ch, uint8_t ccr_num);

uint8_t vcpwm_get_cc_int_status(uint8_t pwm_ch, uint8_t ccr_num, uint8_t cc_int);

void vcpwm_clear_cc_int_status(uint8_t pwm_ch, uint8_t ccr_num, uint8_t cc_int);

void vcpwm_clear_counter(uint8_t pwm_ch);

uint16_t vcpwm_get_counter(uint8_t pwm_ch);

uint8_t vcpwm_get_scci(uint8_t pwm_ch, uint8_t ccr_num);

void vcpwm_outline_select(uint8_t pwm_ch, uint8_t pwm_io, uint8_t out_sel);

#ifdef __cplusplus
}
#endif

#endif // __VC_PWM_H
