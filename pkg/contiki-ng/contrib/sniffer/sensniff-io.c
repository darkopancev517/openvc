#include "sensniff-io.h"

#include "board.h"
#include "isrpipe.h"
#include "periph/uart.h"

sensniff_io_ctx_t sensniff_io_ctx;

static char _sensniff_uart_buf_mem[SENSNIFF_UART_RX_BUFSIZE];
isrpipe_t sensniff_uart_isrpipe = ISRPIPE_INIT(_sensniff_uart_buf_mem);

void sensniff_io_arch_init(void)
{
    uart_init(SENSNIFF_UART_DEV,
              SENSNIFF_UART_BAUDRATE,
              (uart_rx_cb_t)isrpipe_write_one,
              &sensniff_uart_isrpipe);
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
