#ifndef DEBUG_H
#define DEBUG_H

#include <stdio.h>

#include "sched.h"
#include "thread.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef ENABLE_DEBUG
#define ENABLE_DEBUG (0)
#endif

#if !ENABLE_DEBUG
#define DEBUG(...)
#endif

#ifdef __cplusplus
}
#endif

#endif /* DEBUG_H */
