#include <stdio.h>
#include <assert.h>

#include "contiki.h"
#include "contiki-net.h"
#include "sys/platform.h"
#include "dev/serial-line.h"
#include "services/shell/shell.h"
#include "services/shell/serial-shell.h"

int main(void)
{
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

    printf("contiki-ng process started\n");

    while (1) {
        uint8_t p = 0;
        do {
            p = process_run();
            if (etimer_pending()) {
                etimer_request_poll();
            }
        } while (p > 0);
    }

    /* should not reach here */

    return 0;
}
