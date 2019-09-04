#include <assert.h>

#include "cpu.h"
#include "vcsoc.h"
#include "periph/gpio.h"
#include "periph/uart.h"

/**
 * Number of UART peripheral interface.
 */
#define UART_NUMOF (7U)

/**
 * Unsupported parameter will set to it's default value.
 */

static uint8_t uart_apbperiph[UART_NUMOF] = {
    APBPERIPH_UART0,
    APBPERIPH_UART1,
    APBPERIPH_UART2,
    APBPERIPH_UART3,
    APBPERIPH_UART4,
    APBPERIPH_UART5,
    APBPERIPH_UART6
};

static uint8_t uart_stop_bits[2] = {
    UARTSTOPLEN_1BITS,
    UARTSTOPLEN_2BITS
};

static uint8_t uart_data_bits[4] = {
    0,
    0,
    UARTWORDLEN_7BITS,
    UARTWORDLEN_8BITS
};

static uint8_t uart_parity[5] = {
    UARTPARITY_NONE,
    UARTPARITY_EVEN,
    UARTPARITY_ODD,
    0,
    0,
};

static int uart_irqn[UART_NUMOF] = {
    Uart0_IRQn,
    Uart1_IRQn,
    Uart2_IRQn,
    Uart3_IRQn,
    Uart4_IRQn,
    Uart5_IRQn,
    Uart6_IRQn
};

typedef struct {
    uint8_t port;
    uint8_t pin;
} uart_io_t;

static uart_io_t uart_rxio[UART_NUMOF] = {
    { .port = PORTA, .pin = 12 },
    { .port = PORTA, .pin = 13 },
    { .port = PORTA, .pin = 14 },
    { .port = PORTA, .pin = 15 },
    { .port = PORTB, .pin = 0 },
    { .port = PORTB, .pin = 1 },
    { .port = PORTB, .pin = 15 },
};

static uart_isr_ctx_t isr_uart_ctx[UART_NUMOF];

int uart_init(uart_t uart, uint32_t baudrate, uart_rx_cb_t rx_cb, void *arg)
{
    assert(uart < UART_NUMOF);

    vcuart_config_reset(uart);

    /* enable uart clock */
    uart_poweron(uart);

    vcuart_config_mode(uart, UARTMODE_TXRX);
    vcuart_config_firstbit(uart, UARTFIRSTBIT_LSB);
    vcuart_config_baudrate(uart, baudrate);

    /* setup default uart mode */
    uart_mode(uart, UART_DATA_BITS_8, UART_PARITY_NONE, UART_STOP_BITS_1);

    vcuart_config_fifo_softrst(uart, false);
    vcuart_config_fifo_ovmode(uart, false);
    vcuart_config_fifo_txlevel(uart, UARTFIFO_TXLVL_7);
    vcuart_config_fifo_rxlevel(uart, UARTFIFO_RXLVL_0);

    /* save ISR context */
    isr_uart_ctx[uart].rx_cb = rx_cb;
    isr_uart_ctx[uart].arg = arg;

    /* enable UARTx rx interrupt if applicable */
    if (isr_uart_ctx[uart].rx_cb) {
        /* set uart rx gpio input pull high */
        gpio_init(GPIO_PIN(uart_rxio[uart].port, uart_rxio[uart].pin), GPIO_IN_PU);
        /* enable uart interrupt */
        vcuart_config_enable_int(uart, UARTINT_RX);
        NVIC_EnableIRQ(uart_irqn[uart]);
    }

    /* enable UARTx special function gpio */
    vcsfio_enable_uart(uart);

    return UART_OK;
}

int uart_mode(uart_t uart, uart_data_bits_t data_bits, uart_parity_t parity, uart_stop_bits_t stop_bits)
{
    assert(uart < UART_NUMOF);

    vcuart_config_wordlen(uart, uart_data_bits[data_bits]);
    vcuart_config_stoplen(uart, uart_stop_bits[stop_bits]);
    vcuart_config_parity(uart, uart_parity[parity]);

    return UART_OK;
}

static void send_byte(uart_t uart, uint8_t byte)
{
    vcuart_send_byte(uart, byte);
    while (!vcuart_get_status(uart, UARTSTS_TXDONE));
    vcuart_clear_status(uart, UARTSTS_TXDONE);
}

void uart_write(uart_t uart, const uint8_t *data, size_t len)
{
    assert(uart < UART_NUMOF);

    for (size_t i = 0; i < len; i++) {
        send_byte(uart, data[i]);
    }
}

void uart_poweron(uart_t uart)
{
    assert(uart < UART_NUMOF);

    /* enable UARTx clock */
    vcmisc_config_apb_periph(uart_apbperiph[uart], true);
}

void uart_poweroff(uart_t uart)
{
    assert(uart < UART_NUMOF);

    /* disable UARTx clock */
    vcmisc_config_apb_periph(uart_apbperiph[uart], false);
}

static void irq_uart_handler(uart_t uart)
{
    if (vcuart_get_int_status(uart, UARTINT_RX)) {
        vcuart_clear_int_status(uart, UARTINT_RX);
        isr_uart_ctx[uart].rx_cb(isr_uart_ctx[uart].arg, vcuart_recv_byte(uart));
        /* check if context switch was requested */
        cortexm_isr_end();
    }
}

/* UART interrupt function entry  */

void isr_uart0(void)
{
    irq_uart_handler(UART_DEV(0));
}

void isr_uart1(void)
{
    irq_uart_handler(UART_DEV(1));
}

void isr_uart2(void)
{
    irq_uart_handler(UART_DEV(2));
}

void isr_uart3(void)
{
    irq_uart_handler(UART_DEV(3));
}

void isr_uart4(void)
{
    irq_uart_handler(UART_DEV(4));
}

void isr_uart5(void)
{
    irq_uart_handler(UART_DEV(5));
}

void isr_uart6(void)
{
    irq_uart_handler(UART_DEV(6));
}
