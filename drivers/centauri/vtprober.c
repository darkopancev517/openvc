#include "vtprober.h"
#include "board.h"

enum VTPROBE_CMD_E {
    /* Control Register Access */
    VTPROBE_CMD_BASE_REG_IN                 = 0x40,     // RDBR , Read  4 bytes base address register
    VTPROBE_CMD_BASE_REG_OUT                = 0x60,     // WRBR , Write 4 bytes base address register
    VTPROBE_CMD_STATUS_REG_IN               = 0x41,     // RDDR , Read  1 byte dummy delay register
    VTPROBE_CMD_STATUS_REG_OUT              = 0x61,     // WRDR , Write 1 byte dummy delay register
    VTPROBE_CMD_BURST_LEN_REG_IN            = 0x42,     // RDMR , Read  1 byte multiple word register
    VTPROBE_CMD_BURST_LEN_REG_OUT           = 0x62,     // WRMR , Write 1 byte multiple word register

    /* Multiple Words Access */
    VTPROBE_CMD_READ_BURST                  = 0x08,     // RDM  , Read  N words access
    VTPROBE_CMD_READ_BURST_IND              = 0x88,     // RDMI , Read  N words access via indirect addressing
    VTPROBE_CMD_WRITE_BURST                 = 0x28,     // WRM  , Write N words access
    VTPROBE_CMD_WRITE_BURST_IND             = 0xA8,     // WRMI , Write N words access via indirect addressing , i don't have to implement this command , it can't gain any profile ....

    /* Single Word Access */
    VTPROBE_CMD_WORD_IN                     = 0x04,     // RDW  , Read  4 bytes access
    VTPROBE_CMD_WORD_IN_OFFSET              = 0x84,     // RDWI , Read  4 bytes access via indirect addressing
    VTPROBE_CMD_WORD_OUT                    = 0x24,     // WRW  , Write 4 bytes access
    VTPROBE_CMD_WORD_OUT_OFFSET             = 0xa4,     // WRWI , Write 4 bytes access via indirect addressing

    /* Single Half-Word Access */
    VTPROBE_CMD_HALF_IN                     = 0x02,     // RDH  , Read  2 bytes access
    VTPROBE_CMD_HALF_IN_OFFSET              = 0x82,     // RDHI , Read  2 bytes access via indirect addressing
    VTPROBE_CMD_HALF_OUT                    = 0x22,     // WRH  , Write 2 bytes access
    VTPROBE_CMD_HALF_OUT_OFFSET             = 0xa2,     // WRHI , Write 2 bytes access via indirect addressing

    /* Single Byte Access */
    VTPROBE_CMD_BYTE_IN                     = 0x01,     // RDB  , Read  1 byte access
    VTPROBE_CMD_BYTE_IN_OFFSET              = 0x81,     // RDBI , Read  1 byte access via indirect addressing
    VTPROBE_CMD_BYTE_OUT                    = 0x21,     // WRB  , Write 1 byte access
    VTPROBE_CMD_BYTE_OUT_OFFSET             = 0xa1,     // WRBI , Write 1 byte access via indirect addressing
};

static int _delay_bytes;
static int _delay_cycles;

/* Initialize ATE prober */
int vtprober_init(void)
{
    /* set default delay to 2 byte */
    _delay_bytes = 2;
    _delay_cycles = _delay_bytes * 8;

    /* initialize spi interface */
    spi_init(BOARD_CENTAURI_SPI_DEV);

    return VTPROBE_ERR_SUCCESS;
}

/* Set base address for indirect access */
int vtprober_set_base_addr(uint32_t base_addr)
{
    uint8_t data_out[5] = {
        VTPROBE_CMD_BASE_REG_OUT,
        (uint8_t)(base_addr >> 24),
        (uint8_t)(base_addr >> 16),
        (uint8_t)(base_addr >> 8),
        (uint8_t)(base_addr)
    };

    spi_transfer_bytes(BOARD_CENTAURI_SPI_DEV,
                       BOARD_CENTAURI_SPI_CS_PIN,
                       false /* continous */,
                       data_out,
                       NULL,
                       sizeof(data_out));

    return VTPROBE_ERR_SUCCESS;
}

/* Get base address for indirect access */
int vtprober_get_base_addr(uint32_t *p_base_addr)
{
    uint8_t data_in[5];
    uint8_t data_out[5] = {
        VTPROBE_CMD_BASE_REG_IN,
        0, 0, 0, 0
    };

    spi_transfer_bytes(BOARD_CENTAURI_SPI_DEV,
                       BOARD_CENTAURI_SPI_CS_PIN,
                       false /* continous */,
                       data_out,
                       data_in,
                       sizeof(data_out));

    *p_base_addr = ((uint32_t)data_in[1] << 24) |
                   ((uint32_t)data_in[2] << 16) |
                   ((uint32_t)data_in[3] << 8) |
                   ((uint32_t)data_in[4]);

    return VTPROBE_ERR_SUCCESS;
}

/* Set delay cycles. 0 for 8T ~ 3 for 32T */
int vtprober_set_delay(uint32_t delay_bytes)
{
    uint32_t delay_cycles = (delay_bytes + 1) * 8;
    uint8_t data_out[2] = {
        VTPROBE_CMD_STATUS_REG_OUT,
        (uint8_t)((delay_cycles - 1) & 0x01F)
    };

    // Maximum delay is 32T
    if (delay_cycles > 32) return VTPROBE_ERR_ARGUMENT;

    _delay_cycles = delay_cycles;
    _delay_bytes = delay_bytes + 1;

    spi_transfer_bytes(BOARD_CENTAURI_SPI_DEV,
                       BOARD_CENTAURI_SPI_CS_PIN,
                       false /* continous */,
                       data_out,
                       NULL,
                       sizeof(data_out));

    return VTPROBE_ERR_SUCCESS;
}

/* Get delay cycles */
int vtprober_get_delay(uint32_t *p_delay_cycles)
{
    uint8_t data_in[2];
    uint8_t data_out[2] = {
        VTPROBE_CMD_STATUS_REG_IN,
        0
    };

    spi_transfer_bytes(BOARD_CENTAURI_SPI_DEV,
                       BOARD_CENTAURI_SPI_CS_PIN,
                       false /* continous */,
                       data_out,
                       data_in,
                       sizeof(data_out));

    *p_delay_cycles = (uint32_t)(data_in[1] & 0x1F);
    *p_delay_cycles += 1;

    return VTPROBE_ERR_SUCCESS;
}

/* Read a word from address with delay */
int vtprober_read_w_delay(uint32_t address, uint32_t *p_value)
{
    uint8_t data_in[13];
    int length = 9 + _delay_bytes;
    uint8_t *p_data = &data_in[length - 4];
    uint8_t data_out[13] = {
        VTPROBE_CMD_WORD_IN,
        (uint8_t)(address >> 24),
        (uint8_t)(address >> 16),
        (uint8_t)(address >> 8),
        (uint8_t)(address),
        0, 0, 0, 0, // Maximum 32 T delay
        0, 0, 0, 0
    };

    spi_transfer_bytes(BOARD_CENTAURI_SPI_DEV,
                       BOARD_CENTAURI_SPI_CS_PIN,
                       false /* continous */,
                       data_out,
                       data_in,
                       length);

    *p_value = ((uint32_t)p_data[0] << 24) |
               ((uint32_t)p_data[1] << 16) |
               ((uint32_t)p_data[2] << 8)  |
               ((uint32_t)p_data[3]);

    return VTPROBE_ERR_SUCCESS;
}

/* Read a word from address */
int vtprober_read_w(uint32_t address, uint32_t *p_value)
{
    return vtprober_read_w_delay(address, p_value);
}

/* Read a word from index of base address with delay */
int vtprober_read_w_indirect_delay(uint32_t index, uint32_t *p_value)
{
    uint8_t data_in[10];
    int length = 6 + _delay_bytes;
    uint8_t *p_data = &data_in[length - 4];
    uint8_t data_out[10] = {
        VTPROBE_CMD_WORD_IN_OFFSET,
        (uint8_t)index,
        0, 0, 0, 0,
        0, 0, 0, 0
    };

    spi_transfer_bytes(BOARD_CENTAURI_SPI_DEV,
                       BOARD_CENTAURI_SPI_CS_PIN,
                       false /* continous */,
                       data_out,
                       data_in,
                       length);

    *p_value = ((uint32_t)p_data[0] << 24) |
               ((uint32_t)p_data[1] << 16) |
               ((uint32_t)p_data[2] << 8) |
               ((uint32_t)p_data[3]);

    return VTPROBE_ERR_SUCCESS;
}

/* Read a word from index of base address */
int vtprober_read_w_indirect(uint32_t index, uint32_t *p_value)
{
    return vtprober_read_w_indirect_delay(index, p_value);
}

#define RDM_CMD_LEN 5
#define WRM_CMD_LEN 5
#define DUMMY_MAX_SIZE 4

static int _vtprober_burst_len(uint32_t len)
{
    uint8_t data_out[2];
    uint8_t burst_len;

    /* centauri hw burst len register just have 8 bits --> (255+1) * 4 byte */
    if (len > 1024) return VTPROBE_ERR_IO_SIZE;

    /* 0 ~ 255, start from 0 --> need -1 */
    burst_len = (uint8_t)((uint32_t)(len + 3) / 4) - 1;

    data_out[0] = VTPROBE_CMD_BURST_LEN_REG_OUT;
    data_out[1] = burst_len;

    spi_transfer_bytes(BOARD_CENTAURI_SPI_DEV,
                       BOARD_CENTAURI_SPI_CS_PIN,
                       false /* continous */,
                       data_out,
                       NULL,
                       sizeof(data_out));

    return VTPROBE_ERR_SUCCESS;
}

static void _buf_swap_endianess(uint8_t *buf, uint32_t len)
{
    //swap endianess
    for (int i = 0; i < len; i+=4){
        uint8_t b0,b1,b2,b3;
        b0 = ((uint8_t *)buf)[i+3];
        b1 = ((uint8_t *)buf)[i+2];
        b2 = ((uint8_t *)buf)[i+1];
        b3 = ((uint8_t *)buf)[i];
        //
        ((uint8_t *)buf)[i]   = b0;
        ((uint8_t *)buf)[i+1] = b1;
        ((uint8_t *)buf)[i+2] = b2;
        ((uint8_t *)buf)[i+3] = b3;
    }
}

/* Read word in a burst */
int vtprober_read_w_burst(uint32_t burst_len, uint32_t address, uint32_t *p_value, uint32_t read_len)
{
    uint32_t length;

    uint8_t cmd_header[RDM_CMD_LEN + DUMMY_MAX_SIZE] = {
        VTPROBE_CMD_READ_BURST,
        (uint8_t)(address >> 24),
        (uint8_t)(address >> 16),
        (uint8_t)(address >> 8),
        (uint8_t)(address)
    };

    if (read_len > 256) {
        return VTPROBE_ERR_IO_SIZE;
    }

    /* SPI out header + dummy + data size */
    length = RDM_CMD_LEN + _delay_bytes;

    _vtprober_burst_len(burst_len);

    spi_transfer_bytes(BOARD_CENTAURI_SPI_DEV,
                       BOARD_CENTAURI_SPI_CS_PIN,
                       true /* continous */,
                       cmd_header,
                       NULL,
                       length);

    spi_transfer_bytes(BOARD_CENTAURI_SPI_DEV,
                       BOARD_CENTAURI_SPI_CS_PIN,
                       false /* continous */,
                       NULL,
                       (void *)p_value,
                       read_len);

    _buf_swap_endianess((uint8_t *)p_value, read_len);

    return VTPROBE_ERR_SUCCESS;
}

/* Write a word to address */
int vtprober_write_w(uint32_t address, uint32_t value)
{
    uint8_t data_out[9] = {
        VTPROBE_CMD_WORD_OUT,
        (uint8_t)(address >> 24),
        (uint8_t)(address >> 16),
        (uint8_t)(address >> 8),
        (uint8_t)(address),
        (uint8_t)(value >> 24),
        (uint8_t)(value >> 16),
        (uint8_t)(value >> 8),
        (uint8_t)(value)
    };

    spi_transfer_bytes(BOARD_CENTAURI_SPI_DEV,
                       BOARD_CENTAURI_SPI_CS_PIN,
                       false /* continous */,
                       data_out,
                       NULL,
                       sizeof(data_out));

    return VTPROBE_ERR_SUCCESS;
}

/* Write a word to index of the base address */
int vtprober_write_w_indirect(uint32_t index, uint32_t value)
{
    uint8_t data_out[6] = {
        VTPROBE_CMD_WORD_OUT_OFFSET,
        (uint8_t)(index),
        (uint8_t)(value >> 24),
        (uint8_t)(value >> 16),
        (uint8_t)(value >> 8),
        (uint8_t)(value)
    };

    spi_transfer_bytes(BOARD_CENTAURI_SPI_DEV,
                       BOARD_CENTAURI_SPI_CS_PIN,
                       false /* continous */,
                       data_out,
                       NULL,
                       sizeof(data_out));

    return VTPROBE_ERR_SUCCESS;
}

/* Write a word in a burst */
int vtprober_write_w_burst(uint32_t burst_len, uint32_t address, uint8_t *data_out, uint32_t size)
{
    uint8_t cmd_header[WRM_CMD_LEN] = {
        VTPROBE_CMD_WRITE_BURST,
        (uint8_t)(address >> 24),
        (uint8_t)(address >> 16),
        (uint8_t)(address >> 8),
        (uint8_t)(address)
    };

    if (size > 256 || address < 0x8000) {
        return VTPROBE_ERR_IO_SIZE;
    }

    _buf_swap_endianess((uint8_t *)data_out, size);

    _vtprober_burst_len(burst_len);

    spi_transfer_bytes(BOARD_CENTAURI_SPI_DEV,
                       BOARD_CENTAURI_SPI_CS_PIN,
                       true /* continous */,
                       cmd_header,
                       NULL,
                       WRM_CMD_LEN);

    spi_transfer_bytes(BOARD_CENTAURI_SPI_DEV,
                       BOARD_CENTAURI_SPI_CS_PIN,
                       false /* continous */,
                       (void *)data_out,
                       NULL,
                       size);

    _buf_swap_endianess((uint8_t *)data_out, size);

    return VTPROBE_ERR_SUCCESS;
}

/* Read a half word from address with delay */
int vtprober_read_h_delay(uint32_t address, uint32_t *p_value)
{
    uint8_t data_in[11];
    int length = 7 + _delay_bytes;
    uint8_t *p_data = &data_in[length - 2];
    uint8_t data_out[11] = {
        VTPROBE_CMD_HALF_IN,
        (uint8_t)(address >> 24),
        (uint8_t)(address >> 16),
        (uint8_t)(address >> 8),
        (uint8_t)(address),
        0, 0, 0, 0,
        0, 0
    };

    spi_transfer_bytes(BOARD_CENTAURI_SPI_DEV,
                       BOARD_CENTAURI_SPI_CS_PIN,
                       false /* continous */,
                       data_out,
                       data_in,
                       length);

    *p_value = ((uint32_t)p_data[0] << 8) |
               ((uint32_t)p_data[1]);

    return VTPROBE_ERR_SUCCESS;
}

/* Read a half word from address */
int vtprober_read_h(uint32_t address, uint32_t *p_value)
{
    return vtprober_read_h_delay(address, p_value);
}

/* Read a half word from index of base address with delay */
int vtprober_read_h_indirect_delay(uint32_t index, uint32_t *p_value)
{
    uint8_t data_in[8];
    int length = 4 + _delay_bytes;
    uint8_t *p_data = &data_in[length - 2];
    uint8_t data_out[8] = {
        VTPROBE_CMD_HALF_IN_OFFSET,
        (uint8_t)index,
        0, 0, 0, 0,
        0, 0
    };

    spi_transfer_bytes(BOARD_CENTAURI_SPI_DEV,
                       BOARD_CENTAURI_SPI_CS_PIN,
                       false /* continous */,
                       data_out,
                       data_in,
                       length);

    *p_value = ((uint32_t)p_data[0] << 8) |
               ((uint32_t)p_data[1]);

    return VTPROBE_ERR_SUCCESS;
}

/* Read a half word from index of base address */
int vtprober_read_h_indirect(uint32_t index, uint32_t *p_value)
{
    return vtprober_read_h_indirect_delay(index, p_value);
}

/* Write a half word to address */
int vtprober_write_h(uint32_t address, uint32_t value)
{
    uint8_t data_out[7] = {
        VTPROBE_CMD_HALF_OUT,
        (uint8_t)(address >> 24),
        (uint8_t)(address >> 16),
        (uint8_t)(address >> 8),
        (uint8_t)(address),
        (uint8_t)(value >> 8),
        (uint8_t)(value)
    };

    spi_transfer_bytes(BOARD_CENTAURI_SPI_DEV,
                       BOARD_CENTAURI_SPI_CS_PIN,
                       false /* continous */,
                       data_out,
                       NULL,
                       sizeof(data_out));

    return VTPROBE_ERR_SUCCESS;
}

/* Write a half word to index of the base address */
int vtprober_write_h_indirect(uint32_t index, uint32_t value)
{
    uint8_t data_out[4] = {
        VTPROBE_CMD_HALF_OUT_OFFSET,
        (uint8_t)(index),
        (uint8_t)(value >> 8),
        (uint8_t)(value)
    };

    spi_transfer_bytes(BOARD_CENTAURI_SPI_DEV,
                       BOARD_CENTAURI_SPI_CS_PIN,
                       false /* continous */,
                       data_out,
                       NULL,
                       sizeof(data_out));

    return VTPROBE_ERR_SUCCESS;
}

/* Read a byte from address with delay */
int vtprober_read_b_delay(uint32_t address, uint32_t *p_value)
{
    uint8_t data_in[10];
    int length = 6 + _delay_bytes;
    uint8_t data_out[10] = {
        VTPROBE_CMD_BYTE_IN,
        (uint8_t)(address >> 24),
        (uint8_t)(address >> 16),
        (uint8_t)(address >> 8),
        (uint8_t)(address),
        0, 0, 0, 0,
        0
    };

    spi_transfer_bytes(BOARD_CENTAURI_SPI_DEV,
                       BOARD_CENTAURI_SPI_CS_PIN,
                       false /* continous */,
                       data_out,
                       data_in,
                       length);

    *p_value = data_in[length -  1];

    return VTPROBE_ERR_SUCCESS;
}

/* Read a byte from address */
int vtprober_read_b(uint32_t address, uint32_t *p_value)
{
    return vtprober_read_b_delay(address, p_value);
}

/* Read a byte from index of base address with delay */
int vtprober_read_b_indirect_delay(uint32_t index, uint32_t *p_value)
{
    uint8_t data_in[7];
    int length = 3 + _delay_bytes;
    uint8_t data_out[7] = {
        VTPROBE_CMD_BYTE_IN_OFFSET,
        (uint8_t)index,
        0, 0, 0, 0,
        0
    };

    spi_transfer_bytes(BOARD_CENTAURI_SPI_DEV,
                       BOARD_CENTAURI_SPI_CS_PIN,
                       false /* continous */,
                       data_out,
                       data_in,
                       length);

    *p_value = data_in[length - 1];

    return VTPROBE_ERR_SUCCESS;
}

/* Read a byte from index of base address */
int vtprober_read_b_indirect(uint32_t index, uint32_t *p_value)
{
    return vtprober_read_b_indirect_delay(index, p_value);
}

/* Write a byte to address */
int vtprober_write_b(uint32_t address, uint32_t value)
{
    uint8_t data_out[6] = {
        VTPROBE_CMD_BYTE_OUT,
        (uint8_t)(address >> 24),
        (uint8_t)(address >> 16),
        (uint8_t)(address >> 8),
        (uint8_t)(address),
        (uint8_t)(value)
    };

    spi_transfer_bytes(BOARD_CENTAURI_SPI_DEV,
                       BOARD_CENTAURI_SPI_CS_PIN,
                       false /* continous */,
                       data_out,
                       NULL,
                       sizeof(data_out));

    return VTPROBE_ERR_SUCCESS;
}

/* Write a byte to index of the base address */
int vtprober_write_b_indirect(uint32_t index, uint32_t value)
{
    uint8_t data_out[3] = {
        VTPROBE_CMD_BYTE_OUT_OFFSET,
        (uint8_t)(index),
        (uint8_t)(value)
    };

    spi_transfer_bytes(BOARD_CENTAURI_SPI_DEV,
                       BOARD_CENTAURI_SPI_CS_PIN,
                       false /* continous */,
                       data_out,
                       NULL,
                       sizeof(data_out));

    return VTPROBE_ERR_SUCCESS;
}
