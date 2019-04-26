####################################################
# cpu build
####################################################
SRCS_CORTEXM += $(wildcard ../cortexm/*.c)
SRCS_CPU     += $(wildcard *.c)
SRCS_CPU     += $(wildcard periph/*.c)

####################################################
OBJS_CORTEXM += $(addprefix $(BUILD)/, $(SRCS_CORTEXM:.c=.o))
OBJS_CPU 	 += $(addprefix $(BUILD)/, $(SRCS_CPU:.c=.o))

OBJS_DIR += $(sort $(dir $(OBJS_CORTEXM)))
OBJS_DIR += $(sort $(dir $(OBJS_CPU)))

LIB_CPU_ARCHIVE  = $(BUILD)/$(LIB_CPU)
LIB_CPU_OBJS    += $(OBJS_CORTEXM)
LIB_CPU_OBJS    += $(OBJS_CPU)

ARCHIVE_FILES += $(LIB_CPU_ARCHIVE)

all: | $(OBJS_DIR) $(ARCHIVE_FILES)
$(OBJS_DIR):
	$(MKDIR) -p $@

$(BUILD)/%.o: %.c
	$(ECHO) "CC $<"
	$(CC) $(CFLAGS) -c -o $@ $<

$(BUILD)/%.a:
	$(ECHO) "AR $@"
	$(AR) -cr $@ $^

$(LIB_CPU_ARCHIVE): $(LIB_CPU_OBJS)

-include $(OBJS_CPU:%.o=%.d)
-include $(OBJS_CORTEXM:%.o=%.d)
