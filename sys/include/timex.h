#ifndef TIMEX_H
#define TIMEX_H

#include <stdint.h>
#include <inttypes.h>

#ifdef __cplusplus
extern "C" {
#endif

#define US_PER_SEC  (1000000U)
#define SEC_PER_MIN (60U)
#define CS_PER_SEC  (100U)
#define MS_PER_SEC  (1000U)
#define US_PER_MS   (1000U)
#define NS_PER_US   (1000U)

#define TIMEX_MAX_STR_LEN   (20)

typedef struct {
    uint32_t seconds;
    uint32_t microseconds;
} timex_t;

timex_t timex_add(const timex_t a, const timex_t b);

timex_t timex_sub(const timex_t a, const timex_t b);

timex_t timex_set(uint32_t seconds, uint32_t microseconds);

int timex_cmp(const timex_t a, const timex_t b);

static inline void timex_normalize(timex_t *time)
{
    time->seconds += (time->microseconds / US_PER_SEC);
    time->microseconds %= US_PER_SEC;
}

static inline int timex_isnormalized(const timex_t *time)
{
    return (time->microseconds < US_PER_SEC);
}

static inline uint64_t timex_uint64(const timex_t a)
{
    return (uint64_t) a.seconds * US_PER_SEC + a.microseconds;
}

static inline timex_t timex_from_uint64(const uint64_t timestamp)
{
    return timex_set(timestamp / US_PER_SEC, timestamp % US_PER_SEC);
}

const char *timex_to_str(timex_t t, char *timestamp);

#ifdef __cplusplus
}
#endif

#endif /* TIMEX_H */
