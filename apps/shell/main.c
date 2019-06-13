#include <stdio.h>
#include <assert.h>

#include "shell.h"

static char shell_line_buf[SHELL_DEFAULT_BUFSIZE];

static void user_test(int argc, char **argv)
{
    (void) argc;
    (void) argv;

    printf("[user application test command]\n");
}

static const shell_command_t user_command_list[] = {
    { "test", "user test command", user_test },
    { NULL, NULL, NULL }
};

int main(void)
{
    printf("shell is run\n");

    shell_run(user_command_list, shell_line_buf, sizeof(shell_line_buf));

    /* Note: if user don't have `user_command_list` use NULL instead */

    /* should not reach here */
    assert(0);

    return 0;
}
