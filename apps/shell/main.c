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

#include "shell.h"

static char shell_line_buf[SHELL_DEFAULT_BUFSIZE];

static void user_test(int argc, char **argv)
{
    (void) argc;
    (void) argv;

    printf("[user application test command]\n");
}

static const shell_command_t user_command_list[] = {
    { "test", "user test command", user_test },
    { NULL, NULL, NULL }
};

void *shell_thread(void *arg)
{
    (void) arg;

    shell_run(user_command_list, shell_line_buf, sizeof(shell_line_buf));

    /* should not reach here */

    return NULL;
}

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
        } while (p > 0);
#endif
    }

    /* should not reach here */

    return 0;
}
