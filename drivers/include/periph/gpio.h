#ifndef PERIPH_GPIO_H
#define PERIPH_GPIO_H

#include <limits.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef unsigned int gpio_t;

#define GPIO_UNDEF ((gpio_t)(UINT_MAX))

#define GPIO_PIN(port, pin) ((gpio_t)((port & 0xf) | ((pin & 0xf) << 4)))

/**
 * GPIO port definition.
 */
enum {
    PORTA,
    PORTB,
    PORTC,
    PORTD,
    PORTE,
};

typedef enum {
    GPIO_IN,            /* configure as input without pull resistor */
    GPIO_IN_PD,         /* configure as input with pull-down resistor */
    GPIO_IN_PU,         /* configure as input with pull-up resistor */
    GPIO_OUT,           /* configure as output in push-pull mode */
    GPIO_OD,            /* configure as output in open-drain mode without pull resistor */
    GPIO_OD_PU          /* configure as output in open-drain mode with pull resistor enabled */
} gpio_mode_t;

/**
 * Definition of possible active flanks for external interrupt mode.
 */
typedef enum {
    GPIO_FALLING = 0,   /* emit interrupt on falling flank */
    GPIO_RISING = 1,    /* emit interrupt on rising flank */
    GPIO_BOTH = 2       /* emit interrupt on both flank */
} gpio_flank_t;

/**
 * Signature of event callback functions triggered from interrupts.
 */
typedef void (*gpio_cb_t)(void *arg);

typedef struct {
    gpio_cb_t cb;
    void *arg;
} gpio_isr_ctx_t;

int gpio_init(gpio_t pin, gpio_mode_t mode);

int gpio_init_int(gpio_t pin,
                  gpio_mode_t mode,
                  gpio_flank_t flank,
                  gpio_cb_t cb,
                  void *arg);

void gpio_irq_enable(gpio_t pin);

void gpio_irq_disable(gpio_t pin);

int gpio_read(gpio_t pin);

void gpio_set(gpio_t pin);

void gpio_clear(gpio_t pin);

void gpio_toggle(gpio_t pin);

void gpio_write(gpio_t pin, int value);

#ifdef __cplusplus
}
#endif

#endif /* PERIPH_GPIO_H */
