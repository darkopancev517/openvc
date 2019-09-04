#include <stdint.h>
#include <stdbool.h>
#include <errno.h>
#include <stdio.h>

#include "kernel_init.h"
#include "thread.h"
#include "irq.h"

#ifdef MODULE_AUTO_INIT
#include "auto_init.h"
#endif

#include "periph/pm.h"

kernel_pid_t main_thread_pid;
static char main_stack[(THREAD_STACKSIZE_DEFAULT * 16) + THREAD_EXTRA_STACKSIZE_PRINTF];

kernel_pid_t idle_thread_pid;
static char idle_stack[THREAD_STACKSIZE_IDLE];

extern int main(void);

void *main_thread(void *arg)
{
    (void) arg;

    main();
    return NULL;
}

void *idle_thread(void *arg)
{
    (void) arg;

    while (1) {
        pm_set_lowest();
    }

    return NULL;
}

void kernel_init(void)
{
    (void) irq_disable();

    printf("\n\nkernel started (version: 0.0.1)\n\n");

#ifdef MODULE_AUTO_INIT
    auto_init();
#endif

    main_thread_pid = thread_create(main_stack, sizeof(main_stack),
                                    THREAD_PRIORITY_MAIN,
                                    THREAD_CREATE_WOUT_YIELD | THREAD_CREATE_STACKTEST,
                                    main_thread, NULL, "main");

    idle_thread_pid = thread_create(idle_stack, sizeof(idle_stack),
                                    THREAD_PRIORITY_IDLE,
                                    THREAD_CREATE_WOUT_YIELD | THREAD_CREATE_STACKTEST,
                                    idle_thread, NULL, "idle");

    cpu_switch_context_exit();
}
