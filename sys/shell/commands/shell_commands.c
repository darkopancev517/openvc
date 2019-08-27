#include <stdlib.h>

#include "shell_commands.h"

extern void cmd_reboot_handler(int argc, char **argv);
extern void cmd_rb0_handler(int argc, char **argv);
extern void cmd_dw_handler(int argc, char **argv);
extern void cmd_ww_handler(int argc, char **argv);
#ifdef MODULE_PS
extern void cmd_ps_handler(int argc, char **argv);
#endif
extern void cmd_cent_handler(int argc, char **argv);

const shell_command_t _shell_command_list[] = {
    { "reboot", "reboot the mcu.", cmd_reboot_handler },
    { "rb0", "run rom-code (programming mode).", cmd_rb0_handler },
    { "dw", "memory word dump.", cmd_dw_handler },
    { "ww", "memory word write.", cmd_ww_handler },
#ifdef MODULE_PS
    { "ps", "print information about running threads.", cmd_ps_handler },
#endif
    {"cent", "centauri commands", cmd_cent_handler},
    { NULL, NULL, NULL }
};
