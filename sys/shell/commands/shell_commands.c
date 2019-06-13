#include <stdlib.h>

#include "shell_commands.h"

extern void cmd_reboot_handler(int argc, char **argv);
extern void cmd_rb0_handler(int argc, char **argv);

extern void cmd_dw_handler(int argc, char **argv);
extern void cmd_ww_handler(int argc, char **argv);

const shell_command_t _shell_command_list[] = {
    { "reboot", "reboot the mcu", cmd_reboot_handler },
    { "rb0", "enter rom prog-mode", cmd_rb0_handler },
    { "dw", "memory word dump", cmd_dw_handler },
    { "ww", "memory word write", cmd_ww_handler },
    { NULL, NULL, NULL }
};
