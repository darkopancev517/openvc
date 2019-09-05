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

#define CLOCK_CONF_SECOND (1000)
#define RTIMER_ARCH_SECOND (1000000)

/* TSCH related config ------------------------------------------------------ */
#define US_TO_RTIMERTICKS(x) ((uint32_t)(x))
#define RTIMERTICKS_TO_US(x) ((uint32_t)(x))
#define RTIMERTICKS_TO_US_64(x) ((uint32_t)(x))

#define RADIO_PHY_OVERHEAD (3)
#define RADIO_BYTE_AIR_TIME (32)
#define RADIO_DELAY_BEFORE_TX (US_TO_RTIMERTICKS(500))
#define RADIO_DELAY_BEFORE_RX (US_TO_RTIMERTICKS(250))
#define RADIO_DELAY_BEFORE_DETECT (0)

/* Frame filtering done in software */
#define TSCH_CONF_HW_FRAME_FILTERING  (0)
/* -------------------------------------------------------------------------- */

#ifdef CONTIKI_NG_SNIFFER
#define NETSTACK_CONF_WITH_NULLNET 1
#define ROUTING_CONF_NULLROUTING 1
#define NETSTACK_CONF_MAC sensniff_mac_driver
#define NETSTACK_CONF_RADIO centauri_driver
#define centauri_driver_max_payload_len CENTAURI_PAYLOAD_SIZE
#else
#define NETSTACK_CONF_RADIO centauri_driver
#define centauri_driver_max_payload_len CENTAURI_PAYLOAD_SIZE
#endif

typedef unsigned long clock_time_t;
typedef unsigned int uip_stats_t;

#ifdef __cplusplus
}
#endif

#endif /* CONTIKI_CONF_H */
