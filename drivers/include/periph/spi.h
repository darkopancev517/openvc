#ifndef PERIPH_SPI_H
#define PERIPH_SPI_H

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <limits.h>

#include "periph/gpio.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Default SPI device access macro.
 */
#define SPI_DEV(x)      (x - 1)

/**
 * Define global value for undefined SPI device.
 */
#define SPI_UNDEF       (UINT_MAX)

#define SPI_CS_UNDEF    (GPIO_UNDEF)

#ifndef SPI_HWCS
#define SPI_HWCS        (SPI_CS_UNDEF)
#endif

typedef unsigned int spi_t;

typedef gpio_t spi_cs_t;

enum {
    SPI_OK      = 0,
    SPI_NODEV   = -1,
    SPI_NOCS    = -2,
    SPI_NOMODE  = -3,
    SPI_NOCLK   = -4,
};

/**
 * Available SPI modes, defining the configuration of clock polarity
 * and clock phase
 *
 * - MODE_0: CPOL=0, CPHA=0 - The first data bit is sampled by the receiver on
 *           the first SCK rising SCK edge (this mode is used most often).
 * - MODE_1: CPOL=0, CPHA=1 - The first data bit is sampled by the receiver on
 *           the second rising SCK edge.
 * - MODE_2: CPOL=1, CPHA=0 - The first data bit is sampled by the receiver on
 *           the first falling SCK edge.
 * - MODE_3: CPOL=1, CPHA=1 - The first data bit is sampled by the receiver on
 *           the second falling SCK edge.
 */
typedef enum {
    SPI_MODE_0 = 0,     /* CPOL=0, CPHA=0 */
    SPI_MODE_1,         /* CPOL=0, CPHA=1 */
    SPI_MODE_2,         /* CPOL=1, CPHA=0 */
    SPI_MODE_3          /* CPOL=1, CPHA=1 */
} spi_mode_t;

typedef enum {
    SPI_CLK_100KHZ = 0,
    SPI_CLK_400KHZ,
    SPI_CLK_1MHZ,
    SPI_CLK_5MHZ,
    SPI_CLK_10MHZ
} spi_clk_t;

void spi_init(spi_t bus);

void spi_init_pins(spi_t bus);

int spi_init_cs(spi_t bus, spi_cs_t cs);

/**
 * Start a new SPI transaction.
 */
int spi_acquire(spi_t bus, spi_cs_t cs, spi_mode_t mode, spi_clk_t clk);

/**
 * Finish an ongoing SPI transaction by releasing the given SPI bus.
 */
void spi_release(spi_t bus);

void spi_transfer_bytes(spi_t bus, spi_cs_t cs, bool cont, const void *out, void *in, size_t len);

#ifdef __cplusplus
}
#endif

#endif /* PERIPH_SPI_H */
