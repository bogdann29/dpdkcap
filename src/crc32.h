#include <stdint.h>
#include <sys/cdefs.h>
#include <sys/param.h>

/**
 * @file crc32.h
 * @brief Calculating cyclic redundancy check to hash packet data
 *
 */

/**
 * @brief Calculate CRC32C checksum for the input buffer
 *
 * This function selects the appropriate method based on the length of the input buffer.
 *
 * @param crc32c Initial CRC value
 * @param buffer Pointer to the input buffer
 * @param length Length of the input buffer
 * @return Calculated CRC value
 */
uint32_t
calculate_crc32c(uint32_t crc32c,
                 const unsigned char *buffer,
                 unsigned int length);