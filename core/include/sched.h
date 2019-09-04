#ifndef SCHED_H
#define SCHED_H

#include <stddef.h>

#include "kernel_defines.h"
#include "bitarithm.h"
#include "kernel_types.h"
#include "clist.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Forward declaration for thread_t, defined in thread.h
 */
typedef struct _thread thread_t;

typedef enum {
    STATUS_STOPPED,                 /* has terminated                       */
    STATUS_SLEEPING,                /* sleeping                             */
    STATUS_MUTEX_BLOCKED,           /* waiting for a locked mutex           */
    STATUS_RECEIVE_BLOCKED,         /* waiting for a message                */
    STATUS_SEND_BLOCKED,            /* waiting for message to be delivered  */
    STATUS_REPLY_BLOCKED,           /* waiting for a message response       */
    STATUS_FLAG_BLOCKED_ANY,        /* waiting for any flag from flag_mask  */
    STATUS_FLAG_BLOCKED_ALL,        /* waiting for all flags in flag_mask   */
    STATUS_MBOX_BLOCKED,            /* waiting for get/put on mbox          */
    STATUS_COND_BLOCKED,            /* waiting for a condition variable     */
    STATUS_RUNNING,                 /* currently running                    */
    STATUS_PENDING,                 /* waiting to be scheduled to run       */
    STATUS_NUMOF                    /* number of supported thread states    */
} thread_status_t;

#define STATUS_ON_RUNQUEUE STATUS_RUNNING

#define STATUS_NOT_FOUND ((thread_status_t)-1)

/**
 * The number of thread priority levels
 */
#ifndef SCHED_PRIO_LEVELS
#define SCHED_PRIO_LEVELS 16
#endif

int sched_run(void);

void sched_set_status(thread_t *process, thread_status_t status);

void sched_switch(uint16_t other_prio);

NORETURN void cpu_switch_context_exit(void);

extern volatile unsigned int sched_context_switch_request;

extern volatile thread_t *sched_threads[KERNEL_PID_LAST + 1];

extern volatile thread_t *sched_active_thread;

extern volatile int sched_num_threads;

extern volatile kernel_pid_t sched_active_pid;

extern clist_node_t sched_runqueues[SCHED_PRIO_LEVELS];

NORETURN void sched_task_exit(void);

#ifdef MODULE_SCHEDSTATISTICS
typedef struct {
    uint32_t laststart;
    unsigned int schedules;
    uint64_t runtime_ticks;
} schedstat_t;

extern schedstat_t sched_pidlist[KERNEL_PID_LAST + 1];

void sched_register_cb(void (*callback)(uint32_t, uint32_t));
#endif /* MODULE_SCHEDSTATISTICS */

#ifdef __cplusplus
}
#endif

#endif /* SCHED_H */
