#include "stdio_uart.h"
#include "vcsoc.h"

void stdio_init(void)
{
    vcmisc_config_apb_periph(APBPERIPH_UART0, true);
    vcuart_config_reset(UART0);

    vcsfio_enable_uart(UART0);

    vcuart_config_mode(UART0, UARTMODE_TX);
    vcuart_config_parity(UART0, UARTPARITY_NONE);
    vcuart_config_stoplen(UART0, UARTSTOPLEN_1BITS);
    vcuart_config_wordlen(UART0, UARTWORDLEN_8BITS);
    vcuart_config_firstbit(UART0, UARTFIRSTBIT_LSB);
    vcuart_config_baudrate(UART0, 115200);
    vcuart_config_fifo_softrst(UART0, false);
    vcuart_config_fifo_ovmode(UART0, false);

    vcuart_config_fifo_txlevel(UART0, UARTFIFO_TXLVL_7);
    vcuart_config_fifo_rxlevel(UART0, UARTFIFO_RXLVL_0);
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
        vcuart_send_byte(UART0, data[i]);
        while (!vcuart_get_status(UART0, UARTSTS_TXDONE));
        vcuart_clear_status(UART0, UARTSTS_TXDONE);
    }

    return len;
}

ssize_t stdio_write(const void *buffer, size_t len)
{
    return uart_write((const uint8_t *)buffer, len);
}
