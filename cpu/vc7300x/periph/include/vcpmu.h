/**
 * Copyright (c) 2018 Vertexcom Technologies, Inc. All rights reserved
 * Vertexcom Confidential Proprietary
 *
*/

#ifndef __VC_PMU_H
#define __VC_PMU_H

#include <stdint.h>
#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif

#define PMU_REMAP_IROM              0
#define PMU_REMAP_SRAM0_MODE1       1
#define PMU_REMAP_FLASH             2
#define PMU_REMAP_SRAM0_MODE2       3   // SRAM0 boot but flash at 0x1000 ~ 0xffffff region

void vcpmu_enter_deep_sleep_mode(void);

void vcpmu_enter_idle_mode(void);

void vcpmu_enter_sleep_mode(void);

void vcpmu_pwdown_wakeup_enable(void); // wakeup enable when power is off

void vcpmu_pwdown_wakeup_disable(void); // wakeup disable when power is off

void vcpmu_pwdown_wakeup_delay(uint8_t period);

uint32_t vcpmu_get_version_id(void);

void vcpmu_remap(uint32_t remap);

uint8_t vcpmu_get_strap_bits(void);

int vcpmu_get_int_enable_status(void);

void vcpmu_set_int_enable_status(int en);

int vcpmu_32k_xtal_status(void);

#ifdef __cplusplus
}
#endif

#endif // __VC_PMU_H

