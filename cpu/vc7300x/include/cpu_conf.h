#ifndef CPU_CONF_H
#define CPU_CONF_H

#include "cpu_conf_common.h"

#ifdef __cplusplus
extern "C" {
#endif

/* ARM Cortex-M specific CPU configuration */
#define CPU_DEFAULT_IRQ_PRIO        (1U)
#define CPU_IRQ_NUMOF               (32U)

/* NVIC use 8 priority levels */
#define __NVIC_PRIO_BITS            (3U)

typedef enum {
    NonMaskableInt_IRQn     = -14,
    HardFault_IRQn          = -13,
    SVCall_IRQn             = -5,
    PendSV_IRQn             = -2,
    SysTick_IRQn            = -1,
} IRQn_Type;

#include "core_cm3.h"

#ifdef __cplusplus
}
#endif

#endif /* CPU_CONF_H */
