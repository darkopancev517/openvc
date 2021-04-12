#include "centauri_timer.h"

extern void systick_usec_delay(uint32_t usec);
extern uint32_t systick_usec_now(void);

void cent_busy_wait(uint32_t us)
{
    systick_usec_delay(us);
}

uint32_t cent_usec_now(void)
{
    return systick_usec_now();
}
