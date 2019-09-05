#include "sensniff-io.h"

#include "board.h"
#include "periph/uart.h"

typedef struct {
    sensniff_io_arch_input_cb_t cb;
} sensniff_io_ctx_t;

static sensniff_io_ctx_t sensniff_io_ctx;

void sensniff_io_uart_cb(void *arg, uint8_t data)
{
    if (sensniff_io_ctx.cb != NULL) {
        sensniff_io_ctx.cb((unsigned char)data);
    }
}

void sensniff_io_arch_init(void)
{
    uart_init(SENSNIFF_UART_DEV, SENSNIFF_UART_BAUDRATE, sensniff_io_uart_cb, NULL);
}

void sensniff_io_arch_byte_out(unsigned char c)
{
    uart_write(SENSNIFF_UART_DEV, &c, 1);
}

void sensniff_io_arch_set_input(sensniff_io_arch_input_cb_t cb)
{
    sensniff_io_ctx.cb = cb;
}

void sensniff_io_arch_flush(void)
{

}
