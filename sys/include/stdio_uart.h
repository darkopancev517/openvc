#ifndef STDIO_UART_H
#define STDIO_UART_H

/* boards may override the default STDIO UART device */
#include "board.h"
#include "stdio_base.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef STDIO_UART_DEV
#define STDIO_UART_DEV          UART_DEV(0)
#endif

#ifndef STDIO_UART_BAUDRATE
#define STDIO_UART_BAUDRATE     (115200)
#endif

#ifndef STDIO_UART_RX_BUFSIZE
#define STDIO_UART_RX_BUFSIZE   (64)
#endif

#ifdef __cplusplus
}
#endif

#endif /* STDIO_UART_H */
