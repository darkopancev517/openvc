/**
 * Copyright (c) 2018 Vertexcom Technologies, Inc. All rights reserved
 * Vertexcom Confidential Proprietary
 *
*/

#include "vcsoc.h"

#define VCREG_BASE_TIM0         0x40045000
#define VCREG_BASE_TIM1         0x40045020
#define VCREG_BASE_TIM(i)       (VCREG_BASE_TIM0 + ((i) * (VCREG_BASE_TIM1 - VCREG_BASE_TIM0)))

struct VCTIM_REG_CTRL {
    union {
        struct {
            uint32_t EN         : 1;    // (rw) timer x enable control register
            uint32_t EXTEN      : 1;    // (rw) select external clock as clock enable
            uint32_t EXTCLK     : 1;    // (rw) select external clock as clock source
            uint32_t INTEN      : 1;    // (rw) timer x interrupt enable register
            uint32_t reserved   : 28;
        } fields;

        uint32_t value;
    };
};

struct VCTIM_REG_VALUE {
    uint32_t value;                     // (rw) timer x current value register
};

struct VCTIM_REG_RELOAD {
    uint32_t value;                     // (rw) timer x reload value register
};

struct VCTIM_REG_INTSTS {
    union {
        struct {
            uint32_t INTSTS     : 1;    // (rc) timer interrupt status register
            uint32_t reserved   : 31;
        } fields;

        uint32_t value;
    };
};

struct VCTIM_REG_SPACE {
    struct VCTIM_REG_CTRL       CTRL;
    struct VCTIM_REG_VALUE      CURRENT;
    struct VCTIM_REG_RELOAD     RELOAD;
    struct VCTIM_REG_INTSTS     INTSTS;
};

void vctim_config_reset(uint8_t tim)
{
    if ((tim < TIM0) || (tim > TIM3)) return;
    volatile struct VCTIM_REG_SPACE *reg_space = (volatile struct VCTIM_REG_SPACE *)VCREG_BASE_TIM(tim);
    reg_space->CTRL.value = 0;
    reg_space->INTSTS.fields.INTSTS = 1; // clear tim interrupt status register
}

void vctim_config_clock_source(uint8_t tim, uint8_t clksrc)
{
    if ((tim < TIM0) || (tim > TIM3)) return;
    if ((clksrc != TIM_CLKSRC_INTERNAL) || (clksrc != TIM_CLKSRC_EXTERNAL)) return;
    volatile struct VCTIM_REG_SPACE *reg_space = (volatile struct VCTIM_REG_SPACE *)VCREG_BASE_TIM(tim);
    reg_space->CTRL.fields.EXTCLK = clksrc;
}

void vctim_config_external_clock_gate(uint8_t tim, bool state)  // use external clock as clock enable
{
    if ((tim < TIM0) || (tim > TIM3)) return;
    volatile struct VCTIM_REG_SPACE *reg_space = (volatile struct VCTIM_REG_SPACE *)VCREG_BASE_TIM(tim);
    reg_space->CTRL.fields.EXTEN = (state == true) ? 1 : 0;
}

void vctim_config_reload_value(uint8_t tim, uint32_t reload)
{
    if ((tim < TIM0) || (tim > TIM3)) return;
    volatile struct VCTIM_REG_SPACE *reg_space = (volatile struct VCTIM_REG_SPACE *)VCREG_BASE_TIM(tim);
    reg_space->RELOAD.value = reload;
    reg_space->CURRENT.value = reload;
}

void vctim_config_enable_int(uint8_t tim)
{
    if ((tim < TIM0) || (tim > TIM3)) return;
    volatile struct VCTIM_REG_SPACE *reg_space = (volatile struct VCTIM_REG_SPACE *)VCREG_BASE_TIM(tim);
    reg_space->CTRL.fields.INTEN = 1;
}

void vctim_config_disable_int(uint8_t tim)
{
    if ((tim < TIM0) || (tim > TIM3)) return;
    volatile struct VCTIM_REG_SPACE *reg_space = (volatile struct VCTIM_REG_SPACE *)VCREG_BASE_TIM(tim);
    reg_space->CTRL.fields.INTEN = 0;
}

void vctim_enable(uint8_t tim)
{
    if ((tim < TIM0) || (tim > TIM3)) return;
    volatile struct VCTIM_REG_SPACE *reg_space = (volatile struct VCTIM_REG_SPACE *)VCREG_BASE_TIM(tim);
    reg_space->CTRL.fields.EN = 1;
}

void vctim_disable(uint8_t tim)
{
    if ((tim < TIM0) || (tim > TIM3)) return;
    volatile struct VCTIM_REG_SPACE *reg_space = (volatile struct VCTIM_REG_SPACE *)VCREG_BASE_TIM(tim);
    reg_space->CTRL.fields.EN = 0;
}

int vctim_get_int(uint8_t tim)
{
    if ((tim < TIM0) || (tim > TIM3)) return 0;
    volatile struct VCTIM_REG_SPACE *reg_space = (volatile struct VCTIM_REG_SPACE *)VCREG_BASE_TIM(tim);
    return (reg_space->INTSTS.fields.INTSTS == 1) ? 1 : 0;;
}

void vctim_clear_int(uint8_t tim)
{
    if ((tim < TIM0) || (tim > TIM3)) return;
    volatile struct VCTIM_REG_SPACE *reg_space = (volatile struct VCTIM_REG_SPACE *)VCREG_BASE_TIM(tim);
    reg_space->INTSTS.fields.INTSTS = 1;
}

uint32_t vctim_get_value(uint8_t tim)
{
    if ((tim < TIM0) || (tim > TIM3)) return 0;
    volatile struct VCTIM_REG_SPACE *reg_space = (volatile struct VCTIM_REG_SPACE *)VCREG_BASE_TIM(tim);
    return reg_space->CURRENT.value;
}

void vctim_set_value(uint8_t tim, uint32_t value)
{
    if ((tim < TIM0) || (tim > TIM3)) return;
    volatile struct VCTIM_REG_SPACE *reg_space = (volatile struct VCTIM_REG_SPACE *)VCREG_BASE_TIM(tim);
    reg_space->CURRENT.value = value;
}

uint32_t vctim_get_reload(uint8_t tim)
{
    if ((tim < TIM0) || (tim > TIM3)) return 0;
    volatile struct VCTIM_REG_SPACE *reg_space = (volatile struct VCTIM_REG_SPACE *)VCREG_BASE_TIM(tim);
    return reg_space->RELOAD.value;
}
