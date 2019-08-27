#ifndef CENTAURI_PMU_CSR_H
#define CENTAURI_PMU_CSR_H

#ifdef __cplusplus
extern "C" {
#endif

#define PMU_CSR_BASE 0x4002C000

#define CENT_RTN_REG_COUNT 16

/* retention register mapping */
#define CENT_RTN_REG_BASE 0x4002C0A0

#define CENTI_REG_HCMD_INTR 0x4002C048
#define HCMD_TRIGGER_MASK  0x00000001

#define __IO volatile
typedef struct __PMU_CSR_T {
    __IO uint32_t PMU_CCMD_CR;                    // 0x0
    __IO uint32_t PMU_CR;                         // 0x4
    __IO uint32_t PMU_CGCR;                       // 0x8
    __IO uint32_t PMU_REV0[1];                    // 0xc ~ 0xc
    __IO uint32_t PMU_FEPWD_CR;                   // 0x10
    __IO uint32_t PMU_REV1[1];                    // 0x14 ~ 0x14
    __IO uint32_t PMU_PROBE_CR;                   // 0x18
    __IO uint32_t PMU_4M_TIMER_SR;                // 0x1c
    __IO uint32_t PMU_REV2[1];                    // 0x20 ~ 0x20
    __IO uint32_t PMU_32K_TIMER_SR1;              // 0x24
    __IO uint32_t PMU_REV3[1];                    // 0x28 ~ 0x28
    __IO uint32_t PMU_32K_TIMER_IR;               // 0x2c
    __IO uint32_t PMU_HCMD_CR;                    // 0x30
    __IO uint32_t PMU_REV4[2];                    // 0x34 ~ 0x38
    __IO uint32_t PMU_CST_IR;                     // 0x3c
    __IO uint32_t PMU_IER;                        // 0x40
    __IO uint32_t PMU_ISR;                        // 0x44
    __IO uint32_t PMU_HOST_INTR_TR;               // 0x48
    __IO uint32_t PMU_REV5[13];                   // 0x4c ~ 0x7c
    __IO uint32_t SEM1;                           // 0x80
    __IO uint32_t SEM2;                           // 0x84
    __IO uint32_t SEM3;                           // 0x88
    __IO uint32_t SEM4;                           // 0x8c
    __IO uint32_t HCMD_ITCR1;                     // 0x90
    __IO uint32_t HCMD_ITCR2;                     // 0x94
    __IO uint32_t HCMD_ITCR3;                     // 0x98
    __IO uint32_t HCMD_ITCR4;                     // 0x9c
    __IO uint32_t RESR1;                          // 0xa0
    __IO uint32_t RESR2;                          // 0xa4
    __IO uint32_t RESR3;                          // 0xa8
    __IO uint32_t RESR4;                          // 0xac
    __IO uint32_t RESR5;                          // 0xb0
    __IO uint32_t RESR6;                          // 0xb4
    __IO uint32_t RESR7;                          // 0xb8
    __IO uint32_t RESR8;                          // 0xbc
    __IO uint32_t RESR9;                          // 0xc0
    __IO uint32_t RESR10;                         // 0xc4
    __IO uint32_t RESR11;                         // 0xc8
    __IO uint32_t RESR12;                         // 0xcc
    __IO uint32_t RESR13;                         // 0xd0
    __IO uint32_t RESR14;                         // 0xd4
    __IO uint32_t RESR15;                         // 0xd8
    __IO uint32_t RESR16;                         // 0xdc
    __IO uint32_t RESR17;                         // 0xe0
    __IO uint32_t RESR18;                         // 0xe4
    __IO uint32_t RESR19;                         // 0xe8
    __IO uint32_t RESR20;                         // 0xec
    __IO uint32_t RESR21;                         // 0xf0
    __IO uint32_t RESR22;                         // 0xf4
    __IO uint32_t RESR23;                         // 0xf8
    __IO uint32_t RESR24;                         // 0xfc
    __IO uint32_t RESR25;                         // 0x100
    __IO uint32_t RESR26;                         // 0x104
    __IO uint32_t RESR27;                         // 0x108
    __IO uint32_t RESR28;                         // 0x10c
    __IO uint32_t RESR29;                         // 0x110
    __IO uint32_t RESR30;                         // 0x114
    __IO uint32_t RESR31;                         // 0x118
    __IO uint32_t RESR32;                         // 0x11c     
}PMU_CSR_T;

#define CENT_PMU_ADDR(reg)              (PMU_CSR_BASE + offsetof(PMU_CSR_T, reg))

#define CENT_RTN_HOSTIF_INT_MASK_0      CENT_PMU_ADDR(RESR32)
#define CENT_RTN_HOSTIF_INT_MASK_1      CENT_PMU_ADDR(RESR31)
#define CENT_RTN_CALI_SETTING           CENT_PMU_ADDR(RESR30)
#define CENT_RTN_SW_CTRL             	CENT_PMU_ADDR(RESR29)
#define CENT_RTN_CMD_ACK_PARAM          CENT_PMU_ADDR(RESR28)
#define CENT_RTN_REG_SYS_CTRL           CENT_PMU_ADDR(RESR27)
#define CENT_RTN_32K_CTRL_ADDR          CENT_PMU_ADDR(RESR26)
#define CENT_RTN_PERIOD_TOLERANCE       CENT_PMU_ADDR(RESR25)   // ms uint
#define CENT_RTN_PERIOD_TIME            CENT_PMU_ADDR(RESR24)   // ms uint
#define CENT_RTN_REG_FUN_SWITCH         CENT_PMU_ADDR(RESR23)
#define CENT_RTN_REG_PROBE_PIN          CENT_PMU_ADDR(RESR22)
#define CENT_RTN_HOSTIF_PHYINT       	CENT_PMU_ADDR(RESR21)
#define CENT_RTN_STATE               	CENT_PMU_ADDR(RESR20)
#define CENT_RTN_CAL32K4M_RESULT     	CENT_PMU_ADDR(RESR19)
#define CENT_RTN_RX_PARAM1	     		CENT_PMU_ADDR(RESR18)
#define CENT_RTN_RX_PARAM2	     		CENT_PMU_ADDR(RESR17)
#define CENT_RTN_LP_LISTEN     			CENT_PMU_ADDR(RESR16)
#define CENT_RTN_CGCR_IDLE     			CENT_PMU_ADDR(RESR15)

//#define PMU_CSR__ROM_RG1 				CENT_PMU_ADDR(RESR11)
//#define PMU_CSR__ROM_RG2 				CENT_PMU_ADDR(RESR10)
//#define PMU_CSR__ROM_RG3 				CENT_PMU_ADDR(RESR9)
//#define PMU_CSR__ROM_RG4 				CENT_PMU_ADDR(RESR8)
#define RF_CHANNEL_FREQ 				CENT_PMU_ADDR(RESR3)
//#define PMU_CSR__ROM_IQC2 		    CENT_PMU_ADDR(RESR13)
//#define PMU_CSR__RXADC_DACREFIQ 		CENT_PMU_ADDR(RESR14)

#ifdef __cplusplus
}
#endif

#endif /* CENTAURI_PMU_CSR_H */
