/**
 * Copyright (c) 2018 Vertexcom Technologies, Inc. All rights reserved
 * Vertexcom Confidential Proprietary
 *
*/

#include "vcsoc.h"

#define VCREG_BASE_WDT      0x40048040
#define VCWDT_CLR_KEY       0x55AAAA55
#define VCWDT_PASS_KEY      0xAA5555AA

struct VCWDT_REG_WDTPASS {
    union {
        struct {
            uint32_t UNLOCK         : 1;    // (r) watchdog enable register status
            uint32_t reserved       : 31;
        } fields;

        uint32_t value;
    };
};

struct VCWDT_REG_WDTEN {
    union {
        struct {
            uint32_t WDTEN          : 1;    // (rw) watchdog enable control register
            uint32_t reserved       : 1;
            uint32_t WDTSEL         : 2;    // (rw) WDT counting period counter
            uint32_t reserved1      : 28;
        } fields;

        uint32_t value;
    };
};

struct VCWDT_REG_WDTCLR {
    union {
        struct {
            uint32_t WDTCNT         : 16;   // (rc) current counter value of watchdog timer
            uint32_t reserved       : 16;
        } fields;

        uint32_t value;
    };
};

struct VCWDT_REG_WDTSTS {
    union {
        uint32_t WDTSTS             : 1;    // (rc) indicates that WDT reset has happened
        uint32_t reserved           : 31;
    } fields;

    uint32_t value;
};

struct VCWDT_REG_SPACE {
    struct VCWDT_REG_WDTPASS PASS;
    struct VCWDT_REG_WDTEN   EN;
    struct VCWDT_REG_WDTCLR  CLR;
    struct VCWDT_REG_WDTSTS  STS;
};

void vcwdt_clear(void)
{
    volatile struct VCWDT_REG_SPACE *reg_space = (volatile struct VCWDT_REG_SPACE *)VCREG_BASE_WDT;

    reg_space->CLR.value = VCWDT_CLR_KEY;
}

void vcwdt_enable(void)
{
    volatile struct VCWDT_REG_SPACE *reg_space = (volatile struct VCWDT_REG_SPACE *)VCREG_BASE_WDT;

    reg_space->PASS.value = VCWDT_PASS_KEY;
    reg_space->EN.fields.WDTEN = 1;
}

void vcwdt_disable(void)
{
    volatile struct VCWDT_REG_SPACE *reg_space = (volatile struct VCWDT_REG_SPACE *)VCREG_BASE_WDT;

    reg_space->PASS.value = VCWDT_PASS_KEY;
    reg_space->EN.fields.WDTEN = 0;
}

void vcwdt_set_period(uint8_t period)
{
    volatile struct VCWDT_REG_SPACE *reg_space = (volatile struct VCWDT_REG_SPACE *)VCREG_BASE_WDT;

    if (period > 3) return;

    reg_space->PASS.value = VCWDT_PASS_KEY;
    reg_space->EN.fields.WDTSEL = period;
}

uint16_t vcwdt_get_counter(void)
{
    volatile struct VCWDT_REG_SPACE *reg_space = (volatile struct VCWDT_REG_SPACE *)VCREG_BASE_WDT;

    return (uint16_t)reg_space->CLR.fields.WDTCNT;
}

int vcwdt_get_status(void)
{
    volatile struct VCWDT_REG_SPACE *reg_space = (volatile struct VCWDT_REG_SPACE *)VCREG_BASE_WDT;

    return (reg_space->STS.fields.WDTSTS == 1) ? 1 : 0;
}

void vcwdt_clear_status(void)
{
    volatile struct VCWDT_REG_SPACE *reg_space = (volatile struct VCWDT_REG_SPACE *)VCREG_BASE_WDT;

    reg_space->STS.fields.WDTSTS = 1;
}

