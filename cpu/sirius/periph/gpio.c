#include <assert.h>

#include "cpu.h"
#include "vcsoc.h"
#include "periph/gpio.h"

/**
 * Sirius has 32 external interupt lines, 16 pins of PORTA and 16 pins of PORTC.
 */
#define EXTI_NUMOF (32U)

/**
 * isr_gpio_ctx index 0-15 will be used to store PORTA pins and the rest will
 * be used for PORTC pins.
 */
static gpio_isr_ctx_t isr_gpio_ctx[EXTI_NUMOF];

static uint8_t gpio_int_detect[3] = {
    IODETECT_FALLING,
    IODETECT_RISING,
    IODETECT_EDGEBOTH
};

static uint8_t _port(gpio_t pin)
{
    /* get the port number from given GPIO_PIN() */
    return (pin & 0xf);
}

static uint8_t _pin(gpio_t pin)
{
    /* get the pin number from given GPIO_PIN() */
    return ((pin >> 4) & 0xf);
}

int gpio_init(gpio_t pin, gpio_mode_t mode)
{
    vcgpio_reset(_port(pin), _pin(pin));

    /* enable gpio clock */
    vcmisc_config_ahb_periph(AHBPERIPH_GPIO, true);

    if (mode == GPIO_IN) {
        /* input */
        vcgpio_config_mode(_port(pin), _pin(pin), IOMODE_IN);
        vcgpio_config_att(_port(pin), _pin(pin), IOATT_CMOS);
    } else if (mode == GPIO_IN_PD) {
        /* input pull-down */
        vcgpio_config_mode(_port(pin), _pin(pin), IOMODE_IN);
        vcgpio_config_att(_port(pin), _pin(pin), IOATT_OPEN_DRAIN);
        vcgpio_reset_bit(_port(pin), _pin(pin));
    } else if (mode == GPIO_IN_PU) {
        /* input pull-up */
        vcgpio_config_mode(_port(pin), _pin(pin), IOMODE_IN);
        vcgpio_config_att(_port(pin), _pin(pin), IOATT_OPEN_DRAIN);
        vcgpio_set_bit(_port(pin), _pin(pin));
    } else if (mode == GPIO_OUT) {
        /* output */
        vcgpio_config_mode(_port(pin), _pin(pin), IOMODE_OUT);
        vcgpio_config_att(_port(pin), _pin(pin), IOATT_CMOS);
    } else if (mode == GPIO_OD) {
        /* open-drain output low */
        vcgpio_config_mode(_port(pin), _pin(pin), IOMODE_OUT);
        vcgpio_config_att(_port(pin), _pin(pin), IOATT_OPEN_DRAIN);
        vcgpio_reset_bit(_port(pin), _pin(pin));
    } else if (mode == GPIO_OD_PU) {
        /* open-drain output high */
        vcgpio_config_mode(_port(pin), _pin(pin), IOMODE_OUT);
        vcgpio_config_att(_port(pin), _pin(pin), IOATT_OPEN_DRAIN);
        vcgpio_set_bit(_port(pin), _pin(pin));
    } else {
        assert(0); /* unknown gpio mode */
    }

    return 0;
}

int gpio_init_int(gpio_t pin,
                  gpio_mode_t mode,
                  gpio_flank_t flank,
                  gpio_cb_t cb,
                  void *arg)
{
    uint8_t port_num = _port(pin);
    uint8_t pin_num = _pin(pin);

    assert((port_num == PORTA) || (port_num == PORTC));

    /* set callback */
    isr_gpio_ctx[(8 * port_num) + pin_num].cb = cb;
    isr_gpio_ctx[(8 * port_num) + pin_num].arg = arg;

    /* initialize pin as input */
    gpio_init(pin, mode);

    /* enable gpio interrupt special function */
    vcsfio_enable_int(_port(pin), _pin(pin), gpio_int_detect[flank]);

    /* enable global pin interrupt */
    gpio_irq_enable(pin);

    return 0;
}

void gpio_irq_enable(gpio_t pin)
{
    /* enable global pin interrupt */
    if (_port(pin) == PORTA) {
        NVIC_EnableIRQ(Pmu_IRQn);
    } else {
        NVIC_EnableIRQ(Gpio_IRQn);
    }
}

void gpio_irq_disable(gpio_t pin)
{
    /* disable special function interrupt io */
    vcsfio_disable_int(_port(pin), _pin(pin));
}

int gpio_read(gpio_t pin)
{
    return vcgpio_read_output_bit(_port(pin), _pin(pin));
}

void gpio_set(gpio_t pin)
{
    vcgpio_set_bit(_port(pin), _pin(pin));
}

void gpio_clear(gpio_t pin)
{
    vcgpio_reset_bit(_port(pin), _pin(pin));
}

void gpio_toggle(gpio_t pin)
{
    if (gpio_read(pin)) {
        gpio_clear(pin);
    } else {
        gpio_set(pin);
    }
}

void gpio_write(gpio_t pin, int value)
{
    if (value) {
        gpio_set(pin);
    } else {
        gpio_clear(pin);
    }
}

static void irq_gpio_handler(gpio_t pin)
{
    uint8_t index = (8 * _port(pin) + _pin(pin));
    if (isr_gpio_ctx[index].cb != NULL) {
        isr_gpio_ctx[index].cb(isr_gpio_ctx[index].arg);
        /* check if context switch was requested */
        cortexm_isr_end();
    }
}

/* GPIO interrupt function entry */
void isr_pmu(void)
{
    for (int i = 0; i < 16; i++) {
        if (vcsfio_get_int(PORTA, i)) {
            vcsfio_clear_int(PORTA, i);
            irq_gpio_handler(GPIO_PIN(PORTA, i));
            return;
        }
    }
}

void isr_gpio(void)
{
    for (int i = 0; i < 16; i++) {
        if (vcsfio_get_int(PORTC, i)) {
            vcsfio_clear_int(PORTC, i);
            irq_gpio_handler(GPIO_PIN(PORTC, i));
            return;
        }
    }
}
