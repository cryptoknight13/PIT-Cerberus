// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT license.

#include "ecc_kat_vectors.h"


/**
 * Raw P-256 private key for ECC self tests.
 */
const uint8_t ECC_KAT_VECTORS_P256_ECC_PRIVATE[] = {
	0x64,0x85,0x0c,0x50,0x94,0x58,0x9f,0x4b,0x7e,0x1a,0xd7,0x58,0x63,0x82,0xc8,0xbc,
	0xa5,0x16,0x96,0x6a,0x4e,0x87,0xd6,0xc6,0x23,0xa8,0x27,0xdc,0xb5,0x89,0x25,0x99
};

/**
 * DER encoded P-256 private key for ECC self tests.
 */
const uint8_t ECC_KAT_VECTORS_P256_ECC_PRIVATE_DER[] = {
	0x30,0x77,0x02,0x01,0x01,0x04,0x20,0x64,0x85,0x0c,0x50,0x94,0x58,0x9f,0x4b,0x7e,
	0x1a,0xd7,0x58,0x63,0x82,0xc8,0xbc,0xa5,0x16,0x96,0x6a,0x4e,0x87,0xd6,0xc6,0x23,
	0xa8,0x27,0xdc,0xb5,0x89,0x25,0x99,0xa0,0x0a,0x06,0x08,0x2a,0x86,0x48,0xce,0x3d,
	0x03,0x01,0x07,0xa1,0x44,0x03,0x42,0x00,0x04,0xe3,0x51,0xfa,0x63,0x3c,0x37,0xbe,
	0xe6,0xde,0x7f,0x65,0x8e,0xdd,0xbd,0xd6,0xd5,0x31,0xef,0x9c,0xd6,0xb5,0x14,0xc2,
	0x28,0xb1,0x08,0x8b,0x0b,0xe4,0x29,0xc3,0x03,0x67,0x0e,0x28,0xc2,0xb2,0x8b,0xd0,
	0x9b,0xc0,0xe4,0x33,0xa6,0x23,0x5a,0xa9,0x7a,0xeb,0x3a,0x65,0x15,0x95,0x08,0xac,
	0x7a,0xde,0x27,0x36,0x71,0xe4,0x4c,0xde,0x4e
};

const size_t ECC_KAT_VECTORS_P256_ECC_PRIVATE_DER_LEN =
	sizeof (ECC_KAT_VECTORS_P256_ECC_PRIVATE_DER);

/**
 * Raw P-256 public key for ECC self tests.
 */
const struct ecc_point_public_key ECC_KAT_VECTORS_P256_ECC_PUBLIC = {
	.x = {
		0xe3,0x51,0xfa,0x63,0x3c,0x37,0xbe,0xe6,0xde,0x7f,0x65,0x8e,0xdd,0xbd,0xd6,0xd5,
		0x31,0xef,0x9c,0xd6,0xb5,0x14,0xc2,0x28,0xb1,0x08,0x8b,0x0b,0xe4,0x29,0xc3,0x03,
	},
	.y = {
		0x67,0x0e,0x28,0xc2,0xb2,0x8b,0xd0,0x9b,0xc0,0xe4,0x33,0xa6,0x23,0x5a,0xa9,0x7a,
		0xeb,0x3a,0x65,0x15,0x95,0x08,0xac,0x7a,0xde,0x27,0x36,0x71,0xe4,0x4c,0xde,0x4e
	},
	.key_length = ECC_KEY_LENGTH_256
};

/**
 * DER encoded P-256 private key for ECC self tests.
 */
const uint8_t ECC_KAT_VECTORS_P256_ECC_PUBLIC_DER[] = {
	0x30,0x59,0x30,0x13,0x06,0x07,0x2a,0x86,0x48,0xce,0x3d,0x02,0x01,0x06,0x08,0x2a,
	0x86,0x48,0xce,0x3d,0x03,0x01,0x07,0x03,0x42,0x00,0x04,0xe3,0x51,0xfa,0x63,0x3c,
	0x37,0xbe,0xe6,0xde,0x7f,0x65,0x8e,0xdd,0xbd,0xd6,0xd5,0x31,0xef,0x9c,0xd6,0xb5,
	0x14,0xc2,0x28,0xb1,0x08,0x8b,0x0b,0xe4,0x29,0xc3,0x03,0x67,0x0e,0x28,0xc2,0xb2,
	0x8b,0xd0,0x9b,0xc0,0xe4,0x33,0xa6,0x23,0x5a,0xa9,0x7a,0xeb,0x3a,0x65,0x15,0x95,
	0x08,0xac,0x7a,0xde,0x27,0x36,0x71,0xe4,0x4c,0xde,0x4e
};

const size_t ECC_KAT_VECTORS_P256_ECC_PUBLIC_DER_LEN = sizeof (ECC_KAT_VECTORS_P256_ECC_PUBLIC_DER);

/**
 * Raw P-256 signature using SHA-256 for ECDSA self tests.
 */
const struct ecc_ecdsa_signature ECC_KAT_VECTORS_P256_ECDSA_SIGNATURE = {
	.r = {
		0x5b,0xb8,0xfa,0x2b,0x5c,0x6c,0xe4,0x88,0x2e,0x98,0x94,0x6c,0xb6,0x79,0x4f,0xba,
		0xe1,0x73,0xa8,0x67,0x23,0x5c,0x82,0x80,0x6b,0x36,0x8c,0x1a,0x5e,0x58,0x26,0x4a
	},
	.s = {
		0xed,0x35,0x8c,0xef,0x08,0x5b,0xfb,0xa0,0x3a,0x58,0x89,0x3c,0xb3,0x61,0x57,0x02,
		0x6f,0x19,0x88,0xad,0xe4,0x87,0xd2,0x96,0xbe,0x9e,0x99,0x77,0xd6,0xcd,0x22,0x26
	},
	.length = ECC_KEY_LENGTH_256
};

/**
 * DER encoded P-256 signature using SHA-256 for ECDSA self tests.
 */
const uint8_t ECC_KAT_VECTORS_P256_ECDSA_SIGNATURE_DER[] = {
	0x30,0x45,0x02,0x20,0x5b,0xb8,0xfa,0x2b,0x5c,0x6c,0xe4,0x88,0x2e,0x98,0x94,0x6c,
	0xb6,0x79,0x4f,0xba,0xe1,0x73,0xa8,0x67,0x23,0x5c,0x82,0x80,0x6b,0x36,0x8c,0x1a,
	0x5e,0x58,0x26,0x4a,0x02,0x21,0x00,0xed,0x35,0x8c,0xef,0x08,0x5b,0xfb,0xa0,0x3a,
	0x58,0x89,0x3c,0xb3,0x61,0x57,0x02,0x6f,0x19,0x88,0xad,0xe4,0x87,0xd2,0x96,0xbe,
	0x9e,0x99,0x77,0xd6,0xcd,0x22,0x26
};

const uint32_t ECC_KAT_VECTORS_P256_ECDSA_SIGNATURE_DER_LEN =
	sizeof (ECC_KAT_VECTORS_P256_ECDSA_SIGNATURE_DER);


#if (ECC_MAX_KEY_LENGTH >= ECC_KEY_LENGTH_384)
/**
 * Raw P-384 private key for ECC self tests.
 */
const uint8_t ECC_KAT_VECTORS_P384_ECC_PRIVATE[] = {
	0x5d,0x57,0x6f,0x7d,0xd2,0x90,0xd7,0x94,0x53,0x02,0x74,0x38,0xb3,0xe6,0x81,0xa1,
	0x10,0xc5,0xd0,0x95,0x31,0x3d,0xcb,0x69,0x78,0x34,0x41,0x62,0x2f,0x87,0xc7,0x1e,
	0x12,0x80,0x4c,0xb0,0x97,0x2e,0x63,0xbd,0xff,0x8a,0x25,0x6b,0x63,0xd4,0x90,0x8d
};

/**
 * DER encoded P-384 private key for ECC self tests.
 */
const uint8_t ECC_KAT_VECTORS_P384_ECC_PRIVATE_DER[] = {
	0x30,0x81,0xa4,0x02,0x01,0x01,0x04,0x30,0x5d,0x57,0x6f,0x7d,0xd2,0x90,0xd7,0x94,
	0x53,0x02,0x74,0x38,0xb3,0xe6,0x81,0xa1,0x10,0xc5,0xd0,0x95,0x31,0x3d,0xcb,0x69,
	0x78,0x34,0x41,0x62,0x2f,0x87,0xc7,0x1e,0x12,0x80,0x4c,0xb0,0x97,0x2e,0x63,0xbd,
	0xff,0x8a,0x25,0x6b,0x63,0xd4,0x90,0x8d,0xa0,0x07,0x06,0x05,0x2b,0x81,0x04,0x00,
	0x22,0xa1,0x64,0x03,0x62,0x00,0x04,0xcf,0x6b,0x8d,0x9a,0x48,0x75,0xa9,0x5a,0x19,
	0x89,0x72,0x18,0xa4,0x94,0x4d,0xef,0x0a,0x93,0xce,0x5b,0x8b,0x8d,0xf1,0x37,0x54,
	0x09,0x17,0x89,0xbc,0xef,0x69,0xdb,0x6c,0xa7,0x9e,0xf6,0xb6,0x4b,0x5c,0x13,0xed,
	0x3c,0xbf,0xed,0x0b,0x3d,0xf1,0x7e,0x53,0xbf,0xf4,0x76,0x31,0x31,0x33,0xa3,0x58,
	0x3c,0x11,0x3d,0xeb,0x8d,0xb6,0xb7,0x47,0x4a,0xe3,0x51,0xd0,0x38,0x26,0xac,0xec,
	0x11,0x34,0x33,0x04,0x0d,0xc6,0xc3,0x75,0x37,0xa1,0x89,0xdd,0x4f,0x66,0x57,0x72,
	0xac,0xc5,0x3b,0xb6,0xc6,0xb8,0x0c
};

const size_t ECC_KAT_VECTORS_P384_ECC_PRIVATE_DER_LEN =
	sizeof (ECC_KAT_VECTORS_P384_ECC_PRIVATE_DER);

/**
 * Raw P-384 public key for ECC self tests.
 */
const struct ecc_point_public_key ECC_KAT_VECTORS_P384_ECC_PUBLIC = {
	.x = {
		0xcf,0x6b,0x8d,0x9a,0x48,0x75,0xa9,0x5a,0x19,0x89,0x72,0x18,0xa4,0x94,0x4d,0xef,
		0x0a,0x93,0xce,0x5b,0x8b,0x8d,0xf1,0x37,0x54,0x09,0x17,0x89,0xbc,0xef,0x69,0xdb,
		0x6c,0xa7,0x9e,0xf6,0xb6,0x4b,0x5c,0x13,0xed,0x3c,0xbf,0xed,0x0b,0x3d,0xf1,0x7e,
	},
	.y = {
		0x53,0xbf,0xf4,0x76,0x31,0x31,0x33,0xa3,0x58,0x3c,0x11,0x3d,0xeb,0x8d,0xb6,0xb7,
		0x47,0x4a,0xe3,0x51,0xd0,0x38,0x26,0xac,0xec,0x11,0x34,0x33,0x04,0x0d,0xc6,0xc3,
		0x75,0x37,0xa1,0x89,0xdd,0x4f,0x66,0x57,0x72,0xac,0xc5,0x3b,0xb6,0xc6,0xb8,0x0c
	},
	.key_length = ECC_KEY_LENGTH_384
};

/**
 * DER encoded P-384 public key for ECC self tests.
 */
const uint8_t ECC_KAT_VECTORS_P384_ECC_PUBLIC_DER[] = {
	0x30,0x76,0x30,0x10,0x06,0x07,0x2a,0x86,0x48,0xce,0x3d,0x02,0x01,0x06,0x05,0x2b,
	0x81,0x04,0x00,0x22,0x03,0x62,0x00,0x04,0xcf,0x6b,0x8d,0x9a,0x48,0x75,0xa9,0x5a,
	0x19,0x89,0x72,0x18,0xa4,0x94,0x4d,0xef,0x0a,0x93,0xce,0x5b,0x8b,0x8d,0xf1,0x37,
	0x54,0x09,0x17,0x89,0xbc,0xef,0x69,0xdb,0x6c,0xa7,0x9e,0xf6,0xb6,0x4b,0x5c,0x13,
	0xed,0x3c,0xbf,0xed,0x0b,0x3d,0xf1,0x7e,0x53,0xbf,0xf4,0x76,0x31,0x31,0x33,0xa3,
	0x58,0x3c,0x11,0x3d,0xeb,0x8d,0xb6,0xb7,0x47,0x4a,0xe3,0x51,0xd0,0x38,0x26,0xac,
	0xec,0x11,0x34,0x33,0x04,0x0d,0xc6,0xc3,0x75,0x37,0xa1,0x89,0xdd,0x4f,0x66,0x57,
	0x72,0xac,0xc5,0x3b,0xb6,0xc6,0xb8,0x0c
};

const size_t ECC_KAT_VECTORS_P384_ECC_PUBLIC_DER_LEN = sizeof (ECC_KAT_VECTORS_P384_ECC_PUBLIC_DER);

/**
 * Raw P-384 signature using SHA-384 for ECDSA self tests.
 */
const struct ecc_ecdsa_signature ECC_KAT_VECTORS_P384_ECDSA_SIGNATURE = {
	.r = {
		0x28,0xb6,0xeb,0x01,0xde,0x53,0xcd,0x1d,0x91,0xa3,0x21,0x2f,0x73,0x67,0x4f,0x01,
		0x19,0x46,0x74,0xd8,0x89,0x38,0x79,0x39,0x09,0x2c,0x82,0xd8,0x60,0x8f,0xd2,0x63,
		0xee,0x9c,0x15,0x70,0xdd,0xba,0x2f,0xda,0xcd,0x73,0x8d,0x01,0x10,0xab,0x26,0xb1
	},
	.s = {
		0x61,0x49,0x5a,0xbc,0x24,0x5e,0x00,0x86,0x19,0x09,0x6f,0x86,0x9d,0xcc,0x90,0xf4,
		0x36,0x4a,0x2e,0x87,0x90,0x92,0x2a,0x9a,0x5c,0xdc,0x71,0x58,0xd6,0x80,0x7e,0x90,
		0x0d,0xe2,0xb8,0x38,0x55,0xb7,0x74,0x6f,0x12,0xcb,0xca,0x99,0x81,0x48,0x20,0x35
	},
	.length = ECC_KEY_LENGTH_384
};

/**
 * DER encoded P-384 signature using SHA-384 for ECDSA self tests.
 */
const uint8_t ECC_KAT_VECTORS_P384_ECDSA_SIGNATURE_DER[] = {
	0x30,0x64,0x02,0x30,0x28,0xb6,0xeb,0x01,0xde,0x53,0xcd,0x1d,0x91,0xa3,0x21,0x2f,
	0x73,0x67,0x4f,0x01,0x19,0x46,0x74,0xd8,0x89,0x38,0x79,0x39,0x09,0x2c,0x82,0xd8,
	0x60,0x8f,0xd2,0x63,0xee,0x9c,0x15,0x70,0xdd,0xba,0x2f,0xda,0xcd,0x73,0x8d,0x01,
	0x10,0xab,0x26,0xb1,0x02,0x30,0x61,0x49,0x5a,0xbc,0x24,0x5e,0x00,0x86,0x19,0x09,
	0x6f,0x86,0x9d,0xcc,0x90,0xf4,0x36,0x4a,0x2e,0x87,0x90,0x92,0x2a,0x9a,0x5c,0xdc,
	0x71,0x58,0xd6,0x80,0x7e,0x90,0x0d,0xe2,0xb8,0x38,0x55,0xb7,0x74,0x6f,0x12,0xcb,
	0xca,0x99,0x81,0x48,0x20,0x35
};

const uint32_t ECC_KAT_VECTORS_P384_ECDSA_SIGNATURE_DER_LEN =
	sizeof (ECC_KAT_VECTORS_P384_ECDSA_SIGNATURE_DER);
#endif /* (ECC_MAX_KEY_LENGTH >= ECC_KEY_LENGTH_384) */


#if (ECC_MAX_KEY_LENGTH >= ECC_KEY_LENGTH_521)
/**
 * Raw P-521 private key for ECC self tests.
 */
const uint8_t ECC_KAT_VECTORS_P521_ECC_PRIVATE[] = {
	0x00,0x51,0x3d,0xe6,0xfb,0xc9,0x59,0xe9,0x81,0x2f,0x16,0xb3,0x36,0xe7,0x11,0x02,
	0xd4,0x0c,0x61,0xf4,0x5d,0xf5,0xea,0x6a,0xab,0xa0,0xa7,0x7a,0x79,0x7e,0x80,0x79,
	0x31,0xca,0x2d,0x22,0x6b,0x7e,0x5b,0x63,0xe2,0xa8,0x93,0xf1,0xe2,0x7e,0xba,0x6c,
	0xe2,0xd0,0xea,0xfc,0x9b,0xa1,0x35,0xd6,0x23,0xfb,0x21,0x66,0x56,0x0c,0x34,0xc5,
	0x53,0x57
};

/**
 * DER encoded P-521 private key for ECC self tests.
 */
const uint8_t ECC_KAT_VECTORS_P521_ECC_PRIVATE_DER[] = {
	0x30,0x81,0xdc,0x02,0x01,0x01,0x04,0x42,0x00,0x51,0x3d,0xe6,0xfb,0xc9,0x59,0xe9,
	0x81,0x2f,0x16,0xb3,0x36,0xe7,0x11,0x02,0xd4,0x0c,0x61,0xf4,0x5d,0xf5,0xea,0x6a,
	0xab,0xa0,0xa7,0x7a,0x79,0x7e,0x80,0x79,0x31,0xca,0x2d,0x22,0x6b,0x7e,0x5b,0x63,
	0xe2,0xa8,0x93,0xf1,0xe2,0x7e,0xba,0x6c,0xe2,0xd0,0xea,0xfc,0x9b,0xa1,0x35,0xd6,
	0x23,0xfb,0x21,0x66,0x56,0x0c,0x34,0xc5,0x53,0x57,0xa0,0x07,0x06,0x05,0x2b,0x81,
	0x04,0x00,0x23,0xa1,0x81,0x89,0x03,0x81,0x86,0x00,0x04,0x01,0xe0,0x2d,0x01,0x99,
	0x16,0xdf,0xd5,0xec,0x7a,0x4e,0x08,0x70,0x5d,0x4a,0x01,0xc8,0x9f,0xc6,0x4b,0x10,
	0x4a,0xf2,0x53,0xb8,0x48,0xd9,0x49,0xbc,0x49,0x84,0x17,0x78,0x68,0xdd,0x19,0xcc,
	0xdf,0x93,0x70,0x04,0xda,0xbd,0x33,0xbf,0x4b,0x2e,0x81,0x82,0x33,0x00,0x80,0x2f,
	0xfd,0xd0,0x57,0xc6,0x95,0xaa,0x4f,0xf5,0x32,0x1c,0xec,0xea,0xd0,0x00,0xfd,0xc1,
	0xcf,0xb1,0xe3,0xe6,0x6d,0xa6,0x50,0xdc,0x84,0xd6,0x37,0xa2,0x21,0xd9,0x28,0x2e,
	0x61,0x52,0x5a,0xcb,0xe9,0x95,0x39,0xd8,0xc3,0x7d,0x48,0x36,0xe5,0x82,0xb7,0x4d,
	0x1b,0x5e,0xef,0xd3,0x2b,0x80,0x76,0x9f,0x45,0x07,0xf0,0xad,0x73,0x85,0xe8,0x23,
	0x3f,0xd2,0x86,0x9a,0xce,0x35,0x2c,0x27,0x94,0xf9,0x09,0x45,0x30,0xd2,0x59
};

const size_t ECC_KAT_VECTORS_P521_ECC_PRIVATE_DER_LEN =
	sizeof (ECC_KAT_VECTORS_P521_ECC_PRIVATE_DER);

/**
 * Raw P-521 public key for ECC self tests.
 */
const struct ecc_point_public_key ECC_KAT_VECTORS_P521_ECC_PUBLIC = {
	.x = {
		0xcf,0x6b,0x8d,0x9a,0x48,0x75,0xa9,0x5a,0x19,0x89,0x72,0x18,0xa4,0x94,0x4d,0xef,
		0x0a,0x93,0xce,0x5b,0x8b,0x8d,0xf1,0x37,0x54,0x09,0x17,0x89,0xbc,0xef,0x69,0xdb,
		0x6c,0xa7,0x9e,0xf6,0xb6,0x4b,0x5c,0x13,0xed,0x3c,0xbf,0xed,0x0b,0x3d,0xf1,0x7e,
	},
	.y = {
		0x53,0xbf,0xf4,0x76,0x31,0x31,0x33,0xa3,0x58,0x3c,0x11,0x3d,0xeb,0x8d,0xb6,0xb7,
		0x47,0x4a,0xe3,0x51,0xd0,0x38,0x26,0xac,0xec,0x11,0x34,0x33,0x04,0x0d,0xc6,0xc3,
		0x75,0x37,0xa1,0x89,0xdd,0x4f,0x66,0x57,0x72,0xac,0xc5,0x3b,0xb6,0xc6,0xb8,0x0c
	},
	.key_length = ECC_KEY_LENGTH_521
};

/**
 * DER encoded P-521 public key for ECC self tests.
 */
const uint8_t ECC_KAT_VECTORS_P521_ECC_PUBLIC_DER[] = {
	0x30,0x81,0x9b,0x30,0x10,0x06,0x07,0x2a,0x86,0x48,0xce,0x3d,0x02,0x01,0x06,0x05,
	0x2b,0x81,0x04,0x00,0x23,0x03,0x81,0x86,0x00,0x04,0x01,0xe0,0x2d,0x01,0x99,0x16,
	0xdf,0xd5,0xec,0x7a,0x4e,0x08,0x70,0x5d,0x4a,0x01,0xc8,0x9f,0xc6,0x4b,0x10,0x4a,
	0xf2,0x53,0xb8,0x48,0xd9,0x49,0xbc,0x49,0x84,0x17,0x78,0x68,0xdd,0x19,0xcc,0xdf,
	0x93,0x70,0x04,0xda,0xbd,0x33,0xbf,0x4b,0x2e,0x81,0x82,0x33,0x00,0x80,0x2f,0xfd,
	0xd0,0x57,0xc6,0x95,0xaa,0x4f,0xf5,0x32,0x1c,0xec,0xea,0xd0,0x00,0xfd,0xc1,0xcf,
	0xb1,0xe3,0xe6,0x6d,0xa6,0x50,0xdc,0x84,0xd6,0x37,0xa2,0x21,0xd9,0x28,0x2e,0x61,
	0x52,0x5a,0xcb,0xe9,0x95,0x39,0xd8,0xc3,0x7d,0x48,0x36,0xe5,0x82,0xb7,0x4d,0x1b,
	0x5e,0xef,0xd3,0x2b,0x80,0x76,0x9f,0x45,0x07,0xf0,0xad,0x73,0x85,0xe8,0x23,0x3f,
	0xd2,0x86,0x9a,0xce,0x35,0x2c,0x27,0x94,0xf9,0x09,0x45,0x30,0xd2,0x59
};

const size_t ECC_KAT_VECTORS_P521_ECC_PUBLIC_DER_LEN = sizeof (ECC_KAT_VECTORS_P521_ECC_PUBLIC_DER);

/**
 * Raw P-521 signature using SHA-512 for ECDSA self tests.
 */
const struct ecc_ecdsa_signature ECC_KAT_VECTORS_P521_ECDSA_SIGNATURE = {
	.r = {
		0x01,0xce,0xb5,0x3d,0xc6,0xb4,0xf1,0x87,0xd1,0xae,0x6c,0x81,0x3a,0x07,0xf0,0x3c,
		0x79,0xa5,0x5b,0x5e,0x61,0xa4,0x98,0xa0,0xba,0x7b,0x7f,0x84,0xf5,0x2f,0xc6,0x3b,
		0x99,0x6d,0x32,0x64,0x50,0xaf,0x50,0x7b,0xc4,0xbf,0x97,0x97,0xaa,0x8a,0xd3,0xf2,
		0x1e,0x3a,0xeb,0xe4,0xc7,0x1c,0x54,0x75,0x9c,0x3c,0xeb,0xb1,0x99,0x2e,0x53,0xa2,
		0xda,0xad
	},
	.s = {
		0x00,0x35,0x1e,0x6e,0x15,0xe1,0x6c,0x10,0x81,0x27,0x57,0x1a,0xdb,0xfc,0x0e,0xfe,
		0x54,0xff,0x61,0x61,0x8d,0x96,0xae,0x2d,0x11,0xac,0x64,0x41,0xd4,0x62,0x86,0x32,
		0xb5,0x70,0x31,0x96,0x9b,0xde,0xca,0x2f,0xd9,0xf5,0x3f,0xbe,0x5b,0x0b,0xd0,0x4b,
		0x1a,0xe4,0x29,0x1d,0xba,0xbd,0xe5,0x0f,0xac,0x5a,0xc0,0x3a,0x6f,0x9d,0xd2,0x21,
		0x21,0xd7
	},
	.length = ECC_KEY_LENGTH_521
};

/**
 * DER encoded P-521 signature using SHA-512 for ECDSA self tests.
 */
const uint8_t ECC_KAT_VECTORS_P521_ECDSA_SIGNATURE_DER[] = {
	0x30,0x81,0x87,0x02,0x42,0x01,0xce,0xb5,0x3d,0xc6,0xb4,0xf1,0x87,0xd1,0xae,0x6c,
	0x81,0x3a,0x07,0xf0,0x3c,0x79,0xa5,0x5b,0x5e,0x61,0xa4,0x98,0xa0,0xba,0x7b,0x7f,
	0x84,0xf5,0x2f,0xc6,0x3b,0x99,0x6d,0x32,0x64,0x50,0xaf,0x50,0x7b,0xc4,0xbf,0x97,
	0x97,0xaa,0x8a,0xd3,0xf2,0x1e,0x3a,0xeb,0xe4,0xc7,0x1c,0x54,0x75,0x9c,0x3c,0xeb,
	0xb1,0x99,0x2e,0x53,0xa2,0xda,0xad,0x02,0x41,0x35,0x1e,0x6e,0x15,0xe1,0x6c,0x10,
	0x81,0x27,0x57,0x1a,0xdb,0xfc,0x0e,0xfe,0x54,0xff,0x61,0x61,0x8d,0x96,0xae,0x2d,
	0x11,0xac,0x64,0x41,0xd4,0x62,0x86,0x32,0xb5,0x70,0x31,0x96,0x9b,0xde,0xca,0x2f,
	0xd9,0xf5,0x3f,0xbe,0x5b,0x0b,0xd0,0x4b,0x1a,0xe4,0x29,0x1d,0xba,0xbd,0xe5,0x0f,
	0xac,0x5a,0xc0,0x3a,0x6f,0x9d,0xd2,0x21,0x21,0xd7
};

const uint32_t ECC_KAT_VECTORS_P521_ECDSA_SIGNATURE_DER_LEN =
	sizeof (ECC_KAT_VECTORS_P521_ECDSA_SIGNATURE_DER);
#endif /* (ECC_MAX_KEY_LENGTH >= ECC_KEY_LENGTH_384) */


/**
 * Signed data for ECDSA self tests.
 */
const uint8_t ECC_KAT_VECTORS_ECDSA_SIGNED[] = {
	0x7a,0x4d,0x61,0x8c,0x40,0xb6,0x23,0x29,0xa4,0xa8,0x46,0x9d,0x73,0x1c,0xc0,0x3e,
	0xe9,0x45,0x52,0xd6,0xf3,0x35,0xa6,0xc3,0x12,0x70,0x9f,0x33,0xac,0x5b,0x1f,0xf8,
	0x16,0x4a,0x4e,0x40,0x20,0x7c,0x7c,0xe4,0xbc,0x17,0x5c,0x3d,0xa3,0x99,0x5d,0x43,
	0x79,0x35,0x00,0xb0,0x34,0x1d,0x51,0x68,0x6a,0x2e,0x30,0x66,0xb7,0x0f,0x20,0xeb,
	0xdd,0x6f,0xf2,0x79,0x30,0xa7,0x46,0x2a,0x87,0x84,0xd4,0xec,0x91,0x5c,0x25,0xbc,
	0x4c,0x25,0x85,0x8d,0x1a,0x0b,0x89,0xc0,0x67,0x70,0x13,0xe1,0xf4,0x5d,0xd8,0x74,
	0x8b,0x7b,0xe6,0x54,0x9e,0x40,0xf8,0xf4,0x25,0x97,0x73,0xbc,0x83,0x19,0x1a,0x57,
	0x0a,0x68,0x2e,0xc7,0xb1,0x6e,0x8a,0x40,0x7d,0xf1,0x33,0xf0,0xe4,0x73,0xeb,0x8c
};

const size_t ECC_KAT_VECTORS_ECDSA_SIGNED_LEN = sizeof (ECC_KAT_VECTORS_ECDSA_SIGNED);

/**
 * SHA-256 digest of the data being signed for ECDSA self tests.
 */
const uint8_t ECC_KAT_VECTORS_ECDSA_SHA256_DIGEST[] = {
	0x6a,0x42,0x0b,0xed,0x6d,0x7a,0x16,0x78,0x50,0xea,0x8e,0x2d,0xf3,0x52,0x21,0xf2,
	0xfd,0x6f,0x66,0x05,0xac,0xbe,0x9a,0xb9,0xda,0x74,0xb6,0x03,0x2d,0xbb,0xa8,0x9f
};

/**
 * SHA-384 digest of the data being signed for ECDSA self tests.
 */
const uint8_t ECC_KAT_VECTORS_ECDSA_SHA384_DIGEST[] = {
	0x4d,0x5e,0x78,0x09,0xb7,0x1e,0x39,0x7e,0xb8,0x46,0xa0,0x0e,0x80,0x63,0x8f,0xb6,
	0x71,0xfd,0x0c,0x95,0xac,0x98,0x8f,0x37,0xe5,0x53,0x99,0x87,0x0c,0x96,0x55,0xa2,
	0xae,0x79,0xef,0xdb,0x66,0x3f,0x35,0x56,0x4d,0x41,0xa0,0x22,0x65,0xef,0x63,0x9d
};

/**
 * SHA-512 digest of the data being signed for ECDSA self tests.
 */
const uint8_t ECC_KAT_VECTORS_ECDSA_SHA512_DIGEST[] = {
	0xbe,0x34,0xf0,0x73,0xf5,0x50,0x35,0x7a,0xf4,0xd5,0xaf,0x8a,0x64,0x58,0xa2,0x57,
	0x69,0xde,0x1a,0xc6,0x4b,0x71,0xfe,0xa2,0x9f,0x88,0x05,0x8e,0x57,0x76,0xa6,0x18,
	0xa8,0x87,0x13,0x43,0xdc,0x17,0x12,0x9a,0xc6,0xd3,0x82,0x96,0xff,0x2a,0xa3,0xd5,
	0x81,0x27,0xf2,0x09,0x32,0x81,0x93,0x4a,0xcc,0xa1,0x50,0xbc,0x7a,0x88,0x0d,0x2c
};
