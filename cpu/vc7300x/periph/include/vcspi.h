/**
 * Copyright (c) 2018 Vertexcom Technologies, Inc. All rights reserved
 * Vertexcom Confidential Proprietary
 *
*/

#ifndef __VC_SPI_H
#define __VC_SPI_H

#include <stdint.h>
#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif

#ifndef SPI1
#define SPI1 0
#endif

#ifndef SPI2
#define SPI2 1
#endif

#ifndef SPI3
#define SPI3 2
#endif

#define SPIMODE_MASTER  0
#define SPIMODE_SLAVE   1

#define SPIWIDTH_8BITS      0
#define SPIWIDTH_16BITS     1
#define SPIWIDTH_24BITS     2
#define SPIWIDTH_32BITS     3

#define SPIFIRSTBIT_MSB     0
#define SPIFIRSTBIT_LSB     1

#define SPISTATUS_TXIF      0
#define SPISTATUS_TXEMPTY   1
#define SPISTATUS_TXFUR     2
#define SPISTATUS_RXIF      3
#define SPISTATUS_RXFULL    4
#define SPISTATUS_RXFOV     5
#define SPISTATUS_BSY       6
#define SPISTATUS_RFF       7
#define SPISTATUS_RNE       8
#define SPISTATUS_TNF       9
#define SPISTATUS_TFE       10

#define SPIINT_TX       1
#define SPIINT_RX       2

#define SPIFIFO_TXLEV_1     0
#define SPIFIFO_TXLEV_2     1
#define SPIFIFO_TXLEV_3     2
#define SPIFIFO_TXLEV_4     3
#define SPIFIFO_TXLEV_5     4
#define SPIFIFO_TXLEV_6     5
#define SPIFIFO_TXLEV_7     6
#define SPIFIFO_TXLEV_8     7   // hw default: 8 write is allowed


#define SPIFIFO_RXLEV_1     0   // hw default: 1 read is allowed
#define SPIFIFO_RXLEV_2     1
#define SPIFIFO_RXLEV_3     2
#define SPIFIFO_RXLEV_4     3
#define SPIFIFO_RXLEV_5     4
#define SPIFIFO_RXLEV_6     5
#define SPIFIFO_RXLEV_7     6
#define SPIFIFO_RXLEV_8     7

void vcspi_enable(uint8_t spi);

void vcspi_disable(uint8_t spi);


void vcspi_config_reset(uint8_t spi);

void vcspi_config_clk_source(uint8_t spi, bool state);

void vcspi_config_mode(uint8_t spi, uint8_t mode);

void vcspi_config_sck_phase(uint8_t spi, uint8_t phase);

void vcspi_config_sck_polarity(uint8_t spi, uint8_t polarity);

void vcspi_config_clk_div(uint8_t spi, uint8_t div); // 1 --- 256

void vcspi_config_master_cs_gpio(uint8_t spi, bool state); // [true]: use gpio [false]: use spi h/w

void vcspi_config_slave_cs_master(uint8_t spi, bool state); // [true]: control by master [false]: use pin logic 0 

void vcspi_config_swap(uint8_t spi, bool state);

void vcspi_config_transfer_width(uint8_t spi, uint8_t width);

void vcspi_config_firstbit(uint8_t spi, uint8_t firstbit);

void vcspi_config_fifo_transmit(uint8_t spi, uint8_t level);

void vcspi_config_fifo_receive(uint8_t spi, uint8_t level);

void vcspi_config_enable_int(uint8_t spi, uint8_t interrupt);

void vcspi_config_disable_int(uint8_t spi, uint8_t interrupt);


uint8_t vcspi_get_fifo_transmit_level(uint8_t spi);

uint8_t vcspi_get_fifo_receive_level(uint8_t spi);

uint8_t vcspi_get_status(uint8_t spi, uint8_t status);

uint8_t vcspi_get_mode(uint8_t spi);

int vcspi_get_swap_setting(uint8_t spi);

int vcspi_get_csgpio_setting(uint8_t spi);


void vcspi_clear_status(uint8_t spi, uint8_t status);

void vcspi_overwrite_mode(uint8_t spi, bool state);

void vcspi_smart_mode(uint8_t spi, bool state);


void vcspi_send_byte(uint8_t spi, uint8_t data);

uint8_t vcspi_receive_byte(uint8_t spi);

uint32_t vcspi_get_receive_addr(uint8_t spi);

uint32_t vcspi_get_transmit_addr(uint8_t spi);


#ifdef __cplusplus
}
#endif

#endif // __VC_SPI_H

