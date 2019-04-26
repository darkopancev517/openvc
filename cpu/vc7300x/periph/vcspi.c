/**
 * Copyright (c) 2018 Vertexcom Technologies, Inc. All rights reserved
 * Vertexcom Confidential Proprietary
 *
*/

#include "vcsoc.h"

#define VCREG_BASE_SPI1         0x40042000
#define VCREG_BASE_SPI2         0x40042080
#define VCREG_BASE_SPI3         0x40042100

struct VCSPI_REG_CTRL {
    union {
        struct {
            uint32_t CLKDIVL        : 4;
            uint32_t SCKPOL         : 1;
            uint32_t SCKPHA         : 1;
            uint32_t WIDTH          : 2;
            uint32_t MOD            : 1;
            uint32_t SWAP           : 1;
            uint32_t CSGPIO         : 1;
            uint32_t SPIRST         : 1;    // (w) SPI soft reset, reset spi controller and fifo pointer
            uint32_t LSBF           : 1;
            uint32_t BYTEORDER      : 1;
            uint32_t reserved       : 1;
            uint32_t SPIEN          : 1;
            uint32_t CLKDIVH        : 4;
            uint32_t reserved1      : 12;
        } fields;

        uint32_t value;
    };
};

struct VCSPI_REG_TXSTS {
    union {
        struct {
            uint32_t TXFFLAG        : 4;    // (r) transmit fifo data level
            uint32_t TXFLEV         : 3;    // (rw) transmit fifo interrupt level register
            uint32_t reserved       : 1;
            uint32_t TXFUR          : 1;    // (r) transmit fifo under run register
            uint32_t TXEMPTY        : 1;    // (r) transmit fifo empty register
            uint32_t reserved1      : 4;
            uint32_t SPITXIEN       : 1;    // (rw) spi transmit interrupt enable
            uint32_t SPITXIF        : 1;    // (rw) spi transmit interrupt flag
            uint32_t reserved2      : 16;
        } fields;

        uint32_t value;
    };
};

struct VCSPI_REG_TXDAT {
    union {
        struct {
            uint32_t SPITXD         : 8;    // (w) write data to spi transmit fifo
            uint32_t reserved       : 24;
        } fields;

        uint32_t value;
    };
};

struct VCSPI_REG_RXSTS {
    union {
        struct {
            uint32_t RXFFLAG        : 4;    // (r) receive fifo data level
            uint32_t RXFLEV         : 3;    // (rw) receive fifo interrupt level register
            uint32_t reserved       : 1;
            uint32_t RXFOV          : 1;    // (r) receive fifo over run register
            uint32_t RXFULL         : 1;    // (r) receive fifo full register
            uint32_t reserved1      : 4;
            uint32_t SPIRXIEN       : 1;    // (rw) spi receive interrupt enable
            uint32_t SPIRXIF        : 1;    // (rw) spi transmit interrupt flag
            uint32_t reserved2      : 16;
        } fields;

        uint32_t value;
    };
};

struct VCSPI_REG_RXDAT {
    union {
        struct {
            uint32_t SPIRXD         : 8;    // (r) read data from spi receive fifo 
            uint32_t reserved       : 24;
        } fields;

        uint32_t value;
    };
};

struct VCSPI_REG_MISC {
    union {
        struct {
            uint32_t TFE            : 1;    // (r) transmit fifo empty flag
            uint32_t TNF            : 1;    // (r) transmit fifo not full flag
            uint32_t RNE            : 1;    // (r) receive fifo not empty flag
            uint32_t RFF            : 1;    // (r) receive fifo full flag
            uint32_t BSY            : 1;    // (r) spi controller busy flag
            uint32_t reserved       : 3;
            uint32_t SMART          : 1;    // (rw) spi fifo smart mode register
            uint32_t OVER           : 1;    // (rw) spi fifo over write mode
            uint32_t LATTIME        : 1;    // (rw) spi input latch timing control
            uint32_t LOOPBACK       : 1;    // (rw) spi loop back mode
            uint32_t reserved1      : 20;
        } fields;

        uint32_t value;
    };
};

struct VCSPI_REG_SPACE {
    struct VCSPI_REG_CTRL   CTRL;
    struct VCSPI_REG_TXSTS  TXSTS;
    struct VCSPI_REG_TXDAT  TXDAT;
    struct VCSPI_REG_RXSTS  RXSTS;
    struct VCSPI_REG_RXDAT  RXDAT;
    struct VCSPI_REG_MISC   MISC;
};

volatile struct VCSPI_REG_SPACE *reg_spi[3] = {
    (volatile struct VCSPI_REG_SPACE *)VCREG_BASE_SPI1,
    (volatile struct VCSPI_REG_SPACE *)VCREG_BASE_SPI2,
    (volatile struct VCSPI_REG_SPACE *)VCREG_BASE_SPI3
};

static int assert_spi(uint8_t spi)
{
    return ((spi < SPI1) || (spi > SPI3)) ? 0 : 1;
}

#if (CONFIG_DEBUG_SPI==1)
void spi_dump()
{
}
#endif

void vcspi_enable(uint8_t spi)
{
    if (!assert_spi(spi)) return;
    reg_spi[spi]->CTRL.fields.SPIEN = 1;
}

void vcspi_disable(uint8_t spi)
{
    if (!assert_spi(spi)) return;
    reg_spi[spi]->CTRL.fields.SPIEN = 0;
}

void vcspi_config_reset(uint8_t spi)
{
    if (!assert_spi(spi)) return;
    reg_spi[spi]->CTRL.fields.SPIRST = 1;
    reg_spi[spi]->CTRL.value = 0;
}

void vcspi_config_clk_source(uint8_t spi, bool state)
{
    if (!assert_spi(spi)) return;

    switch (spi) {
    case SPI1:
        vcmisc_config_apb_periph(APBPERIPH_SPI1, state);
        return;
    case SPI2:
        vcmisc_config_apb_periph(APBPERIPH_SPI2, state);
        return;
    case SPI3:
        vcmisc_config_apb_periph(APBPERIPH_SPI3, state);
        return;
    default:
        return;
    }
}

void vcspi_config_mode(uint8_t spi, uint8_t mode)
{
    if (!assert_spi(spi)) return;
    if ((mode < SPIMODE_MASTER) || (mode > SPIMODE_SLAVE)) return;
    reg_spi[spi]->CTRL.fields.MOD = mode;
}

void vcspi_config_sck_phase(uint8_t spi, uint8_t phase)
{
    if (!assert_spi(spi)) return;
    if ((phase < 0) || (phase > 1)) return;
    reg_spi[spi]->CTRL.fields.SCKPHA = phase;
}

void vcspi_config_sck_polarity(uint8_t spi, uint8_t polarity)
{
    if (!assert_spi(spi)) return;
    if ((polarity < 0) || (polarity > 1)) return;
    reg_spi[spi]->CTRL.fields.SCKPOL = polarity;
}

void vcspi_config_clk_div(uint8_t spi, uint8_t div)
{
    if (!assert_spi(spi)) return;
    if ((div < 1) || (div > 256)) return;
    reg_spi[spi]->CTRL.fields.CLKDIVL = div - 1;
}

void vcspi_config_master_cs_gpio(uint8_t spi, bool state)
{
    if (!assert_spi(spi)) return;
    // 0: cs controled by spi h/w (default)
    // 1: cs controled by gpio setting
    reg_spi[spi]->CTRL.fields.CSGPIO = (state == true) ? 1 : 0;
}

void vcspi_config_slave_cs_master(uint8_t spi, bool state)
{
    if (!assert_spi(spi)) return;
    // 0: cs controlled by external master (default)
    // 1: cs pin connected to logic 0
    reg_spi[spi]->CTRL.fields.CSGPIO = (state == true) ? 0 : 1;
}

void vcspi_config_swap(uint8_t spi, bool state)
{
    if (!assert_spi(spi)) return;
    reg_spi[spi]->CTRL.fields.SWAP = (state == true) ? 1 : 0;
}

void vcspi_config_transfer_width(uint8_t spi, uint8_t width)
{
    if (!assert_spi(spi)) return;
    if ((width < SPIWIDTH_8BITS) || (width > SPIWIDTH_32BITS)) return;
    reg_spi[spi]->CTRL.fields.WIDTH = width;
}

void vcspi_config_firstbit(uint8_t spi, uint8_t firstbit)
{
    if (!assert_spi(spi)) return;
    if ((firstbit < SPIFIRSTBIT_MSB) || (firstbit > SPIFIRSTBIT_LSB)) return;
    reg_spi[spi]->CTRL.fields.LSBF = firstbit;
}

void vcspi_config_fifo_transmit(uint8_t spi, uint8_t level)
{
    if (!assert_spi(spi)) return;
    if ((level < SPIFIFO_TXLEV_1) || (level > SPIFIFO_TXLEV_8)) return;
    reg_spi[spi]->TXSTS.fields.TXFLEV = level;
}

void vcspi_config_fifo_receive(uint8_t spi, uint8_t level)
{
    if (!assert_spi(spi)) return;
    if ((level < SPIFIFO_RXLEV_1) || (level > SPIFIFO_RXLEV_8)) return;
    reg_spi[spi]->RXSTS.fields.RXFLEV = level;
}

void vcspi_config_enable_int(uint8_t spi, uint8_t interrupt)
{
    if (!assert_spi(spi)) return;
    if ((interrupt != SPIINT_TX) && (interrupt != SPIINT_RX)) return;
    if (interrupt == SPIINT_TX) {
        reg_spi[spi]->TXSTS.fields.SPITXIEN = 1;
    } else if (interrupt == SPIINT_RX) {
        reg_spi[spi]->RXSTS.fields.SPIRXIEN = 1;
    }
}

void vcspi_config_disable_int(uint8_t spi, uint8_t interrupt)
{
    if (!assert_spi(spi)) return;
    if ((interrupt != SPIINT_TX) && (interrupt != SPIINT_RX)) return;
    if (interrupt == SPIINT_TX) {
        reg_spi[spi]->TXSTS.fields.SPITXIEN = 0;
    } else if (interrupt == SPIINT_RX) {
        reg_spi[spi]->RXSTS.fields.SPIRXIEN = 0;
    }
}

uint8_t vcspi_get_fifo_transmit_level(uint8_t spi)
{
    if (!assert_spi(spi)) return 0;
    return (uint8_t)reg_spi[spi]->TXSTS.fields.TXFFLAG;
}

uint8_t vcspi_get_fifo_receive_level(uint8_t spi)
{
    if (!assert_spi(spi)) return 0;
    return (uint8_t)reg_spi[spi]->RXSTS.fields.RXFFLAG;
}

uint8_t vcspi_get_status(uint8_t spi, uint8_t status)
{
    if (!assert_spi(spi)) return 0;
    if ((status < SPISTATUS_TXIF) || (status > SPISTATUS_TFE)) return 0;
    switch (status) {
    case SPISTATUS_TXIF:
        return (uint8_t)reg_spi[spi]->TXSTS.fields.SPITXIF;
    case SPISTATUS_TXEMPTY:
        return (uint8_t)reg_spi[spi]->TXSTS.fields.TXEMPTY;
    case SPISTATUS_TXFUR:
        return (uint8_t)reg_spi[spi]->TXSTS.fields.TXFUR;
    case SPISTATUS_RXIF:
        return (uint8_t)reg_spi[spi]->RXSTS.fields.SPIRXIF;
    case SPISTATUS_RXFULL:
        return (uint8_t)reg_spi[spi]->RXSTS.fields.RXFULL;
    case SPISTATUS_RXFOV:
        return (uint8_t)reg_spi[spi]->RXSTS.fields.RXFOV;
    case SPISTATUS_BSY:
        return (uint8_t)reg_spi[spi]->MISC.fields.BSY;
    case SPISTATUS_RFF:
        return (uint8_t)reg_spi[spi]->MISC.fields.RFF;
    case SPISTATUS_RNE:
        return (uint8_t)reg_spi[spi]->MISC.fields.RNE;
    case SPISTATUS_TNF:
        return (uint8_t)reg_spi[spi]->MISC.fields.TNF;
    case SPISTATUS_TFE:
        return (uint8_t)reg_spi[spi]->MISC.fields.TFE;
    default:
        return 0;
    }
}

uint8_t vcspi_get_mode(uint8_t spi)
{
    if (!assert_spi(spi)) return 0;
    return (reg_spi[spi]->CTRL.fields.MOD == SPIMODE_MASTER) ? SPIMODE_MASTER : SPIMODE_SLAVE;
}

int vcspi_get_swap_setting(uint8_t spi)
{
    if (!assert_spi(spi)) return 0;
    return (reg_spi[spi]->CTRL.fields.SWAP == 1) ? 1 : 0;
}

int vcspi_get_csgpio_setting(uint8_t spi)
{
    if (!assert_spi(spi)) return 0;
    return (reg_spi[spi]->CTRL.fields.CSGPIO == 1) ? 1 : 0;
}

void vcspi_clear_status(uint8_t spi, uint8_t status)
{
    if (!assert_spi(spi)) return;
    if ((status < SPISTATUS_TXIF) || (status > SPISTATUS_RXFOV)) return;
    switch (status) {
    case SPISTATUS_TXIF:
        reg_spi[spi]->TXSTS.fields.SPITXIF = 1;
        return;
    case SPISTATUS_TXEMPTY:
        reg_spi[spi]->TXSTS.fields.TXEMPTY = 1;
        return;
    case SPISTATUS_TXFUR:
        reg_spi[spi]->TXSTS.fields.TXFUR = 1;
        return;
    case SPISTATUS_RXIF:
        reg_spi[spi]->RXSTS.fields.SPIRXIF = 1;
        return;
    case SPISTATUS_RXFULL:
        reg_spi[spi]->RXSTS.fields.RXFULL = 1;
        return;
    case SPISTATUS_RXFOV:
        reg_spi[spi]->RXSTS.fields.RXFOV = 1;
        return;
    default:
        return;
    }
}

void vcspi_overwrite_mode(uint8_t spi, bool state)
{
    if (!assert_spi(spi)) return;
    reg_spi[spi]->MISC.fields.OVER = (state == true) ? 1 : 0;
}

void vcspi_smart_mode(uint8_t spi, bool state)
{
    if (!assert_spi(spi)) return;
    reg_spi[spi]->MISC.fields.SMART = (state == true) ? 1 : 0;
}

void vcspi_send_byte(uint8_t spi, uint8_t data)
{
    if (!assert_spi(spi)) return;
    // wait until transmit fifo is empty
    while (!vcspi_get_status(spi, SPISTATUS_TFE));
    reg_spi[spi]->TXDAT.fields.SPITXD = data;
}

uint8_t vcspi_receive_byte(uint8_t spi)
{
    if (!assert_spi(spi)) return 0;
    // wait unti receive fifo not empty
    while (!vcspi_get_status(spi, SPISTATUS_RNE));
    return (uint8_t)reg_spi[spi]->RXDAT.fields.SPIRXD;
}

uint32_t vcspi_get_receive_addr(uint8_t spi)
{
    if (!assert_spi(spi)) return 0;
    return (uint32_t)&reg_spi[spi]->RXDAT;
}

uint32_t vcspi_get_transmit_addr(uint8_t spi)
{
    if (!assert_spi(spi)) return 0;
    return (uint32_t)&reg_spi[spi]->TXDAT;
}
