SRCS_CORE += assert.c
SRCS_CORE += bitarithm.c
SRCS_CORE += clist.c
SRCS_CORE += kernel_init.c
SRCS_CORE += mutex.c
SRCS_CORE += panic.c
SRCS_CORE += ringbuffer.c
SRCS_CORE += sched.c
SRCS_CORE += thread.c
ifeq ($(MODULE_CORE_MSG),1)
SRCS_CORE += msg.c
endif

OBJS_CORE += $(addprefix $(BUILD)/,$(SRCS_CORE:.c=.o))

OBJS_DIR += $(sort $(dir $(OBJS_CORE)))

LIB_CORE_PATCH_ARCHIVES = $(wildcard archive/*.a)

ifeq (,$(findstring $(LIB_CORE),$(LIB_CORE_PATCH_ARCHIVES)))
LIB_CORE_ARCHIVE = $(BUILD)/$(LIB_CORE)
LIB_CORE_OBJS += $(OBJS_CORE)
else
LIB_CORE_ARCHIVE = $(BUILD)/$(LIB_CORE).patch
LIB_CORE_PATCH += archive/$(LIB_CORE)
endif

ARCHIVE_FILES += $(LIB_CORE_ARCHIVE)

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

$(BUILD)/%.patch:
	$(ECHO) "\033[32mPATCH\033[0m $^"
	$(RM) -f $@
	$(CP) -f $^ $(BUILD)

$(LIB_CORE_ARCHIVE): $(LIB_CORE_OBJS) $(LIB_CORE_PATCH)

-include $(OBJS_CORE:%.o=%.d)
