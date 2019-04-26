#ifndef STDIO_BASE_H
#define STDIO_BASE_H

#include <unistd.h>

#ifdef __cplusplus
extern "C" {
#endif

void stdio_init(void);

ssize_t stdio_read(void* buffer, size_t max_len);

ssize_t stdio_write(const void* buffer, size_t len);

#ifdef __cplusplus
}
#endif

#endif /* STDIO_BASE_H */
