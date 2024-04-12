// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT license.

#ifndef BUFFER_UTIL_H_
#define BUFFER_UTIL_H_

#include <stdint.h>
#include <stddef.h>
#include "status/rot_status.h"


/**
 * Check if two buffers overlap.
 *
 * @param buf1 Pointer start address of first buffer.
 * @param buf1_len Length of first buffer.
 * @param buf2 Pointer start address of second buffer.
 * @param buf2_len Length of second buffer.
 *
 * @return 0 if the buffers do not overlap, 1 if they do.
 */
#define buffer_are_overlapping(buf1, buf1_len, buf2, buf2_len) \
	(((buf1 >= buf2) && (buf1 < (buf2 + buf2_len))) || \
		((buf2 >= buf1) && (buf2 < (buf1 + buf1_len))))


size_t buffer_copy (const uint8_t *src, size_t src_length, size_t *offset, size_t *dest_length,
	uint8_t *dest);
void buffer_reverse (uint8_t *buffer, size_t length);
void buffer_reverse_copy (uint8_t *dest, const uint8_t *src, size_t length);
int buffer_reverse_copy_dwords (uint32_t *dest, const uint32_t *src, size_t length);

int buffer_compare (const uint8_t *buf1, const uint8_t *buf2, size_t length);
int buffer_compare_dwords (const uint32_t *buf1, const uint32_t *buf2, size_t dwords);

void buffer_zeroize (void *buffer, size_t length);

void buffer_unaligned_copy16 (uint16_t *dst, const uint16_t *src);
void buffer_unaligned_copy24 (uint8_t *dst, const uint8_t *src);
void buffer_unaligned_copy32 (uint32_t *dst, const uint32_t *src);
void buffer_unaligned_copy64 (uint64_t *dst, const uint64_t *src);

uint16_t buffer_unaligned_read16 (const uint16_t *buffer);
uint32_t buffer_unaligned_read24 (const uint8_t *buffer);
uint32_t buffer_unaligned_read32 (const uint32_t *buffer);
uint64_t buffer_unaligned_read64 (const uint64_t *buffer);

void buffer_unaligned_write16 (uint16_t *buffer, uint16_t value);
void buffer_unaligned_write24 (uint8_t *buffer, uint32_t value);
void buffer_unaligned_write32 (uint32_t *buffer, uint32_t value);
void buffer_unaligned_write64 (uint64_t *buffer, uint64_t value);


#define	BUFFER_UTIL_ERROR(code)		ROT_ERROR (ROT_MODULE_BUFFER_UTIL, code)

/**
 * Error codes that can be generated by buffer utilities.
 */
enum {
	BUFFER_UTIL_INVALID_ARGUMENT = BUFFER_UTIL_ERROR (0x00),		/**< Input parameter is null or not valid. */
	BUFFER_UTIL_NO_MEMORY = BUFFER_UTIL_ERROR (0x01),				/**< Memory allocation failed. */
	BUFFER_UTIL_DATA_MISMATCH = BUFFER_UTIL_ERROR (0x02),			/**< A buffer does not contain the expected data. */
	BUFFER_UTIL_UNEXPETCED_ALIGNMENT = BUFFER_UTIL_ERROR (0x03),	/**< Detected unexpected buffer address alignment. */
};


#endif /* BUFFER_UTIL_H_ */
