#include <unistd.h>
#include <reent.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/unistd.h>
#include <stdint.h>

#include "cpu.h"
#include "irq.h"
#include "board.h"
#include "stdio_uart.h"

extern char _sheap;                 /* start of the heap */
extern char _eheap;                 /* end of the heap */
char *heap_top = &_sheap + 4;

/**
 * Initialized NewLib, called by __libc_init_array() form the startup.
 */
void _init(void)
{
    stdio_init();
}

__attribute__((used)) void _fini(void)
{
    /* nothing to do here */
}

void _exit(int n)
{
    while(1);
}

/**
 * Allocate memory from the heap.
 */
void *_sbrk_r(struct _reent *r, ptrdiff_t incr)
{
    unsigned int state = irq_disable();
    void *res = heap_top;

    if ((heap_top + incr > &_eheap) || (heap_top + incr < &_sheap)) {
        r->_errno = ENOMEM;
        res = (void *)-1;
    }
    else {
        heap_top += incr;
    }

    irq_restore(state);
    return res;
}

_ssize_t _read_r(struct _reent *r, int fd, void *buffer, size_t count)
{
    (void) r;
    (void) fd;
    return stdio_read(buffer, count);
}

_ssize_t _write_r(struct _reent *r, int fd, const void *data, size_t count)
{
    (void) r;
    (void) fd;
    return stdio_write(data, count);
}

/* Stubs to avoid linking errors, these functions do not have any effect */
int _open_r(struct _reent *r, const char *name, int flags, int mode)
{
    (void) name;
    (void) flags;
    (void) mode;
    r->_errno = ENODEV;
    return -1;
}

int _close_r(struct _reent *r, int fd)
{
    (void) fd;
    r->_errno = ENODEV;
    return -1;
}

_off_t _lseek_r(struct _reent *r, int fd, _off_t pos, int dir)
{
    (void) fd;
    (void) pos;
    (void) dir;
    r->_errno = ENODEV;
    return -1;
}

int _fstat_r(struct _reent *r, int fd, struct stat *st)
{
    (void) fd;
    (void) st;
    r->_errno = ENODEV;
    return -1;
}

int _stat_r(struct _reent *r, const char *name, struct stat *st)
{
    (void) name;
    (void) st;
    r->_errno = ENODEV;
    return -1;
}

int _unlink_r(struct _reent *r, const char *path)
{
    (void) path;
    r->_errno = ENODEV;
    return -1;
}

int _isatty_r(struct _reent *ptr, int fd)
{
    if (fd >= 0 && fd < 3) {
        return 1;
    }

    ptr->_errno = ENOTSUP;
    return -1;
}
