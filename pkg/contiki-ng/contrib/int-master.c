#include <stdbool.h>

#include "irq.h"

#include "contiki.h"
#include "sys/int-master.h"

void int_master_enable(void)
{
    irq_disable();
}

int_master_status_t int_master_read_and_disable(void)
{
    return (int_master_status_t)irq_disable();
}

void int_master_status_set(int_master_status_t status)
{
    irq_restore((uint32_t)status);
}

bool int_master_is_enable(void)
{
    return irq_is_enable() ? true : false;
}
