#ifndef SENSNIFF_IO_H
#define SENSNIFF_IO_H

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

#define sensniff_io_init() sensniff_io_arch_init()
#define sensniff_io_byte_out(b) sensniff_io_arch_byte_out(b)
#define sensniff_io_set_input(cb) sensniff_io_arch_set_input(cb)
#define sensniff_io_flush() sensniff_io_arch_flush()

typedef int (*sensniff_io_arch_input_cb_t)(unsigned char c);

void sensniff_io_arch_init(void);

void sensniff_io_arch_byte_out(unsigned char c);

void sensniff_io_arch_set_input(sensniff_io_arch_input_cb_t cb);

void sensniff_io_arch_flush(void);

#ifdef __cplusplus
}
#endif

#endif /* SENSNIFF_IO_H */
