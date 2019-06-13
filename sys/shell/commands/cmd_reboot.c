#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>

#include "cpu.h"
#include "periph/misc.h"

void cmd_reboot_handler(int argc, char **argv)
{
    if (argc == 1) {
        NVIC_SystemReset();
    } else if (argc == 2) {
        int reboot_arg = (int)atoi(argv[1]);
        if (reboot_arg == 0) {
            misc_enter_prog_mode();
        }
    } else {
        printf("invalid reboot command\n");
    }
}

void cmd_rb0_handler(int argc, char **argv)
{
    if (argc == 1) {
        misc_enter_prog_mode();
    } else {
        printf("invalid rb0 command\n");
    }
}
