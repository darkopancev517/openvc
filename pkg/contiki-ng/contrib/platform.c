#include "contiki.h"
#include "sys/platform.h"
#include "xtimer.h"

void platform_init_stage_one(void)
{
    // reserved for boot up init sequence
}

void platform_init_stage_two(void)
{
    // platform init for networking and timers
    xtimer_init();
}

void platform_init_stage_three(void)
{
    // low-level driver and sensor (optional)
}
