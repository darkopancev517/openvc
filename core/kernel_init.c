#include <stdint.h>
#include <stdbool.h>
#include <errno.h>
#include <stdio.h>

#include "kernel_init.h"
#include "thread.h"
#include "irq.h"

#include "periph/pm.h"

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

kernel_pid_t centauri_thread_pid;
static char centauri_stack[THREAD_STACKSIZE_DEFAULT + THREAD_EXTRA_STACKSIZE_PRINTF];
extern void *centauri_thread(void *arg);

kernel_pid_t shell_thread_pid;
static char shell_stack[THREAD_STACKSIZE_DEFAULT + THREAD_EXTRA_STACKSIZE_PRINTF];
extern void *shell_thread(void *arg);

kernel_pid_t main_thread_pid;
static char main_stack[(THREAD_STACKSIZE_DEFAULT * 16) + THREAD_EXTRA_STACKSIZE_PRINTF];

kernel_pid_t idle_thread_pid;
static char idle_stack[THREAD_STACKSIZE_IDLE];

void kernel_init(void)
{
    (void) irq_disable();

    printf("\n\nkernel started (version: 0.0.1)\n\n");

    centauri_thread_pid = thread_create(centauri_stack, sizeof(centauri_stack),
                                        THREAD_PRIORITY_MAIN - 2,
                                        THREAD_CREATE_WOUT_YIELD | THREAD_CREATE_STACKTEST,
                                        centauri_thread, NULL, "centauri");

    shell_thread_pid = thread_create(shell_stack, sizeof(shell_stack),
                                     THREAD_PRIORITY_MAIN - 1,
                                     THREAD_CREATE_WOUT_YIELD | THREAD_CREATE_STACKTEST,
                                     shell_thread, NULL, "shell");

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
