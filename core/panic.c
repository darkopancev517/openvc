#include <string.h>
#include <stdio.h>

#include "assert.h"
#include "kernel_defines.h"
#include "cpu.h"
#include "irq.h"
#include "panic.h"
#include "periph/pm.h"
#include "log.h"

const char assert_crash_message[] = "FAILED ASSERTION.";

/* flag preventing "recursive crash printing loop" */
static int crashed = 0;

void __attribute__((weak)) panic_arch(void) {}

/* WARNING: this function NEVER returns! */
NORETURN void core_panic(core_panic_t crash_code, const char *message)
{
    if (crashed == 0) {
        /* print panic message to console (if possible) */
        crashed = 1;
        if (crash_code == PANIC_ASSERT_FAIL) {
            cpu_print_last_instruction();
        }

        LOG_ERROR("*** kernel panic:\n%s\n\n", message);
        LOG_ERROR("*** halted.\n\n");
    }

    /* disable watchdog and all possible sources of interrupts */
    irq_disable();
    panic_arch();

    /* tell the compiler that we won't return from this function
       (even if we actually won't even get here...) */
    UNREACHABLE();
}
