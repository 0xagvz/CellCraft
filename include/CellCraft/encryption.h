#ifndef _ENCRYPTION_H
#define _ENCRYPTION_H
#include "config.h"
#ifdef ONLINE_MODE
#include "mbedtls/platform.h"
#include "mbedtls/entropy.h"
#include "mbedtls/ctr_drbg.h"
#include "mbedtls/pk.h"
#include "mbedtls/rsa.h"
#include "mbedtls/sha1.h"
#include "mbedtls/ssl.h"
#include "mbedtls/debug.h"
#include "mbedtls/net_sockets.h"

struct encryptionData_t
{
    mbedtls_pk_context key;
    mbedtls_entropy_context entropy;
    mbedtls_ctr_drbg_context ctr_drbg;
};
typedef struct encryptionData_t encryptionData_t;
int encryptionBegin();
void encryptionHexDigest(unsigned char dest[45], unsigned char src[20], size_t len);
encryptionData_t *encryptionGetData();
void LoginC2S_encryption_response();
void encryptionCleanup();
#endif /*ONLINE_MODE*/
#endif