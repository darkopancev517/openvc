#ifndef VTPROBER_H
#define VTPROBER_H

#include <stdint.h>
#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

enum VTPROBER_ERRORS_E {
    VTPROBE_ERR_SUCCESS             = 0,
    VTPROBE_ERR_FAILED              = -1,
    VTPROBE_ERR_INVALID_DEVICE      = -2,
    VTPROBE_ERR_ARGUMENT            = -3,
    VTPROBE_ERR_IO_READ             = -10,
    VTPROBE_ERR_IO_WRITE            = -11,
    VTPROBE_ERR_IO_GENERIC          = -12,
    VTPROBE_ERR_IO_SIZE             = -13,
    VTPROBE_ERR_ACK                 = -20,
    VTPROBE_ERR_CHECKSUM            = -21,
    VTPROBE_ERR_FORMAT              = -22,
    VTPROBE_ERR_ALLOC               = -30,
};

/* Initialize ATE prober */
int vtprober_init(void);

/* Set base address for indirect access */
int vtprober_set_base_addr(uint32_t base_addr);

/* Get base address for indirect access */
int vtprober_get_base_addr(uint32_t *p_base_addr);

/* Set delay cycles. 0 for 1T ~ 0x1F for 32T */
int vtprober_set_delay(uint32_t delay_bytes);

/* Get delay cycles */
int vtprober_get_delay(uint32_t *p_delay_cycles);

/* Read a word from address with delay */
int vtprober_read_w_delay(uint32_t address, uint32_t *p_value);

/* Read a word from address */
int vtprober_read_w(uint32_t address, uint32_t *p_value);

/* Read a word from index of base address with delay */
int vtprober_read_w_indirect_delay(uint32_t index, uint32_t *p_value);

/* Read a word from index of base address */
int vtprober_read_w_indirect(uint32_t index, uint32_t *p_value);

/* Read word in a burst */
int vtprober_read_w_burst(uint32_t burst_len, uint32_t address, uint32_t *p_value, uint32_t read_len);

/* Write a word to address */
int vtprober_write_w(uint32_t address, uint32_t value);

/* Write a word to index of the base address */
int vtprober_write_w_indirect(uint32_t index, uint32_t value);

/* Write a word in a burst */
int vtprober_write_w_burst(uint32_t burst_len, uint32_t address, uint8_t *data_out, uint32_t size);

/* Read a half word from address with delay */
int vtprober_read_h_delay(uint32_t address, uint32_t *p_value);

/* Read a half word from address */
int vtprober_read_h(uint32_t address, uint32_t *p_value);

/* Read a half word from index of base address with delay */
int vtprober_read_h_indirect_delay(uint32_t index, uint32_t *p_value);

/* Read a half word from index of base address */
int vtprober_read_h_indirect(uint32_t index, uint32_t *p_value);

/* Write a half word to address */
int vtprober_write_h(uint32_t address, uint32_t value);

/* Write a half word to index of the base address */
int vtprober_write_h_indirect(uint32_t index, uint32_t value);

/* Read a byte from address with delay */
int vtprober_read_b_delay(uint32_t address, uint32_t *p_value);

/* Read a byte from address */
int vtprober_read_b(uint32_t address, uint32_t *p_value);

/* Read a byte from index of base address with delay */
int vtprober_read_b_indirect_delay(uint32_t index, uint32_t *p_value);

/* Read a byte from index of base address */
int vtprober_read_b_indirect(uint32_t index, uint32_t *p_value);

/* Write a byte to address */
int vtprober_write_b(uint32_t address, uint32_t value);

/* Write a byte to index of the base address */
int vtprober_write_b_indirect(uint32_t index, uint32_t value);

#ifdef __cplusplus
}
#endif

#endif /* VTPROBER_H */
