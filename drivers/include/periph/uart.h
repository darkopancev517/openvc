#ifndef PERIPH_UART_H
#define PERIPH_UART_H

#include <stddef.h>
#include <stdint.h>
#include <limits.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef unsigned int uart_t;

#define UART_UNDEF ((uart_t)(UINT_MAX))

#define UART_DEV(x) ((uart_t)(x))

typedef void (*uart_rx_cb_t)(void *arg, uint8_t data);

typedef struct {
    uart_rx_cb_t rx_cb;
    void *arg;
} uart_isr_ctx_t;

enum {
    UART_OK         = 0,
    UART_NODEV      = -1,
    UART_NOBAUD     = -2,
    UART_INTERR     = -3,
    UART_NOMODE     = -4,
};

typedef enum {
    UART_PARITY_NONE,
    UART_PARITY_EVEN,
    UART_PARITY_ODD,
    UART_PARITY_MARK,
    UART_PARITY_SPACE,
} uart_parity_t;

typedef enum {
    UART_DATA_BITS_5,
    UART_DATA_BITS_6,
    UART_DATA_BITS_7,
    UART_DATA_BITS_8,
} uart_data_bits_t;

typedef enum {
    UART_STOP_BITS_1,
    UART_STOP_BITS_2,
} uart_stop_bits_t;

int uart_init(uart_t uart, uint32_t baudrate, uart_rx_cb_t rx_cb, void *arg);

int uart_mode(uart_t uart,
              uart_data_bits_t data_bits,
              uart_parity_t parity,
              uart_stop_bits_t stop_bits);

void uart_write(uart_t uart, const uint8_t *data, size_t len);

void uart_poweron(uart_t uart);

void uart_poweroff(uart_t uart);

#ifdef __cplusplus
}
#endif

#endif /* PERIPH_UART_H */
