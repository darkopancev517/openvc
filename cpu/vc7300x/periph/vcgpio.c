/**
 * Copyright (c) 2018 Vertexcom Technologies, Inc. All rights reserved
 * Vertexcom Confidential Proprietary
 *
*/

#include "vcsoc.h"

#define VCREG_BASE_IOA          0x40048010
#define VCREG_BASE_IOB          0x40000040
#define VCREG_BASE_IOC          0x40000080
#define VCREG_BASE_IO(i)        (VCREG_BASE_IOB + ((i) * (VCREG_BASE_IOC - VCREG_BASE_IOB)))

struct VCGPIO_REG_OEN {
    union {
        struct {
            uint32_t OEN        : 16;    // (rw) ouput enable pin register (0: enable, 1: disable)
            uint32_t reserved   : 16;
        } fields;

        uint32_t value;
    };
};

struct VCGPIO_REG_IE {
    union {
        struct {
            uint32_t IE         : 16;    // (rw) input enable pin register (1: enable, 0: disable)
            uint32_t reserved   : 16;
        } fields;

        uint32_t value;
    };
};

struct VCGPIO_REG_DAT {
    union {
        struct {
            uint32_t DAT        : 16;
            uint32_t reserved   : 16;
        } fields;

        uint32_t value;
    };
};

struct VCGPIO_REG_ATT {
    union {
        struct {
            uint32_t ATT        : 16;   // (rw) 0: CMOS mode, 1: Open drain mode
            uint32_t reserved   : 16;
        } fields;

        uint32_t value;
    };
};

struct VCGPIO_REG_STS {
    union {
        struct {
            uint32_t STS        : 16;
            uint32_t reserved   : 16;
        } fields;

        uint32_t value;
    };
};

struct VCGPIO_REG_SPACE {
    struct VCGPIO_REG_OEN       OEN;
    struct VCGPIO_REG_IE        IE;
    struct VCGPIO_REG_DAT       DAT;
    struct VCGPIO_REG_ATT       ATT;
    struct VCGPIO_REG_STS       STS;
};

struct VCIOA_REG_SPACE {
    struct VCGPIO_REG_OEN       OEN;
    struct VCGPIO_REG_IE        IE;
    struct VCGPIO_REG_DAT       DAT;
    struct VCGPIO_REG_ATT       ATT;
    uint32_t reserved;
    struct VCGPIO_REG_STS       STS;
};

void vcgpio_reset(uint8_t port, uint8_t pin)
{
    if ((pin < 0) || (pin > 15)) return;
    if ((port < IOA) || (port > IOF)) return;

    vcsfio_reset(port, pin);

    volatile struct VCGPIO_REG_SPACE *reg_space;

    if (port == IOA) {
        reg_space = (volatile struct VCGPIO_REG_SPACE *)VCREG_BASE_IOA;
    } else {
        reg_space = (volatile struct VCGPIO_REG_SPACE *)VCREG_BASE_IO(port - 1);
    }

    // reset this gpio config
    reg_space->OEN.fields.OEN |= (1 << pin);
    reg_space->IE.fields.IE &= ~(1 << pin);
    reg_space->ATT.fields.ATT &= ~(1 << pin);
}

void vcgpio_config_mode(uint8_t port, uint8_t pin, uint8_t mode)
{
    if ((pin < 0) || (pin > 15)) return;
    if ((port < IOA) || (port > IOF)) return;

    vcsfio_reset(port, pin);

    volatile struct VCGPIO_REG_SPACE *reg_space;

    if (port == IOA) {
        reg_space = (volatile struct VCGPIO_REG_SPACE *)VCREG_BASE_IOA;
    } else {
        reg_space = (volatile struct VCGPIO_REG_SPACE *)VCREG_BASE_IO(port - 1);
    }

    // set gpio mode
    switch (mode) {
    case IOMODE_OUT:
        reg_space->OEN.fields.OEN &= ~(1 << pin);
        reg_space->IE.fields.IE &= ~(1 << pin);
        break;

    case IOMODE_IN:
        reg_space->OEN.fields.OEN |= (1 << pin);
        reg_space->IE.fields.IE |= (1 << pin);
        break;

    case IOMODE_INOUT:
        reg_space->OEN.fields.OEN &= ~(1 << pin);
        reg_space->IE.fields.IE |= (1 << pin);
        break;

    default:
        return;
    }
}

void vcgpio_config_att(uint8_t port, uint8_t pin,  uint8_t att)
{
    if ((pin < 0) || (pin > 15)) return;
    if ((port < IOA) || (port > IOF)) return;

    vcsfio_reset(port, pin);

    volatile struct VCGPIO_REG_SPACE *reg_space;

    if (port == IOA) {
        reg_space = (volatile struct VCGPIO_REG_SPACE *)VCREG_BASE_IOA;
    } else {
        reg_space = (volatile struct VCGPIO_REG_SPACE *)VCREG_BASE_IO(port - 1);
    }

    // set gpio attribute
    if (att == IOATT_OPEN_DRAIN) {
        reg_space->ATT.fields.ATT |= (1 << pin);
    } else {
        reg_space->ATT.fields.ATT &= ~(1 << pin);
    }
}

int vcgpio_read_input_bit(uint8_t port, uint8_t pin)
{
    if ((pin < 0) || (pin > 15)) return 0;
    if ((port < IOA) || (port > IOF)) return 0;
    if ((port == IOF) && (pin > 3)) return 0;

    volatile struct VCIOA_REG_SPACE *ioa_reg = (volatile struct VCIOA_REG_SPACE *)VCREG_BASE_IOA;
    volatile struct VCGPIO_REG_SPACE *gpio_reg = (volatile struct VCGPIO_REG_SPACE *)VCREG_BASE_IO(port - 1);

    int ret = 0;

    if (port == IOA) {
        ret = (ioa_reg->STS.fields.STS & (1 << pin)) ? 1 : 0;
    } else {
        ret = (gpio_reg->STS.fields.STS & (1 << pin)) ? 1 : 0;
    }

    return ret;
}

int vcgpio_read_output_bit(uint8_t port, uint8_t pin)
{
    if ((pin < 0) || (pin > 15)) return 0;
    if ((port < IOA) || (port > IOF)) return 0;
    if ((port == IOF) && (pin > 3)) return 0;

    volatile struct VCGPIO_REG_SPACE *reg_space;

    if (port == IOA) {
        reg_space = (volatile struct VCGPIO_REG_SPACE *)VCREG_BASE_IOA;
    } else {
        reg_space = (volatile struct VCGPIO_REG_SPACE *)VCREG_BASE_IO(port - 1);
    }

    return (reg_space->DAT.fields.DAT & (1 << pin)) ? 1 : 0;
}

void vcgpio_set_bit(uint8_t port, uint8_t pin)
{
    if ((pin < 0) || (pin > 15)) return;
    if ((port < IOA) || (port > IOF)) return;
    if ((port == IOF) && (pin > 3)) return;

    volatile struct VCGPIO_REG_SPACE *reg_space;

    if (port == IOA) {
        reg_space = (volatile struct VCGPIO_REG_SPACE *)VCREG_BASE_IOA;
    } else {
        reg_space = (volatile struct VCGPIO_REG_SPACE *)VCREG_BASE_IO(port - 1);
    }

    reg_space->DAT.fields.DAT |= (1 << pin);
}

void vcgpio_reset_bit(uint8_t port, uint8_t pin)
{
    if ((pin < 0) || (pin > 15)) return;
    if ((port < IOA) || (port > IOF)) return;
    if ((port == IOF) && (pin > 3)) return;

    volatile struct VCGPIO_REG_SPACE *reg_space;

    if (port == IOA) {
        reg_space = (volatile struct VCGPIO_REG_SPACE *)VCREG_BASE_IOA;
    } else {
        reg_space = (volatile struct VCGPIO_REG_SPACE *)VCREG_BASE_IO(port - 1);
    }

    reg_space->DAT.fields.DAT &= ~(1 << pin);
}

void vcgpio_toggle_bit(uint8_t port, uint8_t pin) {
    if (vcgpio_read_output_bit(port, pin)) {
        vcgpio_reset_bit(port, pin);
    } else {
        vcgpio_set_bit(port, pin);
    }
}

uint16_t vcgpio_get_output_pins_config(uint8_t port)
{
    if ((port < IOA) || (port > IOF)) return 0;

    volatile struct VCGPIO_REG_SPACE *reg_space;

    if (port == IOA) {
        reg_space = (volatile struct VCGPIO_REG_SPACE *)VCREG_BASE_IOA;
    } else {
        reg_space = (volatile struct VCGPIO_REG_SPACE *)VCREG_BASE_IO(port - 1);
    }

    uint16_t value = reg_space->OEN.value;

    return ~value;
}

uint16_t vcgpio_get_output_pins_status(uint8_t port)
{
    if ((port < IOA) || (port  > IOE)) return 0;

    volatile struct VCGPIO_REG_SPACE *reg_space;

    if (port == IOA) {
        reg_space = (volatile struct VCGPIO_REG_SPACE *)VCREG_BASE_IOA;
    } else {
        reg_space = (volatile struct VCGPIO_REG_SPACE *)VCREG_BASE_IO(port - 1);
    }

    uint16_t status = reg_space->DAT.value;

    return status;
}

uint16_t vcgpio_get_input_pins_status(uint8_t port)
{
    if ((port < IOA) || (port > IOE)) return 0;

    volatile struct VCIOA_REG_SPACE *ioa_reg = (volatile struct VCIOA_REG_SPACE *)VCREG_BASE_IOA;
    volatile struct VCGPIO_REG_SPACE *gpio_reg = (volatile struct VCGPIO_REG_SPACE *)VCREG_BASE_IO(port - 1);

    uint16_t ret = 0;

    if (port == IOA) {
        ret = ioa_reg->STS.fields.STS;
    } else {
        ret = gpio_reg->STS.fields.STS;
    }

    return ret;
}
