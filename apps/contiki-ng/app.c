/* Note: contiki application example */
#ifndef CONTIKI_NG_SNIFFER

#include "contiki.h"

#include <stdio.h> /* For printf() */

PROCESS(app_process, "App process");
AUTOSTART_PROCESSES(&app_process);

PROCESS_THREAD(app_process, ev, data)
{
    static struct etimer timer;

    PROCESS_BEGIN();

    /* Setup a timer that expires after 1 seconds. */
    etimer_set(&timer, CLOCK_SECOND);

    while(1) {
        /* Wait for the periodic timer to expire and then exit */
        PROCESS_WAIT_EVENT_UNTIL(etimer_expired(&timer));
        printf("Contiki-NG app run succeed\n");
        PROCESS_EXIT();
    }

    PROCESS_END();
}

#endif /* #ifndef CONTIKI_NG_SNIFFER */
