#ifndef TRSB_H
#define TRSB_H

#include <assert.h>
#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct tsrb {
    char *buf;                  /* Buffer to operate on. */
    unsigned int size;          /* Size of buffer, must be power of 2. */
    volatile unsigned reads;    /* total number of reads */
    volatile unsigned writes;   /* total number of writes */
} tsrb_t;

#define TSRB_INIT(BUF) { (BUF), sizeof (BUF), 0, 0 }

static inline void tsrb_init(tsrb_t *rb, char *buffer, unsigned bufsize)
{
    /* make sure bufsize is a power of two.
     * http://www.exploringbinary.com/ten-ways-to-check-if-an-integer-is-a-power-of-two-in-c/
     */
    assert((bufsize != 0) && ((bufsize & (~bufsize + 1)) == bufsize));

    rb->buf = buffer;
    rb->size = bufsize;
    rb->reads = 0;
    rb->writes = 0;
}

static inline int tsrb_empty(const tsrb_t *rb)
{
    return (rb->reads == rb->writes);
}

static inline unsigned int tsrb_avail(const tsrb_t *rb)
{
    return (rb->writes - rb->reads);
}

static inline int tsrb_full(const tsrb_t *rb)
{
    return (rb->writes - rb->reads) == rb->size;
}

static inline unsigned int tsrb_free(const tsrb_t *rb)
{
    return (rb->size - rb->writes + rb->reads);
}

int tsrb_get_one(tsrb_t *rb);

int tsrb_get(tsrb_t *rb, char *dst, size_t n);

int tsrb_drop(tsrb_t *rb, size_t n);

int tsrb_add_one(tsrb_t *rb, char c);

int tsrb_add(tsrb_t *rb, const char *src, size_t n);

#ifdef __cplusplus
}
#endif

#endif /* TRSB_H */
