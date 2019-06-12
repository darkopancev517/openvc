#include <stdio.h>

void assert_failure(const char *file, unsigned line)
{
    printf("ASSERT FAILED: %s:%u\n", file, line); \
    extern unsigned irq_disable(void); \
    irq_disable(); \
    for ( ;; ); \
}
