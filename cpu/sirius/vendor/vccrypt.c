/**
 * Copyright (c) 2018 Vertexcom Technologies, Inc. All rights reserved
 * Vertexcom Confidential Proprietary
 *
*/

#include "vcsoc.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#define SEC_MODE 0
#define ETH_MODE 1

#define AES_128_KEY_SIZE 16
#define AES_192_KEY_SIZE 24
#define AES_256_KEY_SIZE 32

/* see RFC 3610 */
#ifndef CCM_STAR_AUTH_FLAGS
#define CCM_STAR_AUTH_FLAGS(Adata, M) ((Adata ? (1u << 6) : 0) | (((M - 2u) >> 1) << 3) | 1u)
#endif

#ifndef CCM_STAR_ENCRYPTION_FLAGS
#define CCM_STAR_ENCRYPTION_FLAGS     1
#endif

#ifndef CCM_STAR_NONCE_LENGTH
#define CCM_STAR_NONCE_LENGTH 13
#endif

// ----------------------------------------------- CRYPTO DMA Enggine

#define VCDMAC_REG_BASE    0x40018000

struct VCDMAC_CR {
    union {
        struct {
            uint32_t csr_txeng_rstn : 1;
            uint32_t csr_rxeng_rstn : 1;
            uint32_t csr_txbuf_rstn : 1;
            uint32_t csr_rxbuf_rstn : 1;
        } fields;

        uint32_t value;
    };
};

struct VCDMAC_TM_CR {
    union {
        struct {
            uint32_t csr_dma_lb        : 1;
            uint32_t csr_buf_lb        : 1;
            uint32_t csr_rxstatus_drop : 1;
        } fields;

        uint32_t value;
    };
};

struct VCDMAC_TXE_CR {
    union {
        struct {
            uint32_t csr_txe_byteswap : 1;
            uint32_t csr_txe_chkfd    : 1;
        } fields;

        uint32_t value;
    };
};

struct VCDMAC_TXE_SR {
    union {
        struct {
            uint32_t csr_txe_desc_gap : 8;
        } fields;

        uint32_t value;
    };
};

struct VCDMAC_TXE_KR {
    union {
        struct {
            uint32_t csr_txe_kick : 1;
        } fields;

        uint32_t value;
    };
};

struct VCDMAC_TXE_BA_SR {
    union {
        struct {
            uint32_t csr_txbase_addr : 32;
        } fields;

        uint32_t value;
    };
};

struct VCDMAC_TXE_NA_SR {
    union {
        struct {
            uint32_t csr_txnext_addr : 32;
        } fields;

        uint32_t value;
    };
};

struct VCDMAC_TXE_CA_IR {
    union {
        struct {
            uint32_t csr_txcurr_addr : 32;
        } fields;

        uint32_t value;
    };
};

struct VCDMAC_TXE_REQ_IR {
    union {
        struct {
            uint32_t csr_txreq_addr : 32;
        } fields;

        uint32_t value;
    };
};

struct VCDMAC_RXE_CR {
    union {
        struct {
            uint32_t csr_rxe_byteswap : 1;
        } fields;

        uint32_t value;
    };
};

struct VCDMAC_RXE_SR {
    union {
        struct {
            uint32_t csr_rxe_desc_gap : 8;
        } fields;

        uint32_t value;
    };
};

struct VCDMAC_RXE_KR {
    union {
        struct {
            uint32_t csr_rxe_kick : 1;
        } fields;

        uint32_t value;
    };
};

struct VCDMAC_RXE_BA_SR {
    union {
        struct {
            uint32_t csr_rxbase_addr : 32;
        } fields;

        uint32_t value;
    };
};

struct VCDMAC_RXE_NA_SR {
    union {
        struct {
            uint32_t csr_rxnext_addr : 32;
        } fields;

        uint32_t value;
    };
};

struct VCDMAC_RXE_CA_IR {
    union {
        struct {
            uint32_t csr_rxcurr_address : 32;
        } fields;

        uint32_t value;
    };
};

struct VCDMAC_RXE_REQ_IR {
    union {
        struct {
            uint32_t csr_rxreq_addr : 32;
        } fields;

        uint32_t value;
    };
};

struct VCDMAC_RXE_SA_IR {
    union {
        struct {
            uint32_t csr_rxstart_addr : 32;
        } fields;

        uint32_t value;
    };
};

struct VCDMAC_IER {
    union {
        struct {
            uint32_t ier_txcmp     : 1;
            uint32_t ier_txunavail : 1;
            uint32_t ier_txerr     : 1;
            uint32_t ier_txupdate  : 1;
            uint32_t ier_reserved  : 4;
            uint32_t ier_rxcmp     : 1;
            uint32_t ier_rxunavail : 1;
            uint32_t ier_rxerr     : 1;
            uint32_t ier_rxupdate  : 1;
            uint32_t ier_rxreclaim : 1;
            uint32_t ier_msterr    : 1;
        } fields;

        uint32_t value;
    };
};

struct VCDMAC_ISR {
    union {
        struct {
            uint32_t isr_txcmp     : 1;
            uint32_t isr_txunavail : 1;
            uint32_t isr_txerr     : 1;
            uint32_t isr_txupdate  : 1;
            uint32_t isr_reserved  : 4;
            uint32_t isr_rxcmp     : 1;
            uint32_t isr_rxunavail : 1;
            uint32_t isr_rxerr     : 1;
            uint32_t isr_rxupdate  : 1;
            uint32_t isr_rxreclaim : 1;
            uint32_t isr_msterr    : 1;
        } fields;

        uint32_t value;
    };
};

struct VCDMAC_ISTR {
    union {
        struct {
            uint32_t istr_txcmp     : 1;
            uint32_t istr_txunavail : 1;
            uint32_t istr_txerr     : 1;
            uint32_t istr_txupdate  : 1;
            uint32_t reserved       : 4;
            uint32_t istr_rxcmp     : 1;
            uint32_t istr_rxunavail : 1;
            uint32_t istr_rxerr     : 1;
            uint32_t istr_rxupdate  : 1;
            uint32_t istr_rxreclaim : 1;
            uint32_t istr_msterr    : 1;
        } fields;

        uint32_t value;
    };
};

struct VCDMAC_REG_SPACE {
    struct VCDMAC_CR           CR;         // 0x00
    uint32_t reserved0;                    // 0x04
    uint32_t reserved1;                    // 0x08
    struct VCDMAC_TM_CR        TM_CR;      // 0x0c
    struct VCDMAC_TXE_CR       TXE_CR;     // 0x10
    struct VCDMAC_TXE_SR       TXE_SR;     // 0x14
    struct VCDMAC_TXE_KR       TXE_KR;     // 0x18
    struct VCDMAC_TXE_BA_SR    TXE_BA_SR;  // 0x1c
    struct VCDMAC_TXE_NA_SR    TXE_NA_SR;  // 0x20
    struct VCDMAC_TXE_CA_IR    TXE_CA_IR;  // 0x24
    struct VCDMAC_TXE_REQ_IR   TXE_REQ_IR; // 0x28
    uint32_t reserved2;                     // 0x2c
    struct VCDMAC_RXE_CR       RXE_CR;     // 0x30
    struct VCDMAC_RXE_SR       RXE_SR;     // 0x34
    struct VCDMAC_RXE_KR       RXE_KR;     // 0x38
    struct VCDMAC_RXE_BA_SR    RXE_BA_SR;  // 0x3c
    struct VCDMAC_RXE_NA_SR    RXE_NA_SR;  // 0x40
    struct VCDMAC_RXE_CA_IR    RXE_CA_IR;  // 0x44
    struct VCDMAC_RXE_REQ_IR   RXE_REQ_IR; // 0x48
    struct VCDMAC_RXE_SA_IR    RXE_SA_IR;  // 0x4c
    struct VCDMAC_IER          IER;        // 0x50
    struct VCDMAC_ISR          ISR;        // 0x54
    struct VCDMAC_ISTR         ISTR;       // 0x58
};

struct VCDMAC_DESC_CTRL {
    union {
        struct {
            uint32_t pkt_len        : 16;   // packet length
            uint32_t len_err        : 1;    // decriptor length error
            uint32_t reserved0      : 4;
            uint32_t FCS            : 1;    // FCS error
            uint32_t HCS            : 1;    // HCS error
            uint32_t MIC            : 1;    // MIC (Message Integration Code) error
            uint32_t reserved1      : 3;
            uint32_t last           : 1;    // last descriptor of the packet
            uint32_t first          : 1;    // first descriptor of the packet
            uint32_t int_en         : 1;    // interrupt enable for this descriptor
            uint32_t eor            : 1;    // end of ring
            uint32_t owner          : 1;
        } fields;

        uint32_t value;
    };
};

struct VCDMAC_PAYLOAD {
    void *dma_ptr;
    uint16_t dma_size;
};

#define VCDMAC_STRING_NR_DESC      2
#define VCDMAC_SSRING_NR_DESC      1
#define VCDMAC_TXRING_NR_DESC      6
#define VCDMAC_RXRING_NR_DESC      2

#define VCDMAC_RX_BUF_SIZE     1536
#define VCDMAC_TX_BUF_SIZE     1536

struct VCDMAC_PACKET {
    struct VCDMAC_PAYLOAD pld[VCDMAC_TXRING_NR_DESC];
    uint8_t nr_desc;
};

struct VCDMAC_RING_DESC {
    struct VCDMAC_DESC_CTRL ctrl;
    uint32_t ptr;
    uint32_t reserved0;
    uint32_t reserved1;
    struct VCDMAC_RING_DESC *prev;
    struct VCDMAC_RING_DESC *next;
    struct VCDMAC_RING_DESC *last;
    struct VCDMAC_PACKET *pkt;
};

#define VCDMAC_DESC_SPACING_SIZE   (sizeof(struct VCDMAC_RING_DESC) - 8)

enum VCDMAC_USR {
    VCDMAC_USR_KICKOFF_TX   = 0x08,
};

struct VCDMAC_RING {
    struct VCDMAC_RING_DESC *base;
    const char *name;

    struct VCDMAC_RING_DESC *refill_ptr;
    struct VCDMAC_RING_DESC *reclaim_ptr;

    uint32_t user_flag;

    volatile uint32_t *kickoff;
    volatile uint32_t *hw_ptr;

    uint32_t nr_entries;
};

struct VCDMAC_GLOBAL {
    struct VCDMAC_RING st_ring;        // security-tx crypt ring parameters
    struct VCDMAC_RING sr_ring;        // security-rx crypt ring parameters

    struct VCDMAC_RING t_ring;         // tx crypt ring parameters
    struct VCDMAC_RING r_ring;         // rx crypt ring parameters
};

enum VCDMAC_OWNER {
    VCDMAC_OWNER_SW     = 0,    // the desc entry if free to be used by the software
    VCDMAC_OWNER_DMAC   = 1,    // the desc entry is currently in used by the DMA engine
};

struct VCDMAC_GLOBAL_TRX {
    struct VCDMAC_ISR sec_ISR;

    uint8_t cur_tx_index;
    uint8_t cur_rx_index;

    uint32_t rx_data_ok;
    uint32_t rx_data_error;
    uint32_t rx_crc;
    uint32_t rx_len_error;
    uint32_t tx_ok;

    uint8_t sec_wait_rx_done;
    uint16_t sec_rx_len;
    uint8_t *sec_rx_ptr;

    uint8_t addr_default;
};

// ----------------------------------------------- CRYPTO Enggine

#define VCCRYPT_REG_BASE    0x40019000

struct VCCRYPT_CR {
    union {
        struct {
            uint32_t csr_aes_en : 1;
            uint32_t reserved0  : 3;
            uint32_t csr_sm2_en : 1;
            uint32_t csr_sm3_en : 1;
            uint32_t csr_sm4_en : 1;
            uint32_t reserved1  : 1;
            uint32_t csr_fcs_en : 1;
        } fields;

        uint32_t value;
    };
};

struct VCCRYPT_RST_CR {
    union {
        struct {
            uint32_t csr_crypto_rstn : 1;
        } fields;

        uint32_t value;
    };
};

struct VCCRYPT_SM2_CR {
    union {
        struct {
            uint32_t csr_sm2_act : 1;
        } fields;

        uint32_t value;
    };
};

struct VCCRYPT_SM2_SR1 {
    union {
        struct {
            uint32_t csr_sm2_mode   : 3;
            uint32_t reserved0      : 1;
            uint32_t csr_sm2_length : 4;
            uint32_t reserved1      : 8;
            uint32_t csr_sm2_ptr_a  : 13;
        } fields;

        uint32_t value;
    };
};

struct VCCRYPT_SM2_SR2 {
    union {
        struct {
            uint32_t csr_sm2_ptr_b : 13;
            uint32_t reserved0     : 3;
            uint32_t csr_sm2_ptr_o : 13;
            uint32_t reserved1     : 3;
        } fields;

        uint32_t value;
    };
};

struct VCCRYPT_SM2_IR {
    union {
        struct {
            uint32_t csr_sm2_done  : 1;
            uint32_t csr_sm2_carry : 1;
        } fields;

        uint32_t value;
    };
};

struct VCCRYPT_SRAM_CR1 {
    union {
        struct {
            uint32_t csr_cry_sram_addr : 13;
            uint32_t reserved0         : 3;
            uint32_t csr_cry_sram_web  : 1;
            uint32_t reserved1         : 7;
            uint32_t csr_cry_sram_req  : 1;
            uint32_t reserved2         : 7;
        } fields;

        uint32_t value;
    };
};

struct VCCRYPT_SRAM_CR2 {
    union {
        struct {
            uint32_t csr_cry_sram_wd : 32;
        } fields;

        uint32_t value;
    };
};

struct VCCRYPT_SRAM_RR1 {
    union {
        struct {
            uint32_t csr_cry_sram_done : 1;
        } fields;

        uint32_t value;
    };
};

struct VCCRYPT_SRAM_RR2 {
    union {
        struct {
            uint32_t csr_cry_sram_rd : 32;
        } fields;

        uint32_t value;
    };
};

struct VCCRYPT_CFG_ERR  {
    union {
        struct {
            uint32_t csr_sm3_cfgerr : 1;
            uint32_t csr_sm4_cfgerr : 1;
        } fields;

        uint32_t value;
    };
};

struct VCCRYPT_FCS_CFG {
    union {
        struct {
            uint32_t csr_fcs8_reginit0     : 1;
            uint32_t csr_fcs8_1com         : 1;
            uint32_t csr_fcs8_flpbyte_in   : 1;
            uint32_t csr_fcs8_flpbyte_out  : 1;
            uint32_t reserved0             : 4;
            uint32_t csr_fcs16_reginit0    : 1;
            uint32_t csr_fcs16_1com        : 1;
            uint32_t csr_fcs16_flpbyte_in  : 1;
            uint32_t csr_fcs16_flpbyte_out : 1;
            uint32_t reserved1             : 4;
            uint32_t csr_fcs24_reginit0    : 1;
            uint32_t csr_fcs24_1com        : 1;
            uint32_t csr_fcs24_flpbyte_in  : 1;
            uint32_t csr_fcs24_flpbyte_out : 1;
            uint32_t reserved2             : 4;
            uint32_t csr_fcs32_reginit0    : 1;
            uint32_t csr_fcs32_1com        : 1;
            uint32_t csr_fcs32_flpbyte_in  : 1;
            uint32_t csr_fcs32_flpbyte_out : 1;
        } fields;

        uint32_t value;
    };
};

struct VCCRYPT_REG_SPACE {
    struct VCCRYPT_CR           CR;             // 0x00
    struct VCCRYPT_RST_CR       RSTN;           // 0x04
    uint32_t                    reserved0;      // 0x08
    uint32_t                    reserved1;      // 0x0C
    struct VCCRYPT_SM2_CR       SM2_CR;         // 0x10
    struct VCCRYPT_SM2_SR1      SM2_SR1;        // 0x14
    struct VCCRYPT_SM2_SR2      SM2_SR2;        // 0x18
    struct VCCRYPT_SM2_IR       SM2_IR;         // 0x1C
    struct VCCRYPT_SRAM_CR1     SRAM_CR1;       // 0x20
    struct VCCRYPT_SRAM_CR2     SRAM_CR2;       // 0x24
    struct VCCRYPT_SRAM_RR1     SRAM_RR1;       // 0x28
    struct VCCRYPT_SRAM_RR2     SRAM_RR2;       // 0x2C
    struct VCCRYPT_CFG_ERR      CFG_ERR;        // 0x30
    struct VCCRYPT_FCS_CFG      FCS_CFG;        // 0x34
};

enum SEC_TYPE {
    VCSEC_TYPE_AES = 1,
    VCSEC_TYPE_SM  = 3,
    VCSEC_TYPE_CRC = 5,
};

enum SEC_AES_TYPE {
    VCSEC_MODE_ECB_128 = 1,
    VCSEC_MODE_CCM_128,
    VCSEC_MODE_CBC_128,
    VCSEC_MODE_ECB_192,
    VCSEC_MODE_CCM_192,
    VCSEC_MODE_CBC_192,
    VCSEC_MODE_ECB_256,
    VCSEC_MODE_CCM_256,
    VCSEC_MODE_CBC_256,
    VCSEC_MODE_MAX,
};

enum SEC_CRC_TYPE
{
    VCSEC_MODE_CRC_32 = 0,
    VCSEC_MODE_CRC_24 = 1,
    VCSEC_MODE_CRC_16 = 2,
    VCSEC_MODE_CRC_8  = 3,
};

enum SEC_AES_KEY_TYPE {
    AES_128 = 0,
    AES_192 = 1,
    AES_256 = 2,
};

enum SEC_SM_TYPE {
    VCSEC_MODE_SM3 = 1,
    VCSEC_MODE_SM4
};

struct VCSEC_CTRL {
    union {
        struct {
            uint32_t mode     : 4;
            uint32_t type     : 4;
            uint32_t head_len : 8;
            uint32_t config   : 8;
            uint32_t sequence : 8;
        } fields;

        uint32_t value;
    };
};

struct VCSEC_CTRL_HEADER_CBC {
    struct VCSEC_CTRL ctrl;
    uint8_t IV[16];
    uint8_t KEY[32];
};

struct VCSEC_CTRL_HEADER_ECB {
    struct VCSEC_CTRL ctrl;
    uint8_t KEY[32];
};

struct VCSEC_CTRL_HEADER_CCM {
    struct VCSEC_CTRL ctrl;
    uint32_t auth_len : 16;
    uint32_t ciper_len : 16;
    uint8_t  B0[16];
    uint8_t  A0[16];
    uint8_t  KEY[32];
};

struct VCSEC_CTRL_HEADER_CRC
{
    struct VCSEC_CTRL ctrl;
};

// global declarations
struct VCDMAC_GLOBAL vcdmac_global;
struct VCDMAC_GLOBAL_TRX vcdmac_trx_global;

struct VCDMAC_RING_DESC tx_desc[VCDMAC_TXRING_NR_DESC];
struct VCDMAC_RING_DESC rx_desc[VCDMAC_RXRING_NR_DESC];
uint8_t                 rx_buf[VCDMAC_RXRING_NR_DESC][VCDMAC_RX_BUF_SIZE];

static void vcdmac_ring_init(uint8_t mode,
                             struct VCDMAC_RING *ring,
                             bool tx,
                             uint32_t nr_entries,
                             uint32_t *reg_kickoff,
                             uint32_t *reg_hw_ptr)
{
    struct VCDMAC_RING_DESC *desc, *desc_last, *desc_prev;

    int i = 0;

    ring->nr_entries = nr_entries;

    if (mode == SEC_MODE)
    {
        ring->base = tx ? tx_desc : rx_desc;
    }

    ring->kickoff = (volatile uint32_t *)reg_kickoff;
    ring->hw_ptr = (volatile uint32_t *)reg_hw_ptr;
    ring->refill_ptr = (struct VCDMAC_RING_DESC *)ring->base;
    ring->reclaim_ptr = (struct VCDMAC_RING_DESC *)ring->base;

    ring->user_flag = 0;

    // initialize dma-ring decriptors ... (generic initialization)
    desc = (struct VCDMAC_RING_DESC *)ring->base;
    desc_last = &desc[ring->nr_entries - 1];
    desc_prev = desc_last;

    while (desc <= desc_last)
    {
        desc->ctrl.value = 0;
        desc->ptr = 0;

        desc->ctrl.fields.int_en = 1;
        desc->ctrl.fields.owner = VCDMAC_OWNER_SW;

        if (!tx)
        {
            desc->ctrl.fields.owner = VCDMAC_OWNER_DMAC;
            desc->ctrl.fields.pkt_len = VCDMAC_RX_BUF_SIZE;

            if (mode == SEC_MODE)
            {
                desc->ptr = (uint32_t)&rx_buf[i++][0];
            }
        }

        desc->pkt = NULL;
        desc->last = NULL;

        desc->prev = desc_prev;
        desc_prev = desc++;
        desc_prev->next = desc;
    }

    // finalize dma-ring ... (last descriptor entry)
    desc_last->ctrl.fields.eor = 1;
    desc_last->next = (struct VCDMAC_RING_DESC *)ring->base;
}

int vccrypt_init(bool loopback)
{
    // setup DMAC
    volatile struct VCDMAC_REG_SPACE *reg_space = (volatile struct VCDMAC_REG_SPACE *)VCDMAC_REG_BASE;
    uint32_t reg;

    reg = 0x303;
    reg_space->CR.value = reg;


	  memset(&vcdmac_global, 0x0, sizeof(struct VCDMAC_GLOBAL));
	  memset(&vcdmac_trx_global, 0x0, sizeof(struct VCDMAC_GLOBAL_TRX));
    vcdmac_ring_init(SEC_MODE,
                     &vcdmac_global.t_ring,
                     true,
                     VCDMAC_TXRING_NR_DESC,
                     (uint32_t *)&reg_space->TXE_KR,
                     (uint32_t *)&reg_space->TXE_CA_IR);

    vcdmac_ring_init(SEC_MODE,
                     &vcdmac_global.r_ring,
                     false,
                     VCDMAC_RXRING_NR_DESC,
                     (uint32_t *)&reg_space->RXE_KR,
                     (uint32_t *)&reg_space->RXE_CA_IR);

    vcdmac_global.st_ring.name = "sec_tx";
    vcdmac_global.sr_ring.name = "sec_rx";

    vcdmac_global.t_ring.user_flag = VCDMAC_USR_KICKOFF_TX;
    vcdmac_global.t_ring.name = "ppc_tx";
    vcdmac_global.r_ring.name = "ppc_rx";

    reg_space->TXE_BA_SR.value = (uint32_t)vcdmac_global.t_ring.base;
    reg_space->RXE_BA_SR.value = (uint32_t)vcdmac_global.r_ring.base;

    // setup dmac control register

    // TM CR
    reg = 0;
    ((struct VCDMAC_TM_CR *)&reg)->fields.csr_dma_lb = 0;           // dma loopback
    ((struct VCDMAC_TM_CR *)&reg)->fields.csr_buf_lb = loopback;    // dma loopback thru buffer
    ((struct VCDMAC_TM_CR *)&reg)->fields.csr_rxstatus_drop = 0;

    reg_space->TM_CR.value = reg;

    // TX Enable
    reg = 0;
    ((struct VCDMAC_TXE_CR *)&reg)->fields.csr_txe_byteswap = 1;
    ((struct VCDMAC_TXE_CR *)&reg)->fields.csr_txe_chkfd = 1;

    reg_space->TXE_CR.value = reg;
    reg_space->RXE_CR.value = reg;

    reg = 0;
    ((struct VCDMAC_TXE_SR *)&reg)->fields.csr_txe_desc_gap = VCDMAC_DESC_SPACING_SIZE;

    reg_space->TXE_SR.value = reg;
    reg_space->RXE_SR.value = reg;

    // ISR
    reg = 0;

    ((struct VCDMAC_IER *)&reg)->fields.ier_txcmp = 1;
    ((struct VCDMAC_IER *)&reg)->fields.ier_txunavail = 1;
    ((struct VCDMAC_IER *)&reg)->fields.ier_txerr = 1;
    ((struct VCDMAC_IER *)&reg)->fields.ier_txupdate = 1;
    ((struct VCDMAC_IER *)&reg)->fields.ier_rxcmp = 1;
    ((struct VCDMAC_IER *)&reg)->fields.ier_rxunavail = 1;
    ((struct VCDMAC_IER *)&reg)->fields.ier_rxerr = 1;
    ((struct VCDMAC_IER *)&reg)->fields.ier_rxupdate = 1;
    ((struct VCDMAC_IER *)&reg)->fields.ier_rxreclaim = 1;
    ((struct VCDMAC_IER *)&reg)->fields.ier_msterr = 1;

    reg_space->ISR.value = 0xffffffff;

    reg_space->IER.value = reg;

    // kickoff rx dma
    *vcdmac_global.r_ring.kickoff = 1;

    return 0;
}

static void vcdmac_do_rx_data(void)
{
    struct VCDMAC_RING_DESC *cur_desc;
    uint8_t *rx_index;

    {
        rx_index = &vcdmac_trx_global.cur_rx_index;
        cur_desc = &rx_desc[vcdmac_trx_global.cur_rx_index];
    }

    if (cur_desc->ctrl.fields.owner == VCDMAC_OWNER_DMAC)
    {
        soc_printf("RX DESC ERROR %lx\n", cur_desc->ctrl.value);
        return;
    }

    do {
        soc_printf("rx_len=%d\n", cur_desc->ctrl.fields.pkt_len);

        if (cur_desc->ctrl.fields.len_err)
        {
            vcdmac_trx_global.rx_len_error++;
            soc_printf("RX DESC len ERROR %lx\n", cur_desc->ctrl.value);
        }
        else
        {
            if (cur_desc->ctrl.fields.FCS || cur_desc->ctrl.fields.MIC || cur_desc->ctrl.fields.HCS)
            {
                soc_printf("FCS ERROR %lx\n", cur_desc->ctrl.value);
            }

            if (vcdmac_trx_global.sec_wait_rx_done == 0)
            {
                vcdmac_trx_global.sec_wait_rx_done = 1;

                vcdmac_trx_global.sec_rx_len = cur_desc->ctrl.fields.pkt_len - 4;
                vcdmac_trx_global.sec_rx_ptr = (uint8_t *)cur_desc->ptr;
            }
        }

        cur_desc->ctrl.fields.owner = VCDMAC_OWNER_DMAC;
        cur_desc->ctrl.fields.first = 0;
        cur_desc->ctrl.fields.last = 0;
        cur_desc->ctrl.fields.pkt_len = VCDMAC_RX_BUF_SIZE;

        *rx_index = (*rx_index + 1) % VCDMAC_RXRING_NR_DESC;

        {
            cur_desc = &rx_desc[vcdmac_trx_global.cur_rx_index];
        }

    } while (cur_desc->ctrl.fields.owner == VCDMAC_OWNER_SW);
}

int vcdmac_pkt_payload_attach(struct VCDMAC_PACKET *pkt, void *data_ptr, uint32_t data_size)
{
	  pkt->pld[pkt->nr_desc].dma_ptr = data_ptr;
	  pkt->pld[pkt->nr_desc].dma_size = data_size;
	  pkt->nr_desc++;

    return 0;
}

void vcdmac_pkt_payload_reset(struct VCDMAC_PACKET *pkt)
{
	memset(pkt, 0x0, sizeof(struct VCDMAC_PACKET));
	pkt->nr_desc=0;
}

void vcdmac_pkt_submit(uint8_t mode, struct VCDMAC_PACKET *pkt)
{
    struct VCDMAC_RING_DESC *desc_h = NULL;
    struct VCDMAC_RING_DESC *desc_e = NULL;
    struct VCDMAC_RING_DESC *desc = NULL;
    int cout=100;

    struct VCDMAC_PAYLOAD *pld = pkt->pld;

    uint32_t nr_desc = pkt->nr_desc;

    uint8_t need_int_en = true;
    uint8_t index = 0;
    uint8_t cur_tx_index = 0;

    
    if(mode == SEC_MODE)
    {
        cur_tx_index = vcdmac_trx_global.cur_tx_index;
    }
        
    nr_desc = (cur_tx_index + pkt->nr_desc - 1) % VCDMAC_TXRING_NR_DESC;

    if(mode == SEC_MODE)
    {
        desc_h = &tx_desc[cur_tx_index];
        desc_e = &tx_desc[nr_desc]; 
    }
    
    while(desc_e->ctrl.fields.owner != VCDMAC_OWNER_SW)
    {
        if(cout-- ==0) return;
    }
    
    do {
        
        pld = &pkt->pld[index++];

        if(mode == SEC_MODE)
        {
            desc=&tx_desc[cur_tx_index];
        }
        
        if (desc->ctrl.fields.owner != VCDMAC_OWNER_SW)
        {
            soc_printf("tx ring full\n");
        }

        memset(desc, 0x0, sizeof(struct VCDMAC_DESC_CTRL)+4);
        
        desc->ptr = (uint32_t)pld->dma_ptr;
        desc->ctrl.fields.pkt_len = pld->dma_size;

        if((cur_tx_index + 1) == VCDMAC_TXRING_NR_DESC) desc->ctrl.fields.eor = 1;

        desc->ctrl.fields.owner = VCDMAC_OWNER_DMAC;
        
        cur_tx_index = (cur_tx_index + 1) % VCDMAC_TXRING_NR_DESC;
    } while (--pkt->nr_desc);


    if(mode == SEC_MODE)
    {
        vcdmac_trx_global.cur_tx_index = cur_tx_index;
    }

    desc_h->ctrl.fields.first = 1;
    desc_e->ctrl.fields.last = 1;

    if (need_int_en) 
    {
        desc_e->ctrl.fields.int_en = 1;
    }
    else
    {
        desc_e->ctrl.fields.int_en = 0;
    }
}

static void set_iv(uint8_t *iv, uint8_t flags, const uint8_t *nonce, uint16_t counter)
{
    iv[0] = flags;
    memcpy(iv + 1, nonce, CCM_STAR_NONCE_LENGTH);
    iv[14] = counter >> 8; 
    iv[15] = counter & 0xff;
}

static void cbc_encrypt(uint8_t mode, uint8_t *key, uint8_t key_len,
                        uint8_t *a, uint16_t a_len,
                        uint8_t *B0, uint8_t *A0,
                        uint8_t *result, uint8_t mic_len)
{
    volatile struct VCCRYPT_REG_SPACE *crypt_reg = (volatile struct VCCRYPT_REG_SPACE *)VCCRYPT_REG_BASE;
    volatile struct VCDMAC_REG_SPACE *dma_reg = (volatile struct VCDMAC_REG_SPACE *)VCDMAC_REG_BASE;

    struct VCDMAC_PACKET pkt;
    struct VCSEC_CTRL_HEADER_CBC cbc_head;

    uint8_t cbc_ctrl_len = 0;

    switch (mode) {
    case VCSEC_MODE_CBC_128:
        cbc_ctrl_len = ((sizeof(struct VCSEC_CTRL_HEADER_CBC))-16);
        break;
    case VCSEC_MODE_CBC_192:
        cbc_ctrl_len = ((sizeof(struct VCSEC_CTRL_HEADER_CBC))-8);
        break;
    case VCSEC_MODE_CBC_256:
        cbc_ctrl_len = sizeof(struct VCSEC_CTRL_HEADER_CBC);
        break;
    default:
        cbc_ctrl_len = ((sizeof(struct VCSEC_CTRL_HEADER_CBC))-16);
        break;
    }

    uint8_t iv[VC_CRYPT_MAX_IV_LENGTH];
    uint8_t T[8];
    uint8_t S0[8];

    uint8_t a_add[2];
    uint8_t a_pad_len;
    uint8_t a_pad[16];
    uint32_t isr_value;

    // Note: additional 2 byte of header
    a_add[0] = a_len >> 8;
    a_add[1] = a_len & 0xff;

    memset(a_pad, 0, sizeof(a_pad));

    // Note: pad-length to make the header become multiple of 16
    a_pad_len = (((a_len + sizeof(a_add)) % 16) != 0) ? 16 - ((a_len + sizeof(a_add)) % 16) : 0;

    crypt_reg->RSTN.value = 1; // CSR_CRYPTO_RSTN
    crypt_reg->CR.value = 1;   // CSR_AES_EN

    memset(iv, 0x0, sizeof(iv));
    memset(T, 0x0, sizeof(T));
    memset(S0, 0x0, sizeof(S0));

    memset(&cbc_head, 0x0, cbc_ctrl_len);
    cbc_head.ctrl.fields.type = VCSEC_TYPE_AES;
    cbc_head.ctrl.fields.mode = mode;
    cbc_head.ctrl.fields.head_len = cbc_ctrl_len;

    memcpy(cbc_head.IV, iv, VC_CRYPT_MAX_IV_LENGTH);
    memcpy(cbc_head.KEY, key, key_len);

    cbc_head.ctrl.fields.config = 0x3;

    vcdmac_pkt_payload_reset(&pkt);
    vcdmac_pkt_payload_attach(&pkt, &cbc_head, cbc_ctrl_len);
    vcdmac_pkt_payload_attach(&pkt, B0, VC_CRYPT_MAX_BLOCK_LENGTH);
    vcdmac_pkt_payload_attach(&pkt, a_add, sizeof(a_add));
    vcdmac_pkt_payload_attach(&pkt, a, a_len);
    if (a_pad_len != 0) vcdmac_pkt_payload_attach(&pkt, a_pad, a_pad_len);

    vcdmac_pkt_submit(SEC_MODE, &pkt);

    vcdmac_trx_global.sec_wait_rx_done = 0;
    *vcdmac_global.t_ring.kickoff = 1;

    while (!dma_reg->ISR.fields.isr_rxcmp);

    isr_value = dma_reg->ISR.value;
    dma_reg->ISR.value = isr_value;

    vcdmac_do_rx_data();

    if (!vcdmac_trx_global.sec_wait_rx_done) {
        goto exit;
    }

    memcpy(T, vcdmac_trx_global.sec_rx_ptr + 4 + sizeof(a_add) + a_len + a_pad_len, sizeof(T));

    vcdmac_pkt_payload_reset(&pkt);
    vcdmac_pkt_payload_attach(&pkt, &cbc_head, cbc_ctrl_len);
    vcdmac_pkt_payload_attach(&pkt, A0, VC_CRYPT_MAX_BLOCK_LENGTH);

    vcdmac_pkt_submit(SEC_MODE, &pkt);

    vcdmac_trx_global.sec_wait_rx_done = 0;
    *vcdmac_global.t_ring.kickoff = 1;

    while (!dma_reg->ISR.fields.isr_rxcmp);

    isr_value = dma_reg->ISR.value;
    dma_reg->ISR.value = isr_value;

    vcdmac_do_rx_data();

    if (vcdmac_trx_global.sec_wait_rx_done) {
        memcpy(S0, vcdmac_trx_global.sec_rx_ptr + 4, sizeof(S0));
        // result (mic): XOR T and S0
        if (mic_len == sizeof(T)) {
            for (uint8_t i = 0; i < mic_len; i++) {
                result[i] = T[i] ^ S0[i];
            }
        }
    }

exit:
    return;
}

#define VCSWAP(n) (uint16_t)((((uint16_t) (n)) << 8) | (((uint16_t) (n)) >> 8))

static void ccm_encrypt(uint8_t forward, uint8_t mode,
                        uint8_t *key, uint8_t key_len,
                        uint8_t *m /* input */, uint16_t m_len,
                        uint8_t *a /* additional */, uint16_t a_len,
                        uint8_t *B0, uint8_t *A0,
                        uint8_t *result, uint8_t mic_len,
                        uint8_t *output)
{
    volatile struct VCCRYPT_REG_SPACE *crypt_reg = (volatile struct VCCRYPT_REG_SPACE *)VCCRYPT_REG_BASE;
    volatile struct VCDMAC_REG_SPACE *dma_reg = (volatile struct VCDMAC_REG_SPACE *)VCDMAC_REG_BASE;

    struct VCDMAC_PACKET pkt;
    struct VCSEC_CTRL_HEADER_CCM ccm_head;

    uint8_t ccm_ctrl_len = 0;

    switch (mode) {
    case VCSEC_MODE_CCM_128:
        ccm_ctrl_len = ((sizeof(struct VCSEC_CTRL_HEADER_CCM))-16);
        break;
    case VCSEC_MODE_CCM_192:
        ccm_ctrl_len = ((sizeof(struct VCSEC_CTRL_HEADER_CCM))-8);
        break;
    case VCSEC_MODE_CCM_256:
        ccm_ctrl_len = sizeof(struct VCSEC_CTRL_HEADER_CCM);
        break;
    default:
        ccm_ctrl_len = ((sizeof(struct VCSEC_CTRL_HEADER_CCM))-16);
        break;
    }

    uint8_t a_add[2];
    uint8_t a_pad_len;
    uint8_t a_pad[16];
    uint32_t isr_value;

    // Note: additional 2 byte of header
    a_add[0] = a_len >> 8;
    a_add[1] = a_len & 0xff;

    memset(a_pad, 0, sizeof(a_pad));

    // Note: pad-length to make the header become multiple of 16
    a_pad_len = (((a_len + sizeof(a_add)) % 16) != 0) ? 16 - ((a_len + sizeof(a_add)) % 16) : 0;

    crypt_reg->RSTN.value = 1; // CSR_CRYPTO_RSTN
    crypt_reg->CR.value = 1;   // CSR_AES_EN

    ccm_head.ctrl.fields.type = VCSEC_TYPE_AES;
    ccm_head.ctrl.fields.mode = mode;
    ccm_head.ctrl.fields.head_len = ccm_ctrl_len;

    memcpy(ccm_head.KEY, key, key_len);
    memcpy(ccm_head.B0, B0, VC_CRYPT_MAX_BLOCK_LENGTH);
    memcpy(ccm_head.A0, A0, VC_CRYPT_MAX_BLOCK_LENGTH);

    ccm_head.ctrl.fields.config = (forward == VC_OPERATION_ENCRYPT) ? 0x3 : 0x2;

    ccm_head.ciper_len = VCSWAP(m_len);
    ccm_head.auth_len = VCSWAP(sizeof(a_add) + a_len + a_pad_len);

    vcdmac_pkt_payload_reset(&pkt);
    vcdmac_pkt_payload_attach(&pkt, &ccm_head, ccm_head.ctrl.fields.head_len);
    vcdmac_pkt_payload_attach(&pkt, a_add, sizeof(a_add));
    vcdmac_pkt_payload_attach(&pkt, a, a_len);
    if (a_pad_len != 0) vcdmac_pkt_payload_attach(&pkt, a_pad, a_pad_len);
    vcdmac_pkt_payload_attach(&pkt, m, m_len);
    vcdmac_pkt_submit(SEC_MODE, &pkt);

    vcdmac_trx_global.sec_wait_rx_done = 0;
    *vcdmac_global.t_ring.kickoff = 1;

    while (!dma_reg->ISR.fields.isr_rxcmp);

    isr_value = dma_reg->ISR.value;
    dma_reg->ISR.value = isr_value;

    vcdmac_do_rx_data();

    if (vcdmac_trx_global.sec_wait_rx_done) {
        memcpy(result, vcdmac_trx_global.sec_rx_ptr + 4 + m_len, mic_len); // mic
        memcpy(output == NULL ? m : output, vcdmac_trx_global.sec_rx_ptr + 4, m_len);
    }
}

extern int vcradio_lock_irq(void);
extern void vcradio_unlock_irq(int);

void vccrypt_aes_ccm_encrypt(uint8_t forward, uint8_t *key, uint8_t *nonce,
                             uint8_t *m, uint16_t m_len,
                             uint8_t *a, uint16_t a_len,
                             uint8_t *result, uint8_t mic_len)
{
    int rs = vcradio_lock_irq();

    uint8_t B0[VC_CRYPT_MAX_BLOCK_LENGTH];
    uint8_t A0[VC_CRYPT_MAX_BLOCK_LENGTH];

    set_iv(B0, CCM_STAR_AUTH_FLAGS(a_len, mic_len), nonce, m_len);
    set_iv(A0, CCM_STAR_ENCRYPTION_FLAGS, nonce, 0);

    if (m_len != 0) {
        ccm_encrypt(forward,VCSEC_MODE_CCM_128,key, AES_128_KEY_SIZE, m, m_len, a, a_len, B0, A0, result, mic_len, NULL);
        goto exit;
    }

    // payload == 0 and only support encryption to generate MIC
    if ((m_len == 0 && forward == VC_OPERATION_ENCRYPT) || (m_len == 0 && forward == VC_CCM_STAR_DECRYPT)) {
        cbc_encrypt(VCSEC_MODE_CBC_128, key, AES_128_KEY_SIZE, a, a_len, B0, A0, result, mic_len);
    }

exit:
    vcradio_unlock_irq(rs);
    return;
}

void vccrypt_aes_ecb_encrypt(uint8_t forward,uint8_t mode, uint8_t *key,
                             uint8_t *data, uint16_t data_len,uint8_t *result)
{
	  volatile struct VCCRYPT_REG_SPACE *crypt_reg = (volatile struct VCCRYPT_REG_SPACE *)VCCRYPT_REG_BASE;
	  volatile struct VCDMAC_REG_SPACE *dma_reg = (volatile struct VCDMAC_REG_SPACE *)VCDMAC_REG_BASE;

	  struct VCDMAC_PACKET pkt;
    struct VCSEC_CTRL_HEADER_ECB ecb_head;

    uint32_t isr_value;

    crypt_reg->RSTN.value = 1; // CSR_CRYPTO_RSTN
    crypt_reg->CR.value = 1;   // CSR_AES_EN
    ecb_head.ctrl.fields.type = VCSEC_TYPE_AES;

    switch (mode)
    {
        case VCSEC_MODE_ECB_128:
            ecb_head.ctrl.fields.mode = VCSEC_MODE_ECB_128;
            ecb_head.ctrl.fields.head_len = ((sizeof(struct VCSEC_CTRL_HEADER_ECB))-16);
            memcpy(ecb_head.KEY, key, AES_128_KEY_SIZE);
            break;

        case VCSEC_MODE_ECB_192:
            ecb_head.ctrl.fields.mode = VCSEC_MODE_ECB_192;
            ecb_head.ctrl.fields.head_len = ((sizeof(struct VCSEC_CTRL_HEADER_ECB))-8);
            memcpy(ecb_head.KEY, key, AES_192_KEY_SIZE);
			break;

        case VCSEC_MODE_ECB_256:
            ecb_head.ctrl.fields.mode = VCSEC_MODE_ECB_256;
            ecb_head.ctrl.fields.head_len = sizeof(struct VCSEC_CTRL_HEADER_ECB);
            memcpy(ecb_head.KEY, key, AES_256_KEY_SIZE);
            break;

        default:
            ecb_head.ctrl.fields.mode = VCSEC_MODE_ECB_128;
            ecb_head.ctrl.fields.head_len = ((sizeof(struct VCSEC_CTRL_HEADER_ECB))-16);
            memcpy(ecb_head.KEY, key, AES_128_KEY_SIZE);
            break;
    }

    ecb_head.ctrl.fields.config = (forward == VC_OPERATION_ENCRYPT) ? 0x3 : 0x2;
    
    vcdmac_pkt_payload_reset(&pkt);
    vcdmac_pkt_payload_attach(&pkt, &ecb_head, ecb_head.ctrl.fields.head_len);
    vcdmac_pkt_payload_attach(&pkt, data, data_len);
    vcdmac_pkt_submit(SEC_MODE, &pkt);

    vcdmac_trx_global.sec_wait_rx_done = 0;
    *vcdmac_global.t_ring.kickoff = 1;
	
  	while (!dma_reg->ISR.fields.isr_rxcmp);

    // Clear ISR flag write 1 to clean
	  isr_value = dma_reg->ISR.value;
	  dma_reg->ISR.value = isr_value;

	  vcdmac_do_rx_data();

    if (vcdmac_trx_global.sec_wait_rx_done) {
        memcpy(result, vcdmac_trx_global.sec_rx_ptr + 4, data_len);
    }
}

void vccrypt_aes_cbc_encrypt(uint8_t forward,uint8_t mode, uint8_t *key, uint8_t *iv, uint16_t iv_len,
							uint8_t *data, uint16_t data_len,uint8_t *result)
{
	  volatile struct VCCRYPT_REG_SPACE *crypt_reg = (volatile struct VCCRYPT_REG_SPACE *)VCCRYPT_REG_BASE;
	  volatile struct VCDMAC_REG_SPACE *dma_reg = (volatile struct VCDMAC_REG_SPACE *)VCDMAC_REG_BASE;

	  struct VCDMAC_PACKET pkt;
    struct VCSEC_CTRL_HEADER_CBC cbc_head;

    uint32_t isr_value;

    crypt_reg->RSTN.value = 1; 	// CSR_CRYPTO_RSTN
    crypt_reg->CR.value = 1;   	// CSR_AES_EN

    switch (mode)
    {
        case VCSEC_MODE_CBC_128:
		        cbc_head.ctrl.fields.type = VCSEC_TYPE_AES;
            cbc_head.ctrl.fields.mode = VCSEC_MODE_CBC_128;
            cbc_head.ctrl.fields.head_len = ((sizeof(struct VCSEC_CTRL_HEADER_CBC))-16);
            memcpy(cbc_head.KEY, key, AES_128_KEY_SIZE);
			      memcpy(cbc_head.IV, iv, iv_len);
            break;

        case VCSEC_MODE_CBC_192:
		        cbc_head.ctrl.fields.type = VCSEC_TYPE_AES;
            cbc_head.ctrl.fields.mode = VCSEC_MODE_CBC_192;
            cbc_head.ctrl.fields.head_len = ((sizeof(struct VCSEC_CTRL_HEADER_CBC))-8);
            memcpy(cbc_head.KEY, key, AES_192_KEY_SIZE);
			      memcpy(cbc_head.IV, iv, iv_len);
			      break;

        case VCSEC_MODE_CBC_256:
			      cbc_head.ctrl.fields.type = VCSEC_TYPE_AES;
            cbc_head.ctrl.fields.mode = VCSEC_MODE_CBC_256;
            cbc_head.ctrl.fields.head_len = sizeof(struct VCSEC_CTRL_HEADER_CBC);
            memcpy(cbc_head.KEY, key, AES_256_KEY_SIZE);
			      memcpy(cbc_head.IV, iv, iv_len);
            break;

        default:
		        cbc_head.ctrl.fields.type = VCSEC_TYPE_AES;
            cbc_head.ctrl.fields.mode = VCSEC_MODE_CBC_128;
            cbc_head.ctrl.fields.head_len = ((sizeof(struct VCSEC_CTRL_HEADER_CBC))-16);
            memcpy(cbc_head.KEY, key, AES_128_KEY_SIZE);
			      memcpy(cbc_head.IV, iv, iv_len);
            break;
    }

		cbc_head.ctrl.fields.config = (forward == VC_OPERATION_ENCRYPT) ? 0x3 : 0x2;

    vcdmac_pkt_payload_reset(&pkt);

    vcdmac_pkt_payload_attach(&pkt, &cbc_head, cbc_head.ctrl.fields.head_len);
    vcdmac_pkt_payload_attach(&pkt, data, data_len);
    vcdmac_pkt_submit(SEC_MODE, &pkt);

    vcdmac_trx_global.sec_wait_rx_done = 0;
    *vcdmac_global.t_ring.kickoff = 1;

	  while (!dma_reg->ISR.fields.isr_rxcmp);

    // Clear ISR flag write 1 to clean
	  isr_value = dma_reg->ISR.value;
	  dma_reg->ISR.value = isr_value;

	  vcdmac_do_rx_data();

    if (vcdmac_trx_global.sec_wait_rx_done) {
        memcpy(result, vcdmac_trx_global.sec_rx_ptr + 4, data_len);
    }	
}
void vccrypt_crc_encrypt(uint8_t mode,uint8_t *data, uint16_t data_len,uint8_t *result)
{
	  volatile struct VCCRYPT_REG_SPACE *crypt_reg = (volatile struct VCCRYPT_REG_SPACE *)VCCRYPT_REG_BASE;
	  volatile struct VCDMAC_REG_SPACE *dma_reg = (volatile struct VCDMAC_REG_SPACE *)VCDMAC_REG_BASE;

	  struct VCDMAC_PACKET pkt;
    struct VCSEC_CTRL_HEADER_CRC crc_head;

    uint32_t isr_value;

    crypt_reg->RSTN.value = 1; 	// CSR_CRYPTO_RSTN
    crypt_reg->CR.value = 0x100; // CSR_CRC_EN
    crc_head.ctrl.fields.type = VCSEC_TYPE_CRC;

    switch (mode)
    {
        case VCSEC_MODE_CRC_8:
            crc_head.ctrl.fields.mode = VCSEC_MODE_CRC_8;
            crc_head.ctrl.fields.head_len = (sizeof(struct VCSEC_CTRL_HEADER_CRC));
            break;

        case VCSEC_MODE_CRC_16:
            crc_head.ctrl.fields.mode = VCSEC_MODE_CRC_16;
            crc_head.ctrl.fields.head_len = (sizeof(struct VCSEC_CTRL_HEADER_CRC));
			      break;

        case VCSEC_MODE_CRC_24:
            crc_head.ctrl.fields.mode = VCSEC_MODE_CRC_24;
            crc_head.ctrl.fields.head_len = (sizeof(struct VCSEC_CTRL_HEADER_CRC));
            break;

		    case VCSEC_MODE_CRC_32:
			      crc_head.ctrl.fields.mode	= VCSEC_MODE_CRC_32;
			      crc_head.ctrl.fields.head_len = (sizeof(struct VCSEC_CTRL_HEADER_CRC));
			      break;

        default:
            crc_head.ctrl.fields.mode = VCSEC_MODE_CRC_32;
            crc_head.ctrl.fields.head_len = (sizeof(struct VCSEC_CTRL_HEADER_CRC));
            break;
    }
  
    vcdmac_pkt_payload_reset(&pkt);
    vcdmac_pkt_payload_attach(&pkt, &crc_head, crc_head.ctrl.fields.head_len);
    vcdmac_pkt_payload_attach(&pkt, data, data_len);
    vcdmac_pkt_submit(SEC_MODE, &pkt);

    vcdmac_trx_global.sec_wait_rx_done = 0;
    *vcdmac_global.t_ring.kickoff = 1;

	  while (!dma_reg->ISR.fields.isr_rxcmp);

    // Clear ISR flag write 1 to clean
	  isr_value = dma_reg->ISR.value;
	  dma_reg->ISR.value = isr_value;

	  vcdmac_do_rx_data();

    if (vcdmac_trx_global.sec_wait_rx_done) {
        memcpy(result, vcdmac_trx_global.sec_rx_ptr + 4, data_len);
    }
}

// -------------------------------- new vccrypt api implementation --------------------------------

static int vccrypt_ccm_starts(vc_ccm_context *ctx, size_t length,
                              vc_ccm_mode_t ccm_mode,
                              const unsigned char *iv, size_t iv_len,
                              size_t add_len, size_t tag_len)
{
    /* Also implies q is within bounds */
    if (iv_len < 7 || iv_len > 13)
        return VC_ERR_CCM_BAD_INPUT;

    if ((ccm_mode == VC_CCM_STAR_DECRYPT || ccm_mode == VC_CCM_STAR_ENCRYPT) && iv_len != 13)
        return VC_ERR_CCM_BAD_INPUT;

    unsigned char q = 16 - 1 - (unsigned char) iv_len;

    /*
     * Prepare counter block for encryption:
     * 0        .. 0        flags
     * 1        .. iv_len   nonce (aka iv)
     * iv_len+1 .. 15       counter
     *
     * With flags as (bits):
     * 7 .. 3   0
     * 2 .. 0   q - 1
     */
    memset(ctx->A0, 0, 16);
    ctx->A0[0] = q - 1;
    memcpy(ctx->A0 + 1, iv, iv_len);
    memset(ctx->A0 + 1 + iv_len, 0, q);
    ctx->A0[15] = 0;

    /*
     * First block:
     * 0        .. 0        flags
     * 1        .. iv_len   nonce (aka iv)
     * iv_len+1 .. 15       length
     *
     * With flags as (bits):
     * 7        0
     * 6        add present?
     * 5 .. 3   (t - 2) / 2
     * 2 .. 0   q - 1
     */
    memset(ctx->B0, 0, 16);
    memcpy(ctx->B0 + 1, iv, iv_len);
    ctx->B0[0] |= (add_len > 0) << 6;
    ctx->B0[0] |= ((tag_len - 2) / 2) << 3;
    ctx->B0[0] |= q - 1;
    ctx->B0[14] = length >> 8;
    ctx->B0[15] = length & 0xff;

    return 0;
}

static int ccm_auth_crypt(vc_ccm_context *ctx, vc_ccm_mode_t ccm_mode, size_t length,
                          const unsigned char *iv, size_t iv_len,
                          const unsigned char *add, size_t add_len,
                          const unsigned char *input, unsigned char *output,
                          unsigned char *tag, size_t tag_len)
{
    int ret = 0;

    if (iv == NULL || iv_len == 0)
        return VC_ERR_CCM_BAD_INPUT;

    if ((ret = vccrypt_ccm_starts(ctx, length, ccm_mode, iv, iv_len, add_len, tag_len)) != 0)
        return ret;

    if (length != 0) {
        switch (ctx->cipher_ctx.mode) {
        case VC_MODE_CCM:
            ccm_encrypt(ctx->cipher_ctx.operation,
                        ctx->cipher_ctx.type,
                        ctx->key,
                        ctx->key_len,
                        (uint8_t *)input, length,
                        (uint8_t *)add, add_len,
                        ctx->B0, ctx->A0,
                        tag, tag_len,
                        output);
            break;
        case VC_MODE_ECB:
            break;
        case VC_MODE_CBC:
            break;
        default:
            break;
        }
    }

    if ((length == 0 && ctx->cipher_ctx.operation == VC_OPERATION_ENCRYPT) ||
        (length == 0 && ctx->cipher_ctx.operation == VC_OPERATION_DECRYPT)) {

        // Note: length 0 only allowed in ccm star 
        if (ccm_mode != VC_CCM_STAR_ENCRYPT && ccm_mode != VC_CCM_STAR_DECRYPT)
            return VC_ERR_CCM_BAD_INPUT;

        if (ctx->cipher_ctx.mode != VC_MODE_CBC)
            return VC_ERR_CCM_BAD_INPUT;

        if (ctx->cipher_ctx.type != VC_CIPHER_AES_128_CBC &&
            ctx->cipher_ctx.type != VC_CIPHER_AES_192_CBC &&
            ctx->cipher_ctx.type != VC_CIPHER_AES_256_CBC) {
            return VC_ERR_CCM_BAD_INPUT;
        }

        // Note: length 0 must use AES_CBC

        cbc_encrypt(ctx->cipher_ctx.type,
                    ctx->key,
                    ctx->key_len,
                    (uint8_t *)add, add_len,
                    ctx->B0, ctx->A0,
                    tag, tag_len);
    }

    return 0;
}

int vccrypt_ccm_encrypt_and_tag(vc_ccm_context *ctx, size_t length,
                                const unsigned char *iv, size_t iv_len,
                                const unsigned char *add, size_t add_len,
                                const unsigned char *input, unsigned char *output,
                                unsigned char *tag, size_t tag_len)
{
    if (ctx->cipher_ctx.operation != VC_OPERATION_ENCRYPT)
        return VC_ERR_CCM_BAD_INPUT;

    int rs = vcradio_lock_irq();

    int ret = ccm_auth_crypt(ctx, VC_CCM_ENCRYPT, length,iv, iv_len,
                             add, add_len, input, output,
                             tag, tag_len);

    vcradio_unlock_irq(rs);

    return ret;
}

int vccrypt_ccm_auth_decrypt(vc_ccm_context *ctx, size_t length,
                             const unsigned char *iv, size_t iv_len,
                             const unsigned char *add, size_t add_len,
                             const unsigned char *input, unsigned char *output,
                             const unsigned char *tag, size_t tag_len)
{
    if (ctx->cipher_ctx.operation != VC_OPERATION_DECRYPT)
        return VC_ERR_CCM_BAD_INPUT;

    int rs = vcradio_lock_irq();

    int ret = ccm_auth_crypt(ctx, VC_CCM_DECRYPT, length, iv, iv_len,
                             add, add_len, input, output,
                             (unsigned char *)tag, tag_len);

    vcradio_unlock_irq(rs);
    
    return ret;
}

int vccrypt_ccm_star_encrypt_and_tag(vc_ccm_context *ctx, size_t length,
                                     const unsigned char *iv, size_t iv_len,
                                     const unsigned char *add, size_t add_len,
                                     const unsigned char *input, unsigned char *output,
                                     unsigned char *tag, size_t tag_len )
{
    if (ctx->cipher_ctx.operation != VC_OPERATION_ENCRYPT)
        return VC_ERR_CCM_BAD_INPUT;

    int rs = vcradio_lock_irq();

    int ret = ccm_auth_crypt(ctx, VC_CCM_STAR_ENCRYPT, length, iv, iv_len,
                             add, add_len, input, output,
                             tag, tag_len);

    vcradio_unlock_irq(rs);

    return ret;
}

int vccrypt_ccm_star_auth_decrypt(vc_ccm_context *ctx, size_t length,
                                  const unsigned char *iv, size_t iv_len,
                                  const unsigned char *add, size_t add_len,
                                  const unsigned char *input, unsigned char *output,
                                  const unsigned char *tag, size_t tag_len )
{
    if (ctx->cipher_ctx.operation != VC_OPERATION_DECRYPT)
        return VC_ERR_CCM_BAD_INPUT;

    int rs = vcradio_lock_irq();

    int ret = ccm_auth_crypt(ctx, VC_CCM_STAR_DECRYPT, length, iv, iv_len,
                             add, add_len, input, output,
                             (unsigned char *)tag, tag_len);

    vcradio_unlock_irq(rs);

    return ret;
}
