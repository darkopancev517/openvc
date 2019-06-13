#ifndef RINGBUFFER_H
#define RINGBUFFER_H

#ifdef __cplusplus
extern "C" {
#endif

typedef struct {
    char *buf;          /* Buffer to operate on. */
    unsigned int size;  /* Size of buf. */
    unsigned int start; /* Current read position in the ring buffer. */
    unsigned int avail; /* Number of elements available for reading. */
} ringbuffer_t;

#define RINGBUFFER_INIT(BUF) { (BUF), sizeof (BUF), 0, 0 }

static inline void ringbuffer_init(ringbuffer_t *__restrict rb, char *buffer, unsigned bufsize)
{
    rb->buf = buffer;
    rb->size = bufsize;
    rb->start = 0;
    rb->avail = 0;
}

int ringbuffer_add_one(ringbuffer_t *__restrict rb, char c);

unsigned ringbuffer_add(ringbuffer_t *__restrict rb, const char *buf, unsigned n);

int ringbuffer_get_one(ringbuffer_t *__restrict rb);

unsigned ringbuffer_get(ringbuffer_t *__restrict rb, char *buf, unsigned n);

unsigned ringbuffer_remove(ringbuffer_t *__restrict rb, unsigned n);

static inline int ringbuffer_empty(const ringbuffer_t *__restrict rb)
{
    return rb->avail == 0;
}

static inline int ringbuffer_full(const ringbuffer_t *__restrict rb)
{
    return rb->avail == rb->size;
}

static inline unsigned int ringbuffer_get_free(const ringbuffer_t *__restrict rb)
{
    return rb->size - rb->avail;
}

int ringbuffer_peek_one(const ringbuffer_t *__restrict rb);

unsigned ringbuffer_peek(const ringbuffer_t *__restrict rb, char *buf, unsigned n);

#ifdef __cplusplus
}
#endif

#endif /* RINGBUFFER_H */
