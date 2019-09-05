SRCS_PKG_CONTIKI_NG_CONTRIB += $(addprefix contiki-ng/contrib/,\
    clock.c \
    int-master.c \
    platform.c \
    radio.c \
    random.c \
    rtimer-arch.c \
    shell-arch.c \
    slip-arch.c \
    watchdog.c \
    )

ifeq ($(PKG_CONTIKI_NG_MAKE_SNIFFER),1)
SRCS_PKG_CONTIKI_NG_CONTRIB += $(addprefix contiki-ng/contrib/sniffer/,\
    sensniff-io.c \
    sensniff-mac.c \
    sensniff.c \
    )
endif

SRCS_PKG_CONTIKI_NG_SYS += $(addprefix contiki-ng/repo/os/sys/,\
    autostart.c \
    compower.c \
    ctimer.c \
    energest.c \
    etimer.c \
    log.c \
    mutex.c \
    node-id.c \
    process.c \
    rtimer.c \
    stack-check.c \
    stimer.c \
    timer.c \
    )

SRCS_PKG_CONTIKI_NG_LIB += $(addprefix contiki-ng/repo/os/lib/,\
    aes-128.c \
    assert.c \
    ccm-star.c \
    circular-list.c \
    crc16.c \
    dbl-circ-list.c \
    dbl-list.c \
    heapmem.c \
    ifft.c \
    list.c \
    memb.c \
    ringbuf.c \
    ringbufindex.c \
    trickle-timer.c \
    )

SRCS_PKG_CONTIKI_NG_DEV += $(addprefix contiki-ng/repo/os/dev/,\
    nullradio.c \
    slip.c \
    )

SRCS_PKG_CONTIKI_NG_ANTELOPE += $(wildcard contiki-ng/repo/os/storage/antelope/,*.c)
SRCS_PKG_CONTIKI_NG_CFS += $(wildcard contiki-ng/repo/os/storage/cfs/,*.c)

ifeq ($(PKG_CONTIKI_NG_MAKE_SNIFFER),1)
SRCS_PKG_CONTIKI_NG_NET += $(addprefix contiki-ng/repo/os/net/,\
    linkaddr.c \
    packetbuf.c \
    )
else
SRCS_PKG_CONTIKI_NG_NET += $(addprefix contiki-ng/repo/os/net/,\
    link-stats.c \
    linkaddr.c \
    nbr-table.c \
    net-debug.c \
    netstack.c \
    packetbuf.c \
    queuebuf.c \
    )
endif

SRCS_PKG_CONTIKI_NG_NET_MAC += $(addprefix contiki-ng/repo/os/net/mac/,\
    mac-sequence.c \
    mac.c \
    )

SRCS_PKG_CONTIKI_NG_NET_MAC_FRAMER += $(addprefix contiki-ng/repo/os/net/mac/framer/,\
    frame802154.c \
    frame802154e-ie.c \
    framer-802154.c \
    nullframer.c \
    )

SRCS_PKG_CONTIKI_NG_NET_MAC_CSMA += $(addprefix contiki-ng/repo/os/net/mac/csma/,\
    csma-output.c \
    csma-security.c \
    csma.c \
    )

SRCS_PKG_CONTIKI_NG_NET_MAC_NULLMAC += $(addprefix contiki-ng/repo/os/net/mac/nullmac/,\
    nullmac.c \
    )

SRCS_PKG_CONTIKI_NG_NET_MAC_BLE += $(addprefix contiki-ng/repo/os/net/mac/ble/,\
    ble-l2cap.c \
    )

SRCS_PKG_CONTIKI_NG_NET_MAC_TSCH += $(addprefix contiki-ng/repo/os/net/mac/tsch/,\
    tsch-adaptive-timesync.c \
    tsch-log.c \
    tsch-packet.c \
    tsch-queue.c \
    tsch-rpl.c \
    tsch-schedule.c \
    tsch-security.c \
    tsch-slot-operation.c \
    tsch-timeslot-timing.c \
    tsch-stats.c \
    tsch.c \
    )

SRCS_PKG_CONTIKI_NG_NET_MAC_TSCH_SIXTOP += $(addprefix contiki-ng/repo/os/net/mac/tsch/sixtop/,\
    sixp-nbr.c \
    sixp-pkt.c \
    sixp-trans.c \
    sixp.c \
    sixtop.c \
    )

SRCS_PKG_CONTIKI_NG_NET_NULLNET += $(addprefix contiki-ng/repo/os/net/nullnet/,\
    nullnet.c \
    )

SRCS_PKG_CONTIKI_NG_NET_ROUTING_NULLROUTING += $(addprefix contiki-ng/repo/os/net/routing/nullrouting/,\
    nullrouting.c \
    )

SRCS_PKG_CONTIKI_NG_NET_ROUTING_RPL_CLASSIC += $(addprefix contiki-ng/repo/os/net/routing/rpl-classic/,\
    rpl-dag-root.c \
    rpl-dag.c \
    rpl-ext-header.c \
    rpl-icmp6.c \
    rpl-mrhof.c \
    rpl-nbr-policy.c \
    rpl-of0.c \
    rpl-timers.c \
    rpl.c \
    )

SRCS_PKG_CONTIKI_NG_NET_ROUTING_RPL_LITE += $(addprefix contiki-ng/repo/os/net/routing/rpl-lite/,\
    rpl-dag-root.c \
    rpl-dag.c \
    rpl-ext-header.c \
    rpl-icmp6.c \
    rpl-mrhof.c \
    rpl-nbr-policy.c \
    rpl-neighbor.c \
    rpl-of0.c \
    rpl-timers.c \
    rpl.c \
    )

SRCS_PKG_CONTIKI_NG_NET_IPV6 += $(addprefix contiki-ng/repo/os/net/ipv6/,\
    ip64-addr.c \
    psock.c \
    resolv.c \
    sicslowpan.c \
    simple-udp.c \
    tcp-socket.c \
    tcpip.c \
    udp-socket.c \
    uip-ds6-nbr.c \
    uip-ds6-route.c \
    uip-ds6.c \
    uip-icmp6.c \
    uip-nameserver.c \
    uip-nd6.c \
    uip-packetqueue.c \
    uip-sr.c \
    uip-udp-packet.c \
    uip6.c \
    uipbuf.c \
    uiplib.c \
    )

SRCS_PKG_CONTIKI_NG_NET_IPV6_MULTICAST += $(addprefix contiki-ng/repo/os/net/ipv6/multicast/,\
    esmrf.c \
    roll-tm.c \
    smrf.c \
    uip-mcast6-route.c \
    uip-mcast6-stats.c \
    )

SRCS_PKG_CONTIKI_NG_NET_APP_LAYER_COAP += $(addprefix contiki-ng/repo/os/net/app-layer/coap/,\
    coap-block1.c \
    coap-blocking-api.c \
    coap-callback-api.c \
    coap-engine.c \
    coap-keystore-simple.c \
    coap-log.c \
    coap-observe-client.c \
    coap-observe.c \
    coap-res-well-known-core.c \
    coap-separate.c \
    coap-timer-default.c \
    coap-timer.c \
    coap-transactions.c \
    coap-uip.c \
    coap.c \
    )

SRCS_PKG_CONTIKI_NG_NET_APP_LAYER_COAP_TINYDTLS_SUPPORT += \
    $(addprefix contiki-ng/repo/os/net/app-layer/coap/tinydtls-support/,\
    dtls-support.c \
    )

SRCS_PKG_CONTIKI_NG_NET_APP_LAYER_HTTP_SOCKET += \
    $(addprefix contiki-ng/repo/os/net/app-layer/http-socket/,\
    http-socket.c \
    websocket-http-client.c \
    websocket.c \
    )

SRCS_PKG_CONTIKI_NG_NET_APP_LAYER_HTTPD_WS += \
    $(addprefix contiki-ng/repo/os/net/app-layer/httpd-ws/,\
    httpd-ws.c \
    )

SRCS_PKG_CONTIKI_NG_NET_APP_LAYER_MQTT += \
    $(addprefix contiki-ng/repo/os/net/app-layer/mqtt/,\
    mqtt.c \
    )

SRCS_PKG_CONTIKI_NG_SERVICES_IP64 += $(addprefix contiki-ng/repo/os/services/ip64/,\
    ip64-addrmap.c \
    ip64-arp.c \
    ip64-dhcpc.c \
    ip64-dns64.c \
    ip64-eth-interface.c \
    ip64-eth.c \
    ip64-ipv4-dhcp.c \
    ip64-null-driver.c \
    ip64-slip-interface.c \
    ip64-special-ports.c \
    ip64.c \
    )

SRCS_PKG_CONTIKI_NG_SERVICES_SHELL += $(addprefix contiki-ng/repo/os/services/shell/,\
    serial-shell.c \
    shell-commands.c \
    shell.c \
    )

OBJS_PKG_CONTIKI_NG += $(addprefix $(BUILD)/,$(SRCS_PKG_CONTIKI_NG_CONTRIB:.c=.o))
OBJS_PKG_CONTIKI_NG += $(addprefix $(BUILD)/,$(SRCS_PKG_CONTIKI_NG_SYS:.c=.o))
OBJS_PKG_CONTIKI_NG += $(addprefix $(BUILD)/,$(SRCS_PKG_CONTIKI_NG_DEV:.c=.o))
OBJS_PKG_CONTIKI_NG += $(addprefix $(BUILD)/,$(SRCS_PKG_CONTIKI_NG_LIB:.c=.o))
OBJS_PKG_CONTIKI_NG += $(addprefix $(BUILD)/,$(SRCS_PKG_CONTIKI_NG_NET:.c=.o))

# ==============================================================================

ifneq ($(PKG_CONTIKI_NG_MAKE_SNIFFER),1)

OBJS_PKG_CONTIKI_NG += $(addprefix $(BUILD)/,$(SRCS_PKG_CONTIKI_NG_NET_MAC:.c=.o))
OBJS_PKG_CONTIKI_NG += $(addprefix $(BUILD)/,$(SRCS_PKG_CONTIKI_NG_NET_MAC_FRAMER:.c=.o))
OBJS_PKG_CONTIKI_NG += $(addprefix $(BUILD)/,$(SRCS_PKG_CONTIKI_NG_SERVICES_SHELL:.c=.o))

# APP make ---------------------------------------------------------------------

ifeq ($(PKG_CONTIKI_NG_MAKE_APP),MAKE_APP_COAP)
OBJS_PKG_CONTIKI_NG += $(addprefix $(BUILD)/,$(SRCS_PKG_CONTIKI_NG_NET_APP_LAYER_COAP:.c=.o))
endif

ifeq ($(PKG_CONTIKI_NG_MAKE_APP),MAKE_APP_MQTT)
OBJS_PKG_CONTIKI_NG += $(addprefix $(BUILD)/,$(SRCS_PKG_CONTIKI_NG_NET_APP_LAYER_MQTT:.c=.o))
endif

# MAC make ---------------------------------------------------------------------

ifeq ($(PKG_CONTIKI_NG_MAKE_MAC),MAKE_MAC_NULLMAC)
OBJS_PKG_CONTIKI_NG += $(addprefix $(BUILD)/,$(SRCS_PKG_CONTIKI_NG_NET_MAC_NULLMAC:.c=.o))
endif

ifeq ($(PKG_CONTIKI_NG_MAKE_MAC),MAKE_MAC_CSMA)
OBJS_PKG_CONTIKI_NG += $(addprefix $(BUILD)/,$(SRCS_PKG_CONTIKI_NG_NET_MAC_CSMA:.c=.o))
endif

ifeq ($(PKG_CONTIKI_NG_MAKE_MAC),MAKE_MAC_TSCH)
OBJS_PKG_CONTIKI_NG += $(addprefix $(BUILD)/,$(SRCS_PKG_CONTIKI_NG_NET_MAC_TSCH:.c=.o))
endif

ifeq ($(PKG_CONTIKI_NG_MAKE_MAC),MAKE_MAC_BLE)
OBJS_PKG_CONTIKI_NG += $(addprefix $(BUILD)/,$(SRCS_PKG_CONTIKI_NG_NET_MAC_BLE:.c=.o))
endif

# Network make -----------------------------------------------------------------

ifeq ($(PKG_CONTIKI_NG_MAKE_NET),MAKE_NET_NULLNET)
OBJS_PKG_CONTIKI_NG += $(addprefix $(BUILD)/,$(SRCS_PKG_CONTIKI_NG_NET_NULLNET:.c=.o))
endif

ifeq ($(PKG_CONTIKI_NG_MAKE_NET),MAKE_NET_IPV6)
OBJS_PKG_CONTIKI_NG += $(addprefix $(BUILD)/,$(SRCS_PKG_CONTIKI_NG_NET_IPV6:.c=.o))
endif

# Routing make -----------------------------------------------------------------

ifeq ($(PKG_CONTIKI_NG_MAKE_ROUTING),MAKE_ROUTING_NULLROUTING)
OBJS_PKG_CONTIKI_NG += $(addprefix $(BUILD)/,$(SRCS_PKG_CONTIKI_NG_NET_ROUTING_NULLROUTING:.c=.o))
endif

ifeq ($(PKG_CONTIKI_NG_MAKE_ROUTING),MAKE_ROUTING_RPL_CLASSIC)
OBJS_PKG_CONTIKI_NG += $(addprefix $(BUILD)/,$(SRCS_PKG_CONTIKI_NG_NET_ROUTING_RPL_CLASSIC:.c=.o))
endif

ifeq ($(PKG_CONTIKI_NG_MAKE_ROUTING),MAKE_ROUTING_RPL_LITE)
OBJS_PKG_CONTIKI_NG += $(addprefix $(BUILD)/,$(SRCS_PKG_CONTIKI_NG_NET_ROUTING_RPL_LITE:.c=.o))
endif

# ------------------------------------------------------------------------------

endif
# ==============================================================================

OBJS_DIR += $(sort $(dir $(OBJS_PKG_CONTIKI_NG)))

LIB_PKG_CONTIKI_NG_ARCHIVE = $(BUILD)/$(LIB_PKG_CONTIKI_NG)
LIB_PKG_CONTIKI_NG_OBJS += $(OBJS_PKG_CONTIKI_NG)

ARCHIVE_FILES += $(LIB_PKG_CONTIKI_NG_ARCHIVE)

all: | $(OBJS_DIR) $(ARCHIVE_FILES)
$(OBJS_DIR):
	$(MKDIR) -p $@

$(BUILD)/%.o: %.c
	$(ECHO) "CC $<"
	$(CC) -DFILE_RELATIVE=\"$(patsubst $(TOP)/%,%,$(abspath $<))\" \
		  -DFILE_NOPATH=\"$(notdir $<)\" \
		  $(CFLAGS) -c -o $@ $<

$(BUILD)/%.a:
	$(ECHO) "AR $@"
	$(AR) -cr $@ $^

$(LIB_PKG_CONTIKI_NG_ARCHIVE): $(LIB_PKG_CONTIKI_NG_OBJS)

-include $(OBJS_PKG_CONTIKI_NG:%.o=%.d)
