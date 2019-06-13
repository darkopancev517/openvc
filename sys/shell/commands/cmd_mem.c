/* memory utility commands */
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static void cmd_dw_help(void);
static void cmd_ww_help(void);

static void word_dump(const void *data, uint32_t nwords);

void cmd_dw_handler(int argc, char **argv)
{
    if (argc < 2 || argc > 3) {
        cmd_dw_help();
    } else {
        uint32_t addr = (uint32_t)strtoul(argv[1], NULL, 16);
        if (argc == 2) {
            /* dump one word */
            word_dump((void *)(addr & ~0x3), 1);
        } else {
            /* dump n number of words */
            uint32_t nwords = (uint32_t)strtoul(argv[2], NULL, 16);
            word_dump((void *)(addr & ~0x3), nwords);
        }
    }
}

void cmd_ww_handler(int argc, char **argv)
{
    if (argc < 3 || argc > 4) {
        cmd_ww_help();
    } else {
        uint32_t addr = (uint32_t)strtoul(argv[1], NULL, 16);
        uint32_t data = (uint32_t)strtoul(argv[2], NULL, 16);
        if (argc == 3 ) {
            *((volatile uint32_t *)addr) = data;
            word_dump((void*)(addr & ~0x3), 1);
        } else {
            uint32_t naddrs = (uint32_t)strtoul(argv[3], NULL, 16);
            while (naddrs-- > 0) {
                *((volatile uint32_t *)addr) = data;
                addr += 4;
            }
            addr = (uint32_t)strtoul(argv[1], NULL, 16);
            naddrs = (uint32_t)strtoul(argv[3], NULL, 16);
            word_dump((void *)(addr & ~0x3), naddrs);
        }
    }
}

static void cmd_dw_help(void)
{
    printf("format (hex):\n");
    printf("    dw <addr>\n");
    printf("    dw <addr> <nwords>\n");
}

static void cmd_ww_help(void)
{
    printf("format (hex):\n");
    printf("    ww <addr> <word>\n");
    printf("    ww <addr> <word> <naddrs>\n");
}

static void word_dump(const void *data, uint32_t nwords)
{
    volatile uint32_t *addr = (volatile uint32_t *)(((uint32_t)data + 0x3) & ~0x3);

    if (nwords <= 0) {
        return;
    }

    uint32_t nlines = nwords / 4;

    while (nlines--) {
        printf("%08lX | %08lX %08lX - %08lX %08lX\n", (uint32_t)addr, addr[0], addr[1], addr[2], addr[3]);
        addr += 4;
    }

    nwords = nwords & 3;

    if (nwords) {
        printf("%08lX |", (uint32_t)addr);
        for (uint32_t i = 0; i < nwords; ++i) {
            if (i == 2) {
                printf(" -");
            }
            printf(" %08lX", addr[i]);
        }
        printf("\n");
    }
}
