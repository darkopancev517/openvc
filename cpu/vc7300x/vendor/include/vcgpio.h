/**
 * Copyright (c) 2018 Vertexcom Technologies, Inc. All rights reserved
 * Vertexcom Confidential Proprietary
 *
*/

#ifndef __VC_GPIO_H
#define __VC_GPIO_H

#include <stdint.h>
#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif

#define IOA 0
#define IOB 1
#define IOC 2
#define IOD 3
#define IOE 4
#define IOF 5

#define IOMODE_OUT   0
#define IOMODE_IN    1
#define IOMODE_INOUT 2

#define IOATT_CMOS          0
#define IOATT_OPEN_DRAIN    1
#define IOATT_DEFAULT       IOATT_CMOS

void vcgpio_reset(uint8_t port, uint8_t pin);

void vcgpio_config_mode(uint8_t port, uint8_t pin, uint8_t mode);

void vcgpio_config_att(uint8_t port, uint8_t pin,  uint8_t att);

int vcgpio_read_input_bit(uint8_t port, uint8_t pin);

int vcgpio_read_output_bit(uint8_t port, uint8_t pin);

void vcgpio_set_bit(uint8_t port, uint8_t pin);

void vcgpio_reset_bit(uint8_t port, uint8_t pin);

void vcgpio_toggle_bit(uint8_t port, uint8_t pin);

uint16_t vcgpio_get_output_pins_config(uint8_t port);

uint16_t vcgpio_get_output_pins_status(uint8_t port);

uint16_t vcgpio_get_input_pins_status(uint8_t port);

#ifdef __cplusplus
}
#endif

#endif // __VC_GPIO_H

