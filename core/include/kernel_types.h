#ifndef KERNEL_TYPES_H
#define KERNEL_TYPES_H

#include <stdint.h>
#include <inttypes.h>
#include <limits.h>
#include <stddef.h>
#include <sys/types.h>

/**
 * Maximum value for ssize_t
 */
#ifndef SSIZE_MAX
#define SSIZE_MAX ((ssize_t) (SIZE_MAX / 2))
#endif

#ifdef __cplusplus
 extern "C" {
#endif

#ifndef MAXTHREADS
#define MAXTHREADS 32
#endif

#define KERNEL_PID_UNDEF 0

#define KERNEL_PID_FIRST (KERNEL_PID_UNDEF + 1)

#define KERNEL_PID_LAST (KERNEL_PID_FIRST + MAXTHREADS - 1)

#define PRIkernel_pid PRIi16

typedef int16_t kernel_pid_t;

static inline int pid_is_valid(kernel_pid_t pid)
{
    return ((KERNEL_PID_FIRST <= pid) && (pid <= KERNEL_PID_LAST));
}

#ifdef __cplusplus
}
#endif

#endif /* KERNEL_TYPES_H */
