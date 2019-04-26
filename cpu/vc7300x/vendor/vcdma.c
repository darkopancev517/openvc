/**
 * Copyright (c) 2018 Vertexcom Technologies, Inc. All rights reserved
 * Vertexcom Confidential Proprietary
 *
*/

#include "vcsoc.h"

#define VCREG_BASE_DMA          0x40040000
#define VCREG_BASE_DMA_IE       VCREG_BASE_DMA
#define VCREG_BASE_DMA_STS      (VCREG_BASE_DMA + 0x04)
#define VCREG_BASE_DMA_CH0      (VCREG_BASE_DMA + 0x10)
#define VCREG_BASE_DMA_CH1      (VCREG_BASE_DMA + 0x20)
#define VCREG_BASE_DMA_CH(i)    (VCREG_BASE_DMA_CH0 + ((i) * (VCREG_BASE_DMA_CH1 - VCREG_BASE_DMA_CH0)))

struct VCDMA_REG_IE {
    union {
        struct {
            uint32_t C0PEIE         : 1;    // (rw) channel 0 package end interrupt enable
            uint32_t C1PEIE         : 1;    // (rw) channel 1 package end interrupt enable
            uint32_t C2PEIE         : 1;    // (rw) channel 2 package end interrupt enable
            uint32_t C3PEIE         : 1;    // (rw) channel 3 package end interrupt enable
            uint32_t C0FEIE         : 1;    // (rw) channel 0 frame end interrupt enable
            uint32_t C1FEIE         : 1;    // (rw) channel 1 frame end interrupt enable
            uint32_t C2FEIE         : 1;    // (rw) channel 2 frame end interrupt enable
            uint32_t C3FEIE         : 1;    // (rw) channel 3 frame end interrupt enable
            uint32_t C0DAIE         : 1;    // (rw) channel 0 data abort interrupt enable
            uint32_t C1DAIE         : 1;    // (rw) channel 1 data abort interrupt enable
            uint32_t C2DAIE         : 1;    // (rw) channel 2 data abort interrupt enable
            uint32_t C3DAIE         : 1;    // (rw) channel 3 data abort interrupt enable
            uint32_t reserved       : 20;
        } fields;

        uint32_t value;
    };
};

struct VCDMA_REG_STS {
    union {
        struct {
            uint32_t C0BUSY         : 1;    // (r) dma channel 0 busy register
            uint32_t C1BUSY         : 1;    // (r) dma channel 1 busy register
            uint32_t C2BUSY         : 1;    // (r) dma channel 2 busy register
            uint32_t C3BUSY         : 1;    // (r) dma channel 3 busy register
            uint32_t C0PE           : 1;    // (rc) channel 0 package end interrupt flag
            uint32_t C1PE           : 1;    // (rc) channel 1 package end interrupt flag
            uint32_t C2PE           : 1;    // (rc) channel 2 package end interrupt flag
            uint32_t C3PE           : 1;    // (rc) channel 3 package end interrupt flag
            uint32_t C0FE           : 1;    // (rc) channel 0 frame end interrupt flag
            uint32_t C1FE           : 1;    // (rc) channel 1 frame end interrupt flag
            uint32_t C2FE           : 1;    // (rc) channel 2 frame end interrupt flag
            uint32_t C3FE           : 1;    // (rc) channel 3 frame end interrupt flag
            uint32_t C0DA           : 1;    // (rc) channel 0 data abort interrupt flag
            uint32_t C1DA           : 1;    // (rc) channel 1 data abort interrupt flag
            uint32_t C2DA           : 1;    // (rc) channel 2 data abort interrupt flag
            uint32_t C3DA           : 1;    // (rc) channel 3 data abort interrupt flag
            uint32_t reserved       : 16;
        } fields;

        uint32_t value;
    };
};

struct VCDMA_REG_CTL {
    union {
        struct {
            uint32_t EN             : 1;    // (rw) dma channel enable register
            uint32_t SIZE           : 2;    // (rw) transfer size mode
            uint32_t SMODE          : 2;    // (rw) source address mode
            uint32_t DMODE          : 2;    // (rw) destination address mode
            uint32_t SEQ_MODE       : 1;
            uint32_t reserved       : 4;
            uint32_t TMODE          : 1;    // (rw) transfer mode selection register
            uint32_t CONT           : 1;    // (rw) continous mode
            uint32_t reserved1      : 1;
            uint32_t STOP           : 1;    // (rw) force stop dma transfer
            uint32_t DMASEL         : 6;
            uint32_t reserved2      : 10;
        } fields;

        uint32_t value;
    };
};

struct VCDMA_REG_SRC {
    uint32_t value;
};

struct VCDMA_REG_DST {
    uint32_t value;
};

struct VCDMA_REG_LEN {
    union {
        struct {
            uint32_t PLEN           : 8;    // (rw) package length register (actual len: PLEN + 1)
            uint32_t FLEN           : 8;    // (rw) frame length register (actual len: FLEN + 1)
            uint32_t CPLEN          : 8;    // (r) current package length
            uint32_t CFLEN          : 8;    // (r) current frame transferred length
        } fields;

        uint32_t value;
    };
};

struct VCDMA_REG_SPACE {
    struct VCDMA_REG_CTL CTL;
    struct VCDMA_REG_SRC SRC;
    struct VCDMA_REG_DST DST;
    struct VCDMA_REG_LEN LEN;
};

void vcdma_enable(uint8_t ch)
{
    if ((ch < DMA_CH0) || (ch > DMA_CH3)) return;

    volatile struct VCDMA_REG_SPACE *reg_space =  (volatile struct VCDMA_REG_SPACE *)VCREG_BASE_DMA_CH(ch);

    reg_space->CTL.fields.EN = 1;
}

void vcdma_disable(uint8_t ch)
{
    if ((ch < DMA_CH0) || (ch > DMA_CH3)) return;

    volatile struct VCDMA_REG_SPACE *reg_space =  (volatile struct VCDMA_REG_SPACE *)VCREG_BASE_DMA_CH(ch);

    reg_space->CTL.fields.EN = 0;
}


void vcdma_config_reset(uint8_t ch)
{
    if ((ch < DMA_CH0) || (ch > DMA_CH3)) return;

    //volatile struct VCDMA_REG_STS *dma_sts = (volatile struct VCDMA_REG_STS *)VCREG_BASE_DMA_STS;

    volatile struct VCDMA_REG_SPACE *reg_space = (volatile struct VCDMA_REG_SPACE *)VCREG_BASE_DMA_CH(ch);

    reg_space->CTL.value = 0;

    //dma_sts->value = (0xfff << 4);
}

void vcdma_config_force_stop(uint8_t ch)
{
    if ((ch < DMA_CH0) || (ch > DMA_CH3)) return;

    //volatile struct VCDMA_REG_STS *dma_sts = (volatile struct VCDMA_REG_STS *)VCREG_BASE_DMA_STS;

    volatile struct VCDMA_REG_SPACE *reg_space = (volatile struct VCDMA_REG_SPACE *)VCREG_BASE_DMA_CH(ch);

    reg_space->CTL.value = 0x8000;

    //dma_sts->value = (0xfff << 4);
}

void vcdma_config_dest_addr(uint8_t ch, uint32_t addr)
{
    if ((ch < DMA_CH0) || (ch > DMA_CH3)) return;

    volatile struct VCDMA_REG_SPACE *reg_space =  (volatile struct VCDMA_REG_SPACE *)VCREG_BASE_DMA_CH(ch);

    reg_space->DST.value = addr;
}

void vcdma_config_src_addr(uint8_t ch, uint32_t addr)
{
    if ((ch < DMA_CH0) || (ch > DMA_CH3)) return;

    volatile struct VCDMA_REG_SPACE *reg_space =  (volatile struct VCDMA_REG_SPACE *)VCREG_BASE_DMA_CH(ch);

    reg_space->SRC.value = addr;
}

void vcdma_config_frame_len(uint8_t ch, uint8_t len)
{
    if ((ch < DMA_CH0) || (ch > DMA_CH3)) return;
    if (len < 0) return;

    volatile struct VCDMA_REG_SPACE *reg_space =  (volatile struct VCDMA_REG_SPACE *)VCREG_BASE_DMA_CH(ch);

    reg_space->LEN.fields.FLEN = len - 1;
}

void vcdma_config_package_len(uint8_t ch, uint8_t len)
{
    if ((ch < DMA_CH0) || (ch > DMA_CH3)) return;
    if (len < 0) return;

    volatile struct VCDMA_REG_SPACE *reg_space =  (volatile struct VCDMA_REG_SPACE *)VCREG_BASE_DMA_CH(ch);

    reg_space->LEN.fields.PLEN = len - 1;
}

void vcdma_config_16bit_package_len(uint8_t ch, uint16_t len)
{
    if ((ch < DMA_CH0) || (ch > DMA_CH3)) return;
    if (len < 0) return;

    volatile struct VCDMA_REG_SPACE *reg_space =  (volatile struct VCDMA_REG_SPACE *)VCREG_BASE_DMA_CH(ch);

    reg_space->LEN.fields.PLEN = len - 1;
}

void vcdma_config_request_source(uint8_t ch, uint8_t source)
{
    if ((ch < DMA_CH0) || (ch > DMA_CH3)) return;

    volatile struct VCDMA_REG_SPACE *reg_space =  (volatile struct VCDMA_REG_SPACE *)VCREG_BASE_DMA_CH(ch);

    reg_space->CTL.fields.DMASEL = source;
}

void vcdma_config_continous_mode(uint8_t ch, bool state)
{
    if ((ch < DMA_CH0) || (ch > DMA_CH3)) return;

    volatile struct VCDMA_REG_SPACE *reg_space =  (volatile struct VCDMA_REG_SPACE *)VCREG_BASE_DMA_CH(ch);

    reg_space->CTL.fields.CONT = (state == true) ? 1 : 0;
}

void vcdma_config_transfer_mode(uint8_t ch, uint8_t mode)
{
    if ((ch < DMA_CH0) || (ch > DMA_CH3)) return;

    if ((mode < DMA_TRANSMODE_SINGLE) || (mode > DMA_TRANSMODE_PACKAGE)) return;

    volatile struct VCDMA_REG_SPACE *reg_space =  (volatile struct VCDMA_REG_SPACE *)VCREG_BASE_DMA_CH(ch);
   
    reg_space->CTL.fields.TMODE = mode;
}

void vcdma_config_sequence_mode(uint8_t ch, bool state)
{
    if ((ch < DMA_CH0) || (ch > DMA_CH3)) return;

    volatile struct VCDMA_REG_SPACE *reg_space =  (volatile struct VCDMA_REG_SPACE *)VCREG_BASE_DMA_CH(ch);
 
    reg_space->CTL.fields.SEQ_MODE = (state == true) ? 1 : 0;
}

void vcdma_config_dest_addr_mode(uint8_t ch, uint8_t mode)
{
    if ((ch < DMA_CH0) || (ch > DMA_CH3)) return;

    if ((mode < DMA_DESTADDRMODE_FIX) || (mode > DMA_DESTADDRMODE_FEND)) return;

    volatile struct VCDMA_REG_SPACE *reg_space =  (volatile struct VCDMA_REG_SPACE *)VCREG_BASE_DMA_CH(ch);
 
    reg_space->CTL.fields.DMODE = mode;
}

void vcdma_config_src_addr_mode(uint8_t ch, uint8_t mode)
{
    if ((ch < DMA_CH0) || (ch > DMA_CH3)) return;

    if ((mode < DMA_SRCADDRMODE_FIX) || (mode > DMA_SRCADDRMODE_FEND)) return;

    volatile struct VCDMA_REG_SPACE *reg_space =  (volatile struct VCDMA_REG_SPACE *)VCREG_BASE_DMA_CH(ch);
 
    reg_space->CTL.fields.SMODE = mode;
}

void vcdma_config_transfer_size(uint8_t ch, uint8_t size)
{
    if ((ch < DMA_CH0) || (ch > DMA_CH3)) return;

    if ((size < DMA_TRANSSIZE_8BIT) || (size > DMA_TRANSSIZE_32BIT)) return;

    volatile struct VCDMA_REG_SPACE *reg_space =  (volatile struct VCDMA_REG_SPACE *)VCREG_BASE_DMA_CH(ch);
   
    reg_space->CTL.fields.SIZE = size;
}

void vcdma_config_enable_int(uint8_t ch, uint8_t interrupt)
{
    if ((ch < DMA_CH0) || (ch > DMA_CH3)) return;

    if ((interrupt < DMA_INT_PACKET_END) || (interrupt > DMA_INT_DATA_ABORT)) return;

    volatile struct VCDMA_REG_IE *dma_ie = (volatile struct VCDMA_REG_IE *)VCREG_BASE_DMA_IE;

    dma_ie->value |= (1 << (ch + (interrupt * 4)));
}

void vcdma_config_disable_int(uint8_t ch, uint8_t interrupt)
{
    if ((ch < DMA_CH0) || (ch > DMA_CH3)) return;

    if ((interrupt < DMA_INT_PACKET_END) || (interrupt > DMA_INT_DATA_ABORT)) return;

    volatile struct VCDMA_REG_IE *dma_ie = (volatile struct VCDMA_REG_IE *)VCREG_BASE_DMA_IE;

    dma_ie->value &= ~(1 << (ch + (interrupt * 4)));
}


void vcdma_enable_stop_transmit(uint8_t ch)
{
    if ((ch < DMA_CH0) || (ch > DMA_CH3)) return;

    volatile struct VCDMA_REG_SPACE *reg_space = (volatile struct VCDMA_REG_SPACE *)VCREG_BASE_DMA_CH(ch);

    reg_space->CTL.fields.STOP = 1;
}

void vcdma_disable_stop_transmit(uint8_t ch)
{
    if ((ch < DMA_CH0) || (ch > DMA_CH3)) return;

    volatile struct VCDMA_REG_SPACE *reg_space = (volatile struct VCDMA_REG_SPACE *)VCREG_BASE_DMA_CH(ch);

    reg_space->CTL.fields.STOP = 0;
}

uint8_t vcdma_get_transferred_frame_len(uint8_t ch)
{
    if ((ch < DMA_CH0) || (ch > DMA_CH3)) return 0;

    volatile struct VCDMA_REG_SPACE *reg_space = (volatile struct VCDMA_REG_SPACE *)VCREG_BASE_DMA_CH(ch);

    return (uint8_t)reg_space->LEN.fields.CFLEN;
}

uint8_t vcdma_get_transferred_package_len(uint8_t ch)
{
    if ((ch < DMA_CH0) || (ch > DMA_CH3)) return 0;

    volatile struct VCDMA_REG_SPACE *reg_space = (volatile struct VCDMA_REG_SPACE *)VCREG_BASE_DMA_CH(ch);

    return (uint8_t)reg_space->LEN.fields.CPLEN;
}

int vcdma_get_int_status(uint8_t ch, uint8_t intsts)
{
    if ((ch < DMA_CH0) || (ch > DMA_CH3)) return 0;

    if ((intsts < DMA_INTSTS_BUSY) || (intsts > DMA_INTSTS_DATA_ABORT)) return 0;

    volatile struct VCDMA_REG_STS *dma_sts = (volatile struct VCDMA_REG_STS *)VCREG_BASE_DMA_STS;

    return (dma_sts->value & (1 << (ch + (intsts * 4)))) ? 1 : 0;
}

void vcdma_clear_int_status(uint8_t ch, uint8_t intsts)
{
    if ((ch < DMA_CH0) || (ch > DMA_CH3)) return;

    if ((intsts < DMA_INTSTS_PACKET_END) || (intsts > DMA_INTSTS_DATA_ABORT)) return;

    volatile struct VCDMA_REG_STS *dma_sts = (volatile struct VCDMA_REG_STS *)VCREG_BASE_DMA_STS;

    dma_sts->value = (1 << (ch + (intsts * 4)));
}

