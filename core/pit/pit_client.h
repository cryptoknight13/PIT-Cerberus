// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT license.

/*
  Developed by AMI Inc. & Colorado State University.
  Contact person: Rakesh Podder. Email: rakeshpodder3@gmail.com
*/

#include "mbedtls/ecdh.h"
#include "crypto/ecc_mbedtls.h"
#define SUCCESS 1

int pit_connect(int desired_port);

int keyexchangestate(uint8_t *pubkey_cli, size_t pubkey_der_length, uint8_t *pubkey_serv);

int send_unlock_info(uint8_t *OTPs, size_t OTPs_size, uint8_t *unlock_aes_iv, size_t unlock_aes_iv_size, uint8_t *OTP_tag, uint8_t *server_encrypted_message, uint8_t *server_tag);



int receive_product_info(uint8_t *EncryptedProductID, uint8_t *EncryptedProductIDTag, size_t ProductIDSize, uint8_t *aes_iv, size_t aes_iv_size);

#define	PIT_I2C_ERROR(code)		ROT_ERROR (ROT_MODULE_PIT_CRYPTO, code)

/**
 * Error codes that can be generated by a hash or HMAC engine.
 */
enum {
  PIT_I2C_CONNECTION_FAILURE = PIT_I2C_ERROR (0x00),	/** Decryption failed*/
};

