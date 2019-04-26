#include <stdio.h>

int main(void)
{
    extern void cpu_led_on(void);
    cpu_led_on();

    return 0;
}
