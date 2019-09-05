#include <stdio.h>
#include <string.h>

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
static volatile int overflow = 0;

process_event_t serial_line_event_message;

PROCESS(serial_line_process, "Serial driver");

static void print_prompt(void)
{
    putchar('>');
    putchar(' ');
    fflush(stdout);
}

static void new_line(void)
{
    putchar('\r');
    putchar('\n');
}

static void white_tape_char(void)
{
    putchar('\b');
    putchar(' ');
    putchar('\b');
}

int serial_line_input_byte(unsigned char c)
{
    if (c == '\n' || c == '\r') {
        if (!overflow) {
            ringbuf_put(&rxbuf, END);
        } else {
            ringbuf_get(&rxbuf);
            if (ringbuf_put(&rxbuf, END) != 0) {
                overflow = 0;
            }
        }
        new_line();
        process_poll(&serial_line_process);
    }  else if (c == 0x08 || c == 0x7f) {
        if (ringbuf_get(&rxbuf) != -1) {
            white_tape_char();
        }
    } else {
        if (!overflow) {
            if (ringbuf_put(&rxbuf, c) == 0) {
                overflow = 1;
            } else {
                putchar(c);
            }
        }
    }
    fflush(stdout);
    return 0;
}

PROCESS_THREAD(serial_line_process, ev, data)
{
    static char buf[BUFSIZE];
    static int ptr;

    PROCESS_BEGIN();

    serial_line_event_message = process_alloc_event();
    ptr = 0;

    print_prompt();

    while(1) {
        /* Fill application buffer until newline or empty */
        int c = ringbuf_get(&rxbuf);
        
        if (c == -1) {
            /* Buffer empty, wait for poll */
            PROCESS_YIELD();
        } else {
            if (c != END) {
                if (ptr < BUFSIZE-1) {
                    buf[ptr++] = (uint8_t)c;
                } else {
                    /* Ignore character (wait for EOL) */
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
                print_prompt();
            }
        }
    }

    PROCESS_END();
}

void serial_line_init(void)
{
  ringbuf_init(&rxbuf, rxbuf_data, sizeof(rxbuf_data));
  process_start(&serial_line_process, NULL);
}
