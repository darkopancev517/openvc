#include "contiki.h"
#include "sys/platform.h"
#include "xtimer.h"

void platform_init_stage_one(void)
{
}

void platform_init_stage_two(void)
{
}

void platform_init_stage_three(void)
{
    extern void uart_arch_init(void);
    uart_arch_init();
}
