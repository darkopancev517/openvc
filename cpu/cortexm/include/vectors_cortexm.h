#ifndef VECTORS_CORTEXM_H
#define VECTORS_CORTEXM_H

#ifdef __cplusplus
extern "C" {
#endif

#include "cpu_conf.h"

/**
 * Use this macro to make interrupt functions overridable with the dummy_handler
 * as fallback in case they are not implemented
 */
#define WEAK_DEFAULT    __attribute__((weak,alias("dummy_handler")))

/**
 * Use this macro to define the parts of the vector table
 */
#define ISR_VECTOR(x)   __attribute__((used,section(".vectors." # x )))

/**
 * Number of Cortex-M non-ISR exceptions
 *
 * This means those that are no hardware interrupts, or the ones with a
 * negative interrupt number.
 */

#define CPU_NONISR_EXCEPTIONS   (15)

typedef void (*isr_t)(void);

/**
 * Structure of Cortex-M basic vector table
 */
typedef struct {
    void *_estack;                          /* exception stack pointer */
    isr_t vectors[CPU_NONISR_EXCEPTIONS];   /* shared Cortex-M vectors */
} cortexm_base_t;

/**
 * This function is the default entry point after a system reset
 *
 * After a system reset, the following steps are necessary and carried out:
 * 1. load data section from flash to ram
 * 2. overwrite uninitialized data section (BSS) with zeros
 * 3. initialize the board (sync clock, setup std-IO)
 * 4. initialize the newlib (optional, on when newlib is used)
 * 5. initialize and start kernel
 */
void reset_handler_default(void);

void nmi_default(void);

void hard_fault_default(void);

#if defined(CPU_ARCH_CORTEX_M3) || defined(CPU_ARCH_CORTEX_M4)
void mem_manage_default(void);

void bus_fault_default(void);

void usage_fault_default(void);

void debug_mon_default(void);
#endif

void dummy_handler_default(void);

#ifdef __cplusplus
}
#endif

#endif /* VECTORS_CORTEXM_H */
