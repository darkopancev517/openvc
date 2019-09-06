###################################################
# SYSTEM MODULES
###################################################
export MODULE_DIV := 1
export MODULE_STDIO_UART := 1
export MODULE_SYSCALLS := 1
export MODULE_TIMEX := 1
export MODULE_XTIMER := 1
export MODULE_ISRPIPE := 1
export MODULE_TSRB := 1

###################################################
# SYSTEM MODULES COMPILER FLAGS DEFINITION
###################################################
ifeq ($(MODULE_DIV),1)
DEF += -DMODULE_DIV
endif

ifeq ($(MODULE_STDIO_UART),1)
DEF += -DMODULE_STDIO_UART
endif

ifeq ($(MODULE_SYSCALLS),1)
DEF += -DMODULE_SYSCALLS
endif

ifeq ($(MODULE_TIMEX),1)
DEF += -DMODULE_TIMEX
endif

ifeq ($(MODULE_XTIMER),1)
DEF += -DMODULE_XTIMER
endif

ifeq ($(MODULE_ISRPIPE),1)
DEF += -DMODULE_ISRPIPE
endif

ifeq ($(MODULE_TSRB),1)
DEF += -DMODULE_TSRB
endif
