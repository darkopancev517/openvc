#include <stdio.h>
#include <string.h>

#include "vcsoc.h"

static void crypto_test1(void);
static void crypto_test2(void);
static void crypto_test3(void);

static void dump(uint8_t *buf, uint32_t len);

#define TEST1 1
#define TEST2 1
#define TEST3 1

int vcradio_lock_irq(void)
{
  return 0;
}

void vcradio_unlock_irq(int temp)
{
  (void) temp;
}

int main(void)
{
  vccrypt_init(0); // use dma loopback

  printf("Start Security Test:\n");

  crypto_test1();
  crypto_test2();
  crypto_test3();
 
  while(1);

  return 0;
}

static void crypto_test1(void)
{
#if TEST1
    uint8_t key[] = {
        0xa8, 0x79, 0xac, 0x89, 0x71, 0x8f, 0x34, 0x13, 0x2a, 0xe5, 0x4a, 0xdc, 0x13, 0xd7, 0x7d, 0x18
    };

    uint8_t test[] = {
        0x69, 0xee, 0xe6, 0xd2, 0x04, 0x00, 0xfe, 0xff,
        0x00, 0x00, 0x00, 0x01, 0x01, 0x00, 0xfe, 0xff,
        0x00, 0x00, 0x00, 0x0e, 0x1b, 0x00, 0x00, 0x00,
        0x01, 0x05, 0x15, 0x01, 0x04, 0x0a, 0xed, 0x05,
        0x06, 0x15, 0x02, 0xd1, 0x5a, 0xef, 0x01, 0x00,
        0x00, 0x3f,

        0x0e, 0xa0, 0x0c, 0x88, 0xc8, 0x00, 0x00, 0x01,
        0xb8, 0x2c, 0x07, 0x10, 0x62, 0x00, 0x00, 0x00,
        0x3a, 0x98, 0x88, 0xed, 0xa0, 0x7e, 0x33, 0xf0,
        0x02, 0x22, 0x02, 0x23, 0x25, 0xad, 0x01, 0x6c,
        0x19, 0x6d, 0x00, 0x01, 0x00, 0x0c, 0x00, 0x03,
        0x00, 0x06, 0x00, 0x00, 0x00, 0xff, 0xfe, 0x00,
        0x01, 0x01, 0x00, 0x03, 0x00, 0x0c, 0xa8, 0x7b,
        0x0d, 0x29, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
        0xff, 0xff, 0x00, 0x08, 0x00, 0x02, 0x00, 0x00,
        0x00, 0x0e, 0x00, 0x00, 0x00, 0xf8
    };

    uint16_t a_len = 42, m_len = 78;
    uint8_t  mic_len = 8;

    uint8_t m[m_len];
    uint8_t a[a_len];

    memcpy(m, &test[a_len], m_len);
    memcpy(a, test, a_len);

    uint8_t mic_enc[mic_len];
    uint8_t mic_dec[mic_len];

    uint8_t nonce[] = {
        0x00, 0x00, 0x00, 0xff, 0xfe, 0x00, 0x01, 0x01, 0x00, 0x00, 0x00, 0x1b, 0x06
    };

    uint8_t encrypted[] = {
        0x69, 0xee, 0xe6, 0xd2, 0x04, 0x00, 0xfe, 0xff,
        0x00, 0x00, 0x00, 0x01, 0x01, 0x00, 0xfe, 0xff,
        0x00, 0x00, 0x00, 0x0e, 0x1b, 0x00, 0x00, 0x00,
        0x01, 0x05, 0x15, 0x01, 0x04, 0x0a, 0xed, 0x05,
        0x06, 0x15, 0x02, 0xd1, 0x5a, 0xef, 0x01, 0x00,
        0x00, 0x3f,

        0x08, 0x18, 0xff, 0x4b, 0x50, 0x1f, 0x30, 0x15,
        0x38, 0xd9, 0xc5, 0x22, 0x17, 0xb7, 0x08, 0x78,
        0xb3, 0xa0, 0x98, 0xf9, 0xce, 0x10, 0x63, 0x56,
        0x30, 0xef, 0xe1, 0x92, 0xe9, 0xa6, 0x0c, 0x1d,
        0x84, 0x26, 0xbe, 0x3b, 0x9b, 0xc3, 0xa3, 0x76,
        0xc6, 0x19, 0xe0, 0x27, 0x59, 0x11, 0x5a, 0xe6,
        0x72, 0xd9, 0x36, 0x23, 0xc8, 0xf6, 0xff, 0x02,
        0xeb, 0xbb, 0xe0, 0x19, 0x2e, 0x3e, 0xfb, 0x27,
        0xd7, 0x52, 0x57, 0xbd, 0xf0, 0x98, 0xc9, 0x70,
        0x45, 0xf4, 0xd0, 0x7e, 0x7e, 0x88
    };

    uint8_t decrypted[] = {
        0x69, 0xee, 0xe6, 0xd2, 0x04, 0x00, 0xfe, 0xff,
        0x00, 0x00, 0x00, 0x01, 0x01, 0x00, 0xfe, 0xff,
        0x00, 0x00, 0x00, 0x0e, 0x1b, 0x00, 0x00, 0x00,
        0x01, 0x05, 0x15, 0x01, 0x04, 0x0a, 0xed, 0x05,
        0x06, 0x15, 0x02, 0xd1, 0x5a, 0xef, 0x01, 0x00,
        0x00, 0x3f,

        0x0e, 0xa0, 0x0c, 0x88, 0xc8, 0x00, 0x00, 0x01,
        0xb8, 0x2c, 0x07, 0x10, 0x62, 0x00, 0x00, 0x00,
        0x3a, 0x98, 0x88, 0xed, 0xa0, 0x7e, 0x33, 0xf0,
        0x02, 0x22, 0x02, 0x23, 0x25, 0xad, 0x01, 0x6c,
        0x19, 0x6d, 0x00, 0x01, 0x00, 0x0c, 0x00, 0x03,
        0x00, 0x06, 0x00, 0x00, 0x00, 0xff, 0xfe, 0x00,
        0x01, 0x01, 0x00, 0x03, 0x00, 0x0c, 0xa8, 0x7b,
        0x0d, 0x29, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
        0xff, 0xff, 0x00, 0x08, 0x00, 0x02, 0x00, 0x00,
        0x00, 0x0e, 0x00, 0x00, 0x00, 0xf8
    };

    printf("------------------------------------------------------\n");
    printf("crypto_test1: encrypt & decrypt [%u]\n", m_len);
    printf("------------------------------------------------------\n");

    vccrypt_aes_ccm_encrypt(1, key, nonce, m, m_len, a, a_len, mic_enc, mic_len);

    if (memcmp(m, &encrypted[a_len], m_len) == 0) {
        printf("encrypted: succeed\n");
    } else {
        printf("encrypted: failed\n");
    }

    dump(m, m_len);

    printf("mic_enc:\n");
    dump(mic_enc, mic_len);

    vccrypt_aes_ccm_encrypt(0, key, nonce, m, m_len, a, a_len, mic_dec, mic_len);

    if (memcmp(m, &decrypted[a_len], m_len) == 0) {
        printf("decrypted: succeed\n");
    } else {
        printf("decrypted: failed\n");
    }

    dump(m, m_len);

    printf("mic_dec:\n");
    dump(mic_dec, mic_len);
#endif
}

static void crypto_test2(void)
{
#if TEST2
    printf("------------------------------------------------------\n");
    printf("crypto_test2: auth only\n");
    printf("------------------------------------------------------\n");

    uint8_t key2[] = {
        0x8e, 0x59, 0xaf, 0x41, 0x4a, 0xd6, 0xf6, 0xa3, 0x42, 0xce, 0xe5, 0xbf, 0x0e, 0x96, 0x56, 0x8b
    };

    uint8_t nonce2[] = {
        0xff, 0xff, 0xff, 0xff, 0xf4, 0x59, 0xec, 0x53, 0x00, 0x00, 0x00, 0x01, 0x06
    };

    uint8_t a2[] = {
        0x4a, 0xee, 0x28, 0xd2, 0x04, 0x00, 0xfe, 0xff,
        0x00, 0x00, 0x00, 0x53, 0xec, 0x59, 0xf4, 0xff,
        0xff, 0xff, 0xff, 0x0e, 0x01, 0x00, 0x00, 0x00,
        0x02, 0x05, 0x15, 0x01, 0x05, 0xb8, 0x61, 0x01,
        0x02, 0x15, 0x04, 0xa8, 0x06, 0x15, 0x02, 0xbb,
        0x04, 0xbe, 0x01, 0x00
    };

    uint8_t mic2[8];
    uint8_t mic2_auth[8] = {
        0xbe, 0x5d, 0xb3, 0xbf, 0x9c, 0x82, 0x46, 0x62
    };

    vccrypt_aes_ccm_encrypt(1, key2, nonce2, NULL, 0, a2, sizeof(a2), mic2, sizeof(mic2));

    if (memcmp(mic2, mic2_auth, sizeof(mic2)) == 0) {
        printf("mic: ok\n");
    } else {
        printf("mic: failed\n");
    }

    dump(mic2, sizeof(mic2));
#endif
}

static void crypto_test3(void)
{
#if TEST3
    uint8_t key3[] = {
        0x8b, 0xcf, 0x9c, 0x28, 0xde, 0x3e, 0x46, 0x60, 0xbd, 0x3a, 0x65, 0x7c, 0x47, 0xce, 0x2c, 0xe3
    };

    uint8_t nonce3[] = {
        0x00, 0x00, 0x03, 0xff, 0xfe, 0x75, 0x02, 0x89, 0x00, 0x00, 0x00, 0x5f, 0x06
    };

    uint8_t a3[] = {
        0x69, 0xee, 0xa6, 0x8c, 0x0d, 0x00, 0x00, 0x00,
        0x23, 0x18, 0x00, 0x89, 0x02, 0x75, 0xfe, 0xff,
        0x03, 0x00, 0x00, 0x0e, 0x5f, 0x00, 0x00, 0x00,
        0x01, 0x05, 0x15, 0x01, 0x04, 0x13, 0x79, 0x0b,
        0x06, 0x15, 0x02, 0x4b, 0x02, 0x91, 0x01, 0x00,
        0x00, 0x3f
    };

    uint8_t m3[] = {
        0x08, 0xa0, 0x06, 0x88, 0xc8, 0x00, 0x00, 0x10,
        0x07, 0x01, 0x00, 0x99, 0x98, 0xed, 0xa0, 0xe2,
        0xec, 0x00, 0x00, 0x23, 0x79, 0x7a, 0x61, 0x62,
        0x63, 0x64, 0x65, 0x66, 0x67, 0x68, 0x69, 0x6a,
        0x6b, 0x6c, 0x6d, 0x6e, 0x6f, 0x70, 0x71, 0x72,
        0x73, 0x74, 0x75, 0x76, 0x77, 0x78, 0x79, 0x7a,
        0x61, 0x62, 0x63, 0x64, 0x65, 0x66, 0x67, 0x68,
        0x69, 0x6a, 0x6b, 0x6c, 0x6d, 0x6e, 0x6f, 0x70,
        0x71, 0x72, 0x73, 0x74, 0x75, 0x76, 0x77, 0x78,
        0x79, 0x7a, 0x61, 0x62, 0x63, 0x64, 0x65, 0x66,
        0x67, 0x68, 0x69, 0x6a, 0x6b, 0x6c, 0x6d, 0x6e,
        0x6f, 0x70, 0x71, 0x72, 0x73, 0x74, 0x75, 0x76,
        0x77, 0x78, 0x79, 0x7a, 0x61, 0x62, 0x63, 0x64,
        0x65, 0x66, 0x67, 0x68, 0x69, 0x6a, 0x6b, 0x6c,
        0x6d, 0x6e, 0x6f, 0x70, 0x71, 0x72, 0x73, 0x74,
        0x75, 0x76, 0x77, 0x78, 0x79, 0x7a, 0x61, 0x62,
        0x63, 0x64, 0x65, 0x66, 0x67, 0x68, 0x69, 0x6a,
        0x6b, 0x6c, 0x6d, 0x6e, 0x6f, 0x70, 0x71, 0x72,
        0x73, 0x74, 0x75, 0x76, 0x77, 0x78, 0x79, 0x7a,
        0x61, 0x62, 0x63, 0x64, 0x65, 0x66, 0x67, 0x68,
        0x69, 0x6a, 0x6b, 0x6c, 0x6d, 0x6e, 0x6f, 0x70,
        0x71, 0x72, 0x73, 0x74, 0x75, 0x76, 0x77, 0x78,
        0x79, 0x7a, 0x61, 0x62, 0x63, 0x64, 0x65, 0x66,
        0x67, 0x68, 0x69, 0x6a, 0x6b, 0x6c, 0x6d, 0x6e,
        0x6f, 0x70, 0x71, 0x72, 0x73, 0x74, 0x75, 0x76,
        0x77, 0x78, 0x79, 0x7a, 0x61, 0x62, 0x63, 0x64,
        0x65, 0x66, 0x67, 0x68, 0x69, 0x6a, 0x6b, 0x6c,
        0x6d, 0x6e, 0x6f, 0x70, 0x71, 0x72, 0x73, 0x74,
        0x75, 0x76, 0x77, 0x78, 0x79, 0x7a, 0x61, 0x62,
        0x63, 0x64, 0x65, 0x66, 0x67, 0x68, 0x69, 0x6a,
        0x6b, 0x6c, 0x6d, 0x6e, 0x6f, 0x70, 0x71, 0x72,
        0x73, 0x74, 0x75, 0x76, 0x77, 0x78, 0x79, 0x7a,
        0x61, 0x62, 0x63, 0x64, 0x65, 0x66, 0x67, 0x68,
        0x69, 0x6a, 0x6b, 0x6c, 0x00, 0xf8
    };

    uint8_t m3_enc[] = {
        0x2b, 0x53, 0xcd, 0x9e, 0xfb, 0xcd, 0x8c, 0x5d,
        0x3f, 0x55, 0xf2, 0x64, 0x2b, 0x98, 0x72, 0x27,
        0x20, 0x19, 0x2a, 0x0e, 0x04, 0xf6, 0x17, 0x8c,
        0xa3, 0xbc, 0x4b, 0xb0, 0x59, 0x4c, 0xc8, 0xfe,
        0x42, 0x80, 0xee, 0x00, 0xa0, 0xb3, 0xd4, 0x81,
        0x8d, 0x6d, 0xfd, 0xe1, 0xbd, 0x2f, 0x3a, 0x90,
        0x17, 0x73, 0x0b, 0x9b, 0x3b, 0x90, 0xc5, 0xab,
        0xd6, 0x44, 0xf3, 0xcb, 0xca, 0x47, 0x6a, 0xde,
        0x14, 0xf7, 0x5b, 0x0e, 0xac, 0xee, 0x31, 0x76,
        0x0b, 0xa9, 0xf9, 0x26, 0x2a, 0x5b, 0x17, 0x75,
        0xbb, 0x8b, 0xbe, 0x79, 0x74, 0x2c, 0x45, 0x93,
        0x6a, 0xe7, 0x6d, 0x18, 0xb6, 0x1f, 0x07, 0xd7,
        0x84, 0x0d, 0xe4, 0x99, 0xc6, 0x5a, 0x95, 0x8b,
        0xbd, 0xc4, 0xf7, 0xca, 0x67, 0x73, 0x14, 0xdd,
        0xe4, 0xd2, 0x30, 0xe3, 0x01, 0x57, 0x84, 0x46,
        0xd7, 0x15, 0x66, 0x72, 0x08, 0x33, 0x2f, 0x42,
        0x68, 0x17, 0xae, 0xb1, 0x48, 0xd0, 0xed, 0x8c,
        0xd5, 0xff, 0x3c, 0xb4, 0xa4, 0x9e, 0x0c, 0x6d,
        0x3f, 0xfa, 0x9b, 0x33, 0x0b, 0xce, 0x95, 0xb5,
        0xa9, 0xe7, 0xf9, 0x41, 0x8e, 0x32, 0x11, 0x9a,
        0x61, 0x4f, 0xbb, 0x72, 0x01, 0x7e, 0x77, 0x7a,
        0x80, 0x83, 0x04, 0x44, 0xeb, 0x71, 0x15, 0xa6,
        0x46, 0x91, 0xdb, 0x75, 0xdb, 0x39, 0xf8, 0xfb,
        0x94, 0x5e, 0x68, 0x91, 0x23, 0x71, 0x5f, 0xe9,
        0xf7, 0xc4, 0xc0, 0xf4, 0x3c, 0xfe, 0xc3, 0xd9,
        0x96, 0x87, 0x63, 0x21, 0x2d, 0x71, 0xe0, 0xf5,
        0xe3, 0xd4, 0x19, 0xca, 0x45, 0x57, 0x3e, 0x37,
        0x75, 0x02, 0x08, 0x81, 0x9c, 0x2c, 0x70, 0xac,
        0xf2, 0xbc, 0x95, 0x55, 0x90, 0xd6, 0x88, 0x0c,
        0xd3, 0xcb, 0x47, 0x04, 0xa7, 0x31, 0x26, 0x8e,
        0x01, 0xe2, 0xef, 0x80, 0x00, 0xfe, 0xe4, 0x3f,
        0xd2, 0x92, 0xd8, 0xf9, 0x26, 0xbe, 0x3f, 0x99,
        0x8a, 0x2f, 0x42, 0xf3, 0x0d, 0x52, 0xca, 0x89,
        0xd7, 0x47, 0x9f, 0x4f, 0xdb, 0x32
    };

    uint8_t mic3[8];
    uint8_t mic3_auth[8] = {
        0xd3, 0x96, 0x6f, 0x35, 0x30, 0x9a, 0x2c, 0x3c
    };

    printf("------------------------------------------------------\n");
    printf("crypto_test3: encrypt [%u]\n", sizeof(m3));
    printf("------------------------------------------------------\n");

    vccrypt_aes_ccm_encrypt(1, key3, nonce3, m3, sizeof(m3), a3, sizeof(a3), mic3, sizeof(mic3));

    if (memcmp(m3, m3_enc, sizeof(m3)) == 0) {
        printf("encrypt: ok\n");
    } else {
        printf("encrypt: failed\n");
    }

    dump(m3, sizeof(m3));

    if (memcmp(mic3, mic3_auth, sizeof(mic3)) == 0) {
        printf("mic: ok\n");
    } else {
        printf("mic: failed\n");
    }

    dump(mic3, sizeof(mic3));
#endif
}

static void dump(uint8_t *buf, uint32_t len)
{
    for (uint32_t i = 0; i < len; i++) {
        if ((i % 8) == 0) {
            if (i != 0) {
                printf("\n");
            }
        }
        printf("0x%02x ", buf[i]);
    }
    printf("\n");
}
