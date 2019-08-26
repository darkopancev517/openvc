#include <assert.h>
#include <stdbool.h>

#include "cpu.h"
#include "vcsoc.h"
#include "periph/timer.h"

#define TIMER_NUMOF (4U)
#define TIMER_CHAN  TIMER_NUMOF

typedef struct {
    uint32_t ccr[TIMER_CHAN];   /* capture compare register */
    uint32_t ier[TIMER_CHAN];   /* interrupt enable register */
    uint32_t cnt;
    uint32_t freq;
} timer_regs_t;

static int timer_irqn[TIMER_NUMOF] = {
    Tim0_IRQn,
    Tim1_IRQn,
    Tim2_IRQn,
    Tim3_IRQn
};

static bool timer_regs_is_initialized = false;
static uint32_t timer_cnt_max = 0xffffffff;
static volatile timer_regs_t timer_regs[TIMER_NUMOF];
static timer_isr_ctx_t isr_timer_ctx[TIMER_NUMOF];

int timer_init(tim_t dev, unsigned long freq, timer_cb_t cb, void *arg)
{
    assert(dev < TIMER_NUMOF);

    if (!timer_regs_is_initialized) {
        for (int i = 0; i < TIMER_NUMOF; i++) {
            for (int ch = 0; ch < TIMER_CHAN; ch++) {
                timer_regs[i].ccr[ch] = 0;
                timer_regs[i].ier[ch] = 0;
            }
            timer_regs[i].cnt = 0;
        }
        timer_regs_is_initialized = true;
    }

    /* remember the interrupt context */
    isr_timer_ctx[dev].cb = cb;
    isr_timer_ctx[dev].arg = arg;

    /* enable the peripheral clock */
    vcmisc_config_apb_periph(APBPERIPH_TIMER, true);

    vctim_config_reset(dev);
    vctim_config_clock_source(dev, TIM_CLKSRC_INTERNAL);
    vctim_config_external_clock_gate(dev, false);

    /* set timer frequency base */
    timer_regs[dev].freq = freq;

    /* reset the counter */
    timer_regs[dev].cnt = 0;

    return 0;
}

int timer_set_absolute(tim_t dev, int channel, unsigned int value)
{
    assert(dev < TIMER_NUMOF);
    assert(channel < TIMER_CHAN);
    assert(timer_regs[dev].freq != 0);

    timer_regs[dev].ccr[channel] = (value & timer_cnt_max);
    timer_regs[dev].ier[channel] = 1;

    uint32_t reload = (vcmisc_get_apb_clk() / timer_regs[dev].freq) * value;
    vctim_config_reload_value(dev, reload);
    vctim_set_value(dev, 0);

    timer_start(dev);

    return 0;
}

int timer_clear(tim_t dev, int channel)
{
    assert(dev < TIMER_NUMOF);
    assert(channel < TIMER_CHAN);

    timer_regs[dev].ier[channel] = 0;

    return 0;
}

uint32_t timer_read(tim_t dev)
{
    assert(dev < TIMER_NUMOF);
    return timer_regs[dev].cnt;
}

void timer_start(tim_t dev)
{
    vctim_config_enable_int(dev);
    NVIC_EnableIRQ(timer_irqn[dev]);
    vctim_enable(dev);
}

void timer_stop(tim_t dev)
{
    vctim_config_disable_int(dev);
    NVIC_DisableIRQ(timer_irqn[dev]);
    vctim_disable(dev);
}

static void irq_timer_handler(tim_t dev)
{
    if (vctim_get_int(dev)) {
        vctim_clear_int(dev);
        timer_regs[dev].cnt += 1;
        if (isr_timer_ctx[dev].cb != NULL) {
            for (unsigned int i = 0; i < TIMER_CHAN; i++) {
                if ((timer_regs[dev].ccr[i] == timer_regs[dev].cnt) &&
                    (timer_regs[dev].ier[i] == 1)) { 
                    isr_timer_ctx[dev].cb(isr_timer_ctx[dev].arg, i);
                }
            }
        }
    }
    /* check if context switch was requested */
    cortexm_isr_end();
}

/* TIMER interrupt function entry */
void isr_tim0(void)
{
    irq_timer_handler(TIMER_DEV(0));
}

void isr_tim1(void)
{
    irq_timer_handler(TIMER_DEV(1));
}

void isr_tim2(void)
{
    irq_timer_handler(TIMER_DEV(2));
}

void isr_tim3(void)
{
    irq_timer_handler(TIMER_DEV(3));
}
