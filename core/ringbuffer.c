#include <string.h>

#include "ringbuffer.h"

static void add_tail(ringbuffer_t *restrict rb, char c)
{
    unsigned pos = rb->start + rb->avail++;
    if (pos >= rb->size) {
        pos -= rb->size;
    }
    rb->buf[pos] = c;
}

static char get_head(ringbuffer_t *restrict rb)
{
    char result = rb->buf[rb->start];
    if ((--rb->avail == 0) || (++rb->start == rb->size)) {
        rb->start = 0;
    }
    return result;
}

unsigned ringbuffer_add(ringbuffer_t *restrict rb, const char *buf, unsigned n)
{
    unsigned i;
    for (i = 0; i < n; i++) {
        if (ringbuffer_full(rb)) {
            break;
        }
        add_tail(rb, buf[i]);
    }
    return i;
}

int ringbuffer_add_one(ringbuffer_t *restrict rb, char c)
{
    int result = -1;
    if (ringbuffer_full(rb)) {
        result = (unsigned char) get_head(rb);
    }
    add_tail(rb, c);
    return result;
}

int ringbuffer_get_one(ringbuffer_t *restrict rb)
{
    if (!ringbuffer_empty(rb)) {
        return (unsigned char) get_head(rb);
    }
    else {
        return -1;
    }
}

unsigned ringbuffer_get(ringbuffer_t *restrict rb, char *buf, unsigned n)
{
    if (n > rb->avail) {
        n = rb->avail;
    }
    if (n > 0) {
        unsigned bytes_till_end = rb->size - rb->start;
        if (bytes_till_end >= n) {
            memcpy(buf, rb->buf + rb->start, n);
            if (bytes_till_end == n) {
                rb->start = 0;
            }
            else {
                rb->start += n;
            }
        }
        else {
            memcpy(buf, rb->buf + rb->start, bytes_till_end);
            rb->start = n - bytes_till_end;
            memcpy(buf + bytes_till_end, rb->buf, rb->start);
        }
        rb->avail -= n;
    }
    return n;
}

unsigned ringbuffer_remove(ringbuffer_t *restrict rb, unsigned n)
{
    if (n > rb->avail) {
        n = rb->avail;
        rb->start = rb->avail = 0;
    }
    else {
        rb->start += n;
        rb->avail -= n;

        /* compensate underflow */
        if (rb->start > rb->size) {
            rb->start -= rb->size;
        }
    }

    return n;
}

int ringbuffer_peek_one(const ringbuffer_t *restrict rb_)
{
    ringbuffer_t rb = *rb_;
    return ringbuffer_get_one(&rb);
}

unsigned ringbuffer_peek(const ringbuffer_t *restrict rb_, char *buf, unsigned n)
{
    ringbuffer_t rb = *rb_;
    return ringbuffer_get(&rb, buf, n);
}
