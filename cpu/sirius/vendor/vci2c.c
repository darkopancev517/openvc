/**
 * Copyright (c) 2018 Vertexcom Technologies, Inc. All rights reserved
 * Vertexcom Confidential Proprietary
 *
*/

#include "vcsoc.h"

#define VCREG_BASE_I2C1     0x40041000
#define VCREG_BASE_I2C2     0x40041020
#define VCREG_BASE_I2C(i)   (VCREG_BASE_I2C1 + ((i) * (VCREG_BASE_I2C2 - VCREG_BASE_I2C1)))

struct VCI2C_REG_DATA {
    union {
        struct {
            uint32_t DATA       : 8;
            uint32_t reserved   : 24;
        } fields;

        uint32_t value;
    };
};

struct VCI2C_REG_ADDR {
    union {
        struct {
            uint32_t GC         : 1;    // (r/w) general call address acknowledge
            uint32_t SLA        : 7;    // (r/w) own I2C slave address (7 bit)
            uint32_t reserved   : 24;
        } fields;

        uint32_t value;
    };
};

struct VCI2C_REG_CTRL {
    union {
        struct {
            uint32_t CR0        : 1;    // (r/w) clock rate bit 0
            uint32_t CR1        : 1;    // (r/w) clock rate bit 1
            uint32_t AA         : 1;    // (r/w) assert acknowledge flag
            uint32_t SI         : 1;    // (r/w) serial interrupt flag
            uint32_t STO        : 1;    // (r/w) stop flag
            uint32_t STA        : 1;    // (r/w) start flag
            uint32_t EN         : 1;    // (r/w) I2C enable bit
            uint32_t CR2        : 1;    // (r/w) clock rate bit 2
            uint32_t reserved   : 24;
        } fields;

        uint32_t value;
    };
};

struct VCI2C_REG_STS {
    union {
        struct {
            uint32_t reserved   : 5;
            uint32_t STS        : 3;
            uint32_t reserved1  : 24;
        } fields;

        uint32_t value;
    };
};

struct VCI2C_REG_CTRL2 {
    union {
        struct {
            uint32_t INTEN      : 1;
            uint32_t reserved   : 31;
        } fields;

        uint32_t value;
    };
};

struct VCI2C_REG_SPACE {
    struct VCI2C_REG_DATA   DATA;
    struct VCI2C_REG_ADDR   ADDR;
    struct VCI2C_REG_CTRL   CTRL;
    struct VCI2C_REG_STS    STS;
    uint32_t reserved[2];
    struct VCI2C_REG_CTRL2  CTRL2;
};

static uint8_t i2c_receive_data(uint8_t i2c);
static void i2c_send_data(uint8_t i2c, uint8_t data);
static uint16_t i2c_check_state(uint8_t i2c, uint8_t state);
static void i2c_generate_start(uint8_t i2c, bool state);
static void i2c_generate_stop(uint8_t i2c, bool state);
static void i2c_send_start(uint8_t i2c);
static void i2c_send_restart(uint8_t i2c);
static void i2c_send_byte(uint8_t i2c, uint8_t data);
static void i2c_send_stop(uint8_t i2c);
static uint8_t i2c_receive_byte(uint8_t i2c);
static void i2c_wait_operation(uint8_t i2c, uint16_t sla);

static uint8_t i2c_receive_data(uint8_t i2c)
{
    if (i2c < I2C1 || i2c > I2C2) return 0;

    volatile struct VCI2C_REG_SPACE *reg_space = (volatile struct VCI2C_REG_SPACE *)VCREG_BASE_I2C(i2c);

    return reg_space->DATA.value;
}

static uint16_t i2c_check_state(uint8_t i2c, uint8_t state)
{
    if (i2c < I2C1 || i2c > I2C2) return 0;

    uint16_t ret;

    if (vci2c_get_status_code(i2c) != state)
    {
        ret = (state << 8) | (vci2c_get_status_code(i2c));
        return ret;
    }
    else
    {
        return 0;
    }
}

static void i2c_generate_start(uint8_t i2c, bool state)
{
    if (i2c < I2C1 || i2c > I2C2) return;

    volatile struct VCI2C_REG_SPACE *reg_space = (volatile struct VCI2C_REG_SPACE *)VCREG_BASE_I2C(i2c);

    reg_space->CTRL.fields.STA = (state == true) ? 1 : 0;
}

static void i2c_generate_stop(uint8_t i2c, bool state)
{
    if (i2c < I2C1 || i2c > I2C2) return;

    volatile struct VCI2C_REG_SPACE *reg_space = (volatile struct VCI2C_REG_SPACE *)VCREG_BASE_I2C(i2c);

    reg_space->CTRL.fields.STO = (state == true) ? 1 : 0;
}

static void i2c_send_start(uint8_t i2c)
{
    if (i2c < I2C1 || i2c > I2C2) return;

    i2c_generate_start(i2c, true);
    while (vci2c_get_int(i2c) == 0);
    i2c_generate_start(i2c, false);
}

static void i2c_send_restart(uint8_t i2c)
{
    if (i2c < I2C1 || i2c > I2C2) return;

    i2c_generate_start(i2c, true);
    vci2c_clear_int(i2c);
    while (vci2c_get_int(i2c) == 0);
    i2c_generate_start(i2c, false);
}

static void i2c_send_byte(uint8_t i2c, uint8_t data)
{
    if (i2c < I2C1 || i2c > I2C2) return;

    i2c_send_data(i2c, data);
    vci2c_clear_int(i2c);
    while (vci2c_get_int(i2c) == 0);
}

static uint8_t i2c_receive_byte(uint8_t i2c)
{
    if (i2c < I2C1 || i2c > I2C2) return 0;

    vci2c_clear_int(i2c);
    while (vci2c_get_int(i2c) == 0);
    return i2c_receive_data(i2c);
}

static void i2c_send_stop(uint8_t i2c)
{
    if (i2c < I2C1 || i2c > I2C2) return;

    i2c_generate_stop(i2c, true);
    vci2c_clear_int(i2c);
    i2c_generate_stop(i2c, false);
}

static void i2c_send_data(uint8_t i2c, uint8_t data)
{
    if (i2c < I2C1 || i2c > I2C2) return;

    volatile struct VCI2C_REG_SPACE *reg_space = (volatile struct VCI2C_REG_SPACE *)VCREG_BASE_I2C(i2c);

    reg_space->DATA.fields.DATA = data;
}

static void i2c_wait_operation(uint8_t i2c, uint16_t sla)
{
    if (i2c < I2C1 || i2c > I2C2) return;

    do
    {
        i2c_send_restart(i2c);
        i2c_send_byte(i2c, sla);
    } while (vci2c_get_status_code(i2c) != 0x18);

    i2c_send_stop(i2c);
}

void vci2c_reset(uint8_t i2c)
{
    if (i2c < I2C1 || i2c > I2C2) return;

    volatile struct VCI2C_REG_SPACE *reg_space = (volatile struct VCI2C_REG_SPACE *)VCREG_BASE_I2C(i2c);

    // restore I2C register into it's default value
    reg_space->DATA.value = 0;
    reg_space->ADDR.value = 0;
    reg_space->CTRL.value = 0;
    reg_space->CTRL2.value = 0;
}

void vci2c_enable(uint8_t i2c)
{
    if (i2c < I2C1 || i2c > I2C2) return;

    volatile struct VCI2C_REG_SPACE *reg_space = (volatile struct VCI2C_REG_SPACE *)VCREG_BASE_I2C(i2c);

    reg_space->CTRL.fields.EN = 1;
}

void vci2c_disable(uint8_t i2c)
{
    if (i2c < I2C1 || i2c > I2C2) return;

    volatile struct VCI2C_REG_SPACE *reg_space = (volatile struct VCI2C_REG_SPACE *)VCREG_BASE_I2C(i2c);

    reg_space->CTRL.fields.EN = 0;
}

void vci2c_config_slave_addr(uint8_t i2c, uint8_t addr)
{
    if (i2c < I2C1 || i2c > I2C2) return;

    volatile struct VCI2C_REG_SPACE *reg_space = (volatile struct VCI2C_REG_SPACE *)VCREG_BASE_I2C(i2c);

    reg_space->ADDR.fields.SLA = addr;
}

void vci2c_config_general_call_ack(uint8_t i2c, bool state)
{
    if (i2c < I2C1 || i2c > I2C2) return;

    volatile struct VCI2C_REG_SPACE *reg_space = (volatile struct VCI2C_REG_SPACE *)VCREG_BASE_I2C(i2c);

    reg_space->ADDR.fields.GC = (state == true) ? 1 : 0;
}

void vci2c_config_assert_ack(uint8_t i2c, bool state)
{
    if (i2c < I2C1 || i2c > I2C2) return;

    volatile struct VCI2C_REG_SPACE *reg_space = (volatile struct VCI2C_REG_SPACE *)VCREG_BASE_I2C(i2c);

    reg_space->CTRL.fields.AA = (state == true) ? 1 : 0;
}

void vci2c_config_clksrc_apbdiv_256(uint8_t i2c)
{
    if (i2c < I2C1 || i2c > I2C2) return;

    volatile struct VCI2C_REG_SPACE *reg_space = (volatile struct VCI2C_REG_SPACE *)VCREG_BASE_I2C(i2c);

    reg_space->CTRL.fields.CR0 = 0;
    reg_space->CTRL.fields.CR1 = 0;
    reg_space->CTRL.fields.CR2 = 0;
}

void vci2c_config_clksrc_apbdiv_224(uint8_t i2c)
{
    if (i2c < I2C1 || i2c > I2C2) return;

    volatile struct VCI2C_REG_SPACE *reg_space = (volatile struct VCI2C_REG_SPACE *)VCREG_BASE_I2C(i2c);

    reg_space->CTRL.fields.CR0 = 1;
    reg_space->CTRL.fields.CR1 = 0;
    reg_space->CTRL.fields.CR2 = 0;
}

void vci2c_config_clksrc_apbdiv_192(uint8_t i2c)
{
    if (i2c < I2C1 || i2c > I2C2) return;

    volatile struct VCI2C_REG_SPACE *reg_space = (volatile struct VCI2C_REG_SPACE *)VCREG_BASE_I2C(i2c);

    reg_space->CTRL.fields.CR0 = 0;
    reg_space->CTRL.fields.CR1 = 1;
    reg_space->CTRL.fields.CR2 = 0;
}

void vci2c_config_clksrc_apbdiv_160(uint8_t i2c)
{
    if (i2c < I2C1 || i2c > I2C2) return;

    volatile struct VCI2C_REG_SPACE *reg_space = (volatile struct VCI2C_REG_SPACE *)VCREG_BASE_I2C(i2c);

    reg_space->CTRL.fields.CR0 = 1;
    reg_space->CTRL.fields.CR1 = 1;
    reg_space->CTRL.fields.CR2 = 0;
}

void vci2c_config_clksrc_apbdiv_960(uint8_t i2c)
{
    if (i2c < I2C1 || i2c > I2C2) return;

    volatile struct VCI2C_REG_SPACE *reg_space = (volatile struct VCI2C_REG_SPACE *)VCREG_BASE_I2C(i2c);

    reg_space->CTRL.fields.CR0 = 0;
    reg_space->CTRL.fields.CR1 = 0;
    reg_space->CTRL.fields.CR2 = 1;
}

void vci2c_config_clksrc_apbdiv_120(uint8_t i2c)
{
    if (i2c < I2C1 || i2c > I2C2) return;

    volatile struct VCI2C_REG_SPACE *reg_space = (volatile struct VCI2C_REG_SPACE *)VCREG_BASE_I2C(i2c);

    reg_space->CTRL.fields.CR0 = 1;
    reg_space->CTRL.fields.CR1 = 0;
    reg_space->CTRL.fields.CR2 = 1;
}

void vci2c_config_clksrc_apbdiv_60(uint8_t i2c)
{
    if (i2c < I2C1 || i2c > I2C2) return;

    volatile struct VCI2C_REG_SPACE *reg_space = (volatile struct VCI2C_REG_SPACE *)VCREG_BASE_I2C(i2c);

    reg_space->CTRL.fields.CR0 = 0;
    reg_space->CTRL.fields.CR1 = 1;
    reg_space->CTRL.fields.CR2 = 1;
}

void vci2c_config_clksrc_tim3_overflow_div8(uint8_t i2c)
{
    if (i2c < I2C1 || i2c > I2C2) return;

    volatile struct VCI2C_REG_SPACE *reg_space = (volatile struct VCI2C_REG_SPACE *)VCREG_BASE_I2C(i2c);

    reg_space->CTRL.fields.CR0 = 1;
    reg_space->CTRL.fields.CR1 = 1;
    reg_space->CTRL.fields.CR2 = 1;
}

void vci2c_enable_int(uint8_t i2c)
{
    if (i2c < I2C1 || i2c > I2C2) return;

    volatile struct VCI2C_REG_SPACE *reg_space = (volatile struct VCI2C_REG_SPACE *)VCREG_BASE_I2C(i2c);

    reg_space->CTRL2.fields.INTEN = 1;
}

void vci2c_disable_int(uint8_t i2c)
{
    if (i2c < I2C1 || i2c > I2C2) return;

    volatile struct VCI2C_REG_SPACE *reg_space = (volatile struct VCI2C_REG_SPACE *)VCREG_BASE_I2C(i2c);

    reg_space->CTRL2.fields.INTEN = 0;
}

int vci2c_get_int(uint8_t i2c)
{
    if (i2c < I2C1 || i2c > I2C2) return 0;

    volatile struct VCI2C_REG_SPACE *reg_space = (volatile struct VCI2C_REG_SPACE *)VCREG_BASE_I2C(i2c);

    return (reg_space->CTRL.fields.SI == 1) ? 1 : 0;
}

void vci2c_clear_int(uint8_t i2c)
{
    if (i2c < I2C1 || i2c > I2C2) return;

    volatile struct VCI2C_REG_SPACE *reg_space = (volatile struct VCI2C_REG_SPACE *)VCREG_BASE_I2C(i2c);

    reg_space->CTRL.fields.SI = 0;
}

uint8_t vci2c_get_status_code(uint8_t i2c)
{
    if (i2c < I2C1 || i2c > I2C2) return 0;

    volatile struct VCI2C_REG_SPACE *reg_space = (volatile struct VCI2C_REG_SPACE *)VCREG_BASE_I2C(i2c);

    return (reg_space->STS.value & 0xff);
}

int vci2c_write_nbyte(uint8_t i2c,
                      uint8_t slvaddr,
                      uint8_t regaddr,
                      uint8_t *buf,
                      uint32_t length)
{
    if (i2c < I2C1 || i2c > I2C2) return -1;
    uint16_t retval;

    i2c_send_start(i2c);
    retval = i2c_check_state(i2c, 0x08);
    if (retval) return retval;

    i2c_send_byte(i2c, slvaddr);
    retval = i2c_check_state(i2c, 0x18);
    if (retval) return retval;

    i2c_send_byte(i2c, regaddr & 0xff);
    retval = i2c_check_state(i2c, 0x28);
    if (retval) return retval;

    for (int i = 0; i < length; i++) {
        i2c_send_byte(i2c, *buf);
        buf++;
        retval = i2c_check_state(i2c, 0x28);
        if (retval) return retval;
    }

    i2c_send_stop(i2c);
    i2c_wait_operation(i2c, slvaddr);

    return 0;
}

int vci2c_read_nbyte(uint8_t i2c,
                     uint8_t slvaddr,
                     uint8_t regaddr,
                     uint8_t *buf,
                     uint32_t length)
{
    if ((i2c < I2C1) || (i2c > I2C2)) return -1;

    int i;
    uint16_t retval;

    vci2c_config_assert_ack(i2c, true);

    // issue start bit
    i2c_send_start(i2c);

    // [0x8] start condition has been trasmitted
    retval = i2c_check_state(i2c, 0x08);
    if (retval) return retval;

    // write slave address
    i2c_send_byte(i2c, slvaddr);

    // [0x18] SLA write has been transmmitted. ACK has been received
    retval = i2c_check_state(i2c, 0x18);
    if (retval) return retval;

    // write register address
    i2c_send_byte(i2c, regaddr&0xff);

    // [0x28] Data byte has been transmitted. ACK has been received
    retval = i2c_check_state(i2c, 0x28);
    if (retval) return retval;

    // issue restart bit
    i2c_send_restart(i2c);

    // [0x10] A repeated start condition has been transmitted
    retval = i2c_check_state(i2c, 0x10);
    if (retval) return retval;

    // send read cmd to slave
    i2c_send_byte(i2c, slvaddr | 0x01);

    // [0x40] SLA read has been transmitted. ACK has been received
    retval = i2c_check_state(i2c, 0x40);
    if (retval) return retval;


    // read data
    for (i = 0; i < (length - 1); i++)
    {
        // store data into buffer
        *buf = i2c_receive_byte(i2c);
        buf++;

        // [0x50] Data byte has been received. ACK has been returned
        retval = i2c_check_state(i2c, 0x50);
        if (retval) return retval;
    }

    // de-assert ACK
    vci2c_config_assert_ack(i2c, false);

    // store last byte received data
    *buf = i2c_receive_byte(i2c);

    // [0x58] Data byte has been received. Not ACK has been returned
    retval = i2c_check_state(i2c, 0x58);
    if (retval) return retval;

    i2c_send_stop(i2c);

    return 0;
}

