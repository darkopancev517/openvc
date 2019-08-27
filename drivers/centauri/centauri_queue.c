#include <assert.h>

#include "vtprober.h"
#include "centauri_queue.h"
#include "centauri_prober.h"
#include "centauri_cfg.h"

static CENTAURI_QUEUE_T centQ;

uint8_t cent_event_current(void)
{
	if (centQ.number) {
        return centQ.number;
    }
    return 0;
}

uint8_t have_cent_event(void)
{
    return centQ.number ? 1 : 0;
}

uint32_t *get_cent_event(void)
{
    if (centQ.number > 0) {
        centQ.number--;
        if (centQ.tail == CCMD_Q_MAX) {
            centQ.tail = 0;
        }
        return (uint32_t*)&centQ.data[centQ.tail++];
    }
    return NULL;
}

void get_msg_queue(void)
{
	uint32_t msg_queue_head;
	uint32_t msg_queue_tail;

    cent_spi_readW(CENT_MSG_QUEUE_ADDR + offsetof(QUEUE_DEF_T, head),
                   (uint32_t*)&msg_queue_head);

	msg_queue_head = msg_queue_head & 0x0000ffff;

    if (msg_queue_head >= MAX_MSG_Q_NUM) {
		cent_spi_delay_config();
		cent_spi_readW(CENT_MSG_QUEUE_ADDR + offsetof(QUEUE_DEF_T, head), (uint32_t*)&msg_queue_head);
        /* make sure now msg_queue_head < MAX_MSG_Q_NUM */
        assert(msg_queue_head < MAX_MSG_Q_NUM);
    }

    if (msg_queue_head == centQ.read_tail) {
        /* empty or full */
        return;
    }

    while (centQ.read_tail != msg_queue_head) {
		cent_spi_readW(CENT_MSG_QUEUE_ADDR + offsetof(QUEUE_DEF_T, data) + (centQ.read_tail * 4),
                       (uint32_t*)&centQ.data[centQ.head++]);
        if (centQ.head == CCMD_Q_MAX) {
            centQ.head = 0;
        }
        centQ.number++;
        centQ.read_tail++;
        if (centQ.read_tail == MAX_MSG_Q_NUM) {
            centQ.read_tail = 0;
        }
    }

    msg_queue_tail = centQ.read_tail;

    cent_spi_writeW(CENT_MSG_QUEUE_ADDR + offsetof(QUEUE_DEF_T, tail),
                    msg_queue_tail);
}

void msg_queue_init(void)
{
    centQ.number = 0;
    centQ.head = 0;
    centQ.tail = 0;
    centQ.read_tail = 0;
}

void msg_queue_clear(void)
{
    uint8_t *pdata;
    get_msg_queue();
    do {
        pdata = (uint8_t *)get_cent_event();
    } while (pdata != NULL);
}
