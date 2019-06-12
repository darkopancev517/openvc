/**
 * Copyright (c) 2018 Vertexcom Technologies, Inc. All rights reserved
 * Vertexcom Confidential Proprietary
 *
*/

#ifndef __VC_I2C_H
#define __VC_I2C_H

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

#define I2C1 0
#define I2C2 1

void vci2c_reset(uint8_t i2c);

void vci2c_enable(uint8_t i2c);

void vci2c_disable(uint8_t i2c);

void vci2c_config_slave_addr(uint8_t i2c, uint8_t addr);

void vci2c_config_general_call_ack(uint8_t i2c, bool state);

void vci2c_config_assert_ack(uint8_t i2c, bool state);

void vci2c_config_clksrc_apbdiv_256(uint8_t i2c);

void vci2c_config_clksrc_apbdiv_224(uint8_t i2c);

void vci2c_config_clksrc_apbdiv_192(uint8_t i2c);

void vci2c_config_clksrc_apbdiv_160(uint8_t i2c);

void vci2c_config_clksrc_apbdiv_960(uint8_t i2c);

void vci2c_config_clksrc_apbdiv_120(uint8_t i2c);

void vci2c_config_clksrc_apbdiv_60(uint8_t i2c);

void vci2c_config_clksrc_tim3_overflow_div8(uint8_t i2c);

void vci2c_enable_int(uint8_t i2c);

int vci2c_get_int(uint8_t i2c);

void vci2c_clear_int(uint8_t i2c);

uint8_t vci2c_get_status_code(uint8_t i2c);

void vci2c_generate_start(uint8_t i2c, bool state);

void vci2c_generate_stop(uint8_t i2c, bool state);

int vci2c_write_nbyte(uint8_t i2c,
                      uint8_t slvaddr,
                      uint8_t regaddr,
                      uint8_t *buf,
                      uint32_t length);

int vci2c_read_nbyte(uint8_t i2c,
                     uint8_t slvaddr,
                     uint8_t regaddr,
                     uint8_t *buf,
                     uint32_t length);

#ifdef __cplusplus
}
#endif

#endif // __VC_I2C_H

