/**
 * Copyright (c) 2018 Vertexcom Technologies, Inc. All rights reserved
 * Vertexcom Confidential Proprietary
 *
*/

#ifndef __VC_WDT_H
#define __VC_WDT_H

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

#define WDT_PERIOD_2_SECS       0
#define WDT_PERIOD_1_SECS       1
#define WDT_PERIOD_0_5_SECS     2
#define WDT_PERIOD_0_25_SECS    3

void vcwdt_clear(void);

void vcwdt_enable(void);

void vcwdt_disable(void);

void vcwdt_set_period(uint8_t period);

uint16_t vcwdt_get_counter(void);

int vcwdt_get_status(void);

void vcwdt_clear_status(void);

#ifdef __cplusplus
}
#endif

#endif // __VC_WDT_H

