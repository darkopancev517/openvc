#ifndef CENTAURI_PROBER_H
#define CENTAURI_PROBER_H

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

#define NOTCARE     (0xffffffff)
#define REGCLEAR    (0)

void cent_spi_prober_init(void);

void cent_spi_set_base_addr(uint32_t base_address);

void cent_spi_regW_ind(uint32_t offset, uint32_t val, uint32_t clear);

void cent_spi_regW(uint32_t address, uint32_t val, uint32_t clear);

void cent_spi_readW(uint32_t address, uint32_t *val);

void cent_spi_writeW(uint32_t address, uint32_t val);

uint32_t CentauriCsrRead(uint32_t csr_addr);

void CentauriCsrWrite(uint32_t csr_addr, uint32_t csr_val);

#ifdef __cplusplus
}
#endif

#endif /* CENTAURI_PROBER_H */
