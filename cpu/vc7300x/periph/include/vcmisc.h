/**
 * Copyright (c) 2018 Vertexcom Technologies, Inc. All rights reserved
 * Vertexcom Confidential Proprietary
 *
*/

#ifndef __VC_MISC_H
#define __VC_MISC_H

#include <stdint.h>
#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif

#define CLK_SOURCE_HRCO     0
#define CLK_SOURCE_RTCLK    1

#define AHBPERIPH_DMA       0
#define AHBPERIPH_GPIO      1
#define AHBPERIPH_MEM       4
#define AHBPERIPH_PLCSEC    11

#define APBPERIPH_DMA       1
#define APBPERIPH_I2C       2
#define APBPERIPH_SPI1      3
#define APBPERIPH_SPI2      4
#define APBPERIPH_SPI3      5
#define APBPERIPH_UART0     6
#define APBPERIPH_UART1     7
#define APBPERIPH_UART2     8
#define APBPERIPH_UART3     9
#define APBPERIPH_UART4     10
#define APBPERIPH_UART5     11
#define APBPERIPH_UART6     12
#define APBPERIPH_ISO78160  13
#define APBPERIPH_ISO78161  14
#define APBPERIPH_TIMER     15
#define APBPERIPH_MISC      16
#define APBPERIPH_MISC2     17
#define APBPERIPH_PMU       18
#define APBPERIPH_RTC       19
#define APBPERIPH_ANA       20
#define APBPERIPH_U32K0     21
#define APBPERIPH_U32K1     22
#define APBPERIPH_KEYSCAN   24

void vcmisc_set_sys_core_clk(uint32_t clock);

void vcmisc_disable_all_periph_clk(void);

uint32_t vcmisc_get_sys_core_clk(void);

uint32_t vcmisc_get_ahb_clk(void);

void vcmisc_config_ahb_source(uint8_t clk_source);

void vcmisc_config_ahb_div(uint16_t div);

void vcmisc_config_ahb_periph(uint8_t periph, bool state);

uint32_t vcmisc_get_apb_clk(void);

void vcmisc_config_apb_div(uint16_t div);

void vcmisc_config_apb_periph(uint8_t periph, bool state);

void vcmisc_config_embflash_wait_cycle(uint8_t wait_cycle);

void vcmisc_config_embflash_1uscycle(uint8_t cycle);

void vcmisc_sraminit_disable_parity_check(void);

void vcmisc_sraminit_enable_parity_check(void);

void vcmisc_config_pwrup_delay(uint16_t delay);


#ifdef __cplusplus
}
#endif

#endif // __VC_MISC_H

