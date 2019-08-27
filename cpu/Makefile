SRCS_CPU += $(wildcard cortexm/*.c)
SRCS_CPU += $(wildcard cortexm/periph/*.c)
SRCS_CPU += $(wildcard $(CPU)/*.c)
SRCS_CPU += $(wildcard $(CPU)/vendor/*.c)
SRCS_CPU += $(wildcard $(CPU)/periph/*.c)

OBJS_CPU += $(addprefix $(BUILD)/,$(SRCS_CPU:.c=.o))

OBJS_DIR += $(sort $(dir $(OBJS_CPU)))

LIB_CPU_ARCHIVE = $(BUILD)/$(LIB_CPU)
LIB_CPU_OBJS += $(OBJS_CPU)

ARCHIVE_FILES += $(LIB_CPU_ARCHIVE)

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

$(LIB_CPU_ARCHIVE): $(LIB_CPU_OBJS)

-include $(OBJS_CPU:%.o=%.d)
