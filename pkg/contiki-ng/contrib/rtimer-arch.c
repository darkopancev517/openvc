#include <assert.h>
#include <stdbool.h>

#include "contiki.h"
#include "sys/rtimer.h"

void rtimer_arch_init(void)
{
    // init by clock_init();
}

void rtimer_arch_schedule(rtimer_clock_t t)
{
    assert(0); /* not supported */
}

rtimer_clock_t rtimer_arch_now(void)
{
    return (rtimer_clock_t)clock_time();
}
