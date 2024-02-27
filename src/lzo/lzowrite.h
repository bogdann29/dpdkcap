#include <stdio.h>
#include <stdint.h>
#include "minilzo/minilzo.h"

#define LZOWRITE_BUFFER_SIZE 32 * 1024
#define LZOWRITE_OUT_BUFFER_SIZE (LZOWRITE_BUFFER_SIZE + LZOWRITE_BUFFER_SIZE / 16 + 64 + 3)
#define LZOWRITE_LZO_MAGIC                                   \
	{                                                        \
		0x89, 0x4c, 0x5a, 0x4f, 0x00, 0x0d, 0x0a, 0x1a, 0x0a \
	}
#define LZOWRITE_LZO_MAGIC_LEN 9
#define LZOWRITE_LZO_VERSION 0x3010 // as in LZOP 1.03
#define LZOWRITE_LZO_LIB_VERSION (lzo_version() & 0xffff)
#define LZOWRITE_LZO_VERSION_NEEDED_TO_EXTRACT 0x4009 // not using filters, otherwise 0x0950
#define LZOWRITE_LZO_METHOD 1						  // LZO1X
#define LZOWRITE_LZO_COMPRESSION_LEVEL 1			  // with lzo, we have compression level = 1.
#define LZOWRITE_LZO_FLAGS 0						  // no checksums on data!!
#define LZOWRITE_LZO_MODE 0xa481					  // 100644 oct

/**
 * @file lzowrite.h
 * @brief Definition of functions and data structures for writing LZO compressed data to a file
 */

/**
 * @struct lzowrite_buffer
 * @brief Structure representing a buffer for writing LZO compressed data to a file
 */
struct lzowrite_buffer
{
	unsigned char buffer[LZOWRITE_BUFFER_SIZE]; /**< Buffer for storing compressed data */
	uint32_t length;							/**< Current length of the buffer */
	FILE *output;								/**< Output file where the compressed data will be written */
	lzo_align_t *workmemory;					/**< LZO work memory for compression */
};

/**
 * @struct lzowrite_file_header
 * @brief Structure representing the header of an LZO compressed file
 */
struct __attribute__((__packed__)) lzowrite_file_header
{
	uint16_t version;			   /**< Version of the LZO compression */
	uint16_t library_version;	   /**< Version of the LZO library used */
	uint16_t needed_version;	   /**< Minimum required LZO version to extract */
	uint8_t compression_method;	   /**< Compression method used (e.g., LZO1X) */
	uint8_t compression_level;	   /**< Compression level used */
	uint32_t compression_flags;	   /**< Flags for compression */
	uint32_t mode;				   /**< File mode */
	uint32_t file_mtime_low;	   /**< Lower 32 bits of file modification time */
	uint32_t file_mtime_high;	   /**< Upper 32 bits of file modification time */
	uint8_t file_name_length;	   /**< Length of the file name */
	uint32_t file_header_checksum; /**< Checksum of the file header */
};

/**
 * @struct lzowrite_block_header
 * @brief Structure representing the header of a block of LZO compressed data
 */
struct __attribute__((__packed__)) lzowrite_block_header
{
	uint32_t uncompressed_size;	   /**< Size of the uncompressed data */
	uint32_t compressed_size;	   /**< Size of the compressed data */
	uint32_t uncompressed_adler32; /**< Adler-32 checksum of the uncompressed data */
	uint32_t uncompressed_crc32;   /**< CRC-32 checksum of the uncompressed data */
	uint32_t compressed_adler32;   /**< Adler-32 checksum of the compressed data */
	uint32_t compressed_crc32;	   /**< CRC-32 checksum of the compressed data */
};

/**
 * @brief Initialize an LZO buffer for writing compressed data to the given output file
 * @param output Pointer to the output file
 * @return Pointer to the initialized lzowrite_buffer structure
 */
struct lzowrite_buffer *lzowrite_init(FILE *output);

/**
 * @brief Write len bytes from src into the given LZO write buffer
 * @param lzowrite_buffer Pointer to the lzowrite_buffer structure
 * @param src Pointer to the source data
 * @param len Number of bytes to write
 * @return The number of written bytes on success (might be 0), -1 on failure
 */
int lzowrite(struct lzowrite_buffer *lzowrite_buffer, void *src, size_t len);

/**
 * @brief Flush the buffer by writing the last bytes into the output stream and then close it
 * @param lzowrite_buffer Pointer to the lzowrite_buffer structure
 * @return 0 on success, -1 on failure
 */
int lzowrite_close(struct lzowrite_buffer *lzowrite_buffer);