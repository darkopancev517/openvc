#include "ps.h"

#ifdef MODULE_PS
void cmd_ps_handler(int argc, char **argv)
{
    (void) argc;
    (void) argv;

    ps();
}
#endif
