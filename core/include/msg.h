#ifndef MSG_H
#define MSG_H

#include <stdint.h>
#include <stdbool.h>
#include "kernel_types.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct {
    kernel_pid_t sender_pid;
    uint16_t type;
    union {
        void *ptr;
        uint32_t value;
    } content;
} msg_t;

int msg_send(msg_t *m, kernel_pid_t target_pid);

int msg_try_send(msg_t *m, kernel_pid_t target_pid);

int msg_send_to_self(msg_t *m);

#define KERNEL_PID_ISR (KERNEL_PID_LAST + 1)

int msg_send_int(msg_t *m, kernel_pid_t target_pid);

static inline int msg_sent_by_int(const msg_t *m)
{
    return (m->sender_pid == KERNEL_PID_ISR);
}

int msg_receive(msg_t *m);

int msg_try_receive(msg_t *m);

int msg_send_receive(msg_t *m, msg_t *reply, kernel_pid_t target_pid);

int msg_reply(msg_t *m, msg_t *reply);

int msg_reply_int(msg_t *m, msg_t *reply);

int msg_avail(void);

void msg_init_queue(msg_t *array, int num);

void msg_queue_print(void);

#ifdef __cplusplus
}
#endif

#endif /* MSG_H */
