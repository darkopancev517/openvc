#include <assert.h>
#include <stdint.h>
#include <string.h>

#include "xtimer.h"
#include "irq.h"
#include "div.h"

#include "timex.h"

#define ENABLE_DEBUG 0
#include "debug.h"

static volatile uint32_t xtimer_lock = 0;

static void _callback_unlock(void* arg)
{
    xtimer_lock = 0;
}

void _xtimer_tsleep(uint32_t offset, uint32_t long_offset)
{
    if (irq_is_in()) {
        assert(!long_offset);
        _xtimer_spin(offset);
        return;
    }

    xtimer_t timer;

    assert(xtimer_lock == 0);

    xtimer_lock = 1;

    timer.callback = _callback_unlock;
    timer.arg = NULL;
    timer.target = timer.long_target = 0;

    _xtimer_set64(&timer, offset, long_offset);
    while (xtimer_lock);
}
