#include <stdio.h>
#include <string.h>

#include "xtimer.h"
#include "centauri.h"

#define CENTAURI_RX_TEST 0
#define CENTAURI_TX_TEST 1

static volatile uint32_t rxcmp_count = 0;

static void centauri_rftest_rxcmp_cb(void *arg)
{
    cent_dataset_t *cent = (cent_dataset_t *)arg;
    printf("rxcmp: (%u), count %lu\n", cent->rxindex, rxcmp_count++);
}

int main(void)
{
    printf("main entry:\n");

    xtimer_init();

    cent_dataset_t *cent = centauri_init();

    printf("centauri init: done\n");

    cent->rxcmp.rftest = centauri_rftest_rxcmp_cb;

#if CENTAURI_RX_TEST
    printf("centauri rx standby\n");
    centauri_rx();
#endif

#if CENTAURI_TX_TEST
    uint32_t txcount = 10000;
    uint8_t dummy[50];
    memset(dummy, 0xff, sizeof(dummy));
    printf("centauri tx %lu times\n", txcount);
    while (txcount--) {
        centauri_tx(dummy, sizeof(dummy));
    }
#endif

    while (1) {
        xtimer_usleep(1000);
    }

    return 0;
}
