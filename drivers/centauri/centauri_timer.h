#ifndef CENTAURI_TIMER_H
#define CENTAURI_TIMER_H

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

void cent_busy_wait(uint32_t us);

uint32_t cent_usec_now(void);

#ifdef __cplusplus
}
#endif

#endif /* CENTAURI_TIMER_H */
