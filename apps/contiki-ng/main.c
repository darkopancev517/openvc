#include <stdio.h>
#include <assert.h>

#ifdef MODULE_PKG_CONTIKI_NG
#include "contiki.h"
#include "contiki-net.h"
#include "sys/platform.h"
#include "dev/serial-line.h"
#include "services/shell/shell.h"
#include "services/shell/serial-shell.h"
#endif

int main(void)
{
#ifdef MODULE_PKG_CONTIKI_NG
    platform_init_stage_one();

    clock_init();
    rtimer_init();
    process_init();
    process_start(&etimer_process, NULL);
    ctimer_init();

    platform_init_stage_two();

    platform_init_stage_three();

    serial_line_init();
    serial_shell_init();
    shell_init();

    autostart_start(autostart_processes);
#endif

    while (1) {
#ifdef MODULE_PKG_CONTIKI_NG
        uint8_t p = 0;
        do {
            p = process_run();
            if (etimer_pending()) {
                etimer_request_poll();
            }
        } while (p > 0);
#endif
    }

    /* should not reach here */

    return 0;
}
