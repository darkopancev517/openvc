#include <stdio.h>

#include "thread.h"
#include "sched.h"
#include "thread.h"
#include "kernel_types.h"

/* list of states */
static const char *state_names[] = {
    [STATUS_RUNNING] = "running",
    [STATUS_PENDING] = "pending",
    [STATUS_STOPPED] = "stopped",
    [STATUS_SLEEPING] = "sleeping",
    [STATUS_MUTEX_BLOCKED] = "bl mutex",
    [STATUS_RECEIVE_BLOCKED] = "bl rx",
    [STATUS_SEND_BLOCKED] = "bl send",
    [STATUS_REPLY_BLOCKED] = "bl reply",
    [STATUS_FLAG_BLOCKED_ANY] = "bl anyfl",
    [STATUS_FLAG_BLOCKED_ALL] = "bl allfl",
    [STATUS_MBOX_BLOCKED] = "bl mbox",
    [STATUS_COND_BLOCKED] = "bl cond",
};

/**
 * @brief Prints a list of running threads including stack usage to stdout.
 */
void ps(void)
{
    const char queued_name[] = {'_', 'Q'};
    int overall_stacksz = 0, overall_used = 0;

    printf("\tpid | "
            "%-21s| "
            "%-9sQ | pri "
           "| stack  ( used) | base addr  | current     "
#ifdef MODULE_SCHEDSTATISTICS
           "| runtime  | switches"
#endif
           "\n",
           "name",
           "state");

    int isr_usage = thread_isr_stack_usage();
    void *isr_start = thread_isr_stack_start();
    void *isr_sp = thread_isr_stack_pointer();
    printf("\t  - | isr_stack            | -        - |"
           "   - | %6i (%5i) | %10p | %10p\n", ISR_STACKSIZE, isr_usage, isr_start, isr_sp);
    overall_stacksz += ISR_STACKSIZE;
    if (isr_usage > 0) {
        overall_used += isr_usage;
    }

#ifdef MODULE_SCHEDSTATISTICS
    uint64_t rt_sum = 0;
    for (kernel_pid_t i = KERNEL_PID_FIRST; i <= KERNEL_PID_LAST; i++) {
        thread_t *p = (thread_t *)sched_threads[i];
        if (p != NULL) {
            rt_sum += sched_pidlist[i].runtime_ticks;
        }
    }
#endif /* MODULE_SCHEDSTATISTICS */

    for (kernel_pid_t i = KERNEL_PID_FIRST; i <= KERNEL_PID_LAST; i++) {
        thread_t *p = (thread_t *)sched_threads[i];

        if (p != NULL) {
            thread_status_t state = p->status;                                     /* copy state */
            const char *sname = state_names[state];                                /* get state name */
            const char *queued = &queued_name[(int)(state >= STATUS_ON_RUNQUEUE)]; /* get queued flag */
            int stacksz = p->stack_size;                                           /* get stack size */
            overall_stacksz += stacksz;
            stacksz -= thread_measure_stack_free(p->stack_start);
            overall_used += stacksz;
#ifdef MODULE_SCHEDSTATISTICS
            /* multiply with 100 for percentage and to avoid floats/doubles */
            uint64_t runtime_ticks = sched_pidlist[i].runtime_ticks * 100;
            unsigned runtime_major = runtime_ticks / rt_sum;
            unsigned runtime_minor = ((runtime_ticks % rt_sum) * 1000) / rt_sum;
            unsigned switches = sched_pidlist[i].schedules;
#endif
            printf("\t%3" PRIkernel_pid
                   " | %-20s"
                   " | %-8s %.1s | %3i"
                   " | %6i (%5i) | %10p | %10p "
#ifdef MODULE_SCHEDSTATISTICS
                   " | %2d.%03d%% |  %8u"
#endif
                   "\n",
                   p->pid,
                   p->name,
                   sname, queued, p->priority
                   , p->stack_size, stacksz, (void *)p->stack_start, (void *)p->sp
#ifdef MODULE_SCHEDSTATISTICS
                   , runtime_major, runtime_minor, switches
#endif
                  );
        }
    }

    printf("\t%5s %-21s|%13s%6s %6i (%5i)\n", "|", "SUM", "|", "|",
           overall_stacksz, overall_used);
}
