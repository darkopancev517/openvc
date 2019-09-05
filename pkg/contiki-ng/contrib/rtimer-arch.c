#include <assert.h>
#include <stdbool.h>

#include "contiki.h"
#include "sys/rtimer.h"

#include "xtimer.h"

xtimer_t rtimer_arch;

static void _rtimer_arch_callback(void *arg)
{
    rtimer_run_next();
}

void rtimer_arch_init(void)
{
    // init by clock_init();
}

void rtimer_arch_schedule(rtimer_clock_t t)
{
    rtimer_arch.callback = _rtimer_arch_callback;
    rtimer_arch.arg = NULL;
    rtimer_arch.target = rtimer_arch.long_target = 0;
    xtimer_set64(&rtimer_arch, (uint64_t)t);
}

rtimer_clock_t rtimer_arch_now(void)
{
    return (rtimer_clock_t)xtimer_now().ticks32;
}
