#include "centauri_timer.h"
#include "xtimer.h"

void cent_busy_wait(uint32_t us)
{
    xtimer_usleep(us);
}
