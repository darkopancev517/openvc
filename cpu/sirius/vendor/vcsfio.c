/**
 * Copyright (c) 2018 Vertexcom Technologies, Inc. All rights reserved
 * Vertexcom Confidential Proprietary
 *
*/

#include "vcsoc.h"

#define VCREG_BASE_PMU          0x40048000
#define VCREG_BASE_IOA          0x40048010
#define VCREG_BASE_IOASF        0x40048054

#define VCREG_BASE_IOBSF        0x40000054

#define VCREG_BASE_IOC          0x40000080
#define VCREG_BASE_IOCSF        0x40000094

#define VCREG_BASE_IODSF        0x400000D4
#define VCREG_BASE_IOESF        0x40000114
#define VCREG_BASE_IOFSF        0x40000154

#define VCREG_BASE_IOSF(i)      (VCREG_BASE_IOBSF + ((i) * (VCREG_BASE_IOCSF - VCREG_BASE_IOBSF)))

#define VCREG_BASE_IOMISC       0x40000200

struct VCSFIO_REG_SEL0 {
    union {
        struct {
            uint32_t IO0        : 3;
            uint32_t reserved   : 1;
            uint32_t IO1        : 3;
            uint32_t reserved1  : 1;
            uint32_t IO2        : 3;
            uint32_t reserved2  : 1;
            uint32_t IO3        : 3;
            uint32_t reserved3  : 1;
            uint32_t IO4        : 3;
            uint32_t reserved4  : 1;
            uint32_t IO5        : 3;
            uint32_t reserved5  : 1;
            uint32_t IO6        : 3;
            uint32_t reserved6  : 1;
            uint32_t IO7        : 3;
            uint32_t reserved7  : 1;
        } fields;

        uint32_t value;
    };
};

struct VCSFIO_REG_SEL1 {
    union {
        struct {
            uint32_t IO8        : 3;
            uint32_t reserved   : 1;
            uint32_t IO9        : 3;
            uint32_t reserved1  : 1;
            uint32_t IO10       : 3;
            uint32_t reserved2  : 1;
            uint32_t IO11       : 3;
            uint32_t reserved3  : 1;
            uint32_t IO12       : 3;
            uint32_t reserved4  : 1;
            uint32_t IO13       : 3;
            uint32_t reserved5  : 1;
            uint32_t IO14       : 3;
            uint32_t reserved6  : 1;
            uint32_t IO15       : 3;
            uint32_t reserved7  : 1;
        } fields;

        uint32_t value;
    };
};

struct VCSFIO_REG_SEL {
    union {
        struct {
            uint32_t IO0        : 2;
            uint32_t IO1        : 2;
            uint32_t IO2        : 2;
            uint32_t IO3        : 2;
            uint32_t IO4        : 2;
            uint32_t IO5        : 2;
            uint32_t IO6        : 2;
            uint32_t IO7        : 2;
            uint32_t IO8        : 2;
            uint32_t IO9        : 2;
            uint32_t IO10       : 2;
            uint32_t IO11       : 2;
            uint32_t IO12       : 2;
            uint32_t IO13       : 2;
            uint32_t IO14       : 2;
            uint32_t IO15       : 2;
        } fields;
    };

    uint32_t value;
};

struct VCSFIOF_REG_SEL {
    union {
        struct {
            uint32_t IO0        : 2;
            uint32_t IO1        : 2;
            uint32_t IO2        : 2;
            uint32_t IO3        : 2;
            uint32_t reserved   : 24;
        } fields;
    };

    uint32_t value;
};

struct VCIO_REG_OEN {
    union {
        struct {
            uint32_t OEN        : 16;    // (rw) ouput enable pin register (0: enable, 1: disable)
            uint32_t reserved   : 16;
        } fields;

        uint32_t value;
    };
};

struct VCIO_REG_IE {
    union {
        struct {
            uint32_t IE         : 16;    // (rw) input enable pin register (1: enable, 0: disable)
            uint32_t reserved   : 16;
        } fields;

        uint32_t value;
    };
};

struct VCIO_REG_DAT {
    union {
        struct {
            uint32_t DAT        : 16;
            uint32_t reserved   : 16;
        } fields;

        uint32_t value;
    };
};

struct VCIO_REG_ATT {
    union {
        struct {
            uint32_t ATT        : 16;   // (rw) 0: CMOS mode, 1: Open drain mode
            uint32_t reserved   : 16;
        } fields;

        uint32_t value;
    };
};

struct VCIO_REG_WKUEN {
    uint32_t value;
};

struct VCIO_REG_STS {
    union {
        struct {
            uint32_t STS        : 16;
            uint32_t reserved   : 16;
        } fields;

        uint32_t value;
    };
};

struct VCIO_REG_INT {
    union {
        struct {
            uint32_t INT        : 16;
            uint32_t reserved   : 16;
        } fields;

        uint32_t value;
    };
};

struct VCPMU_REG_CONTROL {
    union {
        struct {
            uint32_t INTEN      : 1;
            uint32_t reserved   : 31;
        } fields;

        uint32_t value;
    };
};

struct VCPMU_REG_DEG {
    union {
        struct {
            uint32_t IOANODEG   : 16;
            uint32_t reserved   : 16;
        } fields;

        uint32_t value;
    };
};

struct VCPMU_REG_SPACE {
    uint32_t reserved;                          // PMUDSLEEPEN
    uint32_t reserved1;                         // PMUDSLEEPPASS
    struct VCPMU_REG_CONTROL CONTROL;
    uint32_t reserved2[17];
    struct VCPMU_REG_DEG     DEG;
};

struct VCIOA_REG_SPACE {
    struct VCIO_REG_OEN         OEN;
    struct VCIO_REG_IE          IE;
    struct VCIO_REG_DAT         DAT;
    struct VCIO_REG_ATT         ATT;
    struct VCIO_REG_WKUEN       WKUEN;
    struct VCIO_REG_STS         STS;
    struct VCIO_REG_INT         INT;
};

struct VCIOC_REG_SPACE {
    struct VCIO_REG_OEN         OEN;
    struct VCIO_REG_IE          IE;
    struct VCIO_REG_DAT         DAT;
    struct VCIO_REG_ATT         ATT;
    struct VCIO_REG_STS         STS;
    uint32_t reserverd[6];
    struct VCIO_REG_WKUEN       WKUEN;
    struct VCIO_REG_INT         INT;
};

struct VCSFIO_REG_SPACE {                       // PORTA, PORTB, PORTC
    struct VCSFIO_REG_SEL0      SEL0;
    struct VCSFIO_REG_SEL1      SEL1;
};

struct VCSFIOD_REG_SPACE {                      // PORTD
    struct VCSFIO_REG_SEL       IODSEL;
};

struct VCSFIOE_REG_SPACE {                      // PORTE
    struct VCSFIO_REG_SEL       IOESEL;
};

struct VCSFIOF_REG_SPACE {                      // PORTF
    struct VCSFIOF_REG_SEL      IOFSEL;
};

struct VCSFIO_REG_IOMISC {
    union {
        struct {
            uint32_t PLLDIV     : 3;
            uint32_t reserverd  : 2;
            uint32_t I2CIOC     : 1;    // (rw) 0: I2C is at IOB13 ~ IOB14, 1: I2C is at IOC4 ~ IOC5
            uint32_t SPIMUX     : 2;
            uint32_t reserverd1 : 6;
            uint32_t ANATEST    : 2;
            uint32_t reserverd2 : 16;
        } fields;

        uint32_t value;
    };
};

struct VCSFIO_MISC_REG_SPACE {
    struct VCSFIO_REG_IOMISC    IOMISC;
};

void vcsfio_reset(uint8_t port, uint8_t pin)
{
    volatile struct VCPMU_REG_SPACE *pmu = (volatile struct VCPMU_REG_SPACE *)VCREG_BASE_PMU;

    volatile struct VCSFIO_REG_SPACE *ioa_sf = (volatile struct VCSFIO_REG_SPACE *)VCREG_BASE_IOASF;
    volatile struct VCSFIO_REG_SPACE *iob_sf = (volatile struct VCSFIO_REG_SPACE *)VCREG_BASE_IOBSF;
    volatile struct VCSFIO_REG_SPACE *ioc_sf = (volatile struct VCSFIO_REG_SPACE *)VCREG_BASE_IOCSF;

    volatile struct VCSFIOD_REG_SPACE *iod_sf = (volatile struct VCSFIOD_REG_SPACE *)VCREG_BASE_IODSF;
    volatile struct VCSFIOE_REG_SPACE *ioe_sf = (volatile struct VCSFIOE_REG_SPACE *)VCREG_BASE_IOESF;
    volatile struct VCSFIOF_REG_SPACE *iof_sf = (volatile struct VCSFIOF_REG_SPACE *)VCREG_BASE_IOFSF;

    switch (port) {
    case IOA:
        // enable back IOA de-glitch circuit as default config
        pmu->DEG.fields.IOANODEG &= ~(1 << pin);
        if (pin < 8) {
            ioa_sf->SEL0.value &= ~(0x7 << (pin * 4));
        } else {
            ioa_sf->SEL1.value &= ~(0x7 << ((pin - 8) * 4));
        }
        break;

    case IOB:
        if (pin < 8) {
            iob_sf->SEL0.value &= ~(0x7 << (pin * 4));
        } else {
            iob_sf->SEL1.value &= ~(0x7 << ((pin - 8) * 4));
        }
        break;

    case IOC:
        if (pin < 8) {
            ioc_sf->SEL0.value &= ~(0x7 << (pin * 4));
        } else {
            ioc_sf->SEL1.value &= ~(0x7 << ((pin - 8) * 4));
        }
        break;

    case IOD:
        iod_sf->IODSEL.value &= ~(0x3 << (pin * 2));
        break;

    case IOE:
        ioe_sf->IOESEL.value &= ~(0x3 << (pin * 2));
        break;

    case IOF:
        if (pin > 3) return; // IOF only support special function (IOF0 - IOF3)
        iof_sf->IOFSEL.value &= ~(0x3 << (pin * 2));
        break;

    default:
        break;
    }
}

void vcsfio_enable_uart(uint8_t uart)
{
    volatile struct VCSFIO_REG_SPACE *ioa_sf = (volatile struct VCSFIO_REG_SPACE *)VCREG_BASE_IOASF;
    volatile struct VCSFIO_REG_SPACE *iob_sf = (volatile struct VCSFIO_REG_SPACE *)VCREG_BASE_IOBSF;

    switch (uart) {
    case UART0:
        ioa_sf->SEL1.fields.IO12 = 0x3;   // UART RX0
        iob_sf->SEL0.fields.IO2  = 0x3;   // UART TX0
        break;

    case UART1:
        ioa_sf->SEL1.fields.IO13 = 0x3;   // UART RX1
        iob_sf->SEL0.fields.IO3  = 0x3;   // UART TX1
        break;

    case UART2:
        ioa_sf->SEL1.fields.IO14 = 0x3;   // UART RX2
        iob_sf->SEL0.fields.IO4  = 0x3;   // UART TX2
        break;

    case UART3:
        ioa_sf->SEL1.fields.IO15 = 0x3;   // UART RX3
        iob_sf->SEL0.fields.IO5  = 0x3;   // UART TX3
        break;

    case UART4:
        iob_sf->SEL0.fields.IO0  = 0x3;   // UART RX4
        iob_sf->SEL0.fields.IO6  = 0x3;   // UART TX4
        break;

    case UART5:
        iob_sf->SEL0.fields.IO1  = 0x3;   // UART RX5
        iob_sf->SEL0.fields.IO7  = 0x3;   // UART TX5
        break;

    case UART6:
        iob_sf->SEL1.fields.IO15 = 0x3;   // UART RX6
        iob_sf->SEL1.fields.IO8  = 0x3;   // UART TX6
        break;

    default:
        return;
    }
}

void vcsfio_disable_uart(uint8_t uart)
{
    if ((uart < UART0) || (uart > UART6)) return;

    volatile struct VCSFIO_REG_SPACE *ioa_sf = (volatile struct VCSFIO_REG_SPACE *)VCREG_BASE_IOASF;
    volatile struct VCSFIO_REG_SPACE *iob_sf = (volatile struct VCSFIO_REG_SPACE *)VCREG_BASE_IOBSF;

    switch (uart) {
    case UART0:
        ioa_sf->SEL1.fields.IO12 = 0;
        iob_sf->SEL0.fields.IO2  = 0;
        break;

    case UART1:
        ioa_sf->SEL1.fields.IO13 = 0;
        iob_sf->SEL0.fields.IO3  = 0;
        break;

    case UART2:
        ioa_sf->SEL1.fields.IO14 = 0;
        iob_sf->SEL0.fields.IO4  = 0;
        break;

    case UART3:
        ioa_sf->SEL1.fields.IO15 = 0;
        iob_sf->SEL0.fields.IO5  = 0;
        break;

    case UART4:
        iob_sf->SEL0.fields.IO0  = 0;
        iob_sf->SEL0.fields.IO6  = 0;
        break;

    case UART5:
        iob_sf->SEL0.fields.IO1  = 0;
        iob_sf->SEL0.fields.IO7  = 0;
        break;

    case UART6:
        iob_sf->SEL1.fields.IO15 = 0;
        iob_sf->SEL1.fields.IO8  = 0;
        break;

    default:
        return;
    }
}

#define SFIO_SPI1_CSN  (0x2 << 4)
#define SFIO_SPI1_CLK  (0x2 << 8)
#define SFIO_SPI1_MISO (0x2 << 12)
#define SFIO_SPI1_MOSI (0x2 << 16)

#define SFIO_SPI2_CSN  (0x2 << 0)
#define SFIO_SPI2_CLK  (0x2 << 4)
#define SFIO_SPI2_MISO (0x2 << 8)
#define SFIO_SPI2_MOSI (0x2 << 12)

#define SFIO_SPI3_CSN  (0x2 << 0)
#define SFIO_SPI3_CLK  (0x2 << 4)
#define SFIO_SPI3_MISO (0x2 << 8)
#define SFIO_SPI3_MOSI (0x2 << 12)

void vcsfio_enable_spi(uint8_t spi) // SPI1 --- SPI3
{
    volatile struct VCSFIO_REG_SPACE *iob_sf = (volatile struct VCSFIO_REG_SPACE *)VCREG_BASE_IOBSF;
    volatile struct VCSFIO_REG_SPACE *ioc_sf = (volatile struct VCSFIO_REG_SPACE *)VCREG_BASE_IOCSF;

    switch (spi) {
    case SPI1:
        if ((vcspi_get_mode(spi) == SPIMODE_MASTER) && (vcspi_get_csgpio_setting(spi) == 0)) {
            iob_sf->SEL1.value |= SFIO_SPI1_CSN;
        }
        iob_sf->SEL1.value |= (SFIO_SPI1_CLK | SFIO_SPI1_MISO | SFIO_SPI1_MOSI);
        break;

    case SPI2:
        if ((vcspi_get_mode(spi) == SPIMODE_MASTER) && (vcspi_get_csgpio_setting(spi) == 0)) {
            ioc_sf->SEL0.value |= SFIO_SPI2_CSN;
        }
        ioc_sf->SEL0.value |= (SFIO_SPI2_CLK | SFIO_SPI2_MISO | SFIO_SPI2_MOSI);
        break;

    case SPI3:
        if ((vcspi_get_mode(spi) == SPIMODE_MASTER) && (vcspi_get_csgpio_setting(spi) == 0)) {
            ioc_sf->SEL1.value |= SFIO_SPI3_CSN;
        }
        ioc_sf->SEL1.value |= (SFIO_SPI3_CLK | SFIO_SPI3_MISO | SFIO_SPI3_MOSI);
        break;

    default:
        break;
    }
}

void vcsfio_disable_spi(uint8_t spi)
{
    volatile struct VCSFIO_REG_SPACE *iob_sf = (volatile struct VCSFIO_REG_SPACE *)VCREG_BASE_IOBSF;
    volatile struct VCSFIO_REG_SPACE *ioc_sf = (volatile struct VCSFIO_REG_SPACE *)VCREG_BASE_IOCSF;

    switch (spi) {
    case SPI1:
        iob_sf->SEL1.value &= ~(SFIO_SPI1_CSN | SFIO_SPI1_CLK | SFIO_SPI1_MISO | SFIO_SPI1_MOSI);
        break;

    case SPI2:
        ioc_sf->SEL0.value &= ~(SFIO_SPI2_CSN | SFIO_SPI2_CLK | SFIO_SPI2_MISO | SFIO_SPI2_MOSI);
        break;

    case SPI3:
        ioc_sf->SEL1.value &=  ~(SFIO_SPI3_CSN | SFIO_SPI3_CLK | SFIO_SPI3_MISO | SFIO_SPI3_MOSI);
        break;

    default:
        break;
    }
}

void vcsfio_enable_int(uint8_t port, uint8_t pin, uint8_t detect)
{
    if (pin > 15) return;

    volatile struct VCPMU_REG_SPACE *pmu = (volatile struct VCPMU_REG_SPACE *)VCREG_BASE_PMU;

    volatile struct VCSFIO_REG_SPACE *ioa_sf = (volatile struct VCSFIO_REG_SPACE *)VCREG_BASE_IOASF;
    volatile struct VCSFIO_REG_SPACE *ioc_sf = (volatile struct VCSFIO_REG_SPACE *)VCREG_BASE_IOCSF;

    volatile struct VCIOA_REG_SPACE *ioa = (volatile struct VCIOA_REG_SPACE *)VCREG_BASE_IOA;
    volatile struct VCIOC_REG_SPACE *ioc = (volatile struct VCIOC_REG_SPACE *)VCREG_BASE_IOC;

    if (port == IOA) {
        // disable IOA de-glitch circuit
        pmu->DEG.fields.IOANODEG |= (1 << pin);

        pmu->CONTROL.fields.INTEN = 1;

        ioa->OEN.fields.OEN |= (1 << pin);   // output disable
        ioa->IE.fields.IE |= (1 << pin);     // input enable
        ioa->ATT.fields.ATT |= (1 << pin);   // open-drain attribute
        ioa->WKUEN.value &= ~(3 << (pin * 2));  // disable previous setting

        switch (detect) {
        case IODETECT_RISING:
            ioa->WKUEN.value |= (1 << (pin * 2));
            ioa->DAT.fields.DAT &= ~(1 << pin);
            break;
        case IODETECT_FALLING:
            ioa->WKUEN.value |= (1 << (pin *2));
            ioa->DAT.fields.DAT |= (1 << pin);
            break;
        case IODETECT_HIGH:
            ioa->WKUEN.value |= (2 << (pin * 2));
            ioa->DAT.fields.DAT &= ~(1 << pin);
            break;
        case IODETECT_LOW:
            ioa->WKUEN.value |= (2 << (pin * 2));
            ioa->DAT.fields.DAT |= (1 << pin);
            break;
        case IODETECT_EDGEBOTH:
            ioa->WKUEN.value |= (3 << (pin * 2));
            break;
        default:
            return;
        };

    } else if (port == IOC) {

        ioc->OEN.fields.OEN |= (1 << pin);   // output disable
        ioc->IE.fields.IE |= (1 << pin);     // input enable
        ioc->ATT.fields.ATT |= (1 << pin);   // open-drain attribute       
        ioc->WKUEN.value &= ~(3 << (pin * 2));  // disable previous setting

        switch (detect) {
        case IODETECT_RISING:
            ioc->WKUEN.value |= (1 << (pin * 2));
            ioc->DAT.fields.DAT &= ~(1 << pin);
            break;
        case IODETECT_FALLING:
            ioc->WKUEN.value |= (1 << (pin *2));
            ioc->DAT.fields.DAT |= (1 << pin);
            break;
        case IODETECT_HIGH:
            ioc->WKUEN.value |= (2 << (pin * 2));
            ioc->DAT.fields.DAT &= ~(1 << pin);
            break;
        case IODETECT_LOW:
            ioc->WKUEN.value |= (2 << (pin * 2));
            ioc->DAT.fields.DAT |= (1 << pin);
            break;
        case IODETECT_EDGEBOTH:
            ioc->WKUEN.value |= (3 << (pin * 2));
            break;
        default:
            return;
        };

    } else {
        return;
    }

    if (pin < 8) {
        if (port == IOA) {
            ioa_sf->SEL0.value |= (0x2 << (pin * 4));
        } else if (port == IOC) {
            ioc_sf->SEL0.value &= ~(1 << (pin * 4));
        }
    } else {
        if (port == IOA) {
            ioa_sf->SEL1.value |= (0x2 << ((pin - 8) * 4));
        } else if (port == IOC) {
            ioc_sf->SEL1.value &= ~(1 << ((pin - 8) * 4));
        }
    }
}

void vcsfio_disable_int(uint8_t port, uint8_t pin)
{
    if (pin > 15) return;

    volatile struct VCPMU_REG_SPACE *pmu = (volatile struct VCPMU_REG_SPACE *)VCREG_BASE_PMU;

    volatile struct VCSFIO_REG_SPACE *ioa_sf = (volatile struct VCSFIO_REG_SPACE *)VCREG_BASE_IOASF;
    volatile struct VCSFIO_REG_SPACE *ioc_sf = (volatile struct VCSFIO_REG_SPACE *)VCREG_BASE_IOCSF;

    volatile struct VCIOA_REG_SPACE *ioa = (volatile struct VCIOA_REG_SPACE *)VCREG_BASE_IOA;
    volatile struct VCIOC_REG_SPACE *ioc = (volatile struct VCIOC_REG_SPACE *)VCREG_BASE_IOC;

    if (port == IOA ) {
        // enable back IOA de-glicth circuit as default config
        pmu->DEG.fields.IOANODEG &= ~(1 << pin);

        pmu->CONTROL.fields.INTEN = 0;

        ioa->OEN.fields.OEN |= (1 << pin);   // output disable
        ioa->IE.fields.IE &= ~(1 << pin);    // input disable
        ioa->ATT.fields.ATT &= ~(1 << pin);  // cmos attribute

        ioa->WKUEN.value &= ~(3 << (pin * 2));
        ioa->DAT.fields.DAT &= ~(1 << pin);

    } else if (port == IOC) {

        ioc->OEN.fields.OEN |= (1 << pin);   // output disable
        ioc->IE.fields.IE &= ~(1 << pin);    // input disable
        ioc->ATT.fields.ATT &= ~(1 << pin);  // cmos attribute

        ioc->WKUEN.value &= ~(3 << (pin * 2));
        ioc->DAT.fields.DAT &= ~(1 << pin);

    } else {
        return;
    }

    if (port == IOA) {
        if (pin < 8) {
            ioa_sf->SEL0.value &= ~(0x7 << (pin * 4));
        } else {
            ioa_sf->SEL1.value &= ~(0x7 << ((pin - 8) * 4));
        }
    }

    if (port == IOC) {
        if (pin < 8) {
            ioc_sf->SEL0.value &= ~(0x7 << (pin * 4));
        } else {
            ioc_sf->SEL1.value &= ~(0x7 << ((pin - 8) * 4));
        }
    }
}

int vcsfio_get_int(uint8_t port, uint8_t pin)
{
    int retval = 0;

    if (pin > 15) return retval;

    volatile struct VCIOA_REG_SPACE *ioa =  (volatile struct VCIOA_REG_SPACE *)VCREG_BASE_IOA;
    volatile struct VCIOC_REG_SPACE *ioc =  (volatile struct VCIOC_REG_SPACE *)VCREG_BASE_IOC;

    if (port == IOA) {
        retval = (ioa->INT.fields.INT & (1 << pin)) ? 1 : 0;
    } else if (port == IOC) {
        retval = (ioc->INT.fields.INT & (1 << pin)) ? 1 : 0;
    } else {
        retval = 0;
    }

    return retval;
}

void vcsfio_clear_int(uint8_t port, uint8_t pin)
{
    if (pin > 15) return;

    volatile struct VCIOA_REG_SPACE *ioa =  (volatile struct VCIOA_REG_SPACE *)VCREG_BASE_IOA;
    volatile struct VCIOC_REG_SPACE *ioc =  (volatile struct VCIOC_REG_SPACE *)VCREG_BASE_IOC;

    if (port == IOA) {
        ioa->INT.fields.INT = (1 << pin);
    } else if (port == IOC) {
        ioc->INT.fields.INT = (1 << pin);
    } else {
        return;
    }
}

static int is_pwm_io_valid(uint8_t pwm_io)
{
    return (pwm_io < PWM_IO0 || pwm_io > PWM_IO3) ? 0 : 1;
}

void vcsfio_enable_pwm(uint8_t pwm_io)
{
    if (!is_pwm_io_valid(pwm_io)) return;

    volatile struct VCSFIO_REG_SPACE *iob_sf = (volatile struct VCSFIO_REG_SPACE *)VCREG_BASE_IOBSF;

    switch (pwm_io) {
    case PWM_IO0: // IOB0
        iob_sf->SEL0.fields.IO0 = 2;
        break;

    case PWM_IO1: // IOB6
        iob_sf->SEL0.fields.IO6 = 2;
        break;

    case PWM_IO2: // IOB13
        iob_sf->SEL1.fields.IO13 = 2;
        break;

    case PWM_IO3: // IOB14
        iob_sf->SEL1.fields.IO14 = 2;
        break;

    default:
        break;
    }
}

void vcsfio_disable_pwm(uint8_t pwm_io)
{
    if (!is_pwm_io_valid(pwm_io)) return;

    volatile struct VCSFIO_REG_SPACE *iob_sf = (volatile struct VCSFIO_REG_SPACE *)VCREG_BASE_IOBSF;

    switch (pwm_io) {
    case PWM_IO0: // IOB0
        iob_sf->SEL0.fields.IO0 = 0;
        break;

    case PWM_IO1: // IOB6
        iob_sf->SEL0.fields.IO6 = 0;
        break;

    case PWM_IO2: // IOB13
        iob_sf->SEL1.fields.IO13 = 0;
        break;

    case PWM_IO3: // IOB14
        iob_sf->SEL1.fields.IO14 = 0;
        break;

    default:
        break;
    }
}

void vcsfio_config_spimux(uint8_t spimux)
{
    if (spimux > 3) return;

    volatile struct VCSFIO_MISC_REG_SPACE *reg_space = (volatile struct VCSFIO_MISC_REG_SPACE *)VCREG_BASE_IOMISC;

    reg_space->IOMISC.fields.SPIMUX = spimux;
}

int vcsfio_get_ioc_int_enable_status(uint8_t pin)
{
    if (pin > 15) return 0;

    volatile struct VCIOC_REG_SPACE *ioc =  (volatile struct VCIOC_REG_SPACE *)VCREG_BASE_IOC;

    return (ioc->WKUEN.value & (3 << (pin *2))) != 0;
}

#define SFIO_I2C1_SDA (0x3 << 24)
#define SFIO_I2C1_SCL (0x3 << 20)

#define SFIO_I2C2_SDA (0x3 << 20)
#define SFIO_I2C2_SCL (0x3 << 16)

void vcsfio_enable_i2c(uint8_t i2c)
{
    volatile struct VCSFIO_REG_SPACE *iob_sf = (volatile struct VCSFIO_REG_SPACE *)VCREG_BASE_IOBSF;
    volatile struct VCSFIO_REG_SPACE *ioc_sf = (volatile struct VCSFIO_REG_SPACE *)VCREG_BASE_IOCSF;

    switch (i2c) {
    case I2C1:
        iob_sf->SEL1.value |= (SFIO_I2C1_SDA | SFIO_I2C1_SCL);
        break;

    case I2C2:
        ioc_sf->SEL0.value |= (SFIO_I2C2_SDA | SFIO_I2C2_SCL);
        break;

    default:
        break;
    }
}

void vcsfio_enable_iob1_hrco_out(void)
{
    volatile struct VCSFIO_REG_SPACE *iob_sf = (volatile struct VCSFIO_REG_SPACE *)VCREG_BASE_IOBSF;

    iob_sf->SEL0.fields.IO1 = 0x4;

    *(volatile unsigned *)(0x4004B014) |= 0x10;
}

#define SFIO_FSPI_WPN      (0x5 << 4)
#define SFIO_FSPI_HOLDN    (0x5 << 28)
#define SFIO_FSPI_SRAMCSN  (0x5 << 0)
#define SFIO_FSPI_FLASHCSN (0x5 << 4)
#define SFIO_FSPI_CLK      (0x5 << 8)
#define SFIO_FSPI_MISO     (0x5 << 12)
#define SFIO_FSPI_MOSI     (0x5 << 16)

void vcsfio_enable_iob_spisram(void)
{
    // IOB1 = WPN
    // IOB7 = HOLDN
    // IOB8 = SSRAM_CSN
    // IOB10 = CLK
    // IOB11 = MISO
    // IOB12 = MOSI

    volatile struct VCSFIO_REG_SPACE *iob_sf = (volatile struct VCSFIO_REG_SPACE *)VCREG_BASE_IOBSF;

    iob_sf->SEL0.value |= (SFIO_FSPI_WPN | SFIO_FSPI_HOLDN);
    iob_sf->SEL1.value |= (SFIO_FSPI_SRAMCSN | SFIO_FSPI_CLK | SFIO_FSPI_MISO | SFIO_FSPI_MOSI);
}

void vcsfio_enable_iob_quadmode_spiflash(void)
{
    // IOB1 = WPN
    // IOB7 = HOLDN

    volatile struct VCSFIO_REG_SPACE *iob_sf = (volatile struct VCSFIO_REG_SPACE *)VCREG_BASE_IOBSF;

    iob_sf->SEL0.value |= (SFIO_FSPI_WPN | SFIO_FSPI_HOLDN);
}

void vcsfio_enable_iob_spiflash(void)
{
    // IOB9 = CSN
    // IOB10 = CLK
    // IOB11 = MISO
    // IOB12 = MOSI

    volatile struct VCSFIO_REG_SPACE *iob_sf = (volatile struct VCSFIO_REG_SPACE *)VCREG_BASE_IOBSF;

    iob_sf->SEL1.value |= (SFIO_FSPI_FLASHCSN | SFIO_FSPI_CLK | SFIO_FSPI_MISO | SFIO_FSPI_MOSI);
}
