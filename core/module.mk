###################################################
# CORE MODULES
###################################################
export MODULE_CORE_MSG := 1
export MODULE_SCHEDSTATISTICS := 0

###################################################
# SYSTEM MODULES COMPILER FLAGS DEFINITION
###################################################
ifeq ($(MODULE_CORE_MSG),1)
DEF += -DMODULE_CORE_MSG
endif

ifeq ($(MODULE_SCHEDSTATISTICS),1)
DEF += -DMODULE_SCHEDSTATISTICS
endif
