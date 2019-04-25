/**
 * Cortex-M3 and Cortex-M4 use the
 * following register layout when saving their context onto the stack:
 *
 * -------- highest address (bottom of stack)
 * | xPSR |
 * --------
 * | PC   |
 * --------
 * | LR   |
 * --------
 * | R12  |
 * --------
 * | R3   |
 * --------
 * | R2   |
 * --------
 * | R1   |
 * --------
 * | R0   | <- the registers from xPSR to R0 are handled by hardware
 * --------
 * | R11  |
 * --------
 * | R10  |
 * --------
 * | R9   |
 * --------
 * | R8   |
 * --------
 * | R7   |
 * --------
 * | R6   |
 * --------
 * | R5   |
 * --------
 * | R4   |
 * --------
 * | RET  | <- exception return code
 * -------- lowest address (top of stack)
 */

#include <stdio.h>

#include "sched.h"
#include "thread.h"
#include "irq.h"
#include "cpu.h"

extern uint32_t _estack;
extern uint32_t _sstack;

/**
 * This marker is used e.g. by 'cpu_switch_context_exit' to identify the stacks
 * beginning.
 */
#define STACK_MARKER                (0x77777777)

/**
 * Initial program status register value for a newly created thread
 */ 
#define INITIAL_XPSR                (0x01000000)

/**
 * ARM Cortex-M specific exception return value, that triggers the return to the
 * task mode stack pointer.
 */
#define EXCEPT_RET_TASK_MODE        (0xfffffffd)

char *thread_stack_init(thread_task_func_t task_func,
                        void *arg,
                        void *stack_start,
                        int stack_size)
{
    uint32_t *stk;
    stk = (uint32_t *)((uintptr_t)stack_start + stack_size);

    /* adjust to 32 bit boundary by clearing the last two bits in the address */
    stk = (uint32_t *)(((uint32_t)stk) & ~((uint32_t)0x3));

    /* stack start marker */
    stk--;
    *stk = STACK_MARKER;

    /* make sure the stack is double word aligned (8 bytes) */
    /* This is required in order to conform with Procedure Call Standard for the
     * ARM® Architecture (AAPCS) */
    /* http://infocenter.arm.com/help/topic/com.arm.doc.ihi0042e/IHI0042E_aapcs.pdf */
    if (((uint32_t) stk & 0x7) != 0) {
        /* add a single word padding */
        --stk;
        *stk = ~((uint32_t)STACK_MARKER);
    }

    /* ****************************** */
    /* Automatically popped registers */
    /* ****************************** */

    /* The following eight stacked registers are popped by the hardware upon
     * return from exception. (bx instruction in context_restore) */

    /* xPSR - initial status register */
    stk--;
    *stk = (uint32_t)INITIAL_XPSR;
    /* pc - initial program counter value := thread entry function */
    stk--;
    *stk = (uint32_t)task_func;
    /* lr - contains the return address when the thread exits */
    stk--;
    *stk = (uint32_t)sched_task_exit;
    /* r12 */
    stk--;
    *stk = 0;
    /* r3 - r1 */
    for (int i = 3; i >= 1; i--) {
        stk--;
        *stk = i;
    }
    /* r0 - contains the thread function parameter */
    stk--;
    *stk = (uint32_t)arg;

    /* ************************* */
    /* Manually popped registers */
    /* ************************* */

    /* The following registers are not handled by hardware in return from
     * exception, but manually by context_restore.
     * For the Cortex-M3 and Cortex-M4 we write them continuously onto the stack
     * as they can be read/written continuously by stack instructions. */

    /* r11 - r4 */
    for (int i = 11; i >= 4; i--) {
        stk--;
        *stk = i;
    }

    /* exception return code  - return to task-mode process stack pointer */
    stk--;
    *stk = (uint32_t)EXCEPT_RET_TASK_MODE;

    /* The returned stack pointer will be aligned on a 32 bit boundary not on a
     * 64 bit boundary because of the odd number of registers above (8+9).
     * This is not a problem since the initial stack pointer upon process entry
     * _will_ be 64 bit aligned (because of the cleared bit 9 in the stacked
     * xPSR and aligned stacking of the hardware-handled registers). */

    return (char *) stk;
}

void thread_stack_print(void)
{

}

/* This function returns the number of bytes used on the ISR stack */
int thread_isr_stack_usage(void)
{
    uint32_t *ptr = &_sstack;

    while(((*ptr) == STACK_CANARY_WORD) && (ptr < &_estack)) {
        ++ptr;
    }

    ptrdiff_t num_used_words = &_estack - ptr;
    return num_used_words * sizeof(*ptr);
}

void *thread_isr_stack_pointer(void)
{
    void *msp = (void *)__get_MSP();
    return msp;
}

void *thread_isr_stack_start(void)
{
    return (void *)&_sstack;
}

__attribute__((naked)) void NORETURN cpu_switch_context_exit(void)
{
    __asm__ volatile (
    "bl     irq_enable                    \n" /* enable IRQs to make the SVC
                                               * interrupt is reachable */
    "svc    #1                            \n" /* trigger the SVC interrupt */
    "unreachable%=:                       \n" /* this loop is unreachable */
    "b      unreachable%=                 \n" /* loop indefinitely */
    :::);
}

void thread_yield_higher(void)
{
    /* trigger the PENDSV interrupt to run scheduler and schedule new thread if
     * applicable */
    SCB->ICSR |= SCB_ICSR_PENDSVSET_Msk;
}

void __attribute__((naked)) __attribute__((used)) isr_pendsv(void) {
    __asm__ volatile (
    /* PendSV handler entry point */
    /* save context by pushing unsaved registers to the stack */
    /* {r0-r3,r12,LR,PC,xPSR,s0-s15,FPSCR} are saved automatically on exception entry */
    ".thumb_func                      \n"
    "mrs    r0, psp                   \n" /* get stack pointer from user mode */
    "stmdb  r0!,{r4-r11}              \n" /* save regs */
    "stmdb  r0!,{lr}                  \n" /* exception return value */
    "ldr    r1, =sched_active_thread  \n" /* load address of current tcb */
    "ldr    r1, [r1]                  \n" /* dereference pdc */
    "str    r0, [r1]                  \n" /* write r0 to pdc->sp */
    "bl     isr_svc                   \n" /* continue with svc */
    );
}

void __attribute__((naked)) __attribute__((used)) isr_svc(void) {
    __asm__ volatile (
    /* SVC handler entry point */
    /* PendSV will continue here as well (via jump) */
    ".thumb_func                      \n"
    /* perform scheduling */
    "bl     sched_run                 \n"
    /* restore context and return from exception */
    ".thumb_func                      \n"
    "context_restore:                 \n"
    "ldr    r0, =sched_active_thread  \n" /* load address of current TCB */
    "ldr    r0, [r0]                  \n" /* dereference TCB */
    "ldr    r1, [r0]                  \n" /* load tcb->sp to register 1 */
    "ldmia  r1!, {r0}                 \n" /* restore exception return value */
    "ldmia  r1!, {r4-r11}             \n" /* restore other registers */
    "msr    psp, r1                   \n" /* restore user mode SP to PSP reg */
    "bx     r0                        \n" /* load exception return value to PC,
                                           * causes end of exception*/
    /* {r0-r3,r12,LR,PC,xPSR,s0-s15,FPSCR} are restored automatically on exception return */
    );
}
