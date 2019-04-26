/**
 * Copyright (c) 2018 Vertexcom Technologies, Inc. All rights reserved
 * Vertexcom Confidential Proprietary
 *
*/

#ifndef __VC_UART_H
#define __VC_UART_H

#include <stdint.h>
#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif

#define UART0 0
#define UART1 1
#define UART2 2
#define UART3 3
#define UART4 4
#define UART5 5
#define UART6 6

#define UARTMODE_TX         0
#define UARTMODE_RX         1
#define UARTMODE_TXRX       2

#define UARTPARITY_EVEN     0
#define UARTPARITY_ODD      1
#define UARTPARITY_0        2
#define UARTPARITY_1        3
#define UARTPARITY_NONE     4

#define UARTSTOPLEN_1BITS   0
#define UARTSTOPLEN_2BITS   1

#define UARTWORDLEN_8BITS   0
#define UARTWORDLEN_7BITS   1

#define UARTFIRSTBIT_LSB    0
#define UARTFIRSTBIT_MSB    1

#define UARTFIFO_OVMODE_0   0
#define UARTFIFO_OVMODE_1   1

#define UARTFIFO_TXLVL_0    0
#define UARTFIFO_TXLVL_1    1
#define UARTFIFO_TXLVL_2    2
#define UARTFIFO_TXLVL_3    3
#define UARTFIFO_TXLVL_4    4
#define UARTFIFO_TXLVL_5    5
#define UARTFIFO_TXLVL_6    6
#define UARTFIFO_TXLVL_7    7

#define UARTFIFO_RXLVL_0    0
#define UARTFIFO_RXLVL_1    1
#define UARTFIFO_RXLVL_2    2
#define UARTFIFO_RXLVL_3    3
#define UARTFIFO_RXLVL_4    4
#define UARTFIFO_RXLVL_5    5
#define UARTFIFO_RXLVL_6    6
#define UARTFIFO_RXLVL_7    7

#define UARTINT_TXDONE      1
#define UARTINT_RXPE        2
#define UARTINT_RXOV        3
#define UARTINT_TXOV        4
#define UARTINT_RX          5
#define UARTINT_TX          6

#define UARTSTS_TXFULL      0
#define UARTSTS_RXHFULL     1
#define UARTSTS_TXOV        2
#define UARTSTS_RXOV        3
#define UARTSTS_RXPE        4
#define UARTSTS_TXDONE      5
#define UARTSTS_RXPSTS      6

void vcuart_config_reset(uint8_t uart);

void vcuart_config_clk_source(uint8_t uart, bool state);

void vcuart_config_mode(uint8_t uart, uint8_t mode);

void vcuart_config_parity(uint8_t uart, uint8_t parity);

void vcuart_config_stoplen(uint8_t uart, uint8_t stoplen);

void vcuart_config_wordlen(uint8_t uart, uint8_t wordlen);

void vcuart_config_firstbit(uint8_t uart, uint8_t firstbit);

void vcuart_config_baudrate(uint8_t uart, uint32_t baudrate);

void vcuart_config_fifo_softrst(uint8_t uart, bool state);

void vcuart_config_fifo_ovmode(uint8_t uart, bool state);

void vcuart_config_fifo_txlevel(uint8_t uart, uint8_t level);

void vcuart_config_fifo_rxlevel(uint8_t uart, uint8_t level);

void vcuart_config_enable_int(uint8_t uart, uint8_t interrupt);

void vcuart_config_disable_int(uint8_t uart, uint8_t interrupt);


void vcuart_send_byte(uint8_t uart, uint8_t c);

uint8_t vcuart_recv_byte(uint8_t uart);

int vcuart_fifo_get(uint8_t uart, int n, uint8_t *buf);

int vcuart_get_status(uint8_t uart, uint8_t status);

void vcuart_clear_status(uint8_t uart, uint8_t status);

int vcuart_get_int_status(uint8_t uart, uint8_t interrupt);

void vcuart_clear_int_status(uint8_t uart, uint8_t interrupt);

uint32_t vcuart_get_transmit_addr(uint8_t uart);

#ifdef __cplusplus
}
#endif

#endif // __VC_UART_H

