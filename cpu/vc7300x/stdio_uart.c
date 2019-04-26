#include "stdio_uart.h"
#include "vcsoc.h"

#define UARTx       UART1
#define UARTCLK     APBPERIPH_UART1

void stdio_init(void)
{
    vcmisc_config_apb_periph(UARTCLK, true);
    vcuart_config_reset(UARTx);

    vcsfio_enable_uart(UARTx);

    vcuart_config_mode(UARTx, UARTMODE_TX);
    vcuart_config_parity(UARTx, UARTPARITY_NONE);
    vcuart_config_stoplen(UARTx, UARTSTOPLEN_1BITS);
    vcuart_config_wordlen(UARTx, UARTWORDLEN_8BITS);
    vcuart_config_firstbit(UARTx, UARTFIRSTBIT_LSB);
    vcuart_config_baudrate(UARTx, STDIO_UART_BAUDRATE);
    vcuart_config_fifo_softrst(UARTx, false);
    vcuart_config_fifo_ovmode(UARTx, false);

    vcuart_config_fifo_txlevel(UARTx, UARTFIFO_TXLVL_7);
    vcuart_config_fifo_rxlevel(UARTx, UARTFIFO_RXLVL_0);
}

ssize_t stdio_read(void *buffer, size_t count)
{
    (void) buffer;
    (void) count;
    return 0;
}

static void _uart_out_byte(uint8_t data)
{
    vcuart_send_byte(UART1, data);
    while (!vcuart_get_status(UARTx, UARTSTS_TXDONE));
    vcuart_clear_status(UARTx, UARTSTS_TXDONE);
}

static size_t uart_write(const uint8_t *data, size_t len)
{
    for (size_t i= 0; i < len; i++) {
        _uart_out_byte(data[i]);
        if (data[i] == '\n') {
            _uart_out_byte('\r');
        }
    }

    return len;
}

ssize_t stdio_write(const void *buffer, size_t len)
{
    return uart_write((const uint8_t *)buffer, len);
}
