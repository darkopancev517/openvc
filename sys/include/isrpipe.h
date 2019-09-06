#ifndef ISRPIPE_H
#define ISRPIPE_H

#include <stdint.h>

#include "tsrb.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct {
    tsrb_t tsrb;
} isrpipe_t;

#define ISRPIPE_INIT(tsrb_buf) { .tsrb = TSRB_INIT(tsrb_buf) }

void isrpipe_init(isrpipe_t *isrpipe, char *buf, size_t bufsize);

int isrpipe_write_one(isrpipe_t *isrpipe, char c);

int isrpipe_read(isrpipe_t *isrpipe, char *buf, size_t count);

#ifdef __cplusplus
}
#endif

#endif /* ISRPIPE_H */
