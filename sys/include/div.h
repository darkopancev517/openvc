#ifndef DIV_H
#define DIV_H

#include <assert.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

#define DIV_H_INV_15625_32    0x431bde83ul
#define DIV_H_INV_15625_64    0x431bde82d7b634dbull
#define DIV_H_INV_15625_SHIFT 12

uint64_t _div_mulhi64(const uint64_t a, const uint64_t b);

static inline uint64_t div_u64_by_15625(uint64_t val)
{
    if (val > 16383999997ull) {
        return (_div_mulhi64(DIV_H_INV_15625_64, val) >> DIV_H_INV_15625_SHIFT);
    }
    return (val * DIV_H_INV_15625_32) >> (DIV_H_INV_15625_SHIFT + 32);
}

static inline uint32_t div_u64_by_125(uint64_t val)
{
  /* a higher value would overflow the result type */
  assert(val <= 536870911999LLU);

  uint32_t hi = val >> 32;
  uint32_t lo = val;
  uint32_t r = (lo >> 16) + (hi << 16);
  uint32_t res = r / 125;
  r = ((r % 125) << 16) + (lo & 0xFFFF);
  res = (res << 16) + r / 125;
  return res;
}

static inline uint64_t div_u64_by_1000000(uint64_t val)
{
    return div_u64_by_15625(val) >> 6;
}

static inline uint32_t div_u32_by_15625div512(uint32_t val)
{
    return ((uint64_t)(val) * DIV_H_INV_15625_32) >> (DIV_H_INV_15625_SHIFT + 32 - 9);
}

static inline uint64_t div_u64_by_15625div512(uint64_t val)
{
    /*
     * This saves around 1400 bytes of ROM on Cortex-M platforms (both ARMv6 and
     * ARMv7) from avoiding linking against __aeabi_uldivmod and related helpers
     */
    if (val > 16383999997ull) {
        /* this would overflow 2^64 in the multiplication that follows, need to
         * use the long version */
        return (_div_mulhi64(DIV_H_INV_15625_64, val) >> (DIV_H_INV_15625_SHIFT - 9));
    }
    return (val * DIV_H_INV_15625_32) >> (DIV_H_INV_15625_SHIFT + 32 - 9);
}

static inline uint32_t div_u32_by_44488(uint32_t val)
{
    return ((uint64_t)val * 0xBC8F1391UL) >> (15 + 32);
}

static inline uint32_t div_u32_mod_44488(uint32_t val)
{
    return val - (div_u32_by_44488(val)*44488);
}

#ifdef __cplusplus
}
#endif

#endif /* DIV_H */
