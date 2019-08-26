#include "xtimer.h"
#include "periph/timer.h"

void xtimer_init(void)
{
    timer_init(XTIMER_DEV, XTIMER_FREQ_BASE, NULL, NULL);
    timer_set_absolute(XTIMER_DEV, 0, 1000); /* 1 ms interval */
}

xtimer_ticks32_t xtimer_now(void)
{
    xtimer_ticks32_t ret;
    ret.ticks32 = timer_read(XTIMER_DEV);
    return ret;
}

void xtimer_msleep(uint32_t milliseconds)
{
    uint32_t timeout = xtimer_now().ticks32 + milliseconds;
    while (xtimer_now().ticks32 < timeout);
}
