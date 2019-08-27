#include <stdint.h>
#include <stdbool.h>
#include <errno.h>
#include <stdio.h>

#include "kernel_init.h"
#include "thread.h"
#include "irq.h"

#include "periph/pm.h"

extern int main(void);

static void *main_thread(void *arg)
{
    (void) arg;

    printf("\n\nkernel started (version: 0.0.1)\n\n");

    main();
    return NULL;
}

static void *idle_thread(void *arg)
{
    (void) arg;

    while (1) {
        pm_set_lowest();
    }

    return NULL;
}

kernel_pid_t centauri_thread_pid;
static char centauri_stack[THREAD_STACKSIZE_DEFAULT];
extern void *centauri_thread(void *arg);

kernel_pid_t main_thread_pid;
static char main_stack[THREAD_STACKSIZE_MAIN];

kernel_pid_t idle_thread_pid;
static char idle_stack[THREAD_STACKSIZE_IDLE];

void kernel_init(void)
{
    (void) irq_disable();

    centauri_thread_pid = thread_create(centauri_stack, sizeof(centauri_stack),
                                        THREAD_PRIORITY_MAIN - 1,
                                        THREAD_CREATE_WOUT_YIELD | THREAD_CREATE_STACKTEST,
                                        centauri_thread, NULL, "centauri");

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
