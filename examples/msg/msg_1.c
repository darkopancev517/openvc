#include <stdio.h>
#include <assert.h>

#include "shell.h"
#include "thread.h"

static char shell_line_buf[SHELL_DEFAULT_BUFSIZE];
static char test_stack[THREAD_STACKSIZE_DEFAULT];
static kernel_pid_t test_thread_pid;

static void user_test(int argc, char **argv)
{
    (void) argc;
    (void) argv;

    printf("[user application test command]\n");

    msg_t msg;

    msg.type = 0x20;
    msg.content.ptr = NULL;

    assert(msg_send(&msg, test_thread_pid));
}

static const shell_command_t user_command_list[] = {
    { "test", "user test command", user_test },
    { NULL, NULL, NULL }
};

static void *test_thread(void *arg)
{
    (void) arg;

    msg_t msg;
    while (1) {
        if (msg_receive(&msg)) {
            if (msg.type == 0x20 && msg.content.ptr == NULL) {
                printf("message received from: %d\n", msg.sender_pid);
            }
        }
    }

    return NULL;
}

int main(void)
{
    test_thread_pid = thread_create(test_stack, sizeof(test_stack),
                                    THREAD_PRIORITY_MAIN,
                                    THREAD_CREATE_WOUT_YIELD | THREAD_CREATE_STACKTEST,
                                    test_thread, NULL, "test");

    shell_run(user_command_list, shell_line_buf, sizeof(shell_line_buf));

    /* Note: if user don't have `user_command_list` use NULL instead */

    /* should not reach here */

    return 0;
}
