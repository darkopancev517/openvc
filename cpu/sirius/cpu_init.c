#include "cpu.h"
#include "vcsoc.h"
#include "xtimer.h"

void cpu_init(void)
{
    /* initialize the Cortex-M core */
    cortexm_init();

    /* initialize vc7300x periph */
    vcmisc_config_ahb_source(CLK_SOURCE_HRCO);
    vcmisc_set_sys_core_clk(39321600); // 39.3216 MHz

    vcmisc_config_ahb_div(1);
    vcmisc_config_apb_div(2);

    /* wait until clock is stable */
    uint32_t timeout = 0x10000;
    uint32_t counter = 0;

    while (!vcana_auto_calib_lock()) {
        counter++;
        if (counter >= timeout) {
            break;
        }
    }

    vcana_config_lfxo_capsel(4);
    vcana_config_vdd3_fon(1);
    vcana_config_lpldo_vsel(2);
    vcmisc_config_pwrup_delay(0x3f);

    /* disable watchdog timer */
    vcwdt_disable();
}
