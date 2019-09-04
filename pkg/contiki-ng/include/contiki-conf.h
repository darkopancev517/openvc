#ifndef CONTIKI_CONF_H
#define CONTIKI_CONF_H

#include <stdint.h>
#include <string.h>
#include <inttypes.h>

#include "centauri.h"
#include "project-conf.h"

#ifdef __cplusplus
extern "C" {
#endif

#define CLOCK_CONF_SECOND 1000
#define RTIMER_ARCH_SECOND 1000

#define NETSTACK_CONF_RADIO centauri_driver
#define centauri_driver_max_payload_len CENTAURI_PAYLOAD_SIZE

typedef unsigned long clock_time_t;
typedef unsigned int uip_stats_t;

#ifdef __cplusplus
}
#endif

#endif /* CONTIKI_CONF_H */
