#include <stdio.h>

#include "xtimer.h"

int main(void)
{
    xtimer_init();

    printf("hello world\n");

    while (1) {
        printf("now: %lu\n", xtimer_now().ticks32);
        xtimer_msleep(1000);
    }

    return 0;
}
