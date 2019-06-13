#include "stdio_uart.h"
#include "isrpipe.h"
#include "periph/uart.h"

static char _rx_buf_mem[STDIO_UART_RX_BUFSIZE];
isrpipe_t stdio_uart_isrpipe = ISRPIPE_INIT(_rx_buf_mem);

void stdio_init(void)
{
    uart_init(STDIO_UART_DEV, STDIO_UART_BAUDRATE, (uart_rx_cb_t)isrpipe_write_one, &stdio_uart_isrpipe);
}

ssize_t stdio_read(void *buffer, size_t count)
{
    return (ssize_t)isrpipe_read(&stdio_uart_isrpipe, (char *)buffer, count);
}

ssize_t stdio_write(const void *buffer, size_t len)
{
    uart_write(STDIO_UART_DEV, (const uint8_t *)buffer, len);
    return len;
}
