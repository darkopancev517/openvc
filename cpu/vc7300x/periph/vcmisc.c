/**
 * Copyright (c) 2018 Vertexcom Technologies, Inc. All rights reserved
 * Vertexcom Confidential Proprietary
 *
*/

#include "vcsoc.h"

#define VCREG_BASE_MISC             0x40046000
#define VCREG_BASE_MISC2            0x40047000
#define CLKEN_PASS_KEY              0x55aaaa55

static uint32_t system_core_clock = 0;

struct VCMISC_REG_SRAMINT {
    union {
        struct {
            uint32_t PERR           : 1;
            uint32_t HIAL           : 1;
            uint32_t HIAC           : 1;
            uint32_t PIAC           : 1;
            uint32_t LOCKUP         : 1;
            uint32_t reserved       : 27;
        } fields;

        uint32_t value;
    };
};

struct VCMISC_REG_SRAMINIT {
    union {
        struct {
            uint32_t PEN            : 1;
            uint32_t PERRIE         : 1;
            uint32_t INIT           : 1;
            uint32_t reserved       : 1;
            uint32_t HIALIE         : 1;
            uint32_t HIACIE         : 1;
            uint32_t PIACIE         : 1;
            uint32_t LOCKIE         : 1;
            uint32_t reserved2      : 24;
        } fields;

        uint32_t value;
    };
};

struct VCMISC_REG_IRQLAT {
    union {
        struct {
            uint32_t IRQLAT         : 8;
            uint32_t LOCKRESET      : 1;
            uint32_t NOHARDFAULT    : 1;
            uint32_t reserved       : 22;
        } fields;

        uint32_t value;
    };
};

struct VCMISC2_REG_FLASHWC {
    union {
        struct {
            uint32_t FLASHWC        : 4;    // (rw) used to control wait cycle of flash access (default: 0x1)
            uint32_t reserved       : 4;
            uint32_t USCYCLE1       : 8;    // (rw) used for flash controller to calc 1us tick from AHB clock
            uint32_t reserved1      : 16;
        } fields;

        uint32_t value;
    };
};

struct VCMISC2_REG_CLKSEL {
    union {
        struct {
            uint32_t CLKSEL         : 1;    // (rw) used to control ahb clock source (0: Internal HRCO, 1: RTCLK)
            uint32_t reserved       : 31;
        } fields;

        uint32_t value;
    };
};

struct VCMISC2_REG_CLKDIVH {
    union {
        struct {
            uint32_t CLKDIVH        : 8;    // (rw) AHB clock divider
            uint32_t reserved       : 24;
        } fields;

        uint32_t value;
    };
};

struct VCMISC2_REG_CLKDIVP {
    union {
        struct {
            uint32_t CLKDIVP        : 8;    // (rw) APB clock divider
            uint32_t reserved       : 24;
        } fields;

        uint32_t value;
    };
};

struct VCMISC2_REG_HCLKEN {
    union {
        struct {
            uint32_t HCLKEN         : 16;
            uint32_t reserved       : 16;
        } fields;

        uint32_t value;
    };
};

struct VCMISC2_REG_PCLKEN {
    uint32_t value;
};

struct VCMISC2_REG_CLKEN_UNLOCK {
    union {
        struct {
            uint32_t UNLOCK         : 1;
            uint32_t reserved       : 31;
        } fields;

        uint32_t value;
    };
};

struct VCMISC2_REG_HSOFTRST {
    union {
        struct {
            uint32_t HSOFTRST       : 16;
            uint32_t reserved       : 16;
        } fields;

        uint32_t value;
    };
};

struct VCMISC2_REG_PSOFTRST {
    uint32_t value;
};

struct VCMISC2_REG_SOFTRST_UNLOCK {
    union {
        struct {
            uint32_t UNLOCK         : 1;
            uint32_t reserved       : 31;
        } fields;

        uint32_t value;
    };
};

struct VCMISC2_REG_PWRUPDLY {
    union {
        struct {
            uint32_t PWRUPDLY       : 16;   // (rw) used to control wake-up delay from sleep mode to normal mode
            uint32_t reserved       : 16;
        } fields;

        uint32_t value;
    };
};

struct VCMISC_REG_SPACE {
    struct VCMISC_REG_SRAMINT   SRAMINT;
    struct VCMISC_REG_SRAMINIT  SRAMINIT;
};

struct VCMISC2_REG_SPACE {
    struct VCMISC2_REG_FLASHWC        FLASHWC;
    struct VCMISC2_REG_CLKSEL         CLKSEL;
    struct VCMISC2_REG_CLKDIVH        CLKDIVH;
    struct VCMISC2_REG_CLKDIVP        CLKDIVP;
    struct VCMISC2_REG_HCLKEN         HCLKEN;
    struct VCMISC2_REG_PCLKEN         PCLKEN;
    uint32_t reserved[4];
    struct VCMISC2_REG_CLKEN_UNLOCK   CLKEN_UNLOCK;
    uint32_t reserved1;    
    struct VCMISC2_REG_HSOFTRST       HSOFTRST;
    struct VCMISC2_REG_PSOFTRST       PSOFTRST;
    struct VCMISC2_REG_SOFTRST_UNLOCK SOFTRST_UNLOCK;
    uint32_t reserved2;    
    struct VCMISC2_REG_PWRUPDLY       PWRUPDLY;
};

void vcmisc_set_sys_core_clk(uint32_t clock)
{
    system_core_clock = clock;

    vcana_config_lfxo_cursel(1);

    vcana_config_hfrco_hf(system_core_clock);

    while (vcpmu_32k_xtal_status() == 0);
}

void vcmisc_disable_all_periph_clk(void)
{
     volatile struct VCMISC2_REG_SPACE *reg_space = (volatile struct VCMISC2_REG_SPACE *)VCREG_BASE_MISC2;

     reg_space->CLKEN_UNLOCK.value = CLKEN_PASS_KEY;

     reg_space->HCLKEN.fields.HCLKEN = 0;
     reg_space->PCLKEN.value = 0;
}

uint32_t vcmisc_get_sys_core_clk(void)
{
    return system_core_clock;
}

uint32_t vcmisc_get_ahb_clk(void)
{
    volatile struct VCMISC2_REG_SPACE *reg_space = (volatile struct VCMISC2_REG_SPACE *)VCREG_BASE_MISC2;

    uint8_t ahb_div = (uint8_t)(reg_space->CLKDIVH.fields.CLKDIVH) + 1;

    return (uint32_t)(vcmisc_get_sys_core_clk() / ahb_div);
}

void vcmisc_config_ahb_source(uint8_t clk_source)
{
    if ((clk_source < 0) || (clk_source > 1)) return;

    volatile struct VCMISC2_REG_SPACE *reg_space = (volatile struct VCMISC2_REG_SPACE *)VCREG_BASE_MISC2;

    reg_space->CLKSEL.fields.CLKSEL = clk_source;
}

void vcmisc_config_ahb_div(uint16_t div)
{
    if (div > 256) return;

    volatile struct VCMISC2_REG_SPACE *reg_space = (volatile struct VCMISC2_REG_SPACE *)VCREG_BASE_MISC2;

    reg_space->CLKDIVH.fields.CLKDIVH = (uint8_t)(div - 1);
}

void vcmisc_config_ahb_periph(uint8_t periph, bool state)
{
    if (periph > 15) return;

    volatile struct VCMISC2_REG_SPACE *reg_space = (volatile struct VCMISC2_REG_SPACE *)VCREG_BASE_MISC2;

    reg_space->CLKEN_UNLOCK.value = CLKEN_PASS_KEY;

    if (state == true) {
        reg_space->HCLKEN.fields.HCLKEN |= (1 << periph);
    } else {
        reg_space->HCLKEN.fields.HCLKEN &= ~(1 << periph);
    }
}

uint32_t vcmisc_get_apb_clk(void)
{
    volatile struct VCMISC2_REG_SPACE *reg_space = (volatile struct VCMISC2_REG_SPACE *)VCREG_BASE_MISC2;

    uint8_t apb_div = (uint8_t)(reg_space->CLKDIVP.fields.CLKDIVP) + 1;

    return (uint32_t)(vcmisc_get_ahb_clk() / apb_div);
}

void vcmisc_config_apb_div(uint16_t div)
{
    if (div > 256) return;

    volatile struct VCMISC2_REG_SPACE *reg_space = (volatile struct VCMISC2_REG_SPACE *)VCREG_BASE_MISC2;

    reg_space->CLKDIVP.fields.CLKDIVP = (uint8_t)(div - 1);
}

void vcmisc_config_apb_periph(uint8_t periph, bool state)
{
    if (periph > 31) return;

    volatile struct VCMISC2_REG_SPACE *reg_space = (volatile struct VCMISC2_REG_SPACE *)VCREG_BASE_MISC2;

    reg_space->CLKEN_UNLOCK.value = CLKEN_PASS_KEY;

    if (state == true) {
        reg_space->PCLKEN.value |= (1 << periph);
    } else {
        reg_space->PCLKEN.value &= ~(1 << periph);
    }
}

void vcmisc_config_embflash_wait_cycle(uint8_t wait_cycle)
{
    if ((wait_cycle < 0) || (wait_cycle > 15)) return;

    volatile struct VCMISC2_REG_SPACE *reg_space = (volatile struct VCMISC2_REG_SPACE *)VCREG_BASE_MISC2;

    reg_space->FLASHWC.fields.FLASHWC = wait_cycle;
}

void vcmisc_config_embflash_1uscycle(uint8_t cycle)
{
    volatile struct VCMISC2_REG_SPACE *reg_space = (volatile struct VCMISC2_REG_SPACE *)VCREG_BASE_MISC2;

    reg_space->FLASHWC.fields.USCYCLE1 = cycle;
}

void vcmisc_sraminit_disable_parity_check(void)
{
    volatile struct VCMISC_REG_SPACE *misc = (volatile struct VCMISC_REG_SPACE *)VCREG_BASE_MISC;

    misc->SRAMINIT.fields.PEN = 0;
}

void vcmisc_sraminit_enable_parity_check(void)
{
    volatile struct VCMISC_REG_SPACE *misc = (volatile struct VCMISC_REG_SPACE *)VCREG_BASE_MISC;

    misc->SRAMINIT.fields.PEN = 1;
}

void vcmisc_config_pwrup_delay(uint16_t delay)
{

    volatile struct VCMISC2_REG_SPACE *reg_space = (volatile struct VCMISC2_REG_SPACE *)VCREG_BASE_MISC2;

    reg_space->PWRUPDLY.fields.PWRUPDLY = delay;
}


