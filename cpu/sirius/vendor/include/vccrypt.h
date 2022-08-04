/**
 * Copyright (c) 2018 Vertexcom Technologies, Inc. All rights reserved
 * Vertexcom Confidential Proprietary
 *
*/

#ifndef __VC_CRYPT_H
#define __VC_CRYPT_H

#include <stdint.h>
#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif

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

#ifdef __cplusplus
}
#endif

#endif // __VC_CRYPT_H
