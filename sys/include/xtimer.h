#ifndef XTIMER_H
#define XTIMER_H

#include <stdint.h>
#include "timex.h"
#include "msg.h"
#include "mutex.h"

#include "board.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct {
    uint64_t ticks64;
} xtimer_ticks64_t;

typedef struct {
    uint32_t ticks32;
} xtimer_ticks32_t;

typedef void (*xtimer_callback_t)(void*);

typedef struct xtimer {
    struct xtimer *next;
    uint32_t target;
    uint32_t long_target;
    xtimer_callback_t callback;
    void *arg;
} xtimer_t;

static inline xtimer_ticks32_t xtimer_now(void);

static inline xtimer_ticks64_t xtimer_now64(void);

void xtimer_now_timex(timex_t *out);

static inline uint32_t xtimer_now_usec(void);

static inline uint64_t xtimer_now_usec64(void);

void xtimer_init(void);

static inline void xtimer_sleep(uint32_t seconds);

static inline void xtimer_usleep(uint32_t microseconds);

static inline void xtimer_msleep(uint32_t milliseconds)
{
    xtimer_usleep(milliseconds * US_PER_MS);
}

static inline void xtimer_nanosleep(uint32_t nanoseconds);

static inline void xtimer_tsleep32(xtimer_ticks32_t ticks);

static inline void xtimer_tsleep64(xtimer_ticks64_t ticks);

static inline void xtimer_spin(xtimer_ticks32_t ticks);

static inline void xtimer_periodic_wakeup(xtimer_ticks32_t *last_wakeup, uint32_t period);

static inline void xtimer_set_msg(xtimer_t *timer, uint32_t offset, msg_t *msg, kernel_pid_t target_pid);

static inline void xtimer_set_msg64(xtimer_t *timer, uint64_t offset, msg_t *msg, kernel_pid_t target_pid);

static inline void xtimer_set_wakeup(xtimer_t *timer, uint32_t offset, kernel_pid_t pid);

static inline void xtimer_set_wakeup64(xtimer_t *timer, uint64_t offset, kernel_pid_t pid);

static inline void xtimer_set(xtimer_t *timer, uint32_t offset);

static inline void xtimer_set64(xtimer_t *timer, uint64_t offset_us);

void xtimer_remove(xtimer_t *timer);

static inline int xtimer_msg_receive_timeout(msg_t *msg, uint32_t timeout);

static inline int xtimer_msg_receive_timeout64(msg_t *msg, uint64_t timeout);

static inline xtimer_ticks32_t xtimer_ticks_from_usec(uint32_t usec);

static inline xtimer_ticks64_t xtimer_ticks_from_usec64(uint64_t usec);

static inline uint32_t xtimer_usec_from_ticks(xtimer_ticks32_t ticks);

static inline uint64_t xtimer_usec_from_ticks64(xtimer_ticks64_t ticks);

static inline xtimer_ticks32_t xtimer_ticks(uint32_t ticks);

static inline xtimer_ticks64_t xtimer_ticks64(uint64_t ticks);

static inline xtimer_ticks32_t xtimer_diff(xtimer_ticks32_t a, xtimer_ticks32_t b);

static inline xtimer_ticks64_t xtimer_diff64(xtimer_ticks64_t a, xtimer_ticks64_t b);

static inline xtimer_ticks32_t xtimer_diff32_64(xtimer_ticks64_t a, xtimer_ticks64_t b);

static inline bool xtimer_less(xtimer_ticks32_t a, xtimer_ticks32_t b);

static inline bool xtimer_less64(xtimer_ticks64_t a, xtimer_ticks64_t b);

int xtimer_mutex_lock_timeout(mutex_t *mutex, uint64_t us);

void xtimer_set_timeout_flag(xtimer_t *t, uint32_t timeout);

/**
 * xtimer backoff value
 *
 * All timers that are less than XTIMER_BACKOFF microseconds in the future will
 * just spin.
 */
#ifndef XTIMER_BACKOFF
#define XTIMER_BACKOFF 30
#endif

/**
 * xtimer overhead value, in hardware ticks
 *
 * This value specifies the time a timer will be late if uncorrected, e.g.,
 * the system-specific xtimer execution time from timer ISR to executing
 * a timer's callback's first instruction.
 *
 * E.g., with XTIMER_OVERHEAD == 0
 * start=xtimer_now();
 * xtimer_set(&timer, X);
 * (in callback:)
 * overhead=xtimer_now()-start-X;
 *
 * xtimer automatically substracts XTIMER_OVERHEAD from a timer's target time,
 * but when the timer triggers, xtimer will spin-lock until a timer's target
 * time is reached, so timers will never trigger early.
 */
#ifndef XTIMER_OVERHEAD
#define XTIMER_OVERHEAD 20
#endif

/**
 * xtimer IRQ backoff time, in hardware ticks
 *
 * When scheduling the next IRQ, if it is less than the backoff time
 * in the future, just spin.
 */
#ifndef XTIMER_ISR_BACKOFF
#define XTIMER_ISR_BACKOFF 20
#endif

/**
 * xtimer_periodic_wakeup spin cutoff
 *
 * If the difference between target time and now is less than this value, then
 * xtimer_periodic_wakeup will use xtimer_spin instead of setting a timer.
 */
#ifndef XTIMER_PERIODIC_SPIN
#define XTIMER_PERIODIC_SPIN (XTIMER_BACKOFF * 2)
#endif

/**
 * xtimer_periodic_wakeup relative target cutoff
 *
 * If the difference between target time and now is less than this value, then
 * xtimer_periodic_wakeup will set a relative target time in the future instead
 * of the true target.
 *
 * This is done to prevent target time underflows.
 */
#ifndef XTIMER_PERIODIC_RELATIVE
#define XTIMER_PERIODIC_RELATIVE (512)
#endif

#ifndef XTIMER_DEV
#define XTIMER_DEV TIMER_DEV(0)
#define XTIMER_CHAN (0)
#if (TIMER_0_MAX_VALUE) == 0xfffffful
#define XTIMER_WIDTH (24)
#elif (TIMER_0_MAX_VALUE) == 0xffff
#define XTIMER_WIDTH (16)
#endif
#endif

#ifndef XTIMER_WIDTH
#define XTIMER_WIDTH (32)
#endif

#if (XTIMER_WIDTH != 32)
#define XTIMER_MASK ((0xffffffff >> XTIMER_WIDTH) << XTIMER_WIDTH)
#else
#define XTIMER_MASK (0)
#endif

#define XTIMER_HZ_BASE (1000000ul)

#ifndef XTIMER_HZ
#define XTIMER_HZ XTIMER_HZ_BASE
#endif

#ifndef XTIMER_SHIFT
#if (XTIMER_HZ == 32768ul)
#define XTIMER_SHIFT (0)
#elif (XTIMER_HZ == XTIMER_HZ_BASE)
#define XTIMER_SHIFT (0)
#elif (XTIMER_HZ >> 1 == XTIMER_HZ_BASE) || (XTIMER_HZ << 1 == XTIMER_HZ_BASE)
#define XTIMER_SHIFT (1)
#elif (XTIMER_HZ >> 2 == XTIMER_HZ_BASE) || (XTIMER_HZ << 2 == XTIMER_HZ_BASE)
#define XTIMER_SHIFT (2)
#elif (XTIMER_HZ >> 3 == XTIMER_HZ_BASE) || (XTIMER_HZ << 3 == XTIMER_HZ_BASE)
#define XTIMER_SHIFT (3)
#elif (XTIMER_HZ >> 4 == XTIMER_HZ_BASE) || (XTIMER_HZ << 4 == XTIMER_HZ_BASE)
#define XTIMER_SHIFT (4)
#elif (XTIMER_HZ >> 5 == XTIMER_HZ_BASE) || (XTIMER_HZ << 5 == XTIMER_HZ_BASE)
#define XTIMER_SHIFT (5)
#elif (XTIMER_HZ >> 6 == XTIMER_HZ_BASE) || (XTIMER_HZ << 6 == XTIMER_HZ_BASE)
#define XTIMER_SHIFT (6)
#else
#error "XTIMER_SHIFT cannot be derived for given XTIMER_HZ, verify settings!"
#endif
#else
#error "XTIMER_SHIFT is set relative to XTIMER_HZ, no manual define required!"
#endif

#include "xtimer/tick_conversion.h"
#include "xtimer/implementation.h"

#ifdef __cplusplus
}
#endif

#endif /* XTIMER_H */
