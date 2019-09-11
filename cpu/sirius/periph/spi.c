#include <assert.h>
#include <stdbool.h>

#include "cpu.h"
#include "vcsoc.h"
#include "irq.h"

#include "periph/spi.h"
#include "xtimer.h"

/**
 * Number of SPI peripheral interface.
 */
#define SPI_NUMOF (3U)

typedef struct spi_config {
    spi_cs_t cs;
    spi_mode_t mode;
    spi_clk_t clk;
    uint8_t spi_lock;
} spi_config_t;

static uint8_t spi_apbperiph[SPI_NUMOF] = {
    APBPERIPH_SPI1,
    APBPERIPH_SPI2,
    APBPERIPH_SPI3
};

static spi_config_t spi_config[SPI_NUMOF] = {
    { SPI_CS_UNDEF, SPI_MODE_0, SPI_CLK_5MHZ, 0 },
    { SPI_CS_UNDEF, SPI_MODE_0, SPI_CLK_5MHZ, 0 },
    { SPI_CS_UNDEF, SPI_MODE_0, SPI_CLK_5MHZ, 0 }
};

static uint8_t spi_dma_reqsrc_rx[SPI_NUMOF] = {
    DMA_REQSRC_SPI1_RX,
    DMA_REQSRC_SPI2_RX,
    DMA_REQSRC_SPI3_RX
};

static uint8_t spi_dma_reqsrc_tx[SPI_NUMOF] = {
    DMA_REQSRC_SPI1_TX,
    DMA_REQSRC_SPI2_TX,
    DMA_REQSRC_SPI3_TX
};

static void _spi_config_mode(spi_t bus, spi_mode_t mode)
{
    if (mode == SPI_MODE_0 ) {
        /* CPOL=0, CPHA=0 */
        vcspi_config_sck_polarity(bus, 0);
        vcspi_config_sck_phase(bus, 0);
    } else if (mode == SPI_MODE_1) {
        /* CPOL=0, CPHA=1 */
        vcspi_config_sck_polarity(bus, 0);
        vcspi_config_sck_phase(bus, 1);
    } else if (mode == SPI_MODE_2) {
        /* CPOL=1, CPHA=0 */
        vcspi_config_sck_polarity(bus, 1);
        vcspi_config_sck_phase(bus, 0);
    } else if (mode == SPI_MODE_3) {
        /* CPOL=1, CPHA=1 */
        vcspi_config_sck_polarity(bus, 1);
        vcspi_config_sck_phase(bus, 1);
    } else {
        assert(0); /* unknown spi mode */
    }
}

static void _spi_config_clk(spi_t bus, spi_clk_t clk)
{
    /* set spi clock: clock source = apb / 2 = 40MHz / 2 = 20 MHz */
    if (clk == SPI_CLK_100KHZ) {
        assert(0); /* unsupported spi clock */
    } else if (clk == SPI_CLK_400KHZ) {
        vcspi_config_clk_div(bus, 50);
    } else if (clk == SPI_CLK_1MHZ) {
        vcspi_config_clk_div(bus, 20);
    } else if (clk == SPI_CLK_5MHZ) {
        vcspi_config_clk_div(bus, 4);
    } else if (clk == SPI_CLK_10MHZ) {
        vcspi_config_clk_div(bus, 2);
    } else {
        assert(0); /* unsupported spi clock */
    }
}

void spi_init(spi_t bus)
{
    assert(bus < SPI_NUMOF && bus > 0);

    /* reset spi configuration */
    vcspi_config_reset(bus);

    /* enable spi peripheral clk */
    vcmisc_config_apb_periph(spi_apbperiph[bus], true);

    /* enable dma clock */
    vcmisc_config_apb_periph(APBPERIPH_DMA, true);
    vcmisc_config_ahb_periph(AHBPERIPH_DMA, true);

    /* set as master */
    vcspi_config_mode(bus, SPIMODE_MASTER);

    /* use gpio as chip-select */
    vcspi_config_master_cs_gpio(bus, true);

    vcspi_config_swap(bus, true);
    vcspi_config_transfer_width(bus, SPIWIDTH_8BITS);
    vcspi_config_firstbit(bus, SPIFIRSTBIT_MSB);

    /* initialize spi default config */
    _spi_config_mode(bus, spi_config[bus].mode);
    _spi_config_clk(bus, spi_config[bus].clk);

    /* initialize spi pins */
    spi_init_pins(bus);

    /* enable smart mode for spi dma */
    vcspi_smart_mode(bus, true);

    /* enable spi engine */
    vcspi_enable(bus);

    /* setup spi dma */
    vcdma_config_reset(DMA_CH0);
    vcdma_config_reset(DMA_CH1);

    vcdma_config_src_addr(DMA_CH1, vcspi_get_receive_addr(bus));
    vcdma_config_request_source(DMA_CH1, spi_dma_reqsrc_rx[bus]);

    vcdma_config_continous_mode(DMA_CH1, false);
    vcdma_config_transfer_mode(DMA_CH1, DMA_TRANSMODE_SINGLE);
    vcdma_config_sequence_mode(DMA_CH1, false);
    vcdma_config_dest_addr_mode(DMA_CH1, DMA_DESTADDRMODE_PEND);
    vcdma_config_src_addr_mode(DMA_CH1, DMA_SRCADDRMODE_FIX);
    vcdma_config_transfer_size(DMA_CH1, DMA_TRANSSIZE_8BIT);

    vcdma_config_dest_addr(DMA_CH0, vcspi_get_transmit_addr(bus));
    vcdma_config_request_source(DMA_CH0, spi_dma_reqsrc_tx[bus]);

    vcdma_config_continous_mode(DMA_CH0, false);
    vcdma_config_transfer_mode(DMA_CH0, DMA_TRANSMODE_SINGLE);
    vcdma_config_sequence_mode(DMA_CH0, false);
    vcdma_config_dest_addr_mode(DMA_CH0, DMA_DESTADDRMODE_FIX);
    vcdma_config_src_addr_mode(DMA_CH0, DMA_SRCADDRMODE_PEND);
    vcdma_config_transfer_size(DMA_CH0, DMA_TRANSSIZE_8BIT);
}

void spi_init_pins(spi_t bus)
{
    assert(bus < SPI_NUMOF && bus > 0);

    /* enable spi gpio special function */
    vcsfio_enable_spi(bus);
}

int spi_init_cs(spi_t bus, spi_cs_t cs)
{
    assert(bus < SPI_NUMOF && bus > 0);

    /* initialize spi gpio cs as output */
    gpio_init((gpio_t)cs, GPIO_OUT);

    /* set cs gpio to high */
    gpio_set((gpio_t)cs);

    return SPI_OK;
}

int spi_acquire(spi_t bus, spi_cs_t cs, spi_mode_t mode, spi_clk_t clk)
{
    assert(bus < SPI_NUMOF && bus > 0);

    if (spi_config[bus].spi_lock) {
        return SPI_LOCKED;
    }

    if (cs != SPI_CS_UNDEF && spi_config[bus].cs != cs) {
        spi_init_cs(bus, cs);
        spi_config[bus].cs = cs;
    }

    /* take spi lock */
    spi_config[bus].spi_lock = 1;

    if (spi_config[bus].mode != mode) {
        _spi_config_mode(bus, mode);
    }

    if (spi_config[bus].clk != clk) {
        _spi_config_clk(bus, clk);
    }

    return SPI_OK;
}

void spi_release(spi_t bus)
{
    assert(bus < SPI_NUMOF && bus > 0);
    assert(spi_config[bus].spi_lock);

    /* give spi lock */
    spi_config[bus].spi_lock = 0;
}

static void _transfer_dma(spi_t bus, const void *out, void *in, size_t len)
{
    // channel 1 for receiver (must enable first)
    vcdma_config_dest_addr(DMA_CH1, (uint32_t)in);
    vcdma_config_frame_len(DMA_CH1, 1);
    vcdma_config_package_len(DMA_CH1, len);

    vcdma_enable(DMA_CH1);

    // channel 0 for transmitter
    vcdma_config_src_addr(DMA_CH0, (uint32_t)out);
    vcdma_config_frame_len(DMA_CH0, 1);
    vcdma_config_package_len(DMA_CH0, len);

    vcdma_enable(DMA_CH0);

    int busy = 0;

    uint32_t timeout = xtimer_now().ticks32 + 10000; /* 10 ms timeout */

    do {
        busy = vcdma_get_int_status(DMA_CH0, DMA_INTSTS_BUSY) ||
               vcdma_get_int_status(DMA_CH1, DMA_INTSTS_BUSY);
    } while (busy && timeout > xtimer_now().ticks32);

    assert(!busy && timeout > xtimer_now().ticks32);
}

void spi_transfer_bytes(spi_t bus, spi_cs_t cs, bool cont, const void *out, void *in, size_t len)
{
    assert(bus < SPI_NUMOF && bus > 0);

    /* Note: make sure at least one input or one output buffer is given and
     * mutex has been locked or spi bus is acquired */
    assert((out || in) && (spi_config[bus].spi_lock == 1));

    /* active the given chip-select line if cs is defined */
    if (cs != SPI_CS_UNDEF) {
        gpio_clear((gpio_t)cs);
    }

    /* transfer or receive spi data */
    _transfer_dma(bus, out, in, len);

    /* release the chip select if not continous and cs is defined*/
    if (!cont && cs != SPI_CS_UNDEF) {
        gpio_set((gpio_t)cs);
    }
}
