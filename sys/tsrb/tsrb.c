#include "tsrb.h"

static void _push(tsrb_t *rb, char c)
{
    rb->buf[rb->writes++ & (rb->size - 1)] = c;
}

static char _pop(tsrb_t *rb)
{
    return rb->buf[rb->reads++ & (rb->size - 1)];
}

int tsrb_get_one(tsrb_t *rb)
{
    if (!tsrb_empty(rb)) {
        return _pop(rb);
    }
    else {
        return -1;
    }
}

int tsrb_get(tsrb_t *rb, char *dst, size_t n)
{
    size_t tmp = n;
    while (tmp && !tsrb_empty(rb)) {
        *dst++ = _pop(rb);
        tmp--;
    }
    return (n - tmp);
}

int tsrb_drop(tsrb_t *rb, size_t n)
{
    size_t tmp = n;
    while (tmp && !tsrb_empty(rb)) {
        _pop(rb);
        tmp--;
    }
    return (n - tmp);
}

int tsrb_add_one(tsrb_t *rb, char c)
{
    if (!tsrb_full(rb)) {
        _push(rb, c);
        return 0;
    }
    else {
        return -1;
    }
}

int tsrb_add(tsrb_t *rb, const char *src, size_t n)
{
    size_t tmp = n;
    while (tmp && !tsrb_full(rb)) {
        _push(rb, *src++);
        tmp--;
    }
    return (n - tmp);
}
