/**
 * Copyright (c) 2018 Vertexcom Technologies, Inc. All rights reserved
 * Vertexcom Confidential Proprietary
 *
*/

#include "vcsoc.h"

#define VCREG_BASE_PMU              0x40048000
#define VCREG_BASE_PMU_REMAP        0x40048068
#define VCREG_BASE_PMU_PDOWNEN      0x40048080
#define VCREG_BASE_VERSIONID        0x4004803c

#define REMAPPASS_KEY               0xb4a59687
#define DSLEEPPASS_KEY              0xaa5555aa
#define DSLEEPEN_KEY                0x55aaaa55

struct VCPMU_REG_DSLEEPEN {
    union {
        struct {
            uint32_t DSLEEP         : 1;    // (r) this bit indicate the deep-sleep mode has been entry
            uint32_t reserved       : 30;
            uint32_t WKU            : 1;    // (r) current wake-up signal status
        } fields;

        uint32_t value;
    };
};

struct VCPMU_REG_DSLEEPPASS {
    union {
        struct {
            uint32_t UNLOCK         : 1;    // (r) lock status for entering deep sleep mode
            uint32_t reserved       : 31;
        } fields;

        uint32_t value;
    };
};


struct VCPMU_REG_CONTROL {
    union {
        struct {
            uint32_t INTEN          : 1;    // (rw) pmu's interrupt enable register
            uint32_t RTCLK_SEL      : 1;    // (rw) rtc clock selection, 0: 32K-XTAL, 1: 32K-RC
            uint32_t INT_32K_EN     : 1;    // (rw) 32K XTAL absent interrupt enable register
            uint32_t reserved       : 2;
            uint32_t PLLL_SEL       : 1;    // (rw) low speed pll input clock selection
            uint32_t PD_WKUEN       : 1;    // (rw) wake-up enable/disable when main power is off
            uint32_t reserved1      : 1;
            uint32_t PWUPCYC        : 8;    // (rw) power-up cycle count
            uint32_t reserved2      : 1;
            uint32_t NOWAITLOCK     : 1;
            uint32_t INTWKUEN       : 1;    // (rw) force wakeup from sleep mode when wakeup glitch is too small
            uint32_t FSEL32KXTAL    : 1;
            uint32_t FCLKSELRCH     : 1;
            uint32_t reserved3      : 11;
        } fields;

        uint32_t value;
    };
};

struct VCPMU_REG_STS {
    union {
        struct {
            uint32_t INT_32K        : 1;
            uint32_t reserved       : 1;
            uint32_t EXIST_32K      : 1;
            uint32_t reserved1      : 1;
            uint32_t EXTRST         : 1;
            uint32_t PORST          : 1;
            uint32_t DPORST         : 1;
            uint32_t WDTSTS         : 1;
            uint32_t SFTRST         : 1;
            uint32_t reserved2      : 1;
            uint32_t MODERST        : 1;
            uint32_t reserved3      : 5;
            uint32_t WKUIOA         : 1;
            uint32_t WKURTC         : 1;
            uint32_t WKUANA         : 1;
            uint32_t WKUU32K        : 1;
            uint32_t WKUXTAL        : 1;
            uint32_t WKUPU          : 1;
            uint32_t WKUMODE        : 1;
            uint32_t reserved4      : 1;
            uint32_t MODE           : 1;
            uint32_t reserved5      : 7;
        } fields;

        uint32_t value;
    };
};

struct VCPMU_REG_REMAP {
    union {
        struct {
            uint32_t REMAP          : 2;
            uint32_t reserved       : 30;
        } fields;

        uint32_t value;
    };
};

struct VCPMU_REG_REMAPPASS {
    union {
        struct {
            uint32_t REMAPUNLOCK    : 1;
            uint32_t reserved       : 30;
        } fields;

        uint32_t value;
    };
};

struct VCPMU_REG_PDOWNEN {
    union {
        struct {
            uint32_t PDOWN          : 1;    // (r) power-down mode entry status
            uint32_t reserved       : 30;
            uint32_t WKU            : 1;    // (r) current wake up signal status
        } fields;

        uint32_t value;
    };
};

struct VCPMU_REG_STRAP {
    union {
        struct {
            uint32_t STRAP          : 8;
            uint32_t reserved       : 24;
        } fields;

        uint32_t value;
    };
};

struct VCPMU_REG_SPACE {
    struct VCPMU_REG_DSLEEPEN       DSLEEPEN;
    struct VCPMU_REG_DSLEEPPASS     DSLEEPPASS;
    struct VCPMU_REG_CONTROL        CONTROL;
    struct VCPMU_REG_STS            STS;
};

struct VCPMU_REMAP_REG_SPACE {
    struct VCPMU_REG_REMAP          REMAP;
    struct VCPMU_REG_REMAPPASS      REMAPPASS;
    struct VCPMU_REG_STRAP          STRAP;
};

void vcpmu_enter_deep_sleep_mode(void)
{
    volatile struct VCPMU_REG_SPACE *reg_space = (volatile struct VCPMU_REG_SPACE *)VCREG_BASE_PMU;

    reg_space->DSLEEPPASS.value = DSLEEPPASS_KEY;
    reg_space->DSLEEPEN.value  = DSLEEPEN_KEY;
}

void vcpmu_enter_idle_mode(void)
{
}

void vcpmu_enter_sleep_mode(void)
{
}

void vcpmu_pwdown_wakeup_enable(void)
{
    volatile struct VCPMU_REG_SPACE *reg_space = (volatile struct VCPMU_REG_SPACE *)VCREG_BASE_PMU;

    reg_space->CONTROL.fields.PD_WKUEN = 1;
}

void vcpmu_pwdown_wakeup_disable(void)
{
    volatile struct VCPMU_REG_SPACE *reg_space = (volatile struct VCPMU_REG_SPACE *)VCREG_BASE_PMU;

    reg_space->CONTROL.fields.PD_WKUEN = 0;
}

void vcpmu_pwdown_wakeup_delay(uint8_t period)
{
    volatile struct VCPMU_REG_SPACE *reg_space = (volatile struct VCPMU_REG_SPACE *)VCREG_BASE_PMU;

    reg_space->CONTROL.fields.PWUPCYC = period;
}

uint32_t vcpmu_get_version_id(void)
{
    volatile uint32_t *reg_versionid = (volatile uint32_t *)VCREG_BASE_VERSIONID;

    return (uint32_t)*reg_versionid;
}

void vcpmu_remap(uint32_t remap)
{
    if ((remap < PMU_REMAP_IROM) || (remap > PMU_REMAP_SRAM0_MODE2)) return;

    volatile struct VCPMU_REMAP_REG_SPACE *reg_space = (volatile struct VCPMU_REMAP_REG_SPACE *)VCREG_BASE_PMU_REMAP;

    reg_space->REMAPPASS.value = REMAPPASS_KEY;

    reg_space->REMAP.value = remap;
}

uint8_t vcpmu_get_strap_bits(void)
{
    volatile struct VCPMU_REMAP_REG_SPACE *reg_space = (volatile struct VCPMU_REMAP_REG_SPACE *)VCREG_BASE_PMU_REMAP;

    return (uint8_t)reg_space->STRAP.fields.STRAP;
}

int vcpmu_get_int_enable_status(void)
{
    return ((volatile struct VCPMU_REG_SPACE *)VCREG_BASE_PMU)->CONTROL.fields.INTEN;
}

void vcpmu_set_int_enable_status(int en)
{
    ((volatile struct VCPMU_REG_SPACE *)VCREG_BASE_PMU)->CONTROL.fields.INTEN = en ? 1 : 0;
}

int vcpmu_32k_xtal_status(void)
{
    return ((volatile struct VCPMU_REG_SPACE *)VCREG_BASE_PMU)->STS.fields.EXIST_32K;
}

int vcpmu_get_pmu_status(void)
{
    return ((volatile struct VCPMU_REG_SPACE *)VCREG_BASE_PMU)->STS.value;
}

void vcpmu_clear_pmu_status(void)
{
    ((volatile struct VCPMU_REG_SPACE *)VCREG_BASE_PMU)->STS.value = 0xffff;
}

