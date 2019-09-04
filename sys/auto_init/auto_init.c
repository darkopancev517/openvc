#include "auto_init.h"
#include "thread.h"

#ifdef MODULE_XTIMER
#include "xtimer.h"
#endif

#ifdef MODULE_SHELL
#include "shell.h"
#endif

#ifdef MODULE_DRIVERS_CENTAURI
#include "centauri.h"
#endif

#ifdef MODULE_SHELL
kernel_pid_t shell_thread_pid;
static char shell_stack[THREAD_STACKSIZE_DEFAULT + THREAD_EXTRA_STACKSIZE_PRINTF];
extern void *shell_thread(void *arg);
#endif

#ifdef MODULE_DRIVERS_CENTAURI
kernel_pid_t centauri_thread_pid;
static char centauri_stack[THREAD_STACKSIZE_DEFAULT + THREAD_EXTRA_STACKSIZE_PRINTF];
extern void *centauri_thread(void *arg);
#endif

void auto_init(void)
{
#ifdef MODULE_XTIMER
    xtimer_init();
#endif
#ifdef MODULE_DRIVERS_CENTAURI
    centauri_thread_pid = thread_create(centauri_stack, sizeof(centauri_stack),
                                        THREAD_PRIORITY_MAIN - 2,
                                        THREAD_CREATE_WOUT_YIELD | THREAD_CREATE_STACKTEST,
                                        centauri_thread, NULL, "centauri");
#endif
#ifdef MODULE_SHELL
    shell_thread_pid = thread_create(shell_stack, sizeof(shell_stack),
                                     THREAD_PRIORITY_MAIN - 1,
                                     THREAD_CREATE_WOUT_YIELD | THREAD_CREATE_STACKTEST,
                                     shell_thread, NULL, "shell");
#endif
}
