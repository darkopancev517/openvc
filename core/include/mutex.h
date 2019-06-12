#ifndef MUTEX_H
#define MUTEX_H

#include <stddef.h>

#include "list.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct {
    list_node_t queue;
} mutex_t;

#define MUTEX_INIT { { NULL } }

#define MUTEX_LOCKED ((list_node_t *)-1)

#define MUTEX_INIT_LOCKED { { MUTEX_LOCKED } }

static inline void mutex_init(mutex_t *mutex)
{
    mutex->queue.next = NULL;
}

int _mutex_lock(mutex_t *mutex, int blocking);

static inline int mutex_trylock(mutex_t *mutex)
{
    return _mutex_lock(mutex, 0);
}

static inline void mutex_lock(mutex_t *mutex)
{
    _mutex_lock(mutex, 1);
}

void mutex_unlock(mutex_t *mutex);

void mutex_unlock_and_sleep(mutex_t *mutex);

#ifdef __cplusplus
}
#endif

#endif /* MUTEX_H */
