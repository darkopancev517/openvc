/**
 * Copyright (c) 2018 Vertexcom Technologies, Inc. All rights reserved
 * Vertexcom Confidential Proprietary
 *
*/

#include "vcsoc.h"

#define VCREG_BASE_MEM          0x40020000
#define VCREG_BASE_CACHE        (VCREG_BASE_MEM + 0xC)
#define VCREG_BASE_EMBFLASH     (VCREG_BASE_MEM + 0x40)

#define VCREG_BASE_SPIFLASH     VCREG_BASE_MEM
#define SPIFLASH_BUF_OFFSET     0x100
#define VCREG_BASE_SPIFLASH_BUF(n) (VCREG_BASE_SPIFLASH + SPIFLASH_BUF_OFFSET + (n*4))

#define VCREG_BASE_SPISRAM      VCREG_BASE_MEM

#define EMBFLASH_PASS_KEY       0x55AAAA55
#define EMBFLASH_SERASE_KEY     0xAA5555AA
#define EMBFLASH_CERASE_KEY     0xAA5555AA
#define EMBFLASH_NVRPASS_KEY    0xAA5555AA
#define EMBFLASH_DSTB_KEY       0xAA5555AA

#define WINBOND_CMDID_WRSR1             0x01    // write status register 1
#define WINBOND_CMDID_WRSR2             0x31    // write status register 2
#define WINBOND_CMDID_RDSR1             0x05    // read status register 1
#define WINBOND_CMDID_RDSR2             0x35    // read status register 2
#define WINBOND_CMDID_PAGE_PROG         0x02    // page program
#define WINBOND_CMDID_READ_DATA         0x03    // read data
#define WINBOND_CMDID_WRITE_DISABLE     0x04    // write disable
#define WINBOND_CMDID_WRITE_ENABLE      0x06    // write enable
#define WINBOND_CMDID_FAST_READ         0x0B    // fast read
#define WINBOND_CMDID_RDCR              0x15    // read configuration register
#define WINBOND_CMDID_SECTOR_ERASE      0x20    // sector erase
#define WINBOND_CMDID_QUADPAGE_PROG     0x32    // quad page program
#define WINBOND_CMDID_BLOCK_ERASE_32K   0x52    // 32K block erase
#define WINBOND_CMDID_BLOCK_ERASE_64K   0xD8    // 64K block erase
#define WINBOND_CMDID_CHIP_ERASE        0xC7    // chip erase

#define ISSI_SRAM_CMDID_READ   0x03     // Read data from memory array beginning at selected address
#define ISSI_SRAM_CMDID_WRITE  0x02     // Write data to memory arrary beginning at selected address
#define ISSI_SRAM_CMDID_ESDI   0x3B     // Enter SDI mode
#define ISSI_SRAM_CMDID_ESQI   0x38     // Enter SQI mode
#define ISSI_SRAM_CMDID_RSTDQI 0xff     // Reset SDI/SQI mode
#define ISSI_SRAM_CMDID_RDMR   0x05     // Read mode register
#define ISSI_SRAM_CMDID_WRMR   0x01     // Write mode register

// MEM CACHE ----------------------------------------------

struct VCMEM_REG_CACHECFG {
    union {
        struct {
            uint32_t EN         : 1;    // (rw) cache enable control reg
            uint32_t SIZE       : 1;    // (rw) cache size control reg [0: 8KB, 1: 4KB]
            uint32_t HITEN      : 1;    // (rw) hit rate calculation enable register
            uint32_t reserverd  : 29;
        } fields;

        uint32_t value;
    };
};

struct VCMEM_REG_CACINVS {
    union {
        struct {
            uint32_t INVS       : 25;   // (r) cache invalid start addr
            uint32_t reserverd  : 7;
        } fields;

        uint32_t value;
    };
};

struct VCMEM_REG_CACINVE {
    union {
        struct {
            uint32_t INVE       : 25;   // (r) cache invalid end addr
            uint32_t reserverd  : 7;
        } fields;

        uint32_t value;
    };
};

struct VCMEM_REG_CACINV {
    uint32_t value;                     // (w) cache invalid active
};

struct VCMEM_REG_CACHIT {
    union {
        struct {
            uint32_t HITRATE    : 16;   // (r) cache hit rate status register
            uint32_t reserved   : 16;
        } fields;

        uint32_t value;
    };
};

struct VCMEM_REG_CACHITL {
    union {
        struct {
            uint32_t HITRATEL   : 16;   // (rw) cache hit rate lowest value status register
            uint32_t reserved   : 16;
        } fields;

        uint32_t value;
    };
};

struct VCMEM_CACHE_REG_SPACE {
    struct VCMEM_REG_CACHECFG   CACHECFG;
    uint32_t reserved[4];
    struct VCMEM_REG_CACINVS    CACINVS;
    struct VCMEM_REG_CACINVE    CACINVE;
    struct VCMEM_REG_CACINV     CACINV;
    uint32_t reserved1;
    struct VCMEM_REG_CACHIT     CACHIT;
    struct VCMEM_REG_CACHITL    CACHITL;
};

// EMBFLASH -----------------------------------------------

struct VCEMBFLASH_REG_CTRL {
    union {
        struct {
            uint32_t CSMODE     : 2;
            uint32_t reserved   : 2;
            uint32_t READM0     : 1;
            uint32_t READM1     : 1;
            uint32_t NVR        : 1;
            uint32_t reserved1  : 25;
        } fields;

        uint32_t value;
    };
};

struct VCEMBFLASH_REG_PASS {
    union {
        struct {
            uint32_t UNLOCK     : 1;
            uint32_t reserved   : 31;
        } fields;

        uint32_t value;
    };
};

struct VCEMBFLASH_REG_PGADDR {
    union {
        struct {
            uint32_t PGADDR     : 19;
            uint32_t reserved   : 13;
        } fields;

        uint32_t value;
    };
};

struct VCEMBFLASH_REG_PGDATA {
    uint32_t value;
};

struct VCEMBFLASH_REG_SERASE {
    union {
        struct {
            uint32_t SERASE     : 1;
            uint32_t reserved   : 31;
        } fields;

        uint32_t value;
    };
};

struct VCEMBFLASH_REG_CERASE {
    union {
        struct {
            uint32_t CERASE     : 1;
            uint32_t reserved   : 31;
        } fields;

        uint32_t value;
    };
};

struct VCEMBFLASH_REG_CSSADDR {
    union {
        struct {
            uint32_t CSSADDR    : 19;
            uint32_t reserved   : 13;
        } fields;;

        uint32_t value;
    };
};

struct VCEMBFLASH_REG_CSEADDR {
    union {
        struct {
            uint32_t CSEADDR    : 19;
            uint32_t reserved   : 13;
        } fields;

        uint32_t value;
    };
};

struct VCEMBFLASH_REG_CSVALUE {
    uint32_t value;                     // (r) checksum latched value register
};

struct VCEMBFLASH_REG_CSCVALUE {
    uint32_t value;                     // (rw) checksum compare value register
};

struct VCEMBFLASH_REG_INTEN {
    union {
        struct {
            uint32_t INTEN0     : 1;    // (rw) hit rate lowest value detected interrupt enable
            uint32_t INTEN1     : 1;    // (rw) hit rate done interrupt enable register
            uint32_t INTEN2     : 1;    // (rw) checksum error interrupt enable control register
            uint32_t INTEN3     : 1;    // (rw) checkum done interrupt enable control register
            uint32_t reserved   : 28;
        } fields;

        uint32_t value;
    };
};

struct VCEMBFLASH_REG_INT {
    union {
        struct {
            uint32_t CSDONE     : 1;    // (rc) checksum done status bit
            uint32_t CSERR      : 1;    // (rc) checksum error status bit
            uint32_t HRDONE     : 1;    // (rc) hit rate calculation done status bit
            uint32_t HRLDET     : 1;    // (rc) hit rate lowest value detected status bit
            uint32_t reserved   : 28;
        } fields;

        uint32_t value;
    };
};

struct VCEMBFLASH_REG_RPROT {
    uint32_t value;
};

struct VCEMBFLASH_REG_WPROT {
    uint32_t value;
};

struct VCEMBFLASH_REG_NVRPASS {
    union {
        struct {
            uint32_t NVRUNLOCK  : 1;
            uint32_t reserved   : 31;
        } fields;

        uint32_t value;
    };
};

struct VCEMBFLASH_REG_STS {
    union {
        struct {
            uint32_t STS        : 5;    // (r) 1: flash control in idle state, other is in busy state
            uint32_t reserved   : 27;
        } fields;

        uint32_t value;
    };
};

struct VCEMBFLASH_REG_CONF {
    uint32_t value;
};

struct VCEMBFLASH_REG_DSTB {
    union {
        struct {
            uint32_t DSTB       : 1;
            uint32_t reserved   : 31;
        } fields;

        uint32_t value;
    };
};

struct VCEMBFLASH_REG_PTIME {
    union {
        struct {
            uint32_t PTIME      : 8;    // (rw) program time = (PTIME + 1)*1us
            uint32_t reserved   : 24;
        } fields;

        uint32_t value;
    };
};

struct VCEMBFLASH_REG_ETIME {
    union {
        struct {
            uint32_t ETIME      : 16;   // (rw) erase time = (ETIME + 1)*1us
            uint32_t reserved   : 16;
        } fields;

        uint32_t value;
    };
};

struct VCEMBFLASH_REG_SPACE {
    struct VCEMBFLASH_REG_CTRL      CTRL;
    struct VCEMBFLASH_REG_PASS      PASS;
    struct VCEMBFLASH_REG_PGADDR    PGADDR;
    struct VCEMBFLASH_REG_PGDATA    PGDATA;
    struct VCEMBFLASH_REG_SERASE    SERASE;
    uint32_t reserved;
    struct VCEMBFLASH_REG_CERASE    CERASE;
    uint32_t reserved1;
    struct VCEMBFLASH_REG_CSSADDR   CSSADDR;
    struct VCEMBFLASH_REG_CSEADDR   CSEADDR;
    struct VCEMBFLASH_REG_CSVALUE   CSVALUE;
    struct VCEMBFLASH_REG_CSCVALUE  CSCVALUE;
    struct VCEMBFLASH_REG_INTEN     INTEN;
    struct VCEMBFLASH_REG_INT       INT;
    struct VCEMBFLASH_REG_RPROT     RPROT;
    struct VCEMBFLASH_REG_WPROT     WPROT;
    uint32_t reserved2;
    struct VCEMBFLASH_REG_NVRPASS   NVRPASS;
    struct VCEMBFLASH_REG_STS       STS;
    uint32_t reserved3[4];
    struct VCEMBFLASH_REG_CONF      CONF;
    struct VCEMBFLASH_REG_DSTB      DSTB;
    uint32_t reserved4[3];
    struct VCEMBFLASH_REG_PTIME     PTIME;
    struct VCEMBFLASH_REG_ETIME     ETIME;
};

// SPIFLASH -----------------------------------------------

struct VCSPIFLASH_REG_CMD {
    union {
        struct {
            uint32_t CMDID      : 8;    // (rw) command id register
            uint32_t CMDDATA    : 1;    // (rw) command data control, 0: without data, 1: with data
            uint32_t CMDWR      : 1;    // (rw) command read/write control, 0: read, 1: write
            uint32_t CMDADDR    : 1;    // (rw) command addr control, 0: without addr, 1: with addr
            uint32_t CMDADDR4   : 1;    // (rw) 0: 3 bytes addr cmd, 1: 4 bytes addr cmd
            uint32_t CMDMODE    : 3;    // (rw) command mode ctrl register
            uint32_t reserved   : 1;
            uint32_t LENGTH     : 8;    // (rw) data length register: 1 - 256 bytes
            uint32_t POLL       : 1;    // (rw) flash polling type command ctrl register
            uint32_t SRAMCMD    : 1;    // (rw) 0: send cmd to SPI FLASH, 1: send cmd to SPI SRAM
            uint32_t reserved1  : 5;
            uint32_t ACT        : 1;    // (rw) flash cmd active register
        } fields;

        uint32_t value;
    };
};

struct VCSPIFLASH_REG_ADDR {
    uint32_t value;
};

struct VCSPIFLASH_REG_CFG {
    union {
        struct {
            uint32_t CMDCLK     : 4;    // (rw) cmd access clock speed control
            uint32_t MEMCLK     : 4;    // (rw) spi flash memory access clock speed control
            uint32_t SIZE       : 3;    // (rw) spi flash size control register
            uint32_t reserved   : 1;
            uint32_t MEMMODE    : 3;    // (rw) spi flash memory mode control register
            uint32_t reserved1  : 1;
            uint32_t CMDLAT     : 2;    // (rw) cmd access data latch timing control
            uint32_t MEMLAT     : 2;    // (rw) spi flash memory access data latch timing control
            uint32_t TYPE       : 1;
            uint32_t PERFENHC   : 1;    // (rw) performance enhance control
            uint32_t reserved2  : 1;
            uint32_t MEMADDR4   : 1;    // (rw) spi flash memory access address byte number control
            uint32_t reserved3  : 8;
        } fields;

        uint32_t value;
    };
};

struct VCSPIFLASH_REG_SR {
    union {
        struct {
            uint32_t SR         : 8;    // (r) spi flash status register
            uint32_t reserved   : 24;
        } fields;

        uint32_t value;
    };
};

struct VCSPIFLASH_REG_ID {
    union {
        struct {
            uint32_t DEV_ID     : 8;    // (r) spi flash device ID register
            uint32_t MANU_ID    : 8;    // (r) spi flash manufacture ID register
            uint32_t reserved   : 16;
        } fields;

        uint32_t value;
    };
};

struct VCSPIFLASH_REG_SPACE {
    struct VCSPIFLASH_REG_CMD   CMD;
    struct VCSPIFLASH_REG_ADDR  ADDR;
    struct VCSPIFLASH_REG_CFG   CFG;
    uint32_t reserved;
    struct VCSPIFLASH_REG_SR    SR;
    struct VCSPIFLASH_REG_ID    ID;
};

// SPISRAM ------------------------------------------------
struct VCSPISRAM_REG_CFG {
    union {
        struct {
            uint32_t SRAMEN     : 1;
            uint32_t reserved   : 3;
            uint32_t SRAMCLK    : 4;
            uint32_t SRAMSIZE   : 3;
            uint32_t reserved2  : 1;
            uint32_t SRAMMODE   : 3;
            uint32_t reserved3  : 3;
            uint32_t SRAMLAT    : 2;
            uint32_t reserved4  : 3;
            uint32_t SRAMADDR4  : 1;
            uint32_t reserved5  : 8;
        } fields;

        uint32_t value;
    };
};

struct VCSPISRAM_REG_CMD {
    union {
        struct {
            uint32_t CMDID      : 8;    // (rw) command id register
            uint32_t CMDDATA    : 1;    // (rw) command data control, 0: without data, 1: with data
            uint32_t CMDWR      : 1;    // (rw) command read/write control, 0: read, 1: write
            uint32_t CMDADDR    : 1;    // (rw) command addr control, 0: without addr, 1: with addr
            uint32_t CMDADDR4   : 1;    // (rw) 0: 3 bytes addr cmd, 1: 4 bytes addr cmd
            uint32_t CMDMODE    : 3;    // (rw) command mode ctrl register
            uint32_t reserved   : 1;
            uint32_t LENGTH     : 8;    // (rw) data length register: 1 - 256 bytes
            uint32_t POLL       : 1;    // (rw) flash polling type command ctrl register
            uint32_t SRAMCMD    : 1;    // (rw) 0: send cmd to SPI FLASH, 1: send cmd to SPI SRAM
            uint32_t reserved1  : 5;
            uint32_t ACT        : 1;    // (rw) flash cmd active register
        } fields;

        uint32_t value;
    };
};


struct VCSPISRAM_REG_SPACE {
    struct VCSPISRAM_REG_CMD    CMD;
    uint32_t reserved[6];
    struct VCSPISRAM_REG_CFG    CFG;
};

void vcmem_reset_cache(void)
{
    volatile struct VCMEM_CACHE_REG_SPACE *reg_space = (volatile struct VCMEM_CACHE_REG_SPACE *)VCREG_BASE_CACHE;

    reg_space->CACHECFG.fields.EN = 1;      // enable cache by default
    reg_space->CACHECFG.fields.SIZE = 0;    // 8KB cache size by default
    reg_space->CACHECFG.fields.HITEN = 0;   // disable cache hit rate calculation by default
}

void vcmem_enable_cache(void)
{
    volatile struct VCMEM_CACHE_REG_SPACE *reg_space = (volatile struct VCMEM_CACHE_REG_SPACE *)VCREG_BASE_CACHE;

    reg_space->CACHECFG.fields.EN = 1;
}

void vcmem_disable_cache(void)
{
    volatile struct VCMEM_CACHE_REG_SPACE *reg_space = (volatile struct VCMEM_CACHE_REG_SPACE *)VCREG_BASE_CACHE;

    reg_space->CACHECFG.fields.EN = 0;
}

void vcmem_config_cache_size(uint8_t size)
{
    if ((size > 1) || (size < 0)) return;

    volatile struct VCMEM_CACHE_REG_SPACE *reg_space = (volatile struct VCMEM_CACHE_REG_SPACE *)VCREG_BASE_CACHE;

    reg_space->CACHECFG.fields.SIZE = size;
}

void vcmem_disable_cache_hitrate(void)
{
    volatile struct VCMEM_CACHE_REG_SPACE *reg_space = (volatile struct VCMEM_CACHE_REG_SPACE *)VCREG_BASE_CACHE;

    reg_space->CACHECFG.fields.HITEN = 0;
}

void vcmem_enable_cache_hitrate(void)
{
    volatile struct VCMEM_CACHE_REG_SPACE *reg_space = (volatile struct VCMEM_CACHE_REG_SPACE *)VCREG_BASE_CACHE;

    reg_space->CACHECFG.fields.HITEN = 1;
}

void vcembflash_config_wait_cycle(uint8_t wait_cycle)
{
    vcmisc_config_embflash_wait_cycle(wait_cycle);
}

void vcembflash_config_csmode(uint8_t mode)
{
    if ((mode < 0) || (mode > 3)) return;

    volatile struct VCEMBFLASH_REG_SPACE *reg_space = (volatile struct VCEMBFLASH_REG_SPACE *)VCREG_BASE_EMBFLASH;

    reg_space->CTRL.fields.CSMODE = mode;
}

void vcembflash_config_csrange(uint32_t addr_start, uint32_t addr_end)
{
    volatile struct VCEMBFLASH_REG_SPACE *reg_space = (volatile struct VCEMBFLASH_REG_SPACE *)VCREG_BASE_EMBFLASH;

    reg_space->CSSADDR.value = addr_start;
    reg_space->CSEADDR.value = addr_end;
}

void vcembflash_config_cscomp_value(uint32_t cs)
{
    volatile struct VCEMBFLASH_REG_SPACE *reg_space = (volatile struct VCEMBFLASH_REG_SPACE *)VCREG_BASE_EMBFLASH;

    reg_space->CSCVALUE.value = cs;
}

uint32_t vcembflash_get_cs(void)
{
    volatile struct VCEMBFLASH_REG_SPACE *reg_space = (volatile struct VCEMBFLASH_REG_SPACE *)VCREG_BASE_EMBFLASH;

    return reg_space->CSVALUE.value;
}

void vcembflash_enable_int(uint8_t interrupt)
{
    if ((interrupt < 0) || (interrupt > 3)) return;

    volatile struct VCEMBFLASH_REG_SPACE *reg_space = (volatile struct VCEMBFLASH_REG_SPACE *)VCREG_BASE_EMBFLASH;

    reg_space->INTEN.value |= (1 << interrupt);
}

void vcembflash_disable_int(uint8_t interrupt)
{
    if ((interrupt < 0) || (interrupt > 3)) return;

    volatile struct VCEMBFLASH_REG_SPACE *reg_space = (volatile struct VCEMBFLASH_REG_SPACE *)VCREG_BASE_EMBFLASH;

    reg_space->INTEN.value &= ~(1 << interrupt);
}

int vcembflash_get_int(uint8_t interrupt)
{
    if ((interrupt < 0) || (interrupt > 3)) return 0;

    volatile struct VCEMBFLASH_REG_SPACE *reg_space = (volatile struct VCEMBFLASH_REG_SPACE *)VCREG_BASE_EMBFLASH;

    return (reg_space->INT.value & (1 << interrupt)) ? 1 : 0;
}

void vcembflash_clear_int(uint8_t interrupt)
{
    if ((interrupt < 0) || (interrupt > 3)) return;

    volatile struct VCEMBFLASH_REG_SPACE *reg_space = (volatile struct VCEMBFLASH_REG_SPACE *)VCREG_BASE_EMBFLASH;

    reg_space->INT.value = (1 << interrupt);
}

void vcembflash_unlock(void)
{
    volatile struct VCEMBFLASH_REG_SPACE *reg_space = (volatile struct VCEMBFLASH_REG_SPACE *)VCREG_BASE_EMBFLASH;

    //vcmem_disable_cache();

    reg_space->PASS.value = EMBFLASH_PASS_KEY;
}

void vcembflash_lock(void)
{
    volatile struct VCEMBFLASH_REG_SPACE *reg_space = (volatile struct VCEMBFLASH_REG_SPACE *)VCREG_BASE_EMBFLASH;

    reg_space->PASS.value = 0;

    //vcmem_enable_cache();
}

void vcembflash_erase_sector(uint32_t addr)
{
    volatile struct VCEMBFLASH_REG_SPACE *reg_space = (volatile struct VCEMBFLASH_REG_SPACE *)VCREG_BASE_EMBFLASH;

    reg_space->PGADDR.value = addr;
    reg_space->SERASE.value = EMBFLASH_SERASE_KEY;

    // wait until sector erase is finish
    while (reg_space->SERASE.fields.SERASE != 0);
}

void vcembflash_erase_chip(void)
{
    volatile struct VCEMBFLASH_REG_SPACE *reg_space = (volatile struct VCEMBFLASH_REG_SPACE *)VCREG_BASE_EMBFLASH;

    reg_space->PGADDR.value = 0;
    reg_space->CERASE.value = EMBFLASH_CERASE_KEY;

    // wait until sector erase is finish
    while (reg_space->CERASE.fields.CERASE != 0);
}

void vcembflash_program_word(uint32_t addr, uint32_t word)
{
    volatile struct VCEMBFLASH_REG_SPACE *reg_space = (volatile struct VCEMBFLASH_REG_SPACE *)VCREG_BASE_EMBFLASH;

    reg_space->PGADDR.value = addr;
    reg_space->PGDATA.value = word;

    // wait until write is finish
    while (reg_space->STS.fields.STS != 1);
}

void vcembflash_program_byte(uint32_t addr, uint8_t byte)
{
    volatile struct VCEMBFLASH_REG_SPACE *reg_space = (volatile struct VCEMBFLASH_REG_SPACE *)VCREG_BASE_EMBFLASH;

    reg_space->PGADDR.value = addr;
    if ((addr&0x3) == 0) {
        *((volatile uint8_t *)(&reg_space->PGDATA)) = byte;
    } else if ((addr&0x3) == 1) {
        *((volatile uint8_t *)(&reg_space->PGDATA) + 1) = byte;
    } else if ((addr&0x3) == 2) {
        *((volatile uint8_t *)(&reg_space->PGDATA) + 2) = byte;
    } else {
        *((volatile uint8_t *)(&reg_space->PGDATA) + 3) = byte;
    }
    
    // wait until write is finish
    while (reg_space->STS.fields.STS != 1);
}

void vcspiflash_config_type(uint8_t vendor)
{
    if (vendor > SPIFLASH_MXIC) return;

    volatile struct VCSPIFLASH_REG_SPACE *reg = (volatile struct VCSPIFLASH_REG_SPACE *)VCREG_BASE_SPIFLASH;

    reg->CFG.fields.TYPE = vendor;
}

void vcspiflash_config_cmdclk_div(uint8_t div)
{
    if ((div > 16) || (div <= 0)) return;

    volatile struct VCSPIFLASH_REG_SPACE *reg = (volatile struct VCSPIFLASH_REG_SPACE *)VCREG_BASE_SPIFLASH;

    reg->CFG.fields.CMDCLK = div - 1;
}

void vcspiflash_config_memclk_div(uint8_t div)
{
    if ((div > 16) || (div <= 0)) return;

    volatile struct VCSPIFLASH_REG_SPACE *reg = (volatile struct VCSPIFLASH_REG_SPACE *)VCREG_BASE_SPIFLASH;

    reg->CFG.fields.MEMCLK = div - 1;
}

void vcspiflash_config_size(uint8_t size)
{
    if ((size > SPIFLASH_SIZE_64MBIT) || (size < SPIFLASH_SIZE_512KBIT)) return;

    volatile struct VCSPIFLASH_REG_SPACE *reg = (volatile struct VCSPIFLASH_REG_SPACE *)VCREG_BASE_SPIFLASH;

    reg->CFG.fields.SIZE = size;
}

void vcspiflash_config_memmode(uint8_t mode)
{
    if ((mode > SPIFLASH_MEMMODE_4I4O) || (mode < SPIFLASH_MEMMODE_1I1O)) return;

    volatile struct VCSPIFLASH_REG_SPACE *reg = (volatile struct VCSPIFLASH_REG_SPACE *)VCREG_BASE_SPIFLASH;

    reg->CFG.fields.MEMMODE = mode;
}

void vcspiflash_config_cmdlatency(uint8_t lat)
{
    if ((lat > SPIFLASH_CMDLAT_3) || (lat < SPIFLASH_CMDLAT_0)) return;

    volatile struct VCSPIFLASH_REG_SPACE *reg = (volatile struct VCSPIFLASH_REG_SPACE *)VCREG_BASE_SPIFLASH;

    reg->CFG.fields.CMDLAT = lat;
}

void vcspiflash_config_memlatency(uint8_t lat)
{
    if ((lat > SPIFLASH_MEMLAT_3) || (lat < SPIFLASH_MEMLAT_0)) return;

    volatile struct VCSPIFLASH_REG_SPACE *reg = (volatile struct VCSPIFLASH_REG_SPACE *)VCREG_BASE_SPIFLASH;

    reg->CFG.fields.MEMLAT = lat;
}

void vcspiflash_config_perf_enhc(bool state)
{
    volatile struct VCSPIFLASH_REG_SPACE *reg = (volatile struct VCSPIFLASH_REG_SPACE *)VCREG_BASE_SPIFLASH;

    reg->CFG.fields.PERFENHC = (state == true) ? 1 : 0;
}

void vcspiflash_config_memaddr_bytes(uint8_t bytes)
{
    if ((bytes > SPIFLASH_MEMADDR_4BYTES) || (bytes < SPIFLASH_MEMADDR_3BYTES)) return;

    volatile struct VCSPIFLASH_REG_SPACE *reg = (volatile struct VCSPIFLASH_REG_SPACE *)VCREG_BASE_SPIFLASH;

    reg->CFG.fields.MEMADDR4 = bytes;
}

void vcspiflash_config_spimux(uint8_t spimux)
{
    vcsfio_config_spimux(spimux);

    if ((spimux == SPIMUX0) || (spimux == SPIMUX2)) {
        vcsfio_enable_iob_spiflash();
    }
}

void vcspiflash_write_enable(void)
{
    volatile struct VCSPIFLASH_REG_SPACE *reg = (volatile struct VCSPIFLASH_REG_SPACE *)VCREG_BASE_SPIFLASH;
    uint32_t value = 0;

    ((struct VCSPIFLASH_REG_CMD *)&value)->fields.ACT = 1;
    ((struct VCSPIFLASH_REG_CMD *)&value)->fields.POLL = 1;

    if (reg->CFG.fields.TYPE == SPIFLASH_WINBOND) {
        ((struct VCSPIFLASH_REG_CMD *)&value)->fields.CMDID = WINBOND_CMDID_WRITE_ENABLE;
    }

    reg->CMD.value = value;

    // wait for status register1 write enlatch
    while ((reg->SR.value & 0x2) != 0x2);
}

void vcspiflash_quad_enable(void)
{
    vcsfio_enable_iob_quadmode_spiflash();

    volatile struct VCSPIFLASH_REG_SPACE *reg = (volatile struct VCSPIFLASH_REG_SPACE *)VCREG_BASE_SPIFLASH;
    volatile uint32_t *reg_buf = (volatile uint32_t *)VCREG_BASE_SPIFLASH_BUF(0);
    uint32_t value = 0;

    // wait until spiflash not active
    while ((reg->SR.value & 0x1) == 1);

    vcspiflash_write_enable();

    ((struct VCSPIFLASH_REG_CMD *)&value)->fields.ACT = 1;
    ((struct VCSPIFLASH_REG_CMD *)&value)->fields.CMDWR = 1;
    ((struct VCSPIFLASH_REG_CMD *)&value)->fields.CMDDATA = 1;
    ((struct VCSPIFLASH_REG_CMD *)&value)->fields.POLL = 1;

    if (reg->CFG.fields.TYPE == SPIFLASH_WINBOND) {
        *reg_buf = 0x02;
        ((struct VCSPIFLASH_REG_CMD *)&value)->fields.CMDID = WINBOND_CMDID_WRSR2;
    }

    reg->CMD.value = value;

    while ((reg->SR.value & 0x1) == 1);
}


void vcspiflash_erase_chip(void)
{
    volatile struct VCSPIFLASH_REG_SPACE *reg = (volatile struct VCSPIFLASH_REG_SPACE *)VCREG_BASE_SPIFLASH;
    uint32_t value = 0;

    //vcmem_disable_cache();

    vcspiflash_write_enable();

    ((struct VCSPIFLASH_REG_CMD *)&value)->fields.ACT = 1;
    ((struct VCSPIFLASH_REG_CMD *)&value)->fields.POLL = 1;
    ((struct VCSPIFLASH_REG_CMD *)&value)->fields.LENGTH = 0;
    ((struct VCSPIFLASH_REG_CMD *)&value)->fields.CMDMODE = 0;
    ((struct VCSPIFLASH_REG_CMD *)&value)->fields.CMDADDR4 = 0;
    ((struct VCSPIFLASH_REG_CMD *)&value)->fields.CMDADDR = 0;
    ((struct VCSPIFLASH_REG_CMD *)&value)->fields.CMDWR = 1;
    ((struct VCSPIFLASH_REG_CMD *)&value)->fields.CMDDATA = 0;

    if (reg->CFG.fields.TYPE == SPIFLASH_WINBOND) {
        ((struct VCSPIFLASH_REG_CMD *)&value)->fields.CMDID = WINBOND_CMDID_CHIP_ERASE;
    }

    reg->CMD.value = value;

    while ((reg->SR.value & 0x1) == 1);

    //vcmem_enable_cache();
}

void vcspiflash_erase_sector(uint32_t addr)
{
    volatile struct VCSPIFLASH_REG_SPACE *reg = (volatile struct VCSPIFLASH_REG_SPACE *)VCREG_BASE_SPIFLASH;
    uint32_t value = 0;

    //vcmem_disable_cache();

    vcspiflash_write_enable();

    ((struct VCSPIFLASH_REG_CMD *)&value)->fields.ACT = 1;
    ((struct VCSPIFLASH_REG_CMD *)&value)->fields.POLL = 1;
    ((struct VCSPIFLASH_REG_CMD *)&value)->fields.LENGTH = 0;
    ((struct VCSPIFLASH_REG_CMD *)&value)->fields.CMDMODE = 0;
    ((struct VCSPIFLASH_REG_CMD *)&value)->fields.CMDADDR4 = 0;
    ((struct VCSPIFLASH_REG_CMD *)&value)->fields.CMDADDR = 1;
    ((struct VCSPIFLASH_REG_CMD *)&value)->fields.CMDWR = 1;
    ((struct VCSPIFLASH_REG_CMD *)&value)->fields.CMDDATA = 0;

    if (reg->CFG.fields.TYPE == SPIFLASH_WINBOND) {
        ((struct VCSPIFLASH_REG_CMD *)&value)->fields.CMDID = WINBOND_CMDID_SECTOR_ERASE;
    }

    reg->ADDR.value = addr;
    reg->CMD.value = value;

    while ((reg->SR.value & 0x1) == 1);

    //vcmem_enable_cache();
}

void vcspiflash_erase_64kb_block(uint32_t addr)
{
    volatile struct VCSPIFLASH_REG_SPACE *reg = (volatile struct VCSPIFLASH_REG_SPACE *)VCREG_BASE_SPIFLASH;
    uint32_t value = 0;

    //vcmem_disable_cache();

    vcspiflash_write_enable();

    ((struct VCSPIFLASH_REG_CMD *)&value)->fields.ACT = 1;
    ((struct VCSPIFLASH_REG_CMD *)&value)->fields.POLL = 1;
    ((struct VCSPIFLASH_REG_CMD *)&value)->fields.LENGTH = 0;
    ((struct VCSPIFLASH_REG_CMD *)&value)->fields.CMDMODE = 0;
    ((struct VCSPIFLASH_REG_CMD *)&value)->fields.CMDADDR4 = 0;
    ((struct VCSPIFLASH_REG_CMD *)&value)->fields.CMDADDR = 1;
    ((struct VCSPIFLASH_REG_CMD *)&value)->fields.CMDWR = 1;
    ((struct VCSPIFLASH_REG_CMD *)&value)->fields.CMDDATA = 0;

    if (reg->CFG.fields.TYPE == SPIFLASH_WINBOND) {
        ((struct VCSPIFLASH_REG_CMD *)&value)->fields.CMDID = WINBOND_CMDID_BLOCK_ERASE_64K;
    }

    reg->ADDR.value = addr;
    reg->CMD.value = value;

    while ((reg->SR.value & 0x1) == 1);

    //vcmem_enable_cache();
}

void vcspiflash_erase_32kb_block(uint32_t addr)
{
    volatile struct VCSPIFLASH_REG_SPACE *reg = (volatile struct VCSPIFLASH_REG_SPACE *)VCREG_BASE_SPIFLASH;
    uint32_t value = 0;

    //vcmem_disable_cache();

    vcspiflash_write_enable();

    ((struct VCSPIFLASH_REG_CMD *)&value)->fields.ACT = 1;
    ((struct VCSPIFLASH_REG_CMD *)&value)->fields.POLL = 1;
    ((struct VCSPIFLASH_REG_CMD *)&value)->fields.LENGTH = 0;
    ((struct VCSPIFLASH_REG_CMD *)&value)->fields.CMDMODE = 0;
    ((struct VCSPIFLASH_REG_CMD *)&value)->fields.CMDADDR4 = 0;
    ((struct VCSPIFLASH_REG_CMD *)&value)->fields.CMDADDR = 1;
    ((struct VCSPIFLASH_REG_CMD *)&value)->fields.CMDWR = 1;
    ((struct VCSPIFLASH_REG_CMD *)&value)->fields.CMDDATA = 0;

    if (reg->CFG.fields.TYPE == SPIFLASH_WINBOND) {
        ((struct VCSPIFLASH_REG_CMD *)&value)->fields.CMDID = WINBOND_CMDID_BLOCK_ERASE_32K;
    }

    reg->ADDR.value = addr;
    reg->CMD.value = value;

    while ((reg->SR.value & 0x1) == 1);

    //vcmem_enable_cache();
}

void vcspiflash_program_word(uint32_t addr, uint32_t word)
{
    volatile struct VCSPIFLASH_REG_SPACE *reg = (volatile struct VCSPIFLASH_REG_SPACE *)VCREG_BASE_SPIFLASH;
    volatile uint32_t *reg_buf = (volatile uint32_t *)VCREG_BASE_SPIFLASH_BUF(0);
    uint32_t value = 0;

    *reg_buf = word;

    //vcmem_disable_cache();

    vcspiflash_write_enable();

    ((struct VCSPIFLASH_REG_CMD *)&value)->fields.ACT = 1;
    ((struct VCSPIFLASH_REG_CMD *)&value)->fields.POLL = 1;
    ((struct VCSPIFLASH_REG_CMD *)&value)->fields.LENGTH = 3; // 1 word (4 bytes) - 1
    ((struct VCSPIFLASH_REG_CMD *)&value)->fields.CMDMODE = 0;
    ((struct VCSPIFLASH_REG_CMD *)&value)->fields.CMDADDR4 = 0;
    ((struct VCSPIFLASH_REG_CMD *)&value)->fields.CMDADDR = 1;
    ((struct VCSPIFLASH_REG_CMD *)&value)->fields.CMDWR = 1;
    ((struct VCSPIFLASH_REG_CMD *)&value)->fields.CMDDATA = 1;

    if (reg->CFG.fields.TYPE == SPIFLASH_WINBOND) {
        ((struct VCSPIFLASH_REG_CMD *)&value)->fields.CMDID = WINBOND_CMDID_PAGE_PROG;
    }

    reg->ADDR.value = addr;
    reg->CMD.value = value;

    while ((reg->SR.value & 0x1) == 1);

    //vcmem_enable_cache();
}

void vcspiflash_program_page(uint32_t addr, uint32_t len, uint8_t *buf)
{
    volatile struct VCSPIFLASH_REG_SPACE *reg = (volatile struct VCSPIFLASH_REG_SPACE *)VCREG_BASE_SPIFLASH;
    volatile uint32_t *reg_buf = (volatile uint32_t *)VCREG_BASE_SPIFLASH_BUF(0);
    uint32_t value = 0;

    for (uint32_t i = 0; i < len; i++) {
        ((uint8_t *)reg_buf)[i] = buf[i];
    }

    //vcmem_disable_cache();

    vcspiflash_write_enable();

    ((struct VCSPIFLASH_REG_CMD *)&value)->fields.ACT = 1;
    ((struct VCSPIFLASH_REG_CMD *)&value)->fields.POLL = 1;
    ((struct VCSPIFLASH_REG_CMD *)&value)->fields.LENGTH = len ? len-1 : len;  // 256 Bytes
    ((struct VCSPIFLASH_REG_CMD *)&value)->fields.CMDMODE = 0;
    ((struct VCSPIFLASH_REG_CMD *)&value)->fields.CMDADDR4 = 0;
    ((struct VCSPIFLASH_REG_CMD *)&value)->fields.CMDADDR = 1;
    ((struct VCSPIFLASH_REG_CMD *)&value)->fields.CMDWR = 1;
    ((struct VCSPIFLASH_REG_CMD *)&value)->fields.CMDDATA = 1;

    if (reg->CFG.fields.TYPE == SPIFLASH_WINBOND) {
        ((struct VCSPIFLASH_REG_CMD *)&value)->fields.CMDID = WINBOND_CMDID_PAGE_PROG;
    }

    reg->ADDR.value = addr;
    reg->CMD.value = value;

    while ((reg->SR.value & 0x1) == 1);

    //vcmem_enable_cache();
}

void vcspisram_config_addr_bytes(uint8_t bytes)
{
    volatile struct VCSPISRAM_REG_SPACE *reg = (volatile struct VCSPISRAM_REG_SPACE *)VCREG_BASE_SPISRAM;

    reg->CFG.fields.SRAMADDR4 = bytes;
}

void vcspisram_config_latency(uint8_t latency)
{
    volatile struct VCSPISRAM_REG_SPACE *reg = (volatile struct VCSPISRAM_REG_SPACE *)VCREG_BASE_SPISRAM;

    reg->CFG.fields.SRAMLAT = latency;
}

void vcspisram_config_mode(uint8_t mode)
{
    volatile struct VCSPISRAM_REG_SPACE *reg = (volatile struct VCSPISRAM_REG_SPACE *)VCREG_BASE_SPISRAM;

    reg->CFG.fields.SRAMMODE = mode;
}

void vcspisram_config_clk_div(uint8_t div) // 1 - 16
{
    volatile struct VCSPISRAM_REG_SPACE *reg = (volatile struct VCSPISRAM_REG_SPACE *)VCREG_BASE_SPISRAM;

    reg->CFG.fields.SRAMCLK = (div - 1);
}

void vcspisram_config_size(uint8_t size)
{
    volatile struct VCSPISRAM_REG_SPACE *reg = (volatile struct VCSPISRAM_REG_SPACE *)VCREG_BASE_SPISRAM;

    reg->CFG.fields.SRAMSIZE = size;
}

void vcspisram_config_spimux(uint8_t spimux)
{
   vcsfio_config_spimux(spimux);

   if ((spimux == SPIMUX0) || (spimux == SPIMUX1)) {
       vcsfio_enable_iob_spisram();
   }
}

void vcspisram_enable(void)
{
    volatile struct VCSPISRAM_REG_SPACE *reg = (volatile struct VCSPISRAM_REG_SPACE *)VCREG_BASE_SPISRAM;

    reg->CFG.fields.SRAMEN = 1;
}

void vcspisram_disable(void)
{
    volatile struct VCSPISRAM_REG_SPACE *reg = (volatile struct VCSPISRAM_REG_SPACE *)VCREG_BASE_SPISRAM;

    reg->CFG.fields.SRAMEN = 0;
}

void vcspisram_enable_sqi_mode(void)
{
    volatile struct VCSPISRAM_REG_SPACE *reg = (volatile struct VCSPISRAM_REG_SPACE *)VCREG_BASE_SPISRAM;
    uint32_t value = 0;

    ((struct VCSPISRAM_REG_CMD *)&value)->fields.ACT = 1;
    ((struct VCSPISRAM_REG_CMD *)&value)->fields.SRAMCMD = 1; // send command to SPISRAM
    ((struct VCSPISRAM_REG_CMD *)&value)->fields.POLL = 0;
    ((struct VCSPISRAM_REG_CMD *)&value)->fields.LENGTH = 0;
    ((struct VCSPISRAM_REG_CMD *)&value)->fields.CMDMODE = 0;
    ((struct VCSPISRAM_REG_CMD *)&value)->fields.CMDADDR4 = 0;
    ((struct VCSPISRAM_REG_CMD *)&value)->fields.CMDADDR = 0;
    ((struct VCSPISRAM_REG_CMD *)&value)->fields.CMDWR = 0;
    ((struct VCSPISRAM_REG_CMD *)&value)->fields.CMDDATA = 0;
    ((struct VCSPISRAM_REG_CMD *)&value)->fields.CMDID = ISSI_SRAM_CMDID_ESQI;

    reg->CMD.value = value;

    while (reg->CMD.fields.ACT); // wait until the process is finished
}
