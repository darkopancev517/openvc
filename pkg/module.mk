###################################################
# PKG MODULES
###################################################
export MODULE_PKG_CONTIKI_NG ?= 1

###################################################
# PKG MODULES COMPILER FLAGS DEFINITION
###################################################
ifeq ($(MODULE_PKG_CONTIKI_NG),1)
DEF += -DMODULE_PKG_CONTIKI_NG
endif
