# Set verbosity
ifeq ($(v), 1)
Q =
else
Q = @
endif

###################################################
# Commands
###################################################
export CC       = $(Q)arm-none-eabi-gcc
export AS       = $(Q)arm-none-eabi-gcc
export LD       = $(Q)arm-none-eabi-ld
export AR       = $(Q)arm-none-eabi-ar
export CPP      = $(Q)arm-none-eabi-g++
export SIZE     = $(Q)arm-none-eabi-size
export STRIP    = $(Q)arm-none-eabi-strip -s
export OBJCOPY  = $(Q)arm-none-eabi-objcopy
export OBJDUMP  = $(Q)arm-none-eabi-objdump
export RM       = $(Q)rm
export MV       = $(Q)mv
export MKDIR    = $(Q)mkdir
export ECHO     = $(Q)@echo
ifeq ($(v),1)
export MAKE     = $(Q)make
else
export MAKE     = $(Q)make -s
endif
export TOP      = $(shell pwd)

###################################################
# Targets
###################################################
VCRTOS   = vcrtos
CPU  	 = vc7300x
CPU_ARCH = CORTEX_M3
BOARD    = vc7300-meter
APPS 	 = hello_world
BUILD 	 = $(TOP)/build/$(CPU)

###################################################
# Images
###################################################
FIRMWARE = firmware

###################################################
# Directories
###################################################
CORE_DIR     = core
CPU_DIR 	 = cpu/$(CPU)
BOARD_DIR    = boards/$(BOARD)
APPS_DIR     = apps/$(APPS)
FIRMWARE_DIR = $(FIRMWARE)

###################################################
# BUILD variables
###################################################
INC += -I$(TOP)
INC += -I$(TOP)/core/include
INC += -I$(TOP)/cpu/cortexm/include
INC += -I$(TOP)/cpu/cortexm/include/vendor
INC += -I$(TOP)/cpu/$(CPU)/include
INC += -I$(TOP)/cpu/$(CPU)/periph/include
INC += -I$(TOP)/boards/$(BOARD)/include
INC += -I$(TOP)/apps/$(APPS)

DEF += -DCPU_ARCH_$(CPU_ARCH)

CFLAGS += -fdata-sections -ffunction-sections -fno-builtin -fshort-enums
CFLAGS += -O0
CFLAGS += -Wno-implicit-fallthrough -Wno-unused-parameter
ifeq ($(CPU_ARCH),CORTEX_M3)
CFLAGS += -mcpu=cortex-m3 -mlittle-endian -mthumb -mfloat-abi=soft
CFLAGS += -march=armv7-m -mno-unaligned-access
endif
CFLAGS += -Wall -Werror
CFLAGS += -std=c99
CFLAGS += $(DEF)
CFLAGS += $(INC)

LDFLAGS += -fdata-sections -ffunction-sections -fno-builtin -fshort-enums
LDFLAGS += -O0
LDFLAGS += -Wno-implicit-fallthrough -Wno-unused-parameter
ifeq ($(CPU_ARCH),CORTEX_M3)
LDFLAGS += -mcpu=cortex-m3 -mlittle-endian -mthumb -mfloat-abi=soft
LDFLAGS += -march=armv7-m -mno-unaligned-access
endif
LDFLAGS += -static -lgcc -nostartfiles
LDFLAGS += -specs=nano.specs -Wl,--gc-sections

###################################################
# BUILD path for each modules
###################################################
FIRMWARE_BUILD       = $(BUILD)/$(FIRMWARE_DIR)
FIRMWARE_BUILD_CORE  = $(FIRMWARE_BUILD)/$(CORE_DIR)
FIRMWARE_BUILD_CPU   = $(FIRMWARE_BUILD)/$(CPU_DIR)
FIRMWARE_BUILD_BOARD = $(FIRMWARE_BUILD)/$(BOARD_DIR)
FIRMWARE_BUILD_APPS  = $(FIRMWARE_BUILD)/$(APPS_DIR)

###################################################
# Libraries definitions
###################################################
export LIB_CORE  = libcore.a
export LIB_CPU   = libcpu.a
export LIB_BOARD = libboard.a
export LIB_APPS  = libapps.a

###################################################
# Libraries
###################################################
FIRMWARE_LIBS += $(FIRMWARE_BUILD_CORE)/$(LIB_CORE)
FIRMWARE_LIBS += $(FIRMWARE_BUILD_CPU)/$(LIB_CPU)
FIRMWARE_LIBS += $(FIRMWARE_BUILD_BOARD)/$(LIB_BOARD)
FIRMWARE_LIBS += $(FIRMWARE_BUILD_APPS)/$(LIB_APPS)

###################################################
# Linker script and image info
###################################################
FIRMWARE_LDSCRIPT = cpu/$(CPU)/ldscripts/$(CPU).ld
FIRMWARE_IMAGE    = $(FIRMWARE_BUILD)/$(FIRMWARE)

####################################################
# Make rules
####################################################
all: $(VCRTOS)

$(BUILD):
	$(MKDIR) -p $@

FIRMWARE_OBJS:
	$(MAKE) -C core            BUILD=$(FIRMWARE_BUILD_CORE)  CFLAGS="$(CFLAGS)"
	$(MAKE) -C cpu/$(CPU)      BUILD=$(FIRMWARE_BUILD_CPU)   CFLAGS="$(CFLAGS)"
	$(MAKE) -C boards/$(BOARD) BUILD=$(FIRMWARE_BUILD_BOARD) CFLAGS="$(CFLAGS)"
	$(MAKE) -C apps/$(APPS)    BUILD=$(FIRMWARE_BUILD_APPS)  CFLAGS="$(CFLAGS)"

$(FIRMWARE_IMAGE).elf: $(FIRMWARE_LIBS)
	$(CC) $(LDFLAGS) $(patsubst %,-L%,$(patsubst %/,%,$(sort $(dir $(FIRMWARE_LIBS)))))  \
	-Wl,--whole-archive $(patsubst %,-l%,$(patsubst lib%,%,$(sort $(basename $(notdir $(FIRMWARE_LIBS)))))) \
	-Wl,--no-whole-archive -T$(FIRMWARE_LDSCRIPT) \
	-Wl,-Map,$(BUILD)/$(FIRMWARE_DIR)/firmware.map -o $@

$(FIRMWARE_IMAGE).bin: $(FIRMWARE_IMAGE).elf
	$(OBJCOPY) -O binary $< $@

$(FIRMWARE): FIRMWARE_OBJS $(FIRMWARE_IMAGE).bin
	$(SIZE) --format=berkeley $(FIRMWARE_IMAGE).elf
	@mv $(FIRMWARE_IMAGE).elf $(FIRMWARE_IMAGE).bin $(BUILD)

$(VCRTOS): $(FIRMWARE) | $(BUILD)

.PHONY: all clean

clean:
	-rm -rf $(BUILD)
