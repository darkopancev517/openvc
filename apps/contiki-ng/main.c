#include <stdio.h>
#include <assert.h>

#include "contiki.h"
#include "sys/platform.h"

#ifndef CONTIKI_NG_SNIFFER
#include "contiki-net.h"
#include "dev/serial-line.h"
#include "services/shell/shell.h"
#include "services/shell/serial-shell.h"
#if MAC_CONF_WITH_TSCH
#include "net/mac/tsch/tsch.h"
#endif /* MAC_CONF_WITH_TSCH */
#if MAC_CONF_WITH_CSMA
#include "net/mac/csma/csma.h"
#endif
#include "sys/node-id.h"
#else
#include "net/netstack.h"
#include "sensniff-io.h"
#endif

#ifndef CONTIKI_NG_SNIFFER
#if NETSTACK_CONF_WITH_IPV6
static uip_ds6_addr_t *lladdr;
#endif

#ifdef DEVICE_ROLE_ROOT
static void print_prefix_6addr(const uip_ipaddr_t *ipaddr)
{
  char buf[UIPLIB_IPV6_MAX_STR_LEN];
  uiplib_ipaddr_snprint(buf, sizeof(buf), ipaddr);
  printf("%s", buf);
}
#endif
#endif

PROCESS_NAME(uart_arch_process);

int main(void)
{
    platform_init_stage_one();

    clock_init();
    rtimer_init();
    process_init();
    process_start(&etimer_process, NULL);
    ctimer_init();

    platform_init_stage_two();

    platform_init_stage_three();

#ifndef CONTIKI_NG_SNIFFER
    serial_line_init();
    serial_shell_init();
    shell_init();

    uint16_t uid = DEVICE_ID;

    linkaddr_node_addr.u8[LINKADDR_SIZE - 1] = (uid & 0xff);
    linkaddr_node_addr.u8[LINKADDR_SIZE - 2] = (uid >> 8);

    node_id_init();
    random_init(node_id);

#if NETSTACK_CONF_WITH_IPV6
    memcpy(&uip_lladdr.addr, &linkaddr_node_addr, sizeof(uip_lladdr.addr));
    process_start(&tcpip_process, NULL);
    lladdr = uip_ds6_get_link_local(-1);
#endif

    netstack_init();

    printf("--- Contiki-NG network stack ---\n");
#ifdef DEVICE_ROLE_ROOT
    printf("- Role: root\n");
#else
    printf("- Role: node\n");
#endif
    printf("- Routing: %s\n", NETSTACK_ROUTING.name);
    printf("- Net: %s\n", NETSTACK_NETWORK.name);
    printf("- MAC: %s\n", NETSTACK_MAC.name);
    printf("- Radio frequency: %lu\n", centauri_get_freq());
    printf("- 802.15.4 PANID: 0x%04x\n", IEEE802154_PANID);
    printf("- 802.15.4 Default channel: %u\n", IEEE802154_DEFAULT_CHANNEL);
    printf("- Node ID: 0x%04x\n", node_id);
    printf("- Link-layer address: ");

    linkaddr_t *laddr = &linkaddr_node_addr;

    if (laddr == NULL) {
        printf("(NULL LL addr)");
    } else {
        unsigned i;
        for (i = 0; i < LINKADDR_SIZE; i++) {
            if (i > 0 && i % 2 == 0) {
                printf(".");
            }
            printf("%02x", laddr->u8[i]);
        }
    }

#if NETSTACK_CONF_WITH_IPV6
    printf("\n");
    char buf[UIPLIB_IPV6_MAX_STR_LEN];
    uiplib_ipaddr_snprint(buf, sizeof(buf), lladdr != NULL ? &lladdr->ipaddr : NULL);
    printf("- Tentative link-local IPv6 address: %s\n", buf);
#endif

#ifdef DEVICE_ROLE_ROOT
    const uip_ipaddr_t *default_prefix = uip_ds6_default_prefix();
    uip_ipaddr_t prefix;
    uip_ip6addr_copy(&prefix, default_prefix);
    if(!NETSTACK_ROUTING.node_is_root()) {
        printf("Setting as DAG root with prefix ");
        print_prefix_6addr(&prefix);
        printf("/64\n");
        NETSTACK_ROUTING.root_set_prefix(&prefix, NULL);
        NETSTACK_ROUTING.root_start();
    }
#endif
#else
    sensniff_io_init();
    NETSTACK_RADIO.init();
#endif

    autostart_start(autostart_processes);

    while (1) {
        uint8_t p = 0;
        do {
            p = process_run();
        } while (p > 0);
    }

    /* should not reach here */

    return 0;
}
