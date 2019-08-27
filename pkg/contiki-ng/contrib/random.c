#include "contiki.h"
#include "sys/node-id.h"
#include "lib/random.h"

static uint32_t state = 1;

void random_init(unsigned short seed)
{
    state = clock_time() + (3600 * node_id);
}

unsigned short random_rand(void)
{
    uint32_t mlcg, p, q;
    uint64_t tmpstate;
    tmpstate = (uint64_t)33614 * (uint64_t)state;
    q = tmpstate & 0xffffffff;
    q = q >> 1;
    p = tmpstate >> 32;
    mlcg = p + q;
    if (mlcg & 0x80000000) {
        mlcg &= 0x7fffffff;
        mlcg++;
    }
    state = mlcg;
    return (unsigned short)mlcg;
}
