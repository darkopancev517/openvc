/**
 * Copyright (c) 2018 Vertexcom Technologies, Inc. All rights reserved
 * Vertexcom Confidential Proprietary
 *
*/

#ifndef __VC_TIM_H
#define __VC_TIM_H

#include <stdint.h>
#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif

#define TIM0 0
#define TIM1 1
#define TIM2 2
#define TIM3 3

#define TIM_CLKSRC_INTERNAL 0
#define TIM_CLKSRC_EXTERNAL 1

void vctim_config_reset(uint8_t tim);

void vctim_config_clock_source(uint8_t tim, uint8_t clksrc);

void vctim_config_external_clock_gate(uint8_t tim, bool state); // use external clock as clock enable

void vctim_config_reload_value(uint8_t tim, uint32_t reload);

void vctim_config_enable_int(uint8_t tim);

void vctim_config_disable_int(uint8_t tim);

void vctim_enable(uint8_t tim);

void vctim_disable(uint8_t tim);

int vctim_get_int(uint8_t tim);

void vctim_clear_int(uint8_t tim);

uint32_t vctim_get_value(uint8_t tim);

void vctim_set_value(uint8_t tim, uint32_t value);

uint32_t vctim_get_reload(uint8_t tim);

#ifdef __cplusplus
}
#endif

#endif // __VC_TIM_H

