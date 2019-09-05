###################################################
# DRIVERS MODULES
###################################################
export MODULE_DRIVERS_CENTAURI ?= 1
export MODULE_DRIVERS_NVSETS ?= 1

###################################################
# DRIVERS MODULES COMPILER FLAGS DEFINITION
###################################################
ifeq ($(MODULE_DRIVERS_CENTAURI),1)
DEF += -DMODULE_DRIVERS_CENTAURI
endif

ifeq ($(MODULE_DRIVERS_NVSETS),1)
DEF += -DMODULE_DRIVERS_NVSETS
endif
