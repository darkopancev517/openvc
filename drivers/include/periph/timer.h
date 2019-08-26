#ifndef PERIPH_TIMER_H
#define PERIPH_TIMER_H

#include <stddef.h>
#include <stdint.h>
#include <limits.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef unsigned int tim_t;

#define TIMER_DEV(x) (x)

#define TIMER_UNDEF ((tim_t)(UINT_MAX))

typedef void (*timer_cb_t)(void *arg, int channel);

typedef struct {
    timer_cb_t cb;
    void *arg;
} timer_isr_ctx_t;

int timer_init(tim_t dev, unsigned long freq, timer_cb_t cb, void *arg);

int timer_set_absolute(tim_t dev, int channel, unsigned int value);

int timer_clear(tim_t dev, int channel);

uint32_t timer_read(tim_t dev);

void timer_start(tim_t dev);

void timer_stop(tim_t dev);

#ifdef __cplusplus
}
#endif

#endif /* PERIPH_TIMER_H */
