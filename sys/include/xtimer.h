#ifndef XTIMER_H
#define XTIMER_H

#include <stdint.h>

#include "board.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct {
    uint32_t ticks32;
} xtimer_ticks32_t;

void xtimer_init(void);

xtimer_ticks32_t xtimer_now(void);

void xtimer_msleep(uint32_t milliseconds);

#ifdef __cplusplus
}
#endif

#endif /* XTIMER_H */
