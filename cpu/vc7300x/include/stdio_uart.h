#ifndef STDIO_UART_H
#define STDIO_UART_H

#include "stdio_base.h"

#ifdef __cplusplus
extern "C" {
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
