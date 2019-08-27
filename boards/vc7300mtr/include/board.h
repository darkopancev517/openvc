#ifndef BOARD_H
#define BOARD_H

#include "cpu.h"
#include "periph/uart.h"
#include "periph/gpio.h"
#include "periph/spi.h"
#include "periph/timer.h"

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

/* board spi interface with centauri */
#define BOARD_CENTAURI_SPI_DEV          SPI_DEV(2)
#define BOARD_CENTAURI_SPI_CS_PIN       GPIO_PIN(PORTC, 4)
#define BOARD_CENTAURI_RESET_PIN        GPIO_PIN(PORTC, 5)
#define BOARD_CENTAURI_INT_PIN          GPIO_PIN(PORTA, 14)

/* stdio uart interface */

#define STDIO_UART_DEV                  UART_DEV(1)
#define STDIO_UART_BAUDRATE             (115200)
#define STDIO_UART_RX_BUFSIZE           (128)

/* xtimer interface */
#define XTIMER_DEV                      TIMER_DEV(0)
#define XTIMER_FREQ_BASE                (1000000)

void board_init(void);

#ifdef __cplusplus
}
#endif

#endif /* BOARD_H */
