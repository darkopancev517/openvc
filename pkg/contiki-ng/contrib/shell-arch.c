#include <string.h>
#include <stdio.h>

#include "dev/serial-line.h"
#include "lib/ringbuf.h"

#ifdef SERIAL_LINE_CONF_BUFSIZE
#define BUFSIZE SERIAL_LINE_CONF_BUFSIZE
#else /* SERIAL_LINE_CONF_BUFSIZE */
#define BUFSIZE 128
#endif /* SERIAL_LINE_CONF_BUFSIZE */

#if (BUFSIZE & (BUFSIZE - 1)) != 0
#error SERIAL_LINE_CONF_BUFSIZE must be a power of two (i.e., 1, 2, 4, 8, 16, 32, 64, ...).
#error Change SERIAL_LINE_CONF_BUFSIZE in contiki-conf.h.
#endif

#ifndef END
#define END 0x0a
#endif

static struct ringbuf rxbuf;
static uint8_t rxbuf_data[BUFSIZE];

PROCESS(serial_line_process, "Serial driver");

process_event_t serial_line_event_message;

PROCESS_THREAD(serial_line_process, ev, data)
{
    static char buf[BUFSIZE];
    static int ptr;

    PROCESS_BEGIN();

    serial_line_event_message = process_alloc_event();
    ptr = 0;

    while (1) {
        int c = ringbuf_get(&rxbuf);
        if (c == -1) {
            PROCESS_YIELD();
        } else {
            if (c != END) {
                if (ptr < (BUFSIZE - 1)) {
                    buf[ptr++] = (uint8_t)c;
                } else {
                    /* Ignore char (wait for EOL) */
                }
            } else {
                /* Terminate */
                buf[ptr++] = (uint8_t)'\0';

                /* Broadcast event */
                process_post(PROCESS_BROADCAST, serial_line_event_message, buf);

                /* Wait until all processes have handled the serial line event */
                if (process_post(PROCESS_CURRENT(), PROCESS_EVENT_CONTINUE, NULL) == PROCESS_ERR_OK) {
                    PROCESS_WAIT_EVENT_UNTIL(ev == PROCESS_EVENT_CONTINUE);
                }
                ptr = 0;
            }
        }
    }

    PROCESS_END();
}

void serial_line_input(int argc, char **argv)
{
    char argbuf[48];
    uint8_t overflow = 0;

    for (int i = 0; i < argc; i++) {
        memset(argbuf, '\0', sizeof(argbuf));
        strcpy(argbuf, argv[i]);
        for (int j = 0; j < sizeof(argbuf); j++) {
            if (argbuf[j] != '\0') {
                if (!overflow) {
                    if (ringbuf_put(&rxbuf, argbuf[j]) == 0) {
                        overflow = 1;
                    }
                }
            } else {
                break;
            }
        }
        if (i != argc) {
            /* add space in between argv */
            if (!overflow) {
                if (ringbuf_put(&rxbuf, ' ') == 0) {
                    overflow = 1;
                }
            }
        }
    }

    /* put end char as marker */
    if (!overflow) {
        if (ringbuf_put(&rxbuf, END) == 0) {
            overflow = 1;
        }
    }

    if (!overflow) {
        process_poll(&serial_line_process);
    }
}

void serial_line_init(void)
{
    ringbuf_init(&rxbuf, rxbuf_data, sizeof(rxbuf_data));
    process_start(&serial_line_process, NULL);
}
