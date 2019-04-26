#include "stdio_uart.h"
#include "vcsoc.h"

void stdio_init(void)
{
    vcmisc_config_apb_periph(APBPERIPH_UART1, true);
    vcuart_config_reset(UART1);

    vcsfio_enable_uart(UART1);

    vcuart_config_mode(UART1, UARTMODE_TX);
    vcuart_config_parity(UART1, UARTPARITY_NONE);
    vcuart_config_stoplen(UART1, UARTSTOPLEN_1BITS);
    vcuart_config_wordlen(UART1, UARTWORDLEN_8BITS);
    vcuart_config_firstbit(UART1, UARTFIRSTBIT_LSB);
    vcuart_config_baudrate(UART1, 115200);
    vcuart_config_fifo_softrst(UART1, false);
    vcuart_config_fifo_ovmode(UART1, false);

    vcuart_config_fifo_txlevel(UART1, UARTFIFO_TXLVL_7);
    vcuart_config_fifo_rxlevel(UART1, UARTFIFO_RXLVL_0);
}

ssize_t stdio_read(void *buffer, size_t count)
{
    (void) buffer;
    (void) count;
    return 0;
}

static size_t uart_write(const uint8_t *data, size_t len)
{
    for (size_t i= 0; i < len; i++) {
        vcuart_send_byte(UART1, data[i]);
        while (!vcuart_get_status(UART1, UARTSTS_TXDONE));
        vcuart_clear_status(UART1, UARTSTS_TXDONE);
    }

    return len;
}

ssize_t stdio_write(const void *buffer, size_t len)
{
    return uart_write((const uint8_t *)buffer, len);
}
