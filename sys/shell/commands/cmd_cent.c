#include <assert.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#include "centauri.h"
#include "xtimer.h"

static void centauri_rftest_rxcmp_cb(void *arg);
static void cmd_cent_tx_handler(cent_dataset_t *cent, int argc, char **argv);
static void cmd_cent_rx_handler(cent_dataset_t *cent, int argc, char **argv);

void cmd_cent_handler(int argc, char **argv)
{
    cent_dataset_t *cent = centauri_get_data();

    if (!cent->alivestatus) {
        cent = centauri_init();
    }

    assert(cent->alivestatus);

    if (cent->rxcmp.rftest == NULL) {
        cent->rxcmp.rftest = centauri_rftest_rxcmp_cb;
    }

    if (argc == 1) {
        printf("centauri is alive\n");
    } else {
        if (strcmp("tx", argv[1]) == 0) {
            cmd_cent_tx_handler(cent, argc, argv);
        } else if (strcmp("rx", argv[1]) == 0) {
            cmd_cent_rx_handler(cent, argc, argv);
        }
    }
}

static uint32_t rxcmp_count = 0;
static void centauri_rftest_rxcmp_cb(void *arg)
{
    cent_dataset_t *cent = (cent_dataset_t *)arg;
    printf("rxcmp: (%u), count %lu\n", cent->rxindex, rxcmp_count++);
}

static void cmd_cent_tx_handler(cent_dataset_t *cent, int argc, char **argv)
{
    uint32_t txcount = 0;
    uint8_t dummy[50];

    cent->rftest = 1;

    memset(dummy, 0xff, sizeof(dummy));

    if (argc == 3) {
        txcount = (uint32_t)atoi(argv[2]);
        printf("centauri test tx %lu times\n", txcount);
        while (txcount--) {
            centauri_tx(dummy, sizeof(dummy));
        }
    } else {
        centauri_tx(dummy, sizeof(dummy));
    }

    cent->rftest = 0;
}

static void cmd_cent_rx_handler(cent_dataset_t *cent, int argc, char **argv)
{
    if (argc == 3) {
        uint32_t rxstate = (uint32_t)atoi(argv[2]);
        if (rxstate == 1) {
            cent->rftest = 1;
            printf("centauri test rx on\n");
            centauri_rx();
        } else {
            /* note: don't disable rx, it may used by app layer when rf test is  done. */
            printf("centauri test rx off\n");
            cent->rftest = 0;
        }
    }
}
