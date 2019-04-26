/**
 * Copyright (c) 2018 Vertexcom Technologies, Inc. All rights reserved
 * Vertexcom Confidential Proprietary
 *
*/

#include "vcsoc.h"

#define VCREG_BASE_UART0            0x40043000
#define VCREG_BASE_UART1            0x40043040
#define VCREG_BASE_UART(i)          (VCREG_BASE_UART0 + ((i) * (VCREG_BASE_UART1 - VCREG_BASE_UART0)))

struct VCUART_REG_DATA {
    union {
        struct {
            uint32_t DATA           : 8;    // (rw) read/write rx/tx FIFO
            uint32_t PE             : 1;    // (r) parity error status of received data
            uint32_t reserved       : 23;
        } fields;

        uint32_t value;
    };
};

struct VCUART_REG_STATE {
    union {
        struct {
            uint32_t TXFULL         : 1;    // (r) transmit FIFO full
            uint32_t RXHFULL        : 1;    // (r) receive FIFO half-full
            uint32_t TXOV           : 1;    // (rc) transmit buffer overrun flag
            uint32_t RXOV           : 1;    // (rc) receive buffer overrun flag
            uint32_t RXPE           : 1;    // (rc) receive buffer parity error flag
            uint32_t TXDONE         : 1;    // (rc) transmit done flag
            uint32_t RXPSTS         : 1;    // (r) receive parity data flag
            uint32_t reserved       : 25;
        } fields;

        uint32_t value;
    };
};

struct VCUART_REG_CTRL {
    union {
        struct {
            uint32_t TXEN           : 1;    // (rw) transmit engine enable
            uint32_t RXEN           : 1;    // (rw) receive engine enable
            uint32_t TXIE           : 1;    // (rw) transmit interrupt enable
            uint32_t RXIE           : 1;    // (rw) receive interrupt enable
            uint32_t TXOVIE         : 1;    // (rw) transmit overrun interrupt enable
            uint32_t RXOVIE         : 1;    // (rw) receive overrun interrupt enable
            uint32_t TEST           : 1;    // (rw) high speed test for TX only
            uint32_t RXPEIE         : 1;    // (rw) receive parity error interrupt enable
            uint32_t TXDONEIE       : 1;    // (rw) transmit done interrupt enable register
            uint32_t reserved       : 23;
        } fields;

        uint32_t value;
    };
};

struct VCUART_REG_INTSTS {
    union {
        struct {
            uint32_t TXIF           : 1;    // (rc) transmit interrupt flag
            uint32_t RXIF           : 1;    // (rc) receive interrupt flag
            uint32_t TXOVIF         : 1;    // (rc) transmit overrun interrupt flag
            uint32_t RXOVIF         : 1;    // (rc) receive overrun interrupt flag
            uint32_t RXPEIF         : 1;    // (rc) receive parity error interrupt flag
            uint32_t TXDONEIF       : 1;    // (rc) transmit done interrupt flag
            uint32_t reserved       : 26;
        } fields;

        uint32_t value;
    };
};

struct VCUART_REG_BAUDDIV {
    union {
        struct {
            uint32_t BAUDIV         : 20;   // (rw) baudrate divider register (BAUDDIV : APBCLK / baudrate)
            uint32_t reserved       : 12;
        } fields;

        uint32_t value;
    };
};

struct VCUART_REG_CTRL2 {
    union {
        struct {
            uint32_t MSB            : 1;    // (rw) LSB/MSB transmit order control
            uint32_t PEN            : 1;    // (rw) parity enable bit control
            uint32_t PMODE          : 2;    // (rw) parity mode control
            uint32_t LENGTH         : 1;    // (rw) uart byte length control register
            uint32_t STOPLEN        : 1;    // (rw) uart transmit stop bit control register
            uint32_t IREN           : 1;    // (rw) IR carrier transmit enable
            uint32_t reserved       : 25;
        } fields;

        uint32_t value;
    };
};

struct VCUART_REG_DUTY {
    union {
        struct {
            uint32_t DUTYL          : 16;   // (rw) IR low pulse width control register
            uint32_t DUTYH          : 16;   // (rw) IR high pulse width control register
        } fields;

        uint32_t value;
    };
};

struct VCUART_REG_FIFOCTRL {
    union {
        struct {
            uint32_t RXFIFOLVL      : 3;    // (rw) receive FIFO level control register
            uint32_t reserved       : 1;
            uint32_t TXFIFOLVL      : 3;    // (rw) transmit FIFO level control register
            uint32_t reserved2      : 7;
            uint32_t OVMODE         : 1;    // (rw) FIFO overflow mode control register
            uint32_t SFRST          : 1;    // (rw) FIFO software reset of transmit and receive FIFO
            uint32_t reserved3      : 16;
        } fields;

        uint32_t value;
    };
};

struct VCUART_REG_FIFOSTS {
    union {
        struct {
            uint32_t RXFIFOLAST     : 4;    // (r) receive FIFO data last status register
            uint32_t RXFIFOHEMPTY   : 1;    // (r) receive FIFO half empty flag
            uint32_t RXFIFOEMPTY    : 1;    // (r) receive FIFO empty flag
            uint32_t RXFIFOHFULL    : 1;    // (r) receive FIFO half full flag
            uint32_t RXFIFOFULL     : 1;    // (r) receive FIFO full flag
            uint32_t TXFIFOLAST     : 4;    // (r) transmit FIFO data last status register
            uint32_t TXFIFOHEMPTY   : 1;    // (r) transmit FIFO half empty flag
            uint32_t TXFIFOEMPTY    : 1;    // (r) transmit FIFO empty flag
            uint32_t TXFIFOHFULL    : 1;    // (r) transmit FIFO half full flag
            uint32_t TXFIFOFULL     : 1;    // (r) transmit FIFO full flag
            uint32_t reserved       : 16;
        } fields;

        uint32_t value;
    };
};

struct VCUART_REG_SPACE {
    struct VCUART_REG_DATA     DATA;
    struct VCUART_REG_STATE    STATE;
    struct VCUART_REG_CTRL     CTRL;
    struct VCUART_REG_INTSTS   INTSTS;
    struct VCUART_REG_BAUDDIV  BAUDDIV;
    struct VCUART_REG_CTRL2    CTRL2;
    struct VCUART_REG_DUTY     DUTY;
    struct VCUART_REG_FIFOCTRL FIFOCTRL;
    struct VCUART_REG_FIFOSTS  FIFOSTS;
};

void vcuart_config_reset(uint8_t uart)
{
    if ((uart < UART0) || (uart > UART6)) return;

    volatile struct VCUART_REG_SPACE *reg_space = (volatile struct VCUART_REG_SPACE *)VCREG_BASE_UART(uart);

    reg_space->DATA.value = 0;

    // clear uart state
    reg_space->STATE.value = 0x3C;

    reg_space->CTRL.value = 0;

    // clear uart interrupt status
    reg_space->INTSTS.value = 0x3F;

    reg_space->BAUDDIV.value = 0;
    reg_space->CTRL2.value = 0;

    reg_space->DUTY.value = 0;
    reg_space->FIFOCTRL.value = 0x70;
}

void vcuart_config_clk_source(uint8_t uart, bool state)
{
    if ((uart < UART0) || (uart > UART6)) return;

    switch (uart) {
    case UART0:
        vcmisc_config_apb_periph(APBPERIPH_UART0, state);
        break;

    case UART1:
        vcmisc_config_apb_periph(APBPERIPH_UART1, state);
        break;

    case UART2:
        vcmisc_config_apb_periph(APBPERIPH_UART2, state);
        break;

    case UART3:
        vcmisc_config_apb_periph(APBPERIPH_UART3, state);
        break;

    case UART4:
        vcmisc_config_apb_periph(APBPERIPH_UART4, state);
        break;

    case UART5:
        vcmisc_config_apb_periph(APBPERIPH_UART5, state);
        break;

    case UART6:
        vcmisc_config_apb_periph(APBPERIPH_UART6, state);
        break;

    default:
        break;
    }
}

void vcuart_config_mode(uint8_t uart, uint8_t mode)
{
    if ((uart < UART0) || (uart > UART6)) return;

    volatile struct VCUART_REG_SPACE *reg_space = (volatile struct VCUART_REG_SPACE *)VCREG_BASE_UART(uart);

    switch (mode) {
    case UARTMODE_TX:
        reg_space->CTRL.fields.TXEN = 1;
        reg_space->CTRL.fields.RXEN = 0;
        break;

    case UARTMODE_RX:
        reg_space->CTRL.fields.TXEN = 0;
        reg_space->CTRL.fields.RXEN = 1;
        break;

    case UARTMODE_TXRX:
        reg_space->CTRL.fields.TXEN = 1;
        reg_space->CTRL.fields.RXEN = 1;
        break;

    default:
        break;
    }
}

void vcuart_config_parity(uint8_t uart, uint8_t parity)
{
    if ((uart < UART0) || (uart > UART6)) return;

    volatile struct VCUART_REG_SPACE *reg_space = (volatile struct VCUART_REG_SPACE *)VCREG_BASE_UART(uart);

    if (parity ==  UARTPARITY_NONE) {
        reg_space->CTRL2.fields.PEN = 0;    // disable parity bit control
    } else {
        reg_space->CTRL2.fields.PEN = 1;    // enable parity bit control
        reg_space->CTRL2.fields.PMODE = parity;
    }
}

void vcuart_config_stoplen(uint8_t uart, uint8_t stoplen)
{
    if ((uart < UART0) || (uart > UART6)) return;

    volatile struct VCUART_REG_SPACE *reg_space = (volatile struct VCUART_REG_SPACE *)VCREG_BASE_UART(uart);

    reg_space->CTRL2.fields.STOPLEN = stoplen;
}

void vcuart_config_wordlen(uint8_t uart, uint8_t wordlen)
{
    if ((uart < UART0) || (uart > UART6)) return;

    volatile struct VCUART_REG_SPACE *reg_space = (volatile struct VCUART_REG_SPACE *)VCREG_BASE_UART(uart);

    reg_space->CTRL2.fields.LENGTH = wordlen;
}

void vcuart_config_firstbit(uint8_t uart, uint8_t firstbit)
{
    if ((uart < UART0) || (uart > UART6)) return;

    volatile struct VCUART_REG_SPACE *reg_space = (volatile struct VCUART_REG_SPACE *)VCREG_BASE_UART(uart);

    reg_space->CTRL2.fields.MSB = firstbit;
}

void vcuart_config_baudrate(uint8_t uart, uint32_t baudrate)
{
    if ((uart < UART0) || (uart > UART6)) return;

    volatile struct VCUART_REG_SPACE *reg_space = (volatile struct VCUART_REG_SPACE *)VCREG_BASE_UART(uart);

    uint32_t pclk = vcmisc_get_apb_clk();
    uint32_t div = pclk / baudrate;

    if ((pclk % baudrate) > (baudrate / 2)) div++;

    reg_space->BAUDDIV.value = div;
}

void vcuart_config_fifo_softrst(uint8_t uart, bool state)
{
    if ((uart < UART0) || (uart > UART6)) return;

    volatile struct VCUART_REG_SPACE *reg_space = (volatile struct VCUART_REG_SPACE *)VCREG_BASE_UART(uart);
   
    reg_space->FIFOCTRL.fields.SFRST = (state == true) ? 1 : 0;
}

void vcuart_config_fifo_ovmode(uint8_t uart, bool state)
{
    if ((uart < UART0) || (uart > UART6)) return;

    volatile struct VCUART_REG_SPACE *reg_space = (volatile struct VCUART_REG_SPACE *)VCREG_BASE_UART(uart);

    reg_space->FIFOCTRL.fields.OVMODE = (state == true) ? 1 : 0;
}

void vcuart_config_fifo_txlevel(uint8_t uart, uint8_t level)
{
    if ((uart < UART0) || (uart > UART6)) return;

    volatile struct VCUART_REG_SPACE *reg_space = (volatile struct VCUART_REG_SPACE *)VCREG_BASE_UART(uart);

    reg_space->FIFOCTRL.fields.TXFIFOLVL = level;
}

void vcuart_config_fifo_rxlevel(uint8_t uart, uint8_t level)
{
    if ((uart < UART0) || (uart > UART6)) return;

    volatile struct VCUART_REG_SPACE *reg_space = (volatile struct VCUART_REG_SPACE *)VCREG_BASE_UART(uart);

    reg_space->FIFOCTRL.fields.RXFIFOLVL = level;
}

void vcuart_config_enable_int(uint8_t uart, uint8_t interrupt)
{
    if ((uart < UART0) || (uart > UART6)) return;

    volatile struct VCUART_REG_SPACE *reg_space = (volatile struct VCUART_REG_SPACE *)VCREG_BASE_UART(uart);

    switch (interrupt) {
    case UARTINT_TXDONE:
        reg_space->CTRL.fields.TXDONEIE = 1;
        return;

    case UARTINT_RXPE:
        reg_space->CTRL.fields.RXPEIE = 1;
        return;

    case UARTINT_RXOV:
        reg_space->CTRL.fields.RXOVIE = 1;
        return;

    case UARTINT_TXOV:
        reg_space->CTRL.fields.TXOVIE = 1;
        return;

    case UARTINT_RX:
        reg_space->CTRL.fields.RXIE = 1;
        return;

    case UARTINT_TX:
        reg_space->CTRL.fields.TXIE = 1;
        return;

    default:
        return;
    };
}

void vcuart_config_disable_int(uint8_t uart, uint8_t interrupt)
{
    if ((uart < UART0) || (uart > UART6)) return;

    volatile struct VCUART_REG_SPACE *reg_space = (volatile struct VCUART_REG_SPACE *)VCREG_BASE_UART(uart);

    switch (interrupt) {
    case UARTINT_TXDONE:
        reg_space->CTRL.fields.TXDONEIE = 0;
        return;

    case UARTINT_RXPE:
        reg_space->CTRL.fields.RXPEIE = 0;
        return;

    case UARTINT_RXOV:
        reg_space->CTRL.fields.RXOVIE = 0;
        return;

    case UARTINT_TXOV:
        reg_space->CTRL.fields.TXOVIE = 0;
        return;

    case UARTINT_RX:
        reg_space->CTRL.fields.RXIE = 0;
        return;

    case UARTINT_TX:
        reg_space->CTRL.fields.TXIE = 0;
        return;

    default:
        return;
    };
}

void vcuart_send_byte(uint8_t uart, uint8_t c)
{
    if ((uart < UART0) || (uart > UART6)) return;

    volatile struct VCUART_REG_SPACE *reg_space = (volatile struct VCUART_REG_SPACE *)VCREG_BASE_UART(uart);

    reg_space->DATA.value = c;
}

uint8_t vcuart_recv_byte(uint8_t uart)
{
    if ((uart < UART0) || (uart > UART6)) return 0;

    volatile struct VCUART_REG_SPACE *reg_space = (volatile struct VCUART_REG_SPACE *)VCREG_BASE_UART(uart);

    return (uint8_t)reg_space->DATA.fields.DATA;
}

int vcuart_fifo_get(uint8_t uart, int n, uint8_t *buf)
{
    if ((uart < UART0) || (uart > UART6)) return 0;

    volatile struct VCUART_REG_SPACE *reg_space = (volatile struct VCUART_REG_SPACE *)VCREG_BASE_UART(uart);

    int i;

    for (i = 0; (i < n) && reg_space->FIFOSTS.fields.RXFIFOLAST; i++) {
        buf[i] = (uint8_t)reg_space->DATA.fields.DATA;
    }

    return i;
}

int vcuart_get_status(uint8_t uart, uint8_t status)
{
    int retval = 0;

    if ((uart < UART0) || (uart > UART6)) return retval;

    volatile struct VCUART_REG_SPACE *reg_space = (volatile struct VCUART_REG_SPACE *)VCREG_BASE_UART(uart);

    switch (status) {
    case UARTSTS_TXFULL:
        retval = (reg_space->STATE.fields.TXFULL == 1) ? 1 : 0;
        break;

    case UARTSTS_RXHFULL:
        retval = (reg_space->STATE.fields.RXHFULL == 1) ? 1 : 0;
        break;

    case UARTSTS_TXOV:
        retval = (reg_space->STATE.fields.TXOV == 1) ? 1 : 0;
        break;

    case UARTSTS_RXOV:
        retval = (reg_space->STATE.fields.RXOV == 1) ? 1 : 0;
        break;

    case UARTSTS_RXPE:
        retval = (reg_space->STATE.fields.RXPE == 1) ? 1 : 0;
        break;

    case UARTSTS_TXDONE:
        retval = (reg_space->STATE.fields.TXDONE == 1) ? 1 : 0;
        break;

    case UARTSTS_RXPSTS:
        retval = (reg_space->STATE.fields.RXPSTS == 1) ? 1 : 0;
        break;

    default:
        break;
    };

    return retval;
}

void vcuart_clear_status(uint8_t uart, uint8_t status)
{
    if ((uart < UART0) || (uart > UART6)) return;

    volatile struct VCUART_REG_SPACE *reg_space = (volatile struct VCUART_REG_SPACE *)VCREG_BASE_UART(uart);

    switch (status) {
    case UARTSTS_TXFULL:
        reg_space->STATE.fields.TXFULL = 1;
        break;

    case UARTSTS_RXHFULL:
        reg_space->STATE.fields.RXHFULL = 1;
        break;

    case UARTSTS_TXOV:
        reg_space->STATE.fields.TXOV = 1;
        break;

    case UARTSTS_RXOV:
        reg_space->STATE.fields.RXOV = 1;
        break;

    case UARTSTS_RXPE:
        reg_space->STATE.fields.RXPE = 1;
        break;

    case UARTSTS_TXDONE:
        reg_space->STATE.fields.TXDONE = 1;
        break;

    case UARTSTS_RXPSTS:
        reg_space->STATE.fields.RXPSTS = 1;
        break;

    default:
        break;
    };
}

int vcuart_get_int_status(uint8_t uart, uint8_t interrupt)
{
    int retval = 0;

    if ((uart < UART0) || (uart > UART6)) return retval;

    volatile struct VCUART_REG_SPACE *reg_space = (volatile struct VCUART_REG_SPACE *)VCREG_BASE_UART(uart);

    switch (interrupt) {
    case UARTINT_TXDONE:
        retval = (reg_space->INTSTS.fields.TXDONEIF == 1) ? 1 : 0;
        break;

    case UARTINT_RXPE:
        retval = (reg_space->INTSTS.fields.RXPEIF == 1) ? 1 : 0;
        break;

    case UARTINT_RXOV:
        retval = (reg_space->INTSTS.fields.RXOVIF == 1) ? 1 : 0;
        break;

    case UARTINT_TXOV:
        retval = (reg_space->INTSTS.fields.TXOVIF == 1) ? 1 : 0;
        break;

    case UARTINT_RX:
        retval = (reg_space->INTSTS.fields.RXIF == 1) ? 1 : 0;
        break;

    case UARTINT_TX:
        retval = (reg_space->INTSTS.fields.TXIF == 1) ? 1 : 0;
        break;

    default:
        break;
    };

    return retval;
}

void vcuart_clear_int_status(uint8_t uart, uint8_t interrupt)
{
    if ((uart < UART0) || (uart > UART6)) return;

    volatile struct VCUART_REG_SPACE *reg_space = (volatile struct VCUART_REG_SPACE *)VCREG_BASE_UART(uart);

    switch (interrupt) {
    case UARTINT_TXDONE:
        reg_space->INTSTS.fields.TXDONEIF = 1;
        break;

    case UARTINT_RXPE:
        reg_space->INTSTS.fields.RXPEIF = 1;
        break;

    case UARTINT_RXOV:
        reg_space->INTSTS.fields.RXOVIF = 1;
        break;

    case UARTINT_TXOV:
        reg_space->INTSTS.fields.TXOVIF = 1;
        break;

    case UARTINT_RX:
        reg_space->INTSTS.fields.RXIF = 1;
        break;

    case UARTINT_TX:
        reg_space->INTSTS.fields.TXIF = 1;
        break;

    default:
        return;
    };
}

int vcuart_rxfifo_last(uint8_t uart)
{
    volatile struct VCUART_REG_SPACE *reg_space = (volatile struct VCUART_REG_SPACE *)VCREG_BASE_UART(uart);
    return reg_space->FIFOSTS.fields.RXFIFOLAST;
}

uint32_t vcuart_get_transmit_addr(uint8_t uart)
{
    if ((uart < UART0) || (uart > UART6)) return 0;

    volatile struct VCUART_REG_SPACE *reg_space = (volatile struct VCUART_REG_SPACE *)VCREG_BASE_UART(uart);

    return (uint32_t)&reg_space->DATA;
}
