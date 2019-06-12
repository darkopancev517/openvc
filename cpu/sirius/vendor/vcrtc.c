/**
 * Copyright (c) 2018 Vertexcom Technologies, Inc. All rights reserved
 * Vertexcom Confidential Proprietary
 *
*/

#include "vcsoc.h"

#define VCREG_BASE_RTC          0x40049000

#define VCREG_BASE_RTC_ACOP0    0x40049400
#define VCREG_BASE_RTC_ACOP1    0x40049404
#define VCREG_BASE_RTC_ACOP(i)  (VCREG_BASE_RTC_ACOP0 + ((i) * (VCREG_BASE_RTC_ACOP1 - VCREG_BASE_RTC_ACOP0)))

struct VCRTC_REG_SEC {
    union {
        struct {
            uint32_t SEC            : 7;    // RTC seconds register
            uint32_t reserved       : 25;
        } fields;

        uint32_t value;
    };
};

struct VCRTC_REG_MIN {
    union {
        struct {
            uint32_t MIN            : 7;    // RTC minutes register
            uint32_t reserved       : 25;
        } fields;

        uint32_t value;
    };
};

struct VCRTC_REG_HOUR {
    union {
        struct {
            uint32_t HOUR           : 6;
            uint32_t reserved       : 26;
        } fields;

        uint32_t value;
    };
};

struct VCRTC_REG_DAY {
    union {
        struct {
            uint32_t DAY            : 6;
            uint32_t reserved       : 26;
        } fields;

        uint32_t value;
    };
};

struct VCRTC_REG_WEEK {
    union {
        struct {
            uint32_t WEEK           : 3;
            uint32_t reserved       : 29;
        } fields;

        uint32_t value;
    };
};

struct VCRTC_REG_MON {
    union {
        struct {
            uint32_t MON            : 5;
            uint32_t reserved       : 27;
        } fields;

        uint32_t value;
    };
};

struct VCRTC_REG_YEAR {
    union {
        struct {
            uint32_t YEAR           : 8;
            uint32_t reserved       : 24;
        } fields;

        uint32_t value;
    };
};

struct VCRTC_REG_WKUSEC {
    union {
        struct {
            uint32_t WKUSEC         : 6;    // Wakeup period (WKUSEC + 1) * 1 second
            uint32_t reserved       : 26;
        } fields;

        uint32_t value;
    };
};

struct VCRTC_REG_WKUMIN {
    union {
        struct {
            uint32_t WKUMIN         : 6;    // Wakeup period (WKUMIN + 1) * 1 minute
            uint32_t reserved       : 26;
        } fields;

        uint32_t value;
    };
};

struct VCRTC_REG_WKUHOUR {
    union {
        struct {
            uint32_t WKUHOUR        : 5;    // Wakeup period (WKUHOUR + 1) * 1 Hour
            uint32_t reserved       : 27;
        } fields;

        uint32_t value;
    };
};


struct VCRTC_REG_WKUCNT {
    union {
        struct {
            uint32_t WKUCNT         : 24;   // Wakeup counter period (WKUCNT + 1) * Counter Clock
            uint32_t CNTSEL         : 2;
            uint32_t reserved       : 6;
        } fields;

        uint32_t value;
    };
};

struct VCRTC_REG_CAL {
    union {
        struct {
            uint32_t CAL            : 14;
            uint32_t reserved       : 18;
        } fields;

        uint32_t value;
    };
};

struct VCRTC_REG_DIV {
    union {
        struct {
            uint32_t RTCDIV         : 26;   // Output frequency: (CLK_PLLL / (2 * RTCDIV + 1))
            uint32_t reserved       : 6;
        } fields;

        uint32_t value;
    };
};

struct VCRTC_REG_CTL {
    union {
        struct {
            uint32_t MODE           : 2;    // [0] High frequency divider mode, [1] Wait mode, [2] Capture mode
            uint32_t reserved       : 30;
        } fields;

        uint32_t value;
    };
};

struct VCRTC_REG_ITV {
    union {
        struct {
            uint32_t ITV            : 3;
            uint32_t reserved       : 29;
        } fields;

        uint32_t value;
    };
};

struct VCRTC_REG_SITV {
    union {
        struct {
            uint32_t SITV           : 6;
            uint32_t SITVEN         : 1;
            uint32_t reserved       : 25;
        } fields;

        uint32_t value;
    };
};

struct VCRTC_REG_PWD {
    union {
        struct {
            uint32_t PWDEN          : 1;
            uint32_t reserved       : 31;
        } fields;

        uint32_t value;
    };
};

struct VCRTC_REG_CE {
    union {
        struct {
            uint32_t CE             : 1;
            uint32_t BSY            : 1;
            uint32_t reserved       : 30;
        } fields;

        uint32_t value;
    };
};

struct VCRTC_REG_LOAD {
    union {
        struct {
            uint32_t LOAD           : 32;
        } fields;

        uint32_t value;
    };
};

struct VCRTC_REG_INTSTS {
    union {
        struct {
            uint32_t INTSTS0        : 1;
            uint32_t INTSTS1        : 1;
            uint32_t INTSTS2        : 1;
            uint32_t INTSTS3        : 1;
            uint32_t INTSTS4        : 1;
            uint32_t INTSTS5        : 1;
            uint32_t INTSTS6        : 1;
            uint32_t INTSTS7        : 1;
            uint32_t INTSTS8        : 1;
            uint32_t ACBSY          : 1;
            uint32_t INTSTS10       : 1;
            uint32_t reserved       : 21;
        } fields;

        uint32_t value;
    };
};

struct VCRTC_REG_INTEN {
    union {
        struct {
            uint32_t INTEN0         : 1;
            uint32_t INTEN1         : 1;
            uint32_t INTEN2         : 1;
            uint32_t INTEN3         : 1;
            uint32_t INTEN4         : 1;
            uint32_t INTEN5         : 1;
            uint32_t INTEN6         : 1;
            uint32_t INTEN7         : 1;
            uint32_t INTEN8         : 1;
            uint32_t reserved       : 1;
            uint32_t INTEN10        : 1;
            uint32_t reserved1      : 21;
        } fields;

        uint32_t value;
    };
};

struct VCRTC_REG_PSCA {
    union {
        struct {
            uint32_t PSCA           : 2;
            uint32_t reserved       : 30;
        } fields;

        uint32_t value;
    };
};

struct VCRTC_REG_ACCTRL {
    union {
        struct {
            uint32_t ACEN           : 1;
            uint32_t MANU           : 1;
            uint32_t reserved       : 1;
            uint32_t ADCSEL         : 1;
            uint32_t ACCLK          : 2;
            uint32_t ACDEL          : 2;
            uint32_t ACPER          : 5;
            uint32_t reserved1      : 1;
            uint32_t INIT           : 1;
            uint32_t reserved2      : 17;
        } fields;

        uint32_t value;
    };
};

struct VCRTC_REG_ACTI {
    union {
        struct {
            uint32_t ACTI           : 14;
            uint32_t reserved       : 18;
        } fields;

        uint32_t value;
    };
};

struct VCRTC_REG_ACF200 {
    union {
        struct {
            uint32_t F200           : 26;
            uint32_t reserved       : 6;
        } fields;

        uint32_t value;
    };
};

struct VCRTC_REG_ACADCW {
    union {
        struct {
            uint32_t ADCW           : 16;
            uint32_t reserved       : 16;
        } fields;

        uint32_t value;
    };
};

struct VCRTC_REG_ACPx {
    uint32_t value;
};

struct VCRTC_REG_ACKx {
    union {
        struct {
            uint32_t K1_K5          : 16;
            uint32_t reserved       : 16;
        } fields;

        uint32_t value;
    };
};

struct VCRTC_REG_ACKTEMP {
    union {
        struct {
            uint32_t KTEMP1         : 8;
            uint32_t KTEMP2         : 8;
            uint32_t KTEMP3         : 8;
            uint32_t KTEMP4         : 8;
        } fields;

        uint32_t value;
    };
};

struct VCRTC_REG_ACTEMP {
    union {
        struct {
            uint32_t TEMP           : 16;
            uint32_t reserved       : 16;
        } fields;

        uint32_t value;
    };
};

struct VCRTC_REG_ACPPM {
    union {
        struct {
            uint32_t PPM            : 16;
            uint32_t reserved       : 16;
        } fields;

        uint32_t value;
    };
};

struct VCRTC_REG_ACADCR {
    union {
        struct {
            uint32_t ADCR           : 16;
            uint32_t reserved       : 16;
        } fields;

        uint32_t value;
    };
};

struct VCRTC_REG_ACOPx {
    union {
        struct {
            uint32_t OPx            : 10;
            uint32_t reserved       : 22;
        } fields;

        uint32_t value;
    };
};

struct VCRTC_REG_WKUCNTR {
    union {
        struct {
            uint32_t WKUCNTR        : 24;
            uint32_t reserved       : 8;
        } fields;

        uint32_t value;
    };
};

struct VCRTC_REG_SPACE {
    struct VCRTC_REG_SEC        SEC;        // 0x00
    struct VCRTC_REG_MIN        MIN;        // 0x04
    struct VCRTC_REG_HOUR       HOUR;       // 0x08
    struct VCRTC_REG_DAY        DAY;        // 0x0C
    struct VCRTC_REG_WEEK       WEEK;       // 0x10
    struct VCRTC_REG_MON        MON;        // 0x14
    struct VCRTC_REG_YEAR       YEAR;       // 0x18
    uint32_t reserved_1C;
    struct VCRTC_REG_WKUSEC     WKUSEC;     // 0x20
    struct VCRTC_REG_WKUMIN     WKUMIN;     // 0x24
    struct VCRTC_REG_WKUHOUR    WKUHOUR;    // 0x28
    struct VCRTC_REG_WKUCNT     WKUCNT;     // 0x2C
    struct VCRTC_REG_CAL        CAL;        // 0x30
    struct VCRTC_REG_DIV        DIV;        // 0x34
    struct VCRTC_REG_CTL        CTL;        // 0x38
    struct VCRTC_REG_ITV        ITV;        // 0x3C
    struct VCRTC_REG_SITV       SITV;       // 0x40
    struct VCRTC_REG_PWD        PWD;        // 0x44
    struct VCRTC_REG_CE         CE;         // 0x48
    struct VCRTC_REG_LOAD       LOAD;       // 0x4C
    struct VCRTC_REG_INTSTS     INTSTS;     // 0x50
    struct VCRTC_REG_INTEN      INTEN;      // 0x54
    struct VCRTC_REG_PSCA       PSCA;       // 0x58
    uint32_t reserved_5C_7C[9];
    struct VCRTC_REG_ACCTRL     ACCTRL;     // 0x80
    struct VCRTC_REG_ACTI       ACTI;       // 0x84
    struct VCRTC_REG_ACF200     ACF200;     // 0x88
    struct VCRTC_REG_ACADCW     ACADCW;     // 0x8C
    struct VCRTC_REG_ACPx       ACPx[8];    // 0x90 - 0xAC
    struct VCRTC_REG_ACKx       ACKx[5];    // 0xB0 - 0xC0
    struct VCRTC_REG_ACTEMP     ACTEMP;     // 0xC4
    struct VCRTC_REG_ACPPM      ACPPM;      // 0xC8
    struct VCRTC_REG_ACADCR     ACADCR;     // 0xCC
    struct VCRTC_REG_ACKTEMP    ACKTEMP;    // 0xD0
    struct VCRTC_REG_WKUCNTR    WKUCNTR;    // 0xD4
};

void vcrtc_autocal_engine_init(void)
{
    volatile struct VCRTC_REG_SPACE *rtc = (volatile struct VCRTC_REG_SPACE *)VCREG_BASE_RTC;

    rtc->ACCTRL.fields.INIT = 1;
}

void vcrtc_autocal_deinit(void)
{
    volatile struct VCRTC_REG_SPACE *rtc = (volatile struct VCRTC_REG_SPACE *)VCREG_BASE_RTC;

    rtc->ACCTRL.value = 0;
}

void vcrtc_autocal_period(uint32_t period)
{
    volatile struct VCRTC_REG_SPACE *rtc = (volatile struct VCRTC_REG_SPACE *)VCREG_BASE_RTC;

    rtc->ACCTRL.fields.ACPER = period;
}

void vcrtc_autocal_delay(uint8_t rtc_autocal_delay)
{
    volatile struct VCRTC_REG_SPACE *rtc = (volatile struct VCRTC_REG_SPACE *)VCREG_BASE_RTC;

    rtc->ACCTRL.fields.ACDEL = rtc_autocal_delay;
}

void vcrtc_autocal_clksrc(uint8_t rtc_autocal_clksrc)
{
    volatile struct VCRTC_REG_SPACE *rtc = (volatile struct VCRTC_REG_SPACE *)VCREG_BASE_RTC;

    rtc->ACCTRL.fields.ACCLK = rtc_autocal_clksrc;
}

void vcrtc_autocal_adcsrc(uint8_t rtc_autocal_adcsrc)
{
    volatile struct VCRTC_REG_SPACE *rtc = (volatile struct VCRTC_REG_SPACE *)VCREG_BASE_RTC;

    rtc->ACCTRL.fields.ADCSEL = rtc_autocal_adcsrc;
}

void vcrtc_autocal_manual_trig_start(void)
{
    volatile struct VCRTC_REG_SPACE *rtc = (volatile struct VCRTC_REG_SPACE *)VCREG_BASE_RTC;

    rtc->ACCTRL.fields.MANU = 1;
}

void vcrtc_autocal_enable(void)
{
    volatile struct VCRTC_REG_SPACE *rtc = (volatile struct VCRTC_REG_SPACE *)VCREG_BASE_RTC;

    rtc->ACCTRL.fields.ACEN = 1;
}

void vcrtc_autocal_disable(void)
{
    volatile struct VCRTC_REG_SPACE *rtc = (volatile struct VCRTC_REG_SPACE *)VCREG_BASE_RTC;

    rtc->ACCTRL.fields.ACEN = 0;
}

void vcrtc_autocal_wait_done(void)
{
    volatile struct VCRTC_REG_SPACE *rtc = (volatile struct VCRTC_REG_SPACE *)VCREG_BASE_RTC;

    while (rtc->ACCTRL.fields.MANU);
}

int vcrtc_autocal_get_busy_flag(void)
{
    volatile struct VCRTC_REG_SPACE *rtc = (volatile struct VCRTC_REG_SPACE *)VCREG_BASE_RTC;

    return (rtc->INTSTS.fields.ACBSY) ? 1 : 0;
}


void vcrtc_wait_for_idle(void)
{
    volatile struct VCRTC_REG_SPACE *rtc = (volatile struct VCRTC_REG_SPACE *)VCREG_BASE_RTC;

    while (rtc->CE.fields.BSY);
}

void vcrtc_write_protect(bool state)
{
    volatile struct VCRTC_REG_SPACE *rtc = (volatile struct VCRTC_REG_SPACE *)VCREG_BASE_RTC;

    rtc->PWD.value = 0x5AA55AA5;

    rtc->CE.value = (state == true) ? 0xA55AA55A : 0xA55AA55B;
}

void vcrtc_write(uint8_t rtc_time, uint32_t value)
{
    volatile struct VCRTC_REG_SPACE *rtc = (volatile struct VCRTC_REG_SPACE *)VCREG_BASE_RTC;

    switch (rtc_time) {
    case RTC_SECOND:
        rtc->SEC.fields.SEC = value;
        break;

    case RTC_MINUTE:
        rtc->MIN.fields.MIN = value;
        break;

    case RTC_HOUR:
        rtc->HOUR.fields.HOUR = value;
        break;

    case RTC_DAY:
        rtc->DAY.fields.DAY = value;
        break;

    case RTC_WEEK:
        rtc->WEEK.fields.WEEK = value;
        break;

    case RTC_MONTH:
        rtc->MON.fields.MON = value;
        break;

    case RTC_YEAR:
        rtc->YEAR.fields.YEAR = value;
        break;

    default:
        break;
    }
}

uint32_t vcrtc_read(uint8_t rtc_time)
{
    volatile struct VCRTC_REG_SPACE *rtc = (volatile struct VCRTC_REG_SPACE *)VCREG_BASE_RTC;

    uint32_t rtc_data[7] = {
        rtc->SEC.fields.SEC,
        rtc->MIN.fields.MIN,
        rtc->HOUR.fields.HOUR,
        rtc->DAY.fields.DAY,
        rtc->WEEK.fields.WEEK,
        rtc->MON.fields.MON,
        rtc->YEAR.fields.YEAR,
    };

    return rtc_data[rtc_time];
}


void vcrtc_int_enable(uint8_t rtc_int)
{
    volatile struct VCRTC_REG_SPACE *rtc = (volatile struct VCRTC_REG_SPACE *)VCREG_BASE_RTC;

    rtc->INTEN.value |= (1 << rtc_int);
}

void vcrtc_int_disable(uint8_t rtc_int)
{
    volatile struct VCRTC_REG_SPACE *rtc = (volatile struct VCRTC_REG_SPACE *)VCREG_BASE_RTC;

    rtc->INTEN.value &= ~(1 << rtc_int);
}

int vcrtc_get_int_sts(uint8_t rtc_int)
{
    volatile struct VCRTC_REG_SPACE *rtc = (volatile struct VCRTC_REG_SPACE *)VCREG_BASE_RTC;

    return (rtc->INTSTS.value & (1 << rtc_int)) ? 1 : 0;
}

void vcrtc_clear_int_sts(uint8_t rtc_int)
{
    volatile struct VCRTC_REG_SPACE *rtc = (volatile struct VCRTC_REG_SPACE *)VCREG_BASE_RTC;

    rtc->INTSTS.value = (1 << rtc_int);
}

void vcrtc_clear_all_int_sts(void)
{
    volatile struct VCRTC_REG_SPACE *rtc = (volatile struct VCRTC_REG_SPACE *)VCREG_BASE_RTC;

    rtc->INTSTS.value = (0x5ff << 0);
}

void vcrtc_set_wkusec(uint8_t period)
{
    volatile struct VCRTC_REG_SPACE *rtc = (volatile struct VCRTC_REG_SPACE *)VCREG_BASE_RTC;

    vcrtc_write_protect(false);

    rtc->WKUSEC.fields.WKUSEC = period - 1;

    vcrtc_write_protect(true);
    vcrtc_wait_for_idle();
}

void vcrtc_set_wkumin(uint8_t period)
{
    volatile struct VCRTC_REG_SPACE *rtc = (volatile struct VCRTC_REG_SPACE *)VCREG_BASE_RTC;

    vcrtc_write_protect(false);

    rtc->WKUMIN.fields.WKUMIN = period - 1;

    vcrtc_write_protect(true);
    vcrtc_wait_for_idle();
}

void vcrtc_set_wkuhour(uint8_t period)
{
    volatile struct VCRTC_REG_SPACE *rtc = (volatile struct VCRTC_REG_SPACE *)VCREG_BASE_RTC;

    vcrtc_write_protect(false);

    rtc->WKUHOUR.fields.WKUHOUR = period - 1;

    vcrtc_write_protect(true);
    vcrtc_wait_for_idle();
}

void vcrtc_set_wkuitv(uint8_t type)
{
    volatile struct VCRTC_REG_SPACE *rtc = (volatile struct VCRTC_REG_SPACE *)VCREG_BASE_RTC;

    vcrtc_write_protect(false);

    rtc->ITV.fields.ITV = type;

    vcrtc_write_protect(true);
    vcrtc_wait_for_idle();
}

void vcrtc_set_wkusitv(uint8_t period)
{
    volatile struct VCRTC_REG_SPACE *rtc = (volatile struct VCRTC_REG_SPACE *)VCREG_BASE_RTC;

    vcrtc_write_protect(false);

    rtc->ITV.fields.ITV = RTC_ITV_SITVSEC;
    rtc->SITV.value = (1 << 6) | ((period&(0x3f << 0)) - 1);

    vcrtc_write_protect(true);
    vcrtc_wait_for_idle();
}

void vcrtc_set_wkucnt(uint32_t n_clock, uint8_t cnt_sel)
{
    volatile struct VCRTC_REG_SPACE *rtc = (volatile struct VCRTC_REG_SPACE *)VCREG_BASE_RTC;

    vcrtc_write_protect(false);

    rtc->WKUCNT.value = (cnt_sel << 24) | ((n_clock&(0xffffff << 0)) - 1);

    vcrtc_write_protect(true);
    vcrtc_wait_for_idle();
}


uint32_t vcrtc_get_wkucntr(void)
{
    volatile struct VCRTC_REG_SPACE *rtc = (volatile struct VCRTC_REG_SPACE *)VCREG_BASE_RTC;

    return rtc->WKUCNTR.value;
}

void vcrtc_clock_config(uint8_t rtc_clock)
{
    volatile struct VCRTC_REG_SPACE *rtc = (volatile struct VCRTC_REG_SPACE *)VCREG_BASE_RTC;

    vcrtc_write_protect(false);

    rtc->PSCA.fields.PSCA = rtc_clock;

    vcrtc_write_protect(true);
    vcrtc_wait_for_idle();    
}

void vcrtc_div_config(uint32_t frequency_hz)
{
    volatile struct VCRTC_REG_SPACE *rtc = (volatile struct VCRTC_REG_SPACE *)VCREG_BASE_RTC;

    uint32_t sysclk = vcmisc_get_sys_core_clk();

    rtc->DIV.fields.RTCDIV = sysclk/2/frequency_hz - 1;
}

void vcrtc_mode_config(uint32_t mode)
{
    volatile struct VCRTC_REG_SPACE *rtc = (volatile struct VCRTC_REG_SPACE *)VCREG_BASE_RTC;

    rtc->CTL.fields.MODE = mode;
}

