#include "cpu.h"
#include "vcsoc.h"
#include "periph/misc.h"

void misc_enter_prog_mode(void)
{
    vcmisc_set_sys_core_clk(6225920);
    vcpmu_remap(PMU_REMAP_IROM);
}
