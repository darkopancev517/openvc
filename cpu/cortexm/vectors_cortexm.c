#include <stdint.h>
#include <stdio.h>
#include <inttypes.h>

#include "cpu.h"
#include "kernel_init.h"
#include "board.h"
#include "panic.h"
#include "vectors_cortexm.h"

/**
 * Memory markers, defined in the linker script
 */
extern uint32_t _sfixed;
extern uint32_t _efixed;
extern uint32_t _etext;
extern uint32_t _srelocate;
extern uint32_t _erelocate;
extern uint32_t _szero;
extern uint32_t _ezero;
extern uint32_t _sstack;
extern uint32_t _estack;
extern uint8_t _sram;
extern uint8_t _eram;

/**
 * Allocation of the interrupt stack
 */
__attribute__((used,section(".isr_stack"))) uint8_t isr_stack[ISR_STACKSIZE];

/**
 * Pre-start routine for CPU-specific settings
 */
__attribute__((weak)) void pre_startup(void)
{
}

/**
 * Post-start routine for CPU-specific settings
 */
__attribute__((weak)) void post_startup(void)
{
}

void reset_handler_default(void)
{
    uint32_t *dst;
    uint32_t *src = &_etext;

    pre_startup();

    uint32_t *top;
    /* Fill stack space with canary values up until the current stack pointer */
    /* Read current stack pointer from CPU register */
    __asm__ volatile ("mov %[top], sp" : [top] "=r" (top) : : );
    dst = &_sstack;
    while (dst < top) {
        *(dst++) = STACK_CANARY_WORD;
    }

    /* load data section from flash to ram */
    for (dst = &_srelocate; dst < &_erelocate; ) {
        *(dst++) = *(src++);
    }

    /* default bss section to zero */
    for (dst = &_szero; dst < &_ezero; ) {
        *(dst++) = 0;
    }

    post_startup();

    /* initialize the board (which also initiates CPU initialization) */
    board_init();

    extern void __libc_init_array(void);
    __libc_init_array();

    /* startup the kernel */
    kernel_init();
}

void nmi_default(void)
{
    core_panic(PANIC_NMI_HANDLER, "NMI HANDLER");
}

#define HARDFAULT_HANDLER_REQUIRED_STACK_SPACE      (344U)

static inline int _stack_size_left(uint32_t required)
{
    uint32_t *sp;
    __asm__ volatile ("mov %[sp], sp" : [sp] "=r" (sp) : : );
    return ((int)((uint32_t)sp - (uint32_t)&_sstack) - required);
}

void hard_fault_handler(uint32_t* sp, uint32_t corrupted, uint32_t exc_return, uint32_t* r4_to_r11_stack);

/* Trampoline function to save stack pointer before calling hard fault handler */
__attribute__((naked)) void hard_fault_default(void)
{
    /* Get stack pointer where exception stack frame lies */
    __asm__ volatile
    (
        ".syntax unified                    \n"
        /* Check that msp is valid first because we want to stack all the
         * r4-r11 registers so that we can use r0, r1, r2, r3 for other things. */
        "mov r0, sp                         \n" /* r0 = msp                   */
        "cmp r0, %[eram]                    \n" /* if(msp > &_eram) {         */
        "bhi fix_msp                        \n" /*   goto fix_msp }           */
        "cmp r0, %[sram]                    \n" /* if(msp <= &_sram) {        */
        "bls fix_msp                        \n" /*   goto fix_msp }           */
        "movs r1, #0                        \n" /* else { corrupted = false   */
        "b   test_sp                        \n" /*   goto test_sp     }       */
        " fix_msp:                          \n" /*                            */
        "mov r1, %[estack]                  \n" /*     r1 = _estack           */
        "mov sp, r1                         \n" /*     sp = r1                */
        "movs r1, #1                        \n" /*     corrupted = true       */
        " test_sp:                          \n" /*                            */
        "movs r0, #4                        \n" /* r0 = 0x4                   */
        "mov r2, lr                         \n" /* r2 = lr                    */
        "tst r2, r0                         \n" /* if(lr & 0x4)               */
        "bne use_psp                        \n" /* {                          */
        "mrs r0, msp                        \n" /*   r0 = msp                 */
        "b out                              \n" /* }                          */
        " use_psp:                          \n" /* else {                     */
        "mrs r0, psp                        \n" /*   r0 = psp                 */
        " out:                              \n" /* }                          */
        "push {r4-r11}                      \n" /* save r4..r11 to the stack  */
        "mov r3, sp                         \n" /* r4_to_r11_stack parameter  */
        "bl hard_fault_handler              \n" /* hard_fault_handler(r0)     */
          :
          : [sram]   "r" ((uintptr_t)&_sram + HARDFAULT_HANDLER_REQUIRED_STACK_SPACE),
            [eram]   "r" (&_eram),
            [estack] "r" (&_estack)
          : "r0","r4","r5","r6","r8","r9","r10","r11","lr"
    );
}

__attribute__((used)) void hard_fault_handler(uint32_t* sp, uint32_t corrupted, uint32_t exc_return, uint32_t* r4_to_r11_stack)
{
    /* Initialize these variables even if they're never used uninitialized.
     * Fixes wrong compiler warning by gcc < 6.0. */
    uint32_t pc = 0;
    /* cppcheck-suppress variableScope
     * (reason: used within __asm__ which cppcheck doesn't pick up) */
    uint32_t* orig_sp = NULL;

    /* Check if the ISR stack overflowed previously. Not possible to detect
     * after output may also have overflowed it. */
    if (*(&_sstack) != STACK_CANARY_WORD) {
        puts("\nISR stack overflowed");
    }

    /* Sanity check stack pointer and give additional feedback about hard fault */
    if (corrupted) {
        puts("Stack pointer corrupted, reset to top of stack");
    } else {
        uint32_t  r0 = sp[0];
        uint32_t  r1 = sp[1];
        uint32_t  r2 = sp[2];
        uint32_t  r3 = sp[3];
        uint32_t r12 = sp[4];
        uint32_t  lr = sp[5];  /* Link register. */
                  pc = sp[6];  /* Program counter. */
        uint32_t psr = sp[7];  /* Program status register. */

        /* Reconstruct original stack pointer before fault occurred */
        orig_sp = sp + 8;
#ifdef SCB_CCR_STKALIGN_Msk
        if (psr & SCB_CCR_STKALIGN_Msk) {
            /* Stack was not 8-byte aligned */
            orig_sp += 1;
        }
#endif /* SCB_CCR_STKALIGN_Msk */
        puts("\nContext before hardfault:");

        /* TODO: printf in ISR context might be a bad idea */
        printf("   r0: 0x%08" PRIx32 "\n"
               "   r1: 0x%08" PRIx32 "\n"
               "   r2: 0x%08" PRIx32 "\n"
               "   r3: 0x%08" PRIx32 "\n",
               r0, r1, r2, r3);
        printf("  r12: 0x%08" PRIx32 "\n"
               "   lr: 0x%08" PRIx32 "\n"
               "   pc: 0x%08" PRIx32 "\n"
               "  psr: 0x%08" PRIx32 "\n\n",
               r12, lr, pc, psr);
    }

    puts("Misc");
    printf("EXC_RET: 0x%08" PRIx32 "\n", exc_return);

    if (!corrupted) {
        puts("Attempting to reconstruct state for debugging...");
        printf("In GDB:\n  set $pc=0x%" PRIx32 "\n  frame 0\n  bt\n", pc);
        int stack_left = _stack_size_left(HARDFAULT_HANDLER_REQUIRED_STACK_SPACE);
        if (stack_left < 0) {
            printf("\nISR stack overflowed by at least %d bytes.\n", (-1 * stack_left));
        }
        __asm__ volatile (
            "mov r0, %[sp]\n"
            "ldr r2, [r0, #8]\n"
            "ldr r3, [r0, #12]\n"
            "ldr r1, [r0, #16]\n"
            "mov r12, r1\n"
            "ldr r1, [r0, #20]\n"
            "mov lr, r1\n"
            "mov sp, %[orig_sp]\n"
            "mov r1, %[extra_stack]\n"
            "ldm r1, {r4-r11}\n"
            "ldr r1, [r0, #4]\n"
            "ldr r0, [r0, #0]\n"
            :
            : [sp] "r" (sp),
              [orig_sp] "r" (orig_sp),
              [extra_stack] "r" (r4_to_r11_stack)
            : "r0","r1","r2","r3","r12"
            );
    }
    __BKPT(1);

    core_panic(PANIC_HARD_FAULT, "HARD FAULT HANDLER");
}

#if defined(CPU_ARCH_CORTEX_M3) || defined(CPU_ARCH_CORTEX_M4)
void mem_manage_default(void)
{
    core_panic(PANIC_MEM_MANAGE, "MEM MANAGE HANDLER");
}

void bus_fault_default(void)
{
    core_panic(PANIC_BUS_FAULT, "BUS FAULT HANDLER");
}

void usage_fault_default(void)
{
    core_panic(PANIC_USAGE_FAULT, "USAGE FAULT HANDLER");
}

void debug_mon_default(void)
{
    core_panic(PANIC_DEBUG_MON, "DEBUG MON HANDLER");
}
#endif

void dummy_handler_default(void)
{
    core_panic(PANIC_DUMMY_HANDLER, "DUMMY HANDLER");
}

/* Cortex-M common interrupt vectors */
__attribute__((weak,alias("dummy_handler_default"))) void isr_svc(void);
__attribute__((weak,alias("dummy_handler_default"))) void isr_pendsv(void);
__attribute__((weak,alias("dummy_handler_default"))) void isr_systick(void);

/* define Cortex-M base interrupt vectors */
ISR_VECTOR(0) const cortexm_base_t cortex_vector_base = {
    &_estack,
    {
        /* entry point of the program */
        [0] = reset_handler_default,
        /* [-14] non maskable interrupt handler */
        [1] = nmi_default,
        /* [-13] hard fault exception */
        [2] = hard_fault_default,
        /* [-5] SW interrupt use for triggering context switches */
        [10] = isr_svc,
        /* [-2] pendSV interrupt use to do the actual context switch */
        [13] = isr_pendsv,
        /* [-1] SysTick interrupt not used */
        [14] = isr_systick,

#if defined(CPU_ARCH_CORTEX_M3) || defined(CPU_ARCH_CORTEX_M4)
        /* [-12] memory manage exception */
        [ 3] = mem_manage_default,
        /* [-11] bus fault exception */
        [ 4] = bus_fault_default,
        /* [-10] usage fault exception */
        [ 5] = usage_fault_default,
        /* [-4] debug monitor exception */
        [11] = debug_mon_default,
#endif
    }
};
