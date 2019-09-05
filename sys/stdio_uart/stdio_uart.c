#include "stdio_uart.h"
#include "periph/uart.h"

void stdio_init(void)
{
    uart_init(STDIO_UART_DEV, STDIO_UART_BAUDRATE, NULL, NULL);
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
