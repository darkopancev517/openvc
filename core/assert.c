#include <stdio.h>

#include "assert.h"

void assert_failure(const char *file, unsigned line)
{
    printf("%s:%u => ", file, line); \
    core_panic(PANIC_ASSERT_FAIL, assert_crash_message); \
}
