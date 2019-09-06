#include "contiki.h"
#include "dev/serial-line.h"

#include "isrpipe.h"
#include "board.h"

#ifdef CONTIKI_NG_SNIFFER
#include "sensniff-io.h"
#endif

#ifndef CONTIKI_NG_SNIFFER
extern isrpipe_t stdio_uart_isrpipe;
#else
extern isrpipe_t sensniff_uart_isrpipe;
#endif

static char uart_data = 0;

PROCESS(uart_arch_process, "Uart arch process");

PROCESS_THREAD(uart_arch_process, ev, data)
{
    PROCESS_BEGIN();
    while (1) {
        PROCESS_WAIT_EVENT_UNTIL(ev == PROCESS_EVENT_POLL);
#ifndef CONTIKI_NG_SNIFFER
        while (isrpipe_read(&stdio_uart_isrpipe, &uart_data, 1)) {
            serial_line_input_byte((unsigned char)uart_data);
        }
#else
        while (isrpipe_read(&sensniff_uart_isrpipe, &uart_data, 1)) {
            if (sensniff_io_ctx.cb != NULL) {
                sensniff_io_ctx.cb((unsigned char)uart_data);
            }
        }
#endif
    }
    PROCESS_END();
}

void uart_arch_init(void)
{
    process_start(&uart_arch_process, NULL);
}
