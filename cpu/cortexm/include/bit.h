#ifndef BIT_H
#define BIT_H

#include <stdint.h>

#include "cpu.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef CPU_HAS_BITBAND
#if (__CORTEX_M >= 3)
#define CPU_HAS_BITBAND 1
#else
#define CPU_HAS_BITBAND 0
#endif
#endif

#if CPU_HAS_BITBAND

static inline volatile void *bitband_addr(volatile void *ptr, uintptr_t bit)
{
    return (volatile void *)((((uintptr_t)ptr) & 0xF0000000ul) + 0x2000000ul +
        ((((uintptr_t)ptr) & 0xFFFFFul) << 5) + (bit << 2));
}

static inline void bit_set32(volatile uint32_t *ptr, uint8_t bit)
{
    *((volatile uint32_t *)bitband_addr(ptr, bit)) = 1;
}

static inline void bit_set16(volatile uint16_t *ptr, uint8_t bit)
{
    *((volatile uint16_t *)bitband_addr(ptr, bit)) = 1;
}

static inline void bit_set8(volatile uint8_t *ptr, uint8_t bit)
{
    *((volatile uint8_t *)bitband_addr(ptr, bit)) = 1;
}

static inline void bit_clear32(volatile uint32_t *ptr, uint8_t bit)
{
    *((volatile uint32_t *)bitband_addr(ptr, bit)) = 0;
}

static inline void bit_clear16(volatile uint16_t *ptr, uint8_t bit)
{
    *((volatile uint16_t *)bitband_addr(ptr, bit)) = 0;
}

static inline void bit_clear8(volatile uint8_t *ptr, uint8_t bit)
{
    *((volatile uint8_t *)bitband_addr(ptr, bit)) = 0;
}

static inline void bit_clear8(volatile uint8_t *ptr, uint8_t bit)
{
    *((volatile uint8_t *)bitband_addr(ptr, bit)) = 0;
}

#else /* CPU_HAS_BITBAND */
/* CPU does not have bitbanding, fall back to plain C */
static inline void bit_set32(volatile uint32_t *ptr, uint8_t bit)
{
    *ptr |= (1 << (bit));
}

static inline void bit_set16(volatile uint16_t *ptr, uint8_t bit)
{
    *ptr |= (1 << (bit));
}

static inline void bit_set8(volatile uint8_t *ptr, uint8_t bit)
{
    *ptr |= (1 << (bit));
}

static inline void bit_clear32(volatile uint32_t *ptr, uint8_t bit)
{
    *ptr &= ~(1 << (bit));
}

static inline void bit_clear16(volatile uint16_t *ptr, uint8_t bit)
{
    *ptr &= ~(1 << (bit));
}

static inline void bit_clear8(volatile uint8_t *ptr, uint8_t bit)
{
    *ptr &= ~(1 << (bit));
}

#endif /* CPU_HAS_BITBAND */

#ifdef __cplusplus
}
#endif

#endif /* BIT_H */
