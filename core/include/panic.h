#ifndef PANIC_H
#define PANIC_H

#include "kernel_defines.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef enum {
    PANIC_GENERAL_ERROR,
    PANIC_SOFT_REBOOT,
    PANIC_HARD_REBOOT,
    PANIC_ASSERT_FAIL,
    PANIC_NMI_HANDLER,
    PANIC_HARD_FAULT,
#if defined(CPU_ARCH_CORTEX_M3) || defined(CPU_ARCH_CORTEX_M4)
    PANIC_MEM_MANAGE,
    PANIC_BUS_FAULT,
    PANIC_USAGE_FAULT,
    PANIC_DEBUG_MON,
#endif
    PANIC_DUMMY_HANDLER,
    PANIC_SSP,              /* stack smashing protector failure */
    PANIC_UNDEFINED
} core_panic_t;

NORETURN void core_panic(core_panic_t crash_code, const char *message);

void panic_arch(void);

#ifdef __cplusplus
}
#endif

#endif /* PANIC_H */
