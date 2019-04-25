####################################################
# board build
####################################################
SRCS_BOARD += $(wildcard *.c)

####################################################
OBJS_BOARD += $(addprefix $(BUILD)/, $(SRCS_BOARD:.c=.o))

OBJS_DIR = $(sort $(dir $(OBJS_BOARD)))

LIB_BOARD_ARCHIVE = $(BUILD)/$(LIB_BOARD)
LIB_BOARD_OBJS   += $(OBJS_BOARD)

ARCHIVE_FILES += $(LIB_BOARD_ARCHIVE)

all: | $(OBJS_DIR) $(ARCHIVE_FILES)
$(OBJS_DIR):
	$(MKDIR) -p $@

$(BUILD)/%.o: %.c
	$(ECHO) "CC $<"
	$(CC) $(CFLAGS) -c -o $@ $<

$(BUILD)/%.a:
	$(ECHO) "AR $@"
	$(AR) -cr $@ $^

$(LIB_BOARD_ARCHIVE): $(LIB_BOARD_OBJS)

-include $(OBJS_BOARD:%.o=%.d)
