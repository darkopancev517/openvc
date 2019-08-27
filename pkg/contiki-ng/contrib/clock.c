#include "xtimer.h"

#include "contiki.h"

void clock_init(void)
{
    // clock already initialize in xtimer_init()
}

clock_time_t clock_time(void)
{
    return (clock_time_t)xtimer_now().ticks32;
}

unsigned long clock_seconds(void)
{
    return (unsigned long)(clock_time() / 1000);
}

void clock_wait(clock_time_t i)
{
    xtimer_msleep((uint32_t)i);
}

void clock_delay_usec(uint16_t dt)
{
    (void) dt;
}

void clock_delay(unsigned int i)
{
    clock_wait((clock_time_t)i);
}
