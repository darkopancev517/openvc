#include <assert.h>
#include <stdio.h>
#include "centauri_prober.h"

#define CENT_AHB_GPIO_BASE         0x40010000
#define CENT_AHB_GPIO_DATA         0x0000
#define CENT_AHB_GPIO_DATAOUT      0x0004
#define CENT_AHB_GPIO_OUTENSET     0x0010
#define CENT_AHB_GPIO_OUTENCLR     0x0014
#define CENT_AHB_GPIO_ALTFUNCSET   0x0018
#define CENT_AHB_GPIO_ALTFUNCCLR   0x001C
#define CENT_AHB_GPIO_INTENSET     0x0020
#define CENT_AHB_GPIO_INTENCLR     0x0024
#define CENT_AHB_GPIO_INTTYPESET   0x0028
#define CENT_AHB_GPIO_INTTYPECLR   0x002C
#define CENT_AHB_GPIO_INTPOLSET    0x0030
#define CENT_AHB_GPIO_INTPOLCLR    0x0034
#define CENT_AHB_GPIO_INTSTATUS    0x0038
#define CENT_AHB_GPIO_INTCLEAR     0x0038
#define CENT_AHB_GPIO_MASKLOWBYTE  0x0400
#define CENT_AHB_GPIO_MASKHIGHBYTE 0x0800

static void assert_pin(int pin)
{
    assert(pin >= 0 && pin <= 15);
}

void cent_gpio_set_output_mode(int pin)
{
    assert_pin(pin);
    cent_spi_writeW(CENT_AHB_GPIO_BASE + CENT_AHB_GPIO_OUTENSET, (1 << pin));
}

void cent_gpio_clear_output_mode(int pin)
{
    assert_pin(pin);
    cent_spi_writeW(CENT_AHB_GPIO_BASE + CENT_AHB_GPIO_OUTENCLR, (1 << pin));
}

void cent_gpio_set_data(int pin)
{
    uint32_t reg_addr;

    assert_pin(pin);

    if (pin < 8) {
        reg_addr = CENT_AHB_GPIO_BASE + CENT_AHB_GPIO_MASKLOWBYTE + ((1 << pin) * 4);
    } else {
        reg_addr = CENT_AHB_GPIO_BASE + CENT_AHB_GPIO_MASKHIGHBYTE + ((1 << pin) * 4);
    }

    cent_spi_writeW(reg_addr, (1 << pin));
}

void cent_gpio_clear_data(int pin)
{
    uint32_t reg_addr;

    assert_pin(pin);

    if (pin < 8) {
        reg_addr = CENT_AHB_GPIO_BASE + CENT_AHB_GPIO_MASKLOWBYTE + ((1 << pin) * 4);
    } else {
        reg_addr = CENT_AHB_GPIO_BASE + CENT_AHB_GPIO_MASKHIGHBYTE + ((1 << pin) * 4);
    }

    cent_spi_writeW(reg_addr, 0);
}

uint32_t cent_gpio_get_data(int pin)
{
    uint32_t reg_addr, val;

    assert_pin(pin);

    if (pin < 8) {
        reg_addr = CENT_AHB_GPIO_BASE + CENT_AHB_GPIO_MASKLOWBYTE + ((1 << pin) * 4);
    } else {
        reg_addr = CENT_AHB_GPIO_BASE + CENT_AHB_GPIO_MASKHIGHBYTE + ((1 << pin) * 4);
    }

    cent_spi_readW(reg_addr, &val);

    return val;
}
