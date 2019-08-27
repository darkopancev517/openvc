#include <stdint.h>

#include "irq.h"
#include "cpu.h"

unsigned int irq_disable(void)
{
    uint32_t mask = __get_PRIMASK();
    __disable_irq();
    return mask;
}

__attribute__((used)) unsigned int irq_enable(void)
{
    __enable_irq();
    return __get_PRIMASK();
}

void irq_restore(unsigned int state)
{
    __set_PRIMASK(state);
}

/**
 * See if the current context is inside an ISR
 */
int irq_is_in(void)
{
    return (__get_IPSR() & 0xFF);
}

int irq_is_enable(void)
{
    return __get_PRIMASK() ? 1 : 0;
}
