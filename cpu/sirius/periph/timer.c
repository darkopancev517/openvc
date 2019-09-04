#include <assert.h>
#include <stdbool.h>

#include "cpu.h"
#include "vcsoc.h"
#include "periph/timer.h"

#define TIMER_NUMOF         (4U)
#define TIMER_CHAN_NUMOF    (3U)

static int timer_irqn[TIMER_NUMOF] = {
    Pwm0_IRQn,
    Pwm1_IRQn,
    Pwm2_IRQn,
    Pwm3_IRQn
};

static timer_isr_ctx_t isr_timer_ctx[TIMER_NUMOF];

int timer_init(tim_t dev, unsigned long freq, timer_cb_t cb, void *arg)
{
    assert(dev < TIMER_NUMOF);

    /* remember the interrupt context */
    isr_timer_ctx[dev].cb = cb;
    isr_timer_ctx[dev].arg = arg;

    /* enable the peripheral clock */
    vcmisc_config_apb_periph(APBPERIPH_TIMER, true);

    vcpwm_config_reset(dev);

    /* only support 1 MHz frequency base */
    assert(freq == 1000000ul);

    /* use apb clock as clock source */
    vcpwm_config_clock_source(dev, PWM_CLKSRC_APB);

    /* (system_core_clock / 2(apb_div)) / 16 = (39.3216 / 2) / 16 = ~1 MHz */
    vcpwm_config_clock_division(dev, PWM_CLKDIV16);

    /* start pwm timer */
    timer_start(dev);

    return 0;
}

int timer_set_absolute(tim_t dev, int channel, unsigned int value)
{
    assert(dev < TIMER_NUMOF && channel < TIMER_CHAN_NUMOF);
    vcpwm_config_ccr_period(dev, channel, value);
    vcpwm_config_enable_cc_int(dev, channel);
    NVIC_EnableIRQ(timer_irqn[dev]);
    return 0;
}

int timer_clear(tim_t dev, int channel)
{
    assert(dev < TIMER_NUMOF && channel < TIMER_CHAN_NUMOF);
    vcpwm_config_ccr_period(dev, channel, 0xffff);
    vcpwm_clear_counter(dev);
    return 0;
}

uint32_t timer_read(tim_t dev)
{
    assert(dev < TIMER_NUMOF);
    return vcpwm_get_counter(dev);
}

void timer_start(tim_t dev)
{
    assert(dev < TIMER_NUMOF);
    vcpwm_config_mode(dev, PWM_MODE_CONTINOUS);
}

void timer_stop(tim_t dev)
{
    assert(dev < TIMER_NUMOF);
    vcpwm_config_mode(dev, PWM_MODE_STOP);
}

static void irq_timer_handler(tim_t dev)
{
    for (uint8_t ch = 0; ch < TIMER_CHAN_NUMOF; ch++) {
        if (vcpwm_get_cc_int_status(dev, ch, PWM_CCINT_CCIFG)) {
            vcpwm_clear_cc_int_status(dev, ch, PWM_CCINT_CCIFG);
            vcpwm_config_disable_cc_int(dev, ch);
            NVIC_DisableIRQ(timer_irqn[dev]);
            if (isr_timer_ctx[dev].cb != NULL && vcpwm_get_ccr_val(dev, ch) != 0) {
                isr_timer_ctx[dev].cb(isr_timer_ctx[dev].arg, ch);
                /* check if context switch was requested */
                cortexm_isr_end();
                break;
            }
        }
    }
}

/* PWM TIMER interrupt function entry */
void isr_pwm0(void)
{
    irq_timer_handler(TIMER_DEV(0));
}

void isr_pwm1(void)
{
    irq_timer_handler(TIMER_DEV(1));
}

void isr_pwm2(void)
{
    irq_timer_handler(TIMER_DEV(2));
}

void isr_pwm3(void)
{
    irq_timer_handler(TIMER_DEV(3));
}
