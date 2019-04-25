####################################################
# apps: hello-world build
####################################################
SRCS_APPS += $(wildcard *.c)

####################################################
OBJS_APPS += $(addprefix $(BUILD)/, $(SRCS_APPS:.c=.o))

OBJS_DIR = $(sort $(dir $(OBJS_APPS)))

LIB_APPS_ARCHIVE = $(BUILD)/$(LIB_APPS)
LIB_APPS_OBJS   += $(OBJS_APPS)

ARCHIVE_FILES += $(LIB_APPS_ARCHIVE)

all: | $(OBJS_DIR) $(ARCHIVE_FILES)
$(OBJS_DIR):
	$(MKDIR) -p $@

$(BUILD)/%.o: %.c
	$(ECHO) "CC $<"
	$(CC) $(CFLAGS) -c -o $@ $<

$(BUILD)/%.a:
	$(ECHO) "AR $@"
	$(AR) -cr $@ $^

$(LIB_APPS_ARCHIVE): $(LIB_APPS_OBJS)

-include $(OBJS_APPS:%.o=%.d)
