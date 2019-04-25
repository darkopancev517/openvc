/**
 * Circular integer buffer interface
 */
#ifndef CIB_H
#define CIB_H

#include "assert.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct {
    unsigned int read_count;
    unsigned int write_count;
    unsigned int mask;
} cib_t;

/**
 * Initialize cib_t to a given size
 */
#define CIB_INIT(SIZE) { 0, 0, (SIZE) - 1 }

static inline void cib_init(cib_t *__restrict cib, unsigned int size)
{
    /* check if size is a power of 2 by comparing it to its complement */
    assert(!(size & (size - 1)));

    cib_t c = CIB_INIT(size);
    *cib = c;
}

static inline unsigned int cib_avail(const cib_t *cib)
{
    return cib->write_count - cib->read_count;
}

static inline unsigned int cib_full(const cib_t *cib)
{
    return ((int) cib_avail(cib)) > ((int) cib->mask);
}

static inline int cib_get(cib_t *__restrict cib)
{
    if (cib_avail(cib)) {
        return (int) (cib->read_count++ & cib->mask);
    }

    return -1;
}

static inline int cib_peek(cib_t *__restrict cib)
{
    if (cib_avail(cib)) {
        return (int) (cib->read_count & cib->mask);
    }

    return -1;
}

static inline int cib_get_unsafe(cib_t *cib)
{
        return (int) (cib->read_count++ & cib->mask);
}

static inline int cib_put(cib_t *__restrict cib)
{
    unsigned int avail = cib_avail(cib);

    /* We use a signed compare, because the mask is -1u for an empty CIB. */
    if ((int) avail <= (int) cib->mask) {
        return (int) (cib->write_count++ & cib->mask);
    }

    return -1;
}

static inline int cib_put_unsafe(cib_t *cib)
{
    return (int) (cib->write_count++ & cib->mask);
}

#ifdef __cplusplus
}
#endif

#endif /* CIB_H */
