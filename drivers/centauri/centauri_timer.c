#include "centauri_timer.h"

void cent_busy_wait(uint32_t us)
{
    uint32_t clock_tick = 39; /* 39 tick / usec */
    uint32_t delay = clock_tick * us;
    while (delay--);
}
