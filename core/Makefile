####################################################
# core build
####################################################
SRCS_CORE += $(wildcard *.c)

####################################################
OBJS_CORE += $(addprefix $(BUILD)/, $(SRCS_CORE:.c=.o))

OBJS_DIR = $(sort $(dir $(OBJS_CORE)))

LIB_CORE_ARCHIVE = $(BUILD)/$(LIB_CORE)
LIB_CORE_OBJS   += $(OBJS_CORE)

ARCHIVE_FILES += $(LIB_CORE_ARCHIVE)

all: | $(OBJS_DIR) $(ARCHIVE_FILES)
$(OBJS_DIR):
	$(MKDIR) -p $@

$(BUILD)/%.o: %.c
	$(ECHO) "CC $<"
	$(CC) $(CFLAGS) -c -o $@ $<

$(BUILD)/%.a:
	$(ECHO) "AR $@"
	$(AR) -cr $@ $^

$(LIB_CORE_ARCHIVE): $(LIB_CORE_OBJS)

-include $(OBJS_CORE:%.o=%.d)
