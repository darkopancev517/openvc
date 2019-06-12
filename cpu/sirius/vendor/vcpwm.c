/**
 * Copyright (c) 2018 Vertexcom Technologies, Inc. All rights reserved
 * Vertexcom Confidential Proprietary
 *
*/

#include "vcsoc.h"

#define VCREG_BASE_PWM0     0x40045100
#define VCREG_BASE_PWM1     0x40045140 

#define VCREG_BASE_PWM(i)   (VCREG_BASE_PWM0 + ((i) * (VCREG_BASE_PWM1 - VCREG_BASE_PWM0)))

#define VCREG_BASE_PWMSEL   0x400452f0

struct VCPWM_REG_CTL {
    union {
        struct {
            uint32_t IFG        : 1;    // (rc) interrup status flag
            uint32_t IE         : 1;    // (rw) interrup enable register
            uint32_t CLR        : 1;    // (rw) TAR clear register
            uint32_t TSEL       : 1;    // (rw) clock source selection
            uint32_t MC         : 2;    // (rw) pwm_ch timer mode control
            uint32_t ID         : 3;    // (rw) pwm_ch input clock divider control
            uint32_t reserved   : 23;
        } fields;

        uint32_t value;
    };
};

struct VCPWM_REG_TAR {  
    uint32_t value;         // (r) timer current count register
};

struct VCPWM_REG_CCTL {
    union {
        struct {
            uint32_t CCIFG      : 1;    // (rc) under capture mode
            uint32_t COV        : 1;    // (rc) capture overflow flag
            uint32_t OUT        : 1;    // (rw) used to control output value of OUTx when OUTMODE is set to 0
            uint32_t CCI        : 1;    // (r) read only register to show current status Inx's input
            uint32_t CCIE       : 1;    // (rw) capture/compare interrrupt enable register
            uint32_t OUTMOD     : 3;    // (rw) output mode selection
            uint32_t CAP        : 1;    // (rw) capture/compare mode selection
            uint32_t OUTEN      : 1;    // (rw) outx output enable control register
            uint32_t SCCI       : 1;    // (r) read only register shows the input value when TAR is equal to CCRx
            uint32_t OUT_HRES   : 1;
            uint32_t reserved   : 2;
            uint32_t CM         : 2;    // (rw) capture edge selection
            uint32_t reserved1  : 16;
        } fields;

        uint32_t value;
    };
};

struct VCPWM_REG_CCR {
    union {
        struct {
            uint32_t CCR        : 16;   // (rw) compare/capture data register
            uint32_t reserved   : 16;
        } fields;

        uint32_t value;
    };
};

struct VCPWM_REG_O_SEL {
    union {
        struct {
            uint32_t OSEL0     : 4;    // (rw) external output PWM0's output selection register
            uint32_t OSEL1     : 4;    // (rw) external output PWM1's output selection register
            uint32_t OSEL2     : 4;    // (rw) external output PWM2's output selection register
            uint32_t OSEL3     : 4;    // (rw) external output PWM3's output selection register
            uint32_t reserved  : 16;
        } fields;

        uint32_t value;
    };
};

struct VCPWM_REG_I_SEL01 {
    union {
        struct {
            uint32_t ISEL00    : 2;    // (rw) PWM0's IN0 external input control
            uint32_t ISEL01    : 2;    // (rw) PWM0's IN1 external input control
            uint32_t ISEL02    : 2;    // (rw) PWM0's IN2 external input control
            uint32_t reserved  : 10;
            uint32_t ISEL10    : 2;    // (rw) PWM1's IN0 external input control
            uint32_t ISEL11    : 2;    // (rw) PWM1's IN1 external input control
            uint32_t ISEL12    : 2;    // (rw) PWM1's IN2 external input control
            uint32_t reserved1 : 10;
        } fields;

        uint32_t value;
    };
};

struct VCPWM_REG_I_SEL23 {
    union {
        struct {
            uint32_t ISEL20    : 2;    // (rw) PWM2's IN0 external input control
            uint32_t ISEL21    : 2;    // (rw) PWM2's IN1 external input control
            uint32_t ISEL22    : 2;    // (rw) PWM2's IN2 external input control
            uint32_t reserved  : 10;
            uint32_t ISEL30    : 2;    // (rw) PWM3's IN0 external input control
            uint32_t ISEL31    : 2;    // (rw) PWM3's IN1 external input control
            uint32_t ISEL32    : 2;    // (rw) PWM3's IN2 external input control
            uint32_t reserved1 : 10;
        } fields;

        uint32_t value;
    };
};

struct VCPWM_REG_SPACE {
    struct VCPWM_REG_CTL        CTL;
    struct VCPWM_REG_TAR        TAR;
    struct VCPWM_REG_CCTL       CCTL[3];
    struct VCPWM_REG_CCR        CCR[3];
};

struct VCPWM_SEL_REG_SPACE {
    struct VCPWM_REG_O_SEL      O_SEL;
    struct VCPWM_REG_I_SEL01    I_SEL01;
    struct VCPWM_REG_I_SEL23    I_SEL23;
};

static int is_pwm_ch_valid(uint8_t pwm_ch)
{
    return (pwm_ch < PWM_CH0 || pwm_ch > PWM_CH3) ? 0 : 1;
}

static int is_ccr_num_valid(uint8_t ccr_num)
{
    return (ccr_num < PWM_CCR0 || ccr_num > PWM_CCR2) ? 0 : 1;
}

static int is_pwm_io_valid(uint8_t pwm_io)
{
    return (pwm_io < PWM_IO0 || pwm_io > PWM_IO3) ? 0 : 1;
}

static int is_clkdiv_valid(uint8_t clk_div)
{
    return (clk_div < PWM_CLKDIV1 || clk_div > PWM_CLKDIV128) ? 0 : 1;
}

static int is_mode_valid(uint8_t mode)
{
    return (mode < PWM_MODE_STOP || mode > PWM_MODE_UPDOWN) ? 0 : 1;
}

static int is_clksrc_valid(uint8_t clk_src)
{
    return (clk_src < PWM_CLKSRC_APBDIV128 || clk_src > PWM_CLKSRC_APB) ? 0 : 1;
}

static int is_out_level_valid(uint8_t level)
{
    return (level < PWM_OUTLEVEL_LOW || level > PWM_OUTLEVEL_HIGH) ? 0 : 1;
}

static int is_capture_mode_valid(uint8_t capture_mode)
{
    return (capture_mode < PWM_CAPTUREMODE_DISABLE || capture_mode > PWM_CAPTUREMODE_BOTH) ? 0 : 1;
}

static int is_cc_int_valid(uint8_t cc_int)
{
    return (cc_int < PWM_CCINT_CCIFG || cc_int > PWM_CCINT_COV) ? 0 : 1;
}

static int is_pwm_out_sel_valid(uint8_t outsel)
{
    return (outsel < PWM_OUTSEL0 || outsel > PWM_OUTSEL2) ? 0 : 1;
}

void vcpwm_config_reset(uint8_t pwm_ch)
{
    if (!is_pwm_ch_valid(pwm_ch)) return;

    volatile struct VCPWM_REG_SPACE *reg_space = (volatile struct VCPWM_REG_SPACE *)VCREG_BASE_PWM(pwm_ch);

    reg_space->CTL.value = 0;

    reg_space->CCTL[0].value = 0;
    reg_space->CCTL[1].value = 0;
    reg_space->CCTL[2].value = 0;

    reg_space->CCR[0].value = 0;
    reg_space->CCR[1].value = 0;
    reg_space->CCR[2].value = 0;
}

void vcpwm_config_clock_division(uint8_t pwm_ch, uint8_t clk_div)
{
    if (!is_pwm_ch_valid(pwm_ch)) return;

    if (!is_clkdiv_valid(clk_div)) return;

    volatile struct VCPWM_REG_SPACE *reg_space = (volatile struct VCPWM_REG_SPACE *)VCREG_BASE_PWM(pwm_ch);

    reg_space->CTL.fields.ID = clk_div;
}

void vcpwm_config_mode(uint8_t pwm_ch, uint8_t mode)
{
    if (!is_pwm_ch_valid(pwm_ch)) return;

    if (!is_mode_valid(mode)) return;

    volatile struct VCPWM_REG_SPACE *reg_space = (volatile struct VCPWM_REG_SPACE *)VCREG_BASE_PWM(pwm_ch);

    reg_space->CTL.fields.MC = mode;
}

void vcpwm_config_clock_source(uint8_t pwm_ch, uint8_t clk_src)
{
    if (!is_pwm_ch_valid(pwm_ch)) return;

    if (!is_clksrc_valid(clk_src)) return;

    volatile struct VCPWM_REG_SPACE *reg_space = (volatile struct VCPWM_REG_SPACE *)VCREG_BASE_PWM(pwm_ch);

    reg_space->CTL.fields.TSEL = clk_src;
}

void vcpwm_config_enable_int(uint8_t pwm_ch)
{
    if (!is_pwm_ch_valid(pwm_ch)) return;

    volatile struct VCPWM_REG_SPACE *reg_space = (volatile struct VCPWM_REG_SPACE *)VCREG_BASE_PWM(pwm_ch);

    reg_space->CTL.fields.IE = 1;
}

void vcpwm_config_disable_int(uint8_t pwm_ch)
{
    if (!is_pwm_ch_valid(pwm_ch)) return;

    volatile struct VCPWM_REG_SPACE *reg_space = (volatile struct VCPWM_REG_SPACE *)VCREG_BASE_PWM(pwm_ch);

    reg_space->CTL.fields.IE = 0;
}

int vcpwm_get_int_status(uint8_t pwm_ch)
{
    if (!is_pwm_ch_valid(pwm_ch)) return 0;

    volatile struct VCPWM_REG_SPACE *reg_space = (volatile struct VCPWM_REG_SPACE *)VCREG_BASE_PWM(pwm_ch);

    return (reg_space->CTL.fields.IFG == 1) ? 1 : 0;
}

void vcpwm_clear_int_status(uint8_t pwm_ch)
{
    if (!is_pwm_ch_valid(pwm_ch)) return;

    volatile struct VCPWM_REG_SPACE *reg_space = (volatile struct VCPWM_REG_SPACE *)VCREG_BASE_PWM(pwm_ch);

    reg_space->CTL.fields.IFG = 1;
}

// capture/compare register setting (ccr0 - ccr2)

void vcpwm_config_ccr_period(uint8_t pwm_ch, uint8_t ccr_num, uint32_t period)
{
    if (!is_pwm_ch_valid(pwm_ch)) return;

    if (!is_ccr_num_valid(ccr_num)) return;

    volatile struct VCPWM_REG_SPACE *reg_space = (volatile struct VCPWM_REG_SPACE *)VCREG_BASE_PWM(pwm_ch);

    reg_space->CCR[ccr_num].fields.CCR = period;
}

uint32_t vcpwm_get_ccr_val(uint8_t pwm_ch, uint8_t ccr_num)
{
    if (!is_pwm_ch_valid(pwm_ch)) return 0;

    if (!is_ccr_num_valid(ccr_num)) return 0;

    volatile struct VCPWM_REG_SPACE *reg_space = (volatile struct VCPWM_REG_SPACE *)VCREG_BASE_PWM(pwm_ch);

    return reg_space->CCR[ccr_num].value;
}

// capture/compare outx mode (out0 - out2)

void vcpwm_config_cc_out0_mode(uint8_t pwm_ch, uint8_t out_mode)
{
    if (!is_pwm_ch_valid(pwm_ch)) return;

    volatile struct VCPWM_REG_SPACE *reg_space = (volatile struct VCPWM_REG_SPACE *)VCREG_BASE_PWM(pwm_ch);

    reg_space->CCTL[0].fields.OUTMOD = out_mode;
}

void vcpwm_config_cc_out1_mode(uint8_t pwm_ch, uint8_t out_mode)
{
    if (!is_pwm_ch_valid(pwm_ch)) return;

    volatile struct VCPWM_REG_SPACE *reg_space = (volatile struct VCPWM_REG_SPACE *)VCREG_BASE_PWM(pwm_ch);

    reg_space->CCTL[1].fields.OUTMOD = out_mode;
}

void vcpwm_config_cc_out2_mode(uint8_t pwm_ch, uint8_t out_mode)
{
    if (!is_pwm_ch_valid(pwm_ch)) return;

    volatile struct VCPWM_REG_SPACE *reg_space = (volatile struct VCPWM_REG_SPACE *)VCREG_BASE_PWM(pwm_ch);

    reg_space->CCTL[2].fields.OUTMOD = out_mode;
}


void vcpwm_config_out0_level(uint8_t pwm_ch, uint8_t level)
{
    if (!is_pwm_ch_valid(pwm_ch)) return;

    if (!is_out_level_valid(level)) return;

    volatile struct VCPWM_REG_SPACE *reg_space = (volatile struct VCPWM_REG_SPACE *)VCREG_BASE_PWM(pwm_ch);

    reg_space->CCTL[0].fields.OUT = level;
}

void vcpwm_config_out1_level(uint8_t pwm_ch, uint8_t level)
{
    if (!is_pwm_ch_valid(pwm_ch)) return;

    if (!is_out_level_valid(level)) return;

    volatile struct VCPWM_REG_SPACE *reg_space = (volatile struct VCPWM_REG_SPACE *)VCREG_BASE_PWM(pwm_ch);

    reg_space->CCTL[1].fields.OUT = level;
}

void vcpwm_config_out2_level(uint8_t pwm_ch, uint8_t level)
{
    if (!is_pwm_ch_valid(pwm_ch)) return;

    if (!is_out_level_valid(level)) return;

    volatile struct VCPWM_REG_SPACE *reg_space = (volatile struct VCPWM_REG_SPACE *)VCREG_BASE_PWM(pwm_ch);

    reg_space->CCTL[2].fields.OUT = level;
}

void vcpwm_config_out0_enable(uint8_t pwm_ch, bool state)
{
    if (!is_pwm_ch_valid(pwm_ch)) return;

    volatile struct VCPWM_REG_SPACE *reg_space = (volatile struct VCPWM_REG_SPACE *)VCREG_BASE_PWM(pwm_ch);

    reg_space->CCTL[0].fields.OUTEN = (state == true) ? 1 : 0;
}

void vcpwm_config_out1_enable(uint8_t pwm_ch, bool state)
{
    if (!is_pwm_ch_valid(pwm_ch)) return;

    volatile struct VCPWM_REG_SPACE *reg_space = (volatile struct VCPWM_REG_SPACE *)VCREG_BASE_PWM(pwm_ch);

    reg_space->CCTL[1].fields.OUTEN = (state == true) ? 1 : 0;
}

void vcpwm_config_out2_enable(uint8_t pwm_ch, bool state)
{
    if (!is_pwm_ch_valid(pwm_ch)) return;

    volatile struct VCPWM_REG_SPACE *reg_space = (volatile struct VCPWM_REG_SPACE *)VCREG_BASE_PWM(pwm_ch);

    reg_space->CCTL[2].fields.OUTEN = (state == true) ? 1 : 0;
}

void vcpwm_config_out0_compare_enable(uint8_t pwm_ch)
{
    if (!is_pwm_ch_valid(pwm_ch)) return;

    volatile struct VCPWM_REG_SPACE *reg_space = (volatile struct VCPWM_REG_SPACE *)VCREG_BASE_PWM(pwm_ch);

    reg_space->CCTL[0].fields.CAP = 0;
}

void vcpwm_config_out1_compare_enable(uint8_t pwm_ch)
{
    if (!is_pwm_ch_valid(pwm_ch)) return;

    volatile struct VCPWM_REG_SPACE *reg_space = (volatile struct VCPWM_REG_SPACE *)VCREG_BASE_PWM(pwm_ch);

    reg_space->CCTL[1].fields.CAP = 0;
}

void vcpwm_config_out2_compare_enable(uint8_t pwm_ch)
{
    if (!is_pwm_ch_valid(pwm_ch)) return;

    volatile struct VCPWM_REG_SPACE *reg_space = (volatile struct VCPWM_REG_SPACE *)VCREG_BASE_PWM(pwm_ch);

    reg_space->CCTL[2].fields.CAP = 0;
}

void vcpwm_config_input0_capture_enable(uint8_t pwm_ch)
{
    if (!is_pwm_ch_valid(pwm_ch)) return;

    volatile struct VCPWM_REG_SPACE *reg_space = (volatile struct VCPWM_REG_SPACE *)VCREG_BASE_PWM(pwm_ch);

    reg_space->CCTL[0].fields.CAP = 1;
}

void vcpwm_config_input1_capture_enable(uint8_t pwm_ch)
{
    if (!is_pwm_ch_valid(pwm_ch)) return;

    volatile struct VCPWM_REG_SPACE *reg_space = (volatile struct VCPWM_REG_SPACE *)VCREG_BASE_PWM(pwm_ch);

    reg_space->CCTL[1].fields.CAP = 1;
}

void vcpwm_config_input2_capture_enable(uint8_t pwm_ch)
{
    if (!is_pwm_ch_valid(pwm_ch)) return;

    volatile struct VCPWM_REG_SPACE *reg_space = (volatile struct VCPWM_REG_SPACE *)VCREG_BASE_PWM(pwm_ch);

    reg_space->CCTL[2].fields.CAP = 1;
}

void vcpwm_config_input0_capture_mode(uint8_t pwm_ch, uint8_t capture_mode)
{
    if (!is_pwm_ch_valid(pwm_ch)) return;

    if (!is_capture_mode_valid(capture_mode)) return;

    volatile struct VCPWM_REG_SPACE *reg_space = (volatile struct VCPWM_REG_SPACE *)VCREG_BASE_PWM(pwm_ch);

    reg_space->CCTL[0].fields.CM = capture_mode;
}

void vcpwm_config_input1_capture_mode(uint8_t pwm_ch, uint8_t capture_mode)
{
    if (!is_pwm_ch_valid(pwm_ch)) return;

    if (!is_capture_mode_valid(capture_mode)) return;

    volatile struct VCPWM_REG_SPACE *reg_space = (volatile struct VCPWM_REG_SPACE *)VCREG_BASE_PWM(pwm_ch);

    reg_space->CCTL[1].fields.CM = capture_mode;
}

void vcpwm_config_input2_capture_mode(uint8_t pwm_ch, uint8_t capture_mode)
{
    if (!is_pwm_ch_valid(pwm_ch)) return;

    if (!is_capture_mode_valid(capture_mode)) return;

    volatile struct VCPWM_REG_SPACE *reg_space = (volatile struct VCPWM_REG_SPACE *)VCREG_BASE_PWM(pwm_ch);

    reg_space->CCTL[2].fields.CM = capture_mode;
}

void vcpwm_config_enable_cc0_int(uint8_t pwm_ch)
{
    if (!is_pwm_ch_valid(pwm_ch)) return;

    volatile struct VCPWM_REG_SPACE *reg_space = (volatile struct VCPWM_REG_SPACE *)VCREG_BASE_PWM(pwm_ch);

    reg_space->CCTL[0].fields.CCIE = 1;
}

void vcpwm_config_enable_cc1_int(uint8_t pwm_ch)
{
    if (!is_pwm_ch_valid(pwm_ch)) return;

    volatile struct VCPWM_REG_SPACE *reg_space = (volatile struct VCPWM_REG_SPACE *)VCREG_BASE_PWM(pwm_ch);

    reg_space->CCTL[1].fields.CCIE = 1;
}

void vcpwm_config_enable_cc2_int(uint8_t pwm_ch)
{
    if (!is_pwm_ch_valid(pwm_ch)) return;

    volatile struct VCPWM_REG_SPACE *reg_space = (volatile struct VCPWM_REG_SPACE *)VCREG_BASE_PWM(pwm_ch);

    reg_space->CCTL[2].fields.CCIE = 1;
}

void vcpwm_config_disable_cc0_int(uint8_t pwm_ch)
{
    if (!is_pwm_ch_valid(pwm_ch)) return;

    volatile struct VCPWM_REG_SPACE *reg_space = (volatile struct VCPWM_REG_SPACE *)VCREG_BASE_PWM(pwm_ch);

    reg_space->CCTL[0].fields.CCIE = 0;
}

void vcpwm_config_disable_cc1_int(uint8_t pwm_ch)
{
    if (!is_pwm_ch_valid(pwm_ch)) return;

    volatile struct VCPWM_REG_SPACE *reg_space = (volatile struct VCPWM_REG_SPACE *)VCREG_BASE_PWM(pwm_ch);

    reg_space->CCTL[1].fields.CCIE = 0;
}

void vcpwm_config_disable_cc2_int(uint8_t pwm_ch)
{
    if (!is_pwm_ch_valid(pwm_ch)) return;

    volatile struct VCPWM_REG_SPACE *reg_space = (volatile struct VCPWM_REG_SPACE *)VCREG_BASE_PWM(pwm_ch);

    reg_space->CCTL[2].fields.CCIE = 0;
}

uint8_t vcpwm_get_cc0_int_status(uint8_t pwm_ch, uint8_t cc_int)
{
    if (!is_pwm_ch_valid(pwm_ch)) return 0;

    if (!is_cc_int_valid(cc_int)) return 0;

    volatile struct VCPWM_REG_SPACE *reg_space = (volatile struct VCPWM_REG_SPACE *)VCREG_BASE_PWM(pwm_ch);

    switch (cc_int)
    {
    case PWM_CCINT_CCIFG:
        return reg_space->CCTL[0].fields.CCIFG;

    case PWM_CCINT_COV:
        return reg_space->CCTL[0].fields.COV;

    default:
        return 0;
    }
}

uint8_t vcpwm_get_cc1_int_status(uint8_t pwm_ch, uint8_t cc_int)
{
    if (!is_pwm_ch_valid(pwm_ch)) return 0;

    if (!is_cc_int_valid(cc_int)) return 0;

    volatile struct VCPWM_REG_SPACE *reg_space = (volatile struct VCPWM_REG_SPACE *)VCREG_BASE_PWM(pwm_ch);

    switch (cc_int)
    {
    case PWM_CCINT_CCIFG:
        return reg_space->CCTL[1].fields.CCIFG;

    case PWM_CCINT_COV:
        return reg_space->CCTL[1].fields.COV;

    default:
        return 0;
    }
}

uint8_t vcpwm_get_cc2_int_status(uint8_t pwm_ch, uint8_t cc_int)
{
    if (!is_pwm_ch_valid(pwm_ch)) return 0;

    if (!is_cc_int_valid(cc_int)) return 0;

    volatile struct VCPWM_REG_SPACE *reg_space = (volatile struct VCPWM_REG_SPACE *)VCREG_BASE_PWM(pwm_ch);

    switch (cc_int)
    {
    case PWM_CCINT_CCIFG:
        return reg_space->CCTL[2].fields.CCIFG;

    case PWM_CCINT_COV:
        return reg_space->CCTL[2].fields.COV;

    default:
        return 0;
    }
}

void vcpwm_clear_cc0_int_status(uint8_t pwm_ch, uint8_t cc_int)
{
    if (!is_pwm_ch_valid(pwm_ch)) return;

    if (!is_cc_int_valid(cc_int)) return;

    volatile struct VCPWM_REG_SPACE *reg_space = (volatile struct VCPWM_REG_SPACE *)VCREG_BASE_PWM(pwm_ch);

    switch (cc_int)
    {
    case PWM_CCINT_CCIFG:
        reg_space->CCTL[0].fields.CCIFG = 1;
        break;

    case PWM_CCINT_COV:
        reg_space->CCTL[0].fields.COV = 1;
        break;

    default:
        break;
    }
}

void vcpwm_clear_cc1_int_status(uint8_t pwm_ch, uint8_t cc_int)
{
    if (!is_pwm_ch_valid(pwm_ch)) return;

    if (!is_cc_int_valid(cc_int)) return;

    volatile struct VCPWM_REG_SPACE *reg_space = (volatile struct VCPWM_REG_SPACE *)VCREG_BASE_PWM(pwm_ch);

    switch (cc_int)
    {
    case PWM_CCINT_CCIFG:
        reg_space->CCTL[1].fields.CCIFG = 1;
        break;

    case PWM_CCINT_COV:
        reg_space->CCTL[1].fields.COV = 1;
        break;

    default:
        break;
    }
}

void vcpwm_clear_cc2_int_status(uint8_t pwm_ch, uint8_t cc_int)
{
    if (!is_pwm_ch_valid(pwm_ch)) return;

    if (!is_cc_int_valid(cc_int)) return;

    volatile struct VCPWM_REG_SPACE *reg_space = (volatile struct VCPWM_REG_SPACE *)VCREG_BASE_PWM(pwm_ch);

    switch (cc_int)
    {
    case PWM_CCINT_CCIFG:
        reg_space->CCTL[2].fields.CCIFG = 1;
        break;

    case PWM_CCINT_COV:
        reg_space->CCTL[2].fields.COV = 1;
        break;

    default:
        break;
    }
}

void vcpwm_clear_counter(uint8_t pwm_ch)
{
    if (!is_pwm_ch_valid(pwm_ch)) return;

    volatile struct VCPWM_REG_SPACE *reg_space = (volatile struct VCPWM_REG_SPACE *)VCREG_BASE_PWM(pwm_ch);

    reg_space->CTL.fields.CLR = 1;
}

uint8_t vcpwm_get_scci0(uint8_t pwm_ch)
{
    if (!is_pwm_ch_valid(pwm_ch)) return 0;

    volatile struct VCPWM_REG_SPACE *reg_space = (volatile struct VCPWM_REG_SPACE *)VCREG_BASE_PWM(pwm_ch);

    return reg_space->CCTL[0].fields.SCCI;
}

uint8_t vcpwm_get_scci1(uint8_t pwm_ch)
{
    if (!is_pwm_ch_valid(pwm_ch)) return 0;

    volatile struct VCPWM_REG_SPACE *reg_space = (volatile struct VCPWM_REG_SPACE *)VCREG_BASE_PWM(pwm_ch);

    return reg_space->CCTL[1].fields.SCCI;
}

uint8_t vcpwm_get_scci2(uint8_t pwm_ch)
{
    if (!is_pwm_ch_valid(pwm_ch)) return 0;

    volatile struct VCPWM_REG_SPACE *reg_space = (volatile struct VCPWM_REG_SPACE *)VCREG_BASE_PWM(pwm_ch);

    return reg_space->CCTL[2].fields.SCCI;
}


static uint8_t pwmsel_val[4] = { 0, 4, 8, 12 };

void vcpwm_outline_select(uint8_t pwm_ch, uint8_t pwm_io, uint8_t outsel)
{
    if (!is_pwm_ch_valid(pwm_ch)) return;

    if (!is_pwm_io_valid(pwm_io)) return;

    if (!is_pwm_out_sel_valid(outsel)) return;

    volatile struct VCPWM_SEL_REG_SPACE *reg_space = (volatile struct VCPWM_SEL_REG_SPACE *)VCREG_BASE_PWMSEL;

    switch (pwm_io)
    {
    case PWM_IO0:
        reg_space->O_SEL.fields.OSEL0 = pwmsel_val[pwm_ch] + outsel;
        break;

    case PWM_IO1:
        reg_space->O_SEL.fields.OSEL1 = pwmsel_val[pwm_ch] + outsel;
        break;

    case PWM_IO2:
        reg_space->O_SEL.fields.OSEL2 = pwmsel_val[pwm_ch] + outsel;
        break;

    case PWM_IO3:
        reg_space->O_SEL.fields.OSEL3 = pwmsel_val[pwm_ch] + outsel;
        break;

    default:
        break;
    }
}
