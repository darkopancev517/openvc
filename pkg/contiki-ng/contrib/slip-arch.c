#include "contiki.h"
#include "dev/slip.h"

void slip_arch_writeb(unsigned char c)
{
    (void)c;
}

void slip_arch_init()
{
    return;
}
