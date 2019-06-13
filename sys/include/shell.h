#ifndef SHELL_H
#define SHELL_H

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Max line length shell can handle.
 */
#define SHELL_DEFAULT_BUFSIZE (128)

typedef void (*shell_command_handler_t)(int argc, char **argv);

typedef struct shell_command {
    const char *name;
    const char *desc;
    shell_command_handler_t handler;
} shell_command_t;

void shell_run(const shell_command_t *commands, char *line_buf, int len);

#ifdef __cplusplus
}
#endif

#endif /* SHELL_H */
