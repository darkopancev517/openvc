###################################################
# SYSTEM MODULES
###################################################
MODULE_ISRPIPE ?= 1
MODULE_PS ?= 1
MODULE_SHELL ?= 1
ifeq ($(MODULE_SHELL),1)
MODULE_SHELL_COMMANDS ?= 1
endif
MODULE_STDIO_UART ?= 1
MODULE_SYSCALLS ?= 1
MODULE_TSRB ?= 1

###################################################
# SYSTEM MODULES COMPILER FLAGS DEFINITION
###################################################
ifeq ($(MODULE_ISRPIPE),1)
DEF += -DMODULE_ISRPIPE
endif

ifeq ($(MODULE_PS),1)
DEF += -DMODULE_PS
endif

ifeq ($(MODULE_SHELL),1)
DEF += -DMODULE_SHELL
DEF += -DMODULE_SHELL_COMMANDS
endif

ifeq ($(MODULE_STDIO_UART),1)
DEF += -DMODULE_STDIO_UART
endif

ifeq ($(MODULE_SYSCALLS),1)
DEF += -DMODULE_SYSCALLS
endif

ifeq ($(MODULE_TSRB),1)
DEF += -DMODULE_TRSB
endif
