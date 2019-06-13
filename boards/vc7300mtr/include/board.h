#ifndef BOARD_H
#define BOARD_H

#include "cpu.h"
#include "periph/uart.h"
#include "periph/gpio.h"

#ifdef __cplusplus
extern "C" {
#endif

/* board led interface */

#define BOARD_TXLED_PIN                 GPIO_PIN(PORTA, 7)
#define BOARD_RXLED_PIN                 GPIO_PIN(PORTA, 6)

#define BOARD_TXLED_INIT()              gpio_init(BOARD_TXLED_PIN, GPIO_OUT)
#define BOARD_RXLED_INIT()              gpio_init(BOARD_RXLED_PIN, GPIO_OUT)

#define BOARD_TXLED_ON()                gpio_clear(BOARD_TXLED_PIN)
#define BOARD_TXLED_OFF()               gpio_set(BOARD_TXLED_PIN)
#define BOARD_TXLED_TOGGLE()            gpio_toggle(BOARD_TXLED_PIN)

#define BOARD_RXLED_ON()                gpio_clear(BOARD_RXLED_PIN)
#define BOARD_RXLED_OFF()               gpio_set(BOARD_RXLED_PIN)
#define BOARD_RXLED_TOGGLE()            gpio_toggle(BOARD_RXLED_PIN)

/* stdio uart interface */

#define STDIO_UART_DEV                  UART_DEV(1)
#define STDIO_UART_BAUDRATE             (115200)
#define STDIO_UART_RX_BUFSIZE           (128)

void board_init(void);

#ifdef __cplusplus
}
#endif

#endif /* BOARD_H */
