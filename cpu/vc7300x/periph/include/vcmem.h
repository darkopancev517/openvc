/**
 * Copyright (c) 2018 Vertexcom Technologies, Inc. All rights reserved
 * Vertexcom Confidential Proprietary
 *
*/

#ifndef __VC_MEM_H
#define __VC_MEM_H

#include <stdint.h>
#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif

#define MEM_CACHE_SIZE_8KB  0
#define MEM_CACHE_SIZE_4KB  1

#define EMBFLASH_CSMODE_DISABLE         0
#define EMBFLASH_CSMODE_ALWAYS_ON       1
#define EMBFLASH_CSMODE_SOVTIM2         2    // start at overflow timer 2
#define EMBFLASH_CSMODE_RISINGRTC       3    // start at rising edge of RTC second pulse

#define EMBFLASH_INTEN_CSDONE           0
#define EMBFLASH_INTEN_CSERROR          1
#define EMBFLASH_INTEN_HITRATEDONE      2
#define EMBFLASH_INTEN_HITRATELDETECT   3

#define EMBFLASH_SECTOR_SIZE            0x400 // 1KB

#define SPIFLASH_WINBOND    0
#define SPIFLASH_MXIC       1

#define SPIFLASH_SIZE_512KBIT   0
#define SPIFLASH_SIZE_1MBIT     1
#define SPIFLASH_SIZE_2MBIT     2
#define SPIFLASH_SIZE_4MBIT     3
#define SPIFLASH_SIZE_8MBIT     4
#define SPIFLASH_SIZE_16MBIT    5
#define SPIFLASH_SIZE_32MBIT    6
#define SPIFLASH_SIZE_64MBIT    7

#define SPIFLASH_MEMMODE_1I1O   0
#define SPIFLASH_MEMMODE_1I1OF  1
#define SPIFLASH_MEMMODE_1I2O   2
#define SPIFLASH_MEMMODE_2I2O   3
#define SPIFLASH_MEMMODE_1I4O   4
#define SPIFLASH_MEMMODE_4I4O   5

#define SPIFLASH_CMDLAT_0       0   // fall edge
#define SPIFLASH_CMDLAT_1       1   // 0.5 cycle
#define SPIFLASH_CMDLAT_2       2   // 1 cycle
#define SPIFLASH_CMDLAT_3       3   // 1.5 cycle

#define SPIFLASH_MEMLAT_0       0   // fall edge
#define SPIFLASH_MEMLAT_1       1   // 0.5 cycle
#define SPIFLASH_MEMLAT_2       2   // 1 cycle
#define SPIFLASH_MEMLAT_3       3   // 1.5 cycle

#define SPIFLASH_MEMADDR_3BYTES     0
#define SPIFLASH_MEMADDR_4BYTES     1

#define SPIFLASH_QUADMODE_ENABLE    1
#define SPIFLASH_QUADMODE_DISABLE   0

#define SPIFLASH_SECTOR_SIZE    0x1000  // 4KB

#ifndef SPIMUX0
#define SPIMUX0     0   // both spi flash and sram using iob interface
#endif

#ifndef SPIMUX1
#define SPIMUX1     1   // spi flash use internal iface, sram use iob
#endif

#ifndef SPIMUX2
#define SPIMUX2     2   // spi flash use iob interface, sram use internal
#endif

#ifndef SPIMUX3
#define SPIMUX3     3   // both spi flash and sram use internal interface
#endif

#define SPISRAM_SIZE_512KBIT 0
#define SPISRAM_SIZE_1MBIT   1
#define SPISRAM_SIZE_2MBIT   2
#define SPISRAM_SIZE_4MBIT   3
#define SPISRAM_SIZE_8MBIT   4
#define SPISRAM_SIZE_16MBIT  5
#define SPISRAM_SIZE_32MBIT  6
#define SPISRAM_SIZE_64MBIT  7

#define SPISRAM_MODE_1I1O       0
#define SPISRAM_MODE_FAST_1I1O  1
#define SPISRAM_MODE_1I2O       2
#define SPISRAM_MODE_2IO        3
#define SPISRAM_MODE_1I4O       4
#define SPISRAM_MODE_4IO        5

#define SPISRAM_LATENCY_0 0 // at falling edge of internal SPICLK
#define SPISRAM_LATENCY_1 1 // 0.5 cycle after falling edge of internal SPICLK
#define SPISRAM_LATENCY_2 2 // 1 cycle after falling edge of internal SPICLK
#define SPISRAM_LATENCY_3 3 // 1.5 cycle after falling edge of internal SPICLK

#define SPISRAM_MEMADDR_3BYTES 0
#define SPISRAM_MEMADDR_4BYTES 1

#define VCREG_BASE_SPISRAM_MEM  0x01800000
#define VCREG_BASE_SPIFLASH_MEM 0x01000000


void vcmem_reset_cache(void);

void vcmem_enable_cache(void);

void vcmem_disable_cache(void);

void vcmem_config_cache_size(uint8_t size);

void vcmem_disable_cache_hitrate(void);

void vcmem_enable_cache_hitrate(void);


void vcembflash_config_wait_cycle(uint8_t wait_cycle);

void vcembflash_config_csmode(uint8_t mode);

void vcembflash_config_csrange(uint32_t addr_start, uint32_t addr_end);

void vcembflash_config_cscomp_value(uint32_t cs);

uint32_t vcembflash_get_cs(void);

void vcembflash_enable_int(uint8_t interrupt);

void vcembflash_disable_int(uint8_t interrupt);

int vcembflash_get_int(uint8_t interrupt);

void vcembflash_clear_int(uint8_t interrupt);

void vcembflash_unlock(void);

void vcembflash_lock(void);

void vcembflash_erase_sector(uint32_t addr);

void vcembflash_erase_chip(void);

void vcembflash_program_word(uint32_t addr, uint32_t word);

void vcembflash_program_byte(uint32_t addr, uint8_t byte);


void vcspiflash_config_type(uint8_t vendor);

void vcspiflash_config_cmdclk_div(uint8_t div);

void vcspiflash_config_memclk_div(uint8_t div);

void vcspiflash_config_size(uint8_t size);

void vcspiflash_config_memmode(uint8_t mode);

void vcspiflash_config_cmdlatency( uint8_t lat);

void vcspiflash_config_memlatency(uint8_t lat);

void vcspiflash_config_perf_enhc(bool state);

void vcspiflash_config_memaddr_bytes(uint8_t bytes);

void vcspiflash_config_spimux(uint8_t spimux);

void vcspiflash_write_enable(void);

void vcspiflash_quad_enable(void);

void vcspiflash_erase_chip(void);

void vcspiflash_erase_sector(uint32_t addr);

void vcspiflash_erase_64kb_block(uint32_t addr);

void vcspiflash_erase_32kb_block(uint32_t addr);

void vcspiflash_program_word(uint32_t addr, uint32_t word);

void vcspiflash_program_page(uint32_t addr, uint32_t len, uint8_t *buf);


void vcspisram_config_addr_bytes(uint8_t bytes);

void vcspisram_config_latency(uint8_t latency);

void vcspisram_config_mode(uint8_t mode);

void vcspisram_config_clk_div(uint8_t div); // 1 - 16

void vcspisram_config_size(uint8_t size);

void vcspisram_config_spimux(uint8_t spimux);

void vcspisram_enable(void);

void vcspisram_disable(void);

void vcspisram_enable_sqi_mode(void);

#ifdef __cplusplus
}
#endif

#endif // __VC_MEM_H

