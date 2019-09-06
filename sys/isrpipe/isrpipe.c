#include "isrpipe.h"
#ifdef PKG_CONTIKI_NG
#include "contiki.h"
PROCESS_NAME(uart_arch_process);
#endif

void isrpipe_init(isrpipe_t *isrpipe, char *buf, size_t bufsize)
{
    tsrb_init(&isrpipe->tsrb, buf, bufsize);
}

int isrpipe_write_one(isrpipe_t *isrpipe, char c)
{
    int res = tsrb_add_one(&isrpipe->tsrb, c);
#ifdef PKG_CONTIKI_NG
    process_poll(&uart_arch_process);
#endif
    return res;
}

int isrpipe_read(isrpipe_t *isrpipe, char *buffer, size_t count)
{
    return tsrb_get(&isrpipe->tsrb, buffer, count);
}
