/**
 * Copyright (c) 2018 Vertexcom Technologies, Inc. All rights reserved
 * Vertexcom Confidential Proprietary
 *
*/

#ifndef __VC_RTC_H
#define __VC_RTC_H

#include <stdint.h>
#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif

#define RTC_AUTOCAL_DELAY_15_625MS 0
#define RTC_AUTOCAL_DELAY_31_25MS  1
#define RTC_AUTOCAL_DELAY_62_5MS   2
#define RTC_AUTOCAL_DELAY_125MS    3

#define RTC_AUTOCAL_CLKSRC_DISABLE 0
#define RTC_AUTOCAL_CLKSRC_1SEC    1
#define RTC_AUTOCAL_CLKSRC_1MIN    2
#define RTC_AUTOCAL_CLKSRC_1HOUR   3

#define RTC_AUTOCAL_ADCSRC_DATA 0
#define RTC_AUTOCAL_ADCSRC_PORT 1

#define RTC_SECOND  0
#define RTC_MINUTE  1
#define RTC_HOUR    2 
#define RTC_DAY     3
#define RTC_WEEK    4
#define RTC_MONTH   5
#define RTC_YEAR    6

#define RTC_INT_ITV_SITV     0
#define RTC_INT_TIME_ILLEGAL 1
#define RTC_INT_WKUSEC       2
#define RTC_INT_WKUMIN       3
#define RTC_INT_WKUHOUR      4
#define RTC_INT_MIDNIGHT     5
#define RTC_INT_WKUCNT       6
#define RTC_INT_AUTOCAL_DONE 7
#define RTC_INT_CE_ILLEGAL   8
#define RTC_INT_RTC_DIV      10

#define RTC_ITV_SEC   0
#define RTC_ITV_MIN   1
#define RTC_ITV_HOUR  2
#define RTC_ITV_DAY   3
#define RTC_ITV_500MS 4
#define RTC_ITV_250MS 5
#define RTC_ITV_125MS 6
#define RTC_ITV_62MS  7
#define RTC_ITV_SITVSEC 7

#define RTC_CLOCK_32768 0
#define RTC_CLOCK_8192  1
#define RTC_CLOCK_2048  2
#define RTC_CLOCK_512   3

#define RTC_PSCA0_CNTSEL0_CLK 32768
#define RTC_PSCA0_CNTSEL1 2048
#define RTC_PSCA0_CNTSEL2 512
#define RTC_PSCA0_CNTSEL3 128

#define RTC_PSCA2_CNTSEL0 2048
#define MAXRTC_MS   ((0xFFFFFF*125/256) - 1)//(0xFFFFFF/RTC_PSCA2_CNTSEL0*1000)


#define RTC_CNTSEL0     0
#define RTC_CNTSEL1     1
#define RTC_CNTSEL2     2
#define RTC_CNTSEL3     3

#define RTC_MODE_HFD  0
#define RTC_MODE_WAIT 1
#define RTC_MODE_CAP  2
#define RTC_MODE_IDLE 3

void vcrtc_autocal_engine_init(void);

void vcrtc_autocal_deinit(void);

void vcrtc_autocal_period(uint32_t period);

void vcrtc_autocal_delay(uint8_t rtc_autocal_delay);

void vcrtc_autocal_clksrc(uint8_t rtc_autocal_clksrc);

void vcrtc_autocal_adcsrc(uint8_t rtc_autocal_adcsrc);

void vcrtc_autocal_manual_trig_start(void);

void vcrtc_autocal_enable(void);

void vcrtc_autocal_disable(void);

void vcrtc_autocal_wait_done(void);

int vcrtc_autocal_get_busy_flag(void);


void vcrtc_wait_for_idle(void);

void vcrtc_write_protect(bool state);

void vcrtc_write(uint8_t rtc_time, uint32_t value);

uint32_t vcrtc_read(uint8_t rtc_time);


void vcrtc_int_enable(uint8_t rtc_int);

void vcrtc_int_disable(uint8_t rtc_int);

int vcrtc_get_int_sts(uint8_t rtc_int);

void vcrtc_clear_int_sts(uint8_t rtc_int);

void vcrtc_clear_all_int_sts(void);


void vcrtc_set_wkusec(uint8_t period);

void vcrtc_set_wkumin(uint8_t period);

void vcrtc_set_wkuhour(uint8_t period);

void vcrtc_set_wkuitv(uint8_t type);

void vcrtc_set_wkusitv(uint8_t period);

void vcrtc_set_wkucnt(uint32_t n_clock, uint8_t cnt_sel);

uint32_t vcrtc_get_wkucntr(void);


void vcrtc_clock_config(uint8_t rtc_clock);

void vcrtc_second_pulse_output_cmd(bool state);

void vcrtc_plldiv_output_cmd(bool state);

void vcrtc_plldiv_config(uint32_t frequency_hz);

void vcrtc_mode_config(uint32_t mode);

#ifdef __cplusplus
}
#endif

#endif // __VC_RTC_H
