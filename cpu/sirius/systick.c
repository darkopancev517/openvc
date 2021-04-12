#include <stdint.h>

#include "cpu.h"
#include "vcsoc.h"

#ifdef MODULE_PKG_CONTIKI_NG
#include "contiki.h"
#endif

static volatile uint32_t systick_ms_tick = 0;

void systick_init(void)
{
    SysTick_Config(vcmisc_get_sys_core_clk() / 1000);
    NVIC_SetPriority(SysTick_IRQn, CPU_DEFAULT_IRQ_PRIO);
    NVIC_EnableIRQ(SysTick_IRQn);
}

uint32_t systick_msec_now(void)
{
    return systick_ms_tick;
}

uint32_t systick_usec_now(void)
{
    return (systick_ms_tick * 1000) + 1000 - (SysTick->VAL / (vcmisc_get_sys_core_clk() / 1000000));
}

void systick_usec_delay(uint32_t usec)
{
    uint32_t timeout = systick_usec_now() + usec;
    while (systick_usec_now() < timeout);
}

void isr_systick(void)
{
    systick_ms_tick++;
#ifdef MODULE_PKG_CONTIKI_NG
    if (etimer_pending()) {
        etimer_request_poll();
    }
#endif
}
