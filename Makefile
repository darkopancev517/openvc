###################################################
# MAKE ARGS
###################################################
ifeq ($(v), 1)
Q =
else
Q = @
endif

DEVELHELP ?= 0

###################################################
# Commands
###################################################
export CC = $(Q)arm-none-eabi-gcc
export AS = $(Q)arm-none-eabi-gcc
export LD = $(Q)arm-none-eabi-ld
export AR = $(Q)arm-none-eabi-ar
export CPP = $(Q)arm-none-eabi-g++
export SIZE = $(Q)arm-none-eabi-size
export STRIP = $(Q)arm-none-eabi-strip -s
export OBJCOPY = $(Q)arm-none-eabi-objcopy
export OBJDUMP = $(Q)arm-none-eabi-objdump
export RM = $(Q)rm
export MV = $(Q)mv
export MKDIR = $(Q)mkdir
export ECHO = $(Q)@echo
ifeq ($(v),1)
export MAKE = $(Q)make
else
export MAKE = $(Q)make -s
endif
export CP = $(Q)cp
export TOP = $(shell pwd)

OPENVC = openvc

###################################################
# Targets
###################################################
export APPS ?= test
export BOARD ?= vc7300mtr

ifeq ($(BOARD),$(filter $(BOARD),vc7300mtr))
export CPU = sirius
export CORTEXM = m3
export ARCH = armv7-m
endif

BUILD = $(TOP)/build/$(CPU)

###################################################
# Images
###################################################
FIRMWARE = firmware

###################################################
# Contiki-ng pkg information
###################################################
PKG_CONTIKI_NG_INC += -I$(TOP)/pkg/contiki-ng/include
PKG_CONTIKI_NG_INC += -I$(TOP)/pkg/contiki-ng/repo/os
PKG_CONTIKI_NG_INC += -I$(TOP)/pkg/contiki-ng/repo/os/net
PKG_CONTIKI_NG_INC += -I$(TOP)/pkg/contiki-ng/repo/os/net/ipv6
PKG_CONTIKI_NG_INC += -I$(TOP)/pkg/contiki-ng/repo/os/services
PKG_CONTIKI_NG_INC += -I$(TOP)/pkg/contiki-ng/repo/os/lib

# APP make ---------------------------------------------------------------------

export MAKE_APP_COAP := 0
export MAKE_APP_MQTT := 1

export PKG_CONTIKI_NG_MAKE_APP ?= MAKE_APP_COAP

ifeq ($(PKG_CONTIKI_NG_MAKE_APP),MAKE_APP_COAP)
PKG_CONTIKI_NG_CFLAGS += -DAPP_CONF_WITH_COAP=1
endif

ifeq ($(PKG_CONTIKI_NG_BUILD_MAKE_APP),MAKE_APP_MQTT)
PKG_CONTIKI_NG_CFLAGS += -DAPP_CONF_WITH_MQTT=1
endif

# MAC make ---------------------------------------------------------------------

export MAKE_MAC_NULLMAC := 0
export MAKE_MAC_CSMA    := 1
export MAKE_MAC_TSCH    := 2
export MAKE_MAC_BLE     := 3
export MAKE_MAC_OTHER   := 4

export PKG_CONTIKI_NG_MAKE_MAC ?= MAKE_MAC_CSMA

ifeq ($(PKG_CONTIKI_NG_MAKE_MAC),MAKE_MAC_NULLMAC)
PKG_CONTIKI_NG_CFLAGS += -DMAC_CONF_WITH_NULLMAC=1
endif

ifeq ($(PKG_CONTIKI_NG_MAKE_MAC),MAKE_MAC_CSMA)
PKG_CONTIKI_NG_CFLAGS += -DMAC_CONF_WITH_CSMA=1
endif

ifeq ($(PKG_CONTIKI_NG_MAKE_MAC),MAKE_MAC_TSCH)
PKG_CONTIKI_NG_CFLAGS += -DMAC_CONF_WITH_TSCH=1
endif

ifeq ($(PKG_CONTIKI_NG_MAKE_MAC),MAKE_MAC_BLE)
PKG_CONTIKI_NG_CFLAGS += -DMAC_CONF_WITH_BLE=1
endif

ifeq ($(PKG_CONTIKI_NG_MAKE_MAC),MAKE_MAC_OTHER)
PKG_CONTIKI_NG_CFLAGS += -DMAC_CONF_WITH_OTHER=1
endif

PKG_CONTIKI_NG_CFLAGS += -DPKG_CONTIKI_NG

# Network make -----------------------------------------------------------------

export MAKE_NET_NULLNET := 0
export MAKE_NET_IPV6    := 1
export MAKE_NET_OTHER   := 2

export PKG_CONTIKI_NG_MAKE_NET ?= MAKE_NET_IPV6

ifeq ($(PKG_CONTIKI_NG_MAKE_NET),MAKE_NET_NULLNET)
PKG_CONTIKI_NG_CFLAGS += -DNETSTACK_CONF_WITH_NULLNET=1
endif

ifeq ($(PKG_CONTIKI_NG_MAKE_NET),MAKE_NET_IPV6)
PKG_CONTIKI_NG_CFLAGS += -DNETSTACK_CONF_WITH_IPV6=1
endif

ifeq ($(PKG_CONTIKI_NG_MAKE_NET),MAKE_NET_OTHER)
PKG_CONTIKI_NG_CFLAGS += -DNETSTACK_CONF_WITH_OTHER=1
endif

# Routing make -----------------------------------------------------------------

export MAKE_ROUTING_NULLROUTING := 0
export MAKE_ROUTING_RPL_CLASSIC := 1
export MAKE_ROUTING_RPL_LITE    := 2

export PKG_CONTIKI_NG_MAKE_ROUTING ?= MAKE_ROUTING_RPL_CLASSIC

ifeq ($(PKG_CONTIKI_NG_MAKE_ROUTING),MAKE_ROUTING_NULLROUTING)
PKG_CONTIKI_NG_CFLAGS += -DROUTING_CONF_NULLROUTING=1
endif

ifeq ($(PKG_CONTIKI_NG_MAKE_ROUTING),MAKE_ROUTING_RPL_CLASSIC)
PKG_CONTIKI_NG_CFLAGS += -DROUTING_CONF_RPL_CLASSIC=1
endif

ifeq ($(PKG_CONTIKI_NG_MAKE_ROUTING),MAKE_ROUTING_RPL_LITE)
PKG_CONTIKI_NG_CFLAGS += -DROUTING_CONF_RPL_LITE=1
endif

###################################################
# Pkg build
###################################################
PKG_CFLAGS += $(PKG_CONTIKI_NG_CFLAGS)

###################################################
# BUILD variables
###################################################
# include modules
include drivers/module.mk
include sys/module.mk
include pkg/module.mk

INC += -I$(TOP)
INC += -I$(TOP)/core/include
INC += -I$(TOP)/cpu/cortexm/include
INC += -I$(TOP)/cpu/cortexm/include/vendor
INC += -I$(TOP)/cpu/$(CPU)/include
INC += -I$(TOP)/cpu/$(CPU)/vendor/include
INC += -I$(TOP)/drivers/include
INC += -I$(TOP)/boards/$(BOARD)/include
INC += -I$(TOP)/sys/include
INC += -I$(TOP)/apps/$(APPS)
INC += $(PKG_CONTIKI_NG_INC)

DEF += -DCPU_ARCH_CORTEX_$(shell echo $(CORTEXM) | tr a-z A-Z)

ifeq ($(DEVELHELP),1)
DEF += -DDEVELHELP
endif

CFLAGS += -fdata-sections -ffunction-sections -fno-builtin -fshort-enums
CFLAGS += -O0
CFLAGS += -Wno-implicit-fallthrough -Wno-unused-parameter
CFLAGS += -mcpu=cortex-$(CORTEXM) -mlittle-endian -mthumb -mfloat-abi=soft
CFLAGS += -march=$(ARCH) -mno-unaligned-access
CFLAGS += -Wall -Werror
CFLAGS += -std=c99
CFLAGS += $(DEF)
CFLAGS += $(PKG_CFLAGS)
CFLAGS += $(DRIVERS_CFLAGS)
CFLAGS += $(INC)

LDFLAGS += -fdata-sections -ffunction-sections -fno-builtin -fshort-enums
LDFLAGS += -O0
LDFLAGS += -Wno-implicit-fallthrough -Wno-unused-parameter
LDFLAGS += -mcpu=cortex-$(CORTEXM) -mlittle-endian -mthumb -mfloat-abi=soft
LDFLAGS += -march=$(ARCH) -mno-unaligned-access
LDFLAGS += -static -lgcc -nostartfiles
LDFLAGS += -specs=nano.specs -Wl,--gc-sections

###################################################
# BUILD path for each modules
###################################################
FIRMWARE_BUILD = $(BUILD)/$(FIRMWARE)

###################################################
# Libraries definitions
###################################################
export LIB_CORE = libcore.a
export LIB_CPU = libcpu.a
export LIB_BOARD = libboard.a
export LIB_DRIVERS_NVSETS = libdrivers_nvsets.a
export LIB_DRIVERS_CENTAURI = libdrivers_centauri.a
export LIB_SYS_STDIO_UART = libsys_stdio_uart.a
export LIB_SYS_SYSCALLS = libsys_syscalls.a
export LIB_SYS_TSRB = libsys_tsrb.a
export LIB_SYS_XTIMER = libsys_xtimer.a
export LIB_SYS_DIV = libsys_div.a
export LIB_SYS_TIMEX = libsys_timex.a
export LIB_SYS_ISRPIPE = libsys_isrpipe.a
export LIB_SYS_SHELL = libsys_shell.a
export LIB_SYS_SHELL_COMMANDS = libsys_shell_commands.a
export LIB_SYS_PS = libsys_ps.a
export LIB_SYS_AUTO_INIT = libsys_auto_init.a
export LIB_PKG_CONTIKI_NG = libpkg_contiki_ng.a
export LIB_APPS = libapps.a

###################################################
# Libraries
###################################################
FIRMWARE_LIBS += $(FIRMWARE_BUILD)/core/$(LIB_CORE)
FIRMWARE_LIBS += $(FIRMWARE_BUILD)/cpu/$(LIB_CPU)
FIRMWARE_LIBS += $(FIRMWARE_BUILD)/board/$(LIB_BOARD)
ifeq ($(MODULE_SYSCALLS),1)
FIRMWARE_LIBS += $(FIRMWARE_BUILD)/sys/$(LIB_SYS_SYSCALLS)
endif
ifeq ($(MODULE_STDIO_UART),1)
FIRMWARE_LIBS += $(FIRMWARE_BUILD)/sys/$(LIB_SYS_STDIO_UART)
endif
FIRMWARE_LIBS += $(FIRMWARE_BUILD)/apps/$(LIB_APPS)

###################################################
# Linker script and image info
###################################################
FIRMWARE_LDSCRIPT = cpu/$(CPU)/ldscripts/$(CPU).ld
FIRMWARE_IMAGE = $(FIRMWARE_BUILD)/$(FIRMWARE)

####################################################
# Make rules
####################################################
all: $(OPENVC)

$(BUILD):
	$(MKDIR) -p $@

FIRMWARE_OBJS:
	$(MAKE) -C core BUILD="$(FIRMWARE_BUILD)/core" CFLAGS="$(CFLAGS) -MD -MP"
	$(MAKE) -C cpu BUILD="$(FIRMWARE_BUILD)/cpu" CFLAGS="$(CFLAGS) -MD -MP"
	$(MAKE) -C boards BUILD="$(FIRMWARE_BUILD)/board" CFLAGS="$(CFLAGS) -MD -MP"
	$(MAKE) -C sys BUILD="$(FIRMWARE_BUILD)/sys" CFLAGS="$(CFLAGS) -MD -MP"
	$(MAKE) -C apps BUILD="$(FIRMWARE_BUILD)/apps"  CFLAGS="$(CFLAGS) -MD -MP"

$(FIRMWARE_IMAGE).elf: $(FIRMWARE_LIBS)
	$(CC) $(LDFLAGS) $(patsubst %,-L%,$(patsubst %/,%,$(sort $(dir $(FIRMWARE_LIBS)))))  \
	-Wl,--whole-archive $(patsubst %,-l%,$(patsubst lib%,%,$(sort $(basename $(notdir $(FIRMWARE_LIBS)))))) \
	-Wl,--no-whole-archive -T$(FIRMWARE_LDSCRIPT) \
	-Wl,-Map,$(FIRMWARE_BUILD)/firmware.map -o $@

$(FIRMWARE_IMAGE).bin: $(FIRMWARE_IMAGE).elf
	$(OBJCOPY) -O binary $< $@

$(FIRMWARE_IMAGE).lst: $(FIRMWARE_IMAGE).elf
	$(OBJDUMP) -h -S $< > $@

$(FIRMWARE): FIRMWARE_OBJS $(FIRMWARE_IMAGE).bin $(FIRMWARE_IMAGE).lst
	$(SIZE) --format=berkeley $(FIRMWARE_IMAGE).elf
	@mv $(FIRMWARE_IMAGE).elf $(FIRMWARE_IMAGE).bin $(BUILD)

$(OPENVC): $(FIRMWARE) | $(BUILD)

.PHONY: all clean

clean:
	-rm -rf $(BUILD)
