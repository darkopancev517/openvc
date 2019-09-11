#include <stdbool.h>
#include <stdio.h>

#include "irq.h"

#include "contiki.h"
#include "sys/int-master.h"

void int_master_enable(void)
{
    printf("contiki: int_master_enable\n");
    irq_enable();
}

int_master_status_t int_master_read_and_disable(void)
{
    printf("contiki: int_master_read_and_disable\n");
    return (int_master_status_t)irq_disable();
}

void int_master_status_set(int_master_status_t status)
{
    printf("contiki: int_master_status_set\n");
    irq_restore((uint32_t)status);
}

bool int_master_is_enable(void)
{
    printf("contiki: int_master_is_enable\n");
    return irq_is_enable() ? true : false;
}
