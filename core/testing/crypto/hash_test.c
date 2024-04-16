// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT license.

#include <stddef.h>
#include <stdint.h>
#include <string.h>
#include "platform_io.h"
#include "testing.h"
#include "crypto/kat/hash_kat_vectors.h"
#include "crypto/kat/hmac_kat_vectors.h"
#include "testing/crypto/hash_testing.h"
#include "testing/engines/hash_testing_engine.h"
#include "testing/mock/crypto/hash_mock.h"


TEST_SUITE_LABEL ("hash");

/**
 * A 440-bit block of data.
 */
const uint8_t HASH_TESTING_PARTIAL_BLOCK_440[] = {
	0x3e, 0xbf, 0xb0, 0x6d, 0xb8, 0xc3, 0x8d, 0x5b, 0xa0, 0x37, 0xf1, 0x36, 0x3e, 0x11, 0x85, 0x50,
	0xaa, 0xd9, 0x46, 0x06, 0xe2, 0x68, 0x35, 0xa0, 0x1a, 0xf0, 0x50, 0x78, 0x53, 0x3c, 0xc2, 0x5f,
	0x2f, 0x39, 0x57, 0x3c, 0x04, 0xb6, 0x32, 0xf6, 0x2f, 0x68, 0xc2, 0x94, 0xab, 0x31, 0xf2, 0xa3,
	0xe2, 0xa1, 0xa0, 0xd8, 0xc2, 0xbe, 0x51
};

const uint32_t HASH_TESTING_PARTIAL_BLOCK_440_LEN = sizeof (HASH_TESTING_PARTIAL_BLOCK_440);

/**
 * A 448-bit block of data.
 */
const uint8_t HASH_TESTING_PARTIAL_BLOCK_448[] = {
	0x2d, 0x52, 0x44, 0x7d, 0x12, 0x44, 0xd2, 0xeb, 0xc2, 0x86, 0x50, 0xe7, 0xb0, 0x56, 0x54, 0xba,
	0xd3, 0x5b, 0x3a, 0x68, 0xee, 0xdc, 0x7f, 0x85, 0x15, 0x30, 0x6b, 0x49, 0x6d, 0x75, 0xf3, 0xe7,
	0x33, 0x85, 0xdd, 0x1b, 0x00, 0x26, 0x25, 0x02, 0x4b, 0x81, 0xa0, 0x2f, 0x2f, 0xd6, 0xdf, 0xfb,
	0x6e, 0x6d, 0x56, 0x1c, 0xb7, 0xd0, 0xbd, 0x7a
};

const uint32_t HASH_TESTING_PARTIAL_BLOCK_448_LEN = sizeof (HASH_TESTING_PARTIAL_BLOCK_448);

/**
 * A 480-bit block of data.
 */
const uint8_t HASH_TESTING_PARTIAL_BLOCK_480[] = {
	0xf4, 0x99, 0xcc, 0x3f, 0x6e, 0x3c, 0xf7, 0xc3, 0x12, 0xff, 0xdf, 0xba, 0x61, 0xb1, 0x26, 0x0c,
	0x37, 0x12, 0x9c, 0x1a, 0xfb, 0x39, 0x10, 0x47, 0x19, 0x33, 0x67, 0xb7, 0xb2, 0xed, 0xeb, 0x57,
	0x92, 0x53, 0xe5, 0x1d, 0x62, 0xba, 0x6d, 0x91, 0x1e, 0x7b, 0x81, 0x8c, 0xca, 0xe1, 0x55, 0x3f,
	0x61, 0x46, 0xea, 0x78, 0x0f, 0x78, 0xe2, 0x21, 0x9f, 0x62, 0x93, 0x09
};

const uint32_t HASH_TESTING_PARTIAL_BLOCK_480_LEN = sizeof (HASH_TESTING_PARTIAL_BLOCK_480);

/**
 * A 512-bit block of data.  This is one full block for SHA1/SHA256 hashes.
 */
const uint8_t HASH_TESTING_FULL_BLOCK_512[] = {
	0x5a, 0x86, 0xb7, 0x37, 0xea, 0xea, 0x8e, 0xe9, 0x76, 0xa0, 0xa2, 0x4d, 0xa6, 0x3e, 0x7e, 0xd7,
	0xee, 0xfa, 0xd1, 0x8a, 0x10, 0x1c, 0x12, 0x11, 0xe2, 0xb3, 0x65, 0x0c, 0x51, 0x87, 0xc2, 0xa8,
	0xa6, 0x50, 0x54, 0x72, 0x08, 0x25, 0x1f, 0x6d, 0x42, 0x37, 0xe6, 0x61, 0xc7, 0xbf, 0x4c, 0x77,
	0xf3, 0x35, 0x39, 0x03, 0x94, 0xc3, 0x7f, 0xa1, 0xa9, 0xf9, 0xbe, 0x83, 0x6a, 0xc2, 0x85, 0x09
};

const uint32_t HASH_TESTING_FULL_BLOCK_512_LEN = sizeof (HASH_TESTING_FULL_BLOCK_512);

/**
 * A 952-bit block of data.
 */
const uint8_t HASH_TESTING_PARTIAL_BLOCK_952[] = {
	0xa5, 0xc4, 0xa4, 0x7a, 0x04, 0xf4, 0x71, 0x42, 0x69, 0xd5, 0xd9, 0x22, 0xba, 0x46, 0x94, 0x06,
	0x0a, 0xa2, 0xdf, 0x49, 0x19, 0x37, 0x20, 0xc8, 0x19, 0xfa, 0xc9, 0x3b, 0xb8, 0x78, 0x7e, 0xc5,
	0x5a, 0x10, 0x7a, 0xc9, 0xa6, 0x60, 0x2f, 0x00, 0x45, 0xfd, 0x2c, 0xc8, 0xe6, 0x67, 0x44, 0xbf,
	0x86, 0x3c, 0xed, 0x91, 0xee, 0xab, 0xe6, 0x0e, 0x7d, 0x2c, 0x1d, 0x80, 0x27, 0x6e, 0xcf, 0x3b,
	0xbe, 0x91, 0xf1, 0x75, 0x70, 0x96, 0xcf, 0x58, 0x92, 0x14, 0xf3, 0x56, 0x9c, 0x2c, 0x48, 0xbd,
	0x74, 0xbe, 0x7f, 0x8b, 0xef, 0xdd, 0xb2, 0x83, 0x95, 0x81, 0x47, 0x80, 0xa4, 0x7c, 0x18, 0x0a,
	0x58, 0xb0, 0xd0, 0x27, 0x6a, 0x7e, 0x98, 0x73, 0xd6, 0x82, 0xf4, 0x73, 0xe2, 0x7d, 0xe7, 0x27,
	0x5c, 0x92, 0x5e, 0xde, 0x23, 0xb6, 0xcc
};

const uint32_t HASH_TESTING_PARTIAL_BLOCK_952_LEN = sizeof (HASH_TESTING_PARTIAL_BLOCK_952);

/**
 * A 960-bit block of data.
 */
const uint8_t HASH_TESTING_PARTIAL_BLOCK_960[] = {
	0x75, 0x26, 0x47, 0x74, 0xaf, 0x69, 0xec, 0x7e, 0xe3, 0x12, 0x5e, 0x20, 0x5b, 0xd6, 0xd1, 0xcb,
	0x8f, 0xdb, 0x22, 0xf7, 0xea, 0x6d, 0xbe, 0x72, 0xd1, 0xf2, 0xc0, 0xf7, 0xe2, 0x20, 0x59, 0x02,
	0x79, 0x6d, 0x75, 0xe3, 0x79, 0xc7, 0x9b, 0x11, 0x49, 0x86, 0x15, 0xc2, 0x1c, 0x9f, 0x52, 0xb8,
	0x76, 0x1a, 0x88, 0x5e, 0xec, 0xc6, 0x9d, 0x13, 0x2b, 0x2b, 0x48, 0xc6, 0x3b, 0xc0, 0x74, 0xc3,
	0x05, 0x5e, 0xe5, 0xcc, 0x13, 0xf5, 0x1d, 0x6c, 0x98, 0x7e, 0x81, 0x88, 0xb0, 0x30, 0xb8, 0x37,
	0xe8, 0xf7, 0x54, 0xd4, 0x01, 0x22, 0xb4, 0x51, 0xf1, 0x5b, 0x28, 0xcd, 0x2b, 0xdd, 0x57, 0x69,
	0x20, 0xe1, 0xde, 0x58, 0x06, 0x59, 0x3a, 0x36, 0xd8, 0xe1, 0xe8, 0x9b, 0x9e, 0xf3, 0xca, 0xef,
	0xee, 0x5a, 0xcd, 0x80, 0xb3, 0xe9, 0xc9, 0xd1
};

const uint32_t HASH_TESTING_PARTIAL_BLOCK_960_LEN = sizeof (HASH_TESTING_PARTIAL_BLOCK_960);

/**
 * A 992-bit block of data.
 */
const uint8_t HASH_TESTING_PARTIAL_BLOCK_992[] = {
	0x1a, 0x85, 0x7c, 0x1f, 0x10, 0x5d, 0x06, 0x8c, 0xea, 0xb0, 0xb1, 0xe1, 0x24, 0x94, 0x89, 0x0e,
	0xc1, 0x96, 0x36, 0x2a, 0x48, 0xb0, 0x20, 0x0a, 0x0d, 0x75, 0xd7, 0x12, 0xb1, 0x8f, 0xb1, 0x4b,
	0xec, 0x6b, 0xb5, 0xb6, 0x8a, 0x33, 0xb7, 0xe0, 0xb4, 0xfd, 0xc5, 0xb7, 0x71, 0x42, 0xc2, 0x9c,
	0x6d, 0x91, 0x51, 0xb9, 0xf8, 0x84, 0xf5, 0x95, 0x51, 0xf4, 0x76, 0xe5, 0x25, 0x69, 0x86, 0xa6,
	0x53, 0xd4, 0xa4, 0x68, 0xf2, 0x81, 0x41, 0xed, 0x95, 0x47, 0x21, 0xf2, 0xcd, 0x02, 0x05, 0x4d,
	0xf0, 0x43, 0x87, 0x38, 0x19, 0x45, 0x45, 0xed, 0x70, 0x23, 0x41, 0x73, 0xac, 0x49, 0x88, 0xb7,
	0xd6, 0x28, 0x12, 0xde, 0x4f, 0x2f, 0xea, 0xda, 0x14, 0xf6, 0x8e, 0x3b, 0x41, 0xbc, 0x99, 0x48,
	0xd4, 0x13, 0x9f, 0x4f, 0xb4, 0xda, 0x59, 0x39, 0xf2, 0x6c, 0x02, 0x61
};

const uint32_t HASH_TESTING_PARTIAL_BLOCK_992_LEN = sizeof (HASH_TESTING_PARTIAL_BLOCK_992);

/**
 * A 1024-bit block of data.  This is one full block for SHA384/SHA512 hashes, or two full blocks
 * for SHA1/SHA256 hashes.
 */
const uint8_t HASH_TESTING_FULL_BLOCK_1024[] = {
	0x3b, 0xf5, 0x2c, 0xc5, 0xee, 0x86, 0xb9, 0xa0, 0x19, 0x0f, 0x39, 0x0a, 0x5c, 0x03, 0x66, 0xa5,
	0x60, 0xb5, 0x57, 0x00, 0x0d, 0xbe, 0x51, 0x15, 0xfd, 0x9e, 0xe1, 0x16, 0x30, 0xa6, 0x27, 0x69,
	0x01, 0x15, 0x75, 0xf1, 0x58, 0x81, 0x19, 0x8f, 0x22, 0x78, 0x76, 0xe8, 0xfe, 0x68, 0x5a, 0x69,
	0x39, 0xbc, 0x8b, 0x89, 0xfd, 0x48, 0xa3, 0x4e, 0xc5, 0xe7, 0x1e, 0x13, 0x14, 0x62, 0xb2, 0x88,
	0x67, 0x94, 0xdf, 0xfa, 0x68, 0xcc, 0xc6, 0xd5, 0x64, 0x73, 0x3e, 0x67, 0xff, 0xef, 0x25, 0xe6,
	0x27, 0xc6, 0xf4, 0xb5, 0x46, 0x07, 0x96, 0xe3, 0xbc, 0xe6, 0x7b, 0xf5, 0x8c, 0xa6, 0xe8, 0xe5,
	0x55, 0xbc, 0x91, 0x6a, 0x85, 0x31, 0x69, 0x7a, 0xc9, 0x48, 0xb9, 0x0d, 0xc8, 0x61, 0x6f, 0x25,
	0x10, 0x1d, 0xb9, 0x0b, 0x50, 0xc3, 0xd3, 0xdb, 0xc9, 0xe2, 0x1e, 0x42, 0xff, 0x38, 0x71, 0x87
};

const uint32_t HASH_TESTING_FULL_BLOCK_1024_LEN = sizeof (HASH_TESTING_FULL_BLOCK_1024);

/**
 * A 2048-bit block of data.  This is two full blocks for SHA384/SHA512 hashes, or four full blocks
 * for SHA1/SHA256 hashes.
 */
const uint8_t HASH_TESTING_FULL_BLOCK_2048[] = {
	0x6b, 0x91, 0x8f, 0xb1, 0xa5, 0xad, 0x1f, 0x9c, 0x5e, 0x5d, 0xbd, 0xf1, 0x0a, 0x93, 0xa9, 0xc8,
	0xf6, 0xbc, 0xa8, 0x9f, 0x37, 0xe7, 0x9c, 0x9f, 0xe1, 0x2a, 0x57, 0x22, 0x79, 0x41, 0xb1, 0x73,
	0xac, 0x79, 0xd8, 0xd4, 0x40, 0xcd, 0xe8, 0xc6, 0x4c, 0x4e, 0xbc, 0x84, 0xa4, 0xc8, 0x03, 0xd1,
	0x98, 0xa2, 0x96, 0xf3, 0xde, 0x06, 0x09, 0x00, 0xcc, 0x42, 0x7f, 0x58, 0xca, 0x6e, 0xc3, 0x73,
	0x08, 0x4f, 0x95, 0xdd, 0x6c, 0x7c, 0x42, 0x7e, 0xcf, 0xbf, 0x78, 0x1f, 0x68, 0xbe, 0x57, 0x2a,
	0x88, 0xdb, 0xcb, 0xb1, 0x88, 0x58, 0x1a, 0xb2, 0x00, 0xbf, 0xb9, 0x9a, 0x3a, 0x81, 0x64, 0x07,
	0xe7, 0xdd, 0x6d, 0xd2, 0x10, 0x03, 0x55, 0x4d, 0x4f, 0x7a, 0x99, 0xc9, 0x3e, 0xbf, 0xce, 0x5c,
	0x30, 0x2f, 0xf0, 0xe1, 0x1f, 0x26, 0xf8, 0x3f, 0xe6, 0x69, 0xac, 0xef, 0xb0, 0xc1, 0xbb, 0xb8,
	0xb1, 0xe9, 0x09, 0xbd, 0x14, 0xaa, 0x48, 0xba, 0x34, 0x45, 0xc8, 0x8b, 0x0e, 0x11, 0x90, 0xee,
	0xf7, 0x65, 0xad, 0x89, 0x8a, 0xb8, 0xca, 0x2f, 0xe5, 0x07, 0x01, 0x5f, 0x15, 0x78, 0xf1, 0x0d,
	0xce, 0x3c, 0x11, 0xa5, 0x5f, 0xb9, 0x43, 0x4e, 0xe6, 0xe9, 0xad, 0x6c, 0xc0, 0xfd, 0xc4, 0x68,
	0x44, 0x47, 0xa9, 0xb3, 0xb1, 0x56, 0xb9, 0x08, 0x64, 0x63, 0x60, 0xf2, 0x4f, 0xec, 0x2d, 0x8f,
	0xa6, 0x9e, 0x2c, 0x93, 0xdb, 0x78, 0x70, 0x8f, 0xcd, 0x2e, 0xef, 0x74, 0x3d, 0xcb, 0x93, 0x53,
	0x81, 0x9b, 0x8d, 0x66, 0x7c, 0x48, 0xed, 0x54, 0xcd, 0x43, 0x6f, 0xb1, 0x47, 0x65, 0x98, 0xc4,
	0xa1, 0xd7, 0x02, 0x8e, 0x6f, 0x2f, 0xf5, 0x07, 0x51, 0xdb, 0x36, 0xab, 0x6b, 0xc3, 0x24, 0x35,
	0x15, 0x2a, 0x00, 0xab, 0xd3, 0xd5, 0x8d, 0x9a, 0x87, 0x70, 0xd9, 0xa3, 0xe5, 0x2d, 0x5a, 0x36
};

const uint32_t HASH_TESTING_FULL_BLOCK_2048_LEN = sizeof (HASH_TESTING_FULL_BLOCK_2048);

/**
 * A 4096-bit block of data.  This is four full blocks for SHA384/SHA512 hashes, or eight full
 * blocks for SHA1/SHA256 hashes.
 */
const uint8_t HASH_TESTING_FULL_BLOCK_4096[] = {
	0xb4, 0x1e, 0xf4, 0xa2, 0xb3, 0x1d, 0x3a, 0x47, 0xa5, 0xe8, 0x38, 0x69, 0x25, 0xfb, 0x90, 0xfb,
	0xe9, 0x80, 0xca, 0x2c, 0xf6, 0xba, 0x34, 0xe8, 0x14, 0xa3, 0xec, 0xa2, 0x80, 0xd4, 0x3b, 0x51,
	0xe2, 0xa6, 0x24, 0xb8, 0x7e, 0x97, 0x3d, 0xeb, 0xae, 0xef, 0xbe, 0x0f, 0x90, 0xa3, 0xd8, 0x61,
	0xfc, 0x79, 0x48, 0x7a, 0xb9, 0x6d, 0x2b, 0xd1, 0xf0, 0x53, 0x14, 0x81, 0xe0, 0xbf, 0x5c, 0x4c,
	0xd4, 0x22, 0xb9, 0xe0, 0x52, 0x35, 0x12, 0x5a, 0x96, 0x9b, 0x92, 0x09, 0x3f, 0xc2, 0xfc, 0x74,
	0x47, 0x0a, 0x3e, 0x9e, 0x38, 0x29, 0x48, 0x88, 0x9d, 0xce, 0x1e, 0xf8, 0xb7, 0x84, 0x2c, 0x79,
	0x72, 0xd9, 0xdb, 0xa3, 0x97, 0xc0, 0x61, 0x9c, 0x43, 0x35, 0xdd, 0xdf, 0x98, 0x1f, 0xa3, 0x3c,
	0xb2, 0x7a, 0xd4, 0x20, 0xdd, 0xb5, 0x33, 0x17, 0x05, 0x59, 0x33, 0x8f, 0x6e, 0xec, 0x55, 0xdf,
	0xa5, 0x15, 0xb0, 0x88, 0xb6, 0x01, 0xd1, 0xba, 0x9f, 0x04, 0xc6, 0x1a, 0x05, 0x84, 0x76, 0xc2,
	0x26, 0x13, 0x34, 0x89, 0x0f, 0xdb, 0x93, 0x85, 0x0e, 0x3f, 0x7b, 0xcf, 0x6b, 0xbf, 0x7c, 0x86,
	0x53, 0x1c, 0x63, 0x17, 0x15, 0xbd, 0x0b, 0xbb, 0x91, 0x52, 0x76, 0x41, 0xec, 0xb7, 0x1c, 0x0d,
	0x89, 0x1b, 0x83, 0x61, 0x35, 0x61, 0x10, 0xdb, 0xa2, 0xc6, 0x1d, 0x3f, 0x17, 0xc5, 0x4c, 0x77,
	0x65, 0x38, 0x1a, 0xd8, 0x1d, 0xbf, 0xb7, 0xa7, 0x00, 0x65, 0x15, 0xdc, 0xb7, 0x81, 0x3e, 0x25,
	0xc5, 0xdb, 0xec, 0x2e, 0xb9, 0x10, 0x53, 0x20, 0xa8, 0x38, 0x42, 0x68, 0xda, 0xc5, 0x6a, 0xb9,
	0xc4, 0xae, 0xfd, 0x54, 0x36, 0xce, 0x7c, 0x87, 0xd6, 0x87, 0xca, 0x73, 0xcd, 0xaa, 0x84, 0x13,
	0xc0, 0x9b, 0x95, 0x7a, 0x02, 0xb0, 0x04, 0x5c, 0x08, 0xdb, 0x11, 0xd0, 0x1d, 0x89, 0x81, 0x54,
	0x56, 0xc9, 0x36, 0x12, 0xc9, 0xb1, 0x02, 0x62, 0xfa, 0xfd, 0xbd, 0x8f, 0x96, 0xfa, 0x95, 0xde,
	0x64, 0xa3, 0xa6, 0xcc, 0x78, 0x09, 0xcb, 0x98, 0xaa, 0xf8, 0xb3, 0x01, 0x46, 0xd7, 0x37, 0x51,
	0x05, 0xd0, 0xea, 0x9a, 0x3c, 0x31, 0xf2, 0x40, 0x54, 0x12, 0x17, 0xb7, 0x7a, 0x39, 0x1a, 0x8e,
	0x97, 0x3a, 0x48, 0xad, 0x83, 0xe2, 0x4e, 0xdb, 0x76, 0xd6, 0x4f, 0x83, 0xbf, 0x78, 0x34, 0xb7,
	0xb8, 0x0a, 0x44, 0x75, 0xf9, 0x16, 0xf4, 0x29, 0xcc, 0x0d, 0x00, 0x74, 0xe1, 0x2e, 0xba, 0x2c,
	0x43, 0xa9, 0xa2, 0xa4, 0x8b, 0x05, 0x38, 0x2d, 0x54, 0xbf, 0x0e, 0xdc, 0xee, 0x34, 0x21, 0x8e,
	0x57, 0xc0, 0x69, 0x2a, 0x66, 0x28, 0xaf, 0x26, 0x4a, 0x35, 0x9f, 0x4d, 0x33, 0xa2, 0x1e, 0xbf,
	0x4f, 0x39, 0xde, 0x39, 0xf8, 0x38, 0x2f, 0x96, 0x2c, 0xf9, 0x18, 0x96, 0x3d, 0xd2, 0xa6, 0xdf,
	0xc9, 0x3b, 0x84, 0x41, 0xed, 0x2e, 0xcc, 0x3e, 0xb6, 0xd4, 0x1d, 0xca, 0xd8, 0x5d, 0xee, 0x4f,
	0xa3, 0x2f, 0x21, 0xf4, 0x32, 0x44, 0xdb, 0x1f, 0xe6, 0xcd, 0x94, 0x38, 0x13, 0x1c, 0x6a, 0xb1,
	0xf8, 0xc0, 0xbb, 0x43, 0xf5, 0xf2, 0xf2, 0x7a, 0xf8, 0x30, 0xa1, 0x73, 0x39, 0x27, 0xd1, 0xe5,
	0x27, 0xd6, 0x96, 0x5e, 0xa1, 0xf1, 0xe6, 0xcf, 0x6a, 0x83, 0xaa, 0x4b, 0xd7, 0xd8, 0x16, 0x0c,
	0xcb, 0x9a, 0x36, 0xb7, 0xe5, 0x3a, 0xca, 0xe0, 0xf8, 0x91, 0x54, 0xd1, 0xbc, 0xc8, 0x6f, 0x87,
	0xc3, 0x75, 0x62, 0xfe, 0xae, 0x06, 0xf5, 0xaf, 0xa0, 0x63, 0x84, 0x56, 0xf3, 0xcf, 0x51, 0xf8,
	0x2a, 0x0f, 0x1e, 0x25, 0x27, 0xcf, 0xfc, 0x7b, 0x9f, 0x41, 0x5e, 0x6b, 0xca, 0x07, 0x71, 0x40,
	0x5f, 0x53, 0xb0, 0x5c, 0xbf, 0x4d, 0xb3, 0xc5, 0x70, 0xb5, 0x47, 0xe1, 0xce, 0xc9, 0xc4, 0x7e
};

const uint32_t HASH_TESTING_FULL_BLOCK_4096_LEN = sizeof (HASH_TESTING_FULL_BLOCK_4096);

/**
 * Test input for hashing that spans multiple hash blocks, and is not aligned to the block size.
 */
const uint8_t HASH_TESTING_MULTI_BLOCK_NOT_ALIGNED[] = {
	0xb8, 0x72, 0x7e, 0x61, 0x9a, 0x77, 0xb7, 0x21, 0x52, 0xa4, 0x6d, 0x80, 0xef, 0xe1, 0xc1, 0xad,
	0x34, 0xf1, 0x31, 0xb8, 0x3e, 0x8f, 0x61, 0x49, 0x67, 0xbd, 0x1b, 0x92, 0x6b, 0x59, 0x94, 0x82,
	0xc9, 0xf1, 0xf1, 0x3b, 0x6c, 0xd8, 0x09, 0xc7, 0x8b, 0x79, 0x6d, 0x06, 0xce, 0xec, 0xa6, 0xeb,
	0xb2, 0xc7, 0xbd, 0xe8, 0x2e, 0x37, 0x01, 0xa7, 0x97, 0x4f, 0x04, 0xfb, 0xc1, 0x9f, 0xe7, 0x16,
	0x67, 0x09, 0xd7, 0xfc, 0xcc, 0xd0, 0xd8, 0x38, 0xa3, 0xf2, 0xc1, 0xcd, 0x2c, 0xb8, 0x88, 0x6f,
	0xa1, 0x8b, 0xc0, 0xf3, 0xd0, 0x09, 0x60, 0x05, 0x09, 0x58, 0xc6, 0x19, 0x3a, 0xba, 0xfc, 0xa4,
	0x59, 0x62, 0x39, 0x8b, 0x02, 0x87, 0xab, 0xdb, 0x62, 0xb6, 0x73, 0xbc, 0x53, 0x6c, 0xf2, 0xa0,
	0xc8, 0xe4, 0x43, 0xc0, 0x6c, 0x2e, 0x08, 0xc9, 0x86, 0x81, 0x6a, 0xd2, 0x20, 0xd2, 0x5b, 0x92,
	0x68, 0xa5, 0x1e, 0xd0, 0x56, 0x24, 0x0a, 0x1a, 0x8f, 0x6e, 0x8b, 0xba, 0x8a, 0x31, 0x69, 0xe6,
	0xf1, 0x7b, 0x4d, 0x37, 0x4a, 0xcd, 0x81, 0x5d, 0xd6, 0x72, 0xf7, 0x10, 0xb9, 0x0e, 0x8d, 0x49,
	0x5c, 0x7a, 0x8f, 0xb3, 0x10, 0xcf, 0x7d, 0x5c, 0xf4, 0xc1, 0x0f, 0xb1, 0x18, 0x2f, 0x77, 0xa9,
	0xe2, 0xf7, 0xe6, 0x40, 0xb1, 0x0f, 0x51, 0x27, 0xc1, 0xd2, 0x75, 0xba, 0x4f, 0x97, 0x19, 0x32,
	0xfd, 0x88, 0x93, 0x1c, 0x77, 0xb2, 0x8d, 0x0a, 0x57, 0x58, 0x09, 0x88, 0x46, 0x8d, 0xa3, 0x51,
	0x64, 0x02, 0x16, 0xc3, 0xeb, 0x1c, 0x02, 0x91, 0x0f, 0x49, 0xed, 0xb8, 0x28, 0x95, 0x87, 0xb4,
	0x12, 0x78, 0x32, 0xf3, 0xd4, 0xf2, 0xc1, 0x8a, 0x81, 0xda, 0x80, 0x27, 0x5c, 0x74, 0x75, 0x46,
	0x3f, 0x41, 0xe6, 0xa8, 0x3e, 0x1b, 0x1c, 0x01, 0x87, 0x81, 0x66, 0xf2, 0x8c, 0x2f, 0x60, 0x36,
	0x65, 0xf1, 0x74, 0x20, 0x6f, 0xba, 0xa2, 0x45, 0x3a, 0xf0, 0x7d, 0x76, 0xa2, 0x0b, 0x76, 0xf1,
	0x3b, 0x5e, 0x5d, 0xd7, 0xf3, 0x34, 0x25, 0xe1, 0xf2, 0x1f, 0xe8, 0x4f, 0xc5, 0x8d, 0x2a, 0x22,
	0xbc, 0x9c, 0x62, 0x8b, 0x90, 0x30, 0xb7, 0xa3, 0x49, 0x42, 0x07, 0x5c, 0x5f, 0x7b, 0x2d, 0xb8,
	0x20, 0x01, 0x84, 0x39, 0x51, 0x91, 0xa7, 0x98, 0x18, 0xce, 0x7b, 0xba, 0x1a, 0xd8, 0x70, 0xdf,
	0xe0, 0x21, 0x03, 0x1d, 0x7f, 0x7c, 0x88, 0x0d, 0x78, 0x77, 0x26, 0xc4, 0xdd, 0xeb, 0x23, 0x04,
	0xb5, 0xd1, 0x61, 0xb4, 0xa2, 0x57, 0x29, 0x8e, 0xc1, 0x34, 0x28, 0x18, 0xd2, 0x38, 0xb7, 0xd5,
	0x99, 0x27, 0x60, 0xbc, 0x83, 0xc7, 0x9d, 0xe9, 0x8d, 0x38, 0xe2, 0x93, 0x62, 0x84, 0xde, 0x3e,
	0xc3, 0x77, 0xff, 0x31, 0x2c, 0xb1, 0x34, 0x2b, 0xb5, 0xf9, 0xf6, 0x52, 0x36, 0xd4, 0x89, 0x6c,
	0xae, 0x56, 0x7f, 0x51, 0xe6, 0x39, 0x7f, 0xa0, 0x51, 0x2c, 0x44, 0xb2, 0x37, 0x6d, 0xe8, 0xcc,
	0x12, 0x9a, 0x63, 0x99, 0x39, 0xc5, 0x4f, 0xd7, 0xbb, 0xc6, 0xee, 0x50, 0x8e, 0xd5, 0x6d, 0x0c,
	0xe9, 0x58, 0x6a, 0xc5, 0xee, 0xf9, 0xb5, 0x9b, 0x8c, 0xfc, 0x53, 0x09, 0xa4, 0xcf, 0xc9, 0x18,
	0x6a, 0xe3, 0x97, 0xd2, 0x0f, 0xbb, 0x02, 0xfa, 0x9d, 0x43, 0x16, 0xfa, 0x22, 0x62, 0xec, 0x1d,
	0x10, 0xd2, 0x29, 0xfe, 0xe4, 0x30, 0xc7, 0x41, 0x06, 0x4f, 0x18, 0x80, 0xf0, 0xd2, 0x07, 0x88,
	0x93, 0xfa, 0xa2, 0xc6, 0xf6, 0xbc, 0xd5, 0xfc, 0x21, 0x17, 0x78, 0x38, 0x39, 0xa4, 0x8d, 0x07,
	0xec, 0x6f, 0xc2, 0xe6, 0x10, 0x05, 0x3e, 0xf9, 0x86, 0xce, 0x99, 0x00, 0x65, 0x9d, 0x2c, 0x86,
	0x54, 0x86, 0x8c, 0x5b, 0x38, 0xf0, 0x51, 0x45, 0x10, 0xea, 0x1c, 0xf3, 0x1c, 0xc3, 0xd8, 0x32,
	0x45, 0xd4, 0x3f, 0x64, 0xb9, 0xa1, 0xa0, 0x2d, 0xd6, 0x21, 0xe0, 0x6f, 0x49, 0x59, 0xc0, 0x79,
	0x77, 0x30, 0x5d, 0x7b, 0x1c, 0x7e, 0xfd, 0x3d, 0x31, 0x66, 0x08, 0x11, 0x14, 0xe6, 0x55, 0x07,
	0xe3, 0xac, 0xa7, 0x5f, 0x28, 0x2b, 0x78, 0x44, 0xbc, 0xef, 0xf5, 0xb7, 0xe5, 0x2d, 0x49, 0xc9,
	0xc2, 0x9f, 0x1e, 0x0d, 0xe9, 0x8e, 0x61, 0x4d, 0x4e, 0x31, 0x46, 0x7c, 0x67, 0x35, 0x8d, 0xec,
	0x8d, 0x9d, 0x03, 0xc1, 0xa6, 0xcc, 0x4b, 0xa6, 0x01, 0xe0, 0xde, 0xbe, 0x81, 0x42, 0x51, 0xdd,
	0xfe, 0x7b, 0xd7, 0xf9, 0xe8, 0x4a, 0x06, 0xdb, 0x2d, 0xf3, 0xde, 0x1a, 0x5d, 0xd9, 0x07, 0x4a,
	0x0d, 0x4f, 0x5a, 0x71, 0x79, 0xac, 0xa3, 0xba, 0x6d, 0x9d, 0xa5, 0x6e, 0x65, 0xc0, 0x5f, 0x1f,
	0xf3, 0x6e, 0x8e, 0x27, 0x61, 0xd8, 0x73, 0x51, 0x97, 0x55, 0xd6, 0xd5, 0x40, 0xfa, 0x4b, 0x8a,
	0x29, 0x6c, 0xb4, 0x57, 0xe9, 0xf2, 0x07, 0xea, 0xc7, 0xce, 0x52, 0xad, 0xd8, 0xce, 0xfc, 0xf6,
	0x68, 0x1e, 0x4d, 0x7f, 0x9b, 0x60, 0x30, 0x15, 0x54, 0xfe, 0x38, 0x94, 0x56, 0xbf, 0xe2, 0x12,
	0xaa, 0x99, 0x1a, 0x5b, 0x40, 0xc7, 0x00, 0x9e, 0xd9, 0x1b, 0xeb, 0x65, 0x23, 0x94, 0xae, 0xca,
	0x26, 0x33, 0x1b, 0xe8, 0xe0, 0x0b, 0xc6, 0x91, 0x2c, 0x98, 0x0c, 0x3f, 0xe9, 0x51, 0x53, 0x4c,
	0x57, 0x80, 0x92, 0x65, 0xc4, 0x52, 0x15, 0x3c, 0x69, 0x2a, 0x7a, 0x7d, 0x8f, 0x3b, 0x00, 0x04,
	0xf6, 0x56, 0x01, 0x4d, 0x76, 0x00, 0xbc, 0x2b, 0xe7, 0xc8, 0x58, 0xbd, 0x3f, 0xd8, 0x26, 0x9e,
	0xfa, 0xc9, 0x27, 0x5d, 0xbf, 0xbc, 0xce, 0x2d, 0x40, 0xa6, 0x06, 0xdd, 0x62, 0xeb, 0x77, 0x0a,
	0x9e, 0x2f, 0x05, 0x93, 0xa6, 0x68, 0x9a, 0x4d, 0x4c, 0x38, 0x26, 0xf8, 0xa0, 0x7b, 0xe4, 0x72,
	0x59, 0x1c, 0xde, 0x2b, 0x77, 0x2c, 0xb3, 0xd9, 0x26, 0x35, 0x98, 0x6d, 0xe4, 0xcb, 0x9d, 0x45,
	0xe6, 0x65, 0x32, 0xa3, 0xb8, 0x6b, 0xe9, 0x5e, 0x25, 0x90, 0x7d, 0xd7, 0x56, 0x62, 0x14, 0x2f,
	0x3e, 0x1f, 0xc1, 0xb7, 0x35, 0xcb, 0x4d, 0xa8, 0xe2, 0x7f, 0x37, 0x15, 0x5f, 0x04, 0xf9, 0x1d,
	0x98, 0xa1, 0x8d, 0x65, 0xf4, 0x30, 0x30, 0xc6, 0x38, 0x77, 0x66, 0x42, 0xa8, 0xb6, 0x3e, 0x3d,
	0x6f, 0x7d, 0xd7, 0xe9, 0x40, 0xc0, 0x23, 0x03, 0x3e, 0x2d, 0xeb, 0xbd, 0x19, 0xbd, 0x13, 0xfb,
	0x7a, 0x8a, 0x20, 0xc1, 0xa2, 0xe0, 0xf7, 0xec, 0x4e, 0x96, 0xe7, 0x21, 0xdd, 0x9f, 0xea, 0x04,
	0xb4, 0xdc, 0x28, 0xaa, 0xe2, 0x34, 0xbd, 0x50, 0x00, 0xe7, 0xbc, 0x4d, 0x5b, 0x1f, 0x74, 0x45,
	0x56, 0xc9, 0xf2, 0xa0, 0x09, 0xa2, 0xc7, 0x3a, 0x2e, 0x95, 0x0b, 0x5c, 0x3e, 0x44, 0xa1, 0xec,
	0xd7, 0xe5, 0xbd, 0xe0, 0x61, 0x4f, 0xa4, 0xf8, 0xf1, 0x54, 0xb3, 0xad, 0x6d, 0x52, 0xa3, 0x65,
	0xf2, 0x05, 0x0b, 0xe8, 0x72, 0x9f, 0x26, 0x17
};

const uint32_t HASH_TESTING_MULTI_BLOCK_NOT_ALIGNED_LEN =
	sizeof (HASH_TESTING_MULTI_BLOCK_NOT_ALIGNED);

/**
 * SHA1 hash of "Test".
 */
const uint8_t SHA1_TEST_HASH[] = {
	0x64, 0x0a, 0xb2, 0xba, 0xe0, 0x7b, 0xed, 0xc4, 0xc1, 0x63, 0xf6, 0x79, 0xa7, 0x46, 0xf7, 0xab,
	0x7f, 0xb5, 0xd1, 0xfa
};

/**
 * SHA1 hash of "TestTest".
 */
const uint8_t SHA1_TEST_TEST_HASH[] = {
	0x7d, 0xf7, 0x1b, 0x73, 0x81, 0x9f, 0x2e, 0x0c, 0x61, 0x83, 0x39, 0xa2, 0xa4, 0x53, 0x08, 0xa9,
	0x77, 0x5e, 0x3c, 0x6f
};

/**
 * SHA1 hash of "Test2".
 */
const uint8_t SHA1_TEST2_HASH[] = {
	0x2b, 0x84, 0xf6, 0x21, 0xc0, 0xfd, 0x4b, 0xa8, 0xbd, 0x51, 0x4c, 0x5c, 0x43, 0xab, 0x9a, 0x89,
	0x7c, 0x8c, 0x01, 0x4e
};

/**
 * SHA1 hash of "Nope".
 */
const uint8_t SHA1_NOPE_HASH[] = {
	0x2f, 0x35, 0xce, 0xbe, 0xbc, 0xa8, 0xfe, 0x85, 0x91, 0xe4, 0x48, 0x7f, 0xac, 0xe7, 0xcc, 0x9e,
	0x00, 0x40, 0x5a, 0x9d
};

/**
 * SHA1 hash of "Bad".
 */
const uint8_t SHA1_BAD_HASH[] = {
	0xbe, 0x7e, 0x10, 0xd1, 0xc5, 0xdd, 0x2a, 0xd7, 0x7f, 0x6d, 0x5a, 0x61, 0x73, 0x72, 0xa7, 0xbf,
	0x01, 0x3c, 0xb7, 0xbf
};

/**
 * SHA1 hash of an empty buffer.
 */
const uint8_t SHA1_EMPTY_BUFFER_HASH[] = {
	0xda, 0x39, 0xa3, 0xee, 0x5e, 0x6b, 0x4b, 0x0d, 0x32, 0x55, 0xbf, 0xef, 0x95, 0x60, 0x18, 0x90,
	0xaf, 0xd8, 0x07, 0x09
};

/**
 * SHA1 hash of a 32 byte buffer filled with zeros.
 */
const uint8_t SHA1_ZERO_BUFFER_HASH[] = {
	0xde, 0x8a, 0x84, 0x7b, 0xff, 0x8c, 0x34, 0x3d, 0x69, 0xb8, 0x53, 0xa2, 0x15, 0xe6, 0xee, 0x77,
	0x5e, 0xf2, 0xef, 0x96
};

/**
 * SHA1 hash of HASH_TESTING_PARTIAL_BLOCK_440.
 */
const uint8_t SHA1_PARTIAL_BLOCK_440_HASH[] = {
	0x28, 0x16, 0xc0, 0x1a, 0xa3, 0xfa, 0x99, 0x09, 0xeb, 0xdd, 0x0d, 0x16, 0x23, 0xdf, 0x45, 0x01,
	0x4d, 0x37, 0xb7, 0xc8
};

/**
 * SHA1 hash of HASH_TESTING_PARTIAL_BLOCK_448.
 */
const uint8_t SHA1_PARTIAL_BLOCK_448_HASH[] = {
	0xa1, 0xe9, 0x67, 0xae, 0xc5, 0xcd, 0xd4, 0x49, 0x39, 0xed, 0x96, 0xc7, 0xcb, 0xdf, 0x10, 0x1d,
	0xfa, 0xa7, 0xd2, 0xeb
};

/**
 * SHA1 hash of HASH_TESTING_PARTIAL_BLOCK_480.
 */
const uint8_t SHA1_PARTIAL_BLOCK_480_HASH[] = {
	0x36, 0x13, 0xee, 0x44, 0x4b, 0xb1, 0xb3, 0x66, 0xeb, 0x31, 0x3c, 0x3e, 0x4d, 0x14, 0x48, 0x47,
	0x6e, 0xb4, 0x68, 0x69
};

/**
 * SHA1 hash of HASH_TESTING_FULL_BLOCK_512.
 */
const uint8_t SHA1_FULL_BLOCK_512_HASH[] = {
	0xa4, 0x8a, 0xad, 0x53, 0xd0, 0x9b, 0x0a, 0x58, 0xc7, 0x26, 0x6a, 0x29, 0x40, 0x66, 0x73, 0xca,
	0xa0, 0x2f, 0xda, 0x17
};

/**
 * SHA1 hash of HASH_TESTING_PARTIAL_BLOCK_952.
 */
const uint8_t SHA1_PARTIAL_BLOCK_952_HASH[] = {
	0x72, 0xeb, 0xef, 0x47, 0x1e, 0xe2, 0x7d, 0xb4, 0x1e, 0xcb, 0x61, 0x27, 0x6b, 0xf5, 0xe6, 0x33,
	0x50, 0xee, 0x1c, 0x5e
};

/**
 * SHA1 hash of HASH_TESTING_PARTIAL_BLOCK_960.
 */
const uint8_t SHA1_PARTIAL_BLOCK_960_HASH[] = {
	0x4d, 0x38, 0x87, 0x95, 0x08, 0xd7, 0x27, 0x35, 0x90, 0xd6, 0xec, 0x86, 0x1d, 0x33, 0x91, 0xf7,
	0xd4, 0x15, 0x4d, 0xf7
};

/**
 * SHA1 hash of HASH_TESTING_PARTIAL_BLOCK_992.
 */
const uint8_t SHA1_PARTIAL_BLOCK_992_HASH[] = {
	0x8b, 0xc6, 0x74, 0x67, 0x8c, 0x62, 0xfe, 0xbe, 0xb3, 0xaf, 0x38, 0x84, 0x62, 0x4b, 0x97, 0x4d,
	0x31, 0x8f, 0x78, 0x76
};

/**
 * SHA1 hash of HASH_TESTING_FULL_BLOCK_1024.
 */
const uint8_t SHA1_FULL_BLOCK_1024_HASH[] = {
	0x53, 0xb4, 0x9e, 0x94, 0x2a, 0xf7, 0x13, 0x5a, 0xfa, 0x20, 0x73, 0xb4, 0x98, 0x2e, 0xb3, 0xb4,
	0x49, 0x26, 0x6d, 0x02
};

/**
 * SHA1 hash of HASH_TESTING_FULL_BLOCK_2048.
 */
const uint8_t SHA1_FULL_BLOCK_2048_HASH[] = {
	0xb3, 0x4b, 0x5d, 0xc0, 0xe3, 0xf7, 0x25, 0x4c, 0x1c, 0xa6, 0xbb, 0x37, 0xa9, 0xd8, 0x06, 0xd1,
	0x14, 0x9f, 0xb5, 0x67
};

/**
 * SHA1 hash of HASH_TESTING_FULL_BLOCK_4096.
 */
const uint8_t SHA1_FULL_BLOCK_4096_HASH[] = {
	0x60, 0x93, 0xc8, 0x53, 0xf6, 0xc2, 0x24, 0x69, 0x5b, 0x43, 0x60, 0x1d, 0xa5, 0xc9, 0x26, 0xae,
	0x93, 0x39, 0xc6, 0x4b
};

/**
 * SHA1 hash of HASH_TESTING_MULTI_BLOCK_NOT_ALIGNED.
 */
const uint8_t SHA1_MULTI_BLOCK_NOT_ALIGNED_HASH[] = {
	0x9e, 0x92, 0x17, 0x2c, 0x45, 0xf8, 0xb8, 0xd8, 0x33, 0x58, 0xd1, 0xe5, 0xc0, 0x69, 0x84, 0x93,
	0xb0, 0x9f, 0xd9, 0xcb
};

/**
 * Test key to use for SHA1 HMAC.  The key length is equal to SHA1_HASH_LENGTH.
 */
const uint8_t SHA1_HMAC_KEY[] = {
	0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0a, 0x0b, 0x0c, 0x0d, 0x0e, 0x0f,
	0x10, 0x11, 0x12, 0x13
};

/**
 * Test key to use for SHA1 HMAC.  The key length is equal to SHA1_BLOCK_SIZE.
 */
const uint8_t SHA1_HMAC_BLOCK_KEY[] = {
	0x16, 0x35, 0x92, 0xfb, 0x06, 0x2c, 0xb8, 0x4f, 0x84, 0x71, 0x57, 0x60, 0x3a, 0x0a, 0x66, 0x5a,
	0x37, 0xd1, 0xf0, 0x56, 0x9c, 0x3a, 0x4d, 0x9a, 0xf4, 0x83, 0xb0, 0xf1, 0x66, 0xa7, 0x7e, 0xf1,
	0xc4, 0x1c, 0xc8, 0x04, 0xfd, 0x29, 0x79, 0x2d, 0x1a, 0xaf, 0xd9, 0x01, 0x31, 0x9d, 0x79, 0x24,
	0x1b, 0x1b, 0x06, 0x2a, 0x88, 0x2d, 0x87, 0x7c, 0xde, 0x2b, 0x76, 0xa1, 0xcd, 0x45, 0xcb, 0x0a
};

/**
 * SHA1 HMAC of "Test" using SHA1_HMAC_KEY.
 */
const uint8_t SHA1_TEST_HMAC[] = {
	0xcf, 0xed, 0x6f, 0x69, 0x6a, 0xf6, 0x9d, 0x06, 0xbc, 0xe0, 0xe7, 0x1e, 0x43, 0xe6, 0x69, 0x29,
	0x71, 0x7e, 0x35, 0x0f
};

/**
 * SHA1 HMAC of HASH_TESTING_FULL_BLOCK_1024 using SHA1_HMAC_KEY.
 */
const uint8_t SHA1_FULL_BLOCK_1024_HMAC[] = {
	0xfb, 0x39, 0xd4, 0x29, 0xad, 0x5b, 0xeb, 0xfb, 0xeb, 0x65, 0xab, 0xf5, 0x0e, 0xf3, 0x39, 0xd3,
	0xc1, 0x29, 0x1e, 0x7e
};

/**
 * SHA1 HMAC of HASH_TESTING_FULL_BLOCK_4096 using SHA1_HMAC_BLOCK_KEY.
 */
const uint8_t SHA1_FULL_BLOCK_4096_BLOCK_KEY_HMAC[] = {
	0x2f, 0xbc, 0xb7, 0xf7, 0x77, 0x38, 0x5a, 0xae, 0x5c, 0xf5, 0x67, 0x8a, 0x26, 0x48, 0x05, 0xc6,
	0x3f, 0xd6, 0x72, 0x98
};

/**
 * SHA1 hash of HMAC_KAT_VECTORS_CALCULATE_KEY.
 */
const uint8_t SHA1_HMAC_KAT_CALCULATE_KEY_HASH[] = {
	0xbc, 0xa3, 0x89, 0xa0, 0xdf, 0x8a, 0xde, 0x31, 0x1c, 0xc4, 0xd4, 0xd6, 0x04, 0x7b, 0xe8, 0xaf,
	0xfe, 0xd7, 0x78, 0xb9
};

/**
 * SHA256 hash of "Test"
 */
const uint8_t SHA256_TEST_HASH[] = {
	0x53, 0x2e, 0xaa, 0xbd, 0x95, 0x74, 0x88, 0x0d, 0xbf, 0x76, 0xb9, 0xb8, 0xcc, 0x00, 0x83, 0x2c,
	0x20, 0xa6, 0xec, 0x11, 0x3d, 0x68, 0x22, 0x99, 0x55, 0x0d, 0x7a, 0x6e, 0x0f, 0x34, 0x5e, 0x25
};

/**
 * SHA256 hash of "TestTest"
 */
const uint8_t SHA256_TEST_TEST_HASH[] = {
	0xa8, 0xd6, 0x27, 0xd9, 0x3f, 0x51, 0x8e, 0x90, 0x96, 0xb6, 0xf4, 0x0e, 0x36, 0xd2, 0x7b, 0x76,
	0x60, 0xfa, 0x26, 0xd3, 0x18, 0xef, 0x1a, 0xdc, 0x43, 0xda, 0x75, 0x0e, 0x49, 0xeb, 0xe4, 0xbe
};

/**
 * SHA256 hash of "Test2"
 */
const uint8_t SHA256_TEST2_HASH[] = {
	0x32, 0xe6, 0xe1, 0xe1, 0x34, 0xf9, 0xcc, 0x8f, 0x14, 0xb0, 0x59, 0x25, 0x66, 0x7c, 0x11, 0x8d,
	0x19, 0x24, 0x4a, 0xeb, 0xce, 0x44, 0x2d, 0x6f, 0xec, 0xd2, 0xac, 0x38, 0xcd, 0xc9, 0x76, 0x49
};

/**
 * SHA256 hash of "Nope"
 */
const uint8_t SHA256_NOPE_HASH[] = {
	0x7b, 0xf1, 0x55, 0x67, 0x08, 0xef, 0xd0, 0xd8, 0xaf, 0x60, 0x50, 0xf5, 0x92, 0xae, 0x25, 0xa5,
	0xb6, 0xfd, 0xd4, 0xf7, 0xd1, 0x5a, 0xe3, 0xed, 0x6d, 0xeb, 0x43, 0xb5, 0xa2, 0x6c, 0x6f, 0xf8
};

/**
 * SHA256 hash of "Bad"
 */
const uint8_t SHA256_BAD_HASH[] = {
	0x6f, 0xe7, 0xd7, 0x11, 0x2c, 0xaa, 0xba, 0x1b, 0x1b, 0xc7, 0xbf, 0xa6, 0x56, 0x97, 0x4a, 0xc4,
	0x01, 0x6c, 0xc5, 0x25, 0xa7, 0x28, 0x61, 0x17, 0x49, 0x4f, 0x5b, 0x29, 0xdf, 0xec, 0x1f, 0x77
};

/**
 * SHA256 hash of an empty buffer.
 */
const uint8_t SHA256_EMPTY_BUFFER_HASH[] = {
	0xe3, 0xb0, 0xc4, 0x42, 0x98, 0xfc, 0x1c, 0x14, 0x9a, 0xfb, 0xf4, 0xc8, 0x99, 0x6f, 0xb9, 0x24,
	0x27, 0xae, 0x41, 0xe4, 0x64, 0x9b, 0x93, 0x4c, 0xa4, 0x95, 0x99, 0x1b, 0x78, 0x52, 0xb8, 0x55
};

/**
 * SHA256 hash of a 32 byte buffer filled with zeros.
 */
const uint8_t SHA256_ZERO_BUFFER_HASH[] = {
	0x66, 0x68, 0x7a, 0xad, 0xf8, 0x62, 0xbd, 0x77, 0x6c, 0x8f, 0xc1, 0x8b, 0x8e, 0x9f, 0x8e, 0x20,
	0x08, 0x97, 0x14, 0x85, 0x6e, 0xe2, 0x33, 0xb3, 0x90, 0x2a, 0x59, 0x1d, 0x0d, 0x5f, 0x29, 0x25
};

/**
 * SHA256 hash of HASH_TESTING_PARTIAL_BLOCK_440.
 */
const uint8_t SHA256_PARTIAL_BLOCK_440_HASH[] = {
	0x65, 0x95, 0xa2, 0xef, 0x53, 0x7a, 0x69, 0xba, 0x85, 0x83, 0xdf, 0xbf, 0x7f, 0x5b, 0xec, 0x0a,
	0xb1, 0xf9, 0x3c, 0xe4, 0xc8, 0xee, 0x19, 0x16, 0xef, 0xf4, 0x4a, 0x93, 0xaf, 0x57, 0x49, 0xc4
};

/**
 * SHA256 hash of HASH_TESTING_PARTIAL_BLOCK_448.
 */
const uint8_t SHA256_PARTIAL_BLOCK_448_HASH[] = {
	0xcf, 0xb8, 0x8d, 0x6f, 0xaf, 0x2d, 0xe3, 0xa6, 0x9d, 0x36, 0x19, 0x5a, 0xce, 0xc2, 0xe2, 0x55,
	0xe2, 0xaf, 0x2b, 0x7d, 0x93, 0x39, 0x97, 0xf3, 0x48, 0xe0, 0x9f, 0x6c, 0xe5, 0x75, 0x83, 0x60
};

/**
 * SHA256 hash of HASH_TESTING_PARTIAL_BLOCK_480.
 */
const uint8_t SHA256_PARTIAL_BLOCK_480_HASH[] = {
	0x0b, 0x66, 0xc8, 0xb4, 0xfe, 0xfe, 0xbc, 0x8d, 0xc7, 0xda, 0x0b, 0xbe, 0xdc, 0x11, 0x14, 0xf2,
	0x28, 0xaa, 0x63, 0xc3, 0x7d, 0x5c, 0x30, 0xe9, 0x1a, 0xb5, 0x00, 0xf3, 0xea, 0xdf, 0xce, 0xc5
};

/**
 * SHA256 hash of HASH_TESTING_FULL_BLOCK_512.
 */
const uint8_t SHA256_FULL_BLOCK_512_HASH[] = {
	0x42, 0xe6, 0x1e, 0x17, 0x4f, 0xbb, 0x38, 0x97, 0xd6, 0xdd, 0x6c, 0xef, 0x3d, 0xd2, 0x80, 0x2f,
	0xe6, 0x7b, 0x33, 0x19, 0x53, 0xb0, 0x61, 0x14, 0xa6, 0x5c, 0x77, 0x28, 0x59, 0xdf, 0xc1, 0xaa
};

/**
 * SHA256 hash of HASH_TESTING_PARTIAL_BLOCK_952.
 */
const uint8_t SHA256_PARTIAL_BLOCK_952_HASH[] = {
	0x25, 0x93, 0xb7, 0x91, 0xae, 0x34, 0x4f, 0x63, 0x0c, 0xfd, 0x4f, 0x29, 0xec, 0xa2, 0x9c, 0x3a,
	0x81, 0x67, 0x0a, 0x8a, 0xa7, 0xc9, 0x60, 0x9f, 0x2c, 0x79, 0x8f, 0xb0, 0x85, 0x20, 0x46, 0x78
};

/**
 * SHA256 hash of HASH_TESTING_PARTIAL_BLOCK_960.
 */
const uint8_t SHA256_PARTIAL_BLOCK_960_HASH[] = {
	0xc4, 0xaf, 0x25, 0xdd, 0x3f, 0x8a, 0x14, 0x62, 0xcf, 0x28, 0xcb, 0xee, 0x39, 0x12, 0x59, 0x96,
	0x7a, 0x52, 0xe9, 0x3f, 0x9f, 0x85, 0x73, 0x82, 0x6d, 0xdc, 0x70, 0x05, 0xca, 0xee, 0xb0, 0x68
};

/**
 * SHA256 hash of HASH_TESTING_PARTIAL_BLOCK_992.
 */
const uint8_t SHA256_PARTIAL_BLOCK_992_HASH[] = {
	0x58, 0x60, 0xe4, 0x42, 0x8f, 0xdc, 0x69, 0xd2, 0x50, 0x7f, 0xa0, 0x22, 0x86, 0xb0, 0x17, 0xf2,
	0xe3, 0xe1, 0x83, 0xe8, 0xa3, 0x18, 0x32, 0xf4, 0x10, 0x32, 0x81, 0x64, 0xd9, 0x60, 0x18, 0xef
};

/**
 * SHA256 hash of HASH_TESTING_FULL_BLOCK_1024.
 */
const uint8_t SHA256_FULL_BLOCK_1024_HASH[] = {
	0x8e, 0xc0, 0x19, 0x28, 0x9b, 0x97, 0xa9, 0x6b, 0x06, 0xac, 0x2a, 0x7f, 0x04, 0xe1, 0x10, 0x8b,
	0xc4, 0xe6, 0x52, 0x7f, 0x50, 0xdd, 0xd1, 0x2a, 0x25, 0x27, 0x2a, 0x7e, 0x9a, 0xe6, 0x54, 0x92
};

/**
 * SHA256 hash of HASH_TESTING_FULL_BLOCK_2048.
 */
const uint8_t SHA256_FULL_BLOCK_2048_HASH[] = {
	0x28, 0x02, 0x04, 0x1f, 0x7f, 0x81, 0xdc, 0xc7, 0xfd, 0xc0, 0x82, 0x88, 0x18, 0xc3, 0x34, 0x14,
	0x0c, 0x33, 0x08, 0x21, 0xa7, 0x84, 0x76, 0xa0, 0x75, 0x59, 0xd8, 0x39, 0x6f, 0xb8, 0xbb, 0x42
};

/**
 * SHA256 hash of HASH_TESTING_FULL_BLOCK_4096.
 */
const uint8_t SHA256_FULL_BLOCK_4096_HASH[] = {
	0xf2, 0x81, 0x95, 0xf3, 0x67, 0x8e, 0x0d, 0x2e, 0x6f, 0x9f, 0x16, 0x49, 0x50, 0x89, 0xcb, 0x6c,
	0xaf, 0xa3, 0x09, 0xf6, 0x65, 0xc3, 0x48, 0x92, 0x7d, 0xc8, 0x50, 0xda, 0x96, 0xc8, 0x39, 0xec
};

/**
 * SHA256 hash of HASH_TESTING_MULTI_BLOCK_NOT_ALIGNED.
 */
const uint8_t SHA256_MULTI_BLOCK_NOT_ALIGNED_HASH[] = {
	0xf4, 0xce, 0x13, 0xdf, 0x39, 0x13, 0x2d, 0x40, 0x28, 0x01, 0x19, 0xaf, 0xe3, 0xa7, 0xc1, 0x68,
	0xb5, 0xf9, 0xd8, 0xef, 0xfa, 0x4d, 0x4f, 0xcf, 0xec, 0xcd, 0x49, 0x62, 0x3c, 0x9a, 0xba, 0x44
};

/**
 * Test key to use for SHA256 HMAC.  The key length is equal to SHA256_HASH_LENGTH.
 */
const uint8_t SHA256_HMAC_KEY[] = {
	0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0a, 0x0b, 0x0c, 0x0d, 0x0e, 0x0f,
	0x10, 0x11, 0x12, 0x13, 0x14, 0x15, 0x16, 0x17, 0x18, 0x19, 0x1a, 0x1b, 0x1c, 0x1d, 0x1e, 0x1f
};

/**
 * Test key to use for SHA256 HMAC.  The key length is equal to SHA256_BLOCK_SIZE.
 */
const uint8_t SHA256_HMAC_BLOCK_KEY[] = {
	0xe0, 0x5a, 0x1b, 0xc5, 0x1f, 0xd4, 0x97, 0xc3, 0xb8, 0x7f, 0x6a, 0x45, 0x3c, 0x50, 0x5d, 0xf3,
	0x65, 0xd0, 0x7e, 0x4b, 0x55, 0x6a, 0x63, 0x11, 0xbe, 0x63, 0x7b, 0xf3, 0xbe, 0xa1, 0x91, 0x65,
	0x9e, 0x9d, 0x82, 0xcc, 0x38, 0xae, 0x16, 0x20, 0x32, 0x6e, 0x05, 0xf1, 0x7e, 0xb0, 0x66, 0x85,
	0x07, 0x41, 0x92, 0xb6, 0x68, 0xbf, 0xb9, 0xf6, 0x9e, 0x65, 0x9a, 0x92, 0x56, 0x20, 0x26, 0x1e
};

/**
 * SHA256 HMAC of "Test" using SHA256_HMAC_KEY.
 */
const uint8_t SHA256_TEST_HMAC[] = {
	0xbe, 0xac, 0xa5, 0x36, 0x3b, 0xec, 0xae, 0x40, 0xda, 0x59, 0x28, 0x57, 0x79, 0x4e, 0x38, 0x79,
	0x6e, 0x86, 0xd2, 0x9a, 0x7a, 0x23, 0xdf, 0x5e, 0x1c, 0x62, 0xb5, 0xd0, 0xa5, 0xba, 0x2e, 0x67
};

/**
 * SHA256 HMAC of HASH_TESTING_FULL_BLOCK_1024 using SHA256_HMAC_KEY.
 */
const uint8_t SHA256_FULL_BLOCK_1024_HMAC[] = {
	0x2a, 0xcb, 0x2d, 0xb4, 0x39, 0x40, 0xdd, 0x1b, 0x0f, 0xfb, 0x87, 0x5b, 0x35, 0x3c, 0xc6, 0x5e,
	0x41, 0x81, 0xb8, 0xa8, 0x83, 0x7c, 0x5e, 0x0a, 0xb3, 0x39, 0x96, 0x8b, 0x19, 0x2f, 0x96, 0x76
};

/**
 * SHA256 HMAC of HASH_TESTING_FULL_BLOCK_4096 using SHA256_HMAC_BLOCK_KEY.
 */
const uint8_t SHA256_FULL_BLOCK_4096_BLOCK_KEY_HMAC[] = {
	0x65, 0xed, 0xf3, 0xf0, 0x0d, 0xe8, 0xcd, 0x16, 0x07, 0x49, 0xc5, 0xd8, 0xfb, 0x38, 0x9b, 0x09,
	0x4b, 0x37, 0x4f, 0x95, 0x96, 0x28, 0xb7, 0xe3, 0xd0, 0x72, 0x5d, 0xb2, 0x17, 0x2e, 0xb3, 0x3d
};

/**
 * SHA256 hash of HMAC_KAT_VECTORS_CALCULATE_KEY.
 */
const uint8_t SHA256_HMAC_KAT_CALCULATE_KEY_HASH[] = {
	0x4c, 0x12, 0x90, 0x69, 0x31, 0x9f, 0xf5, 0x30, 0x9f, 0x36, 0xf8, 0xed, 0x31, 0x8e, 0x86, 0xf0,
	0x76, 0x8e, 0xdb, 0xe2, 0x95, 0x6d, 0xf7, 0x69, 0x35, 0x08, 0x81, 0xb6, 0x1a, 0xf7, 0xf0, 0x94
};

/**
 * SHA384 hash of "Test".
 */
const uint8_t SHA384_TEST_HASH[] = {
	0x7b, 0x8f, 0x46, 0x54, 0x07, 0x6b, 0x80, 0xeb, 0x96, 0x39, 0x11, 0xf1, 0x9c, 0xfa, 0xd1, 0xaa,
	0xf4, 0x28, 0x5e, 0xd4, 0x8e, 0x82, 0x6f, 0x6c, 0xde, 0x1b, 0x01, 0xa7, 0x9a, 0xa7, 0x3f, 0xad,
	0xb5, 0x44, 0x6e, 0x66, 0x7f, 0xc4, 0xf9, 0x04, 0x17, 0x78, 0x2c, 0x91, 0x27, 0x05, 0x40, 0xf3
};

/**
 * SHA384 hash of "TestTest".
 */
const uint8_t SHA384_TEST_TEST_HASH[] = {
	0xcc, 0x13, 0x39, 0x93, 0x29, 0xa2, 0xcd, 0x34, 0x3b, 0xaf, 0x57, 0x80, 0xad, 0x94, 0xa2, 0x2f,
	0xb8, 0x26, 0x02, 0x51, 0xf0, 0x4b, 0x6f, 0xfa, 0x8e, 0x11, 0x44, 0x13, 0x44, 0x7e, 0x3f, 0x50,
	0x9a, 0x30, 0x0b, 0x6b, 0x82, 0x9c, 0x7a, 0xbd, 0xaf, 0x98, 0x29, 0x8f, 0x4b, 0x31, 0xf0, 0xfc
};

/**
 * SHA384 hash of "Test2".
 */
const uint8_t SHA384_TEST2_HASH[] = {
	0xc2, 0x50, 0x99, 0x84, 0x5d, 0x75, 0x16, 0x74, 0x51, 0xbc, 0xb2, 0x40, 0x46, 0x9d, 0x91, 0xf0,
	0x83, 0xe9, 0xee, 0xc8, 0x19, 0xf7, 0x58, 0xcd, 0x42, 0xcb, 0x19, 0xb7, 0x33, 0xf1, 0xa0, 0x22,
	0x25, 0xdd, 0xc8, 0x33, 0xcd, 0x50, 0x82, 0x7e, 0x87, 0xf1, 0x09, 0x16, 0x2d, 0x92, 0x24, 0xb5
};

/**
 * SHA384 hash of "Nope".
 */
const uint8_t SHA384_NOPE_HASH[] = {
	0x64, 0xe0, 0xa5, 0x50, 0xe7, 0x2a, 0x1e, 0xa8, 0x0d, 0xcd, 0x8c, 0xb0, 0x8b, 0xf5, 0x69, 0x50,
	0xfe, 0x44, 0x3d, 0xb7, 0x21, 0x5a, 0x6f, 0xae, 0xa7, 0x4b, 0x07, 0x33, 0x2c, 0x29, 0xda, 0x1c,
	0x94, 0xd6, 0x83, 0xbe, 0x7d, 0xc5, 0x91, 0x39, 0x85, 0x35, 0x9b, 0x6e, 0x89, 0xa5, 0x90, 0xbf
};

/**
 * SHA384 hash of "Bad".
 */
const uint8_t SHA384_BAD_HASH[] = {
	0x6c, 0x21, 0xde, 0xea, 0xa2, 0xfb, 0x6e, 0xb7, 0x17, 0xc7, 0xcc, 0xe2, 0x70, 0xbc, 0x14, 0x07,
	0xf1, 0x1c, 0xb1, 0x5a, 0x1a, 0x4e, 0x23, 0x43, 0xb0, 0x3b, 0xb2, 0xd0, 0x4d, 0x95, 0x06, 0x83,
	0xb2, 0xc7, 0x2e, 0x22, 0xf5, 0x1f, 0xac, 0x87, 0x04, 0x17, 0x38, 0x93, 0x3a, 0xc7, 0xc4, 0x37
};

/**
 * SHA384 hash of an empty buffer.
 */
const uint8_t SHA384_EMPTY_BUFFER_HASH[] = {
	0x38, 0xb0, 0x60, 0xa7, 0x51, 0xac, 0x96, 0x38, 0x4c, 0xd9, 0x32, 0x7e, 0xb1, 0xb1, 0xe3, 0x6a,
	0x21, 0xfd, 0xb7, 0x11, 0x14, 0xbe, 0x07, 0x43, 0x4c, 0x0c, 0xc7, 0xbf, 0x63, 0xf6, 0xe1, 0xda,
	0x27, 0x4e, 0xde, 0xbf, 0xe7, 0x6f, 0x65, 0xfb, 0xd5, 0x1a, 0xd2, 0xf1, 0x48, 0x98, 0xb9, 0x5b
};

/**
 * SHA384 hash of a 32 byte buffer filled with zeros.
 */
const uint8_t SHA384_ZERO_BUFFER_HASH[] = {
	0xa3, 0x8f, 0xff, 0x4b, 0xa2, 0x6c, 0x15, 0xe4, 0xac, 0x9c, 0xde, 0x8c, 0x03, 0x10, 0x3a, 0xc8,
	0x90, 0x80, 0xfd, 0x47, 0x54, 0x5f, 0xde, 0x94, 0x46, 0xc8, 0xf1, 0x92, 0x72, 0x9e, 0xab, 0x7b,
	0xd0, 0x3a, 0x4d, 0x5c, 0x31, 0x87, 0xf7, 0x5f, 0xe2, 0xa7, 0x1b, 0x0e, 0xe5, 0x0a, 0x4a, 0x40
};

/**
 * SHA384 hash of HASH_TESTING_PARTIAL_BLOCK_440.
 */
const uint8_t SHA384_PARTIAL_BLOCK_440_HASH[] = {
	0x99, 0xa8, 0x74, 0xc9, 0x24, 0x4f, 0x6c, 0x38, 0x46, 0xfe, 0x00, 0xf5, 0xf9, 0x9e, 0xce, 0x1a,
	0xc8, 0x3a, 0x9d, 0x25, 0x8c, 0xea, 0xdd, 0x72, 0x06, 0x25, 0x3c, 0x7e, 0xef, 0x77, 0xb6, 0x49,
	0x6d, 0x4b, 0xe5, 0x6d, 0xa1, 0xd4, 0xb7, 0x93, 0x0f, 0x19, 0xc2, 0x51, 0xab, 0x82, 0x2c, 0xb8
};

/**
 * SHA384 hash of HASH_TESTING_PARTIAL_BLOCK_448.
 */
const uint8_t SHA384_PARTIAL_BLOCK_448_HASH[] = {
	0x54, 0xa5, 0x99, 0x56, 0x93, 0x44, 0x67, 0x2b, 0xd1, 0xb5, 0x38, 0x1e, 0x46, 0x95, 0xb8, 0x02,
	0x5b, 0x64, 0x8c, 0xcb, 0xc8, 0xff, 0xb4, 0x57, 0x51, 0x90, 0xab, 0x1e, 0x91, 0xa8, 0xe9, 0x36,
	0x06, 0xfc, 0xe7, 0xb8, 0x9d, 0x49, 0x53, 0x1f, 0x44, 0xae, 0x58, 0xfe, 0xf1, 0x26, 0x2b, 0xd3
};

/**
 * SHA384 hash of HASH_TESTING_PARTIAL_BLOCK_480.
 */
const uint8_t SHA384_PARTIAL_BLOCK_480_HASH[] = {
	0x86, 0xdd, 0x35, 0x2b, 0x3f, 0xa7, 0xc6, 0x4e, 0x1e, 0xe1, 0x35, 0xb6, 0x05, 0x28, 0xe4, 0xa4,
	0x0d, 0xe8, 0x67, 0x75, 0xe5, 0x3d, 0x47, 0x27, 0xb1, 0xfc, 0xf0, 0x70, 0xc7, 0x1b, 0xeb, 0xd6,
	0x65, 0xa1, 0x53, 0x5a, 0xaf, 0x1f, 0x66, 0x6f, 0x4f, 0xc4, 0x7c, 0x32, 0x0c, 0xbf, 0x91, 0xe1
};

/**
 * SHA384 hash of HASH_TESTING_FULL_BLOCK_512.
 */
const uint8_t SHA384_FULL_BLOCK_512_HASH[] = {
	0x16, 0xe8, 0xe1, 0xda, 0x9a, 0xa6, 0xae, 0xcf, 0x8f, 0x6b, 0xaa, 0xa9, 0x87, 0x73, 0x85, 0x79,
	0xc0, 0xf6, 0x0e, 0x1f, 0xac, 0x2e, 0x90, 0x01, 0x1d, 0x42, 0xd2, 0x41, 0x9f, 0x15, 0x63, 0x1b,
	0xa1, 0xec, 0x15, 0x9b, 0x38, 0x26, 0x59, 0x6c, 0x28, 0xe7, 0x74, 0x52, 0x48, 0x62, 0xf4, 0x18
};

/**
 * SHA384 hash of HASH_TESTING_PARTIAL_BLOCK_952.
 */
const uint8_t SHA384_PARTIAL_BLOCK_952_HASH[] = {
	0x6b, 0xd9, 0xe1, 0x30, 0x35, 0x79, 0xd8, 0x15, 0xf5, 0x8e, 0x8c, 0x6c, 0x98, 0x55, 0x85, 0x01,
	0x33, 0x25, 0x17, 0x78, 0xa6, 0x32, 0xf7, 0xb3, 0x12, 0xc4, 0xb3, 0x16, 0x3b, 0x29, 0xb5, 0xef,
	0x6c, 0xb9, 0x51, 0x1a, 0x08, 0xa3, 0x1a, 0x23, 0x7d, 0x9a, 0x76, 0x04, 0xaf, 0xbf, 0xa0, 0x56
};

/**
 * SHA384 hash of HASH_TESTING_PARTIAL_BLOCK_960.
 */
const uint8_t SHA384_PARTIAL_BLOCK_960_HASH[] = {
	0xff, 0xa9, 0xe4, 0xe8, 0x56, 0xd0, 0x62, 0x27, 0xc1, 0xcc, 0xb9, 0x59, 0xbe, 0x55, 0x83, 0x09,
	0xcc, 0x10, 0x63, 0x31, 0x73, 0xf4, 0xb6, 0x6c, 0xeb, 0x38, 0x29, 0x23, 0xb5, 0x2b, 0x91, 0x50,
	0xac, 0xfb, 0x08, 0xa7, 0x39, 0x35, 0x00, 0x47, 0x7a, 0x6e, 0xe4, 0x42, 0x5a, 0x82, 0x7e, 0x76
};

/**
 * SHA384 hash of HASH_TESTING_PARTIAL_BLOCK_992.
 */
const uint8_t SHA384_PARTIAL_BLOCK_992_HASH[] = {
	0xb7, 0x5d, 0x92, 0xb5, 0xcd, 0x37, 0x72, 0x84, 0x6f, 0x7b, 0x68, 0x06, 0x4a, 0x35, 0x67, 0xae,
	0x43, 0xe5, 0x01, 0x00, 0x99, 0xf2, 0xb6, 0x49, 0xf3, 0x50, 0x87, 0xe7, 0x59, 0x2a, 0xee, 0xc1,
	0x76, 0x64, 0x6f, 0xc8, 0xc2, 0x62, 0x92, 0x88, 0x94, 0x42, 0x61, 0xcd, 0x35, 0xb5, 0xfc, 0xba
};

/**
 * SHA384 hash of HASH_TESTING_FULL_BLOCK_1024.
 */
const uint8_t SHA384_FULL_BLOCK_1024_HASH[] = {
	0x12, 0xb6, 0xcb, 0x35, 0xed, 0xa9, 0x2e, 0xe3, 0x73, 0x56, 0xdd, 0xee, 0x77, 0x78, 0x1a, 0x17,
	0xb3, 0xd9, 0x0e, 0x56, 0x38, 0x24, 0xa9, 0x84, 0xfa, 0xff, 0xc6, 0xfd, 0xd1, 0x69, 0x3b, 0xd7,
	0x62, 0x60, 0x39, 0x63, 0x55, 0x63, 0xcf, 0xc3, 0xb9, 0xa2, 0xb0, 0x0f, 0x9c, 0x65, 0xee, 0xfd
};

/**
 * SHA384 hash of HASH_TESTING_FULL_BLOCK_2048.
 */
const uint8_t SHA384_FULL_BLOCK_2048_HASH[] = {
	0xa5, 0xfd, 0xc9, 0xf7, 0x96, 0x92, 0x41, 0x66, 0xd2, 0xe7, 0xe8, 0xdd, 0x08, 0x62, 0x36, 0xca,
	0x92, 0x9b, 0x39, 0x9d, 0x5e, 0xe3, 0x44, 0x4b, 0x99, 0x6f, 0x7f, 0x9e, 0x8b, 0x08, 0x2c, 0xc6,
	0x1b, 0x14, 0x6b, 0x56, 0x5e, 0xbf, 0x49, 0x1d, 0xef, 0x22, 0xdf, 0xe2, 0xdc, 0xfc, 0x36, 0x5a
};

/**
 * SHA384 hash of HASH_TESTING_FULL_BLOCK_4096.
 */
const uint8_t SHA384_FULL_BLOCK_4096_HASH[] = {
	0x20, 0xe3, 0x2d, 0xa7, 0x70, 0xaf, 0x8b, 0x14, 0x01, 0xf8, 0xb6, 0x56, 0x3c, 0x30, 0x10, 0xc5,
	0x6c, 0x79, 0xc7, 0x1f, 0x5d, 0x88, 0x8c, 0xa6, 0xfe, 0xb0, 0x5b, 0x4c, 0x1e, 0x06, 0x52, 0x43,
	0x16, 0x0a, 0xb1, 0x92, 0x3b, 0xe5, 0xf2, 0x71, 0x19, 0x15, 0x45, 0xdc, 0x9d, 0xe1, 0x97, 0xbd
};

/**
 * SHA384 hash of HASH_TESTING_MULTI_BLOCK_NOT_ALIGNED.
 */
const uint8_t SHA384_MULTI_BLOCK_NOT_ALIGNED_HASH[] = {
	0x2a, 0xc3, 0xab, 0x52, 0x99, 0xff, 0xba, 0xc1, 0xc2, 0x73, 0x00, 0x85, 0x9a, 0x92, 0xa6, 0x9a,
	0x80, 0xf5, 0x10, 0xa1, 0xf2, 0x8b, 0x70, 0x54, 0xf1, 0x31, 0xb4, 0x3a, 0xf7, 0x4a, 0x0d, 0xf5,
	0xe2, 0x98, 0xa9, 0xea, 0xb7, 0x7e, 0x49, 0xca, 0x81, 0xa5, 0x78, 0xc3, 0x09, 0xf5, 0xae, 0xc4
};

/**
 * Test key to use for SHA384 HMAC.  The key length is equal to SHA384_HASH_LENGTH.
 */
const uint8_t SHA384_HMAC_KEY[] = {
	0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0a, 0x0b, 0x0c, 0x0d, 0x0e, 0x0f,
	0x10, 0x11, 0x12, 0x13, 0x14, 0x15, 0x16, 0x17, 0x18, 0x19, 0x1a, 0x1b, 0x1c, 0x1d, 0x1e, 0x1f,
	0x20, 0x21, 0x22, 0x23, 0x24, 0x25, 0x26, 0x27, 0x28, 0x29, 0x2a, 0x2b, 0x2c, 0x2d, 0x2e, 0x2f
};

/**
 * Test key to use for SHA384 HMAC.  The key length is equal to SHA384_BLOCK_SIZE.
 */
const uint8_t SHA384_HMAC_BLOCK_KEY[] = {
	0xc2, 0x87, 0xee, 0x6b, 0x64, 0x4f, 0x6a, 0x66, 0x65, 0xfd, 0x75, 0x50, 0x9b, 0x02, 0x56, 0xf9,
	0xc9, 0x75, 0xec, 0x98, 0xcc, 0x36, 0x9c, 0x90, 0x10, 0xbc, 0x8b, 0xd7, 0x28, 0xa1, 0xa0, 0x81,
	0x6d, 0x52, 0x80, 0x64, 0x3d, 0xd6, 0x58, 0x64, 0x26, 0x19, 0x43, 0x07, 0x7c, 0x76, 0xd0, 0xa1,
	0x76, 0x68, 0xe7, 0xef, 0x39, 0x0a, 0x0a, 0xf1, 0x1e, 0x96, 0xda, 0x57, 0x2b, 0x0e, 0xfb, 0xcc,
	0xc7, 0x3a, 0x97, 0xa9, 0x6a, 0x5f, 0x51, 0x72, 0x82, 0x3c, 0x98, 0x9d, 0x19, 0x0b, 0x85, 0x8c,
	0x54, 0x80, 0xb7, 0x54, 0xb8, 0xff, 0x9c, 0x39, 0xc6, 0x65, 0xdb, 0x29, 0xd6, 0x81, 0xf5, 0xa9,
	0x7a, 0x18, 0x13, 0x6a, 0x52, 0x55, 0x7c, 0x8f, 0x59, 0xcf, 0xda, 0x84, 0xa2, 0x7b, 0xe7, 0x21,
	0xa1, 0x78, 0x24, 0x3f, 0xf4, 0x45, 0x59, 0xd4, 0xd4, 0xd0, 0xb4, 0xa0, 0x72, 0x8b, 0x04, 0xac
};

/**
 * SHA384 HMAC of "Test" using SHA384_HMAC_KEY.
 */
const uint8_t SHA384_TEST_HMAC[] = {
	0x59, 0x38, 0x2e, 0xc3, 0x89, 0xf5, 0x8f, 0x5b, 0x95, 0x1b, 0xad, 0xed, 0xd4, 0xab, 0x25, 0x40,
	0xc3, 0x49, 0x7e, 0x99, 0x23, 0xb5, 0x08, 0x84, 0x6b, 0x0a, 0x68, 0x62, 0xf2, 0xe5, 0x7f, 0x1c,
	0x86, 0x3b, 0x9b, 0x81, 0x4e, 0xce, 0x4a, 0x91, 0x6b, 0x20, 0x80, 0x32, 0x2b, 0x86, 0x2f, 0xf1
};

/**
 * SHA384 HMAC of HASH_TESTING_FULL_BLOCK_1024 using SHA384_HMAC_KEY.
 */
const uint8_t SHA384_FULL_BLOCK_1024_HMAC[] = {
	0xf5, 0x8f, 0xaa, 0x62, 0xb6, 0x46, 0x29, 0x1e, 0x86, 0x24, 0xca, 0x70, 0xb4, 0xc7, 0x42, 0x0a,
	0x01, 0xe3, 0xbf, 0x13, 0xdb, 0x58, 0x3c, 0x8a, 0x16, 0x62, 0xae, 0x81, 0x36, 0x21, 0x56, 0xd8,
	0x21, 0xbf, 0xea, 0xbe, 0x79, 0xbd, 0x9d, 0x42, 0x5d, 0x5b, 0x53, 0x41, 0xd9, 0xdf, 0xc9, 0x38
};

/**
 * SHA384 HMAC of HASH_TESTING_FULL_BLOCK_4096 using SHA384_HMAC_BLOCK_KEY.
 */
const uint8_t SHA384_FULL_BLOCK_4096_BLOCK_KEY_HMAC[] = {
	0x4e, 0x9b, 0x11, 0xe4, 0x0b, 0xf1, 0xda, 0xbd, 0x75, 0xc4, 0xb0, 0xf6, 0x7d, 0x0d, 0xc1, 0x02,
	0x81, 0x34, 0x85, 0x22, 0xa0, 0xe3, 0xe5, 0xf1, 0x4e, 0x5c, 0xbf, 0x75, 0x48, 0x56, 0x81, 0xef,
	0xa8, 0x9c, 0xfc, 0x7c, 0x19, 0xea, 0x13, 0xda, 0xcc, 0x77, 0xce, 0x37, 0xdd, 0x47, 0xbc, 0xa1
};

/**
 * SHA384 hash of HMAC_KAT_VECTORS_CALCULATE_KEY.
 */
const uint8_t SHA384_HMAC_KAT_CALCULATE_KEY_HASH[] = {
	0x75, 0xee, 0xe9, 0xaf, 0x74, 0x5c, 0x63, 0xbf, 0x11, 0x25, 0xfd, 0x79, 0x59, 0xad, 0x9c, 0x31,
	0x3f, 0x33, 0x45, 0x4b, 0xd8, 0xe2, 0xe3, 0x3d, 0xc7, 0xa8, 0xe9, 0x6b, 0xc1, 0xd0, 0x30, 0x7b,
	0x68, 0x8d, 0xc5, 0x73, 0x8f, 0x62, 0xb9, 0xbd, 0x84, 0x24, 0xcf, 0xd0, 0xca, 0x35, 0x57, 0x70
};

/**
 * SHA512 hash of "Test".
 */
const uint8_t SHA512_TEST_HASH[] = {
	0xc6, 0xee, 0x9e, 0x33, 0xcf, 0x5c, 0x67, 0x15, 0xa1, 0xd1, 0x48, 0xfd, 0x73, 0xf7, 0x31, 0x88,
	0x84, 0xb4, 0x1a, 0xdc, 0xb9, 0x16, 0x02, 0x1e, 0x2b, 0xc0, 0xe8, 0x00, 0xa5, 0xc5, 0xdd, 0x97,
	0xf5, 0x14, 0x21, 0x78, 0xf6, 0xae, 0x88, 0xc8, 0xfd, 0xd9, 0x8e, 0x1a, 0xfb, 0x0c, 0xe4, 0xc8,
	0xd2, 0xc5, 0x4b, 0x5f, 0x37, 0xb3, 0x0b, 0x7d, 0xa1, 0x99, 0x7b, 0xb3, 0x3b, 0x0b, 0x8a, 0x31
};

/**
 * SHA512 hash of "TestTest".
 */
const uint8_t SHA512_TEST_TEST_HASH[] = {
	0xf7, 0xc8, 0x74, 0x28, 0xfa, 0xdd, 0xa0, 0xa5, 0x5c, 0x3c, 0xd4, 0x2f, 0x35, 0x3e, 0xb1, 0x73,
	0x4e, 0xb0, 0xe3, 0xd1, 0x8f, 0x3a, 0x46, 0xdb, 0xc5, 0x35, 0xf8, 0xc6, 0x53, 0x41, 0x8a, 0x91,
	0x52, 0xe7, 0x4d, 0xe7, 0x40, 0x27, 0x04, 0x98, 0x35, 0xf1, 0x49, 0x1f, 0x43, 0xce, 0x53, 0x68,
	0xbb, 0xbf, 0xfe, 0x18, 0xd8, 0x53, 0xbc, 0xe9, 0xb6, 0x41, 0x4c, 0x52, 0x0b, 0x7d, 0x6b, 0xc6
};

/**
 * SHA512 hash of "Test2".
 */
const uint8_t SHA512_TEST2_HASH[] = {
	0x91, 0x8d, 0x11, 0xb7, 0xa7, 0xf8, 0x08, 0x04, 0x55, 0x79, 0x5c, 0xb7, 0x11, 0x5d, 0x13, 0xf5,
	0x35, 0x66, 0xe9, 0xe0, 0xe6, 0x0e, 0x28, 0x7d, 0xc8, 0xeb, 0x39, 0xc9, 0x3c, 0xb2, 0xdb, 0x0f,
	0xd1, 0x3b, 0xd7, 0x4c, 0xd2, 0x8e, 0x8e, 0x49, 0x99, 0xed, 0xfb, 0xd9, 0xd1, 0xfd, 0xdb, 0x60,
	0xb5, 0x87, 0xe2, 0x9c, 0xc4, 0xe3, 0xb9, 0x06, 0x3a, 0x03, 0xed, 0xde, 0x29, 0x13, 0xb5, 0xbd
};

/**
 * SHA512 hash of "Nope".
 */
const uint8_t SHA512_NOPE_HASH[] = {
	0xec, 0x9e, 0x04, 0x5f, 0x37, 0xc1, 0x79, 0x94, 0xaf, 0xb4, 0x5d, 0x11, 0x35, 0x30, 0x97, 0x3f,
	0xf2, 0xbe, 0x46, 0xcb, 0xe9, 0xff, 0x56, 0x2b, 0x7e, 0xa7, 0x94, 0x27, 0xf8, 0x29, 0x61, 0xb4,
	0x0e, 0xf9, 0xee, 0xaa, 0xe1, 0x10, 0x3b, 0x16, 0x3b, 0xac, 0xe5, 0xaa, 0xa3, 0xf2, 0xc8, 0x9c,
	0xba, 0xca, 0x03, 0x63, 0xe9, 0x1c, 0x59, 0x6e, 0xa4, 0x25, 0xb0, 0x3a, 0x7c, 0x0b, 0x8c, 0x72
};

/**
 * SHA512 hash of "Bad".
 */
const uint8_t SHA512_BAD_HASH[] = {
	0xc8, 0x5f, 0xb9, 0x4f, 0x63, 0xc5, 0xb9, 0xf9, 0x3e, 0x49, 0x5f, 0xb5, 0x75, 0x89, 0x65, 0x6d,
	0x31, 0xb4, 0x41, 0x1e, 0x0c, 0x79, 0x3a, 0x11, 0xfd, 0xe6, 0x40, 0x39, 0xfd, 0xaa, 0x2d, 0xa8,
	0x59, 0xd1, 0x4d, 0x41, 0x67, 0x24, 0x14, 0x86, 0x46, 0x91, 0x63, 0x7f, 0x82, 0x06, 0x50, 0x72,
	0xf6, 0x4e, 0x23, 0x8d, 0x7c, 0xe2, 0x77, 0x43, 0x79, 0x27, 0xca, 0x7c, 0xcb, 0xfa, 0x86, 0x9c
};

/**
 * SHA512 hash of an empty buffer.
 */
const uint8_t SHA512_EMPTY_BUFFER_HASH[] = {
	0xcf, 0x83, 0xe1, 0x35, 0x7e, 0xef, 0xb8, 0xbd, 0xf1, 0x54, 0x28, 0x50, 0xd6, 0x6d, 0x80, 0x07,
	0xd6, 0x20, 0xe4, 0x05, 0x0b, 0x57, 0x15, 0xdc, 0x83, 0xf4, 0xa9, 0x21, 0xd3, 0x6c, 0xe9, 0xce,
	0x47, 0xd0, 0xd1, 0x3c, 0x5d, 0x85, 0xf2, 0xb0, 0xff, 0x83, 0x18, 0xd2, 0x87, 0x7e, 0xec, 0x2f,
	0x63, 0xb9, 0x31, 0xbd, 0x47, 0x41, 0x7a, 0x81, 0xa5, 0x38, 0x32, 0x7a, 0xf9, 0x27, 0xda, 0x3e
};

/**
 * SHA512 hash of a 32 byte buffer filled with zeros.
 */
const uint8_t SHA512_ZERO_BUFFER_HASH[] = {
	0x50, 0x46, 0xad, 0xc1, 0xdb, 0xa8, 0x38, 0x86, 0x7b, 0x2b, 0xbb, 0xfd, 0xd0, 0xc3, 0x42, 0x3e,
	0x58, 0xb5, 0x79, 0x70, 0xb5, 0x26, 0x7a, 0x90, 0xf5, 0x79, 0x60, 0x92, 0x4a, 0x87, 0xf1, 0x96,
	0x0a, 0x6a, 0x85, 0xea, 0xa6, 0x42, 0xda, 0xc8, 0x35, 0x42, 0x4b, 0x5d, 0x7c, 0x8d, 0x63, 0x7c,
	0x00, 0x40, 0x8c, 0x7a, 0x73, 0xda, 0x67, 0x2b, 0x7f, 0x49, 0x85, 0x21, 0x42, 0x0b, 0x6d, 0xd3
};

/**
 * SHA512 hash of HASH_TESTING_PARTIAL_BLOCK_440.
 */
const uint8_t SHA512_PARTIAL_BLOCK_440_HASH[] = {
	0x2d, 0xda, 0xd4, 0x1e, 0xe1, 0x04, 0x9c, 0x1d, 0x71, 0x2e, 0xb4, 0x0f, 0x6d, 0xd6, 0x3c, 0xc5,
	0x77, 0x0c, 0xba, 0xb2, 0xf3, 0x91, 0xc7, 0xcb, 0x7b, 0xea, 0x5c, 0xb2, 0xc3, 0xbe, 0xce, 0x08,
	0xe3, 0xb3, 0x01, 0x09, 0x39, 0x2a, 0x37, 0x85, 0xa1, 0x67, 0x26, 0x16, 0xa2, 0x9c, 0x65, 0x18,
	0xfb, 0xdf, 0x5c, 0xb1, 0x80, 0xa5, 0xdd, 0x4e, 0x85, 0x12, 0x42, 0xb5, 0x5d, 0xe2, 0xc9, 0x33
};

/**
 * SHA512 hash of HASH_TESTING_PARTIAL_BLOCK_448.
 */
const uint8_t SHA512_PARTIAL_BLOCK_448_HASH[] = {
	0x88, 0x7f, 0x60, 0x81, 0xa1, 0x8b, 0x32, 0x9e, 0xfb, 0x51, 0xa8, 0x45, 0x81, 0xd4, 0x8a, 0x68,
	0x08, 0x85, 0x1e, 0x64, 0x36, 0xc2, 0x11, 0x7e, 0x4e, 0x78, 0xaa, 0x28, 0xa5, 0x1c, 0x6d, 0x7e,
	0xbd, 0xce, 0x5c, 0x6b, 0xf3, 0xd0, 0x1e, 0x4b, 0x2b, 0x50, 0x9d, 0x94, 0xdd, 0xc9, 0xd7, 0x3e,
	0xbb, 0xe2, 0xff, 0x4a, 0xdc, 0x76, 0xb7, 0xa0, 0x6e, 0x25, 0x53, 0x51, 0xf3, 0xf9, 0x4b, 0xbe
};

/**
 * SHA512 hash of HASH_TESTING_PARTIAL_BLOCK_480.
 */
const uint8_t SHA512_PARTIAL_BLOCK_480_HASH[] = {
	0xf6, 0xbc, 0xde, 0x7e, 0x16, 0xcf, 0xdf, 0x30, 0x1a, 0x7f, 0xc3, 0x51, 0x3d, 0x8e, 0x80, 0xfe,
	0x71, 0xbe, 0x4e, 0xec, 0x7e, 0x03, 0x20, 0x6e, 0x6a, 0xc5, 0x47, 0x0f, 0xb8, 0x9b, 0xe5, 0xca,
	0xf4, 0xcd, 0x75, 0x5e, 0x07, 0x78, 0x60, 0xb2, 0x84, 0x08, 0xf9, 0xcc, 0x7a, 0xac, 0xde, 0xa6,
	0x8a, 0x20, 0xf1, 0xa3, 0x96, 0xe7, 0x2e, 0x34, 0x68, 0x31, 0x64, 0x03, 0x32, 0x51, 0x3a, 0x87
};

/**
 * SHA512 hash of HASH_TESTING_FULL_BLOCK_512.
 */
const uint8_t SHA512_FULL_BLOCK_512_HASH[] = {
	0x41, 0xab, 0x2b, 0x5b, 0x4a, 0x9b, 0x8e, 0x9b, 0xe7, 0x97, 0x90, 0x2d, 0x11, 0x7c, 0x65, 0x67,
	0x0f, 0x25, 0x9a, 0xb0, 0x7f, 0xe6, 0x93, 0x40, 0x05, 0x1a, 0xc5, 0x5f, 0x24, 0x82, 0x18, 0xa2,
	0x83, 0xa9, 0xf2, 0x46, 0x67, 0xa3, 0x02, 0xbd, 0x21, 0xb2, 0xe2, 0x3c, 0x7d, 0x97, 0x63, 0xd3,
	0x4d, 0xeb, 0xdf, 0x95, 0x98, 0x71, 0xf0, 0xf7, 0x6d, 0x60, 0x72, 0x86, 0xd1, 0x2e, 0x61, 0x75
};

/**
 * SHA512 hash of HASH_TESTING_PARTIAL_BLOCK_952.
 */
const uint8_t SHA512_PARTIAL_BLOCK_952_HASH[] = {
	0x30, 0x65, 0xa8, 0xda, 0x0c, 0xf9, 0x61, 0x74, 0x25, 0xa5, 0x4b, 0x21, 0x46, 0x37, 0xac, 0xea,
	0xf0, 0xb0, 0x0d, 0x08, 0x59, 0x23, 0x4c, 0x11, 0x46, 0x9f, 0x75, 0x86, 0x28, 0x05, 0x04, 0x6f,
	0xf8, 0x1d, 0x2f, 0x9b, 0xdf, 0x7d, 0x3b, 0xf1, 0x78, 0x0e, 0x21, 0xde, 0xcb, 0xcb, 0x3c, 0x38,
	0xaf, 0xaa, 0x35, 0x54, 0xfb, 0x7e, 0x42, 0x1b, 0xb0, 0x31, 0x1b, 0x70, 0xe5, 0x85, 0x4b, 0x6f
};

/**
 * SHA512 hash of HASH_TESTING_PARTIAL_BLOCK_960.
 */
const uint8_t SHA512_PARTIAL_BLOCK_960_HASH[] = {
	0x25, 0x33, 0x10, 0x2b, 0x54, 0x05, 0xd8, 0x5b, 0xd5, 0xd1, 0x1e, 0x4e, 0x06, 0xfb, 0x4d, 0xe2,
	0xe0, 0x5d, 0xfb, 0x3e, 0x2d, 0x8b, 0xb4, 0x4e, 0x30, 0x38, 0xd9, 0x90, 0xf8, 0x05, 0x8e, 0x34,
	0x74, 0xf0, 0x2b, 0xd6, 0xcb, 0x08, 0xb1, 0xba, 0x5d, 0xc5, 0x27, 0x57, 0x12, 0x09, 0x75, 0xa6,
	0xf2, 0x77, 0x81, 0x24, 0x91, 0xcc, 0x33, 0x0f, 0x0f, 0x5a, 0x0f, 0xb6, 0xf2, 0xe3, 0x61, 0xd7
};

/**
 * SHA512 hash of HASH_TESTING_PARTIAL_BLOCK_992.
 */
const uint8_t SHA512_PARTIAL_BLOCK_992_HASH[] = {
	0x78, 0x41, 0xef, 0x8a, 0xc7, 0x0e, 0xec, 0x22, 0xed, 0xff, 0xd5, 0xb6, 0x5c, 0x84, 0x54, 0x71,
	0xf9, 0x84, 0x96, 0x38, 0x92, 0x77, 0xe1, 0xd4, 0xb1, 0xae, 0xaf, 0xdc, 0xd1, 0x0b, 0x43, 0xc0,
	0xe6, 0xe2, 0x6a, 0x4b, 0xfc, 0xe5, 0xd1, 0x8c, 0x5b, 0x1d, 0xdf, 0x3a, 0xf3, 0x03, 0x0b, 0x08,
	0x87, 0xce, 0x75, 0x22, 0x52, 0x02, 0x33, 0x23, 0x4b, 0x38, 0x20, 0xd0, 0xcd, 0x2a, 0x7c, 0xa7
};

/**
 * SHA512 hash of HASH_TESTING_FULL_BLOCK_1024.
 */
const uint8_t SHA512_FULL_BLOCK_1024_HASH[] = {
	0x8d, 0xde, 0xb7, 0x82, 0x78, 0xb0, 0x2a, 0x3d, 0xe8, 0x79, 0xbe, 0xc1, 0x7d, 0x3c, 0xfd, 0xda,
	0x0a, 0x8f, 0x7f, 0xcf, 0x0e, 0x77, 0x6d, 0x89, 0x53, 0xa0, 0xdf, 0x68, 0xe3, 0x7d, 0xb7, 0x05,
	0x48, 0x7c, 0xd0, 0x75, 0x0a, 0xf3, 0xe7, 0x14, 0xed, 0x29, 0x56, 0x5b, 0x9e, 0xb9, 0xdd, 0xc6,
	0xc7, 0x6a, 0x36, 0x10, 0xde, 0x65, 0x73, 0xa9, 0xf9, 0x45, 0xfb, 0xb9, 0xf5, 0x71, 0x81, 0x3f
};

/**
 * SHA512 hash of HASH_TESTING_FULL_BLOCK_2048.
 */
const uint8_t SHA512_FULL_BLOCK_2048_HASH[] = {
	0xed, 0x30, 0x2c, 0x2c, 0xf8, 0xb5, 0xa2, 0x27, 0x6a, 0x5b, 0x28, 0xbc, 0x32, 0xda, 0x45, 0xac,
	0x2f, 0x9d, 0x3b, 0x56, 0x02, 0x69, 0xaa, 0x3d, 0x58, 0x24, 0x1e, 0xbb, 0x2b, 0x87, 0x74, 0x91,
	0x32, 0x4d, 0xc1, 0xa8, 0xdf, 0x09, 0x38, 0x07, 0x55, 0x70, 0x72, 0xe0, 0x7d, 0x48, 0xab, 0xa7,
	0xa7, 0x60, 0x2e, 0x82, 0x36, 0x5a, 0x77, 0x9d, 0x56, 0x17, 0x6b, 0xab, 0x4e, 0x1a, 0x94, 0xea
};

/**
 * SHA512 hash of HASH_TESTING_FULL_BLOCK_4096.
 */
const uint8_t SHA512_FULL_BLOCK_4096_HASH[] = {
	0x63, 0x1b, 0x4a, 0x20, 0xe3, 0x59, 0xd9, 0xdb, 0x38, 0x75, 0x3b, 0x68, 0x91, 0xc8, 0x26, 0x72,
	0x5e, 0x73, 0x6d, 0x1f, 0x19, 0x16, 0x09, 0xb9, 0x5a, 0xcc, 0xe2, 0x2c, 0xc0, 0xde, 0xa2, 0x71,
	0xff, 0xdf, 0xf7, 0xe6, 0x1b, 0x12, 0x1a, 0x9c, 0x36, 0x50, 0xfd, 0xeb, 0x68, 0xe4, 0xd4, 0xe3,
	0xa4, 0x08, 0x2c, 0x17, 0x0c, 0x4d, 0xde, 0xd0, 0x77, 0xec, 0xe7, 0x1f, 0xef, 0xf3, 0x9f, 0x90
};

/**
 * SHA512 hash of HASH_TESTING_MULTI_BLOCK_NOT_ALIGNED.
 */
const uint8_t SHA512_MULTI_BLOCK_NOT_ALIGNED_HASH[] = {
	0x58, 0xa5, 0x63, 0xc0, 0x36, 0xbb, 0xaa, 0x33, 0x7b, 0xee, 0xa1, 0xda, 0x29, 0x28, 0x63, 0x20,
	0x4e, 0xf7, 0x91, 0x9b, 0x46, 0xac, 0x91, 0x1e, 0x8c, 0x2b, 0x5a, 0x66, 0x78, 0x7f, 0x08, 0xd4,
	0x4c, 0x9c, 0xe2, 0x18, 0x07, 0xe4, 0xc8, 0xe8, 0x7a, 0x62, 0xcb, 0x01, 0x57, 0xf4, 0xb6, 0x3f,
	0x7f, 0xf6, 0x8d, 0x7f, 0x86, 0x91, 0x08, 0x7c, 0x10, 0x4a, 0x1b, 0x58, 0x0c, 0x4b, 0xc9, 0x2d
};

/**
 * Test key to use for SHA512 HMAC.  The key length is equal to SHA512_HASH_LENGTH.
 */
const uint8_t SHA512_HMAC_KEY[] = {
	0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0a, 0x0b, 0x0c, 0x0d, 0x0e, 0x0f,
	0x10, 0x11, 0x12, 0x13, 0x14, 0x15, 0x16, 0x17, 0x18, 0x19, 0x1a, 0x1b, 0x1c, 0x1d, 0x1e, 0x1f,
	0x20, 0x21, 0x22, 0x23, 0x24, 0x25, 0x26, 0x27, 0x28, 0x29, 0x2a, 0x2b, 0x2c, 0x2d, 0x2e, 0x2f,
	0x30, 0x31, 0x32, 0x33, 0x34, 0x35, 0x36, 0x37, 0x38, 0x39, 0x3a, 0x3b, 0x3c, 0x3d, 0x3e, 0x3f
};

/**
 * Test key to use for SHA512 HMAC.  The key length is equal to SHA512_BLOCK_SIZE.
 */
const uint8_t SHA512_HMAC_BLOCK_KEY[] = {
	0xd9, 0xdc, 0xe2, 0x44, 0xc5, 0x1f, 0x9c, 0xeb, 0x5c, 0xfb, 0x8e, 0x48, 0xe7, 0x52, 0xd2, 0x99,
	0x81, 0xf2, 0xa4, 0x1b, 0x28, 0xaf, 0xfd, 0x44, 0x66, 0x9e, 0xfa, 0x94, 0x34, 0x44, 0xbe, 0x5e,
	0xef, 0xbd, 0xfa, 0x19, 0x04, 0xa1, 0x8a, 0x59, 0x16, 0x6d, 0xdb, 0xa5, 0x24, 0x40, 0xb2, 0xd3,
	0x45, 0x46, 0xfc, 0xf0, 0x54, 0x86, 0xdb, 0x64, 0x57, 0x01, 0xf3, 0x44, 0x5c, 0xbc, 0x8d, 0x65,
	0x0d, 0xef, 0x82, 0x29, 0x09, 0x6e, 0x94, 0xc3, 0xd2, 0xc2, 0x3d, 0xcd, 0x40, 0xe7, 0x82, 0xc2,
	0xb9, 0x2f, 0x98, 0x75, 0xe9, 0xda, 0x45, 0x6d, 0x08, 0x52, 0x07, 0x2d, 0xd3, 0xc8, 0x32, 0x89,
	0x62, 0x69, 0x91, 0x97, 0x31, 0x23, 0xb3, 0xd6, 0x39, 0xac, 0xfd, 0xae, 0xdb, 0x4c, 0xf4, 0x07,
	0x70, 0x30, 0x9e, 0x05, 0x19, 0x6b, 0x4d, 0x88, 0xfb, 0xba, 0x36, 0x87, 0x7b, 0x56, 0x19, 0x63
};

/**
 * SHA512 HMAC of "Test" using SHA512_HMAC_KEY.
 */
const uint8_t SHA512_TEST_HMAC[] = {
	0xc3, 0x25, 0x2d, 0x64, 0x2a, 0xf1, 0x3e, 0x37, 0xd1, 0xd1, 0x2a, 0x4d, 0xd7, 0x2e, 0xae, 0xac,
	0x28, 0x8c, 0x9b, 0x40, 0xbf, 0xfd, 0xad, 0x91, 0x05, 0x4f, 0xc5, 0x79, 0x7a, 0x91, 0x4b, 0x94,
	0xbf, 0x82, 0xa9, 0x21, 0xac, 0x41, 0xba, 0x92, 0xed, 0xae, 0x05, 0x70, 0xc0, 0xc6, 0x5f, 0xfd,
	0xf6, 0x82, 0x43, 0xe7, 0xed, 0x79, 0xa8, 0xaa, 0x9a, 0xa5, 0x40, 0x1f, 0x06, 0x22, 0xc0, 0x46
};

/**
 * SHA512 HMAC of HASH_TESTING_FULL_BLOCK_1024 using SHA512_HMAC_KEY.
 */
const uint8_t SHA512_FULL_BLOCK_1024_HMAC[] = {
	0xf0, 0x1d, 0xac, 0x42, 0x48, 0xee, 0x66, 0x5d, 0x84, 0xe6, 0xb0, 0xd0, 0x38, 0x9d, 0xee, 0xe2,
	0x64, 0xd3, 0xd5, 0xe9, 0x2c, 0xb6, 0x00, 0x7f, 0xf5, 0xc5, 0x86, 0x5a, 0x65, 0x57, 0xbc, 0x4a,
	0xb9, 0x4f, 0xf3, 0x60, 0xef, 0xe1, 0x9f, 0xc4, 0xa4, 0xf8, 0x01, 0x36, 0x20, 0xfc, 0x32, 0xfb,
	0x55, 0x27, 0x9f, 0xf6, 0xeb, 0x6b, 0x08, 0x52, 0xd4, 0xbb, 0xf2, 0xa4, 0x89, 0x7d, 0x68, 0xf4
};

/**
 * SHA512 HMAC of HASH_TESTING_FULL_BLOCK_4096 using SHA512_HMAC_BLOCK_KEY.
 */
const uint8_t SHA512_FULL_BLOCK_4096_BLOCK_KEY_HMAC[] = {
	0xba, 0x02, 0xf6, 0x4c, 0x0a, 0x62, 0xbd, 0x35, 0xc0, 0xd1, 0x15, 0xcf, 0x33, 0x5c, 0xde, 0xfa,
	0x48, 0x4b, 0x04, 0x89, 0x68, 0x96, 0xb4, 0x8a, 0x36, 0x95, 0x54, 0x50, 0x35, 0x58, 0x10, 0x8a,
	0xfa, 0x2a, 0x20, 0xa5, 0x07, 0x37, 0x5e, 0x88, 0xb7, 0xd9, 0x22, 0x84, 0xfa, 0x94, 0x63, 0xed,
	0xc7, 0xa3, 0x64, 0xdd, 0xaa, 0x99, 0xce, 0x95, 0x8a, 0x62, 0xa2, 0x46, 0xb3, 0x58, 0x5a, 0x31
};

/**
 * SHA512 hash of HMAC_KAT_VECTORS_CALCULATE_KEY.
 */
const uint8_t SHA512_HMAC_KAT_CALCULATE_KEY_HASH[] = {
	0xc7, 0xbb, 0x62, 0x07, 0xde, 0xd7, 0x35, 0x46, 0x43, 0x81, 0xc5, 0xab, 0x93, 0x06, 0xc3, 0x0e,
	0xb4, 0x29, 0x79, 0x9f, 0x96, 0x81, 0x82, 0xdb, 0xb7, 0xa9, 0x74, 0xa0, 0xdc, 0xad, 0x29, 0xcc,
	0x22, 0x8b, 0x47, 0xf6, 0x20, 0x39, 0xc3, 0xbb, 0x17, 0x69, 0x69, 0x1a, 0x02, 0xf3, 0xa1, 0x04,
	0xdb, 0x7b, 0xc4, 0x80, 0x4f, 0xbe, 0x73, 0x9f, 0x92, 0xad, 0xb7, 0xb8, 0xc9, 0xdd, 0x0e, 0xc1
};


/*******************
 * Test cases
 *******************/

static void hash_test_hmac_sha1_incremental (CuTest *test)
{
	HASH_TESTING_ENGINE engine;
	int status;
	char *message = "Test";
	uint8_t key[] = {0x31, 0x32, 0x33, 0x34};
	uint8_t hmac[SHA1_HASH_LENGTH];
	uint8_t expected[] = {
		0xfc, 0x3d, 0x91, 0xe6, 0xc1, 0x13, 0xd6, 0x82, 0x18, 0x33, 0xf6, 0x5b, 0x12, 0xc7, 0xe7,
		0x6e,
		0x7f, 0x38, 0x9c, 0x4f
	};
	struct hmac_engine hmac_engine;

	TEST_START;

	status = HASH_TESTING_ENGINE_INIT (&engine);
	CuAssertIntEquals (test, 0, status);

	status = hash_hmac_init (&hmac_engine, &engine.base, HMAC_SHA1, key, sizeof (key));
#ifdef HASH_ENABLE_SHA1
	CuAssertIntEquals (test, 0, status);

	status = hash_hmac_update (&hmac_engine, (uint8_t*) message, strlen (message));
	CuAssertIntEquals (test, 0, status);

	status = hash_hmac_finish (&hmac_engine, hmac, sizeof (hmac));
	CuAssertIntEquals (test, 0, status);

	status = testing_validate_array (expected, hmac, sizeof (hmac));
	CuAssertIntEquals (test, 0, status);
#else
	CuAssertIntEquals (test, HASH_ENGINE_UNSUPPORTED_HASH, status);
#endif

	HASH_TESTING_ENGINE_RELEASE (&engine);
}

#ifdef HASH_ENABLE_SHA1
static void hash_test_hmac_sha1_incremental_large_key (CuTest *test)
{
	HASH_TESTING_ENGINE engine;
	int status;
	char *message = "Test";
	uint8_t key[SHA1_BLOCK_SIZE + 1];
	uint8_t hmac[SHA1_HASH_LENGTH];
	uint8_t expected[] = {
		0x19, 0x75, 0xda, 0x73, 0x05, 0xeb, 0xd1, 0x29, 0x3a, 0x90, 0xc8, 0x36, 0xe1, 0xed, 0x76,
		0x7f,
		0xa3, 0x67, 0x51, 0x31
	};
	struct hmac_engine hmac_engine;
	int i;

	TEST_START;

	for (i = 0; i < (int) sizeof (key); i++) {
		key[i] = i;
	}

	status = HASH_TESTING_ENGINE_INIT (&engine);
	CuAssertIntEquals (test, 0, status);

	status = hash_hmac_init (&hmac_engine, &engine.base, HMAC_SHA1, key, sizeof (key));
	CuAssertIntEquals (test, 0, status);

	status = hash_hmac_update (&hmac_engine, (uint8_t*) message, strlen (message));
	CuAssertIntEquals (test, 0, status);

	status = hash_hmac_finish (&hmac_engine, hmac, sizeof (hmac));
	CuAssertIntEquals (test, 0, status);

	status = testing_validate_array (expected, hmac, sizeof (hmac));
	CuAssertIntEquals (test, 0, status);

	HASH_TESTING_ENGINE_RELEASE (&engine);
}
#endif

static void hash_test_hmac_sha256_incremental (CuTest *test)
{
	HASH_TESTING_ENGINE engine;
	int status;
	char *message = "Test";
	uint8_t key[] = {0x31, 0x32, 0x33, 0x34};
	uint8_t hmac[SHA256_HASH_LENGTH];
	uint8_t expected[] = {
		0x88, 0x69, 0xde, 0x57, 0x9d, 0xd0, 0xe9, 0x05, 0xe0, 0xa7, 0x11, 0x24, 0x57, 0x55, 0x94,
		0xf5,
		0x0a, 0x03, 0xd3, 0xd9, 0xcd, 0xf1, 0x6e, 0x9a, 0x3f, 0x9d, 0x6c, 0x60, 0xc0, 0x32, 0x4b,
		0x54
	};
	struct hmac_engine hmac_engine;

	TEST_START;

	status = HASH_TESTING_ENGINE_INIT (&engine);
	CuAssertIntEquals (test, 0, status);

	status = hash_hmac_init (&hmac_engine, &engine.base, HMAC_SHA256, key, sizeof (key));
	CuAssertIntEquals (test, 0, status);

	status = hash_hmac_update (&hmac_engine, (uint8_t*) message, strlen (message));
	CuAssertIntEquals (test, 0, status);

	status = hash_hmac_finish (&hmac_engine, hmac, sizeof (hmac));
	CuAssertIntEquals (test, 0, status);

	status = testing_validate_array (expected, hmac, sizeof (hmac));
	CuAssertIntEquals (test, 0, status);

	HASH_TESTING_ENGINE_RELEASE (&engine);
}

static void hash_test_hmac_sha256_incremental_large_key (CuTest *test)
{
	HASH_TESTING_ENGINE engine;
	int status;
	char *message = "Test";
	uint8_t key[SHA256_BLOCK_SIZE + 1];
	uint8_t hmac[SHA256_HASH_LENGTH];
	uint8_t expected[] = {
		0xf1, 0x3b, 0x43, 0x16, 0x2c, 0xe4, 0x05, 0x75, 0x73, 0xc5, 0x54, 0x10, 0xad, 0xd5, 0xc5,
		0xc6,
		0x0e, 0x9a, 0x37, 0xff, 0x3e, 0xa0, 0x02, 0x34, 0xd6, 0x41, 0x80, 0xfa, 0x1a, 0x0e, 0x0a,
		0x04
	};
	struct hmac_engine hmac_engine;
	int i;

	TEST_START;

	for (i = 0; i < (int) sizeof (key); i++) {
		key[i] = i;
	}

	status = HASH_TESTING_ENGINE_INIT (&engine);
	CuAssertIntEquals (test, 0, status);

	status = hash_hmac_init (&hmac_engine, &engine.base, HMAC_SHA256, key, sizeof (key));
	CuAssertIntEquals (test, 0, status);

	status = hash_hmac_update (&hmac_engine, (uint8_t*) message, strlen (message));
	CuAssertIntEquals (test, 0, status);

	status = hash_hmac_finish (&hmac_engine, hmac, sizeof (hmac));
	CuAssertIntEquals (test, 0, status);

	status = testing_validate_array (expected, hmac, sizeof (hmac));
	CuAssertIntEquals (test, 0, status);

	HASH_TESTING_ENGINE_RELEASE (&engine);
}

static void hash_test_hmac_sha384_incremental (CuTest *test)
{
	HASH_TESTING_ENGINE engine;
	int status;
	char *message = "Test";
	uint8_t key[] = {0x31, 0x32, 0x33, 0x34};
	uint8_t hmac[SHA384_HASH_LENGTH];
	uint8_t expected[] = {
		0xd3, 0x31, 0xf1, 0x53, 0x07, 0x7e, 0xfb, 0xad, 0x73, 0x8e, 0xea, 0x4f, 0x3e, 0x0c, 0x5d,
		0x3f,
		0x6b, 0x60, 0x4d, 0x7b, 0x32, 0xb6, 0xa2, 0xe8, 0xb0, 0xeb, 0x4e, 0x4e, 0x7f, 0xc9, 0x52,
		0x7b,
		0xc6, 0x04, 0x44, 0xf2, 0x04, 0x7e, 0xac, 0xc1, 0xec, 0x88, 0x0b, 0xff, 0xd0, 0xb1, 0xc1,
		0xf2
	};
	struct hmac_engine hmac_engine;

	TEST_START;

	status = HASH_TESTING_ENGINE_INIT (&engine);
	CuAssertIntEquals (test, 0, status);

	status = hash_hmac_init (&hmac_engine, &engine.base, HMAC_SHA384, key, sizeof (key));
#ifdef HASH_ENABLE_SHA384
	CuAssertIntEquals (test, 0, status);

	status = hash_hmac_update (&hmac_engine, (uint8_t*) message, strlen (message));
	CuAssertIntEquals (test, 0, status);

	status = hash_hmac_finish (&hmac_engine, hmac, sizeof (hmac));
	CuAssertIntEquals (test, 0, status);

	status = testing_validate_array (expected, hmac, sizeof (hmac));
	CuAssertIntEquals (test, 0, status);
#else
	CuAssertIntEquals (test, HASH_ENGINE_UNSUPPORTED_HASH, status);
#endif

	HASH_TESTING_ENGINE_RELEASE (&engine);
}

#ifdef HASH_ENABLE_SHA384
static void hash_test_hmac_sha384_incremental_large_key (CuTest *test)
{
	HASH_TESTING_ENGINE engine;
	int status;
	char *message = "Test";
	uint8_t key[SHA384_BLOCK_SIZE + 1];
	uint8_t hmac[SHA384_HASH_LENGTH];
	uint8_t expected[] = {
		0xf8, 0xa1, 0x45, 0x7e, 0x62, 0xdf, 0x77, 0xff, 0x48, 0x98, 0xf4, 0xc6, 0x3b, 0xa3, 0x45,
		0x29,
		0x3b, 0x1e, 0x50, 0x5c, 0x90, 0x9c, 0xd3, 0x00, 0x70, 0xc9, 0x90, 0x18, 0xe2, 0xa1, 0x3f,
		0xec,
		0x54, 0xaf, 0x70, 0x65, 0xc5, 0x3b, 0x97, 0xf7, 0x63, 0x30, 0x9e, 0x28, 0xd1, 0xcf, 0x1f,
		0x0f
	};
	struct hmac_engine hmac_engine;
	int i;

	TEST_START;

	for (i = 0; i < (int) sizeof (key); i++) {
		key[i] = i;
	}

	status = HASH_TESTING_ENGINE_INIT (&engine);
	CuAssertIntEquals (test, 0, status);

	status = hash_hmac_init (&hmac_engine, &engine.base, HMAC_SHA384, key, sizeof (key));
	CuAssertIntEquals (test, 0, status);

	status = hash_hmac_update (&hmac_engine, (uint8_t*) message, strlen (message));
	CuAssertIntEquals (test, 0, status);

	status = hash_hmac_finish (&hmac_engine, hmac, sizeof (hmac));
	CuAssertIntEquals (test, 0, status);

	status = testing_validate_array (expected, hmac, sizeof (hmac));
	CuAssertIntEquals (test, 0, status);

	HASH_TESTING_ENGINE_RELEASE (&engine);
}
#endif

static void hash_test_hmac_sha512_incremental (CuTest *test)
{
	HASH_TESTING_ENGINE engine;
	int status;
	char *message = "Test";
	uint8_t key[] = {0x31, 0x32, 0x33, 0x34};
	uint8_t hmac[SHA512_HASH_LENGTH];
	uint8_t expected[] = {
		0x39, 0xb8, 0x29, 0x9b, 0x43, 0x30, 0xcb, 0x1e, 0x8b, 0x51, 0xfa, 0xcb, 0x76, 0x79, 0xaf,
		0x47,
		0xea, 0x35, 0xbf, 0xea, 0xb9, 0x1b, 0x34, 0xd0, 0x9e, 0x0a, 0xac, 0xc9, 0xde, 0x64, 0x80,
		0x60,
		0x29, 0x8d, 0x86, 0xd5, 0x47, 0x9d, 0x4e, 0xb5, 0x68, 0xdf, 0xe0, 0xea, 0xb6, 0x2c, 0x0e,
		0x4a,
		0x47, 0x90, 0x7e, 0x28, 0x09, 0xb8, 0x4b, 0x21, 0xdd, 0x6b, 0xc7, 0x41, 0xca, 0x09, 0x00,
		0x3a
	};
	struct hmac_engine hmac_engine;

	TEST_START;

	status = HASH_TESTING_ENGINE_INIT (&engine);
	CuAssertIntEquals (test, 0, status);

	status = hash_hmac_init (&hmac_engine, &engine.base, HMAC_SHA512, key, sizeof (key));
#ifdef HASH_ENABLE_SHA512
	CuAssertIntEquals (test, 0, status);

	status = hash_hmac_update (&hmac_engine, (uint8_t*) message, strlen (message));
	CuAssertIntEquals (test, 0, status);

	status = hash_hmac_finish (&hmac_engine, hmac, sizeof (hmac));
	CuAssertIntEquals (test, 0, status);

	status = testing_validate_array (expected, hmac, sizeof (hmac));
	CuAssertIntEquals (test, 0, status);
#else
	CuAssertIntEquals (test, HASH_ENGINE_UNSUPPORTED_HASH, status);
#endif

	HASH_TESTING_ENGINE_RELEASE (&engine);
}

#ifdef HASH_ENABLE_SHA512
static void hash_test_hmac_sha512_incremental_large_key (CuTest *test)
{
	HASH_TESTING_ENGINE engine;
	int status;
	char *message = "Test";
	uint8_t key[SHA512_BLOCK_SIZE + 1];
	uint8_t hmac[SHA512_HASH_LENGTH];
	uint8_t expected[] = {
		0x4b, 0xf9, 0x6c, 0x4d, 0x3d, 0x7f, 0xac, 0x2f, 0x10, 0x48, 0xc2, 0x96, 0x78, 0xe1, 0x07,
		0x95,
		0x33, 0xa1, 0x47, 0x37, 0x5b, 0x1e, 0xdd, 0x2d, 0x5f, 0xa4, 0xbc, 0xf6, 0x22, 0x40, 0x9f,
		0x96,
		0x4b, 0x54, 0x59, 0xab, 0xaa, 0x6f, 0x7b, 0x58, 0x56, 0x14, 0xe1, 0x78, 0x6b, 0x0e, 0xd8,
		0xf7,
		0x75, 0x45, 0xcb, 0x90, 0x1d, 0xd6, 0xd6, 0x12, 0xc2, 0x33, 0xb2, 0x53, 0xb3, 0x17, 0x05,
		0x5d
	};
	struct hmac_engine hmac_engine;
	int i;

	TEST_START;

	for (i = 0; i < (int) sizeof (key); i++) {
		key[i] = i;
	}

	status = HASH_TESTING_ENGINE_INIT (&engine);
	CuAssertIntEquals (test, 0, status);

	status = hash_hmac_init (&hmac_engine, &engine.base, HMAC_SHA512, key, sizeof (key));
	CuAssertIntEquals (test, 0, status);

	status = hash_hmac_update (&hmac_engine, (uint8_t*) message, strlen (message));
	CuAssertIntEquals (test, 0, status);

	status = hash_hmac_finish (&hmac_engine, hmac, sizeof (hmac));
	CuAssertIntEquals (test, 0, status);

	status = testing_validate_array (expected, hmac, sizeof (hmac));
	CuAssertIntEquals (test, 0, status);

	HASH_TESTING_ENGINE_RELEASE (&engine);
}
#endif

static void hash_test_hmac_cancel (CuTest *test)
{
	HASH_TESTING_ENGINE engine;
	int status;
	char *message = "Test";
	uint8_t key[] = {0x31, 0x32, 0x33, 0x34};
	uint8_t hmac[SHA256_HASH_LENGTH];
	struct hmac_engine hmac_engine;

	TEST_START;

	status = HASH_TESTING_ENGINE_INIT (&engine);
	CuAssertIntEquals (test, 0, status);

	status = hash_hmac_init (&hmac_engine, &engine.base, HMAC_SHA256, key, sizeof (key));
	CuAssertIntEquals (test, 0, status);

	hash_hmac_cancel (&hmac_engine);

	status = hash_hmac_update (&hmac_engine, (uint8_t*) message, strlen (message));
	CuAssertIntEquals (test, HASH_ENGINE_NO_ACTIVE_HASH, status);

	status = hash_hmac_finish (&hmac_engine, hmac, sizeof (hmac));
	CuAssertIntEquals (test, HASH_ENGINE_NO_ACTIVE_HASH, status);

	HASH_TESTING_ENGINE_RELEASE (&engine);
}

static void hash_test_hmac_init_null (CuTest *test)
{
	HASH_TESTING_ENGINE engine;
	int status;
	uint8_t key[] = {0x31, 0x32, 0x33, 0x34};
	struct hmac_engine hmac_engine;

	TEST_START;

	status = HASH_TESTING_ENGINE_INIT (&engine);
	CuAssertIntEquals (test, 0, status);

	status = hash_hmac_init (NULL, &engine.base, HMAC_SHA256, key, sizeof (key));
	CuAssertIntEquals (test, HASH_ENGINE_INVALID_ARGUMENT, status);

	status = hash_hmac_init (&hmac_engine, NULL, HMAC_SHA256, key, sizeof (key));
	CuAssertIntEquals (test, HASH_ENGINE_INVALID_ARGUMENT, status);

	status = hash_hmac_init (&hmac_engine, &engine.base, HMAC_SHA256, NULL, sizeof (key));
	CuAssertIntEquals (test, HASH_ENGINE_INVALID_ARGUMENT, status);

	status = hash_hmac_init (&hmac_engine, &engine.base, HMAC_SHA256, key, 0);
	CuAssertIntEquals (test, HASH_ENGINE_INVALID_ARGUMENT, status);

	HASH_TESTING_ENGINE_RELEASE (&engine);
}

static void hash_test_hmac_init_unknown (CuTest *test)
{
	HASH_TESTING_ENGINE engine;
	int status;
	uint8_t key[] = {0x31, 0x32, 0x33, 0x34};
	struct hmac_engine hmac_engine;

	TEST_START;

	status = HASH_TESTING_ENGINE_INIT (&engine);
	CuAssertIntEquals (test, 0, status);

	status = hash_hmac_init (&hmac_engine, &engine.base, (enum hmac_hash) 4, key, sizeof (key));
	CuAssertIntEquals (test, HASH_ENGINE_UNKNOWN_HASH, status);

	HASH_TESTING_ENGINE_RELEASE (&engine);
}

static void hash_test_hmac_init_error (CuTest *test)
{
	struct hash_engine_mock engine;
	int status;
	uint8_t key[] = {0x31, 0x32, 0x33, 0x34};
	struct hmac_engine hmac_engine;

	TEST_START;

	status = hash_mock_init (&engine);
	CuAssertIntEquals (test, 0, status);

	status = mock_expect (&engine.mock, engine.base.start_sha256, &engine, 0);

	status |= mock_expect (&engine.mock, engine.base.update, &engine, HASH_ENGINE_UPDATE_FAILED,
		MOCK_ARG_NOT_NULL, MOCK_ARG (SHA1_BLOCK_SIZE));
	status |= mock_expect (&engine.mock, engine.base.cancel, &engine, 0);

	CuAssertIntEquals (test, 0, status);

	status = hash_hmac_init (&hmac_engine, &engine.base, HMAC_SHA256, key, sizeof (key));
	CuAssertIntEquals (test, HASH_ENGINE_UPDATE_FAILED, status);

	status = hash_mock_validate_and_release (&engine);
	CuAssertIntEquals (test, 0, status);
}

#ifdef HASH_ENABLE_SHA1
static void hash_test_hmac_init_sha1_large_key_error (CuTest *test)
{
	struct hash_engine_mock engine;
	int status;
	uint8_t key[SHA1_BLOCK_SIZE + 1];
	struct hmac_engine hmac_engine;
	int i;

	TEST_START;

	for (i = 0; i < (int) sizeof (key); i++) {
		key[i] = i;
	}

	status = hash_mock_init (&engine);
	CuAssertIntEquals (test, 0, status);

	status = mock_expect (&engine.mock, engine.base.calculate_sha1, &engine,
		HASH_ENGINE_SHA1_FAILED, MOCK_ARG_PTR (key), MOCK_ARG (sizeof (key)), MOCK_ARG_NOT_NULL,
		MOCK_ARG_ANY);
	CuAssertIntEquals (test, 0, status);

	status = hash_hmac_init (&hmac_engine, &engine.base, HMAC_SHA1, key, sizeof (key));
	CuAssertIntEquals (test, HASH_ENGINE_SHA1_FAILED, status);

	status = hash_mock_validate_and_release (&engine);
	CuAssertIntEquals (test, 0, status);
}
#endif

static void hash_test_hmac_init_sha256_large_key_error (CuTest *test)
{
	struct hash_engine_mock engine;
	int status;
	uint8_t key[SHA256_BLOCK_SIZE + 1];
	struct hmac_engine hmac_engine;
	int i;

	TEST_START;

	for (i = 0; i < (int) sizeof (key); i++) {
		key[i] = i;
	}

	status = hash_mock_init (&engine);
	CuAssertIntEquals (test, 0, status);

	status = mock_expect (&engine.mock, engine.base.calculate_sha256, &engine,
		HASH_ENGINE_SHA256_FAILED, MOCK_ARG_PTR (key), MOCK_ARG (sizeof (key)), MOCK_ARG_NOT_NULL,
		MOCK_ARG_ANY);
	CuAssertIntEquals (test, 0, status);

	status = hash_hmac_init (&hmac_engine, &engine.base, HMAC_SHA256, key, sizeof (key));
	CuAssertIntEquals (test, HASH_ENGINE_SHA256_FAILED, status);

	status = hash_mock_validate_and_release (&engine);
	CuAssertIntEquals (test, 0, status);
}

#ifdef HASH_ENABLE_SHA384
static void hash_test_hmac_init_sha384_large_key_error (CuTest *test)
{
	struct hash_engine_mock engine;
	int status;
	uint8_t key[SHA384_BLOCK_SIZE + 1];
	struct hmac_engine hmac_engine;
	int i;

	TEST_START;

	for (i = 0; i < (int) sizeof (key); i++) {
		key[i] = i;
	}

	status = hash_mock_init (&engine);
	CuAssertIntEquals (test, 0, status);

	status = mock_expect (&engine.mock, engine.base.calculate_sha384, &engine,
		HASH_ENGINE_SHA384_FAILED, MOCK_ARG_PTR (key), MOCK_ARG (sizeof (key)), MOCK_ARG_NOT_NULL,
		MOCK_ARG_ANY);
	CuAssertIntEquals (test, 0, status);

	status = hash_hmac_init (&hmac_engine, &engine.base, HMAC_SHA384, key, sizeof (key));
	CuAssertIntEquals (test, HASH_ENGINE_SHA384_FAILED, status);

	status = hash_mock_validate_and_release (&engine);
	CuAssertIntEquals (test, 0, status);
}
#endif

#ifdef HASH_ENABLE_SHA512
static void hash_test_hmac_init_sha512_large_key_error (CuTest *test)
{
	struct hash_engine_mock engine;
	int status;
	uint8_t key[SHA512_BLOCK_SIZE + 1];
	struct hmac_engine hmac_engine;
	int i;

	TEST_START;

	for (i = 0; i < (int) sizeof (key); i++) {
		key[i] = i;
	}

	status = hash_mock_init (&engine);
	CuAssertIntEquals (test, 0, status);

	status = mock_expect (&engine.mock, engine.base.calculate_sha512, &engine,
		HASH_ENGINE_SHA512_FAILED, MOCK_ARG_PTR (key), MOCK_ARG (sizeof (key)), MOCK_ARG_NOT_NULL,
		MOCK_ARG_ANY);
	CuAssertIntEquals (test, 0, status);

	status = hash_hmac_init (&hmac_engine, &engine.base, HMAC_SHA512, key, sizeof (key));
	CuAssertIntEquals (test, HASH_ENGINE_SHA512_FAILED, status);

	status = hash_mock_validate_and_release (&engine);
	CuAssertIntEquals (test, 0, status);
}
#endif

static void hash_test_hmac_update_null (CuTest *test)
{
	HASH_TESTING_ENGINE engine;
	int status;
	char *message = "Test";
	uint8_t key[] = {0x31, 0x32, 0x33, 0x34};
	struct hmac_engine hmac_engine;

	TEST_START;

	status = HASH_TESTING_ENGINE_INIT (&engine);
	CuAssertIntEquals (test, 0, status);

	status = hash_hmac_init (&hmac_engine, &engine.base, HMAC_SHA256, key, sizeof (key));
	CuAssertIntEquals (test, 0, status);

	status = hash_hmac_update (NULL, (uint8_t*) message, strlen (message));
	CuAssertIntEquals (test, HASH_ENGINE_INVALID_ARGUMENT, status);

	status = hash_hmac_update (&hmac_engine, NULL, strlen (message));
	CuAssertIntEquals (test, HASH_ENGINE_INVALID_ARGUMENT, status);

	HASH_TESTING_ENGINE_RELEASE (&engine);
}

static void hash_test_hmac_finish_null (CuTest *test)
{
	HASH_TESTING_ENGINE engine;
	int status;
	char *message = "Test";
	uint8_t key[] = {0x31, 0x32, 0x33, 0x34};
	uint8_t hmac[SHA256_HASH_LENGTH];
	struct hmac_engine hmac_engine;

	TEST_START;

	status = HASH_TESTING_ENGINE_INIT (&engine);
	CuAssertIntEquals (test, 0, status);

	status = hash_hmac_init (&hmac_engine, &engine.base, HMAC_SHA256, key, sizeof (key));
	CuAssertIntEquals (test, 0, status);

	status = hash_hmac_update (&hmac_engine, (uint8_t*) message, strlen (message));
	CuAssertIntEquals (test, 0, status);

	status = hash_hmac_finish (NULL, hmac, sizeof (hmac));
	CuAssertIntEquals (test, HASH_ENGINE_INVALID_ARGUMENT, status);

	status = hash_hmac_finish (&hmac_engine, NULL, sizeof (hmac));
	CuAssertIntEquals (test, HASH_ENGINE_INVALID_ARGUMENT, status);

	HASH_TESTING_ENGINE_RELEASE (&engine);
}

#ifdef HASH_ENABLE_SHA1
static void hash_test_hmac_finish_sha1_small_buffer (CuTest *test)
{
	HASH_TESTING_ENGINE engine;
	int status;
	char *message = "Test";
	uint8_t key[] = {0x31, 0x32, 0x33, 0x34};
	uint8_t hmac[SHA1_HASH_LENGTH];
	uint8_t expected[] = {
		0xfc, 0x3d, 0x91, 0xe6, 0xc1, 0x13, 0xd6, 0x82, 0x18, 0x33, 0xf6, 0x5b, 0x12, 0xc7, 0xe7,
		0x6e,
		0x7f, 0x38, 0x9c, 0x4f
	};
	struct hmac_engine hmac_engine;

	TEST_START;

	status = HASH_TESTING_ENGINE_INIT (&engine);
	CuAssertIntEquals (test, 0, status);

	status = hash_hmac_init (&hmac_engine, &engine.base, HMAC_SHA1, key, sizeof (key));
	CuAssertIntEquals (test, 0, status);

	status = hash_hmac_update (&hmac_engine, (uint8_t*) message, strlen (message));
	CuAssertIntEquals (test, 0, status);

	status = hash_hmac_finish (&hmac_engine, hmac, sizeof (hmac) - 1);
	CuAssertIntEquals (test, HASH_ENGINE_HASH_BUFFER_TOO_SMALL, status);

	status = hash_hmac_finish (&hmac_engine, hmac, sizeof (hmac));
	CuAssertIntEquals (test, 0, status);

	status = testing_validate_array (expected, hmac, sizeof (hmac));
	CuAssertIntEquals (test, 0, status);

	HASH_TESTING_ENGINE_RELEASE (&engine);
}
#endif

static void hash_test_hmac_finish_sha256_small_buffer (CuTest *test)
{
	HASH_TESTING_ENGINE engine;
	int status;
	char *message = "Test";
	uint8_t key[] = {0x31, 0x32, 0x33, 0x34};
	uint8_t hmac[SHA256_HASH_LENGTH];
	uint8_t expected[] = {
		0x88, 0x69, 0xde, 0x57, 0x9d, 0xd0, 0xe9, 0x05, 0xe0, 0xa7, 0x11, 0x24, 0x57, 0x55, 0x94,
		0xf5,
		0x0a, 0x03, 0xd3, 0xd9, 0xcd, 0xf1, 0x6e, 0x9a, 0x3f, 0x9d, 0x6c, 0x60, 0xc0, 0x32, 0x4b,
		0x54
	};
	struct hmac_engine hmac_engine;

	TEST_START;

	status = HASH_TESTING_ENGINE_INIT (&engine);
	CuAssertIntEquals (test, 0, status);

	status = hash_hmac_init (&hmac_engine, &engine.base, HMAC_SHA256, key, sizeof (key));
	CuAssertIntEquals (test, 0, status);

	status = hash_hmac_update (&hmac_engine, (uint8_t*) message, strlen (message));
	CuAssertIntEquals (test, 0, status);

	status = hash_hmac_finish (&hmac_engine, hmac, sizeof (hmac) - 1);
	CuAssertIntEquals (test, HASH_ENGINE_HASH_BUFFER_TOO_SMALL, status);

	status = hash_hmac_finish (&hmac_engine, hmac, sizeof (hmac));
	CuAssertIntEquals (test, 0, status);

	status = testing_validate_array (expected, hmac, sizeof (hmac));
	CuAssertIntEquals (test, 0, status);

	HASH_TESTING_ENGINE_RELEASE (&engine);
}

#ifdef HASH_ENABLE_SHA384
static void hash_test_hmac_finish_sha384_small_buffer (CuTest *test)
{
	HASH_TESTING_ENGINE engine;
	int status;
	char *message = "Test";
	uint8_t key[] = {0x31, 0x32, 0x33, 0x34};
	uint8_t hmac[SHA384_HASH_LENGTH];
	uint8_t expected[] = {
		0xd3, 0x31, 0xf1, 0x53, 0x07, 0x7e, 0xfb, 0xad, 0x73, 0x8e, 0xea, 0x4f, 0x3e, 0x0c, 0x5d,
		0x3f,
		0x6b, 0x60, 0x4d, 0x7b, 0x32, 0xb6, 0xa2, 0xe8, 0xb0, 0xeb, 0x4e, 0x4e, 0x7f, 0xc9, 0x52,
		0x7b,
		0xc6, 0x04, 0x44, 0xf2, 0x04, 0x7e, 0xac, 0xc1, 0xec, 0x88, 0x0b, 0xff, 0xd0, 0xb1, 0xc1,
		0xf2
	};
	struct hmac_engine hmac_engine;

	TEST_START;

	status = HASH_TESTING_ENGINE_INIT (&engine);
	CuAssertIntEquals (test, 0, status);

	status = hash_hmac_init (&hmac_engine, &engine.base, HMAC_SHA384, key, sizeof (key));
	CuAssertIntEquals (test, 0, status);

	status = hash_hmac_update (&hmac_engine, (uint8_t*) message, strlen (message));
	CuAssertIntEquals (test, 0, status);

	status = hash_hmac_finish (&hmac_engine, hmac, sizeof (hmac) - 1);
	CuAssertIntEquals (test, HASH_ENGINE_HASH_BUFFER_TOO_SMALL, status);

	status = hash_hmac_finish (&hmac_engine, hmac, sizeof (hmac));
	CuAssertIntEquals (test, 0, status);

	status = testing_validate_array (expected, hmac, sizeof (hmac));
	CuAssertIntEquals (test, 0, status);

	HASH_TESTING_ENGINE_RELEASE (&engine);
}
#endif

#ifdef HASH_ENABLE_SHA512
static void hash_test_hmac_finish_sha512_small_buffer (CuTest *test)
{
	HASH_TESTING_ENGINE engine;
	int status;
	char *message = "Test";
	uint8_t key[] = {0x31, 0x32, 0x33, 0x34};
	uint8_t hmac[SHA512_HASH_LENGTH];
	uint8_t expected[] = {
		0x39, 0xb8, 0x29, 0x9b, 0x43, 0x30, 0xcb, 0x1e, 0x8b, 0x51, 0xfa, 0xcb, 0x76, 0x79, 0xaf,
		0x47,
		0xea, 0x35, 0xbf, 0xea, 0xb9, 0x1b, 0x34, 0xd0, 0x9e, 0x0a, 0xac, 0xc9, 0xde, 0x64, 0x80,
		0x60,
		0x29, 0x8d, 0x86, 0xd5, 0x47, 0x9d, 0x4e, 0xb5, 0x68, 0xdf, 0xe0, 0xea, 0xb6, 0x2c, 0x0e,
		0x4a,
		0x47, 0x90, 0x7e, 0x28, 0x09, 0xb8, 0x4b, 0x21, 0xdd, 0x6b, 0xc7, 0x41, 0xca, 0x09, 0x00,
		0x3a
	};
	struct hmac_engine hmac_engine;

	TEST_START;

	status = HASH_TESTING_ENGINE_INIT (&engine);
	CuAssertIntEquals (test, 0, status);

	status = hash_hmac_init (&hmac_engine, &engine.base, HMAC_SHA512, key, sizeof (key));
	CuAssertIntEquals (test, 0, status);

	status = hash_hmac_update (&hmac_engine, (uint8_t*) message, strlen (message));
	CuAssertIntEquals (test, 0, status);

	status = hash_hmac_finish (&hmac_engine, hmac, sizeof (hmac) - 1);
	CuAssertIntEquals (test, HASH_ENGINE_HASH_BUFFER_TOO_SMALL, status);

	status = hash_hmac_finish (&hmac_engine, hmac, sizeof (hmac));
	CuAssertIntEquals (test, 0, status);

	status = testing_validate_array (expected, hmac, sizeof (hmac));
	CuAssertIntEquals (test, 0, status);

	HASH_TESTING_ENGINE_RELEASE (&engine);
}
#endif

static void hash_test_hmac_finish_inner_hash_error (CuTest *test)
{
	struct hash_engine_mock engine;
	int status;
	char *message = "Test";
	uint8_t key[] = {0x31, 0x32, 0x33, 0x34};
	uint8_t hmac[SHA256_HASH_LENGTH];
	struct hmac_engine hmac_engine;

	TEST_START;

	status = hash_mock_init (&engine);
	CuAssertIntEquals (test, 0, status);

	status = mock_expect (&engine.mock, engine.base.start_sha256, &engine, 0);
	status |= mock_expect (&engine.mock, engine.base.update, &engine, 0, MOCK_ARG_NOT_NULL,
		MOCK_ARG (SHA256_BLOCK_SIZE));

	status |= mock_expect (&engine.mock, engine.base.update, &engine, 0, MOCK_ARG_PTR (message),
		MOCK_ARG (strlen (message)));

	status |= mock_expect (&engine.mock, engine.base.finish, &engine, HASH_ENGINE_FINISH_FAILED,
		MOCK_ARG_NOT_NULL, MOCK_ARG (SHA512_HASH_LENGTH));
	status |= mock_expect (&engine.mock, engine.base.cancel, &engine, 0);

	CuAssertIntEquals (test, 0, status);

	status = hash_hmac_init (&hmac_engine, &engine.base, HMAC_SHA256, key, sizeof (key));
	CuAssertIntEquals (test, 0, status);

	status = hash_hmac_update (&hmac_engine, (uint8_t*) message, strlen (message));
	CuAssertIntEquals (test, 0, status);

	status = hash_hmac_finish (&hmac_engine, hmac, sizeof (hmac));
	CuAssertIntEquals (test, HASH_ENGINE_FINISH_FAILED, status);

	status = hash_mock_validate_and_release (&engine);
	CuAssertIntEquals (test, 0, status);
}

static void hash_test_hmac_finish_outer_init_error (CuTest *test)
{
	struct hash_engine_mock engine;
	int status;
	char *message = "Test";
	uint8_t key[] = {0x31, 0x32, 0x33, 0x34};
	uint8_t hmac[SHA256_HASH_LENGTH];
	struct hmac_engine hmac_engine;

	TEST_START;

	status = hash_mock_init (&engine);
	CuAssertIntEquals (test, 0, status);

	status = mock_expect (&engine.mock, engine.base.start_sha256, &engine, 0);
	status |= mock_expect (&engine.mock, engine.base.update, &engine, 0, MOCK_ARG_NOT_NULL,
		MOCK_ARG (SHA256_BLOCK_SIZE));

	status |= mock_expect (&engine.mock, engine.base.update, &engine, 0, MOCK_ARG_PTR (message),
		MOCK_ARG (strlen (message)));

	status |= mock_expect (&engine.mock, engine.base.finish, &engine, 0, MOCK_ARG_NOT_NULL,
		MOCK_ARG (SHA512_HASH_LENGTH));

	status |= mock_expect (&engine.mock, engine.base.start_sha256, &engine,
		HASH_ENGINE_START_SHA256_FAILED);
	status |= mock_expect (&engine.mock, engine.base.cancel, &engine, 0);

	CuAssertIntEquals (test, 0, status);

	status = hash_hmac_init (&hmac_engine, &engine.base, HMAC_SHA256, key, sizeof (key));
	CuAssertIntEquals (test, 0, status);

	status = hash_hmac_update (&hmac_engine, (uint8_t*) message, strlen (message));
	CuAssertIntEquals (test, 0, status);

	status = hash_hmac_finish (&hmac_engine, hmac, sizeof (hmac));
	CuAssertIntEquals (test, HASH_ENGINE_START_SHA256_FAILED, status);

	status = hash_mock_validate_and_release (&engine);
	CuAssertIntEquals (test, 0, status);
}

static void hash_test_hmac_finish_outer_key_error (CuTest *test)
{
	struct hash_engine_mock engine;
	int status;
	char *message = "Test";
	uint8_t key[] = {0x31, 0x32, 0x33, 0x34};
	uint8_t hmac[SHA256_HASH_LENGTH];
	struct hmac_engine hmac_engine;

	TEST_START;

	status = hash_mock_init (&engine);
	CuAssertIntEquals (test, 0, status);

	status = mock_expect (&engine.mock, engine.base.start_sha256, &engine, 0);
	status |= mock_expect (&engine.mock, engine.base.update, &engine, 0, MOCK_ARG_NOT_NULL,
		MOCK_ARG (SHA256_BLOCK_SIZE));

	status |= mock_expect (&engine.mock, engine.base.update, &engine, 0, MOCK_ARG_PTR (message),
		MOCK_ARG (strlen (message)));

	status |= mock_expect (&engine.mock, engine.base.finish, &engine, 0, MOCK_ARG_NOT_NULL,
		MOCK_ARG (SHA512_HASH_LENGTH));

	status |= mock_expect (&engine.mock, engine.base.start_sha256, &engine, 0);

	status |= mock_expect (&engine.mock, engine.base.update, &engine, HASH_ENGINE_UPDATE_FAILED,
		MOCK_ARG_NOT_NULL, MOCK_ARG (SHA256_BLOCK_SIZE));
	status |= mock_expect (&engine.mock, engine.base.cancel, &engine, 0);

	CuAssertIntEquals (test, 0, status);

	status = hash_hmac_init (&hmac_engine, &engine.base, HMAC_SHA256, key, sizeof (key));
	CuAssertIntEquals (test, 0, status);

	status = hash_hmac_update (&hmac_engine, (uint8_t*) message, strlen (message));
	CuAssertIntEquals (test, 0, status);

	status = hash_hmac_finish (&hmac_engine, hmac, sizeof (hmac));
	CuAssertIntEquals (test, HASH_ENGINE_UPDATE_FAILED, status);

	status = hash_mock_validate_and_release (&engine);
	CuAssertIntEquals (test, 0, status);
}

static void hash_test_hmac_finish_outer_update_error (CuTest *test)
{
	struct hash_engine_mock engine;
	int status;
	char *message = "Test";
	uint8_t key[] = {0x31, 0x32, 0x33, 0x34};
	uint8_t hmac[SHA256_HASH_LENGTH];
	struct hmac_engine hmac_engine;

	TEST_START;

	status = hash_mock_init (&engine);
	CuAssertIntEquals (test, 0, status);

	status = mock_expect (&engine.mock, engine.base.start_sha256, &engine, 0);
	status |= mock_expect (&engine.mock, engine.base.update, &engine, 0, MOCK_ARG_NOT_NULL,
		MOCK_ARG (SHA256_BLOCK_SIZE));

	status |= mock_expect (&engine.mock, engine.base.update, &engine, 0, MOCK_ARG_PTR (message),
		MOCK_ARG (strlen (message)));

	status |= mock_expect (&engine.mock, engine.base.finish, &engine, 0, MOCK_ARG_NOT_NULL,
		MOCK_ARG (SHA512_HASH_LENGTH));

	status |= mock_expect (&engine.mock, engine.base.start_sha256, &engine, 0);

	status |= mock_expect (&engine.mock, engine.base.update, &engine, 0, MOCK_ARG_NOT_NULL,
		MOCK_ARG (SHA256_BLOCK_SIZE));

	status |= mock_expect (&engine.mock, engine.base.update, &engine, HASH_ENGINE_UPDATE_FAILED,
		MOCK_ARG_NOT_NULL, MOCK_ARG (SHA256_HASH_LENGTH));
	status |= mock_expect (&engine.mock, engine.base.cancel, &engine, 0);

	CuAssertIntEquals (test, 0, status);

	status = hash_hmac_init (&hmac_engine, &engine.base, HMAC_SHA256, key, sizeof (key));
	CuAssertIntEquals (test, 0, status);

	status = hash_hmac_update (&hmac_engine, (uint8_t*) message, strlen (message));
	CuAssertIntEquals (test, 0, status);

	status = hash_hmac_finish (&hmac_engine, hmac, sizeof (hmac));
	CuAssertIntEquals (test, HASH_ENGINE_UPDATE_FAILED, status);

	status = hash_mock_validate_and_release (&engine);
	CuAssertIntEquals (test, 0, status);
}

static void hash_test_hmac_finish_outer_hash_error (CuTest *test)
{
	struct hash_engine_mock engine;
	int status;
	char *message = "Test";
	uint8_t key[] = {0x31, 0x32, 0x33, 0x34};
	uint8_t hmac[SHA256_HASH_LENGTH];
	struct hmac_engine hmac_engine;

	TEST_START;

	status = hash_mock_init (&engine);
	CuAssertIntEquals (test, 0, status);

	status = mock_expect (&engine.mock, engine.base.start_sha256, &engine, 0);
	status |= mock_expect (&engine.mock, engine.base.update, &engine, 0, MOCK_ARG_NOT_NULL,
		MOCK_ARG (SHA256_BLOCK_SIZE));

	status |= mock_expect (&engine.mock, engine.base.update, &engine, 0, MOCK_ARG_PTR (message),
		MOCK_ARG (strlen (message)));

	status |= mock_expect (&engine.mock, engine.base.finish, &engine, 0, MOCK_ARG_NOT_NULL,
		MOCK_ARG (SHA512_HASH_LENGTH));

	status |= mock_expect (&engine.mock, engine.base.start_sha256, &engine, 0);

	status |= mock_expect (&engine.mock, engine.base.update, &engine, 0, MOCK_ARG_NOT_NULL,
		MOCK_ARG (SHA256_BLOCK_SIZE));

	status |= mock_expect (&engine.mock, engine.base.update, &engine, 0, MOCK_ARG_NOT_NULL,
		MOCK_ARG (SHA256_HASH_LENGTH));

	status |= mock_expect (&engine.mock, engine.base.finish, &engine, HASH_ENGINE_FINISH_FAILED,
		MOCK_ARG_PTR (hmac), MOCK_ARG (SHA256_HASH_LENGTH));
	status |= mock_expect (&engine.mock, engine.base.cancel, &engine, 0);

	CuAssertIntEquals (test, 0, status);

	status = hash_hmac_init (&hmac_engine, &engine.base, HMAC_SHA256, key, sizeof (key));
	CuAssertIntEquals (test, 0, status);

	status = hash_hmac_update (&hmac_engine, (uint8_t*) message, strlen (message));
	CuAssertIntEquals (test, 0, status);

	status = hash_hmac_finish (&hmac_engine, hmac, sizeof (hmac));
	CuAssertIntEquals (test, HASH_ENGINE_FINISH_FAILED, status);

	status = hash_mock_validate_and_release (&engine);
	CuAssertIntEquals (test, 0, status);
}

static void hash_test_hmac_cancel_null (CuTest *test)
{
	TEST_START;

	hash_hmac_cancel (NULL);
}

static void hash_test_hmac_sha1 (CuTest *test)
{
	HASH_TESTING_ENGINE engine;
	int status;
	char *message = "Test";
	uint8_t key[] = {0x31, 0x32, 0x33, 0x34};
	uint8_t hmac[SHA1_HASH_LENGTH];
	uint8_t expected[] = {
		0xfc, 0x3d, 0x91, 0xe6, 0xc1, 0x13, 0xd6, 0x82, 0x18, 0x33, 0xf6, 0x5b, 0x12, 0xc7, 0xe7,
		0x6e,
		0x7f, 0x38, 0x9c, 0x4f
	};

	TEST_START;

	status = HASH_TESTING_ENGINE_INIT (&engine);
	CuAssertIntEquals (test, 0, status);

	status = hash_generate_hmac (&engine.base, key, sizeof (key), (uint8_t*) message,
		strlen (message), HMAC_SHA1, hmac, sizeof (hmac));
#ifdef HASH_ENABLE_SHA1
	CuAssertIntEquals (test, 0, status);

	status = testing_validate_array (expected, hmac, sizeof (hmac));
	CuAssertIntEquals (test, 0, status);
#else
	CuAssertIntEquals (test, HASH_ENGINE_UNSUPPORTED_HASH, status);
#endif

	HASH_TESTING_ENGINE_RELEASE (&engine);
}

#ifdef HASH_ENABLE_SHA1
static void hash_test_hmac_sha1_large_key (CuTest *test)
{
	HASH_TESTING_ENGINE engine;
	int status;
	char *message = "Test";
	uint8_t key[SHA1_BLOCK_SIZE + 1];
	uint8_t hmac[SHA1_HASH_LENGTH];
	uint8_t expected[] = {
		0x19, 0x75, 0xda, 0x73, 0x05, 0xeb, 0xd1, 0x29, 0x3a, 0x90, 0xc8, 0x36, 0xe1, 0xed, 0x76,
		0x7f,
		0xa3, 0x67, 0x51, 0x31
	};
	int i;

	TEST_START;

	for (i = 0; i < (int) sizeof (key); i++) {
		key[i] = i;
	}

	status = HASH_TESTING_ENGINE_INIT (&engine);
	CuAssertIntEquals (test, 0, status);

	status = hash_generate_hmac (&engine.base, key, sizeof (key), (uint8_t*) message,
		strlen (message), HMAC_SHA1, hmac, sizeof (hmac));
	CuAssertIntEquals (test, 0, status);

	status = testing_validate_array (expected, hmac, sizeof (hmac));
	CuAssertIntEquals (test, 0, status);

	HASH_TESTING_ENGINE_RELEASE (&engine);
}

static void hash_test_hmac_sha1_test_key (CuTest *test)
{
	HASH_TESTING_ENGINE engine;
	int status;
	char *message = "Test";
	uint8_t hmac[SHA1_HASH_LENGTH];

	TEST_START;

	status = HASH_TESTING_ENGINE_INIT (&engine);
	CuAssertIntEquals (test, 0, status);

	status = hash_generate_hmac (&engine.base, SHA1_HMAC_KEY, SHA1_HASH_LENGTH, (uint8_t*) message,
		strlen (message), HMAC_SHA1, hmac, sizeof (hmac));
	CuAssertIntEquals (test, 0, status);

	status = testing_validate_array (SHA1_TEST_HMAC, hmac, sizeof (hmac));
	CuAssertIntEquals (test, 0, status);

	HASH_TESTING_ENGINE_RELEASE (&engine);
}

static void hash_test_hmac_sha1_block_size_key (CuTest *test)
{
	HASH_TESTING_ENGINE engine;
	int status;
	uint8_t hmac[SHA1_HASH_LENGTH];

	TEST_START;

	status = HASH_TESTING_ENGINE_INIT (&engine);
	CuAssertIntEquals (test, 0, status);

	status = hash_generate_hmac (&engine.base, SHA1_HMAC_BLOCK_KEY, SHA1_BLOCK_SIZE,
		HASH_TESTING_FULL_BLOCK_4096, HASH_TESTING_FULL_BLOCK_4096_LEN, HMAC_SHA1, hmac,
		sizeof (hmac));
	CuAssertIntEquals (test, 0, status);

	status = testing_validate_array (SHA1_FULL_BLOCK_4096_BLOCK_KEY_HMAC, hmac, sizeof (hmac));
	CuAssertIntEquals (test, 0, status);

	HASH_TESTING_ENGINE_RELEASE (&engine);
}
#endif

static void hash_test_hmac_sha256 (CuTest *test)
{
	HASH_TESTING_ENGINE engine;
	int status;
	char *message = "Test";
	uint8_t key[] = {0x31, 0x32, 0x33, 0x34};
	uint8_t hmac[SHA256_HASH_LENGTH];
	uint8_t expected[] = {
		0x88, 0x69, 0xde, 0x57, 0x9d, 0xd0, 0xe9, 0x05, 0xe0, 0xa7, 0x11, 0x24, 0x57, 0x55, 0x94,
		0xf5,
		0x0a, 0x03, 0xd3, 0xd9, 0xcd, 0xf1, 0x6e, 0x9a, 0x3f, 0x9d, 0x6c, 0x60, 0xc0, 0x32, 0x4b,
		0x54
	};

	TEST_START;

	status = HASH_TESTING_ENGINE_INIT (&engine);
	CuAssertIntEquals (test, 0, status);

	status = hash_generate_hmac (&engine.base, key, sizeof (key), (uint8_t*) message,
		strlen (message), HMAC_SHA256, hmac, sizeof (hmac));
	CuAssertIntEquals (test, 0, status);

	status = testing_validate_array (expected, hmac, sizeof (hmac));
	CuAssertIntEquals (test, 0, status);

	HASH_TESTING_ENGINE_RELEASE (&engine);
}

static void hash_test_hmac_sha256_large_key (CuTest *test)
{
	HASH_TESTING_ENGINE engine;
	int status;
	char *message = "Test";
	uint8_t key[SHA256_BLOCK_SIZE + 1];
	uint8_t hmac[SHA256_HASH_LENGTH];
	uint8_t expected[] = {
		0xf1, 0x3b, 0x43, 0x16, 0x2c, 0xe4, 0x05, 0x75, 0x73, 0xc5, 0x54, 0x10, 0xad, 0xd5, 0xc5,
		0xc6,
		0x0e, 0x9a, 0x37, 0xff, 0x3e, 0xa0, 0x02, 0x34, 0xd6, 0x41, 0x80, 0xfa, 0x1a, 0x0e, 0x0a,
		0x04
	};
	int i;

	TEST_START;

	for (i = 0; i < (int) sizeof (key); i++) {
		key[i] = i;
	}

	status = HASH_TESTING_ENGINE_INIT (&engine);
	CuAssertIntEquals (test, 0, status);

	status = hash_generate_hmac (&engine.base, key, sizeof (key), (uint8_t*) message,
		strlen (message), HMAC_SHA256, hmac, sizeof (hmac));
	CuAssertIntEquals (test, 0, status);

	status = testing_validate_array (expected, hmac, sizeof (hmac));
	CuAssertIntEquals (test, 0, status);

	HASH_TESTING_ENGINE_RELEASE (&engine);
}

static void hash_test_hmac_sha256_test_key (CuTest *test)
{
	HASH_TESTING_ENGINE engine;
	int status;
	char *message = "Test";
	uint8_t hmac[SHA256_HASH_LENGTH];

	TEST_START;

	status = HASH_TESTING_ENGINE_INIT (&engine);
	CuAssertIntEquals (test, 0, status);

	status = hash_generate_hmac (&engine.base, SHA256_HMAC_KEY, SHA256_HASH_LENGTH,
		(uint8_t*) message, strlen (message), HMAC_SHA256, hmac, sizeof (hmac));
	CuAssertIntEquals (test, 0, status);

	status = testing_validate_array (SHA256_TEST_HMAC, hmac, sizeof (hmac));
	CuAssertIntEquals (test, 0, status);

	HASH_TESTING_ENGINE_RELEASE (&engine);
}

static void hash_test_hmac_sha256_block_size_key (CuTest *test)
{
	HASH_TESTING_ENGINE engine;
	int status;
	uint8_t hmac[SHA256_HASH_LENGTH];

	TEST_START;

	status = HASH_TESTING_ENGINE_INIT (&engine);
	CuAssertIntEquals (test, 0, status);

	status = hash_generate_hmac (&engine.base, SHA256_HMAC_BLOCK_KEY, SHA256_BLOCK_SIZE,
		HASH_TESTING_FULL_BLOCK_4096, HASH_TESTING_FULL_BLOCK_4096_LEN, HMAC_SHA256, hmac,
		sizeof (hmac));
	CuAssertIntEquals (test, 0, status);

	status = testing_validate_array (SHA256_FULL_BLOCK_4096_BLOCK_KEY_HMAC, hmac, sizeof (hmac));
	CuAssertIntEquals (test, 0, status);

	HASH_TESTING_ENGINE_RELEASE (&engine);
}

static void hash_test_hmac_sha384 (CuTest *test)
{
	HASH_TESTING_ENGINE engine;
	int status;
	char *message = "Test";
	uint8_t key[] = {0x31, 0x32, 0x33, 0x34};
	uint8_t hmac[SHA384_HASH_LENGTH];
	uint8_t expected[] = {
		0xd3, 0x31, 0xf1, 0x53, 0x07, 0x7e, 0xfb, 0xad, 0x73, 0x8e, 0xea, 0x4f, 0x3e, 0x0c, 0x5d,
		0x3f,
		0x6b, 0x60, 0x4d, 0x7b, 0x32, 0xb6, 0xa2, 0xe8, 0xb0, 0xeb, 0x4e, 0x4e, 0x7f, 0xc9, 0x52,
		0x7b,
		0xc6, 0x04, 0x44, 0xf2, 0x04, 0x7e, 0xac, 0xc1, 0xec, 0x88, 0x0b, 0xff, 0xd0, 0xb1, 0xc1,
		0xf2
	};

	TEST_START;

	status = HASH_TESTING_ENGINE_INIT (&engine);
	CuAssertIntEquals (test, 0, status);

	status = hash_generate_hmac (&engine.base, key, sizeof (key), (uint8_t*) message,
		strlen (message), HMAC_SHA384, hmac, sizeof (hmac));
#ifdef HASH_ENABLE_SHA384
	CuAssertIntEquals (test, 0, status);

	status = testing_validate_array (expected, hmac, sizeof (hmac));
	CuAssertIntEquals (test, 0, status);
#else
	CuAssertIntEquals (test, HASH_ENGINE_UNSUPPORTED_HASH, status);
#endif

	HASH_TESTING_ENGINE_RELEASE (&engine);
}

#ifdef HASH_ENABLE_SHA384
static void hash_test_hmac_sha384_large_key (CuTest *test)
{
	HASH_TESTING_ENGINE engine;
	int status;
	char *message = "Test";
	uint8_t key[SHA384_BLOCK_SIZE + 1];
	uint8_t hmac[SHA384_HASH_LENGTH];
	uint8_t expected[] = {
		0xf8, 0xa1, 0x45, 0x7e, 0x62, 0xdf, 0x77, 0xff, 0x48, 0x98, 0xf4, 0xc6, 0x3b, 0xa3, 0x45,
		0x29,
		0x3b, 0x1e, 0x50, 0x5c, 0x90, 0x9c, 0xd3, 0x00, 0x70, 0xc9, 0x90, 0x18, 0xe2, 0xa1, 0x3f,
		0xec,
		0x54, 0xaf, 0x70, 0x65, 0xc5, 0x3b, 0x97, 0xf7, 0x63, 0x30, 0x9e, 0x28, 0xd1, 0xcf, 0x1f,
		0x0f
	};
	int i;

	TEST_START;

	for (i = 0; i < (int) sizeof (key); i++) {
		key[i] = i;
	}

	status = HASH_TESTING_ENGINE_INIT (&engine);
	CuAssertIntEquals (test, 0, status);

	status = hash_generate_hmac (&engine.base, key, sizeof (key), (uint8_t*) message,
		strlen (message), HMAC_SHA384, hmac, sizeof (hmac));
	CuAssertIntEquals (test, 0, status);

	status = testing_validate_array (expected, hmac, sizeof (hmac));
	CuAssertIntEquals (test, 0, status);

	HASH_TESTING_ENGINE_RELEASE (&engine);
}

static void hash_test_hmac_sha384_test_key (CuTest *test)
{
	HASH_TESTING_ENGINE engine;
	int status;
	char *message = "Test";
	uint8_t hmac[SHA384_HASH_LENGTH];

	TEST_START;

	status = HASH_TESTING_ENGINE_INIT (&engine);
	CuAssertIntEquals (test, 0, status);

	status = hash_generate_hmac (&engine.base, SHA384_HMAC_KEY, SHA384_HASH_LENGTH,
		(uint8_t*) message, strlen (message), HMAC_SHA384, hmac, sizeof (hmac));
	CuAssertIntEquals (test, 0, status);

	status = testing_validate_array (SHA384_TEST_HMAC, hmac, sizeof (hmac));
	CuAssertIntEquals (test, 0, status);

	HASH_TESTING_ENGINE_RELEASE (&engine);
}

static void hash_test_hmac_sha384_block_size_key (CuTest *test)
{
	HASH_TESTING_ENGINE engine;
	int status;
	uint8_t hmac[SHA384_HASH_LENGTH];

	TEST_START;

	status = HASH_TESTING_ENGINE_INIT (&engine);
	CuAssertIntEquals (test, 0, status);

	status = hash_generate_hmac (&engine.base, SHA384_HMAC_BLOCK_KEY, SHA384_BLOCK_SIZE,
		HASH_TESTING_FULL_BLOCK_4096, HASH_TESTING_FULL_BLOCK_4096_LEN, HMAC_SHA384, hmac,
		sizeof (hmac));
	CuAssertIntEquals (test, 0, status);

	status = testing_validate_array (SHA384_FULL_BLOCK_4096_BLOCK_KEY_HMAC, hmac, sizeof (hmac));
	CuAssertIntEquals (test, 0, status);

	HASH_TESTING_ENGINE_RELEASE (&engine);
}
#endif

static void hash_test_hmac_sha512 (CuTest *test)
{
	HASH_TESTING_ENGINE engine;
	int status;
	char *message = "Test";
	uint8_t key[] = {0x31, 0x32, 0x33, 0x34};
	uint8_t hmac[SHA512_HASH_LENGTH];
	uint8_t expected[] = {
		0x39, 0xb8, 0x29, 0x9b, 0x43, 0x30, 0xcb, 0x1e, 0x8b, 0x51, 0xfa, 0xcb, 0x76, 0x79, 0xaf,
		0x47,
		0xea, 0x35, 0xbf, 0xea, 0xb9, 0x1b, 0x34, 0xd0, 0x9e, 0x0a, 0xac, 0xc9, 0xde, 0x64, 0x80,
		0x60,
		0x29, 0x8d, 0x86, 0xd5, 0x47, 0x9d, 0x4e, 0xb5, 0x68, 0xdf, 0xe0, 0xea, 0xb6, 0x2c, 0x0e,
		0x4a,
		0x47, 0x90, 0x7e, 0x28, 0x09, 0xb8, 0x4b, 0x21, 0xdd, 0x6b, 0xc7, 0x41, 0xca, 0x09, 0x00,
		0x3a
	};

	TEST_START;

	status = HASH_TESTING_ENGINE_INIT (&engine);
	CuAssertIntEquals (test, 0, status);

	status = hash_generate_hmac (&engine.base, key, sizeof (key), (uint8_t*) message,
		strlen (message), HMAC_SHA512, hmac, sizeof (hmac));
#ifdef HASH_ENABLE_SHA512
	CuAssertIntEquals (test, 0, status);

	status = testing_validate_array (expected, hmac, sizeof (hmac));
	CuAssertIntEquals (test, 0, status);
#else
	CuAssertIntEquals (test, HASH_ENGINE_UNSUPPORTED_HASH, status);
#endif

	HASH_TESTING_ENGINE_RELEASE (&engine);
}

#ifdef HASH_ENABLE_SHA512
static void hash_test_hmac_sha512_large_key (CuTest *test)
{
	HASH_TESTING_ENGINE engine;
	int status;
	char *message = "Test";
	uint8_t key[SHA512_BLOCK_SIZE + 1];
	uint8_t hmac[SHA512_HASH_LENGTH];
	uint8_t expected[] = {
		0x4b, 0xf9, 0x6c, 0x4d, 0x3d, 0x7f, 0xac, 0x2f, 0x10, 0x48, 0xc2, 0x96, 0x78, 0xe1, 0x07,
		0x95,
		0x33, 0xa1, 0x47, 0x37, 0x5b, 0x1e, 0xdd, 0x2d, 0x5f, 0xa4, 0xbc, 0xf6, 0x22, 0x40, 0x9f,
		0x96,
		0x4b, 0x54, 0x59, 0xab, 0xaa, 0x6f, 0x7b, 0x58, 0x56, 0x14, 0xe1, 0x78, 0x6b, 0x0e, 0xd8,
		0xf7,
		0x75, 0x45, 0xcb, 0x90, 0x1d, 0xd6, 0xd6, 0x12, 0xc2, 0x33, 0xb2, 0x53, 0xb3, 0x17, 0x05,
		0x5d
	};
	int i;

	TEST_START;

	for (i = 0; i < (int) sizeof (key); i++) {
		key[i] = i;
	}

	status = HASH_TESTING_ENGINE_INIT (&engine);
	CuAssertIntEquals (test, 0, status);

	status = hash_generate_hmac (&engine.base, key, sizeof (key), (uint8_t*) message,
		strlen (message), HMAC_SHA512, hmac, sizeof (hmac));
	CuAssertIntEquals (test, 0, status);

	status = testing_validate_array (expected, hmac, sizeof (hmac));
	CuAssertIntEquals (test, 0, status);

	HASH_TESTING_ENGINE_RELEASE (&engine);
}

static void hash_test_hmac_sha512_test_key (CuTest *test)
{
	HASH_TESTING_ENGINE engine;
	int status;
	char *message = "Test";
	uint8_t hmac[SHA512_HASH_LENGTH];

	TEST_START;

	status = HASH_TESTING_ENGINE_INIT (&engine);
	CuAssertIntEquals (test, 0, status);

	status = hash_generate_hmac (&engine.base, SHA512_HMAC_KEY, SHA512_HASH_LENGTH,
		(uint8_t*) message, strlen (message), HMAC_SHA512, hmac, sizeof (hmac));
	CuAssertIntEquals (test, 0, status);

	status = testing_validate_array (SHA512_TEST_HMAC, hmac, sizeof (hmac));
	CuAssertIntEquals (test, 0, status);

	HASH_TESTING_ENGINE_RELEASE (&engine);
}

static void hash_test_hmac_sha512_block_size_key (CuTest *test)
{
	HASH_TESTING_ENGINE engine;
	int status;
	uint8_t hmac[SHA512_HASH_LENGTH];

	TEST_START;

	status = HASH_TESTING_ENGINE_INIT (&engine);
	CuAssertIntEquals (test, 0, status);

	status = hash_generate_hmac (&engine.base, SHA512_HMAC_BLOCK_KEY, SHA512_BLOCK_SIZE,
		HASH_TESTING_FULL_BLOCK_4096, HASH_TESTING_FULL_BLOCK_4096_LEN, HMAC_SHA512, hmac,
		sizeof (hmac));
	CuAssertIntEquals (test, 0, status);

	status = testing_validate_array (SHA512_FULL_BLOCK_4096_BLOCK_KEY_HMAC, hmac, sizeof (hmac));
	CuAssertIntEquals (test, 0, status);

	HASH_TESTING_ENGINE_RELEASE (&engine);
}
#endif

static void hash_test_hmac_unknown (CuTest *test)
{
	HASH_TESTING_ENGINE engine;
	int status;
	char *message = "Test";
	uint8_t key[] = {0x31, 0x32, 0x33, 0x34};
	uint8_t hmac[SHA256_HASH_LENGTH];

	TEST_START;

	status = HASH_TESTING_ENGINE_INIT (&engine);
	CuAssertIntEquals (test, 0, status);

	status = hash_generate_hmac (&engine.base, key, sizeof (key), (uint8_t*) message,
		strlen (message), (enum hmac_hash) 4, hmac, sizeof (hmac));
	CuAssertIntEquals (test, HASH_ENGINE_UNKNOWN_HASH, status);

	HASH_TESTING_ENGINE_RELEASE (&engine);
}

static void hash_test_hmac_null (CuTest *test)
{
	HASH_TESTING_ENGINE engine;
	int status;
	char *message = "Test";
	uint8_t key[] = {0x31, 0x32, 0x33, 0x34};
	uint8_t hmac[SHA256_HASH_LENGTH];

	TEST_START;

	status = HASH_TESTING_ENGINE_INIT (&engine);
	CuAssertIntEquals (test, 0, status);

	status = hash_generate_hmac (NULL, key, sizeof (key), (uint8_t*) message, strlen (message),
		HMAC_SHA256, hmac, sizeof (hmac));
	CuAssertIntEquals (test, HASH_ENGINE_INVALID_ARGUMENT, status);

	status = hash_generate_hmac (&engine.base, NULL, sizeof (key), (uint8_t*) message,
		strlen (message), HMAC_SHA256, hmac, sizeof (hmac));
	CuAssertIntEquals (test, HASH_ENGINE_INVALID_ARGUMENT, status);

	status = hash_generate_hmac (&engine.base, key, 0, (uint8_t*) message, strlen (message),
		HMAC_SHA256, hmac, sizeof (hmac));
	CuAssertIntEquals (test, HASH_ENGINE_INVALID_ARGUMENT, status);

	status = hash_generate_hmac (&engine.base, key, sizeof (key), NULL, strlen (message),
		HMAC_SHA256, hmac, sizeof (hmac));
	CuAssertIntEquals (test, HASH_ENGINE_INVALID_ARGUMENT, status);

	status = hash_generate_hmac (&engine.base, key, sizeof (key), (uint8_t*) message,
		strlen (message), HMAC_SHA256, NULL, sizeof (hmac));
	CuAssertIntEquals (test, HASH_ENGINE_INVALID_ARGUMENT, status);

	HASH_TESTING_ENGINE_RELEASE (&engine);
}

static void hash_test_hash_generate_hmac_start_error (CuTest *test)
{
	struct hash_engine_mock engine;
	int status;
	char *message = "Test";
	uint8_t key[] = {0x31, 0x32, 0x33, 0x34};
	uint8_t hmac[SHA256_HASH_LENGTH];

	TEST_START;

	status = hash_mock_init (&engine);
	CuAssertIntEquals (test, 0, status);

	status = mock_expect (&engine.mock, engine.base.start_sha256, &engine,
		HASH_ENGINE_START_SHA256_FAILED);

	CuAssertIntEquals (test, 0, status);

	status = hash_generate_hmac (&engine.base, key, sizeof (key), (uint8_t*) message,
		strlen (message), HMAC_SHA256, hmac, sizeof (hmac));
	CuAssertIntEquals (test, HASH_ENGINE_START_SHA256_FAILED, status);

	status = hash_mock_validate_and_release (&engine);
	CuAssertIntEquals (test, 0, status);
}

static void hash_test_hash_generate_hmac_init_error (CuTest *test)
{
	struct hash_engine_mock engine;
	int status;
	char *message = "Test";
	uint8_t key[] = {0x31, 0x32, 0x33, 0x34};
	uint8_t hmac[SHA256_HASH_LENGTH];

	TEST_START;

	status = hash_mock_init (&engine);
	CuAssertIntEquals (test, 0, status);

	status = mock_expect (&engine.mock, engine.base.start_sha256, &engine, 0);

	status |= mock_expect (&engine.mock, engine.base.update, &engine, HASH_ENGINE_UPDATE_FAILED,
		MOCK_ARG_NOT_NULL, MOCK_ARG (SHA256_BLOCK_SIZE));
	status |= mock_expect (&engine.mock, engine.base.cancel, &engine, 0);

	CuAssertIntEquals (test, 0, status);

	status = hash_generate_hmac (&engine.base, key, sizeof (key), (uint8_t*) message,
		strlen (message), HMAC_SHA256, hmac, sizeof (hmac));
	CuAssertIntEquals (test, HASH_ENGINE_UPDATE_FAILED, status);

	status = hash_mock_validate_and_release (&engine);
	CuAssertIntEquals (test, 0, status);
}

static void hash_test_hash_generate_hmac_update_error (CuTest *test)
{
	struct hash_engine_mock engine;
	int status;
	char *message = "Test";
	uint8_t key[] = {0x31, 0x32, 0x33, 0x34};
	uint8_t hmac[SHA256_HASH_LENGTH];

	TEST_START;

	status = hash_mock_init (&engine);
	CuAssertIntEquals (test, 0, status);

	status = mock_expect (&engine.mock, engine.base.start_sha256, &engine, 0);

	status |= mock_expect (&engine.mock, engine.base.update, &engine, 0, MOCK_ARG_NOT_NULL,
		MOCK_ARG (SHA256_BLOCK_SIZE));

	status |= mock_expect (&engine.mock, engine.base.update, &engine, HASH_ENGINE_UPDATE_FAILED,
		MOCK_ARG_PTR (message), MOCK_ARG (strlen (message)));
	status |= mock_expect (&engine.mock, engine.base.cancel, &engine, 0);

	CuAssertIntEquals (test, 0, status);

	status = hash_generate_hmac (&engine.base, key, sizeof (key), (uint8_t*) message,
		strlen (message), HMAC_SHA256, hmac, sizeof (hmac));
	CuAssertIntEquals (test, HASH_ENGINE_UPDATE_FAILED, status);

	status = hash_mock_validate_and_release (&engine);
	CuAssertIntEquals (test, 0, status);
}

static void hash_test_hash_generate_hmac_finish_error (CuTest *test)
{
	struct hash_engine_mock engine;
	int status;
	char *message = "Test";
	uint8_t key[] = {0x31, 0x32, 0x33, 0x34};
	uint8_t hmac[SHA256_HASH_LENGTH];

	TEST_START;

	status = hash_mock_init (&engine);
	CuAssertIntEquals (test, 0, status);

	status = mock_expect (&engine.mock, engine.base.start_sha256, &engine, 0);

	status |= mock_expect (&engine.mock, engine.base.update, &engine, 0, MOCK_ARG_NOT_NULL,
		MOCK_ARG (SHA256_BLOCK_SIZE));

	status |= mock_expect (&engine.mock, engine.base.update, &engine, 0, MOCK_ARG_PTR (message),
		MOCK_ARG (strlen (message)));

	status |= mock_expect (&engine.mock, engine.base.finish, &engine, HASH_ENGINE_FINISH_FAILED,
		MOCK_ARG_NOT_NULL, MOCK_ARG (SHA512_HASH_LENGTH));
	status |= mock_expect (&engine.mock, engine.base.cancel, &engine, 0);

	CuAssertIntEquals (test, 0, status);

	status = hash_generate_hmac (&engine.base, key, sizeof (key), (uint8_t*) message,
		strlen (message), HMAC_SHA256, hmac, sizeof (hmac));
	CuAssertIntEquals (test, HASH_ENGINE_FINISH_FAILED, status);

	status = hash_mock_validate_and_release (&engine);
	CuAssertIntEquals (test, 0, status);
}

#ifdef HASH_ENABLE_SHA1
static void hash_test_hash_generate_hmac_sha1_small_buffer (CuTest *test)
{
	struct hash_engine_mock engine;
	int status;
	char *message = "Test";
	uint8_t key[] = {0x31, 0x32, 0x33, 0x34};
	uint8_t hmac[SHA1_HASH_LENGTH - 1];

	TEST_START;

	status = hash_mock_init (&engine);
	CuAssertIntEquals (test, 0, status);

	status = mock_expect (&engine.mock, engine.base.start_sha1, &engine, 0);

	status |= mock_expect (&engine.mock, engine.base.update, &engine, 0, MOCK_ARG_NOT_NULL,
		MOCK_ARG (SHA1_BLOCK_SIZE));
	status |= mock_expect (&engine.mock, engine.base.cancel, &engine, 0);

	CuAssertIntEquals (test, 0, status);

	status = hash_generate_hmac (&engine.base, key, sizeof (key), (uint8_t*) message,
		strlen (message), HMAC_SHA1, hmac, sizeof (hmac));
	CuAssertIntEquals (test, HASH_ENGINE_HASH_BUFFER_TOO_SMALL, status);

	status = hash_mock_validate_and_release (&engine);
	CuAssertIntEquals (test, 0, status);
}
#endif

static void hash_test_hash_generate_hmac_sha256_small_buffer (CuTest *test)
{
	struct hash_engine_mock engine;
	int status;
	char *message = "Test";
	uint8_t key[] = {0x31, 0x32, 0x33, 0x34};
	uint8_t hmac[SHA256_HASH_LENGTH - 1];

	TEST_START;

	status = hash_mock_init (&engine);
	CuAssertIntEquals (test, 0, status);

	status = mock_expect (&engine.mock, engine.base.start_sha256, &engine, 0);

	status |= mock_expect (&engine.mock, engine.base.update, &engine, 0, MOCK_ARG_NOT_NULL,
		MOCK_ARG (SHA256_BLOCK_SIZE));
	status |= mock_expect (&engine.mock, engine.base.cancel, &engine, 0);

	CuAssertIntEquals (test, 0, status);

	status = hash_generate_hmac (&engine.base, key, sizeof (key), (uint8_t*) message,
		strlen (message), HMAC_SHA256, hmac, sizeof (hmac));
	CuAssertIntEquals (test, HASH_ENGINE_HASH_BUFFER_TOO_SMALL, status);

	status = hash_mock_validate_and_release (&engine);
	CuAssertIntEquals (test, 0, status);
}

#ifdef HASH_ENABLE_SHA384
static void hash_test_hash_generate_hmac_sha384_small_buffer (CuTest *test)
{
	struct hash_engine_mock engine;
	int status;
	char *message = "Test";
	uint8_t key[] = {0x31, 0x32, 0x33, 0x34};
	uint8_t hmac[SHA384_HASH_LENGTH - 1];

	TEST_START;

	status = hash_mock_init (&engine);
	CuAssertIntEquals (test, 0, status);

	status = mock_expect (&engine.mock, engine.base.start_sha384, &engine, 0);

	status |= mock_expect (&engine.mock, engine.base.update, &engine, 0, MOCK_ARG_NOT_NULL,
		MOCK_ARG (SHA384_BLOCK_SIZE));
	status |= mock_expect (&engine.mock, engine.base.cancel, &engine, 0);

	CuAssertIntEquals (test, 0, status);

	status = hash_generate_hmac (&engine.base, key, sizeof (key), (uint8_t*) message,
		strlen (message), HMAC_SHA384, hmac, sizeof (hmac));
	CuAssertIntEquals (test, HASH_ENGINE_HASH_BUFFER_TOO_SMALL, status);

	status = hash_mock_validate_and_release (&engine);
	CuAssertIntEquals (test, 0, status);
}
#endif

#ifdef HASH_ENABLE_SHA512
static void hash_test_hash_generate_hmac_sha512_small_buffer (CuTest *test)
{
	struct hash_engine_mock engine;
	int status;
	char *message = "Test";
	uint8_t key[] = {0x31, 0x32, 0x33, 0x34};
	uint8_t hmac[SHA512_HASH_LENGTH - 1];

	TEST_START;

	status = hash_mock_init (&engine);
	CuAssertIntEquals (test, 0, status);

	status = mock_expect (&engine.mock, engine.base.start_sha512, &engine, 0);

	status |= mock_expect (&engine.mock, engine.base.update, &engine, 0, MOCK_ARG_NOT_NULL,
		MOCK_ARG (SHA512_BLOCK_SIZE));
	status |= mock_expect (&engine.mock, engine.base.cancel, &engine, 0);

	CuAssertIntEquals (test, 0, status);

	status = hash_generate_hmac (&engine.base, key, sizeof (key), (uint8_t*) message,
		strlen (message), HMAC_SHA512, hmac, sizeof (hmac));
	CuAssertIntEquals (test, HASH_ENGINE_HASH_BUFFER_TOO_SMALL, status);

	status = hash_mock_validate_and_release (&engine);
	CuAssertIntEquals (test, 0, status);
}
#endif

static void hash_test_start_new_hash_sha1 (CuTest *test)
{
	HASH_TESTING_ENGINE engine;
	int status;
	char *message = "Test";
	uint8_t hash[SHA1_HASH_LENGTH];

	TEST_START;

	status = HASH_TESTING_ENGINE_INIT (&engine);
	CuAssertIntEquals (test, 0, status);

	status = hash_start_new_hash (&engine.base, HASH_TYPE_SHA1);
#ifdef HASH_ENABLE_SHA1
	CuAssertIntEquals (test, 0, status);

	status = engine.base.update (&engine.base, (uint8_t*) message, strlen (message));
	CuAssertIntEquals (test, 0, status);

	status = engine.base.finish (&engine.base, hash, sizeof (hash));
	CuAssertIntEquals (test, 0, status);

	status = testing_validate_array (SHA1_TEST_HASH, hash, sizeof (hash));
	CuAssertIntEquals (test, 0, status);
#else
	CuAssertIntEquals (test, HASH_ENGINE_UNSUPPORTED_HASH, status);
#endif

	HASH_TESTING_ENGINE_RELEASE (&engine);
}

static void hash_test_start_new_hash_sha256 (CuTest *test)
{
	HASH_TESTING_ENGINE engine;
	int status;
	char *message = "Test";
	uint8_t hash[SHA256_HASH_LENGTH];

	TEST_START;

	status = HASH_TESTING_ENGINE_INIT (&engine);
	CuAssertIntEquals (test, 0, status);

	status = hash_start_new_hash (&engine.base, HASH_TYPE_SHA256);
	CuAssertIntEquals (test, 0, status);

	status = engine.base.update (&engine.base, (uint8_t*) message, strlen (message));
	CuAssertIntEquals (test, 0, status);

	status = engine.base.finish (&engine.base, hash, sizeof (hash));
	CuAssertIntEquals (test, 0, status);

	status = testing_validate_array (SHA256_TEST_HASH, hash, sizeof (hash));
	CuAssertIntEquals (test, 0, status);

	HASH_TESTING_ENGINE_RELEASE (&engine);
}

static void hash_test_start_new_hash_sha384 (CuTest *test)
{
	HASH_TESTING_ENGINE engine;
	int status;
	char *message = "Test";
	uint8_t hash[SHA384_HASH_LENGTH];

	TEST_START;

	status = HASH_TESTING_ENGINE_INIT (&engine);
	CuAssertIntEquals (test, 0, status);

	status = hash_start_new_hash (&engine.base, HASH_TYPE_SHA384);
#ifdef HASH_ENABLE_SHA384
	CuAssertIntEquals (test, 0, status);

	status = engine.base.update (&engine.base, (uint8_t*) message, strlen (message));
	CuAssertIntEquals (test, 0, status);

	status = engine.base.finish (&engine.base, hash, sizeof (hash));
	CuAssertIntEquals (test, 0, status);

	status = testing_validate_array (SHA384_TEST_HASH, hash, sizeof (hash));
	CuAssertIntEquals (test, 0, status);
#else
	CuAssertIntEquals (test, HASH_ENGINE_UNSUPPORTED_HASH, status);
#endif

	HASH_TESTING_ENGINE_RELEASE (&engine);
}

static void hash_test_start_new_hash_sha512 (CuTest *test)
{
	HASH_TESTING_ENGINE engine;
	int status;
	char *message = "Test";
	uint8_t hash[SHA512_HASH_LENGTH];

	TEST_START;

	status = HASH_TESTING_ENGINE_INIT (&engine);
	CuAssertIntEquals (test, 0, status);

	status = hash_start_new_hash (&engine.base, HASH_TYPE_SHA512);
#ifdef HASH_ENABLE_SHA512
	CuAssertIntEquals (test, 0, status);

	status = engine.base.update (&engine.base, (uint8_t*) message, strlen (message));
	CuAssertIntEquals (test, 0, status);

	status = engine.base.finish (&engine.base, hash, sizeof (hash));
	CuAssertIntEquals (test, 0, status);

	status = testing_validate_array (SHA512_TEST_HASH, hash, sizeof (hash));
	CuAssertIntEquals (test, 0, status);
#else
	CuAssertIntEquals (test, HASH_ENGINE_UNSUPPORTED_HASH, status);
#endif

	HASH_TESTING_ENGINE_RELEASE (&engine);
}

static void hash_test_start_new_hash_unknown (CuTest *test)
{
	HASH_TESTING_ENGINE engine;
	int status;

	TEST_START;

	status = HASH_TESTING_ENGINE_INIT (&engine);
	CuAssertIntEquals (test, 0, status);

	status = hash_start_new_hash (&engine.base, (enum hash_type) 10);
	CuAssertIntEquals (test, HASH_ENGINE_UNKNOWN_HASH, status);

	HASH_TESTING_ENGINE_RELEASE (&engine);
}

static void hash_test_start_new_hash_null (CuTest *test)
{
	int status;

	TEST_START;

	status = hash_start_new_hash (NULL, HASH_TYPE_SHA256);
	CuAssertIntEquals (test, HASH_ENGINE_INVALID_ARGUMENT, status);
}

#ifdef HASH_ENABLE_SHA1
static void hash_test_start_new_hash_sha1_error (CuTest *test)
{
	struct hash_engine_mock engine;
	int status;

	TEST_START;

	status = hash_mock_init (&engine);
	CuAssertIntEquals (test, 0, status);

	status = mock_expect (&engine.mock, engine.base.start_sha1, &engine,
		HASH_ENGINE_START_SHA1_FAILED);
	CuAssertIntEquals (test, 0, status);

	status = hash_start_new_hash (&engine.base, HASH_TYPE_SHA1);
	CuAssertIntEquals (test, HASH_ENGINE_START_SHA1_FAILED, status);

	status = hash_mock_validate_and_release (&engine);
	CuAssertIntEquals (test, 0, status);
}
#endif

static void hash_test_start_new_hash_sha256_error (CuTest *test)
{
	struct hash_engine_mock engine;
	int status;

	TEST_START;

	status = hash_mock_init (&engine);
	CuAssertIntEquals (test, 0, status);

	status = mock_expect (&engine.mock, engine.base.start_sha256, &engine,
		HASH_ENGINE_START_SHA256_FAILED);
	CuAssertIntEquals (test, 0, status);

	status = hash_start_new_hash (&engine.base, HASH_TYPE_SHA256);
	CuAssertIntEquals (test, HASH_ENGINE_START_SHA256_FAILED, status);

	status = hash_mock_validate_and_release (&engine);
	CuAssertIntEquals (test, 0, status);
}

#ifdef HASH_ENABLE_SHA384
static void hash_test_start_new_hash_sha384_error (CuTest *test)
{
	struct hash_engine_mock engine;
	int status;

	TEST_START;

	status = hash_mock_init (&engine);
	CuAssertIntEquals (test, 0, status);

	status = mock_expect (&engine.mock, engine.base.start_sha384, &engine,
		HASH_ENGINE_START_SHA384_FAILED);
	CuAssertIntEquals (test, 0, status);

	status = hash_start_new_hash (&engine.base, HASH_TYPE_SHA384);
	CuAssertIntEquals (test, HASH_ENGINE_START_SHA384_FAILED, status);

	status = hash_mock_validate_and_release (&engine);
	CuAssertIntEquals (test, 0, status);
}
#endif

#ifdef HASH_ENABLE_SHA512
static void hash_test_start_new_hash_sha512_error (CuTest *test)
{
	struct hash_engine_mock engine;
	int status;

	TEST_START;

	status = hash_mock_init (&engine);
	CuAssertIntEquals (test, 0, status);

	status = mock_expect (&engine.mock, engine.base.start_sha512, &engine,
		HASH_ENGINE_START_SHA512_FAILED);
	CuAssertIntEquals (test, 0, status);

	status = hash_start_new_hash (&engine.base, HASH_TYPE_SHA512);
	CuAssertIntEquals (test, HASH_ENGINE_START_SHA512_FAILED, status);

	status = hash_mock_validate_and_release (&engine);
	CuAssertIntEquals (test, 0, status);
}
#endif

static void hash_test_calculate_sha1 (CuTest *test)
{
	HASH_TESTING_ENGINE engine;
	int status;
	char *message = "Test";
	uint8_t hash[SHA1_HASH_LENGTH];

	TEST_START;

	status = HASH_TESTING_ENGINE_INIT (&engine);
	CuAssertIntEquals (test, 0, status);

	status = hash_calculate (&engine.base, HASH_TYPE_SHA1, (uint8_t*) message, strlen (message),
		hash, sizeof (hash));
#ifdef HASH_ENABLE_SHA1
	CuAssertIntEquals (test, SHA1_HASH_LENGTH, status);

	status = testing_validate_array (SHA1_TEST_HASH, hash, sizeof (hash));
	CuAssertIntEquals (test, 0, status);
#else
	CuAssertIntEquals (test, HASH_ENGINE_UNSUPPORTED_HASH, status);
#endif

	HASH_TESTING_ENGINE_RELEASE (&engine);
}

static void hash_test_calculate_sha256 (CuTest *test)
{
	HASH_TESTING_ENGINE engine;
	int status;
	char *message = "Test";
	uint8_t hash[SHA256_HASH_LENGTH];

	TEST_START;

	status = HASH_TESTING_ENGINE_INIT (&engine);
	CuAssertIntEquals (test, 0, status);

	status = hash_calculate (&engine.base, HASH_TYPE_SHA256, (uint8_t*) message, strlen (message),
		hash, sizeof (hash));
	CuAssertIntEquals (test, SHA256_HASH_LENGTH, status);

	status = testing_validate_array (SHA256_TEST_HASH, hash, sizeof (hash));
	CuAssertIntEquals (test, 0, status);

	HASH_TESTING_ENGINE_RELEASE (&engine);
}

static void hash_test_calculate_sha384 (CuTest *test)
{
	HASH_TESTING_ENGINE engine;
	int status;
	char *message = "Test";
	uint8_t hash[SHA384_HASH_LENGTH];

	TEST_START;

	status = HASH_TESTING_ENGINE_INIT (&engine);
	CuAssertIntEquals (test, 0, status);

	status = hash_calculate (&engine.base, HASH_TYPE_SHA384, (uint8_t*) message, strlen (message),
		hash, sizeof (hash));
#ifdef HASH_ENABLE_SHA384
	CuAssertIntEquals (test, SHA384_HASH_LENGTH, status);

	status = testing_validate_array (SHA384_TEST_HASH, hash, sizeof (hash));
	CuAssertIntEquals (test, 0, status);
#else
	CuAssertIntEquals (test, HASH_ENGINE_UNSUPPORTED_HASH, status);
#endif

	HASH_TESTING_ENGINE_RELEASE (&engine);
}

static void hash_test_calculate_sha512 (CuTest *test)
{
	HASH_TESTING_ENGINE engine;
	int status;
	char *message = "Test";
	uint8_t hash[SHA512_HASH_LENGTH];

	TEST_START;

	status = HASH_TESTING_ENGINE_INIT (&engine);
	CuAssertIntEquals (test, 0, status);

	status = hash_calculate (&engine.base, HASH_TYPE_SHA512, (uint8_t*) message, strlen (message),
		hash, sizeof (hash));
#ifdef HASH_ENABLE_SHA512
	CuAssertIntEquals (test, SHA512_HASH_LENGTH, status);

	status = testing_validate_array (SHA512_TEST_HASH, hash, sizeof (hash));
	CuAssertIntEquals (test, 0, status);
#else
	CuAssertIntEquals (test, HASH_ENGINE_UNSUPPORTED_HASH, status);
#endif

	HASH_TESTING_ENGINE_RELEASE (&engine);
}

static void hash_test_calculate_unknown (CuTest *test)
{
	HASH_TESTING_ENGINE engine;
	int status;
	char *message = "Test";
	uint8_t hash[SHA256_HASH_LENGTH];

	TEST_START;

	status = HASH_TESTING_ENGINE_INIT (&engine);
	CuAssertIntEquals (test, 0, status);

	status = hash_calculate (&engine.base, (enum hash_type) 10, (uint8_t*) message,
		strlen (message), hash, sizeof (hash));
	CuAssertIntEquals (test, HASH_ENGINE_UNKNOWN_HASH, status);

	HASH_TESTING_ENGINE_RELEASE (&engine);
}

static void hash_test_calculate_null (CuTest *test)
{
	HASH_TESTING_ENGINE engine;
	int status;
	char *message = "Test";
	uint8_t hash[SHA256_HASH_LENGTH];

	TEST_START;

	status = HASH_TESTING_ENGINE_INIT (&engine);
	CuAssertIntEquals (test, 0, status);

	status = hash_calculate (NULL, HASH_TYPE_SHA256, (uint8_t*) message, strlen (message), hash,
		sizeof (hash));
	CuAssertIntEquals (test, HASH_ENGINE_INVALID_ARGUMENT, status);

	status = hash_calculate (&engine.base, HASH_TYPE_SHA256, NULL, strlen (message), hash,
		sizeof (hash));
	CuAssertIntEquals (test, HASH_ENGINE_INVALID_ARGUMENT, status);

	status = hash_calculate (&engine.base, HASH_TYPE_SHA256, (uint8_t*) message, strlen (message),
		NULL, sizeof (hash));
	CuAssertIntEquals (test, HASH_ENGINE_INVALID_ARGUMENT, status);

	HASH_TESTING_ENGINE_RELEASE (&engine);
}

#ifdef HASH_ENABLE_SHA1
static void hash_test_calculate_sha1_small_buffer (CuTest *test)
{
	HASH_TESTING_ENGINE engine;
	int status;
	char *message = "Test";
	uint8_t hash[SHA1_HASH_LENGTH];

	TEST_START;

	status = HASH_TESTING_ENGINE_INIT (&engine);
	CuAssertIntEquals (test, 0, status);

	status = hash_calculate (&engine.base, HASH_TYPE_SHA1, (uint8_t*) message, strlen (message),
		hash, sizeof (hash) - 1);
	CuAssertIntEquals (test, HASH_ENGINE_HASH_BUFFER_TOO_SMALL, status);

	HASH_TESTING_ENGINE_RELEASE (&engine);
}
#endif

static void hash_test_calculate_sha256_small_buffer (CuTest *test)
{
	HASH_TESTING_ENGINE engine;
	int status;
	char *message = "Test";
	uint8_t hash[SHA256_HASH_LENGTH];

	TEST_START;

	status = HASH_TESTING_ENGINE_INIT (&engine);
	CuAssertIntEquals (test, 0, status);

	status = hash_calculate (&engine.base, HASH_TYPE_SHA256, (uint8_t*) message, strlen (message),
		hash, sizeof (hash) - 1);
	CuAssertIntEquals (test, HASH_ENGINE_HASH_BUFFER_TOO_SMALL, status);

	HASH_TESTING_ENGINE_RELEASE (&engine);
}

#ifdef HASH_ENABLE_SHA384
static void hash_test_calculate_sha384_small_buffer (CuTest *test)
{
	HASH_TESTING_ENGINE engine;
	int status;
	char *message = "Test";
	uint8_t hash[SHA384_HASH_LENGTH];

	TEST_START;

	status = HASH_TESTING_ENGINE_INIT (&engine);
	CuAssertIntEquals (test, 0, status);

	status = hash_calculate (&engine.base, HASH_TYPE_SHA384, (uint8_t*) message, strlen (message),
		hash, sizeof (hash) - 1);
	CuAssertIntEquals (test, HASH_ENGINE_HASH_BUFFER_TOO_SMALL, status);

	HASH_TESTING_ENGINE_RELEASE (&engine);
}
#endif

#ifdef HASH_ENABLE_SHA512
static void hash_test_calculate_sha512_small_buffer (CuTest *test)
{
	HASH_TESTING_ENGINE engine;
	int status;
	char *message = "Test";
	uint8_t hash[SHA512_HASH_LENGTH];

	TEST_START;

	status = HASH_TESTING_ENGINE_INIT (&engine);
	CuAssertIntEquals (test, 0, status);

	status = hash_calculate (&engine.base, HASH_TYPE_SHA512, (uint8_t*) message, strlen (message),
		hash, sizeof (hash) - 1);
	CuAssertIntEquals (test, HASH_ENGINE_HASH_BUFFER_TOO_SMALL, status);

	HASH_TESTING_ENGINE_RELEASE (&engine);
}
#endif

static void hash_test_get_hash_length (CuTest *test)
{
	int status;

	TEST_START;

	status = hash_get_hash_length (HASH_TYPE_SHA1);
	CuAssertIntEquals (test, SHA1_HASH_LENGTH, status);

	status = hash_get_hash_length (HASH_TYPE_SHA256);
	CuAssertIntEquals (test, SHA256_HASH_LENGTH, status);

	status = hash_get_hash_length (HASH_TYPE_SHA384);
	CuAssertIntEquals (test, SHA384_HASH_LENGTH, status);

	status = hash_get_hash_length (HASH_TYPE_SHA512);
	CuAssertIntEquals (test, SHA512_HASH_LENGTH, status);
}

static void hash_test_get_hash_length_unsupported (CuTest *test)
{
	int status;

	TEST_START;

	status = hash_get_hash_length (HASH_TYPE_INVALID);
	CuAssertIntEquals (test, HASH_ENGINE_UNKNOWN_HASH, status);
}

static void hash_test_hmac_get_hmac_length (CuTest *test)
{
	int status;

	TEST_START;

	status = hash_hmac_get_hmac_length (HMAC_SHA1);
	CuAssertIntEquals (test, SHA1_HASH_LENGTH, status);

	status = hash_hmac_get_hmac_length (HMAC_SHA256);
	CuAssertIntEquals (test, SHA256_HASH_LENGTH, status);

	status = hash_hmac_get_hmac_length (HMAC_SHA384);
	CuAssertIntEquals (test, SHA384_HASH_LENGTH, status);

	status = hash_hmac_get_hmac_length (HMAC_SHA512);
	CuAssertIntEquals (test, SHA512_HASH_LENGTH, status);
}

static void hash_test_hmac_get_hmac_length_unsupported (CuTest *test)
{
	int status;

	TEST_START;

	status = hash_hmac_get_hmac_length (HMAC_INVALID);
	CuAssertIntEquals (test, HASH_ENGINE_UNKNOWN_HASH, status);
}

static void hash_test_get_block_size (CuTest *test)
{
	int status;

	TEST_START;

	status = hash_get_block_size (HASH_TYPE_SHA1);
	CuAssertIntEquals (test, SHA1_BLOCK_SIZE, status);

	status = hash_get_block_size (HASH_TYPE_SHA256);
	CuAssertIntEquals (test, SHA256_BLOCK_SIZE, status);

	status = hash_get_block_size (HASH_TYPE_SHA384);
	CuAssertIntEquals (test, SHA384_BLOCK_SIZE, status);

	status = hash_get_block_size (HASH_TYPE_SHA512);
	CuAssertIntEquals (test, SHA512_BLOCK_SIZE, status);
}

static void hash_test_get_block_size_unsupported (CuTest *test)
{
	int status;

	TEST_START;

	status = hash_get_block_size (HASH_TYPE_INVALID);
	CuAssertIntEquals (test, HASH_ENGINE_UNKNOWN_HASH, status);
}

static void hash_test_is_alg_supported (CuTest *test)
{
	int status;

	TEST_START;

	status = hash_is_alg_supported (HASH_TYPE_SHA1);
#ifdef HASH_ENABLE_SHA1
	CuAssertIntEquals (test, 1, status);
#else
	CuAssertIntEquals (test, 0, status);
#endif

	status = hash_is_alg_supported (HASH_TYPE_SHA256);
	CuAssertIntEquals (test, 1, status);

	status = hash_is_alg_supported (HASH_TYPE_SHA384);
#ifdef HASH_ENABLE_SHA384
	CuAssertIntEquals (test, 1, status);
#else
	CuAssertIntEquals (test, 0, status);
#endif

	status = hash_is_alg_supported (HASH_TYPE_SHA512);
#ifdef HASH_ENABLE_SHA512
	CuAssertIntEquals (test, 1, status);
#else
	CuAssertIntEquals (test, 0, status);
#endif

	status = hash_is_alg_supported ((enum hash_type) (HASH_TYPE_SHA512 + 1));
	CuAssertIntEquals (test, 0, status);
}

static void hash_test_run_self_test_sha1 (CuTest *test)
{
	HASH_TESTING_ENGINE engine;
	int status;

	TEST_START;

	status = HASH_TESTING_ENGINE_INIT (&engine);
	CuAssertIntEquals (test, 0, status);

	status = hash_run_self_test_sha1 (&engine.base);
#ifdef HASH_ENABLE_SHA1
	CuAssertIntEquals (test, 0, status);
#else
	CuAssertIntEquals (test, HASH_ENGINE_UNSUPPORTED_HASH, status);
#endif

	HASH_TESTING_ENGINE_RELEASE (&engine);
}

#ifdef HASH_ENABLE_SHA1
static void hash_test_run_self_test_sha1_mismatch_data_calculate (CuTest *test)
{
	struct hash_engine_mock engine;
	int status;

	TEST_START;

	status = hash_mock_init (&engine);
	CuAssertIntEquals (test, 0, status);

	status = mock_expect (&engine.mock, engine.base.calculate_sha1, &engine, 0,
		MOCK_ARG_PTR_CONTAINS (SHA_KAT_VECTORS_CALCULATE_DATA, SHA_KAT_VECTORS_CALCULATE_DATA_LEN),
		MOCK_ARG (SHA_KAT_VECTORS_CALCULATE_DATA_LEN), MOCK_ARG_NOT_NULL,
		MOCK_ARG_AT_LEAST (SHA1_HASH_LENGTH));
	status |= mock_expect_output (&engine.mock, 2, SHA1_TEST_HASH, SHA1_HASH_LENGTH, 3);

	CuAssertIntEquals (test, 0, status);

	status = hash_run_self_test_sha1 (&engine.base);
	CuAssertIntEquals (test, HASH_ENGINE_SHA1_SELF_TEST_FAILED, status);

	status = hash_mock_validate_and_release (&engine);
	CuAssertIntEquals (test, 0, status);
}

static void hash_test_run_self_test_sha1_mismatch_data_update (CuTest *test)
{
	struct hash_engine_mock engine;
	int status;

	TEST_START;

	status = hash_mock_init (&engine);
	CuAssertIntEquals (test, 0, status);

	status = mock_expect (&engine.mock, engine.base.calculate_sha1, &engine, 0,
		MOCK_ARG_PTR_CONTAINS (SHA_KAT_VECTORS_CALCULATE_DATA, SHA_KAT_VECTORS_CALCULATE_DATA_LEN),
		MOCK_ARG (SHA_KAT_VECTORS_CALCULATE_DATA_LEN), MOCK_ARG_NOT_NULL,
		MOCK_ARG_AT_LEAST (SHA1_HASH_LENGTH));
	status |= mock_expect_output (&engine.mock, 2, SHA_KAT_VECTORS_CALCULATE_SHA1_DIGEST,
		SHA1_HASH_LENGTH, 3);

	status |= mock_expect (&engine.mock, engine.base.start_sha1, &engine, 0);
	status |= mock_expect (&engine.mock, engine.base.update, &engine, 0,
		MOCK_ARG_PTR_CONTAINS (SHA_KAT_VECTORS_UPDATE_DATA_1, SHA_KAT_VECTORS_UPDATE_DATA_1_LEN),
		MOCK_ARG (SHA_KAT_VECTORS_UPDATE_DATA_1_LEN));
	status |= mock_expect (&engine.mock, engine.base.update, &engine, 0,
		MOCK_ARG_PTR_CONTAINS (SHA_KAT_VECTORS_UPDATE_DATA_2, SHA_KAT_VECTORS_UPDATE_DATA_2_LEN),
		MOCK_ARG (SHA_KAT_VECTORS_UPDATE_DATA_2_LEN));

	status |= mock_expect (&engine.mock, engine.base.finish, &engine, 0,
		MOCK_ARG_NOT_NULL, MOCK_ARG_AT_LEAST (SHA1_HASH_LENGTH));
	status |= mock_expect_output (&engine.mock, 0, SHA1_TEST2_HASH, SHA1_HASH_LENGTH, 1);

	CuAssertIntEquals (test, 0, status);

	status = hash_run_self_test_sha1 (&engine.base);
	CuAssertIntEquals (test, HASH_ENGINE_SHA1_SELF_TEST_FAILED, status);

	status = hash_mock_validate_and_release (&engine);
	CuAssertIntEquals (test, 0, status);
}

static void hash_test_run_self_test_sha1_null (CuTest *test)
{
	HASH_TESTING_ENGINE engine;
	int status;

	TEST_START;

	status = HASH_TESTING_ENGINE_INIT (&engine);
	CuAssertIntEquals (test, 0, status);

	status = hash_run_self_test_sha1 (NULL);
	CuAssertIntEquals (test, HASH_ENGINE_INVALID_ARGUMENT, status);

	HASH_TESTING_ENGINE_RELEASE (&engine);
}

static void hash_test_run_self_test_sha1_calculate_fail (CuTest *test)
{
	struct hash_engine_mock engine;
	int status;

	TEST_START;

	status = hash_mock_init (&engine);
	CuAssertIntEquals (test, 0, status);

	status = mock_expect (&engine.mock, engine.base.calculate_sha1, &engine,
		HASH_ENGINE_SHA1_FAILED,
		MOCK_ARG_PTR_CONTAINS (SHA_KAT_VECTORS_CALCULATE_DATA, SHA_KAT_VECTORS_CALCULATE_DATA_LEN),
		MOCK_ARG (SHA_KAT_VECTORS_CALCULATE_DATA_LEN), MOCK_ARG_NOT_NULL,
		MOCK_ARG_AT_LEAST (SHA1_HASH_LENGTH));
	CuAssertIntEquals (test, 0, status);

	status = hash_run_self_test_sha1 (&engine.base);
	CuAssertIntEquals (test, HASH_ENGINE_SHA1_FAILED, status);

	status = hash_mock_validate_and_release (&engine);
	CuAssertIntEquals (test, 0, status);
}

static void hash_test_run_self_test_sha1_start_fail (CuTest *test)
{
	struct hash_engine_mock engine;
	int status;

	TEST_START;

	status = hash_mock_init (&engine);
	CuAssertIntEquals (test, 0, status);

	status = mock_expect (&engine.mock, engine.base.calculate_sha1, &engine, 0,
		MOCK_ARG_PTR_CONTAINS (SHA_KAT_VECTORS_CALCULATE_DATA, SHA_KAT_VECTORS_CALCULATE_DATA_LEN),
		MOCK_ARG (SHA_KAT_VECTORS_CALCULATE_DATA_LEN), MOCK_ARG_NOT_NULL,
		MOCK_ARG_AT_LEAST (SHA1_HASH_LENGTH));
	status |= mock_expect_output (&engine.mock, 2, SHA_KAT_VECTORS_CALCULATE_SHA1_DIGEST,
		SHA1_HASH_LENGTH, 3);

	status |= mock_expect (&engine.mock, engine.base.start_sha1, &engine,
		HASH_ENGINE_START_SHA1_FAILED);

	CuAssertIntEquals (test, 0, status);

	status = hash_run_self_test_sha1 (&engine.base);
	CuAssertIntEquals (test, HASH_ENGINE_START_SHA1_FAILED, status);

	status = hash_mock_validate_and_release (&engine);
	CuAssertIntEquals (test, 0, status);
}

static void hash_test_run_self_test_sha1_update_first_fail (CuTest *test)
{
	struct hash_engine_mock engine;
	int status;

	TEST_START;

	status = hash_mock_init (&engine);
	CuAssertIntEquals (test, 0, status);

	status = mock_expect (&engine.mock, engine.base.calculate_sha1, &engine, 0,
		MOCK_ARG_PTR_CONTAINS (SHA_KAT_VECTORS_CALCULATE_DATA, SHA_KAT_VECTORS_CALCULATE_DATA_LEN),
		MOCK_ARG (SHA_KAT_VECTORS_CALCULATE_DATA_LEN), MOCK_ARG_NOT_NULL,
		MOCK_ARG_AT_LEAST (SHA1_HASH_LENGTH));
	status |= mock_expect_output (&engine.mock, 2, SHA_KAT_VECTORS_CALCULATE_SHA1_DIGEST,
		SHA1_HASH_LENGTH, 3);

	status |= mock_expect (&engine.mock, engine.base.start_sha1, &engine, 0);
	status |= mock_expect (&engine.mock, engine.base.update, &engine, HASH_ENGINE_UPDATE_FAILED,
		MOCK_ARG_PTR_CONTAINS (SHA_KAT_VECTORS_UPDATE_DATA_1, SHA_KAT_VECTORS_UPDATE_DATA_1_LEN),
		MOCK_ARG (SHA_KAT_VECTORS_UPDATE_DATA_1_LEN));

	status |= mock_expect (&engine.mock, engine.base.cancel, &engine, 0);

	CuAssertIntEquals (test, 0, status);

	status = hash_run_self_test_sha1 (&engine.base);
	CuAssertIntEquals (test, HASH_ENGINE_UPDATE_FAILED, status);

	status = hash_mock_validate_and_release (&engine);
	CuAssertIntEquals (test, 0, status);
}

static void hash_test_run_self_test_sha1_update_second_fail (CuTest *test)
{
	struct hash_engine_mock engine;
	int status;

	TEST_START;

	status = hash_mock_init (&engine);
	CuAssertIntEquals (test, 0, status);

	status = mock_expect (&engine.mock, engine.base.calculate_sha1, &engine, 0,
		MOCK_ARG_PTR_CONTAINS (SHA_KAT_VECTORS_CALCULATE_DATA, SHA_KAT_VECTORS_CALCULATE_DATA_LEN),
		MOCK_ARG (SHA_KAT_VECTORS_CALCULATE_DATA_LEN), MOCK_ARG_NOT_NULL,
		MOCK_ARG_AT_LEAST (SHA1_HASH_LENGTH));
	status |= mock_expect_output (&engine.mock, 2, SHA_KAT_VECTORS_CALCULATE_SHA1_DIGEST,
		SHA1_HASH_LENGTH, 3);

	status |= mock_expect (&engine.mock, engine.base.start_sha1, &engine, 0);
	status |= mock_expect (&engine.mock, engine.base.update, &engine, 0,
		MOCK_ARG_PTR_CONTAINS (SHA_KAT_VECTORS_UPDATE_DATA_1, SHA_KAT_VECTORS_UPDATE_DATA_1_LEN),
		MOCK_ARG (SHA_KAT_VECTORS_UPDATE_DATA_1_LEN));
	status |= mock_expect (&engine.mock, engine.base.update, &engine, HASH_ENGINE_UPDATE_FAILED,
		MOCK_ARG_PTR_CONTAINS (SHA_KAT_VECTORS_UPDATE_DATA_2, SHA_KAT_VECTORS_UPDATE_DATA_2_LEN),
		MOCK_ARG (SHA_KAT_VECTORS_UPDATE_DATA_2_LEN));

	status |= mock_expect (&engine.mock, engine.base.cancel, &engine, 0);

	CuAssertIntEquals (test, 0, status);

	status = hash_run_self_test_sha1 (&engine.base);
	CuAssertIntEquals (test, HASH_ENGINE_UPDATE_FAILED, status);

	status = hash_mock_validate_and_release (&engine);
	CuAssertIntEquals (test, 0, status);
}

static void hash_test_run_self_test_sha1_finish_fail (CuTest *test)
{
	struct hash_engine_mock engine;
	int status;

	TEST_START;

	status = hash_mock_init (&engine);
	CuAssertIntEquals (test, 0, status);

	status = mock_expect (&engine.mock, engine.base.calculate_sha1, &engine, 0,
		MOCK_ARG_PTR_CONTAINS (SHA_KAT_VECTORS_CALCULATE_DATA, SHA_KAT_VECTORS_CALCULATE_DATA_LEN),
		MOCK_ARG (SHA_KAT_VECTORS_CALCULATE_DATA_LEN), MOCK_ARG_NOT_NULL,
		MOCK_ARG_AT_LEAST (SHA1_HASH_LENGTH));
	status |= mock_expect_output (&engine.mock, 2, SHA_KAT_VECTORS_CALCULATE_SHA1_DIGEST,
		SHA1_HASH_LENGTH, 3);

	status |= mock_expect (&engine.mock, engine.base.start_sha1, &engine, 0);
	status |= mock_expect (&engine.mock, engine.base.update, &engine, 0,
		MOCK_ARG_PTR_CONTAINS (SHA_KAT_VECTORS_UPDATE_DATA_1, SHA_KAT_VECTORS_UPDATE_DATA_1_LEN),
		MOCK_ARG (SHA_KAT_VECTORS_UPDATE_DATA_1_LEN));
	status |= mock_expect (&engine.mock, engine.base.update, &engine, 0,
		MOCK_ARG_PTR_CONTAINS (SHA_KAT_VECTORS_UPDATE_DATA_2, SHA_KAT_VECTORS_UPDATE_DATA_2_LEN),
		MOCK_ARG (SHA_KAT_VECTORS_UPDATE_DATA_2_LEN));

	status |= mock_expect (&engine.mock, engine.base.finish, &engine, HASH_ENGINE_FINISH_FAILED,
		MOCK_ARG_NOT_NULL, MOCK_ARG_AT_LEAST (SHA1_HASH_LENGTH));

	status |= mock_expect (&engine.mock, engine.base.cancel, &engine, 0);

	CuAssertIntEquals (test, 0, status);

	status = hash_run_self_test_sha1 (&engine.base);
	CuAssertIntEquals (test, HASH_ENGINE_FINISH_FAILED, status);

	status = hash_mock_validate_and_release (&engine);
	CuAssertIntEquals (test, 0, status);
}
#endif

static void hash_test_run_self_test_sha256 (CuTest *test)
{
	HASH_TESTING_ENGINE engine;
	int status;

	TEST_START;

	status = HASH_TESTING_ENGINE_INIT (&engine);
	CuAssertIntEquals (test, 0, status);

	status = hash_run_self_test_sha256 (&engine.base);
	CuAssertIntEquals (test, 0, status);

	HASH_TESTING_ENGINE_RELEASE (&engine);
}

static void hash_test_run_self_test_sha256_mismatch_data_calculate (CuTest *test)
{
	struct hash_engine_mock engine;
	int status;

	TEST_START;

	status = hash_mock_init (&engine);
	CuAssertIntEquals (test, 0, status);

	status = mock_expect (&engine.mock, engine.base.calculate_sha256, &engine, 0,
		MOCK_ARG_PTR_CONTAINS (SHA_KAT_VECTORS_CALCULATE_DATA, SHA_KAT_VECTORS_CALCULATE_DATA_LEN),
		MOCK_ARG (SHA_KAT_VECTORS_CALCULATE_DATA_LEN), MOCK_ARG_NOT_NULL,
		MOCK_ARG_AT_LEAST (SHA256_HASH_LENGTH));
	status |= mock_expect_output (&engine.mock, 2, SHA256_TEST_HASH, SHA256_HASH_LENGTH, 3);

	CuAssertIntEquals (test, 0, status);

	status = hash_run_self_test_sha256 (&engine.base);
	CuAssertIntEquals (test, HASH_ENGINE_SHA256_SELF_TEST_FAILED, status);

	status = hash_mock_validate_and_release (&engine);
	CuAssertIntEquals (test, 0, status);
}

static void hash_test_run_self_test_sha256_mismatch_data_update (CuTest *test)
{
	struct hash_engine_mock engine;
	int status;

	TEST_START;

	status = hash_mock_init (&engine);
	CuAssertIntEquals (test, 0, status);

	status = mock_expect (&engine.mock, engine.base.calculate_sha256, &engine, 0,
		MOCK_ARG_PTR_CONTAINS (SHA_KAT_VECTORS_CALCULATE_DATA, SHA_KAT_VECTORS_CALCULATE_DATA_LEN),
		MOCK_ARG (SHA_KAT_VECTORS_CALCULATE_DATA_LEN), MOCK_ARG_NOT_NULL,
		MOCK_ARG_AT_LEAST (SHA256_HASH_LENGTH));
	status |= mock_expect_output (&engine.mock, 2, SHA_KAT_VECTORS_CALCULATE_SHA256_DIGEST,
		SHA256_HASH_LENGTH, 3);

	status |= mock_expect (&engine.mock, engine.base.start_sha256, &engine, 0);
	status |= mock_expect (&engine.mock, engine.base.update, &engine, 0,
		MOCK_ARG_PTR_CONTAINS (SHA_KAT_VECTORS_UPDATE_DATA_1, SHA_KAT_VECTORS_UPDATE_DATA_1_LEN),
		MOCK_ARG (SHA_KAT_VECTORS_UPDATE_DATA_1_LEN));
	status |= mock_expect (&engine.mock, engine.base.update, &engine, 0,
		MOCK_ARG_PTR_CONTAINS (SHA_KAT_VECTORS_UPDATE_DATA_2, SHA_KAT_VECTORS_UPDATE_DATA_2_LEN),
		MOCK_ARG (SHA_KAT_VECTORS_UPDATE_DATA_2_LEN));

	status |= mock_expect (&engine.mock, engine.base.finish, &engine, 0,
		MOCK_ARG_NOT_NULL, MOCK_ARG_AT_LEAST (SHA256_HASH_LENGTH));
	status |= mock_expect_output (&engine.mock, 0, SHA256_TEST2_HASH, SHA256_HASH_LENGTH, 1);

	CuAssertIntEquals (test, 0, status);

	status = hash_run_self_test_sha256 (&engine.base);
	CuAssertIntEquals (test, HASH_ENGINE_SHA256_SELF_TEST_FAILED, status);

	status = hash_mock_validate_and_release (&engine);
	CuAssertIntEquals (test, 0, status);
}

static void hash_test_run_self_test_sha256_null (CuTest *test)
{
	HASH_TESTING_ENGINE engine;
	int status;

	TEST_START;

	status = HASH_TESTING_ENGINE_INIT (&engine);
	CuAssertIntEquals (test, 0, status);

	status = hash_run_self_test_sha256 (NULL);
	CuAssertIntEquals (test, HASH_ENGINE_INVALID_ARGUMENT, status);

	HASH_TESTING_ENGINE_RELEASE (&engine);
}

static void hash_test_run_self_test_sha256_calculate_fail (CuTest *test)
{
	struct hash_engine_mock engine;
	int status;

	TEST_START;

	status = hash_mock_init (&engine);
	CuAssertIntEquals (test, 0, status);

	status = mock_expect (&engine.mock, engine.base.calculate_sha256, &engine,
		HASH_ENGINE_SHA256_FAILED,
		MOCK_ARG_PTR_CONTAINS (SHA_KAT_VECTORS_CALCULATE_DATA, SHA_KAT_VECTORS_CALCULATE_DATA_LEN),
		MOCK_ARG (SHA_KAT_VECTORS_CALCULATE_DATA_LEN), MOCK_ARG_NOT_NULL,
		MOCK_ARG_AT_LEAST (SHA256_HASH_LENGTH));
	CuAssertIntEquals (test, 0, status);

	status = hash_run_self_test_sha256 (&engine.base);
	CuAssertIntEquals (test, HASH_ENGINE_SHA256_FAILED, status);

	status = hash_mock_validate_and_release (&engine);
	CuAssertIntEquals (test, 0, status);
}

static void hash_test_run_self_test_sha256_start_fail (CuTest *test)
{
	struct hash_engine_mock engine;
	int status;

	TEST_START;

	status = hash_mock_init (&engine);
	CuAssertIntEquals (test, 0, status);

	status = mock_expect (&engine.mock, engine.base.calculate_sha256, &engine, 0,
		MOCK_ARG_PTR_CONTAINS (SHA_KAT_VECTORS_CALCULATE_DATA, SHA_KAT_VECTORS_CALCULATE_DATA_LEN),
		MOCK_ARG (SHA_KAT_VECTORS_CALCULATE_DATA_LEN), MOCK_ARG_NOT_NULL,
		MOCK_ARG_AT_LEAST (SHA256_HASH_LENGTH));
	status |= mock_expect_output (&engine.mock, 2, SHA_KAT_VECTORS_CALCULATE_SHA256_DIGEST,
		SHA256_HASH_LENGTH, 3);

	status |= mock_expect (&engine.mock, engine.base.start_sha256, &engine,
		HASH_ENGINE_START_SHA256_FAILED);

	CuAssertIntEquals (test, 0, status);

	status = hash_run_self_test_sha256 (&engine.base);
	CuAssertIntEquals (test, HASH_ENGINE_START_SHA256_FAILED, status);

	status = hash_mock_validate_and_release (&engine);
	CuAssertIntEquals (test, 0, status);
}

static void hash_test_run_self_test_sha256_update_first_fail (CuTest *test)
{
	struct hash_engine_mock engine;
	int status;

	TEST_START;

	status = hash_mock_init (&engine);
	CuAssertIntEquals (test, 0, status);

	status = mock_expect (&engine.mock, engine.base.calculate_sha256, &engine, 0,
		MOCK_ARG_PTR_CONTAINS (SHA_KAT_VECTORS_CALCULATE_DATA, SHA_KAT_VECTORS_CALCULATE_DATA_LEN),
		MOCK_ARG (SHA_KAT_VECTORS_CALCULATE_DATA_LEN), MOCK_ARG_NOT_NULL,
		MOCK_ARG_AT_LEAST (SHA256_HASH_LENGTH));
	status |= mock_expect_output (&engine.mock, 2, SHA_KAT_VECTORS_CALCULATE_SHA256_DIGEST,
		SHA256_HASH_LENGTH, 3);

	status |= mock_expect (&engine.mock, engine.base.start_sha256, &engine, 0);
	status |= mock_expect (&engine.mock, engine.base.update, &engine, HASH_ENGINE_UPDATE_FAILED,
		MOCK_ARG_PTR_CONTAINS (SHA_KAT_VECTORS_UPDATE_DATA_1, SHA_KAT_VECTORS_UPDATE_DATA_1_LEN),
		MOCK_ARG (SHA_KAT_VECTORS_UPDATE_DATA_1_LEN));

	status |= mock_expect (&engine.mock, engine.base.cancel, &engine, 0);

	CuAssertIntEquals (test, 0, status);

	status = hash_run_self_test_sha256 (&engine.base);
	CuAssertIntEquals (test, HASH_ENGINE_UPDATE_FAILED, status);

	status = hash_mock_validate_and_release (&engine);
	CuAssertIntEquals (test, 0, status);
}

static void hash_test_run_self_test_sha256_update_second_fail (CuTest *test)
{
	struct hash_engine_mock engine;
	int status;

	TEST_START;

	status = hash_mock_init (&engine);
	CuAssertIntEquals (test, 0, status);

	status = mock_expect (&engine.mock, engine.base.calculate_sha256, &engine, 0,
		MOCK_ARG_PTR_CONTAINS (SHA_KAT_VECTORS_CALCULATE_DATA, SHA_KAT_VECTORS_CALCULATE_DATA_LEN),
		MOCK_ARG (SHA_KAT_VECTORS_CALCULATE_DATA_LEN), MOCK_ARG_NOT_NULL,
		MOCK_ARG_AT_LEAST (SHA256_HASH_LENGTH));
	status |= mock_expect_output (&engine.mock, 2, SHA_KAT_VECTORS_CALCULATE_SHA256_DIGEST,
		SHA256_HASH_LENGTH, 3);

	status |= mock_expect (&engine.mock, engine.base.start_sha256, &engine, 0);
	status |= mock_expect (&engine.mock, engine.base.update, &engine, 0,
		MOCK_ARG_PTR_CONTAINS (SHA_KAT_VECTORS_UPDATE_DATA_1, SHA_KAT_VECTORS_UPDATE_DATA_1_LEN),
		MOCK_ARG (SHA_KAT_VECTORS_UPDATE_DATA_1_LEN));
	status |= mock_expect (&engine.mock, engine.base.update, &engine, HASH_ENGINE_UPDATE_FAILED,
		MOCK_ARG_PTR_CONTAINS (SHA_KAT_VECTORS_UPDATE_DATA_2, SHA_KAT_VECTORS_UPDATE_DATA_2_LEN),
		MOCK_ARG (SHA_KAT_VECTORS_UPDATE_DATA_2_LEN));

	status |= mock_expect (&engine.mock, engine.base.cancel, &engine, 0);

	CuAssertIntEquals (test, 0, status);

	status = hash_run_self_test_sha256 (&engine.base);
	CuAssertIntEquals (test, HASH_ENGINE_UPDATE_FAILED, status);

	status = hash_mock_validate_and_release (&engine);
	CuAssertIntEquals (test, 0, status);
}

static void hash_test_run_self_test_sha256_finish_fail (CuTest *test)
{
	struct hash_engine_mock engine;
	int status;

	TEST_START;

	status = hash_mock_init (&engine);
	CuAssertIntEquals (test, 0, status);

	status = mock_expect (&engine.mock, engine.base.calculate_sha256, &engine, 0,
		MOCK_ARG_PTR_CONTAINS (SHA_KAT_VECTORS_CALCULATE_DATA, SHA_KAT_VECTORS_CALCULATE_DATA_LEN),
		MOCK_ARG (SHA_KAT_VECTORS_CALCULATE_DATA_LEN), MOCK_ARG_NOT_NULL,
		MOCK_ARG_AT_LEAST (SHA256_HASH_LENGTH));
	status |= mock_expect_output (&engine.mock, 2, SHA_KAT_VECTORS_CALCULATE_SHA256_DIGEST,
		SHA256_HASH_LENGTH, 3);

	status |= mock_expect (&engine.mock, engine.base.start_sha256, &engine, 0);
	status |= mock_expect (&engine.mock, engine.base.update, &engine, 0,
		MOCK_ARG_PTR_CONTAINS (SHA_KAT_VECTORS_UPDATE_DATA_1, SHA_KAT_VECTORS_UPDATE_DATA_1_LEN),
		MOCK_ARG (SHA_KAT_VECTORS_UPDATE_DATA_1_LEN));
	status |= mock_expect (&engine.mock, engine.base.update, &engine, 0,
		MOCK_ARG_PTR_CONTAINS (SHA_KAT_VECTORS_UPDATE_DATA_2, SHA_KAT_VECTORS_UPDATE_DATA_2_LEN),
		MOCK_ARG (SHA_KAT_VECTORS_UPDATE_DATA_2_LEN));

	status |= mock_expect (&engine.mock, engine.base.finish, &engine, HASH_ENGINE_FINISH_FAILED,
		MOCK_ARG_NOT_NULL, MOCK_ARG_AT_LEAST (SHA256_HASH_LENGTH));

	status |= mock_expect (&engine.mock, engine.base.cancel, &engine, 0);

	CuAssertIntEquals (test, 0, status);

	status = hash_run_self_test_sha256 (&engine.base);
	CuAssertIntEquals (test, HASH_ENGINE_FINISH_FAILED, status);

	status = hash_mock_validate_and_release (&engine);
	CuAssertIntEquals (test, 0, status);
}

static void hash_test_run_self_test_sha384 (CuTest *test)
{
	HASH_TESTING_ENGINE engine;
	int status;

	TEST_START;

	status = HASH_TESTING_ENGINE_INIT (&engine);
	CuAssertIntEquals (test, 0, status);

	status = hash_run_self_test_sha384 (&engine.base);
#ifdef HASH_ENABLE_SHA384
	CuAssertIntEquals (test, 0, status);
#else
	CuAssertIntEquals (test, HASH_ENGINE_UNSUPPORTED_HASH, status);
#endif

	HASH_TESTING_ENGINE_RELEASE (&engine);
}

#ifdef HASH_ENABLE_SHA384
static void hash_test_run_self_test_sha384_mismatch_data_calculate (CuTest *test)
{
	struct hash_engine_mock engine;
	int status;

	TEST_START;

	status = hash_mock_init (&engine);
	CuAssertIntEquals (test, 0, status);

	status = mock_expect (&engine.mock, engine.base.calculate_sha384, &engine, 0,
		MOCK_ARG_PTR_CONTAINS (SHA_KAT_VECTORS_CALCULATE_DATA, SHA_KAT_VECTORS_CALCULATE_DATA_LEN),
		MOCK_ARG (SHA_KAT_VECTORS_CALCULATE_DATA_LEN), MOCK_ARG_NOT_NULL,
		MOCK_ARG_AT_LEAST (SHA384_HASH_LENGTH));
	status |= mock_expect_output (&engine.mock, 2, SHA384_TEST_HASH, SHA384_HASH_LENGTH, 3);

	CuAssertIntEquals (test, 0, status);

	status = hash_run_self_test_sha384 (&engine.base);
	CuAssertIntEquals (test, HASH_ENGINE_SHA384_SELF_TEST_FAILED, status);

	status = hash_mock_validate_and_release (&engine);
	CuAssertIntEquals (test, 0, status);
}

static void hash_test_run_self_test_sha384_mismatch_data_update (CuTest *test)
{
	struct hash_engine_mock engine;
	int status;

	TEST_START;

	status = hash_mock_init (&engine);
	CuAssertIntEquals (test, 0, status);

	status = mock_expect (&engine.mock, engine.base.calculate_sha384, &engine, 0,
		MOCK_ARG_PTR_CONTAINS (SHA_KAT_VECTORS_CALCULATE_DATA, SHA_KAT_VECTORS_CALCULATE_DATA_LEN),
		MOCK_ARG (SHA_KAT_VECTORS_CALCULATE_DATA_LEN), MOCK_ARG_NOT_NULL,
		MOCK_ARG_AT_LEAST (SHA384_HASH_LENGTH));
	status |= mock_expect_output (&engine.mock, 2, SHA_KAT_VECTORS_CALCULATE_SHA384_DIGEST,
		SHA384_HASH_LENGTH, 3);

	status |= mock_expect (&engine.mock, engine.base.start_sha384, &engine, 0);
	status |= mock_expect (&engine.mock, engine.base.update, &engine, 0,
		MOCK_ARG_PTR_CONTAINS (SHA_KAT_VECTORS_UPDATE_DATA_1, SHA_KAT_VECTORS_UPDATE_DATA_1_LEN),
		MOCK_ARG (SHA_KAT_VECTORS_UPDATE_DATA_1_LEN));
	status |= mock_expect (&engine.mock, engine.base.update, &engine, 0,
		MOCK_ARG_PTR_CONTAINS (SHA_KAT_VECTORS_UPDATE_DATA_2, SHA_KAT_VECTORS_UPDATE_DATA_2_LEN),
		MOCK_ARG (SHA_KAT_VECTORS_UPDATE_DATA_2_LEN));

	status |= mock_expect (&engine.mock, engine.base.finish, &engine, 0,
		MOCK_ARG_NOT_NULL, MOCK_ARG_AT_LEAST (SHA384_HASH_LENGTH));
	status |= mock_expect_output (&engine.mock, 0, SHA384_TEST2_HASH, SHA384_HASH_LENGTH, 1);

	CuAssertIntEquals (test, 0, status);

	status = hash_run_self_test_sha384 (&engine.base);
	CuAssertIntEquals (test, HASH_ENGINE_SHA384_SELF_TEST_FAILED, status);

	status = hash_mock_validate_and_release (&engine);
	CuAssertIntEquals (test, 0, status);
}

static void hash_test_run_self_test_sha384_null (CuTest *test)
{
	HASH_TESTING_ENGINE engine;
	int status;

	TEST_START;

	status = HASH_TESTING_ENGINE_INIT (&engine);
	CuAssertIntEquals (test, 0, status);

	status = hash_run_self_test_sha384 (NULL);
	CuAssertIntEquals (test, HASH_ENGINE_INVALID_ARGUMENT, status);

	HASH_TESTING_ENGINE_RELEASE (&engine);
}

static void hash_test_run_self_test_sha384_calculate_fail (CuTest *test)
{
	struct hash_engine_mock engine;
	int status;

	TEST_START;

	status = hash_mock_init (&engine);
	CuAssertIntEquals (test, 0, status);

	status = mock_expect (&engine.mock, engine.base.calculate_sha384, &engine,
		HASH_ENGINE_SHA384_FAILED,
		MOCK_ARG_PTR_CONTAINS (SHA_KAT_VECTORS_CALCULATE_DATA, SHA_KAT_VECTORS_CALCULATE_DATA_LEN),
		MOCK_ARG (SHA_KAT_VECTORS_CALCULATE_DATA_LEN), MOCK_ARG_NOT_NULL,
		MOCK_ARG_AT_LEAST (SHA384_HASH_LENGTH));
	CuAssertIntEquals (test, 0, status);

	status = hash_run_self_test_sha384 (&engine.base);
	CuAssertIntEquals (test, HASH_ENGINE_SHA384_FAILED, status);

	status = hash_mock_validate_and_release (&engine);
	CuAssertIntEquals (test, 0, status);
}

static void hash_test_run_self_test_sha384_start_fail (CuTest *test)
{
	struct hash_engine_mock engine;
	int status;

	TEST_START;

	status = hash_mock_init (&engine);
	CuAssertIntEquals (test, 0, status);

	status = mock_expect (&engine.mock, engine.base.calculate_sha384, &engine, 0,
		MOCK_ARG_PTR_CONTAINS (SHA_KAT_VECTORS_CALCULATE_DATA, SHA_KAT_VECTORS_CALCULATE_DATA_LEN),
		MOCK_ARG (SHA_KAT_VECTORS_CALCULATE_DATA_LEN), MOCK_ARG_NOT_NULL,
		MOCK_ARG_AT_LEAST (SHA384_HASH_LENGTH));
	status |= mock_expect_output (&engine.mock, 2, SHA_KAT_VECTORS_CALCULATE_SHA384_DIGEST,
		SHA384_HASH_LENGTH, 3);

	status |= mock_expect (&engine.mock, engine.base.start_sha384, &engine,
		HASH_ENGINE_START_SHA384_FAILED);

	CuAssertIntEquals (test, 0, status);

	status = hash_run_self_test_sha384 (&engine.base);
	CuAssertIntEquals (test, HASH_ENGINE_START_SHA384_FAILED, status);

	status = hash_mock_validate_and_release (&engine);
	CuAssertIntEquals (test, 0, status);
}

static void hash_test_run_self_test_sha384_update_first_fail (CuTest *test)
{
	struct hash_engine_mock engine;
	int status;

	TEST_START;

	status = hash_mock_init (&engine);
	CuAssertIntEquals (test, 0, status);

	status = mock_expect (&engine.mock, engine.base.calculate_sha384, &engine, 0,
		MOCK_ARG_PTR_CONTAINS (SHA_KAT_VECTORS_CALCULATE_DATA, SHA_KAT_VECTORS_CALCULATE_DATA_LEN),
		MOCK_ARG (SHA_KAT_VECTORS_CALCULATE_DATA_LEN), MOCK_ARG_NOT_NULL,
		MOCK_ARG_AT_LEAST (SHA384_HASH_LENGTH));
	status |= mock_expect_output (&engine.mock, 2, SHA_KAT_VECTORS_CALCULATE_SHA384_DIGEST,
		SHA384_HASH_LENGTH, 3);

	status |= mock_expect (&engine.mock, engine.base.start_sha384, &engine, 0);
	status |= mock_expect (&engine.mock, engine.base.update, &engine, HASH_ENGINE_UPDATE_FAILED,
		MOCK_ARG_PTR_CONTAINS (SHA_KAT_VECTORS_UPDATE_DATA_1, SHA_KAT_VECTORS_UPDATE_DATA_1_LEN),
		MOCK_ARG (SHA_KAT_VECTORS_UPDATE_DATA_1_LEN));

	status |= mock_expect (&engine.mock, engine.base.cancel, &engine, 0);

	CuAssertIntEquals (test, 0, status);

	status = hash_run_self_test_sha384 (&engine.base);
	CuAssertIntEquals (test, HASH_ENGINE_UPDATE_FAILED, status);

	status = hash_mock_validate_and_release (&engine);
	CuAssertIntEquals (test, 0, status);
}

static void hash_test_run_self_test_sha384_update_second_fail (CuTest *test)
{
	struct hash_engine_mock engine;
	int status;

	TEST_START;

	status = hash_mock_init (&engine);
	CuAssertIntEquals (test, 0, status);

	status = mock_expect (&engine.mock, engine.base.calculate_sha384, &engine, 0,
		MOCK_ARG_PTR_CONTAINS (SHA_KAT_VECTORS_CALCULATE_DATA, SHA_KAT_VECTORS_CALCULATE_DATA_LEN),
		MOCK_ARG (SHA_KAT_VECTORS_CALCULATE_DATA_LEN), MOCK_ARG_NOT_NULL,
		MOCK_ARG_AT_LEAST (SHA384_HASH_LENGTH));
	status |= mock_expect_output (&engine.mock, 2, SHA_KAT_VECTORS_CALCULATE_SHA384_DIGEST,
		SHA384_HASH_LENGTH, 3);

	status |= mock_expect (&engine.mock, engine.base.start_sha384, &engine, 0);
	status |= mock_expect (&engine.mock, engine.base.update, &engine, 0,
		MOCK_ARG_PTR_CONTAINS (SHA_KAT_VECTORS_UPDATE_DATA_1, SHA_KAT_VECTORS_UPDATE_DATA_1_LEN),
		MOCK_ARG (SHA_KAT_VECTORS_UPDATE_DATA_1_LEN));
	status |= mock_expect (&engine.mock, engine.base.update, &engine, HASH_ENGINE_UPDATE_FAILED,
		MOCK_ARG_PTR_CONTAINS (SHA_KAT_VECTORS_UPDATE_DATA_2, SHA_KAT_VECTORS_UPDATE_DATA_2_LEN),
		MOCK_ARG (SHA_KAT_VECTORS_UPDATE_DATA_2_LEN));

	status |= mock_expect (&engine.mock, engine.base.cancel, &engine, 0);

	CuAssertIntEquals (test, 0, status);

	status = hash_run_self_test_sha384 (&engine.base);
	CuAssertIntEquals (test, HASH_ENGINE_UPDATE_FAILED, status);

	status = hash_mock_validate_and_release (&engine);
	CuAssertIntEquals (test, 0, status);
}

static void hash_test_run_self_test_sha384_finish_fail (CuTest *test)
{
	struct hash_engine_mock engine;
	int status;

	TEST_START;

	status = hash_mock_init (&engine);
	CuAssertIntEquals (test, 0, status);

	status = mock_expect (&engine.mock, engine.base.calculate_sha384, &engine, 0,
		MOCK_ARG_PTR_CONTAINS (SHA_KAT_VECTORS_CALCULATE_DATA, SHA_KAT_VECTORS_CALCULATE_DATA_LEN),
		MOCK_ARG (SHA_KAT_VECTORS_CALCULATE_DATA_LEN), MOCK_ARG_NOT_NULL,
		MOCK_ARG_AT_LEAST (SHA384_HASH_LENGTH));
	status |= mock_expect_output (&engine.mock, 2, SHA_KAT_VECTORS_CALCULATE_SHA384_DIGEST,
		SHA384_HASH_LENGTH, 3);

	status |= mock_expect (&engine.mock, engine.base.start_sha384, &engine, 0);
	status |= mock_expect (&engine.mock, engine.base.update, &engine, 0,
		MOCK_ARG_PTR_CONTAINS (SHA_KAT_VECTORS_UPDATE_DATA_1, SHA_KAT_VECTORS_UPDATE_DATA_1_LEN),
		MOCK_ARG (SHA_KAT_VECTORS_UPDATE_DATA_1_LEN));
	status |= mock_expect (&engine.mock, engine.base.update, &engine, 0,
		MOCK_ARG_PTR_CONTAINS (SHA_KAT_VECTORS_UPDATE_DATA_2, SHA_KAT_VECTORS_UPDATE_DATA_2_LEN),
		MOCK_ARG (SHA_KAT_VECTORS_UPDATE_DATA_2_LEN));

	status |= mock_expect (&engine.mock, engine.base.finish, &engine, HASH_ENGINE_FINISH_FAILED,
		MOCK_ARG_NOT_NULL, MOCK_ARG_AT_LEAST (SHA384_HASH_LENGTH));

	status |= mock_expect (&engine.mock, engine.base.cancel, &engine, 0);

	CuAssertIntEquals (test, 0, status);

	status = hash_run_self_test_sha384 (&engine.base);
	CuAssertIntEquals (test, HASH_ENGINE_FINISH_FAILED, status);

	status = hash_mock_validate_and_release (&engine);
	CuAssertIntEquals (test, 0, status);
}
#endif

static void hash_test_run_self_test_sha512 (CuTest *test)
{
	HASH_TESTING_ENGINE engine;
	int status;

	TEST_START;

	status = HASH_TESTING_ENGINE_INIT (&engine);
	CuAssertIntEquals (test, 0, status);

	status = hash_run_self_test_sha512 (&engine.base);
#ifdef HASH_ENABLE_SHA512
	CuAssertIntEquals (test, 0, status);
#else
	CuAssertIntEquals (test, HASH_ENGINE_UNSUPPORTED_HASH, status);
#endif

	HASH_TESTING_ENGINE_RELEASE (&engine);
}

#ifdef HASH_ENABLE_SHA512
static void hash_test_run_self_test_sha512_mismatch_data_calculate (CuTest *test)
{
	struct hash_engine_mock engine;
	int status;

	TEST_START;

	status = hash_mock_init (&engine);
	CuAssertIntEquals (test, 0, status);

	status = mock_expect (&engine.mock, engine.base.calculate_sha512, &engine, 0,
		MOCK_ARG_PTR_CONTAINS (SHA_KAT_VECTORS_CALCULATE_DATA, SHA_KAT_VECTORS_CALCULATE_DATA_LEN),
		MOCK_ARG (SHA_KAT_VECTORS_CALCULATE_DATA_LEN), MOCK_ARG_NOT_NULL,
		MOCK_ARG_AT_LEAST (SHA512_HASH_LENGTH));
	status |= mock_expect_output (&engine.mock, 2, SHA512_TEST_HASH, SHA512_HASH_LENGTH, 3);

	CuAssertIntEquals (test, 0, status);

	status = hash_run_self_test_sha512 (&engine.base);
	CuAssertIntEquals (test, HASH_ENGINE_SHA512_SELF_TEST_FAILED, status);

	status = hash_mock_validate_and_release (&engine);
	CuAssertIntEquals (test, 0, status);
}

static void hash_test_run_self_test_sha512_mismatch_data_update (CuTest *test)
{
	struct hash_engine_mock engine;
	int status;

	TEST_START;

	status = hash_mock_init (&engine);
	CuAssertIntEquals (test, 0, status);

	status = mock_expect (&engine.mock, engine.base.calculate_sha512, &engine, 0,
		MOCK_ARG_PTR_CONTAINS (SHA_KAT_VECTORS_CALCULATE_DATA, SHA_KAT_VECTORS_CALCULATE_DATA_LEN),
		MOCK_ARG (SHA_KAT_VECTORS_CALCULATE_DATA_LEN), MOCK_ARG_NOT_NULL,
		MOCK_ARG_AT_LEAST (SHA512_HASH_LENGTH));
	status |= mock_expect_output (&engine.mock, 2, SHA_KAT_VECTORS_CALCULATE_SHA512_DIGEST,
		SHA512_HASH_LENGTH, 3);

	status |= mock_expect (&engine.mock, engine.base.start_sha512, &engine, 0);
	status |= mock_expect (&engine.mock, engine.base.update, &engine, 0,
		MOCK_ARG_PTR_CONTAINS (SHA_KAT_VECTORS_UPDATE_DATA_1, SHA_KAT_VECTORS_UPDATE_DATA_1_LEN),
		MOCK_ARG (SHA_KAT_VECTORS_UPDATE_DATA_1_LEN));
	status |= mock_expect (&engine.mock, engine.base.update, &engine, 0,
		MOCK_ARG_PTR_CONTAINS (SHA_KAT_VECTORS_UPDATE_DATA_2, SHA_KAT_VECTORS_UPDATE_DATA_2_LEN),
		MOCK_ARG (SHA_KAT_VECTORS_UPDATE_DATA_2_LEN));

	status |= mock_expect (&engine.mock, engine.base.finish, &engine, 0,
		MOCK_ARG_NOT_NULL, MOCK_ARG_AT_LEAST (SHA512_HASH_LENGTH));
	status |= mock_expect_output (&engine.mock, 0, SHA512_TEST2_HASH, SHA512_HASH_LENGTH, 1);

	CuAssertIntEquals (test, 0, status);

	status = hash_run_self_test_sha512 (&engine.base);
	CuAssertIntEquals (test, HASH_ENGINE_SHA512_SELF_TEST_FAILED, status);

	status = hash_mock_validate_and_release (&engine);
	CuAssertIntEquals (test, 0, status);
}

static void hash_test_run_self_test_sha512_null (CuTest *test)
{
	HASH_TESTING_ENGINE engine;
	int status;

	TEST_START;

	status = HASH_TESTING_ENGINE_INIT (&engine);
	CuAssertIntEquals (test, 0, status);

	status = hash_run_self_test_sha512 (NULL);
	CuAssertIntEquals (test, HASH_ENGINE_INVALID_ARGUMENT, status);

	HASH_TESTING_ENGINE_RELEASE (&engine);
}

static void hash_test_run_self_test_sha512_calculate_fail (CuTest *test)
{
	struct hash_engine_mock engine;
	int status;

	TEST_START;

	status = hash_mock_init (&engine);
	CuAssertIntEquals (test, 0, status);

	status = mock_expect (&engine.mock, engine.base.calculate_sha512, &engine,
		HASH_ENGINE_SHA512_FAILED,
		MOCK_ARG_PTR_CONTAINS (SHA_KAT_VECTORS_CALCULATE_DATA, SHA_KAT_VECTORS_CALCULATE_DATA_LEN),
		MOCK_ARG (SHA_KAT_VECTORS_CALCULATE_DATA_LEN), MOCK_ARG_NOT_NULL,
		MOCK_ARG_AT_LEAST (SHA512_HASH_LENGTH));
	CuAssertIntEquals (test, 0, status);

	status = hash_run_self_test_sha512 (&engine.base);
	CuAssertIntEquals (test, HASH_ENGINE_SHA512_FAILED, status);

	status = hash_mock_validate_and_release (&engine);
	CuAssertIntEquals (test, 0, status);
}

static void hash_test_run_self_test_sha512_start_fail (CuTest *test)
{
	struct hash_engine_mock engine;
	int status;

	TEST_START;

	status = hash_mock_init (&engine);
	CuAssertIntEquals (test, 0, status);

	status = mock_expect (&engine.mock, engine.base.calculate_sha512, &engine, 0,
		MOCK_ARG_PTR_CONTAINS (SHA_KAT_VECTORS_CALCULATE_DATA, SHA_KAT_VECTORS_CALCULATE_DATA_LEN),
		MOCK_ARG (SHA_KAT_VECTORS_CALCULATE_DATA_LEN), MOCK_ARG_NOT_NULL,
		MOCK_ARG_AT_LEAST (SHA512_HASH_LENGTH));
	status |= mock_expect_output (&engine.mock, 2, SHA_KAT_VECTORS_CALCULATE_SHA512_DIGEST,
		SHA512_HASH_LENGTH, 3);

	status |= mock_expect (&engine.mock, engine.base.start_sha512, &engine,
		HASH_ENGINE_START_SHA512_FAILED);

	CuAssertIntEquals (test, 0, status);

	status = hash_run_self_test_sha512 (&engine.base);
	CuAssertIntEquals (test, HASH_ENGINE_START_SHA512_FAILED, status);

	status = hash_mock_validate_and_release (&engine);
	CuAssertIntEquals (test, 0, status);
}

static void hash_test_run_self_test_sha512_update_first_fail (CuTest *test)
{
	struct hash_engine_mock engine;
	int status;

	TEST_START;

	status = hash_mock_init (&engine);
	CuAssertIntEquals (test, 0, status);

	status = mock_expect (&engine.mock, engine.base.calculate_sha512, &engine, 0,
		MOCK_ARG_PTR_CONTAINS (SHA_KAT_VECTORS_CALCULATE_DATA, SHA_KAT_VECTORS_CALCULATE_DATA_LEN),
		MOCK_ARG (SHA_KAT_VECTORS_CALCULATE_DATA_LEN), MOCK_ARG_NOT_NULL,
		MOCK_ARG_AT_LEAST (SHA512_HASH_LENGTH));
	status |= mock_expect_output (&engine.mock, 2, SHA_KAT_VECTORS_CALCULATE_SHA512_DIGEST,
		SHA512_HASH_LENGTH, 3);

	status |= mock_expect (&engine.mock, engine.base.start_sha512, &engine, 0);
	status |= mock_expect (&engine.mock, engine.base.update, &engine, HASH_ENGINE_UPDATE_FAILED,
		MOCK_ARG_PTR_CONTAINS (SHA_KAT_VECTORS_UPDATE_DATA_1, SHA_KAT_VECTORS_UPDATE_DATA_1_LEN),
		MOCK_ARG (SHA_KAT_VECTORS_UPDATE_DATA_1_LEN));

	status |= mock_expect (&engine.mock, engine.base.cancel, &engine, 0);

	CuAssertIntEquals (test, 0, status);

	status = hash_run_self_test_sha512 (&engine.base);
	CuAssertIntEquals (test, HASH_ENGINE_UPDATE_FAILED, status);

	status = hash_mock_validate_and_release (&engine);
	CuAssertIntEquals (test, 0, status);
}

static void hash_test_run_self_test_sha512_update_second_fail (CuTest *test)
{
	struct hash_engine_mock engine;
	int status;

	TEST_START;

	status = hash_mock_init (&engine);
	CuAssertIntEquals (test, 0, status);

	status = mock_expect (&engine.mock, engine.base.calculate_sha512, &engine, 0,
		MOCK_ARG_PTR_CONTAINS (SHA_KAT_VECTORS_CALCULATE_DATA, SHA_KAT_VECTORS_CALCULATE_DATA_LEN),
		MOCK_ARG (SHA_KAT_VECTORS_CALCULATE_DATA_LEN), MOCK_ARG_NOT_NULL,
		MOCK_ARG_AT_LEAST (SHA512_HASH_LENGTH));
	status |= mock_expect_output (&engine.mock, 2, SHA_KAT_VECTORS_CALCULATE_SHA512_DIGEST,
		SHA512_HASH_LENGTH, 3);

	status |= mock_expect (&engine.mock, engine.base.start_sha512, &engine, 0);
	status |= mock_expect (&engine.mock, engine.base.update, &engine, 0,
		MOCK_ARG_PTR_CONTAINS (SHA_KAT_VECTORS_UPDATE_DATA_1, SHA_KAT_VECTORS_UPDATE_DATA_1_LEN),
		MOCK_ARG (SHA_KAT_VECTORS_UPDATE_DATA_1_LEN));
	status |= mock_expect (&engine.mock, engine.base.update, &engine, HASH_ENGINE_UPDATE_FAILED,
		MOCK_ARG_PTR_CONTAINS (SHA_KAT_VECTORS_UPDATE_DATA_2, SHA_KAT_VECTORS_UPDATE_DATA_2_LEN),
		MOCK_ARG (SHA_KAT_VECTORS_UPDATE_DATA_2_LEN));

	status |= mock_expect (&engine.mock, engine.base.cancel, &engine, 0);

	CuAssertIntEquals (test, 0, status);

	status = hash_run_self_test_sha512 (&engine.base);
	CuAssertIntEquals (test, HASH_ENGINE_UPDATE_FAILED, status);

	status = hash_mock_validate_and_release (&engine);
	CuAssertIntEquals (test, 0, status);
}

static void hash_test_run_self_test_sha512_finish_fail (CuTest *test)
{
	struct hash_engine_mock engine;
	int status;

	TEST_START;

	status = hash_mock_init (&engine);
	CuAssertIntEquals (test, 0, status);

	status = mock_expect (&engine.mock, engine.base.calculate_sha512, &engine, 0,
		MOCK_ARG_PTR_CONTAINS (SHA_KAT_VECTORS_CALCULATE_DATA, SHA_KAT_VECTORS_CALCULATE_DATA_LEN),
		MOCK_ARG (SHA_KAT_VECTORS_CALCULATE_DATA_LEN), MOCK_ARG_NOT_NULL,
		MOCK_ARG_AT_LEAST (SHA512_HASH_LENGTH));
	status |= mock_expect_output (&engine.mock, 2, SHA_KAT_VECTORS_CALCULATE_SHA512_DIGEST,
		SHA512_HASH_LENGTH, 3);

	status |= mock_expect (&engine.mock, engine.base.start_sha512, &engine, 0);
	status |= mock_expect (&engine.mock, engine.base.update, &engine, 0,
		MOCK_ARG_PTR_CONTAINS (SHA_KAT_VECTORS_UPDATE_DATA_1, SHA_KAT_VECTORS_UPDATE_DATA_1_LEN),
		MOCK_ARG (SHA_KAT_VECTORS_UPDATE_DATA_1_LEN));
	status |= mock_expect (&engine.mock, engine.base.update, &engine, 0,
		MOCK_ARG_PTR_CONTAINS (SHA_KAT_VECTORS_UPDATE_DATA_2, SHA_KAT_VECTORS_UPDATE_DATA_2_LEN),
		MOCK_ARG (SHA_KAT_VECTORS_UPDATE_DATA_2_LEN));

	status |= mock_expect (&engine.mock, engine.base.finish, &engine, HASH_ENGINE_FINISH_FAILED,
		MOCK_ARG_NOT_NULL, MOCK_ARG_AT_LEAST (SHA512_HASH_LENGTH));

	status |= mock_expect (&engine.mock, engine.base.cancel, &engine, 0);

	CuAssertIntEquals (test, 0, status);

	status = hash_run_self_test_sha512 (&engine.base);
	CuAssertIntEquals (test, HASH_ENGINE_FINISH_FAILED, status);

	status = hash_mock_validate_and_release (&engine);
	CuAssertIntEquals (test, 0, status);
}
#endif

static void hash_test_run_all_self_tests (CuTest *test)
{
	HASH_TESTING_ENGINE engine;
	int status;

	TEST_START;

	status = HASH_TESTING_ENGINE_INIT (&engine);
	CuAssertIntEquals (test, 0, status);

	status = hash_run_all_self_tests (&engine.base);
	CuAssertIntEquals (test, 0, status);

	HASH_TESTING_ENGINE_RELEASE (&engine);
}

static void hash_test_run_all_self_tests_mock (CuTest *test)
{
	struct hash_engine_mock engine;
	int status;

	TEST_START;

	status = hash_mock_init (&engine);
	CuAssertIntEquals (test, 0, status);

#ifdef HASH_ENABLE_SHA1
	status = mock_expect (&engine.mock, engine.base.calculate_sha1, &engine, 0,
		MOCK_ARG_PTR_CONTAINS (SHA_KAT_VECTORS_CALCULATE_DATA, SHA_KAT_VECTORS_CALCULATE_DATA_LEN),
		MOCK_ARG (SHA_KAT_VECTORS_CALCULATE_DATA_LEN), MOCK_ARG_NOT_NULL,
		MOCK_ARG_AT_LEAST (SHA1_HASH_LENGTH));
	status |= mock_expect_output (&engine.mock, 2, SHA_KAT_VECTORS_CALCULATE_SHA1_DIGEST,
		SHA1_HASH_LENGTH, 3);

	status |= mock_expect (&engine.mock, engine.base.start_sha1, &engine, 0);
	status |= mock_expect (&engine.mock, engine.base.update, &engine, 0,
		MOCK_ARG_PTR_CONTAINS (SHA_KAT_VECTORS_UPDATE_DATA_1, SHA_KAT_VECTORS_UPDATE_DATA_1_LEN),
		MOCK_ARG (SHA_KAT_VECTORS_UPDATE_DATA_1_LEN));
	status |= mock_expect (&engine.mock, engine.base.update, &engine, 0,
		MOCK_ARG_PTR_CONTAINS (SHA_KAT_VECTORS_UPDATE_DATA_2, SHA_KAT_VECTORS_UPDATE_DATA_2_LEN),
		MOCK_ARG (SHA_KAT_VECTORS_UPDATE_DATA_2_LEN));

	status |= mock_expect (&engine.mock, engine.base.finish, &engine, 0,
		MOCK_ARG_NOT_NULL, MOCK_ARG_AT_LEAST (SHA1_HASH_LENGTH));
	status |= mock_expect_output (&engine.mock, 0, SHA_KAT_VECTORS_UPDATE_SHA1_DIGEST,
		SHA1_HASH_LENGTH, 1);
#endif

	status |= mock_expect (&engine.mock, engine.base.calculate_sha256, &engine, 0,
		MOCK_ARG_PTR_CONTAINS (SHA_KAT_VECTORS_CALCULATE_DATA, SHA_KAT_VECTORS_CALCULATE_DATA_LEN),
		MOCK_ARG (SHA_KAT_VECTORS_CALCULATE_DATA_LEN), MOCK_ARG_NOT_NULL,
		MOCK_ARG_AT_LEAST (SHA256_HASH_LENGTH));
	status |= mock_expect_output (&engine.mock, 2, SHA_KAT_VECTORS_CALCULATE_SHA256_DIGEST,
		SHA256_HASH_LENGTH, 3);

	status |= mock_expect (&engine.mock, engine.base.start_sha256, &engine, 0);
	status |= mock_expect (&engine.mock, engine.base.update, &engine, 0,
		MOCK_ARG_PTR_CONTAINS (SHA_KAT_VECTORS_UPDATE_DATA_1, SHA_KAT_VECTORS_UPDATE_DATA_1_LEN),
		MOCK_ARG (SHA_KAT_VECTORS_UPDATE_DATA_1_LEN));
	status |= mock_expect (&engine.mock, engine.base.update, &engine, 0,
		MOCK_ARG_PTR_CONTAINS (SHA_KAT_VECTORS_UPDATE_DATA_2, SHA_KAT_VECTORS_UPDATE_DATA_2_LEN),
		MOCK_ARG (SHA_KAT_VECTORS_UPDATE_DATA_2_LEN));

	status |= mock_expect (&engine.mock, engine.base.finish, &engine, 0,
		MOCK_ARG_NOT_NULL, MOCK_ARG_AT_LEAST (SHA256_HASH_LENGTH));
	status |= mock_expect_output (&engine.mock, 0, SHA_KAT_VECTORS_UPDATE_SHA256_DIGEST,
		SHA256_HASH_LENGTH, 1);

#ifdef HASH_ENABLE_SHA384
	status = mock_expect (&engine.mock, engine.base.calculate_sha384, &engine, 0,
		MOCK_ARG_PTR_CONTAINS (SHA_KAT_VECTORS_CALCULATE_DATA, SHA_KAT_VECTORS_CALCULATE_DATA_LEN),
		MOCK_ARG (SHA_KAT_VECTORS_CALCULATE_DATA_LEN), MOCK_ARG_NOT_NULL,
		MOCK_ARG_AT_LEAST (SHA1_HASH_LENGTH));
	status |= mock_expect_output (&engine.mock, 2, SHA_KAT_VECTORS_CALCULATE_SHA384_DIGEST,
		SHA384_HASH_LENGTH, 3);

	status |= mock_expect (&engine.mock, engine.base.start_sha384, &engine, 0);
	status |= mock_expect (&engine.mock, engine.base.update, &engine, 0,
		MOCK_ARG_PTR_CONTAINS (SHA_KAT_VECTORS_UPDATE_DATA_1, SHA_KAT_VECTORS_UPDATE_DATA_1_LEN),
		MOCK_ARG (SHA_KAT_VECTORS_UPDATE_DATA_1_LEN));
	status |= mock_expect (&engine.mock, engine.base.update, &engine, 0,
		MOCK_ARG_PTR_CONTAINS (SHA_KAT_VECTORS_UPDATE_DATA_2, SHA_KAT_VECTORS_UPDATE_DATA_2_LEN),
		MOCK_ARG (SHA_KAT_VECTORS_UPDATE_DATA_2_LEN));

	status |= mock_expect (&engine.mock, engine.base.finish, &engine, 0,
		MOCK_ARG_NOT_NULL, MOCK_ARG_AT_LEAST (SHA384_HASH_LENGTH));
	status |= mock_expect_output (&engine.mock, 0, SHA_KAT_VECTORS_UPDATE_SHA384_DIGEST,
		SHA384_HASH_LENGTH, 1);
#endif

#ifdef HASH_ENABLE_SHA512
	status |= mock_expect (&engine.mock, engine.base.calculate_sha512, &engine, 0,
		MOCK_ARG_PTR_CONTAINS (SHA_KAT_VECTORS_CALCULATE_DATA, SHA_KAT_VECTORS_CALCULATE_DATA_LEN),
		MOCK_ARG (SHA_KAT_VECTORS_CALCULATE_DATA_LEN), MOCK_ARG_NOT_NULL,
		MOCK_ARG_AT_LEAST (SHA512_HASH_LENGTH));
	status |= mock_expect_output (&engine.mock, 2, SHA_KAT_VECTORS_CALCULATE_SHA512_DIGEST,
		SHA512_HASH_LENGTH, 3);

	status |= mock_expect (&engine.mock, engine.base.start_sha512, &engine, 0);
	status |= mock_expect (&engine.mock, engine.base.update, &engine, 0,
		MOCK_ARG_PTR_CONTAINS (SHA_KAT_VECTORS_UPDATE_DATA_1, SHA_KAT_VECTORS_UPDATE_DATA_1_LEN),
		MOCK_ARG (SHA_KAT_VECTORS_UPDATE_DATA_1_LEN));
	status |= mock_expect (&engine.mock, engine.base.update, &engine, 0,
		MOCK_ARG_PTR_CONTAINS (SHA_KAT_VECTORS_UPDATE_DATA_2, SHA_KAT_VECTORS_UPDATE_DATA_2_LEN),
		MOCK_ARG (SHA_KAT_VECTORS_UPDATE_DATA_2_LEN));

	status |= mock_expect (&engine.mock, engine.base.finish, &engine, 0,
		MOCK_ARG_NOT_NULL, MOCK_ARG_AT_LEAST (SHA512_HASH_LENGTH));
	status |= mock_expect_output (&engine.mock, 0, SHA_KAT_VECTORS_UPDATE_SHA512_DIGEST,
		SHA512_HASH_LENGTH, 1);
#endif

	CuAssertIntEquals (test, 0, status);

	status = hash_run_all_self_tests (&engine.base);
	CuAssertIntEquals (test, 0, status);

	status = hash_mock_validate_and_release (&engine);
	CuAssertIntEquals (test, 0, status);
}

static void hash_test_run_all_self_tests_null (CuTest *test)
{
	HASH_TESTING_ENGINE engine;
	int status;

	TEST_START;

	status = HASH_TESTING_ENGINE_INIT (&engine);
	CuAssertIntEquals (test, 0, status);

	status = hash_run_all_self_tests (NULL);
	CuAssertIntEquals (test, HASH_ENGINE_INVALID_ARGUMENT, status);

	HASH_TESTING_ENGINE_RELEASE (&engine);
}

#ifdef HASH_ENABLE_SHA1
static void hash_test_run_all_self_tests_sha1_fail (CuTest *test)
{
	struct hash_engine_mock engine;
	int status;

	TEST_START;

	status = hash_mock_init (&engine);
	CuAssertIntEquals (test, 0, status);

	status = mock_expect (&engine.mock, engine.base.calculate_sha1, &engine,
		HASH_ENGINE_SHA1_FAILED,
		MOCK_ARG_PTR_CONTAINS (SHA_KAT_VECTORS_CALCULATE_DATA, SHA_KAT_VECTORS_CALCULATE_DATA_LEN),
		MOCK_ARG (SHA_KAT_VECTORS_CALCULATE_DATA_LEN), MOCK_ARG_NOT_NULL,
		MOCK_ARG_AT_LEAST (SHA1_HASH_LENGTH));
	CuAssertIntEquals (test, 0, status);

	status = hash_run_all_self_tests (&engine.base);
	CuAssertIntEquals (test, HASH_ENGINE_SHA1_FAILED, status);

	status = hash_mock_validate_and_release (&engine);
	CuAssertIntEquals (test, 0, status);
}
#endif

static void hash_test_run_all_self_tests_sha256_fail (CuTest *test)
{
	struct hash_engine_mock engine;
	int status;

	TEST_START;

	status = hash_mock_init (&engine);
	CuAssertIntEquals (test, 0, status);

#ifdef HASH_ENABLE_SHA1
	status = mock_expect (&engine.mock, engine.base.calculate_sha1, &engine, 0,
		MOCK_ARG_PTR_CONTAINS (SHA_KAT_VECTORS_CALCULATE_DATA, SHA_KAT_VECTORS_CALCULATE_DATA_LEN),
		MOCK_ARG (SHA_KAT_VECTORS_CALCULATE_DATA_LEN), MOCK_ARG_NOT_NULL,
		MOCK_ARG_AT_LEAST (SHA1_HASH_LENGTH));
	status |= mock_expect_output (&engine.mock, 2, SHA_KAT_VECTORS_CALCULATE_SHA1_DIGEST,
		SHA1_HASH_LENGTH, 3);

	status |= mock_expect (&engine.mock, engine.base.start_sha1, &engine, 0);
	status |= mock_expect (&engine.mock, engine.base.update, &engine, 0,
		MOCK_ARG_PTR_CONTAINS (SHA_KAT_VECTORS_UPDATE_DATA_1, SHA_KAT_VECTORS_UPDATE_DATA_1_LEN),
		MOCK_ARG (SHA_KAT_VECTORS_UPDATE_DATA_1_LEN));
	status |= mock_expect (&engine.mock, engine.base.update, &engine, 0,
		MOCK_ARG_PTR_CONTAINS (SHA_KAT_VECTORS_UPDATE_DATA_2, SHA_KAT_VECTORS_UPDATE_DATA_2_LEN),
		MOCK_ARG (SHA_KAT_VECTORS_UPDATE_DATA_2_LEN));

	status |= mock_expect (&engine.mock, engine.base.finish, &engine, 0,
		MOCK_ARG_NOT_NULL, MOCK_ARG_AT_LEAST (SHA1_HASH_LENGTH));
	status |= mock_expect_output (&engine.mock, 0, SHA_KAT_VECTORS_UPDATE_SHA1_DIGEST,
		SHA1_HASH_LENGTH, 1);
#endif

	status |= mock_expect (&engine.mock, engine.base.calculate_sha256, &engine,
		HASH_ENGINE_SHA256_FAILED,
		MOCK_ARG_PTR_CONTAINS (SHA_KAT_VECTORS_CALCULATE_DATA, SHA_KAT_VECTORS_CALCULATE_DATA_LEN),
		MOCK_ARG (SHA_KAT_VECTORS_CALCULATE_DATA_LEN), MOCK_ARG_NOT_NULL,
		MOCK_ARG_AT_LEAST (SHA256_HASH_LENGTH));

	CuAssertIntEquals (test, 0, status);

	status = hash_run_all_self_tests (&engine.base);
	CuAssertIntEquals (test, HASH_ENGINE_SHA256_FAILED, status);

	status = hash_mock_validate_and_release (&engine);
	CuAssertIntEquals (test, 0, status);
}

#ifdef HASH_ENABLE_SHA384
static void hash_test_run_all_self_tests_sha384_fail (CuTest *test)
{
	struct hash_engine_mock engine;
	int status;

	TEST_START;

	status = hash_mock_init (&engine);
	CuAssertIntEquals (test, 0, status);

#ifdef HASH_ENABLE_SHA1
	status = mock_expect (&engine.mock, engine.base.calculate_sha1, &engine, 0,
		MOCK_ARG_PTR_CONTAINS (SHA_KAT_VECTORS_CALCULATE_DATA, SHA_KAT_VECTORS_CALCULATE_DATA_LEN),
		MOCK_ARG (SHA_KAT_VECTORS_CALCULATE_DATA_LEN), MOCK_ARG_NOT_NULL,
		MOCK_ARG_AT_LEAST (SHA1_HASH_LENGTH));
	status |= mock_expect_output (&engine.mock, 2, SHA_KAT_VECTORS_CALCULATE_SHA1_DIGEST,
		SHA1_HASH_LENGTH, 3);

	status |= mock_expect (&engine.mock, engine.base.start_sha1, &engine, 0);
	status |= mock_expect (&engine.mock, engine.base.update, &engine, 0,
		MOCK_ARG_PTR_CONTAINS (SHA_KAT_VECTORS_UPDATE_DATA_1, SHA_KAT_VECTORS_UPDATE_DATA_1_LEN),
		MOCK_ARG (SHA_KAT_VECTORS_UPDATE_DATA_1_LEN));
	status |= mock_expect (&engine.mock, engine.base.update, &engine, 0,
		MOCK_ARG_PTR_CONTAINS (SHA_KAT_VECTORS_UPDATE_DATA_2, SHA_KAT_VECTORS_UPDATE_DATA_2_LEN),
		MOCK_ARG (SHA_KAT_VECTORS_UPDATE_DATA_2_LEN));

	status |= mock_expect (&engine.mock, engine.base.finish, &engine, 0,
		MOCK_ARG_NOT_NULL, MOCK_ARG_AT_LEAST (SHA1_HASH_LENGTH));
	status |= mock_expect_output (&engine.mock, 0, SHA_KAT_VECTORS_UPDATE_SHA1_DIGEST,
		SHA1_HASH_LENGTH, 1);
#endif

	status |= mock_expect (&engine.mock, engine.base.calculate_sha256, &engine, 0,
		MOCK_ARG_PTR_CONTAINS (SHA_KAT_VECTORS_CALCULATE_DATA, SHA_KAT_VECTORS_CALCULATE_DATA_LEN),
		MOCK_ARG (SHA_KAT_VECTORS_CALCULATE_DATA_LEN), MOCK_ARG_NOT_NULL,
		MOCK_ARG_AT_LEAST (SHA256_HASH_LENGTH));
	status |= mock_expect_output (&engine.mock, 2, SHA_KAT_VECTORS_CALCULATE_SHA256_DIGEST,
		SHA256_HASH_LENGTH, 3);

	status |= mock_expect (&engine.mock, engine.base.start_sha256, &engine, 0);
	status |= mock_expect (&engine.mock, engine.base.update, &engine, 0,
		MOCK_ARG_PTR_CONTAINS (SHA_KAT_VECTORS_UPDATE_DATA_1, SHA_KAT_VECTORS_UPDATE_DATA_1_LEN),
		MOCK_ARG (SHA_KAT_VECTORS_UPDATE_DATA_1_LEN));
	status |= mock_expect (&engine.mock, engine.base.update, &engine, 0,
		MOCK_ARG_PTR_CONTAINS (SHA_KAT_VECTORS_UPDATE_DATA_2, SHA_KAT_VECTORS_UPDATE_DATA_2_LEN),
		MOCK_ARG (SHA_KAT_VECTORS_UPDATE_DATA_2_LEN));

	status |= mock_expect (&engine.mock, engine.base.finish, &engine, 0,
		MOCK_ARG_NOT_NULL, MOCK_ARG_AT_LEAST (SHA256_HASH_LENGTH));
	status |= mock_expect_output (&engine.mock, 0, SHA_KAT_VECTORS_UPDATE_SHA256_DIGEST,
		SHA256_HASH_LENGTH, 1);

	status |= mock_expect (&engine.mock, engine.base.calculate_sha384, &engine,
		HASH_ENGINE_SHA384_FAILED,
		MOCK_ARG_PTR_CONTAINS (SHA_KAT_VECTORS_CALCULATE_DATA, SHA_KAT_VECTORS_CALCULATE_DATA_LEN),
		MOCK_ARG (SHA_KAT_VECTORS_CALCULATE_DATA_LEN), MOCK_ARG_NOT_NULL,
		MOCK_ARG_AT_LEAST (SHA384_HASH_LENGTH));

	CuAssertIntEquals (test, 0, status);

	status = hash_run_all_self_tests (&engine.base);
	CuAssertIntEquals (test, HASH_ENGINE_SHA384_FAILED, status);

	status = hash_mock_validate_and_release (&engine);
	CuAssertIntEquals (test, 0, status);
}
#endif

#ifdef HASH_ENABLE_SHA512
static void hash_test_run_all_self_tests_sha512_fail (CuTest *test)
{
	struct hash_engine_mock engine;
	int status;

	TEST_START;

	status = hash_mock_init (&engine);
	CuAssertIntEquals (test, 0, status);

#ifdef HASH_ENABLE_SHA1
	status = mock_expect (&engine.mock, engine.base.calculate_sha1, &engine, 0,
		MOCK_ARG_PTR_CONTAINS (SHA_KAT_VECTORS_CALCULATE_DATA, SHA_KAT_VECTORS_CALCULATE_DATA_LEN),
		MOCK_ARG (SHA_KAT_VECTORS_CALCULATE_DATA_LEN), MOCK_ARG_NOT_NULL,
		MOCK_ARG_AT_LEAST (SHA1_HASH_LENGTH));
	status |= mock_expect_output (&engine.mock, 2, SHA_KAT_VECTORS_CALCULATE_SHA1_DIGEST,
		SHA1_HASH_LENGTH, 3);

	status |= mock_expect (&engine.mock, engine.base.start_sha1, &engine, 0);
	status |= mock_expect (&engine.mock, engine.base.update, &engine, 0,
		MOCK_ARG_PTR_CONTAINS (SHA_KAT_VECTORS_UPDATE_DATA_1, SHA_KAT_VECTORS_UPDATE_DATA_1_LEN),
		MOCK_ARG (SHA_KAT_VECTORS_UPDATE_DATA_1_LEN));
	status |= mock_expect (&engine.mock, engine.base.update, &engine, 0,
		MOCK_ARG_PTR_CONTAINS (SHA_KAT_VECTORS_UPDATE_DATA_2, SHA_KAT_VECTORS_UPDATE_DATA_2_LEN),
		MOCK_ARG (SHA_KAT_VECTORS_UPDATE_DATA_2_LEN));

	status |= mock_expect (&engine.mock, engine.base.finish, &engine, 0,
		MOCK_ARG_NOT_NULL, MOCK_ARG_AT_LEAST (SHA1_HASH_LENGTH));
	status |= mock_expect_output (&engine.mock, 0, SHA_KAT_VECTORS_UPDATE_SHA1_DIGEST,
		SHA1_HASH_LENGTH, 1);
#endif

	status |= mock_expect (&engine.mock, engine.base.calculate_sha256, &engine, 0,
		MOCK_ARG_PTR_CONTAINS (SHA_KAT_VECTORS_CALCULATE_DATA, SHA_KAT_VECTORS_CALCULATE_DATA_LEN),
		MOCK_ARG (SHA_KAT_VECTORS_CALCULATE_DATA_LEN), MOCK_ARG_NOT_NULL,
		MOCK_ARG_AT_LEAST (SHA256_HASH_LENGTH));
	status |= mock_expect_output (&engine.mock, 2, SHA_KAT_VECTORS_CALCULATE_SHA256_DIGEST,
		SHA256_HASH_LENGTH, 3);

	status |= mock_expect (&engine.mock, engine.base.start_sha256, &engine, 0);
	status |= mock_expect (&engine.mock, engine.base.update, &engine, 0,
		MOCK_ARG_PTR_CONTAINS (SHA_KAT_VECTORS_UPDATE_DATA_1, SHA_KAT_VECTORS_UPDATE_DATA_1_LEN),
		MOCK_ARG (SHA_KAT_VECTORS_UPDATE_DATA_1_LEN));
	status |= mock_expect (&engine.mock, engine.base.update, &engine, 0,
		MOCK_ARG_PTR_CONTAINS (SHA_KAT_VECTORS_UPDATE_DATA_2, SHA_KAT_VECTORS_UPDATE_DATA_2_LEN),
		MOCK_ARG (SHA_KAT_VECTORS_UPDATE_DATA_2_LEN));

	status |= mock_expect (&engine.mock, engine.base.finish, &engine, 0,
		MOCK_ARG_NOT_NULL, MOCK_ARG_AT_LEAST (SHA256_HASH_LENGTH));
	status |= mock_expect_output (&engine.mock, 0, SHA_KAT_VECTORS_UPDATE_SHA256_DIGEST,
		SHA256_HASH_LENGTH, 1);

#ifdef HASH_ENABLE_SHA384
	status = mock_expect (&engine.mock, engine.base.calculate_sha384, &engine, 0,
		MOCK_ARG_PTR_CONTAINS (SHA_KAT_VECTORS_CALCULATE_DATA, SHA_KAT_VECTORS_CALCULATE_DATA_LEN),
		MOCK_ARG (SHA_KAT_VECTORS_CALCULATE_DATA_LEN), MOCK_ARG_NOT_NULL,
		MOCK_ARG_AT_LEAST (SHA1_HASH_LENGTH));
	status |= mock_expect_output (&engine.mock, 2, SHA_KAT_VECTORS_CALCULATE_SHA384_DIGEST,
		SHA384_HASH_LENGTH, 3);

	status |= mock_expect (&engine.mock, engine.base.start_sha384, &engine, 0);
	status |= mock_expect (&engine.mock, engine.base.update, &engine, 0,
		MOCK_ARG_PTR_CONTAINS (SHA_KAT_VECTORS_UPDATE_DATA_1, SHA_KAT_VECTORS_UPDATE_DATA_1_LEN),
		MOCK_ARG (SHA_KAT_VECTORS_UPDATE_DATA_1_LEN));
	status |= mock_expect (&engine.mock, engine.base.update, &engine, 0,
		MOCK_ARG_PTR_CONTAINS (SHA_KAT_VECTORS_UPDATE_DATA_2, SHA_KAT_VECTORS_UPDATE_DATA_2_LEN),
		MOCK_ARG (SHA_KAT_VECTORS_UPDATE_DATA_2_LEN));

	status |= mock_expect (&engine.mock, engine.base.finish, &engine, 0,
		MOCK_ARG_NOT_NULL, MOCK_ARG_AT_LEAST (SHA384_HASH_LENGTH));
	status |= mock_expect_output (&engine.mock, 0, SHA_KAT_VECTORS_UPDATE_SHA384_DIGEST,
		SHA384_HASH_LENGTH, 1);
#endif

	status |= mock_expect (&engine.mock, engine.base.calculate_sha512, &engine,
		HASH_ENGINE_SHA512_FAILED,
		MOCK_ARG_PTR_CONTAINS (SHA_KAT_VECTORS_CALCULATE_DATA, SHA_KAT_VECTORS_CALCULATE_DATA_LEN),
		MOCK_ARG (SHA_KAT_VECTORS_CALCULATE_DATA_LEN), MOCK_ARG_NOT_NULL,
		MOCK_ARG_AT_LEAST (SHA512_HASH_LENGTH));

	CuAssertIntEquals (test, 0, status);

	status = hash_run_all_self_tests (&engine.base);
	CuAssertIntEquals (test, HASH_ENGINE_SHA512_FAILED, status);

	status = hash_mock_validate_and_release (&engine);
	CuAssertIntEquals (test, 0, status);
}
#endif

static void hash_test_hmac_run_self_test_sha1 (CuTest *test)
{
	HASH_TESTING_ENGINE engine;
	int status;

	TEST_START;

	status = HASH_TESTING_ENGINE_INIT (&engine);
	CuAssertIntEquals (test, 0, status);

	status = hash_hmac_run_self_test_sha1 (&engine.base);
#ifdef HASH_ENABLE_SHA1
	CuAssertIntEquals (test, 0, status);
#else
	CuAssertIntEquals (test, HASH_ENGINE_UNSUPPORTED_HASH, status);
#endif

	HASH_TESTING_ENGINE_RELEASE (&engine);
}

#ifdef HASH_ENABLE_SHA1
static void hash_test_hmac_run_self_test_sha1_mismatch_data_calculate (CuTest *test)
{
	struct hash_engine_mock engine;
	int status;

	TEST_START;

	status = hash_mock_init (&engine);
	CuAssertIntEquals (test, 0, status);

	status = hash_mock_expect_hmac_large_key (&engine, HMAC_KAT_VECTORS_CALCULATE_KEY,
		HMAC_KAT_VECTORS_CALCULATE_KEY_LEN, SHA1_HMAC_KAT_CALCULATE_KEY_HASH,
		HMAC_KAT_VECTORS_CALCULATE_DATA, HMAC_KAT_VECTORS_CALCULATE_DATA_LEN, NULL, 0,
		HASH_TYPE_SHA1, SHA1_TEST_HMAC, SHA1_HASH_LENGTH);
	CuAssertIntEquals (test, 0, status);

	status = hash_hmac_run_self_test_sha1 (&engine.base);
	CuAssertIntEquals (test, HASH_ENGINE_HMAC_SHA1_SELF_TEST_FAILED, status);

	status = hash_mock_validate_and_release (&engine);
	CuAssertIntEquals (test, 0, status);
}

static void hash_test_hmac_run_self_test_sha1_mismatch_data_update (CuTest *test)
{
	struct hash_engine_mock engine;
	int status;

	TEST_START;

	status = hash_mock_init (&engine);
	CuAssertIntEquals (test, 0, status);

	status = hash_mock_expect_hmac_large_key (&engine, HMAC_KAT_VECTORS_CALCULATE_KEY,
		HMAC_KAT_VECTORS_CALCULATE_KEY_LEN, SHA1_HMAC_KAT_CALCULATE_KEY_HASH,
		HMAC_KAT_VECTORS_CALCULATE_DATA, HMAC_KAT_VECTORS_CALCULATE_DATA_LEN, NULL, 0,
		HASH_TYPE_SHA1, HMAC_KAT_VECTORS_CALCULATE_SHA1_MAC, SHA1_HASH_LENGTH);

	status |= hash_mock_expect_hmac_init (&engine, HMAC_KAT_VECTORS_UPDATE_KEY,
		HMAC_KAT_VECTORS_UPDATE_KEY_LEN, HASH_TYPE_SHA1);

	status |= mock_expect (&engine.mock, engine.base.update, &engine, 0,
		MOCK_ARG_PTR_CONTAINS (HMAC_KAT_VECTORS_UPDATE_DATA_1, HMAC_KAT_VECTORS_UPDATE_DATA_1_LEN),
		MOCK_ARG (HMAC_KAT_VECTORS_UPDATE_DATA_1_LEN));
	status |= mock_expect (&engine.mock, engine.base.update, &engine, 0,
		MOCK_ARG_PTR_CONTAINS (HMAC_KAT_VECTORS_UPDATE_DATA_2, HMAC_KAT_VECTORS_UPDATE_DATA_2_LEN),
		MOCK_ARG (HMAC_KAT_VECTORS_UPDATE_DATA_2_LEN));

	status |= hash_mock_expect_hmac_finish (&engine, HMAC_KAT_VECTORS_UPDATE_KEY,
		HMAC_KAT_VECTORS_UPDATE_KEY_LEN, NULL, 0, HASH_TYPE_SHA1, SHA1_FULL_BLOCK_1024_HMAC,
		SHA1_HASH_LENGTH);

	CuAssertIntEquals (test, 0, status);

	status = hash_hmac_run_self_test_sha1 (&engine.base);
	CuAssertIntEquals (test, HASH_ENGINE_HMAC_SHA1_SELF_TEST_FAILED, status);

	status = hash_mock_validate_and_release (&engine);
	CuAssertIntEquals (test, 0, status);
}

static void hash_test_hmac_run_self_test_sha1_null (CuTest *test)
{
	HASH_TESTING_ENGINE engine;
	int status;

	TEST_START;

	status = HASH_TESTING_ENGINE_INIT (&engine);
	CuAssertIntEquals (test, 0, status);

	status = hash_hmac_run_self_test_sha1 (NULL);
	CuAssertIntEquals (test, HASH_ENGINE_INVALID_ARGUMENT, status);

	HASH_TESTING_ENGINE_RELEASE (&engine);
}

static void hash_test_hmac_run_self_test_sha1_calculate_fail (CuTest *test)
{
	struct hash_engine_mock engine;
	int status;

	TEST_START;

	status = hash_mock_init (&engine);
	CuAssertIntEquals (test, 0, status);

	status = mock_expect (&engine.mock, engine.base.calculate_sha1, &engine,
		HASH_ENGINE_SHA1_FAILED,
		MOCK_ARG_PTR_CONTAINS (HMAC_KAT_VECTORS_CALCULATE_KEY, HMAC_KAT_VECTORS_CALCULATE_KEY_LEN),
		MOCK_ARG (HMAC_KAT_VECTORS_CALCULATE_KEY_LEN), MOCK_ARG_NOT_NULL,
		MOCK_ARG_AT_LEAST (SHA1_HASH_LENGTH));
	CuAssertIntEquals (test, 0, status);

	status = hash_hmac_run_self_test_sha1 (&engine.base);
	CuAssertIntEquals (test, HASH_ENGINE_SHA1_FAILED, status);

	status = hash_mock_validate_and_release (&engine);
	CuAssertIntEquals (test, 0, status);
}

static void hash_test_hmac_run_self_test_sha1_hmac_init_fail (CuTest *test)
{
	struct hash_engine_mock engine;
	int status;

	TEST_START;

	status = hash_mock_init (&engine);
	CuAssertIntEquals (test, 0, status);

	status = hash_mock_expect_hmac_large_key (&engine, HMAC_KAT_VECTORS_CALCULATE_KEY,
		HMAC_KAT_VECTORS_CALCULATE_KEY_LEN, SHA1_HMAC_KAT_CALCULATE_KEY_HASH,
		HMAC_KAT_VECTORS_CALCULATE_DATA, HMAC_KAT_VECTORS_CALCULATE_DATA_LEN, NULL, 0,
		HASH_TYPE_SHA1, HMAC_KAT_VECTORS_CALCULATE_SHA1_MAC, SHA1_HASH_LENGTH);

	status = mock_expect (&engine.mock, engine.base.start_sha1, &engine,
		HASH_ENGINE_START_SHA1_FAILED);

	CuAssertIntEquals (test, 0, status);

	status = hash_hmac_run_self_test_sha1 (&engine.base);
	CuAssertIntEquals (test, HASH_ENGINE_START_SHA1_FAILED, status);

	status = hash_mock_validate_and_release (&engine);
	CuAssertIntEquals (test, 0, status);
}

static void hash_test_hmac_run_self_test_sha1_update_first_fail (CuTest *test)
{
	struct hash_engine_mock engine;
	int status;

	TEST_START;

	status = hash_mock_init (&engine);
	CuAssertIntEquals (test, 0, status);

	status = hash_mock_expect_hmac_large_key (&engine, HMAC_KAT_VECTORS_CALCULATE_KEY,
		HMAC_KAT_VECTORS_CALCULATE_KEY_LEN, SHA1_HMAC_KAT_CALCULATE_KEY_HASH,
		HMAC_KAT_VECTORS_CALCULATE_DATA, HMAC_KAT_VECTORS_CALCULATE_DATA_LEN, NULL, 0,
		HASH_TYPE_SHA1, HMAC_KAT_VECTORS_CALCULATE_SHA1_MAC, SHA1_HASH_LENGTH);

	status |= hash_mock_expect_hmac_init (&engine, HMAC_KAT_VECTORS_UPDATE_KEY,
		HMAC_KAT_VECTORS_UPDATE_KEY_LEN, HASH_TYPE_SHA1);

	status |= mock_expect (&engine.mock, engine.base.update, &engine, HASH_ENGINE_UPDATE_FAILED,
		MOCK_ARG_PTR_CONTAINS (HMAC_KAT_VECTORS_UPDATE_DATA_1, HMAC_KAT_VECTORS_UPDATE_DATA_1_LEN),
		MOCK_ARG (HMAC_KAT_VECTORS_UPDATE_DATA_1_LEN));

	status |= mock_expect (&engine.mock, engine.base.cancel, &engine, 0);

	CuAssertIntEquals (test, 0, status);

	status = hash_hmac_run_self_test_sha1 (&engine.base);
	CuAssertIntEquals (test, HASH_ENGINE_UPDATE_FAILED, status);

	status = hash_mock_validate_and_release (&engine);
	CuAssertIntEquals (test, 0, status);
}

static void hash_test_hmac_run_self_test_sha1_update_second_fail (CuTest *test)
{
	struct hash_engine_mock engine;
	int status;

	TEST_START;

	status = hash_mock_init (&engine);
	CuAssertIntEquals (test, 0, status);

	status = hash_mock_expect_hmac_large_key (&engine, HMAC_KAT_VECTORS_CALCULATE_KEY,
		HMAC_KAT_VECTORS_CALCULATE_KEY_LEN, SHA1_HMAC_KAT_CALCULATE_KEY_HASH,
		HMAC_KAT_VECTORS_CALCULATE_DATA, HMAC_KAT_VECTORS_CALCULATE_DATA_LEN, NULL, 0,
		HASH_TYPE_SHA1, HMAC_KAT_VECTORS_CALCULATE_SHA1_MAC, SHA1_HASH_LENGTH);

	status |= hash_mock_expect_hmac_init (&engine, HMAC_KAT_VECTORS_UPDATE_KEY,
		HMAC_KAT_VECTORS_UPDATE_KEY_LEN, HASH_TYPE_SHA1);

	status |= mock_expect (&engine.mock, engine.base.update, &engine, 0,
		MOCK_ARG_PTR_CONTAINS (HMAC_KAT_VECTORS_UPDATE_DATA_1, HMAC_KAT_VECTORS_UPDATE_DATA_1_LEN),
		MOCK_ARG (HMAC_KAT_VECTORS_UPDATE_DATA_1_LEN));
	status |= mock_expect (&engine.mock, engine.base.update, &engine, HASH_ENGINE_UPDATE_FAILED,
		MOCK_ARG_PTR_CONTAINS (HMAC_KAT_VECTORS_UPDATE_DATA_2, HMAC_KAT_VECTORS_UPDATE_DATA_2_LEN),
		MOCK_ARG (HMAC_KAT_VECTORS_UPDATE_DATA_2_LEN));

	status |= mock_expect (&engine.mock, engine.base.cancel, &engine, 0);

	CuAssertIntEquals (test, 0, status);

	status = hash_hmac_run_self_test_sha1 (&engine.base);
	CuAssertIntEquals (test, HASH_ENGINE_UPDATE_FAILED, status);

	status = hash_mock_validate_and_release (&engine);
	CuAssertIntEquals (test, 0, status);
}

static void hash_test_hmac_run_self_test_sha1_finish_fail (CuTest *test)
{
	struct hash_engine_mock engine;
	int status;

	TEST_START;

	status = hash_mock_init (&engine);
	CuAssertIntEquals (test, 0, status);

	status = hash_mock_expect_hmac_large_key (&engine, HMAC_KAT_VECTORS_CALCULATE_KEY,
		HMAC_KAT_VECTORS_CALCULATE_KEY_LEN, SHA1_HMAC_KAT_CALCULATE_KEY_HASH,
		HMAC_KAT_VECTORS_CALCULATE_DATA, HMAC_KAT_VECTORS_CALCULATE_DATA_LEN, NULL, 0,
		HASH_TYPE_SHA1, HMAC_KAT_VECTORS_CALCULATE_SHA1_MAC, SHA1_HASH_LENGTH);

	status |= hash_mock_expect_hmac_init (&engine, HMAC_KAT_VECTORS_UPDATE_KEY,
		HMAC_KAT_VECTORS_UPDATE_KEY_LEN, HASH_TYPE_SHA1);

	status |= mock_expect (&engine.mock, engine.base.update, &engine, 0,
		MOCK_ARG_PTR_CONTAINS (HMAC_KAT_VECTORS_UPDATE_DATA_1, HMAC_KAT_VECTORS_UPDATE_DATA_1_LEN),
		MOCK_ARG (HMAC_KAT_VECTORS_UPDATE_DATA_1_LEN));
	status |= mock_expect (&engine.mock, engine.base.update, &engine, 0,
		MOCK_ARG_PTR_CONTAINS (HMAC_KAT_VECTORS_UPDATE_DATA_2, HMAC_KAT_VECTORS_UPDATE_DATA_2_LEN),
		MOCK_ARG (HMAC_KAT_VECTORS_UPDATE_DATA_2_LEN));

	status |= mock_expect (&engine.mock, engine.base.finish, &engine, HASH_ENGINE_FINISH_FAILED,
		MOCK_ARG_NOT_NULL, MOCK_ARG_AT_LEAST (SHA1_HASH_LENGTH));

	status |= mock_expect (&engine.mock, engine.base.cancel, &engine, 0);

	CuAssertIntEquals (test, 0, status);

	status = hash_hmac_run_self_test_sha1 (&engine.base);
	CuAssertIntEquals (test, HASH_ENGINE_FINISH_FAILED, status);

	status = hash_mock_validate_and_release (&engine);
	CuAssertIntEquals (test, 0, status);
}
#endif

static void hash_test_hmac_run_self_test_sha256 (CuTest *test)
{
	HASH_TESTING_ENGINE engine;
	int status;

	TEST_START;

	status = HASH_TESTING_ENGINE_INIT (&engine);
	CuAssertIntEquals (test, 0, status);

	status = hash_hmac_run_self_test_sha256 (&engine.base);
	CuAssertIntEquals (test, 0, status);

	HASH_TESTING_ENGINE_RELEASE (&engine);
}

static void hash_test_hmac_run_self_test_sha256_mismatch_data_calculate (CuTest *test)
{
	struct hash_engine_mock engine;
	int status;

	TEST_START;

	status = hash_mock_init (&engine);
	CuAssertIntEquals (test, 0, status);

	status = hash_mock_expect_hmac_large_key (&engine, HMAC_KAT_VECTORS_CALCULATE_KEY,
		HMAC_KAT_VECTORS_CALCULATE_KEY_LEN, SHA256_HMAC_KAT_CALCULATE_KEY_HASH,
		HMAC_KAT_VECTORS_CALCULATE_DATA, HMAC_KAT_VECTORS_CALCULATE_DATA_LEN, NULL, 0,
		HASH_TYPE_SHA256, SHA256_TEST_HMAC, SHA256_HASH_LENGTH);
	CuAssertIntEquals (test, 0, status);

	status = hash_hmac_run_self_test_sha256 (&engine.base);
	CuAssertIntEquals (test, HASH_ENGINE_HMAC_SHA256_SELF_TEST_FAILED, status);

	status = hash_mock_validate_and_release (&engine);
	CuAssertIntEquals (test, 0, status);
}

static void hash_test_hmac_run_self_test_sha256_mismatch_data_update (CuTest *test)
{
	struct hash_engine_mock engine;
	int status;

	TEST_START;

	status = hash_mock_init (&engine);
	CuAssertIntEquals (test, 0, status);

	status = hash_mock_expect_hmac_large_key (&engine, HMAC_KAT_VECTORS_CALCULATE_KEY,
		HMAC_KAT_VECTORS_CALCULATE_KEY_LEN, SHA256_HMAC_KAT_CALCULATE_KEY_HASH,
		HMAC_KAT_VECTORS_CALCULATE_DATA, HMAC_KAT_VECTORS_CALCULATE_DATA_LEN, NULL, 0,
		HASH_TYPE_SHA256, HMAC_KAT_VECTORS_CALCULATE_SHA256_MAC, SHA256_HASH_LENGTH);

	status |= hash_mock_expect_hmac_init (&engine, HMAC_KAT_VECTORS_UPDATE_KEY,
		HMAC_KAT_VECTORS_UPDATE_KEY_LEN, HASH_TYPE_SHA256);

	status |= mock_expect (&engine.mock, engine.base.update, &engine, 0,
		MOCK_ARG_PTR_CONTAINS (HMAC_KAT_VECTORS_UPDATE_DATA_1, HMAC_KAT_VECTORS_UPDATE_DATA_1_LEN),
		MOCK_ARG (HMAC_KAT_VECTORS_UPDATE_DATA_1_LEN));
	status |= mock_expect (&engine.mock, engine.base.update, &engine, 0,
		MOCK_ARG_PTR_CONTAINS (HMAC_KAT_VECTORS_UPDATE_DATA_2, HMAC_KAT_VECTORS_UPDATE_DATA_2_LEN),
		MOCK_ARG (HMAC_KAT_VECTORS_UPDATE_DATA_2_LEN));

	status |= hash_mock_expect_hmac_finish (&engine, HMAC_KAT_VECTORS_UPDATE_KEY,
		HMAC_KAT_VECTORS_UPDATE_KEY_LEN, NULL, 0, HASH_TYPE_SHA256, SHA256_FULL_BLOCK_1024_HMAC,
		SHA256_HASH_LENGTH);

	CuAssertIntEquals (test, 0, status);

	status = hash_hmac_run_self_test_sha256 (&engine.base);
	CuAssertIntEquals (test, HASH_ENGINE_HMAC_SHA256_SELF_TEST_FAILED, status);

	status = hash_mock_validate_and_release (&engine);
	CuAssertIntEquals (test, 0, status);
}

static void hash_test_hmac_run_self_test_sha256_null (CuTest *test)
{
	HASH_TESTING_ENGINE engine;
	int status;

	TEST_START;

	status = HASH_TESTING_ENGINE_INIT (&engine);
	CuAssertIntEquals (test, 0, status);

	status = hash_hmac_run_self_test_sha256 (NULL);
	CuAssertIntEquals (test, HASH_ENGINE_INVALID_ARGUMENT, status);

	HASH_TESTING_ENGINE_RELEASE (&engine);
}

static void hash_test_hmac_run_self_test_sha256_calculate_fail (CuTest *test)
{
	struct hash_engine_mock engine;
	int status;

	TEST_START;

	status = hash_mock_init (&engine);
	CuAssertIntEquals (test, 0, status);

	status = mock_expect (&engine.mock, engine.base.calculate_sha256, &engine,
		HASH_ENGINE_SHA256_FAILED,
		MOCK_ARG_PTR_CONTAINS (HMAC_KAT_VECTORS_CALCULATE_KEY, HMAC_KAT_VECTORS_CALCULATE_KEY_LEN),
		MOCK_ARG (HMAC_KAT_VECTORS_CALCULATE_KEY_LEN), MOCK_ARG_NOT_NULL,
		MOCK_ARG_AT_LEAST (SHA256_HASH_LENGTH));
	CuAssertIntEquals (test, 0, status);

	status = hash_hmac_run_self_test_sha256 (&engine.base);
	CuAssertIntEquals (test, HASH_ENGINE_SHA256_FAILED, status);

	status = hash_mock_validate_and_release (&engine);
	CuAssertIntEquals (test, 0, status);
}

static void hash_test_hmac_run_self_test_sha256_hmac_init_fail (CuTest *test)
{
	struct hash_engine_mock engine;
	int status;

	TEST_START;

	status = hash_mock_init (&engine);
	CuAssertIntEquals (test, 0, status);

	status = hash_mock_expect_hmac_large_key (&engine, HMAC_KAT_VECTORS_CALCULATE_KEY,
		HMAC_KAT_VECTORS_CALCULATE_KEY_LEN, SHA256_HMAC_KAT_CALCULATE_KEY_HASH,
		HMAC_KAT_VECTORS_CALCULATE_DATA, HMAC_KAT_VECTORS_CALCULATE_DATA_LEN, NULL, 0,
		HASH_TYPE_SHA256, HMAC_KAT_VECTORS_CALCULATE_SHA256_MAC, SHA256_HASH_LENGTH);

	status = mock_expect (&engine.mock, engine.base.start_sha256, &engine,
		HASH_ENGINE_START_SHA256_FAILED);

	CuAssertIntEquals (test, 0, status);

	status = hash_hmac_run_self_test_sha256 (&engine.base);
	CuAssertIntEquals (test, HASH_ENGINE_START_SHA256_FAILED, status);

	status = hash_mock_validate_and_release (&engine);
	CuAssertIntEquals (test, 0, status);
}

static void hash_test_hmac_run_self_test_sha256_update_first_fail (CuTest *test)
{
	struct hash_engine_mock engine;
	int status;

	TEST_START;

	status = hash_mock_init (&engine);
	CuAssertIntEquals (test, 0, status);

	status = hash_mock_expect_hmac_large_key (&engine, HMAC_KAT_VECTORS_CALCULATE_KEY,
		HMAC_KAT_VECTORS_CALCULATE_KEY_LEN, SHA256_HMAC_KAT_CALCULATE_KEY_HASH,
		HMAC_KAT_VECTORS_CALCULATE_DATA, HMAC_KAT_VECTORS_CALCULATE_DATA_LEN, NULL, 0,
		HASH_TYPE_SHA256, HMAC_KAT_VECTORS_CALCULATE_SHA256_MAC, SHA256_HASH_LENGTH);

	status |= hash_mock_expect_hmac_init (&engine, HMAC_KAT_VECTORS_UPDATE_KEY,
		HMAC_KAT_VECTORS_UPDATE_KEY_LEN, HASH_TYPE_SHA256);

	status |= mock_expect (&engine.mock, engine.base.update, &engine, HASH_ENGINE_UPDATE_FAILED,
		MOCK_ARG_PTR_CONTAINS (HMAC_KAT_VECTORS_UPDATE_DATA_1, HMAC_KAT_VECTORS_UPDATE_DATA_1_LEN),
		MOCK_ARG (HMAC_KAT_VECTORS_UPDATE_DATA_1_LEN));

	status |= mock_expect (&engine.mock, engine.base.cancel, &engine, 0);

	CuAssertIntEquals (test, 0, status);

	status = hash_hmac_run_self_test_sha256 (&engine.base);
	CuAssertIntEquals (test, HASH_ENGINE_UPDATE_FAILED, status);

	status = hash_mock_validate_and_release (&engine);
	CuAssertIntEquals (test, 0, status);
}

static void hash_test_hmac_run_self_test_sha256_update_second_fail (CuTest *test)
{
	struct hash_engine_mock engine;
	int status;

	TEST_START;

	status = hash_mock_init (&engine);
	CuAssertIntEquals (test, 0, status);

	status = hash_mock_expect_hmac_large_key (&engine, HMAC_KAT_VECTORS_CALCULATE_KEY,
		HMAC_KAT_VECTORS_CALCULATE_KEY_LEN, SHA256_HMAC_KAT_CALCULATE_KEY_HASH,
		HMAC_KAT_VECTORS_CALCULATE_DATA, HMAC_KAT_VECTORS_CALCULATE_DATA_LEN, NULL, 0,
		HASH_TYPE_SHA256, HMAC_KAT_VECTORS_CALCULATE_SHA256_MAC, SHA256_HASH_LENGTH);

	status |= hash_mock_expect_hmac_init (&engine, HMAC_KAT_VECTORS_UPDATE_KEY,
		HMAC_KAT_VECTORS_UPDATE_KEY_LEN, HASH_TYPE_SHA256);

	status |= mock_expect (&engine.mock, engine.base.update, &engine, 0,
		MOCK_ARG_PTR_CONTAINS (HMAC_KAT_VECTORS_UPDATE_DATA_1, HMAC_KAT_VECTORS_UPDATE_DATA_1_LEN),
		MOCK_ARG (HMAC_KAT_VECTORS_UPDATE_DATA_1_LEN));
	status |= mock_expect (&engine.mock, engine.base.update, &engine, HASH_ENGINE_UPDATE_FAILED,
		MOCK_ARG_PTR_CONTAINS (HMAC_KAT_VECTORS_UPDATE_DATA_2, HMAC_KAT_VECTORS_UPDATE_DATA_2_LEN),
		MOCK_ARG (HMAC_KAT_VECTORS_UPDATE_DATA_2_LEN));

	status |= mock_expect (&engine.mock, engine.base.cancel, &engine, 0);

	CuAssertIntEquals (test, 0, status);

	status = hash_hmac_run_self_test_sha256 (&engine.base);
	CuAssertIntEquals (test, HASH_ENGINE_UPDATE_FAILED, status);

	status = hash_mock_validate_and_release (&engine);
	CuAssertIntEquals (test, 0, status);
}

static void hash_test_hmac_run_self_test_sha256_finish_fail (CuTest *test)
{
	struct hash_engine_mock engine;
	int status;

	TEST_START;

	status = hash_mock_init (&engine);
	CuAssertIntEquals (test, 0, status);

	status = hash_mock_expect_hmac_large_key (&engine, HMAC_KAT_VECTORS_CALCULATE_KEY,
		HMAC_KAT_VECTORS_CALCULATE_KEY_LEN, SHA256_HMAC_KAT_CALCULATE_KEY_HASH,
		HMAC_KAT_VECTORS_CALCULATE_DATA, HMAC_KAT_VECTORS_CALCULATE_DATA_LEN, NULL, 0,
		HASH_TYPE_SHA256, HMAC_KAT_VECTORS_CALCULATE_SHA256_MAC, SHA256_HASH_LENGTH);

	status |= hash_mock_expect_hmac_init (&engine, HMAC_KAT_VECTORS_UPDATE_KEY,
		HMAC_KAT_VECTORS_UPDATE_KEY_LEN, HASH_TYPE_SHA256);

	status |= mock_expect (&engine.mock, engine.base.update, &engine, 0,
		MOCK_ARG_PTR_CONTAINS (HMAC_KAT_VECTORS_UPDATE_DATA_1, HMAC_KAT_VECTORS_UPDATE_DATA_1_LEN),
		MOCK_ARG (HMAC_KAT_VECTORS_UPDATE_DATA_1_LEN));
	status |= mock_expect (&engine.mock, engine.base.update, &engine, 0,
		MOCK_ARG_PTR_CONTAINS (HMAC_KAT_VECTORS_UPDATE_DATA_2, HMAC_KAT_VECTORS_UPDATE_DATA_2_LEN),
		MOCK_ARG (HMAC_KAT_VECTORS_UPDATE_DATA_2_LEN));

	status |= mock_expect (&engine.mock, engine.base.finish, &engine, HASH_ENGINE_FINISH_FAILED,
		MOCK_ARG_NOT_NULL, MOCK_ARG_AT_LEAST (SHA256_HASH_LENGTH));

	status |= mock_expect (&engine.mock, engine.base.cancel, &engine, 0);

	CuAssertIntEquals (test, 0, status);

	status = hash_hmac_run_self_test_sha256 (&engine.base);
	CuAssertIntEquals (test, HASH_ENGINE_FINISH_FAILED, status);

	status = hash_mock_validate_and_release (&engine);
	CuAssertIntEquals (test, 0, status);
}

static void hash_test_hmac_run_self_test_sha384 (CuTest *test)
{
	HASH_TESTING_ENGINE engine;
	int status;

	TEST_START;

	status = HASH_TESTING_ENGINE_INIT (&engine);
	CuAssertIntEquals (test, 0, status);

	status = hash_hmac_run_self_test_sha384 (&engine.base);
#ifdef HASH_ENABLE_SHA384
	CuAssertIntEquals (test, 0, status);
#else
	CuAssertIntEquals (test, HASH_ENGINE_UNSUPPORTED_HASH, status);
#endif

	HASH_TESTING_ENGINE_RELEASE (&engine);
}

#ifdef HASH_ENABLE_SHA384
static void hash_test_hmac_run_self_test_sha384_mismatch_data_calculate (CuTest *test)
{
	struct hash_engine_mock engine;
	int status;

	TEST_START;

	status = hash_mock_init (&engine);
	CuAssertIntEquals (test, 0, status);

	status = hash_mock_expect_hmac_large_key (&engine, HMAC_KAT_VECTORS_CALCULATE_KEY,
		HMAC_KAT_VECTORS_CALCULATE_KEY_LEN, SHA384_HMAC_KAT_CALCULATE_KEY_HASH,
		HMAC_KAT_VECTORS_CALCULATE_DATA, HMAC_KAT_VECTORS_CALCULATE_DATA_LEN, NULL, 0,
		HASH_TYPE_SHA384, SHA384_TEST_HMAC, SHA384_HASH_LENGTH);
	CuAssertIntEquals (test, 0, status);

	status = hash_hmac_run_self_test_sha384 (&engine.base);
	CuAssertIntEquals (test, HASH_ENGINE_HMAC_SHA384_SELF_TEST_FAILED, status);

	status = hash_mock_validate_and_release (&engine);
	CuAssertIntEquals (test, 0, status);
}

static void hash_test_hmac_run_self_test_sha384_mismatch_data_update (CuTest *test)
{
	struct hash_engine_mock engine;
	int status;

	TEST_START;

	status = hash_mock_init (&engine);
	CuAssertIntEquals (test, 0, status);

	status = hash_mock_expect_hmac_large_key (&engine, HMAC_KAT_VECTORS_CALCULATE_KEY,
		HMAC_KAT_VECTORS_CALCULATE_KEY_LEN, SHA384_HMAC_KAT_CALCULATE_KEY_HASH,
		HMAC_KAT_VECTORS_CALCULATE_DATA, HMAC_KAT_VECTORS_CALCULATE_DATA_LEN, NULL, 0,
		HASH_TYPE_SHA384, HMAC_KAT_VECTORS_CALCULATE_SHA384_MAC, SHA384_HASH_LENGTH);

	status |= hash_mock_expect_hmac_init (&engine, HMAC_KAT_VECTORS_UPDATE_KEY,
		HMAC_KAT_VECTORS_UPDATE_KEY_LEN, HASH_TYPE_SHA384);

	status |= mock_expect (&engine.mock, engine.base.update, &engine, 0,
		MOCK_ARG_PTR_CONTAINS (HMAC_KAT_VECTORS_UPDATE_DATA_1, HMAC_KAT_VECTORS_UPDATE_DATA_1_LEN),
		MOCK_ARG (HMAC_KAT_VECTORS_UPDATE_DATA_1_LEN));
	status |= mock_expect (&engine.mock, engine.base.update, &engine, 0,
		MOCK_ARG_PTR_CONTAINS (HMAC_KAT_VECTORS_UPDATE_DATA_2, HMAC_KAT_VECTORS_UPDATE_DATA_2_LEN),
		MOCK_ARG (HMAC_KAT_VECTORS_UPDATE_DATA_2_LEN));

	status |= hash_mock_expect_hmac_finish (&engine, HMAC_KAT_VECTORS_UPDATE_KEY,
		HMAC_KAT_VECTORS_UPDATE_KEY_LEN, NULL, 0, HASH_TYPE_SHA384, SHA384_FULL_BLOCK_1024_HMAC,
		SHA384_HASH_LENGTH);

	CuAssertIntEquals (test, 0, status);

	status = hash_hmac_run_self_test_sha384 (&engine.base);
	CuAssertIntEquals (test, HASH_ENGINE_HMAC_SHA384_SELF_TEST_FAILED, status);

	status = hash_mock_validate_and_release (&engine);
	CuAssertIntEquals (test, 0, status);
}

static void hash_test_hmac_run_self_test_sha384_null (CuTest *test)
{
	HASH_TESTING_ENGINE engine;
	int status;

	TEST_START;

	status = HASH_TESTING_ENGINE_INIT (&engine);
	CuAssertIntEquals (test, 0, status);

	status = hash_hmac_run_self_test_sha384 (NULL);
	CuAssertIntEquals (test, HASH_ENGINE_INVALID_ARGUMENT, status);

	HASH_TESTING_ENGINE_RELEASE (&engine);
}

static void hash_test_hmac_run_self_test_sha384_calculate_fail (CuTest *test)
{
	struct hash_engine_mock engine;
	int status;

	TEST_START;

	status = hash_mock_init (&engine);
	CuAssertIntEquals (test, 0, status);

	status = mock_expect (&engine.mock, engine.base.calculate_sha384, &engine,
		HASH_ENGINE_SHA384_FAILED,
		MOCK_ARG_PTR_CONTAINS (HMAC_KAT_VECTORS_CALCULATE_KEY, HMAC_KAT_VECTORS_CALCULATE_KEY_LEN),
		MOCK_ARG (HMAC_KAT_VECTORS_CALCULATE_KEY_LEN), MOCK_ARG_NOT_NULL,
		MOCK_ARG_AT_LEAST (SHA384_HASH_LENGTH));
	CuAssertIntEquals (test, 0, status);

	status = hash_hmac_run_self_test_sha384 (&engine.base);
	CuAssertIntEquals (test, HASH_ENGINE_SHA384_FAILED, status);

	status = hash_mock_validate_and_release (&engine);
	CuAssertIntEquals (test, 0, status);
}

static void hash_test_hmac_run_self_test_sha384_hmac_init_fail (CuTest *test)
{
	struct hash_engine_mock engine;
	int status;

	TEST_START;

	status = hash_mock_init (&engine);
	CuAssertIntEquals (test, 0, status);

	status = hash_mock_expect_hmac_large_key (&engine, HMAC_KAT_VECTORS_CALCULATE_KEY,
		HMAC_KAT_VECTORS_CALCULATE_KEY_LEN, SHA384_HMAC_KAT_CALCULATE_KEY_HASH,
		HMAC_KAT_VECTORS_CALCULATE_DATA, HMAC_KAT_VECTORS_CALCULATE_DATA_LEN, NULL, 0,
		HASH_TYPE_SHA384, HMAC_KAT_VECTORS_CALCULATE_SHA384_MAC, SHA384_HASH_LENGTH);

	status = mock_expect (&engine.mock, engine.base.start_sha384, &engine,
		HASH_ENGINE_START_SHA384_FAILED);

	CuAssertIntEquals (test, 0, status);

	status = hash_hmac_run_self_test_sha384 (&engine.base);
	CuAssertIntEquals (test, HASH_ENGINE_START_SHA384_FAILED, status);

	status = hash_mock_validate_and_release (&engine);
	CuAssertIntEquals (test, 0, status);
}

static void hash_test_hmac_run_self_test_sha384_update_first_fail (CuTest *test)
{
	struct hash_engine_mock engine;
	int status;

	TEST_START;

	status = hash_mock_init (&engine);
	CuAssertIntEquals (test, 0, status);

	status = hash_mock_expect_hmac_large_key (&engine, HMAC_KAT_VECTORS_CALCULATE_KEY,
		HMAC_KAT_VECTORS_CALCULATE_KEY_LEN, SHA384_HMAC_KAT_CALCULATE_KEY_HASH,
		HMAC_KAT_VECTORS_CALCULATE_DATA, HMAC_KAT_VECTORS_CALCULATE_DATA_LEN, NULL, 0,
		HASH_TYPE_SHA384, HMAC_KAT_VECTORS_CALCULATE_SHA384_MAC, SHA384_HASH_LENGTH);

	status |= hash_mock_expect_hmac_init (&engine, HMAC_KAT_VECTORS_UPDATE_KEY,
		HMAC_KAT_VECTORS_UPDATE_KEY_LEN, HASH_TYPE_SHA384);

	status |= mock_expect (&engine.mock, engine.base.update, &engine, HASH_ENGINE_UPDATE_FAILED,
		MOCK_ARG_PTR_CONTAINS (HMAC_KAT_VECTORS_UPDATE_DATA_1, HMAC_KAT_VECTORS_UPDATE_DATA_1_LEN),
		MOCK_ARG (HMAC_KAT_VECTORS_UPDATE_DATA_1_LEN));

	status |= mock_expect (&engine.mock, engine.base.cancel, &engine, 0);

	CuAssertIntEquals (test, 0, status);

	status = hash_hmac_run_self_test_sha384 (&engine.base);
	CuAssertIntEquals (test, HASH_ENGINE_UPDATE_FAILED, status);

	status = hash_mock_validate_and_release (&engine);
	CuAssertIntEquals (test, 0, status);
}

static void hash_test_hmac_run_self_test_sha384_update_second_fail (CuTest *test)
{
	struct hash_engine_mock engine;
	int status;

	TEST_START;

	status = hash_mock_init (&engine);
	CuAssertIntEquals (test, 0, status);

	status = hash_mock_expect_hmac_large_key (&engine, HMAC_KAT_VECTORS_CALCULATE_KEY,
		HMAC_KAT_VECTORS_CALCULATE_KEY_LEN, SHA384_HMAC_KAT_CALCULATE_KEY_HASH,
		HMAC_KAT_VECTORS_CALCULATE_DATA, HMAC_KAT_VECTORS_CALCULATE_DATA_LEN, NULL, 0,
		HASH_TYPE_SHA384, HMAC_KAT_VECTORS_CALCULATE_SHA384_MAC, SHA384_HASH_LENGTH);

	status |= hash_mock_expect_hmac_init (&engine, HMAC_KAT_VECTORS_UPDATE_KEY,
		HMAC_KAT_VECTORS_UPDATE_KEY_LEN, HASH_TYPE_SHA384);

	status |= mock_expect (&engine.mock, engine.base.update, &engine, 0,
		MOCK_ARG_PTR_CONTAINS (HMAC_KAT_VECTORS_UPDATE_DATA_1, HMAC_KAT_VECTORS_UPDATE_DATA_1_LEN),
		MOCK_ARG (HMAC_KAT_VECTORS_UPDATE_DATA_1_LEN));
	status |= mock_expect (&engine.mock, engine.base.update, &engine, HASH_ENGINE_UPDATE_FAILED,
		MOCK_ARG_PTR_CONTAINS (HMAC_KAT_VECTORS_UPDATE_DATA_2, HMAC_KAT_VECTORS_UPDATE_DATA_2_LEN),
		MOCK_ARG (HMAC_KAT_VECTORS_UPDATE_DATA_2_LEN));

	status |= mock_expect (&engine.mock, engine.base.cancel, &engine, 0);

	CuAssertIntEquals (test, 0, status);

	status = hash_hmac_run_self_test_sha384 (&engine.base);
	CuAssertIntEquals (test, HASH_ENGINE_UPDATE_FAILED, status);

	status = hash_mock_validate_and_release (&engine);
	CuAssertIntEquals (test, 0, status);
}

static void hash_test_hmac_run_self_test_sha384_finish_fail (CuTest *test)
{
	struct hash_engine_mock engine;
	int status;

	TEST_START;

	status = hash_mock_init (&engine);
	CuAssertIntEquals (test, 0, status);

	status = hash_mock_expect_hmac_large_key (&engine, HMAC_KAT_VECTORS_CALCULATE_KEY,
		HMAC_KAT_VECTORS_CALCULATE_KEY_LEN, SHA384_HMAC_KAT_CALCULATE_KEY_HASH,
		HMAC_KAT_VECTORS_CALCULATE_DATA, HMAC_KAT_VECTORS_CALCULATE_DATA_LEN, NULL, 0,
		HASH_TYPE_SHA384, HMAC_KAT_VECTORS_CALCULATE_SHA384_MAC, SHA384_HASH_LENGTH);

	status |= hash_mock_expect_hmac_init (&engine, HMAC_KAT_VECTORS_UPDATE_KEY,
		HMAC_KAT_VECTORS_UPDATE_KEY_LEN, HASH_TYPE_SHA384);

	status |= mock_expect (&engine.mock, engine.base.update, &engine, 0,
		MOCK_ARG_PTR_CONTAINS (HMAC_KAT_VECTORS_UPDATE_DATA_1, HMAC_KAT_VECTORS_UPDATE_DATA_1_LEN),
		MOCK_ARG (HMAC_KAT_VECTORS_UPDATE_DATA_1_LEN));
	status |= mock_expect (&engine.mock, engine.base.update, &engine, 0,
		MOCK_ARG_PTR_CONTAINS (HMAC_KAT_VECTORS_UPDATE_DATA_2, HMAC_KAT_VECTORS_UPDATE_DATA_2_LEN),
		MOCK_ARG (HMAC_KAT_VECTORS_UPDATE_DATA_2_LEN));

	status |= mock_expect (&engine.mock, engine.base.finish, &engine, HASH_ENGINE_FINISH_FAILED,
		MOCK_ARG_NOT_NULL, MOCK_ARG_AT_LEAST (SHA384_HASH_LENGTH));

	status |= mock_expect (&engine.mock, engine.base.cancel, &engine, 0);

	CuAssertIntEquals (test, 0, status);

	status = hash_hmac_run_self_test_sha384 (&engine.base);
	CuAssertIntEquals (test, HASH_ENGINE_FINISH_FAILED, status);

	status = hash_mock_validate_and_release (&engine);
	CuAssertIntEquals (test, 0, status);
}
#endif

static void hash_test_hmac_run_self_test_sha512 (CuTest *test)
{
	HASH_TESTING_ENGINE engine;
	int status;

	TEST_START;

	status = HASH_TESTING_ENGINE_INIT (&engine);
	CuAssertIntEquals (test, 0, status);

	status = hash_hmac_run_self_test_sha512 (&engine.base);
#ifdef HASH_ENABLE_SHA512
	CuAssertIntEquals (test, 0, status);
#else
	CuAssertIntEquals (test, HASH_ENGINE_UNSUPPORTED_HASH, status);
#endif

	HASH_TESTING_ENGINE_RELEASE (&engine);
}

#ifdef HASH_ENABLE_SHA512
static void hash_test_hmac_run_self_test_sha512_mismatch_data_calculate (CuTest *test)
{
	struct hash_engine_mock engine;
	int status;

	TEST_START;

	status = hash_mock_init (&engine);
	CuAssertIntEquals (test, 0, status);

	status = hash_mock_expect_hmac_large_key (&engine, HMAC_KAT_VECTORS_CALCULATE_KEY,
		HMAC_KAT_VECTORS_CALCULATE_KEY_LEN, SHA512_HMAC_KAT_CALCULATE_KEY_HASH,
		HMAC_KAT_VECTORS_CALCULATE_DATA, HMAC_KAT_VECTORS_CALCULATE_DATA_LEN, NULL, 0,
		HASH_TYPE_SHA512, SHA512_TEST_HMAC, SHA512_HASH_LENGTH);
	CuAssertIntEquals (test, 0, status);

	status = hash_hmac_run_self_test_sha512 (&engine.base);
	CuAssertIntEquals (test, HASH_ENGINE_HMAC_SHA512_SELF_TEST_FAILED, status);

	status = hash_mock_validate_and_release (&engine);
	CuAssertIntEquals (test, 0, status);
}

static void hash_test_hmac_run_self_test_sha512_mismatch_data_update (CuTest *test)
{
	struct hash_engine_mock engine;
	int status;

	TEST_START;

	status = hash_mock_init (&engine);
	CuAssertIntEquals (test, 0, status);

	status = hash_mock_expect_hmac_large_key (&engine, HMAC_KAT_VECTORS_CALCULATE_KEY,
		HMAC_KAT_VECTORS_CALCULATE_KEY_LEN, SHA512_HMAC_KAT_CALCULATE_KEY_HASH,
		HMAC_KAT_VECTORS_CALCULATE_DATA, HMAC_KAT_VECTORS_CALCULATE_DATA_LEN, NULL, 0,
		HASH_TYPE_SHA512, HMAC_KAT_VECTORS_CALCULATE_SHA512_MAC, SHA512_HASH_LENGTH);

	status |= hash_mock_expect_hmac_init (&engine, HMAC_KAT_VECTORS_UPDATE_KEY,
		HMAC_KAT_VECTORS_UPDATE_KEY_LEN, HASH_TYPE_SHA512);

	status |= mock_expect (&engine.mock, engine.base.update, &engine, 0,
		MOCK_ARG_PTR_CONTAINS (HMAC_KAT_VECTORS_UPDATE_DATA_1, HMAC_KAT_VECTORS_UPDATE_DATA_1_LEN),
		MOCK_ARG (HMAC_KAT_VECTORS_UPDATE_DATA_1_LEN));
	status |= mock_expect (&engine.mock, engine.base.update, &engine, 0,
		MOCK_ARG_PTR_CONTAINS (HMAC_KAT_VECTORS_UPDATE_DATA_2, HMAC_KAT_VECTORS_UPDATE_DATA_2_LEN),
		MOCK_ARG (HMAC_KAT_VECTORS_UPDATE_DATA_2_LEN));

	status |= hash_mock_expect_hmac_finish (&engine, HMAC_KAT_VECTORS_UPDATE_KEY,
		HMAC_KAT_VECTORS_UPDATE_KEY_LEN, NULL, 0, HASH_TYPE_SHA512, SHA512_FULL_BLOCK_1024_HMAC,
		SHA512_HASH_LENGTH);

	CuAssertIntEquals (test, 0, status);

	status = hash_hmac_run_self_test_sha512 (&engine.base);
	CuAssertIntEquals (test, HASH_ENGINE_HMAC_SHA512_SELF_TEST_FAILED, status);

	status = hash_mock_validate_and_release (&engine);
	CuAssertIntEquals (test, 0, status);
}

static void hash_test_hmac_run_self_test_sha512_null (CuTest *test)
{
	HASH_TESTING_ENGINE engine;
	int status;

	TEST_START;

	status = HASH_TESTING_ENGINE_INIT (&engine);
	CuAssertIntEquals (test, 0, status);

	status = hash_hmac_run_self_test_sha512 (NULL);
	CuAssertIntEquals (test, HASH_ENGINE_INVALID_ARGUMENT, status);

	HASH_TESTING_ENGINE_RELEASE (&engine);
}

static void hash_test_hmac_run_self_test_sha512_calculate_fail (CuTest *test)
{
	struct hash_engine_mock engine;
	int status;

	TEST_START;

	status = hash_mock_init (&engine);
	CuAssertIntEquals (test, 0, status);

	status = mock_expect (&engine.mock, engine.base.calculate_sha512, &engine,
		HASH_ENGINE_SHA512_FAILED,
		MOCK_ARG_PTR_CONTAINS (HMAC_KAT_VECTORS_CALCULATE_KEY, HMAC_KAT_VECTORS_CALCULATE_KEY_LEN),
		MOCK_ARG (HMAC_KAT_VECTORS_CALCULATE_KEY_LEN), MOCK_ARG_NOT_NULL,
		MOCK_ARG_AT_LEAST (SHA512_HASH_LENGTH));
	CuAssertIntEquals (test, 0, status);

	status = hash_hmac_run_self_test_sha512 (&engine.base);
	CuAssertIntEquals (test, HASH_ENGINE_SHA512_FAILED, status);

	status = hash_mock_validate_and_release (&engine);
	CuAssertIntEquals (test, 0, status);
}

static void hash_test_hmac_run_self_test_sha512_hmac_init_fail (CuTest *test)
{
	struct hash_engine_mock engine;
	int status;

	TEST_START;

	status = hash_mock_init (&engine);
	CuAssertIntEquals (test, 0, status);

	status = hash_mock_expect_hmac_large_key (&engine, HMAC_KAT_VECTORS_CALCULATE_KEY,
		HMAC_KAT_VECTORS_CALCULATE_KEY_LEN, SHA512_HMAC_KAT_CALCULATE_KEY_HASH,
		HMAC_KAT_VECTORS_CALCULATE_DATA, HMAC_KAT_VECTORS_CALCULATE_DATA_LEN, NULL, 0,
		HASH_TYPE_SHA512, HMAC_KAT_VECTORS_CALCULATE_SHA512_MAC, SHA512_HASH_LENGTH);

	status = mock_expect (&engine.mock, engine.base.start_sha512, &engine,
		HASH_ENGINE_START_SHA512_FAILED);

	CuAssertIntEquals (test, 0, status);

	status = hash_hmac_run_self_test_sha512 (&engine.base);
	CuAssertIntEquals (test, HASH_ENGINE_START_SHA512_FAILED, status);

	status = hash_mock_validate_and_release (&engine);
	CuAssertIntEquals (test, 0, status);
}

static void hash_test_hmac_run_self_test_sha512_update_first_fail (CuTest *test)
{
	struct hash_engine_mock engine;
	int status;

	TEST_START;

	status = hash_mock_init (&engine);
	CuAssertIntEquals (test, 0, status);

	status = hash_mock_expect_hmac_large_key (&engine, HMAC_KAT_VECTORS_CALCULATE_KEY,
		HMAC_KAT_VECTORS_CALCULATE_KEY_LEN, SHA512_HMAC_KAT_CALCULATE_KEY_HASH,
		HMAC_KAT_VECTORS_CALCULATE_DATA, HMAC_KAT_VECTORS_CALCULATE_DATA_LEN, NULL, 0,
		HASH_TYPE_SHA512, HMAC_KAT_VECTORS_CALCULATE_SHA512_MAC, SHA512_HASH_LENGTH);

	status |= hash_mock_expect_hmac_init (&engine, HMAC_KAT_VECTORS_UPDATE_KEY,
		HMAC_KAT_VECTORS_UPDATE_KEY_LEN, HASH_TYPE_SHA512);

	status |= mock_expect (&engine.mock, engine.base.update, &engine, HASH_ENGINE_UPDATE_FAILED,
		MOCK_ARG_PTR_CONTAINS (HMAC_KAT_VECTORS_UPDATE_DATA_1, HMAC_KAT_VECTORS_UPDATE_DATA_1_LEN),
		MOCK_ARG (HMAC_KAT_VECTORS_UPDATE_DATA_1_LEN));

	status |= mock_expect (&engine.mock, engine.base.cancel, &engine, 0);

	CuAssertIntEquals (test, 0, status);

	status = hash_hmac_run_self_test_sha512 (&engine.base);
	CuAssertIntEquals (test, HASH_ENGINE_UPDATE_FAILED, status);

	status = hash_mock_validate_and_release (&engine);
	CuAssertIntEquals (test, 0, status);
}

static void hash_test_hmac_run_self_test_sha512_update_second_fail (CuTest *test)
{
	struct hash_engine_mock engine;
	int status;

	TEST_START;

	status = hash_mock_init (&engine);
	CuAssertIntEquals (test, 0, status);

	status = hash_mock_expect_hmac_large_key (&engine, HMAC_KAT_VECTORS_CALCULATE_KEY,
		HMAC_KAT_VECTORS_CALCULATE_KEY_LEN, SHA512_HMAC_KAT_CALCULATE_KEY_HASH,
		HMAC_KAT_VECTORS_CALCULATE_DATA, HMAC_KAT_VECTORS_CALCULATE_DATA_LEN, NULL, 0,
		HASH_TYPE_SHA512, HMAC_KAT_VECTORS_CALCULATE_SHA512_MAC, SHA512_HASH_LENGTH);

	status |= hash_mock_expect_hmac_init (&engine, HMAC_KAT_VECTORS_UPDATE_KEY,
		HMAC_KAT_VECTORS_UPDATE_KEY_LEN, HASH_TYPE_SHA512);

	status |= mock_expect (&engine.mock, engine.base.update, &engine, 0,
		MOCK_ARG_PTR_CONTAINS (HMAC_KAT_VECTORS_UPDATE_DATA_1, HMAC_KAT_VECTORS_UPDATE_DATA_1_LEN),
		MOCK_ARG (HMAC_KAT_VECTORS_UPDATE_DATA_1_LEN));
	status |= mock_expect (&engine.mock, engine.base.update, &engine, HASH_ENGINE_UPDATE_FAILED,
		MOCK_ARG_PTR_CONTAINS (HMAC_KAT_VECTORS_UPDATE_DATA_2, HMAC_KAT_VECTORS_UPDATE_DATA_2_LEN),
		MOCK_ARG (HMAC_KAT_VECTORS_UPDATE_DATA_2_LEN));

	status |= mock_expect (&engine.mock, engine.base.cancel, &engine, 0);

	CuAssertIntEquals (test, 0, status);

	status = hash_hmac_run_self_test_sha512 (&engine.base);
	CuAssertIntEquals (test, HASH_ENGINE_UPDATE_FAILED, status);

	status = hash_mock_validate_and_release (&engine);
	CuAssertIntEquals (test, 0, status);
}

static void hash_test_hmac_run_self_test_sha512_finish_fail (CuTest *test)
{
	struct hash_engine_mock engine;
	int status;

	TEST_START;

	status = hash_mock_init (&engine);
	CuAssertIntEquals (test, 0, status);

	status = hash_mock_expect_hmac_large_key (&engine, HMAC_KAT_VECTORS_CALCULATE_KEY,
		HMAC_KAT_VECTORS_CALCULATE_KEY_LEN, SHA512_HMAC_KAT_CALCULATE_KEY_HASH,
		HMAC_KAT_VECTORS_CALCULATE_DATA, HMAC_KAT_VECTORS_CALCULATE_DATA_LEN, NULL, 0,
		HASH_TYPE_SHA512, HMAC_KAT_VECTORS_CALCULATE_SHA512_MAC, SHA512_HASH_LENGTH);

	status |= hash_mock_expect_hmac_init (&engine, HMAC_KAT_VECTORS_UPDATE_KEY,
		HMAC_KAT_VECTORS_UPDATE_KEY_LEN, HASH_TYPE_SHA512);

	status |= mock_expect (&engine.mock, engine.base.update, &engine, 0,
		MOCK_ARG_PTR_CONTAINS (HMAC_KAT_VECTORS_UPDATE_DATA_1, HMAC_KAT_VECTORS_UPDATE_DATA_1_LEN),
		MOCK_ARG (HMAC_KAT_VECTORS_UPDATE_DATA_1_LEN));
	status |= mock_expect (&engine.mock, engine.base.update, &engine, 0,
		MOCK_ARG_PTR_CONTAINS (HMAC_KAT_VECTORS_UPDATE_DATA_2, HMAC_KAT_VECTORS_UPDATE_DATA_2_LEN),
		MOCK_ARG (HMAC_KAT_VECTORS_UPDATE_DATA_2_LEN));

	status |= mock_expect (&engine.mock, engine.base.finish, &engine, HASH_ENGINE_FINISH_FAILED,
		MOCK_ARG_NOT_NULL, MOCK_ARG_AT_LEAST (SHA512_HASH_LENGTH));

	status |= mock_expect (&engine.mock, engine.base.cancel, &engine, 0);

	CuAssertIntEquals (test, 0, status);

	status = hash_hmac_run_self_test_sha512 (&engine.base);
	CuAssertIntEquals (test, HASH_ENGINE_FINISH_FAILED, status);

	status = hash_mock_validate_and_release (&engine);
	CuAssertIntEquals (test, 0, status);
}
#endif

static void hash_test_hmac_run_all_self_tests (CuTest *test)
{
	HASH_TESTING_ENGINE engine;
	int status;

	TEST_START;

	status = HASH_TESTING_ENGINE_INIT (&engine);
	CuAssertIntEquals (test, 0, status);

	status = hash_hmac_run_all_self_tests (&engine.base);
	CuAssertIntEquals (test, 0, status);

	HASH_TESTING_ENGINE_RELEASE (&engine);
}

static void hash_test_hmac_run_all_self_tests_mock (CuTest *test)
{
	struct hash_engine_mock engine;
	int status;

	TEST_START;

	status = hash_mock_init (&engine);
	CuAssertIntEquals (test, 0, status);

#ifdef HASH_ENABLE_SHA1
	status = hash_mock_expect_hmac_large_key (&engine, HMAC_KAT_VECTORS_CALCULATE_KEY,
		HMAC_KAT_VECTORS_CALCULATE_KEY_LEN, SHA1_HMAC_KAT_CALCULATE_KEY_HASH,
		HMAC_KAT_VECTORS_CALCULATE_DATA, HMAC_KAT_VECTORS_CALCULATE_DATA_LEN, NULL, 0,
		HASH_TYPE_SHA1, HMAC_KAT_VECTORS_CALCULATE_SHA1_MAC, SHA1_HASH_LENGTH);

	status |= hash_mock_expect_hmac_init (&engine, HMAC_KAT_VECTORS_UPDATE_KEY,
		HMAC_KAT_VECTORS_UPDATE_KEY_LEN, HASH_TYPE_SHA1);

	status |= mock_expect (&engine.mock, engine.base.update, &engine, 0,
		MOCK_ARG_PTR_CONTAINS (HMAC_KAT_VECTORS_UPDATE_DATA_1, HMAC_KAT_VECTORS_UPDATE_DATA_1_LEN),
		MOCK_ARG (HMAC_KAT_VECTORS_UPDATE_DATA_1_LEN));
	status |= mock_expect (&engine.mock, engine.base.update, &engine, 0,
		MOCK_ARG_PTR_CONTAINS (HMAC_KAT_VECTORS_UPDATE_DATA_2, HMAC_KAT_VECTORS_UPDATE_DATA_2_LEN),
		MOCK_ARG (HMAC_KAT_VECTORS_UPDATE_DATA_2_LEN));

	status |= hash_mock_expect_hmac_finish (&engine, HMAC_KAT_VECTORS_UPDATE_KEY,
		HMAC_KAT_VECTORS_UPDATE_KEY_LEN, NULL, 0, HASH_TYPE_SHA1, HMAC_KAT_VECTORS_UPDATE_SHA1_MAC,
		SHA1_HASH_LENGTH);
#endif

	status |= hash_mock_expect_hmac_large_key (&engine, HMAC_KAT_VECTORS_CALCULATE_KEY,
		HMAC_KAT_VECTORS_CALCULATE_KEY_LEN, SHA256_HMAC_KAT_CALCULATE_KEY_HASH,
		HMAC_KAT_VECTORS_CALCULATE_DATA, HMAC_KAT_VECTORS_CALCULATE_DATA_LEN, NULL, 0,
		HASH_TYPE_SHA256, HMAC_KAT_VECTORS_CALCULATE_SHA256_MAC, SHA256_HASH_LENGTH);

	status |= hash_mock_expect_hmac_init (&engine, HMAC_KAT_VECTORS_UPDATE_KEY,
		HMAC_KAT_VECTORS_UPDATE_KEY_LEN, HASH_TYPE_SHA256);

	status |= mock_expect (&engine.mock, engine.base.update, &engine, 0,
		MOCK_ARG_PTR_CONTAINS (HMAC_KAT_VECTORS_UPDATE_DATA_1, HMAC_KAT_VECTORS_UPDATE_DATA_1_LEN),
		MOCK_ARG (HMAC_KAT_VECTORS_UPDATE_DATA_1_LEN));
	status |= mock_expect (&engine.mock, engine.base.update, &engine, 0,
		MOCK_ARG_PTR_CONTAINS (HMAC_KAT_VECTORS_UPDATE_DATA_2, HMAC_KAT_VECTORS_UPDATE_DATA_2_LEN),
		MOCK_ARG (HMAC_KAT_VECTORS_UPDATE_DATA_2_LEN));

	status |= hash_mock_expect_hmac_finish (&engine, HMAC_KAT_VECTORS_UPDATE_KEY,
		HMAC_KAT_VECTORS_UPDATE_KEY_LEN, NULL, 0, HASH_TYPE_SHA256,
		HMAC_KAT_VECTORS_UPDATE_SHA256_MAC, SHA256_HASH_LENGTH);

#ifdef HASH_ENABLE_SHA384
	status |= hash_mock_expect_hmac_large_key (&engine, HMAC_KAT_VECTORS_CALCULATE_KEY,
		HMAC_KAT_VECTORS_CALCULATE_KEY_LEN, SHA384_HMAC_KAT_CALCULATE_KEY_HASH,
		HMAC_KAT_VECTORS_CALCULATE_DATA, HMAC_KAT_VECTORS_CALCULATE_DATA_LEN, NULL, 0,
		HASH_TYPE_SHA384, HMAC_KAT_VECTORS_CALCULATE_SHA384_MAC, SHA384_HASH_LENGTH);

	status |= hash_mock_expect_hmac_init (&engine, HMAC_KAT_VECTORS_UPDATE_KEY,
		HMAC_KAT_VECTORS_UPDATE_KEY_LEN, HASH_TYPE_SHA384);

	status |= mock_expect (&engine.mock, engine.base.update, &engine, 0,
		MOCK_ARG_PTR_CONTAINS (HMAC_KAT_VECTORS_UPDATE_DATA_1, HMAC_KAT_VECTORS_UPDATE_DATA_1_LEN),
		MOCK_ARG (HMAC_KAT_VECTORS_UPDATE_DATA_1_LEN));
	status |= mock_expect (&engine.mock, engine.base.update, &engine, 0,
		MOCK_ARG_PTR_CONTAINS (HMAC_KAT_VECTORS_UPDATE_DATA_2, HMAC_KAT_VECTORS_UPDATE_DATA_2_LEN),
		MOCK_ARG (HMAC_KAT_VECTORS_UPDATE_DATA_2_LEN));

	status |= hash_mock_expect_hmac_finish (&engine, HMAC_KAT_VECTORS_UPDATE_KEY,
		HMAC_KAT_VECTORS_UPDATE_KEY_LEN, NULL, 0, HASH_TYPE_SHA384,
		HMAC_KAT_VECTORS_UPDATE_SHA384_MAC, SHA384_HASH_LENGTH);
#endif

#ifdef HASH_ENABLE_SHA512
	status |= hash_mock_expect_hmac_large_key (&engine, HMAC_KAT_VECTORS_CALCULATE_KEY,
		HMAC_KAT_VECTORS_CALCULATE_KEY_LEN, SHA512_HMAC_KAT_CALCULATE_KEY_HASH,
		HMAC_KAT_VECTORS_CALCULATE_DATA, HMAC_KAT_VECTORS_CALCULATE_DATA_LEN, NULL, 0,
		HASH_TYPE_SHA512, HMAC_KAT_VECTORS_CALCULATE_SHA512_MAC, SHA512_HASH_LENGTH);

	status |= hash_mock_expect_hmac_init (&engine, HMAC_KAT_VECTORS_UPDATE_KEY,
		HMAC_KAT_VECTORS_UPDATE_KEY_LEN, HASH_TYPE_SHA512);

	status |= mock_expect (&engine.mock, engine.base.update, &engine, 0,
		MOCK_ARG_PTR_CONTAINS (HMAC_KAT_VECTORS_UPDATE_DATA_1, HMAC_KAT_VECTORS_UPDATE_DATA_1_LEN),
		MOCK_ARG (HMAC_KAT_VECTORS_UPDATE_DATA_1_LEN));
	status |= mock_expect (&engine.mock, engine.base.update, &engine, 0,
		MOCK_ARG_PTR_CONTAINS (HMAC_KAT_VECTORS_UPDATE_DATA_2, HMAC_KAT_VECTORS_UPDATE_DATA_2_LEN),
		MOCK_ARG (HMAC_KAT_VECTORS_UPDATE_DATA_2_LEN));

	status |= hash_mock_expect_hmac_finish (&engine, HMAC_KAT_VECTORS_UPDATE_KEY,
		HMAC_KAT_VECTORS_UPDATE_KEY_LEN, NULL, 0, HASH_TYPE_SHA512,
		HMAC_KAT_VECTORS_UPDATE_SHA512_MAC, SHA512_HASH_LENGTH);
#endif

	CuAssertIntEquals (test, 0, status);

	status = hash_hmac_run_all_self_tests (&engine.base);
	CuAssertIntEquals (test, 0, status);

	status = hash_mock_validate_and_release (&engine);
	CuAssertIntEquals (test, 0, status);
}

static void hash_test_hmac_run_all_self_tests_null (CuTest *test)
{
	HASH_TESTING_ENGINE engine;
	int status;

	TEST_START;

	status = HASH_TESTING_ENGINE_INIT (&engine);
	CuAssertIntEquals (test, 0, status);

	status = hash_hmac_run_all_self_tests (NULL);
	CuAssertIntEquals (test, HASH_ENGINE_INVALID_ARGUMENT, status);

	HASH_TESTING_ENGINE_RELEASE (&engine);
}

#ifdef HASH_ENABLE_SHA1
static void hash_test_hmac_run_all_self_tests_sha1_fail (CuTest *test)
{
	struct hash_engine_mock engine;
	int status;

	TEST_START;

	status = hash_mock_init (&engine);
	CuAssertIntEquals (test, 0, status);

	status = mock_expect (&engine.mock, engine.base.calculate_sha1, &engine,
		HASH_ENGINE_SHA1_FAILED,
		MOCK_ARG_PTR_CONTAINS (HMAC_KAT_VECTORS_CALCULATE_KEY, HMAC_KAT_VECTORS_CALCULATE_KEY_LEN),
		MOCK_ARG (HMAC_KAT_VECTORS_CALCULATE_KEY_LEN), MOCK_ARG_NOT_NULL,
		MOCK_ARG_AT_LEAST (SHA1_HASH_LENGTH));
	CuAssertIntEquals (test, 0, status);

	status = hash_hmac_run_all_self_tests (&engine.base);
	CuAssertIntEquals (test, HASH_ENGINE_SHA1_FAILED, status);

	status = hash_mock_validate_and_release (&engine);
	CuAssertIntEquals (test, 0, status);
}
#endif

static void hash_test_hmac_run_all_self_tests_sha256_fail (CuTest *test)
{
	struct hash_engine_mock engine;
	int status;

	TEST_START;

	status = hash_mock_init (&engine);
	CuAssertIntEquals (test, 0, status);

#ifdef HASH_ENABLE_SHA1
	status = hash_mock_expect_hmac_large_key (&engine, HMAC_KAT_VECTORS_CALCULATE_KEY,
		HMAC_KAT_VECTORS_CALCULATE_KEY_LEN, SHA1_HMAC_KAT_CALCULATE_KEY_HASH,
		HMAC_KAT_VECTORS_CALCULATE_DATA, HMAC_KAT_VECTORS_CALCULATE_DATA_LEN, NULL, 0,
		HASH_TYPE_SHA1, HMAC_KAT_VECTORS_CALCULATE_SHA1_MAC, SHA1_HASH_LENGTH);

	status |= hash_mock_expect_hmac_init (&engine, HMAC_KAT_VECTORS_UPDATE_KEY,
		HMAC_KAT_VECTORS_UPDATE_KEY_LEN, HASH_TYPE_SHA1);

	status |= mock_expect (&engine.mock, engine.base.update, &engine, 0,
		MOCK_ARG_PTR_CONTAINS (HMAC_KAT_VECTORS_UPDATE_DATA_1, HMAC_KAT_VECTORS_UPDATE_DATA_1_LEN),
		MOCK_ARG (HMAC_KAT_VECTORS_UPDATE_DATA_1_LEN));
	status |= mock_expect (&engine.mock, engine.base.update, &engine, 0,
		MOCK_ARG_PTR_CONTAINS (HMAC_KAT_VECTORS_UPDATE_DATA_2, HMAC_KAT_VECTORS_UPDATE_DATA_2_LEN),
		MOCK_ARG (HMAC_KAT_VECTORS_UPDATE_DATA_2_LEN));

	status |= hash_mock_expect_hmac_finish (&engine, HMAC_KAT_VECTORS_UPDATE_KEY,
		HMAC_KAT_VECTORS_UPDATE_KEY_LEN, NULL, 0, HASH_TYPE_SHA1, HMAC_KAT_VECTORS_UPDATE_SHA1_MAC,
		SHA1_HASH_LENGTH);
#endif

	status = mock_expect (&engine.mock, engine.base.calculate_sha256, &engine,
		HASH_ENGINE_SHA256_FAILED,
		MOCK_ARG_PTR_CONTAINS (HMAC_KAT_VECTORS_CALCULATE_KEY, HMAC_KAT_VECTORS_CALCULATE_KEY_LEN),
		MOCK_ARG (HMAC_KAT_VECTORS_CALCULATE_KEY_LEN), MOCK_ARG_NOT_NULL,
		MOCK_ARG_AT_LEAST (SHA256_HASH_LENGTH));

	CuAssertIntEquals (test, 0, status);

	status = hash_hmac_run_all_self_tests (&engine.base);
	CuAssertIntEquals (test, HASH_ENGINE_SHA256_FAILED, status);

	status = hash_mock_validate_and_release (&engine);
	CuAssertIntEquals (test, 0, status);
}

#ifdef HASH_ENABLE_SHA384
static void hash_test_hmac_run_all_self_tests_sha384_fail (CuTest *test)
{
	struct hash_engine_mock engine;
	int status;

	TEST_START;

	status = hash_mock_init (&engine);
	CuAssertIntEquals (test, 0, status);

#ifdef HASH_ENABLE_SHA1
	status = hash_mock_expect_hmac_large_key (&engine, HMAC_KAT_VECTORS_CALCULATE_KEY,
		HMAC_KAT_VECTORS_CALCULATE_KEY_LEN, SHA1_HMAC_KAT_CALCULATE_KEY_HASH,
		HMAC_KAT_VECTORS_CALCULATE_DATA, HMAC_KAT_VECTORS_CALCULATE_DATA_LEN, NULL, 0,
		HASH_TYPE_SHA1, HMAC_KAT_VECTORS_CALCULATE_SHA1_MAC, SHA1_HASH_LENGTH);

	status |= hash_mock_expect_hmac_init (&engine, HMAC_KAT_VECTORS_UPDATE_KEY,
		HMAC_KAT_VECTORS_UPDATE_KEY_LEN, HASH_TYPE_SHA1);

	status |= mock_expect (&engine.mock, engine.base.update, &engine, 0,
		MOCK_ARG_PTR_CONTAINS (HMAC_KAT_VECTORS_UPDATE_DATA_1, HMAC_KAT_VECTORS_UPDATE_DATA_1_LEN),
		MOCK_ARG (HMAC_KAT_VECTORS_UPDATE_DATA_1_LEN));
	status |= mock_expect (&engine.mock, engine.base.update, &engine, 0,
		MOCK_ARG_PTR_CONTAINS (HMAC_KAT_VECTORS_UPDATE_DATA_2, HMAC_KAT_VECTORS_UPDATE_DATA_2_LEN),
		MOCK_ARG (HMAC_KAT_VECTORS_UPDATE_DATA_2_LEN));

	status |= hash_mock_expect_hmac_finish (&engine, HMAC_KAT_VECTORS_UPDATE_KEY,
		HMAC_KAT_VECTORS_UPDATE_KEY_LEN, NULL, 0, HASH_TYPE_SHA1, HMAC_KAT_VECTORS_UPDATE_SHA1_MAC,
		SHA1_HASH_LENGTH);
#endif

	status |= hash_mock_expect_hmac_large_key (&engine, HMAC_KAT_VECTORS_CALCULATE_KEY,
		HMAC_KAT_VECTORS_CALCULATE_KEY_LEN, SHA256_HMAC_KAT_CALCULATE_KEY_HASH,
		HMAC_KAT_VECTORS_CALCULATE_DATA, HMAC_KAT_VECTORS_CALCULATE_DATA_LEN, NULL, 0,
		HASH_TYPE_SHA256, HMAC_KAT_VECTORS_CALCULATE_SHA256_MAC, SHA256_HASH_LENGTH);

	status |= hash_mock_expect_hmac_init (&engine, HMAC_KAT_VECTORS_UPDATE_KEY,
		HMAC_KAT_VECTORS_UPDATE_KEY_LEN, HASH_TYPE_SHA256);

	status |= mock_expect (&engine.mock, engine.base.update, &engine, 0,
		MOCK_ARG_PTR_CONTAINS (HMAC_KAT_VECTORS_UPDATE_DATA_1, HMAC_KAT_VECTORS_UPDATE_DATA_1_LEN),
		MOCK_ARG (HMAC_KAT_VECTORS_UPDATE_DATA_1_LEN));
	status |= mock_expect (&engine.mock, engine.base.update, &engine, 0,
		MOCK_ARG_PTR_CONTAINS (HMAC_KAT_VECTORS_UPDATE_DATA_2, HMAC_KAT_VECTORS_UPDATE_DATA_2_LEN),
		MOCK_ARG (HMAC_KAT_VECTORS_UPDATE_DATA_2_LEN));

	status |= hash_mock_expect_hmac_finish (&engine, HMAC_KAT_VECTORS_UPDATE_KEY,
		HMAC_KAT_VECTORS_UPDATE_KEY_LEN, NULL, 0, HASH_TYPE_SHA256,
		HMAC_KAT_VECTORS_UPDATE_SHA256_MAC, SHA256_HASH_LENGTH);

	status = mock_expect (&engine.mock, engine.base.calculate_sha384, &engine,
		HASH_ENGINE_SHA384_FAILED,
		MOCK_ARG_PTR_CONTAINS (HMAC_KAT_VECTORS_CALCULATE_KEY, HMAC_KAT_VECTORS_CALCULATE_KEY_LEN),
		MOCK_ARG (HMAC_KAT_VECTORS_CALCULATE_KEY_LEN), MOCK_ARG_NOT_NULL,
		MOCK_ARG_AT_LEAST (SHA384_HASH_LENGTH));

	CuAssertIntEquals (test, 0, status);

	status = hash_hmac_run_all_self_tests (&engine.base);
	CuAssertIntEquals (test, HASH_ENGINE_SHA384_FAILED, status);

	status = hash_mock_validate_and_release (&engine);
	CuAssertIntEquals (test, 0, status);
}
#endif

#ifdef HASH_ENABLE_SHA512
static void hash_test_hmac_run_all_self_tests_sha512_fail (CuTest *test)
{
	struct hash_engine_mock engine;
	int status;

	TEST_START;

	status = hash_mock_init (&engine);
	CuAssertIntEquals (test, 0, status);

#ifdef HASH_ENABLE_SHA1
	status = hash_mock_expect_hmac_large_key (&engine, HMAC_KAT_VECTORS_CALCULATE_KEY,
		HMAC_KAT_VECTORS_CALCULATE_KEY_LEN, SHA1_HMAC_KAT_CALCULATE_KEY_HASH,
		HMAC_KAT_VECTORS_CALCULATE_DATA, HMAC_KAT_VECTORS_CALCULATE_DATA_LEN, NULL, 0,
		HASH_TYPE_SHA1, HMAC_KAT_VECTORS_CALCULATE_SHA1_MAC, SHA1_HASH_LENGTH);

	status |= hash_mock_expect_hmac_init (&engine, HMAC_KAT_VECTORS_UPDATE_KEY,
		HMAC_KAT_VECTORS_UPDATE_KEY_LEN, HASH_TYPE_SHA1);

	status |= mock_expect (&engine.mock, engine.base.update, &engine, 0,
		MOCK_ARG_PTR_CONTAINS (HMAC_KAT_VECTORS_UPDATE_DATA_1, HMAC_KAT_VECTORS_UPDATE_DATA_1_LEN),
		MOCK_ARG (HMAC_KAT_VECTORS_UPDATE_DATA_1_LEN));
	status |= mock_expect (&engine.mock, engine.base.update, &engine, 0,
		MOCK_ARG_PTR_CONTAINS (HMAC_KAT_VECTORS_UPDATE_DATA_2, HMAC_KAT_VECTORS_UPDATE_DATA_2_LEN),
		MOCK_ARG (HMAC_KAT_VECTORS_UPDATE_DATA_2_LEN));

	status |= hash_mock_expect_hmac_finish (&engine, HMAC_KAT_VECTORS_UPDATE_KEY,
		HMAC_KAT_VECTORS_UPDATE_KEY_LEN, NULL, 0, HASH_TYPE_SHA1, HMAC_KAT_VECTORS_UPDATE_SHA1_MAC,
		SHA1_HASH_LENGTH);
#endif

	status |= hash_mock_expect_hmac_large_key (&engine, HMAC_KAT_VECTORS_CALCULATE_KEY,
		HMAC_KAT_VECTORS_CALCULATE_KEY_LEN, SHA256_HMAC_KAT_CALCULATE_KEY_HASH,
		HMAC_KAT_VECTORS_CALCULATE_DATA, HMAC_KAT_VECTORS_CALCULATE_DATA_LEN, NULL, 0,
		HASH_TYPE_SHA256, HMAC_KAT_VECTORS_CALCULATE_SHA256_MAC, SHA256_HASH_LENGTH);

	status |= hash_mock_expect_hmac_init (&engine, HMAC_KAT_VECTORS_UPDATE_KEY,
		HMAC_KAT_VECTORS_UPDATE_KEY_LEN, HASH_TYPE_SHA256);

	status |= mock_expect (&engine.mock, engine.base.update, &engine, 0,
		MOCK_ARG_PTR_CONTAINS (HMAC_KAT_VECTORS_UPDATE_DATA_1, HMAC_KAT_VECTORS_UPDATE_DATA_1_LEN),
		MOCK_ARG (HMAC_KAT_VECTORS_UPDATE_DATA_1_LEN));
	status |= mock_expect (&engine.mock, engine.base.update, &engine, 0,
		MOCK_ARG_PTR_CONTAINS (HMAC_KAT_VECTORS_UPDATE_DATA_2, HMAC_KAT_VECTORS_UPDATE_DATA_2_LEN),
		MOCK_ARG (HMAC_KAT_VECTORS_UPDATE_DATA_2_LEN));

	status |= hash_mock_expect_hmac_finish (&engine, HMAC_KAT_VECTORS_UPDATE_KEY,
		HMAC_KAT_VECTORS_UPDATE_KEY_LEN, NULL, 0, HASH_TYPE_SHA256,
		HMAC_KAT_VECTORS_UPDATE_SHA256_MAC, SHA256_HASH_LENGTH);

#ifdef HASH_ENABLE_SHA384
	status |= hash_mock_expect_hmac_large_key (&engine, HMAC_KAT_VECTORS_CALCULATE_KEY,
		HMAC_KAT_VECTORS_CALCULATE_KEY_LEN, SHA384_HMAC_KAT_CALCULATE_KEY_HASH,
		HMAC_KAT_VECTORS_CALCULATE_DATA, HMAC_KAT_VECTORS_CALCULATE_DATA_LEN, NULL, 0,
		HASH_TYPE_SHA384, HMAC_KAT_VECTORS_CALCULATE_SHA384_MAC, SHA384_HASH_LENGTH);

	status |= hash_mock_expect_hmac_init (&engine, HMAC_KAT_VECTORS_UPDATE_KEY,
		HMAC_KAT_VECTORS_UPDATE_KEY_LEN, HASH_TYPE_SHA384);

	status |= mock_expect (&engine.mock, engine.base.update, &engine, 0,
		MOCK_ARG_PTR_CONTAINS (HMAC_KAT_VECTORS_UPDATE_DATA_1, HMAC_KAT_VECTORS_UPDATE_DATA_1_LEN),
		MOCK_ARG (HMAC_KAT_VECTORS_UPDATE_DATA_1_LEN));
	status |= mock_expect (&engine.mock, engine.base.update, &engine, 0,
		MOCK_ARG_PTR_CONTAINS (HMAC_KAT_VECTORS_UPDATE_DATA_2, HMAC_KAT_VECTORS_UPDATE_DATA_2_LEN),
		MOCK_ARG (HMAC_KAT_VECTORS_UPDATE_DATA_2_LEN));

	status |= hash_mock_expect_hmac_finish (&engine, HMAC_KAT_VECTORS_UPDATE_KEY,
		HMAC_KAT_VECTORS_UPDATE_KEY_LEN, NULL, 0, HASH_TYPE_SHA384,
		HMAC_KAT_VECTORS_UPDATE_SHA384_MAC, SHA384_HASH_LENGTH);
#endif

	status = mock_expect (&engine.mock, engine.base.calculate_sha512, &engine,
		HASH_ENGINE_SHA512_FAILED,
		MOCK_ARG_PTR_CONTAINS (HMAC_KAT_VECTORS_CALCULATE_KEY, HMAC_KAT_VECTORS_CALCULATE_KEY_LEN),
		MOCK_ARG (HMAC_KAT_VECTORS_CALCULATE_KEY_LEN), MOCK_ARG_NOT_NULL,
		MOCK_ARG_AT_LEAST (SHA512_HASH_LENGTH));

	CuAssertIntEquals (test, 0, status);

	status = hash_hmac_run_all_self_tests (&engine.base);
	CuAssertIntEquals (test, HASH_ENGINE_SHA512_FAILED, status);

	status = hash_mock_validate_and_release (&engine);
	CuAssertIntEquals (test, 0, status);
}
#endif


TEST_SUITE_START (hash);

TEST (hash_test_hmac_sha1_incremental);
#ifdef HASH_ENABLE_SHA1
TEST (hash_test_hmac_sha1_incremental_large_key);
#endif
TEST (hash_test_hmac_sha256_incremental);
TEST (hash_test_hmac_sha256_incremental_large_key);
TEST (hash_test_hmac_sha384_incremental);
#ifdef HASH_ENABLE_SHA384
TEST (hash_test_hmac_sha384_incremental_large_key);
#endif
TEST (hash_test_hmac_sha512_incremental);
#ifdef HASH_ENABLE_SHA512
TEST (hash_test_hmac_sha512_incremental_large_key);
#endif
TEST (hash_test_hmac_cancel);
TEST (hash_test_hmac_init_null);
TEST (hash_test_hmac_init_unknown);
TEST (hash_test_hmac_init_error);
#ifdef HASH_ENABLE_SHA1
TEST (hash_test_hmac_init_sha1_large_key_error);
#endif
TEST (hash_test_hmac_init_sha256_large_key_error);
#ifdef HASH_ENABLE_SHA384
TEST (hash_test_hmac_init_sha384_large_key_error);
#endif
#ifdef HASH_ENABLE_SHA512
TEST (hash_test_hmac_init_sha512_large_key_error);
#endif
TEST (hash_test_hmac_update_null);
TEST (hash_test_hmac_finish_null);
#ifdef HASH_ENABLE_SHA1
TEST (hash_test_hmac_finish_sha1_small_buffer);
#endif
TEST (hash_test_hmac_finish_sha256_small_buffer);
#ifdef HASH_ENABLE_SHA384
TEST (hash_test_hmac_finish_sha384_small_buffer);
#endif
#ifdef HASH_ENABLE_SHA512
TEST (hash_test_hmac_finish_sha512_small_buffer);
#endif
TEST (hash_test_hmac_finish_inner_hash_error);
TEST (hash_test_hmac_finish_outer_init_error);
TEST (hash_test_hmac_finish_outer_key_error);
TEST (hash_test_hmac_finish_outer_update_error);
TEST (hash_test_hmac_finish_outer_hash_error);
TEST (hash_test_hmac_cancel_null);
TEST (hash_test_hmac_sha1);
#ifdef HASH_ENABLE_SHA1
TEST (hash_test_hmac_sha1_large_key);
TEST (hash_test_hmac_sha1_test_key);
TEST (hash_test_hmac_sha1_block_size_key);
#endif
TEST (hash_test_hmac_sha256);
TEST (hash_test_hmac_sha256_large_key);
TEST (hash_test_hmac_sha256_test_key);
TEST (hash_test_hmac_sha256_block_size_key);
TEST (hash_test_hmac_sha384);
#ifdef HASH_ENABLE_SHA384
TEST (hash_test_hmac_sha384_large_key);
TEST (hash_test_hmac_sha384_test_key);
TEST (hash_test_hmac_sha384_block_size_key);
#endif
TEST (hash_test_hmac_sha512);
#ifdef HASH_ENABLE_SHA512
TEST (hash_test_hmac_sha512_large_key);
TEST (hash_test_hmac_sha512_test_key);
TEST (hash_test_hmac_sha512_block_size_key);
#endif
TEST (hash_test_hmac_unknown);
TEST (hash_test_hmac_null);
TEST (hash_test_hash_generate_hmac_start_error);
TEST (hash_test_hash_generate_hmac_init_error);
TEST (hash_test_hash_generate_hmac_update_error);
TEST (hash_test_hash_generate_hmac_finish_error);
#ifdef HASH_ENABLE_SHA1
TEST (hash_test_hash_generate_hmac_sha1_small_buffer);
#endif
TEST (hash_test_hash_generate_hmac_sha256_small_buffer);
#ifdef HASH_ENABLE_SHA384
TEST (hash_test_hash_generate_hmac_sha384_small_buffer);
#endif
#ifdef HASH_ENABLE_SHA512
TEST (hash_test_hash_generate_hmac_sha512_small_buffer);
#endif
TEST (hash_test_start_new_hash_sha1);
TEST (hash_test_start_new_hash_sha256);
TEST (hash_test_start_new_hash_sha384);
TEST (hash_test_start_new_hash_sha512);
TEST (hash_test_start_new_hash_unknown);
TEST (hash_test_start_new_hash_null);
#ifdef HASH_ENABLE_SHA1
TEST (hash_test_start_new_hash_sha1_error);
#endif
TEST (hash_test_start_new_hash_sha256_error);
#ifdef HASH_ENABLE_SHA384
TEST (hash_test_start_new_hash_sha384_error);
#endif
#ifdef HASH_ENABLE_SHA512
TEST (hash_test_start_new_hash_sha512_error);
#endif
TEST (hash_test_calculate_sha1);
TEST (hash_test_calculate_sha256);
TEST (hash_test_calculate_sha384);
TEST (hash_test_calculate_sha512);
TEST (hash_test_calculate_unknown);
TEST (hash_test_calculate_null);
#ifdef HASH_ENABLE_SHA1
TEST (hash_test_calculate_sha1_small_buffer);
#endif
TEST (hash_test_calculate_sha256_small_buffer);
#ifdef HASH_ENABLE_SHA384
TEST (hash_test_calculate_sha384_small_buffer);
#endif
#ifdef HASH_ENABLE_SHA512
TEST (hash_test_calculate_sha512_small_buffer);
#endif
TEST (hash_test_get_hash_length);
TEST (hash_test_get_hash_length_unsupported);
TEST (hash_test_hmac_get_hmac_length);
TEST (hash_test_hmac_get_hmac_length_unsupported);
TEST (hash_test_get_block_size);
TEST (hash_test_get_block_size_unsupported);
TEST (hash_test_is_alg_supported);
TEST (hash_test_run_self_test_sha1);
#ifdef HASH_ENABLE_SHA1
TEST (hash_test_run_self_test_sha1_mismatch_data_calculate);
TEST (hash_test_run_self_test_sha1_mismatch_data_update);
TEST (hash_test_run_self_test_sha1_null);
TEST (hash_test_run_self_test_sha1_calculate_fail);
TEST (hash_test_run_self_test_sha1_start_fail);
TEST (hash_test_run_self_test_sha1_update_first_fail);
TEST (hash_test_run_self_test_sha1_update_second_fail);
TEST (hash_test_run_self_test_sha1_finish_fail);
#endif
TEST (hash_test_run_self_test_sha256);
TEST (hash_test_run_self_test_sha256_mismatch_data_calculate);
TEST (hash_test_run_self_test_sha256_mismatch_data_update);
TEST (hash_test_run_self_test_sha256_null);
TEST (hash_test_run_self_test_sha256_calculate_fail);
TEST (hash_test_run_self_test_sha256_start_fail);
TEST (hash_test_run_self_test_sha256_update_first_fail);
TEST (hash_test_run_self_test_sha256_update_second_fail);
TEST (hash_test_run_self_test_sha256_finish_fail);
TEST (hash_test_run_self_test_sha384);
#ifdef HASH_ENABLE_SHA384
TEST (hash_test_run_self_test_sha384_mismatch_data_calculate);
TEST (hash_test_run_self_test_sha384_mismatch_data_update);
TEST (hash_test_run_self_test_sha384_null);
TEST (hash_test_run_self_test_sha384_calculate_fail);
TEST (hash_test_run_self_test_sha384_start_fail);
TEST (hash_test_run_self_test_sha384_update_first_fail);
TEST (hash_test_run_self_test_sha384_update_second_fail);
TEST (hash_test_run_self_test_sha384_finish_fail);
#endif
TEST (hash_test_run_self_test_sha512);
#ifdef HASH_ENABLE_SHA512
TEST (hash_test_run_self_test_sha512_mismatch_data_calculate);
TEST (hash_test_run_self_test_sha512_mismatch_data_update);
TEST (hash_test_run_self_test_sha512_null);
TEST (hash_test_run_self_test_sha512_calculate_fail);
TEST (hash_test_run_self_test_sha512_start_fail);
TEST (hash_test_run_self_test_sha512_update_first_fail);
TEST (hash_test_run_self_test_sha512_update_second_fail);
TEST (hash_test_run_self_test_sha512_finish_fail);
#endif
TEST (hash_test_run_all_self_tests);
TEST (hash_test_run_all_self_tests_mock);
TEST (hash_test_run_all_self_tests_null);
#ifdef HASH_ENABLE_SHA1
TEST (hash_test_run_all_self_tests_sha1_fail);
#endif
TEST (hash_test_run_all_self_tests_sha256_fail);
#ifdef HASH_ENABLE_SHA384
TEST (hash_test_run_all_self_tests_sha384_fail);
#endif
#ifdef HASH_ENABLE_SHA512
TEST (hash_test_run_all_self_tests_sha512_fail);
#endif
TEST (hash_test_hmac_run_self_test_sha1);
#ifdef HASH_ENABLE_SHA1
TEST (hash_test_hmac_run_self_test_sha1_mismatch_data_calculate);
TEST (hash_test_hmac_run_self_test_sha1_mismatch_data_update);
TEST (hash_test_hmac_run_self_test_sha1_null);
TEST (hash_test_hmac_run_self_test_sha1_calculate_fail);
TEST (hash_test_hmac_run_self_test_sha1_hmac_init_fail);
TEST (hash_test_hmac_run_self_test_sha1_update_first_fail);
TEST (hash_test_hmac_run_self_test_sha1_update_second_fail);
TEST (hash_test_hmac_run_self_test_sha1_finish_fail);
#endif
TEST (hash_test_hmac_run_self_test_sha256);
TEST (hash_test_hmac_run_self_test_sha256_mismatch_data_calculate);
TEST (hash_test_hmac_run_self_test_sha256_mismatch_data_update);
TEST (hash_test_hmac_run_self_test_sha256_null);
TEST (hash_test_hmac_run_self_test_sha256_calculate_fail);
TEST (hash_test_hmac_run_self_test_sha256_hmac_init_fail);
TEST (hash_test_hmac_run_self_test_sha256_update_first_fail);
TEST (hash_test_hmac_run_self_test_sha256_update_second_fail);
TEST (hash_test_hmac_run_self_test_sha256_finish_fail);
TEST (hash_test_hmac_run_self_test_sha384);
#ifdef HASH_ENABLE_SHA384
TEST (hash_test_hmac_run_self_test_sha384_mismatch_data_calculate);
TEST (hash_test_hmac_run_self_test_sha384_mismatch_data_update);
TEST (hash_test_hmac_run_self_test_sha384_null);
TEST (hash_test_hmac_run_self_test_sha384_calculate_fail);
TEST (hash_test_hmac_run_self_test_sha384_hmac_init_fail);
TEST (hash_test_hmac_run_self_test_sha384_update_first_fail);
TEST (hash_test_hmac_run_self_test_sha384_update_second_fail);
TEST (hash_test_hmac_run_self_test_sha384_finish_fail);
#endif
TEST (hash_test_hmac_run_self_test_sha512);
#ifdef HASH_ENABLE_SHA512
TEST (hash_test_hmac_run_self_test_sha512_mismatch_data_calculate);
TEST (hash_test_hmac_run_self_test_sha512_mismatch_data_update);
TEST (hash_test_hmac_run_self_test_sha512_null);
TEST (hash_test_hmac_run_self_test_sha512_calculate_fail);
TEST (hash_test_hmac_run_self_test_sha512_hmac_init_fail);
TEST (hash_test_hmac_run_self_test_sha512_update_first_fail);
TEST (hash_test_hmac_run_self_test_sha512_update_second_fail);
TEST (hash_test_hmac_run_self_test_sha512_finish_fail);
#endif
TEST (hash_test_hmac_run_all_self_tests);
TEST (hash_test_hmac_run_all_self_tests_mock);
TEST (hash_test_hmac_run_all_self_tests_null);
#ifdef HASH_ENABLE_SHA1
TEST (hash_test_hmac_run_all_self_tests_sha1_fail);
#endif
TEST (hash_test_hmac_run_all_self_tests_sha256_fail);
#ifdef HASH_ENABLE_SHA384
TEST (hash_test_hmac_run_all_self_tests_sha384_fail);
#endif
#ifdef HASH_ENABLE_SHA512
TEST (hash_test_hmac_run_all_self_tests_sha512_fail);
#endif

TEST_SUITE_END;
