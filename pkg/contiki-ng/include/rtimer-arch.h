#ifndef RTIMER_ARCH_H
#define RTIMER_ARCH_H

#include "contiki.h"

#ifdef __cplusplus
extern "C" {
#endif

rtimer_clock_t rtimer_arch_now(void);

#ifdef __cplusplus
}
#endif

#endif // RTIMER_ARCH_H
