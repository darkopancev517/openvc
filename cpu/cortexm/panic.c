#include "cpu.h"
#include "log.h"

static void print_ipsr(void)
{
    uint32_t ipsr = __get_IPSR() & IPSR_ISR_Msk;
    if (ipsr) {
        /* if you get here, you might have forgotten to implement the isr
         * for the printed interrupt number */
        LOG_ERROR("Inside isr %d\n", ((int)ipsr) - 16);
    }
}

void panic_arch(void)
{
    print_ipsr();
    /* The bkpt instruction will signal to the debugger to break here. */
    __asm__("bkpt #0");
}
