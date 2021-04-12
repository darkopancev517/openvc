#include "contiki.h"

extern uint32_t systick_msec_now(void);
extern void systick_usec_delay(uint32_t usec);

void clock_init(void)
{
    // clock already initialize in systick_init()
}

clock_time_t clock_time(void)
{
    return (clock_time_t)systick_msec_now();
}

unsigned long clock_seconds(void)
{
    return (unsigned long)(clock_time() / 1000);
}

void clock_wait(clock_time_t i)
{
    systick_usec_delay((uint32_t)i * 1000);
}

void clock_delay_usec(uint16_t dt)
{
    systick_usec_delay(dt);
}

void clock_delay(unsigned int i)
{
    clock_wait((clock_time_t)i);
}
