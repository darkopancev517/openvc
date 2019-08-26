#ifndef THREAD_H
#define THREAD_H

#include "clist.h"
#include "cib.h"
#include "msg.h"
#include "cpu_conf.h"
#include "sched.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef void *(*thread_task_func_t)(void *arg);

struct _thread {
    char *sp;
    thread_status_t status;
    uint8_t priority;
    kernel_pid_t pid;
    clist_node_t rq_entry;
#if defined(MODULE_CORE_MSG)
    void *wait_data;
#endif
#if defined (MODULE_CORE_MSG)
    list_node_t msg_waiters;
    cib_t msg_queue;
    msg_t *msg_array;
#endif
    char *stack_start;
    const char *name;
    int stack_size;
};

#ifndef THREAD_STACKSIZE_DEFAULT
#error THREAD_STACKSIZE_DEFAULT must be defined per CPU
#endif

#ifndef THREAD_STACKSIZE_IDLE
#error THREAD_STACKSIZE_IDLE must be defined per CPU
#endif

#ifndef THREAD_EXTRA_STACKSIZE_PRINTF
#error THREAD_EXTRA_STACKSIZE_PRINTF must be defined per CPU
#endif

#ifndef THREAD_STACKSIZE_MAIN
#define THREAD_STACKSIZE_MAIN (THREAD_STACKSIZE_DEFAULT + THREAD_EXTRA_STACKSIZE_PRINTF)
#endif

#ifndef THREAD_STACKSIZE_LARGE
#define THREAD_STACKSIZE_LARGE (THREAD_STACKSIZE_MEDIUM * 2)
#endif

#ifndef THREAD_STACKSIZE_MEDIUM
#define THREAD_STACKSIZE_MEDIUM THREAD_STACKSIZE_DEFAULT
#endif

#ifndef THREAD_STACKSIZE_SMALL
#define THREAD_STACKSIZE_SMALL (THREAD_STACKSIZE_MEDIUM / 2)
#endif

#ifndef THREAD_STACKSIZE_TINY
#define THREAD_STACKSIZE_TINY (THREAD_STACKSIZE_MEDIUM / 4)
#endif

#ifndef THREAD_STACKSIZE_MINIMUM
#define THREAD_STACKSIZE_MINIMUM (sizeof(thread_t))
#endif

#define THREAD_PRIORITY_MIN (SCHED_PRIO_LEVELS - 1)
#define THREAD_PRIORITY_IDLE (THREAD_PRIORITY_MIN)

#ifndef THREAD_PRIORITY_MAIN
#define THREAD_PRIORITY_MAIN (THREAD_PRIORITY_MIN - (SCHED_PRIO_LEVELS / 2))
#endif

/**
 * Optional flags for controlling a threads initial state.
 */

/**
 * Set the new thread to sleeping. It must be woken up manually.
 */
#define THREAD_CREATE_SLEEPING          (1)

/**
 * Currently not implemented.
 */
#define THREAD_AUTO_FREE                (2)

/**
 * Do not automatically call thread_yield() after creation: the newly
 * created thread might not run immediately. Purely for optimization.
 * Any other context switch (i.e. an interrupt) can still start the
 * thread at any time!
 */
#define THREAD_CREATE_WOUT_YIELD        (4)

/**
 * Write markers into the thread's stack to measure stack usage (for
 * debugging and profiling purposes)
 */
#define THREAD_CREATE_STACKTEST         (8)

/**
 * Measures the stack usage of a stack.
 */
uintptr_t thread_measure_stack_free(char *stack);

/**
 * Creates a new thread.
 */
kernel_pid_t thread_create(char *stack,
                           int stacksize,
                           char priority,
                           int flags,
                           thread_task_func_t task_func,
                           void *arg,
                           const char *name);

/**
 * Retreive a thread control block by PID.
 */
volatile thread_t *thread_get(kernel_pid_t pid);

/**
 * Returns the status of a process.
 */
int thread_getstatus(kernel_pid_t pid);

/**
 * Puts the current thread into sleep mode. Has to be woken up externally.
 */
void thread_sleep(void);

/**
 * Lets current thread yield.
 */
void thread_yield(void);

/**
 * Lets current thread yield in favor of a higher prioritized thread.
 */
void thread_yield_higher(void);

/**
 * Wakes up a sleeping thread.
 */
int thread_wakeup(kernel_pid_t pid);

/**
 * Returns the process ID of the currently running thread.
 */
static inline kernel_pid_t thread_getpid(void)
{
    extern volatile kernel_pid_t sched_active_pid;
    return sched_active_pid;
}


/**
 * Gets called upon thread creation to set CPU registers.
 */
char *thread_stack_init(thread_task_func_t task_func, void *arg, void *stack_start, int stack_size);

/**
 * Add thread to list, sorted by priority (internal).
 */
void thread_add_to_list(list_node_t *list, thread_t *thread);

/**
 * Returns the name of a process.
 */
const char *thread_getname(kernel_pid_t pid);

/**
 * Get the number of bytes used on the ISR stack.
 */
int thread_isr_stack_usage(void);

/**
 * Get the current ISR stack pointer.
 */
void *thread_isr_stack_pointer(void);

/**
 * Get the start of the ISR stack.
 */
void *thread_isr_stack_start(void);

/**
 * Print the current stack to stdout.
 */
void thread_stack_print(void);

/**
 * Prints human readable, ps-like thread information for debugging purposes
 */
void thread_print_stack(void);

static inline int thread_has_msg_queue(const volatile struct _thread *thread)
{
#if defined(MODULE_CORE_MSG)
    return (thread->msg_array != NULL);
#else
    (void) thread;
    return 0;
#endif
}

#ifdef __cplusplus
}
#endif

#endif /* THREAD_H */
