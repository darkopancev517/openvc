/**
 * Copyright (c) 2018 Vertexcom Technologies, Inc. All rights reserved
 * Vertexcom Confidential Proprietary
 *
*/

#ifndef __VC_CRYPT_H
#define __VC_CRYPT_H

#include <stdint.h>
#include <stdbool.h>
#include <string.h>

#define VC_CCM_DECRYPT       0
#define VC_CCM_ENCRYPT       1
#define VC_CCM_STAR_DECRYPT  2
#define VC_CCM_STAR_ENCRYPT  3

/** Bad input parameters to the function. */
#define VC_ERR_CCM_BAD_INPUT    -0x000D
/** Authenticated decryption failed. */
#define VC_ERR_CCM_AUTH_FAILED  -0x000F

#ifdef __cplusplus
extern "C" {
#endif

typedef enum
{
    VC_CIPHER_NONE = 0,
    VC_CIPHER_NULL,
    VC_CIPHER_AES_128_ECB,
    VC_CIPHER_AES_192_ECB,
    VC_CIPHER_AES_256_ECB,
    VC_CIPHER_AES_128_CBC,
    VC_CIPHER_AES_192_CBC,
    VC_CIPHER_AES_256_CBC,
    VC_CIPHER_AES_128_CCM,
    VC_CIPHER_AES_192_CCM,
    VC_CIPHER_AES_256_CCM,
} vc_cipher_type_t;

typedef enum
{
    VC_MODE_NONE = 0,
    VC_MODE_ECB,
    VC_MODE_CBC,
    VC_MODE_CCM,
} vc_cipher_mode_t;

typedef enum
{
    VC_OPERATION_NONE = -1,
    VC_DECRYPT = 0,
    VC_ENCRYPT = 1,
} vc_crypto_operation_t;

enum {
    VC_CRYPT_KEY_LENGTH_NONE = 0,
    VC_CRYPT_KEY_LENGTH_DES = 64,
    VC_CRYPT_KEY_LENGTH_EDE = 128,
    VC_CRYPT_KEY_LENGTH_EDE3 = 192,
};

#define VC_CRYPT_MAX_IV_LENGTH 16
#define VC_CRYPT_MAX_BLOCK_LENGTH 16
#define VC_CRYPT_MAX_KEY_LENGTH 32

typedef struct vc_cipher_context_t
{
    vc_cipher_type_t type;
    vc_cipher_mode_t mode;
    vc_crypto_operation_t operation;
    unsigned char iv[VC_CRYPT_MAX_IV_LENGTH];
    size_t iv_size;
} vc_cipher_context_t;;

typedef struct vc_ccm_context
{
    unsigned char B0[16];
    unsigned char A0[16];
    vc_cipher_context_t cipher_ctx;
    size_t add_len;
    size_t tag_len;
    unsigned char q;
    unsigned char mode;
} vc_ccm_context;

void vccrpt_ccm_init(vc_ccm_context *ctx);

int vccrypt_ccm_encrypt_and_tag(vc_ccm_context *ctx, size_t length,
                                const unsigned char *iv, size_t iv_len,
                                const unsigned char *add, size_t add_len,
                                const unsigned char *input, unsigned char *output,
                                unsigned char *tag, size_t tag_len);

int vccrypt_ccm_auth_decrypt(vc_ccm_context *ctx, size_t length,
                             const unsigned char *iv, size_t iv_len,
                             const unsigned char *add, size_t add_len,
                             const unsigned char *input, unsigned char *output,
                             const unsigned char *tag, size_t tag_len);

// ------------------------------------ old legacy api
int vccrypt_init(bool loopback);

//AES
void vccrypt_aes_cbc_encrypt(uint8_t forward,uint8_t mode, uint8_t *key, uint8_t *iv, uint16_t iv_len,
							uint8_t *data, uint16_t data_len,uint8_t *result);

void vccrypt_aes_ecb_encrypt(uint8_t forward,uint8_t mode, uint8_t *key
							,uint8_t *data, uint16_t data_len,uint8_t *result);

void vccrypt_aes_ccm_encrypt(uint8_t forward, uint8_t *key, uint8_t *nonce,
                             uint8_t *m, uint16_t m_len,
                             uint8_t *a, uint16_t a_len,
                             uint8_t *result, uint8_t mic_len);

//CRC
void vccrypt_crc_encrypt(uint8_t mode,uint8_t *data, uint16_t data_len,uint8_t *result);

// ---------------------------------------------------

#ifdef __cplusplus
}
#endif

#endif // __VC_CRYPT_H
