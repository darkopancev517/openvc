/**
 * Copyright (c) 2018 Vertexcom Technologies, Inc. All rights reserved
 * Vertexcom Confidential Proprietary
 *
*/

#include "vcsoc.h"

#define VCREG_BASE_ANA              0x4004b000
#define VCREG_BASE_ANA_INT          0x4004b054

#define VCREG_BASE_ANA_ADCCTRL1     0x4004b070
#define VCREG_BASE_ANA_ADCDATA0     0x4004b080
#define VCREG_BASE_ANA_ADCDATA1     0x4004b084
#define VCREG_BASE_ANA_ADCDATA_ALL  0x4004b0C0
#define VCREG_BASE_ANA_ADCDATA(i)   (VCREG_BASE_ANA_ADCDATA0 + ((i) * (VCREG_BASE_ANA_ADCDATA1 - VCREG_BASE_ANA_ADCDATA0)))

struct VCANA_REG_LDOCTRL {
    union {
        struct {
            uint32_t NMLDO_EN_F         : 1;    // (rw) Normal LDO force enable control register
            uint32_t reserved           : 1;
            uint32_t NMLDO15_VSEL       : 2;    // (rw) Normal LDO15 voltage selection
            uint32_t LPLDO15_VSEL_NM    : 2;    // (rw) Low power LDO15 voltage selection under idle or normal mode
            uint32_t reserved2          : 2;
            uint32_t LPLDO15_VSEL_SLP   : 2;    // (rw) Low power LDO15 voltage selection under sleep or deep sleep mode
            uint32_t reserved3          : 2;            
            uint32_t PORL_OFF           : 1;    // (rw) PORL disable control register
            uint32_t PORH_OFF           : 1;    // (rw) PORH disable control register
            uint32_t VDD2_FON           : 1;    // (rw) VDD2 Domain force enabled control register
            uint32_t VDD3_FON           : 1;    // (rw) VDD3 Domain force enabled control register
            uint32_t reserved4      : 16;
        } fields;

        uint32_t value;
    };
};


struct VCANA_REG_LVDCTRL {
    union {
        struct {
            uint32_t PWD            : 1;    // (rw) LVD power down control register
            uint32_t reserved       : 1;
            uint32_t VTHSEL         : 2;    // (rw) LVD trigger voltage selection
            uint32_t PDNS           : 1;    // (rw) This register is used to set the deep sleep behavior when LVD is 0
            uint32_t reserved2      : 1;
            uint32_t LVD_DEBSEL     : 2;    // (rw) LVD de-bounce control register
            uint32_t LVD_SMPSEL     : 2;    // (rw) LVD sample frequency control register
            uint32_t reserved3      : 22;
        } fields;

        uint32_t value;
    };
};

struct VCANA_REG_CLKCTRL1 {
    union {
        struct {
            uint32_t LFXO_PWD       : 1;    //
            uint32_t LFXO_CURSEL    : 1;    //
            uint32_t LFXO_CSEL      : 3;    //
            uint32_t LFRCO_PWD      : 1;    //
            uint32_t reserved       : 2;    //
            uint32_t LDRCO_CSEL     : 5;    //
            uint32_t LFRCO_RSEL     : 3;    //
            uint32_t reserved2      :16;    //
        } fields;

        uint32_t value;
    };
};

struct VCANA_REG_CLKCTRL2 {
    union {
        struct {
            uint32_t HFRCO_PWD      : 1;    //
            uint32_t HFRCO_HF       : 1;    // HFRCO high frequency mode control register.  0: lower frequency mode(6.22592 MHz), 1: high frequency mode(39.3216 MHz)
            uint32_t AC_EN          : 1;    //
            uint32_t AC_RTRIM_EN    : 1;    //
            uint32_t AC_PERIOD      : 1;    //
            uint32_t LFCCODE_INIT   : 7;    //
            uint32_t LFRCODE_INIT   : 4;    //
            uint32_t NO_BINARY      : 1;    //
            uint32_t reserved1      : 4;
            uint32_t HFCCODE_INIT   : 7;
            uint32_t HFRCODE_INIT   : 4;
        } fields;

        uint32_t value;
    };
};

struct VCANA_REG_CLKCTRL4 {
    union {
        struct {
            uint32_t AC_LOCK        : 1;    // (r) auto calibration lock status register
            uint32_t AC_STATE       : 3;    // (r) auto calibration status register
            uint32_t AC_ERROR       : 1;    // (r) auto calibration error status register
            uint32_t CCODE          : 7;    // (r) current c-code output value
            uint32_t RCODE          : 4;    // (r) current r-code output value
            uint32_t reserved       : 16;
        } fields;

        uint32_t value;
    };
};

struct VCANA_REG_ADCCTRL1 {
    union {
        struct {
            uint32_t ADC_EN         : 1;    // (rw) ADC enable control register
            uint32_t ADC_MSTART     : 1;    // (rw) ADC manual conversion start control register
            uint32_t ADC_STOP       : 1;    // (rw) ADC manual conversion stop control register
            uint32_t ADC_CONTI      : 1;    // (rw) ADC continous mode
            uint32_t ADC_TRGSEL     : 3;    // (rw) ADC auto conversion trigger source selection
            uint32_t ADC_ALIEN      : 1;    // (rw) ADC data alien control register
            uint32_t ADC_DELAY      : 8;    // (rw) ADC enable delay control register
            uint32_t ADC_CLKSEL     : 1;    // (rw) ADC control source selection
            uint32_t ADC_FEN        : 1;    // (rw) ADC force enable control register
            uint32_t reserved       : 2;
            uint32_t ADC_CLKDIV     : 8;    // (rw) ADC sample rate control reg. ADC_CLK = ADC_CLKSRC / (ADC_CLKDIV + 1)
            uint32_t reserved2      : 4;
        } fields;

        uint32_t value;
    };
};

struct VCANA_REG_ADCCTRL2 {
    union {
        struct {
            uint32_t ADC_VREFBIAS   : 2;
            uint32_t ADC_VMIDBIAS   : 2;
            uint32_t ADC_BUFBIAS    : 2;
            uint32_t reserved       : 1;
            uint32_t ADC_VREFSEL    : 1;    // (rw) ADC VREF control register
            uint32_t ADC_DIFFEN     : 1;    // (rw) ADC differential mode control register
            uint32_t reserved2      : 7;
            uint32_t ADC_RSV        : 16;
        } fields;

        uint32_t value;
    };
};

struct VCANA_REG_ADCCTRL3 {
    union {
        struct {
            uint32_t ADC_MCHEN      : 16;   // (rw) each bit control the conversion enable of each channel under manual trigger mode
            uint32_t ADC_DIVSEL     : 16;   // (rw) each bit control the division enable of each channel
        } fields;

        uint32_t value;
    };
};

struct VCANA_REG_ADCCTRL4 {
    union {
        struct {
            uint32_t ADC_ACHEN      : 16;   // (rw) each bit control the conversion enable of each channel under auto trigger mode
            uint32_t reserved       : 16;
        } fields;

        uint32_t value;
    };
};

struct VCANA_REG_ADCDATAx {
    union {
        struct {
            uint32_t ADCDATAx       : 16;   // (rw) the result of ADC conversion will be stored in these register. Only the channel specified by ADC_MCHEN or ADC_ACHEN will be updated.
            uint32_t reserved       : 16;
        } fields;

        uint32_t value;
    };
};

struct VCANA_REG_ADCDATA {
    union {
        struct {
            uint32_t ADCDATA        : 16;   // (rw) the result of ADC conversion will be stored in this register. This register is stored most recently sampled ADC of all 16 channels.
            uint32_t reserved       : 16;
        } fields;

        uint32_t value;
    };
};

struct VCANA_REG_INTSTS {
    union {
        struct {
            uint32_t INTSTS0        : 1;    // (rw) interrupt flag of HFACLOCK
            uint32_t INTSTS1        : 1;    // (rw) interrupt flag of HFACERROR
            uint32_t INTSTS2        : 1;    // (rw) interrupt flag of COMP1 (has longer response time 90us)
            uint32_t INTSTS3        : 1;    // (rw) interrupt flag of COMP2 (has longer response time 90us)
            uint32_t INTSTS4        : 1;    // (rw) interrupt flag of LVD (has longer response time 90us)
            uint32_t INTSTS5        : 1;    // (rw) interrupt flag of COMP1 (has longer response time 3 PCLKs)
            uint32_t INTSTS6        : 1;    // (rw) interrupt flag of COMP2 (host longer response time 3 PCLKs)
            uint32_t INTSTS7        : 1;    // (rw) interrupt flag of LVD (has longer response time 3 PCLKs)
            uint32_t reserved       : 2;
            uint32_t INTSTS10       : 1;    // (rw) interrupt flag of TRNGERR
            uint32_t INTSTS11       : 1;    // (rw) interrupt flag of auto ADC conversion done
            uint32_t INTSTS12       : 1;    // (rw) interrupt flag of auto ADC single conversion done
            uint32_t INTSTS13       : 1;    // (rw) interrupt flag of manual ADC conversion done
            uint32_t INTSTS14       : 1;    // (rw) interrupt flag of manual ADC multiple entry error
            uint32_t INTSTS15       : 1;    // (rw) interrupt flag of ADC sample overrun
            uint32_t INTSTS16       : 1;
            uint32_t INTSTSADC_OVR  : 15;
        } fields;

        uint32_t value;
    };
};

struct VCANA_REG_INTEN {
    union {
        struct {
            uint32_t INTEN_INTSTS0  : 1;
            uint32_t INTEN_INTSTS1  : 1;
            uint32_t INTEN_INTSTS2  : 1;
            uint32_t INTEN_INTSTS3  : 1;
            uint32_t INTEN_INTSTS4  : 1;
            uint32_t INTEN_INTSTS5  : 1;
            uint32_t INTEN_INTSTS6  : 1;
            uint32_t INTEN_INTSTS7  : 1;
            uint32_t reserved       : 2;
            uint32_t INTEN_INTSTS10 : 1;
            uint32_t INTEN_INTSTS11 : 1;
            uint32_t INTEN_INTSTS12 : 1;
            uint32_t INTEN_INTSTS13 : 1;
            uint32_t INTEN_INTSTS14 : 1;
            uint32_t INTEN_INTSTS15 : 1;
            uint32_t INTEN_INTSTS16 : 1;
            uint32_t INTEN_INTSTSADC_OVR : 15;
        } fields;

        uint32_t value;
    };
};

struct VCANA_REG_SPACE {
    uint32_t reserved;
    struct VCANA_REG_LDOCTRL  LDOCTRL;    
    struct VCANA_REG_LVDCTRL  LVDCTRL;
    uint32_t reserved1;
    struct VCANA_REG_CLKCTRL1 CLKCTRL1;
    struct VCANA_REG_CLKCTRL2 CLKCTRL2;
    uint32_t reserved3;
    struct VCANA_REG_CLKCTRL4 CLKCTRL4;
};

struct VCANA_ADC_REG_SPACE {
    struct VCANA_REG_ADCCTRL1       ADCCTRL1;
    struct VCANA_REG_ADCCTRL2       ADCCTRL2;
    struct VCANA_REG_ADCCTRL3       ADCCTRL3;
    struct VCANA_REG_ADCCTRL4       ADCCTRL4;
    struct VCANA_REG_ADCDATAx       ADCDATAx[16];
    struct VCANA_REG_ADCDATA        ADCDATA_ALL;
};

struct VCANA_INT_REG_SPACE {
    struct VCANA_REG_INTSTS     ANAINTSTS;
    struct VCANA_REG_INTEN      ANAINTEN;
};

void vcana_config_vdd3_fon(int bHigh)
{
    volatile struct VCANA_REG_SPACE *reg_space = (volatile struct VCANA_REG_SPACE *)VCREG_BASE_ANA;
    reg_space->LDOCTRL.fields.VDD3_FON = bHigh? 1:0;
}

void vcana_config_lpldo_vsel(int vSel)
{
    volatile struct VCANA_REG_SPACE *reg_space = (volatile struct VCANA_REG_SPACE *)VCREG_BASE_ANA;
    reg_space->LDOCTRL.fields.LPLDO15_VSEL_SLP = vSel;
}

void vcana_config_lfxo_cursel(int bHigh)
{
    volatile struct VCANA_REG_SPACE *reg_space = (volatile struct VCANA_REG_SPACE *)VCREG_BASE_ANA;
    reg_space->CLKCTRL1.fields.LFXO_CURSEL = bHigh? 1:0;
}

void vcana_config_lfxo_capsel(int capsel)
{
    volatile struct VCANA_REG_SPACE *reg_space = (volatile struct VCANA_REG_SPACE *)VCREG_BASE_ANA;
    reg_space->CLKCTRL1.fields.LFXO_CSEL = capsel;
}


void vcana_config_lfrco_pwr(int bHigh)
{
    volatile struct VCANA_REG_SPACE *reg_space = (volatile struct VCANA_REG_SPACE *)VCREG_BASE_ANA;
    reg_space->CLKCTRL1.fields.LFRCO_PWD = bHigh? 1:0;
}

void vcana_config_hfrco_hf(uint32_t clk)
{
    volatile struct VCANA_REG_SPACE *reg_space = (volatile struct VCANA_REG_SPACE *)VCREG_BASE_ANA;

    switch (clk) {
        case 39321600:
            reg_space->CLKCTRL2.fields.HFRCO_HF = 1;
            break;
        case  6225920:
            reg_space->CLKCTRL2.fields.HFRCO_HF = 0;
            break;
        default:
            reg_space->CLKCTRL2.fields.HFRCO_HF = 0;
            break;
    }
}

int vcana_auto_calib_lock(void)
{
    volatile struct VCANA_REG_SPACE *reg_space = (volatile struct VCANA_REG_SPACE *)VCREG_BASE_ANA;

    return (reg_space->CLKCTRL4.fields.AC_LOCK == 1) ? 1 : 0;
}

void vcana_adc_enable(void)
{
    volatile struct VCANA_ADC_REG_SPACE *reg_space = (volatile struct VCANA_ADC_REG_SPACE *)VCREG_BASE_ANA_ADCCTRL1;

    reg_space->ADCCTRL1.fields.ADC_EN = 1;
}

void vcana_adc_disable(void)
{
    volatile struct VCANA_ADC_REG_SPACE *reg_space = (volatile struct VCANA_ADC_REG_SPACE *)VCREG_BASE_ANA_ADCCTRL1;

    reg_space->ADCCTRL1.fields.ADC_EN = 0;
}

void vcana_adc_clk_source_select(uint8_t clksel)
{
    if ((clksel != ADC_CLKSEL_HFRCO) && (clksel != ADC_CLKSEL_RTCLK)) return;

    volatile struct VCANA_ADC_REG_SPACE *reg_space = (volatile struct VCANA_ADC_REG_SPACE *)VCREG_BASE_ANA_ADCCTRL1;

    reg_space->ADCCTRL1.fields.ADC_CLKSEL = clksel;
}

void vcana_adc_force_enable(bool state)
{
    volatile struct VCANA_ADC_REG_SPACE *reg_space = (volatile struct VCANA_ADC_REG_SPACE *)VCREG_BASE_ANA_ADCCTRL1;

    reg_space->ADCCTRL1.fields.ADC_FEN = (state == true) ? 1 : 0;
}

void vcana_adc_config_delay(uint8_t n_adc_clocks)
{
     volatile struct VCANA_ADC_REG_SPACE *reg_space = (volatile struct VCANA_ADC_REG_SPACE *)VCREG_BASE_ANA_ADCCTRL1;
   
     reg_space->ADCCTRL1.fields.ADC_DELAY = n_adc_clocks;
}

void vcana_adc_config_data_align(uint8_t adc_data_align)
{
     volatile struct VCANA_ADC_REG_SPACE *reg_space = (volatile struct VCANA_ADC_REG_SPACE *)VCREG_BASE_ANA_ADCCTRL1;

     reg_space->ADCCTRL1.fields.ADC_ALIEN = adc_data_align;
}

void vcana_adc_config_continous_mode(bool state)
{
     volatile struct VCANA_ADC_REG_SPACE *reg_space = (volatile struct VCANA_ADC_REG_SPACE *)VCREG_BASE_ANA_ADCCTRL1;

     reg_space->ADCCTRL1.fields.ADC_CONTI = (state == true) ? 1 : 0;
}

void vcana_adc_config_clkdiv(uint8_t clkdiv)
{
    // Note: ADC_CLK = ADC_CLK_SOURCE / (ADC_CLKDIV + 1)

    volatile struct VCANA_ADC_REG_SPACE *reg_space = (volatile struct VCANA_ADC_REG_SPACE *)VCREG_BASE_ANA_ADCCTRL1;

    reg_space->ADCCTRL1.fields.ADC_CLKDIV = (clkdiv > 0) ? clkdiv - 1 : clkdiv;
}

void vcana_adc_manual_conversion_start(void)
{
    volatile struct VCANA_ADC_REG_SPACE *reg_space = (volatile struct VCANA_ADC_REG_SPACE *)VCREG_BASE_ANA_ADCCTRL1;

    reg_space->ADCCTRL1.fields.ADC_MSTART = 1;
}

int vcana_adc_get_manual_conversion_start_status(void)
{
    volatile struct VCANA_ADC_REG_SPACE *reg_space = (volatile struct VCANA_ADC_REG_SPACE *)VCREG_BASE_ANA_ADCCTRL1;

    // 0 : previous manual convert start action is done
    // 1 : previous manual convert start action is on-going

    return reg_space->ADCCTRL1.fields.ADC_MSTART;
}

void vcana_adc_manual_conversion_stop(void)
{
    volatile struct VCANA_ADC_REG_SPACE *reg_space = (volatile struct VCANA_ADC_REG_SPACE *)VCREG_BASE_ANA_ADCCTRL1;

    reg_space->ADCCTRL1.fields.ADC_STOP = 1;
}

int vcana_adc_get_manual_conversion_stop_status(void)
{
    volatile struct VCANA_ADC_REG_SPACE *reg_space = (volatile struct VCANA_ADC_REG_SPACE *)VCREG_BASE_ANA_ADCCTRL1;

    // 0 : previous manual convert stop action is done
    // 1 : previous manual convert stop action is on-going

    return reg_space->ADCCTRL1.fields.ADC_STOP;
}

void vcana_adc_auto_trigger_source_sel(uint8_t adc_trigger)
{
    if ((adc_trigger < ADC_AUTOTRIGGER_OFF) || (adc_trigger > ADC_AUTOTRIGGER_TIMER3_OV)) return;

    volatile struct VCANA_ADC_REG_SPACE *reg_space = (volatile struct VCANA_ADC_REG_SPACE *)VCREG_BASE_ANA_ADCCTRL1;

    reg_space->ADCCTRL1.fields.ADC_TRGSEL = adc_trigger;
}

void vcana_adc_vref_sel(uint8_t adc_vref)
{
    if ((adc_vref != ADC_VREF_INTERNAL_LDO) && (adc_vref != ADC_VREF_EXTERNAL_LDO)) return;

    volatile struct VCANA_ADC_REG_SPACE *reg_space = (volatile struct VCANA_ADC_REG_SPACE *)VCREG_BASE_ANA_ADCCTRL1;

    reg_space->ADCCTRL2.fields.ADC_VREFSEL = adc_vref;
}

void vcana_adc_config_differential_mode(uint8_t adc_diff_mode)
{
    if ((adc_diff_mode != ADC_DIFFMODE_SINGLE_END) && (adc_diff_mode != ADC_DIFFMODE_DIFF_ENABLE)) return;

    volatile struct VCANA_ADC_REG_SPACE *reg_space = (volatile struct VCANA_ADC_REG_SPACE *)VCREG_BASE_ANA_ADCCTRL1;

    reg_space->ADCCTRL2.fields.ADC_DIFFEN = adc_diff_mode;
}

void vcana_adc_config_channel_division_enable(uint8_t adc_channel, bool state)
{
    if ((adc_channel < ADC_CH0) || (adc_channel > ADC_CH15)) return;

    volatile struct VCANA_ADC_REG_SPACE *reg_space = (volatile struct VCANA_ADC_REG_SPACE *)VCREG_BASE_ANA_ADCCTRL1;

    if (state == true) {
        reg_space->ADCCTRL3.fields.ADC_DIVSEL |= (1 << adc_channel);
    } else {
        reg_space->ADCCTRL3.fields.ADC_DIVSEL &= ~(1 << adc_channel);
    }
}

void vcana_adc_config_channel_manual_conversion_enable(uint8_t adc_channel, bool state)
{
    if ((adc_channel < ADC_CH0) || (adc_channel > ADC_CH15)) return;

    volatile struct VCANA_ADC_REG_SPACE *reg_space = (volatile struct VCANA_ADC_REG_SPACE *)VCREG_BASE_ANA_ADCCTRL1;

    if (state == true) {
        reg_space->ADCCTRL3.fields.ADC_MCHEN |= (1 << adc_channel);
    } else {
        reg_space->ADCCTRL3.fields.ADC_MCHEN &= ~(1 << adc_channel);
    }
}

void vcana_adc_config_channel_auto_conversion_enable(uint8_t adc_channel, bool state)
{
    if ((adc_channel < ADC_CH0) || (adc_channel > ADC_CH15)) return;

    volatile struct VCANA_ADC_REG_SPACE *reg_space = (volatile struct VCANA_ADC_REG_SPACE *)VCREG_BASE_ANA_ADCCTRL1;

    if (state == true) {
        reg_space->ADCCTRL4.fields.ADC_ACHEN |= (1 << adc_channel);
    } else {
        reg_space->ADCCTRL4.fields.ADC_ACHEN &= ~(1 << adc_channel);
    }
}

uint32_t vcana_adc_manual_read_data(uint8_t adc_channel)
{
    if ((adc_channel < ADC_CH0) || (adc_channel > ADC_CH15)) return 0;

    volatile struct VCANA_ADC_REG_SPACE *reg_space = (volatile struct VCANA_ADC_REG_SPACE *)VCREG_BASE_ANA_ADCCTRL1;

    // manual start adc conversion
    if (reg_space->ADCCTRL1.fields.ADC_MSTART == 0) {
        reg_space->ADCCTRL1.fields.ADC_MSTART = 1;
    }

    if (!reg_space->ADCCTRL1.fields.ADC_CONTI) {
        // wait until conversion is finish
        while (reg_space->ADCCTRL1.value & 0x2);
    }

    return *(volatile uint32_t *)VCREG_BASE_ANA_ADCDATA(adc_channel);
}

// LVD (Low Voltage Detection) functions

void vcana_lvd_enable(void)
{
    volatile struct VCANA_REG_SPACE *reg_space = (volatile struct VCANA_REG_SPACE *)VCREG_BASE_ANA;

    reg_space->LVDCTRL.fields.PWD = 0;
}

void vcana_lvd_disable(void)
{
    volatile struct VCANA_REG_SPACE *reg_space = (volatile struct VCANA_REG_SPACE *)VCREG_BASE_ANA;

    reg_space->LVDCTRL.fields.PWD = 1;
}

void vcana_lvd_trigger_sel(uint8_t trigsel)
{
    if ((trigsel < 0) || (trigsel > 3)) return;

    volatile struct VCANA_REG_SPACE *reg_space = (volatile struct VCANA_REG_SPACE *)VCREG_BASE_ANA;

    reg_space->LVDCTRL.fields.VTHSEL = trigsel;
}

void vcana_lvd_config_debounce(uint8_t debsel)
{
    if ((debsel < 0) || (debsel > 3)) return;

    volatile struct VCANA_REG_SPACE *reg_space = (volatile struct VCANA_REG_SPACE *)VCREG_BASE_ANA;

    reg_space->LVDCTRL.fields.LVD_DEBSEL = debsel;
}

void vcana_lvd_config_sample_cycles(uint8_t sample)
{
    if ((sample < 0) || (sample > 3)) return;

    volatile struct VCANA_REG_SPACE *reg_space = (volatile struct VCANA_REG_SPACE *)VCREG_BASE_ANA;

    reg_space->LVDCTRL.fields.LVD_SMPSEL = sample;
}

void vcana_lvd_int_enable(void)
{
    volatile struct VCANA_INT_REG_SPACE *reg_space = (volatile struct VCANA_INT_REG_SPACE *)VCREG_BASE_ANA_INT;

    reg_space->ANAINTEN.fields.INTEN_INTSTS4 = 1;
}

int vcana_lvd_get_int_sts(void)
{
    volatile struct VCANA_INT_REG_SPACE *reg_space = (volatile struct VCANA_INT_REG_SPACE *)VCREG_BASE_ANA_INT;

    return reg_space->ANAINTSTS.fields.INTSTS4;
}

void vcana_lvd_clear_int_sts(void)
{
    volatile struct VCANA_INT_REG_SPACE *reg_space = (volatile struct VCANA_INT_REG_SPACE *)VCREG_BASE_ANA_INT;

    reg_space->ANAINTSTS.fields.INTSTS4 = 1;
}

void vcana_adc_temperature_init(void)
{
    vcana_adc_clk_source_select(ADC_CLKSEL_HFRCO);
    vcana_adc_config_clkdiv(40);
    vcana_adc_config_channel_manual_conversion_enable(ADC_CH10, true);
    vcana_adc_config_continous_mode(true);
    vcana_adc_enable();
}
