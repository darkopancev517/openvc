#include "cpu.h"
#include "periph/pm.h"

void pm_reboot(void)
{
    NVIC_SystemReset();
}

void pm_set_lowest(void)
{
    cortexm_sleep(0);
}
