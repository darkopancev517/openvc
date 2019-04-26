/**
 * Copyright (c) 2018 Vertexcom Technologies, Inc. All rights reserved
 * Vertexcom Confidential Proprietary
 *
*/

#ifndef __VC_SFIO_H
#define __VC_SFIO_H

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

#ifndef IODETECT_RISING
#define IODETECT_RISING         0
#endif

#ifndef IODETECT_FALLING
#define IODETECT_FALLING        1
#endif

#ifndef IODETECT_HIGH
#define IODETECT_HIGH           2
#endif

#ifndef IODETECT_LOW
#define IODETECT_LOW            3
#endif

#ifndef IODETECT_EDGEBOTH
#define IODETECT_EDGEBOTH       4
#endif

// Sirius internal SPI configuration

#define SPIMUX0     0   // both spi flash and sram using iob interface
#define SPIMUX1     1   // spi flash use internal iface, sram use iob
#define SPIMUX2     2   // spi flash use iob interface, sram use internal
#define SPIMUX3     3   // both spi flash and sram use internal interface

void vcsfio_reset(uint8_t port, uint8_t pin);

void vcsfio_enable_int(uint8_t port, uint8_t pin, uint8_t detect);

void vcsfio_disable_int(uint8_t port, uint8_t pin);

int vcsfio_get_int(uint8_t port, uint8_t pin);

void vcsfio_clear_int(uint8_t port, uint8_t pin);

void vcsfio_enable_uart(uint8_t uart); // UART0 --- UART6

void vcsfio_disable_uart(uint8_t uart);

void vcsfio_enable_iso7816(uint8_t id, bool bClk);

void vcsfio_disable_iso7816(uint8_t id);

void vcsfio_enable_spi(uint8_t spi); // SPI1 --- SPI3

void vcsfio_disable_spi(uint8_t spi);

void vcsfio_enable_pwm(uint8_t pwm_io); // PWM_IO0 -- PWM_IO3

void vcsfio_disable_pwm(uint8_t pwm_io);

void vcsfio_config_spimux(uint8_t spimux);

int vcsfio_get_ioc_int_enable_status(uint8_t pin);

void vcsfio_enable_i2c(uint8_t i2c);

void vcsfio_enable_iob1_hrco_out(void);

void vcsfio_enable_iob_spisram(void);

void vcsfio_enable_iob_quadmode_spiflash(void);

void vcsfio_enable_iob_spiflash(void);

#ifdef __cplusplus
}
#endif

#endif // __VC_SFIO_H

