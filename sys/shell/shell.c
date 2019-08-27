#include <string.h>
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <assert.h>

#include "ringbuffer.h"
#include "shell.h"
#include "shell_commands.h"

#ifdef MODULE_PKG_CONTIKI_NG
extern void serial_line_input(int argc, char **argv);
#endif

#define CMD_HIST_MAX_INDEX  (5)
#define CMD_HIST_BUF_SIZE   (256)

typedef struct cmd_hist {
    char *buf;
    unsigned size;
    struct cmd_hist *next;
    struct cmd_hist *prev;
} cmd_hist_t;

static ringbuffer_t cmd_hist_rb;

static cmd_hist_t cmd_hist_node[CMD_HIST_MAX_INDEX];
static char cmd_hist_buf[CMD_HIST_BUF_SIZE];

static cmd_hist_t *cmd_hist_head = NULL;
static cmd_hist_t *cmd_hist_pointer = NULL;

static void cmd_hist_init(ringbuffer_t *rb, char *buf, unsigned size)
{
    /* initialize command history ringbuffer */
    ringbuffer_init(rb, buf, size);

    for (unsigned i = 0; i < CMD_HIST_MAX_INDEX; i++) {
        cmd_hist_node[i].size = 0;
        cmd_hist_node[i].next = &cmd_hist_node[(i + 1) % CMD_HIST_MAX_INDEX];
        if (i == (CMD_HIST_MAX_INDEX - 1)) {
            cmd_hist_node[CMD_HIST_MAX_INDEX - (i + 1)].prev = &cmd_hist_node[i];
        } else {
            cmd_hist_node[CMD_HIST_MAX_INDEX - (i + 1)].prev = &cmd_hist_node[CMD_HIST_MAX_INDEX - (2 + i)];
        }
    }

    cmd_hist_head = &cmd_hist_node[0];
    cmd_hist_pointer = cmd_hist_head;
}

static void cmd_hist_add(ringbuffer_t *rb, char *buf, unsigned size)
{
    /* we can't store command bigger than CMD_HIST_BUF_SIZE */
    if (size > CMD_HIST_BUF_SIZE) {
        return;
    }

    /* don't store the same command */
    for (unsigned i = 0; i < CMD_HIST_MAX_INDEX; i++) {
        if (cmd_hist_node[i].size != 0) {
            if (strncmp(buf, cmd_hist_node[i].buf, size) == 0) {
                return;
            }
        }
    }

    while (ringbuffer_get_free(rb) < size) {
        /* not enough space to store the command, remove previous stored command */
        cmd_hist_head = cmd_hist_head->prev;
        ringbuffer_remove(rb, cmd_hist_head->size);
        cmd_hist_head->size = 0;
    }

    if ((cmd_hist_head->next)->size != 0) {
        /* regular command update once it's reach CMD_HIST_MAX_INDEX by removing oldest stored command */
        ringbuffer_remove(rb, (cmd_hist_head->next)->size);
        (cmd_hist_head->next)->size = 0;
    }

    unsigned pos = rb->start + rb->avail;

    ringbuffer_add(rb, buf, size);

    cmd_hist_head->buf = &rb->buf[pos];
    cmd_hist_head->size = size;

    cmd_hist_head = cmd_hist_head->next;
    cmd_hist_pointer = cmd_hist_head;
}

static shell_command_handler_t find_handler(const shell_command_t *command_list, char *command)
{
    const shell_command_t *command_lists[] = {
        command_list,
        _shell_command_list,
    };

    const shell_command_t *entry;

    /* iterating over command_lists */
    for (unsigned int i = 0; i < sizeof(command_lists) / sizeof(entry); i++) {
        if ((entry = command_lists[i])) {
            /* iterating over commands in command_lists entry */
            while (entry->name != NULL) {
                if (strcmp(entry->name, command) == 0) {
                    return entry->handler;
                } else {
                    entry++;
                }
            }
        }
    }

    return NULL;
}

static void print_help(const shell_command_t *command_list)
{
    printf("%-20s %s\n", "Command", "Description");
    puts("---------------------------------------");

    const shell_command_t *command_lists[] = {
        command_list,
        _shell_command_list,
    };

    const shell_command_t *entry;

    /* iterating over command_lists */
    for (unsigned int i = 0; i < sizeof(command_lists) / sizeof(entry); i++) {
        if ((entry = command_lists[i])) {
            /* iterating over commands in command_lists entry */
            while (entry->name != NULL) {
                printf("%-20s %s\n", entry->name, entry->desc);
                entry++;
            }
        }
    }
}

static void handle_input_line(const shell_command_t *command_list, char *line)
{
    static const char *UNSUPPORTED_QUOTING = "shell: doesn't support quoting";

    /* first we need to calculate the number of arguments */
    unsigned argc = 0;
    char *pos = line;

    while (1) {
        if ((unsigned char) *pos > ' ') {
            /* found an argument */
            do {
                ++pos;
                if (*pos == '"') {
                    puts(UNSUPPORTED_QUOTING);
                    return;
                }
            } while ((unsigned char) *pos > ' ');

            /* count the number of arguments we got */
            ++argc;
        }

        /* zero out the current position (space or quotation mark) and advance */
        if (*pos > 0) {
            *pos = 0;
            ++pos;
        } else {
            break;
        }
    }

    if (!argc) {
        return;
    }

    /* then we fill the argv array */
    char *argv[argc + 1];
    argv[argc] = NULL;
    pos = line;
    for (unsigned i = 0; i < argc; ++i) {
        while (!*pos) {
            ++pos;
        }
        argv[i] = pos;
        while (*pos) {
            ++pos;
        }
    }

    /* then we call the appropriate handler */
    shell_command_handler_t handler = find_handler(command_list, argv[0]);
    if (handler != NULL) {
        handler(argc, argv);
    } else {
        if (strcmp("help", argv[0]) == 0) {
            print_help(command_list);
#ifdef MODULE_PKG_CONTIKI_NG
            serial_line_input(argc, argv);
#endif
        } else {
#ifdef MODULE_PKG_CONTIKI_NG
            serial_line_input(argc, argv);
#else
            printf("shell: command not found: %s\n", argv[0]);
#endif
        }
    }
}

static void white_tape_char(void)
{
    putchar('\b');
    putchar(' ');
    putchar('\b');
}

static int readline(char *buf, size_t size, unsigned *char_count)
{
    unsigned i;

    int esc_seq[3];

    char *line_buf_ptr = buf;

    while (1) {
        if ((line_buf_ptr - buf) >= ((int) size) - 1) {
            return -1;
        }

        int c = getchar();

        if (c < 0) {
            /* this should not happen */
            return EOF;
        }

        if (c == '\r' || c == '\n') {
            *line_buf_ptr = '\0';
            putchar('\r');
            putchar('\n');

            cmd_hist_pointer = cmd_hist_head;

            /* return 1 if line is empty, 0 otherwise */
            return line_buf_ptr == buf;

        } else if (c == 0x08 || c == 0x7f) {
            if (line_buf_ptr == buf) {
                /* The line is empty. */
                continue;
            }

            *--line_buf_ptr = '\0';
            *char_count -= 1;
            /* white-tape the character */
            white_tape_char();

        } else if (c == 0x1b) {

            /* get all esc sequences */
            esc_seq[0] = c;

            esc_seq[1] = getchar();
            if (esc_seq[1] < 0) {
                /* this should not happen */
                return EOF;
            }

            esc_seq[2] = getchar();
            if (esc_seq[2] < 0) {
                /* this should not happen */
                return EOF;
            }

            if (esc_seq[1] == 0x5b && esc_seq[2] == 0x41) {
                /* up key */
                if ((cmd_hist_pointer->prev)->size != 0) {
                    if (*char_count != 0) {
                        while (*char_count != 0) {
                            *--line_buf_ptr = '\0';
                            *char_count -= 1;
                            /* white-tape the character */
                            white_tape_char();
                        }
                    }

                    for (i = 0; i < (cmd_hist_pointer->prev)->size; i++) {
                        *line_buf_ptr++ = (cmd_hist_pointer->prev)->buf[i];
                        putchar((cmd_hist_pointer->prev)->buf[i]);
                        *char_count += 1;
                    }

                    cmd_hist_pointer = cmd_hist_pointer->prev;
                }

            } else if (esc_seq[1] == 0x5b && esc_seq[2] == 0x42) {
                /* down key */
                if (((cmd_hist_pointer->next)->size != 0) && (cmd_hist_pointer != cmd_hist_head)) {
                    if (*char_count != 0) {
                        while (*char_count != 0) {
                            *--line_buf_ptr = '\0';
                            *char_count -= 1;
                            /* white-tape the character */
                            white_tape_char();
                        }
                    }

                    for (i = 0; i < (cmd_hist_pointer->next)->size; i++) {
                        *line_buf_ptr++ = (cmd_hist_pointer->next)->buf[i];
                        putchar((cmd_hist_pointer->next)->buf[i]);
                        *char_count += 1;
                    }

                    cmd_hist_pointer = cmd_hist_pointer->next;

                } else {

                    if (*char_count != 0) {
                        while (*char_count != 0) {
                            *--line_buf_ptr = '\0';
                            *char_count -= 1;
                            /* white-tape the character */
                            white_tape_char();
                        }
                    }

                    cmd_hist_pointer = cmd_hist_head;
                }

            } else {
                for (i = 0; i < (sizeof(esc_seq) / sizeof(esc_seq[0])); i++) {
                    *line_buf_ptr++ = esc_seq[i];
                    putchar(esc_seq[i]);
                    *char_count += 1;
                }
            }

        } else {
            *line_buf_ptr++ = c;
            *char_count += 1;
            putchar(c);
        }

        fflush(stdout);
    }
}

static inline void print_prompt(void)
{
    putchar('>');
    putchar(' ');

    fflush(stdout);
}

void shell_run(const shell_command_t *shell_commands, char *line_buf, int len)
{
    unsigned char_count = 0;

    cmd_hist_init(&cmd_hist_rb, cmd_hist_buf, CMD_HIST_BUF_SIZE);

    print_prompt();

    while (1) {
        int res = readline(line_buf, len, &char_count);

        assert(res != EOF);

        if (!res) {
            if (char_count != 0) {
                cmd_hist_add(&cmd_hist_rb, line_buf, char_count);
            }
            handle_input_line(shell_commands, line_buf);
        }

        char_count = 0;
        print_prompt();
    }
}
