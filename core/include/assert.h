#ifndef ASSERT_H
#define ASSERT_H

#include "panic.h"

#ifdef __cplusplus
extern "C" {
#endif

extern const char assert_crash_message[];

extern void assert_failure(const char *file, unsigned line);

#define assert(cond) ((cond) ? (void)0 : assert_failure(FILE_RELATIVE, __LINE__))

#ifdef __cplusplus
}
#endif

#endif /* ASSERT_H */
