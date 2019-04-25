#ifndef CPU_H
#define CPU_H

#include <stdio.h>

#include "irq.h"
#include "sched.h"
#include "thread.h"
#include "cpu_conf.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Interrupt stack canary value 0xe7fe is the ARM Thumb machine code equivalent
 * of asm("bl #-2\n") or 'while (1);', i.e. an infinite loop
 */
#define STACK_CANARY_WORD   (0xE7FEE7FEu)

/**
 * All Cortex-m-based CPUs provide pm_set_lowest
 */
#define PROVIDE_PM_SET_LOWEST

void cpu_init(void);

void cortexm_init(void);

static inline void cpu_print_last_instruction(void)
{
    uint32_t *lr_ptr;
    __asm__ __volatile__("mov %0, lr" : "=r"(lr_ptr));
    printf("%p\n", (void*) lr_ptr);
}

static inline void cortexm_sleep_until_event(void)
{
    __WFE();
}

static inline void cortexm_sleep(int deep)
{
    if (deep) {
        SCB->SCR |=  (SCB_SCR_SLEEPDEEP_Msk);
    } else {
        SCB->SCR &= ~(SCB_SCR_SLEEPDEEP_Msk);
    }

    /* ensure that all memory accesses have completed and trigger sleeping */
    unsigned state = irq_disable();
    __DSB();
    __WFI();
    irq_restore(state);
}

/**
 * Trigger a conditional context scheduler run / context switch
 */
static inline void cortexm_isr_end(void)
{
    if (sched_context_switch_request) {
        thread_yield_higher();
    }
}

static inline void cpu_jump_to_image(uint32_t image_address)
{
    /* Disable IRQ */
    __disable_irq();

    /* set MSP */
    __set_MSP(*(uint32_t*)image_address);

    /* skip stack pointer */
    image_address += 4;

    /* load the images reset_vector address */
    uint32_t destination_address = *(uint32_t*)image_address;

    /* Make sure the Thumb State bit is set. */
    destination_address |= 0x1;

    /* Branch execution */
    __asm("BX %0" :: "r" (destination_address));
}

#if defined(CPU_ARCH_CORTEX_M3) || defined(CPU_ARCH_CORTEX_M4)
static inline uint32_t cpu_get_image_baseaddr(void)
{
    return SCB->VTOR;
}
#endif

#ifdef __cplusplus
}
#endif

#endif /* CPU_H */
