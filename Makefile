# Set verbosity
ifeq ($(v), 1)
Q =
else
Q = @
endif

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
export TOP = $(shell pwd)

OPENVC = openvc

###################################################
# Targets
###################################################
export APPS ?= shell
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
# BUILD variables
###################################################
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

DEF += -DCPU_ARCH_CORTEX_$(shell echo $(CORTEXM) | tr a-z A-Z)
ifeq ($(DEVELHELP),1)
DEF += -DNDEBUG
endif

CFLAGS += -fdata-sections -ffunction-sections -fno-builtin -fshort-enums
CFLAGS += -O0
CFLAGS += -Wno-implicit-fallthrough -Wno-unused-parameter
CFLAGS += -mcpu=cortex-$(CORTEXM) -mlittle-endian -mthumb -mfloat-abi=soft
CFLAGS += -march=$(ARCH) -mno-unaligned-access
CFLAGS += -Wall -Werror
CFLAGS += -std=c99
CFLAGS += $(DEF)
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
export LIB_SYS_STDIO_UART = libsys_stdio_uart.a
export LIB_SYS_SYSCALLS = libsys_syscalls.a
export LIB_SYS_TSRB = libsys_tsrb.a
export LIB_SYS_ISRPIPE = libsys_isrpipe.a
export LIB_SYS_SHELL = libsys_shell.a
export LIB_SYS_SHELL_COMMANDS = libsys_shell_commands.a
export LIB_SYS_PS = libsys_ps.a
export LIB_APPS = libapps.a

###################################################
# Libraries
###################################################
FIRMWARE_LIBS += $(FIRMWARE_BUILD)/core/$(LIB_CORE)
FIRMWARE_LIBS += $(FIRMWARE_BUILD)/cpu/$(LIB_CPU)
FIRMWARE_LIBS += $(FIRMWARE_BUILD)/board/$(LIB_BOARD)
FIRMWARE_LIBS += $(FIRMWARE_BUILD)/sys/$(LIB_SYS_STDIO_UART)
FIRMWARE_LIBS += $(FIRMWARE_BUILD)/sys/$(LIB_SYS_SYSCALLS)
FIRMWARE_LIBS += $(FIRMWARE_BUILD)/sys/$(LIB_SYS_TSRB)
FIRMWARE_LIBS += $(FIRMWARE_BUILD)/sys/$(LIB_SYS_ISRPIPE)
FIRMWARE_LIBS += $(FIRMWARE_BUILD)/sys/$(LIB_SYS_SHELL)
FIRMWARE_LIBS += $(FIRMWARE_BUILD)/sys/$(LIB_SYS_SHELL_COMMANDS)
FIRMWARE_LIBS += $(FIRMWARE_BUILD)/sys/$(LIB_SYS_PS)
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
