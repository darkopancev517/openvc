#ifndef CPU_CONF_H
#define CPU_CONF_H

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Default stack size configurations
 */
#define THREAD_EXTRA_STACKSIZE_PRINTF (512)
#define THREAD_STACKSIZE_DEFAULT (1024)
#define THREAD_STACKSIZE_IDLE (256)
#define THREAD_STACKSIZE_MAIN (THREAD_STACKSIZE_DEFAULT + THREAD_EXTRA_STACKSIZE_PRINTF)
#define ISR_STACKSIZE (1024)

/* ARM Cortex-M specific CPU configuration */
#define CPU_DEFAULT_IRQ_PRIO (63U)

#define CPU_IRQ_NUMOF (64U)

/* NVIC use 64 priority levels */
#define __NVIC_PRIO_BITS (6U)

typedef enum {
    NonMaskableInt_IRQn     = -14,
    HardFault_IRQn          = -13,
    SVCall_IRQn             = -5,
    PendSV_IRQn             = -2,
    SysTick_IRQn            = -1,

    Pmu_IRQn                = 0,
    Rtc_IRQn                = 1,
    U32k0_IRQn              = 2,
    U32k1_IRQn              = 3,
    I2c1_IRQn               = 4,
    Spi1_IRQn               = 5,
    Uart0_IRQn              = 6,
    Uart1_IRQn              = 7,
    Uart2_IRQn              = 8,
    Uart3_IRQn              = 9,
    Uart4_IRQn              = 10,
    Uart5_IRQn              = 11,
    Iso78160_IRQn           = 12,
    Iso78161_IRQn           = 13,
    Tim0_IRQn               = 14,
    Tim1_IRQn               = 15,
    Tim2_IRQn               = 16,
    Tim3_IRQn               = 17,
    Pwm0_IRQn               = 18,
    Pwm1_IRQn               = 19,
    Pwm2_IRQn               = 20,
    Pwm3_IRQn               = 21,
    Dma_IRQn                = 22,
    EmbFlash_IRQn           = 23,
    Ana_IRQn                = 24,
    Spi2_IRQn               = 27,
    Spi3_IRQn               = 28,
    KeyScan_IRQn            = 29,
    Uart6_IRQn              = 30,
    Crypto_IRQn             = 31,
    I2c2_IRQn               = 36,
    Gpio_IRQn               = 37,
} IRQn_Type;

#include "core_cm3.h"

#ifdef __cplusplus
}
#endif

#endif /* CPU_CONF_H */
