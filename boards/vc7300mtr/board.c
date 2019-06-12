#include "board.h"

void board_init(void)
{
    cpu_init();

    BOARD_TXLED_INIT();
    BOARD_RXLED_INIT();

    BOARD_TXLED_OFF();
    BOARD_RXLED_OFF();
}
