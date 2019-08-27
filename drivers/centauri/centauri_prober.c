#include "vtprober.h"
#include "centauri_prober.h"

void cent_spi_prober_init(void)
{
    vtprober_init();
}

void cent_spi_set_base_addr(uint32_t base_address)
{
    vtprober_set_base_addr(base_address);
}

void cent_spi_regW_ind(uint32_t offset, uint32_t val, uint32_t clear)
{
    uint32_t reg_val;

    vtprober_read_w_indirect_delay(offset, &reg_val);

    reg_val &= clear;
    reg_val |= val;

    vtprober_write_w_indirect(offset, reg_val);
}

void cent_spi_regW(uint32_t address, uint32_t val, uint32_t clear)
{
    uint32_t reg_val;

    vtprober_read_w(address, &reg_val);

    reg_val &= clear;
    reg_val |= val;

    vtprober_write_w(address, reg_val);
}

void cent_spi_readW(uint32_t address, uint32_t *val)
{
    //vtprober_set_delay(2);
    vtprober_read_w_delay(address, val);
}

void cent_spi_writeW(uint32_t address, uint32_t val)
{
    vtprober_write_w(address, val);
}

uint32_t CentauriCsrRead(uint32_t csr_addr)
{
    uint32_t csr_val = 0xdeadbeef;
    cent_spi_readW(csr_addr, &csr_val);
    return csr_val;
}

void CentauriCsrWrite(uint32_t csr_addr, uint32_t csr_val)
{
    cent_spi_writeW(csr_addr, csr_val);
}
