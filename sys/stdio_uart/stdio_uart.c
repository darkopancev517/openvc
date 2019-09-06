#include "stdio_uart.h"
#include "isrpipe.h"
#include "periph/uart.h"

#ifndef CONTIKI_NG_SNIFFER
static char _stdio_uart_buf_mem[STDIO_UART_RX_BUFSIZE];
isrpipe_t stdio_uart_isrpipe = ISRPIPE_INIT(_stdio_uart_buf_mem);
#endif

void stdio_init(void)
{
#ifndef CONTIKI_NG_SNIFFER
    uart_init(STDIO_UART_DEV, STDIO_UART_BAUDRATE, (uart_rx_cb_t)isrpipe_write_one, &stdio_uart_isrpipe);
#else
    uart_init(STDIO_UART_DEV, STDIO_UART_BAUDRATE, NULL, NULL);
#endif
}

ssize_t stdio_read(void *buffer, size_t count)
{
    (void) buffer;
    (void) count;
    return -1; 
}

ssize_t stdio_write(const void *buffer, size_t len)
{
    uart_write(STDIO_UART_DEV, (const uint8_t *)buffer, len);
    return len;
}
