/**
 * Copyright (c) 2018 Vertexcom Technologies, Inc. All rights reserved
 * Vertexcom Confidential Proprietary
 *
*/

#ifndef __VC_DMA_H
#define __VC_DMA_H

#include <stdint.h>
#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif

#define DMA_CH0     0
#define DMA_CH1     1
#define DMA_CH2     2
#define DMA_CH3     3

// DMA request source selection
#define DMA_REQSRC_SOFT         0
#define DMA_REQSRC_UART0_TX     2
#define DMA_REQSRC_UART0_RX     3
#define DMA_REQSRC_UART1_TX     4
#define DMA_REQSRC_UART1_RX     5
#define DMA_REQSRC_UART2_TX     6
#define DMA_REQSRC_UART2_RX     7
#define DMA_REQSRC_UART3_TX     8
#define DMA_REQSRC_UART3_RX     9
#define DMA_REQSRC_UART4_TX     10
#define DMA_REQSRC_UART4_RX     11
#define DMA_REQSRC_UART5_TX     12
#define DMA_REQSRC_UART5_RX     13
#define DMA_REQSRC_UART6_TX     14
#define DMA_REQSRC_UART6_RX     15
#define DMA_REQSRC_UART32K0     16
#define DMA_REQSRC_UART32K1     17
#define DMA_REQSRC_ISO78160_TX  18
#define DMA_REQSRC_ISO78160_RX  19
#define DMA_REQSRC_ISO78161_TX  20
#define DMA_REQSRC_ISO78161_RX  21
#define DMA_REQSRC_TIMER0       22
#define DMA_REQSRC_TIMER1       23
#define DMA_REQSRC_TIMER2       24
#define DMA_REQSRC_TIMER3       25
#define DMA_REQSRC_SPI1_TX      26
#define DMA_REQSRC_SPI1_RX      27
#define DMA_REQSRC_SPI2_TX      28
#define DMA_REQSRC_SPI2_RX      29
#define DMA_REQSRC_SPI3_TX      30
#define DMA_REQSRC_SPI3_RX      31
#define DMA_REQSRC_SOFT2        32
#define DMA_REQSRC_CMP1         34
#define DMA_REQSRC_CMP2         35

#define DMA_TRANSMODE_SINGLE    0
#define DMA_TRANSMODE_PACKAGE   1

#define DMA_DESTADDRMODE_FIX    0   // fix address
#define DMA_DESTADDRMODE_PEND   1   // incremental but rounded at package end
#define DMA_DESTADDRMODE_FEND   2   // incremental but rounded at frame end

#define DMA_SRCADDRMODE_FIX     0   // fix address
#define DMA_SRCADDRMODE_PEND    1   // incremental but rounded at package end
#define DMA_SRCADDRMODE_FEND    2   // incremental but rounded at frame end

#define DMA_TRANSSIZE_8BIT      0
#define DMA_TRANSSIZE_16BIT     1
#define DMA_TRANSSIZE_32BIT     2

#define DMA_INT_PACKET_END      0
#define DMA_INT_FRAME_END       1
#define DMA_INT_DATA_ABORT      2

#define DMA_INTSTS_BUSY         0
#define DMA_INTSTS_PACKET_END   1
#define DMA_INTSTS_FRAME_END    2
#define DMA_INTSTS_DATA_ABORT   3

void vcdma_enable(uint8_t ch);

void vcdma_disable(uint8_t ch);


void vcdma_config_reset(uint8_t ch);

void vcdma_config_force_stop(uint8_t ch);

void vcdma_config_dest_addr(uint8_t ch, uint32_t addr);

void vcdma_config_src_addr(uint8_t ch, uint32_t addr);

void vcdma_config_frame_len(uint8_t ch, uint8_t len);

void vcdma_config_package_len(uint8_t ch, uint8_t len);

void vcdma_config_16bit_package_len(uint8_t ch, uint16_t len); // only when sequence mode is true

void vcdma_config_request_source(uint8_t ch, uint8_t source);

void vcdma_config_continous_mode(uint8_t ch, bool state);

void vcdma_config_transfer_mode(uint8_t ch, uint8_t mode);

void vcdma_config_sequence_mode(uint8_t ch, bool state);

void vcdma_config_dest_addr_mode(uint8_t ch, uint8_t mode);

void vcdma_config_src_addr_mode(uint8_t ch, uint8_t mode);

void vcdma_config_transfer_size(uint8_t ch, uint8_t size);

void vcdma_config_enable_int(uint8_t ch, uint8_t interrupt);

void vcdma_config_disable_int(uint8_t ch, uint8_t interrupt);


void vcdma_enable_stop_transmit(uint8_t ch);

void vcdma_disable_stop_transmit(uint8_t ch);

uint8_t vcdma_get_transferred_frame_len(uint8_t ch);

uint8_t vcdma_get_transferred_package_len(uint8_t ch);


int vcdma_get_int_status(uint8_t ch, uint8_t intsts);

void vcdma_clear_int_status(uint8_t ch, uint8_t intsts);


#ifdef __cplusplus
}
#endif

#endif // __VC_DMA_H

