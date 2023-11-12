#ifndef SHA256_H
#define SHA256_H

/*************************** HEADER FILES ***************************/
#include <stddef.h>
#include <stdint.h>

/****************************** MACROS ******************************/
#define SHA256_BLOCK_SIZE 32    /**< Size of a SHA-256 block in bytes. */

/**************************** DATA TYPES ****************************/
typedef unsigned char uint8_t;/**< Unsigned 8-bit type. */
typedef unsigned int uint32_t; /**< Unsigned 32-bit type. */

typedef struct
{
    uint8_t data[64];
    uint32_t datalen;
    unsigned long long bitlen;
    uint32_t state[8];
} SHA256_CTX; /**< Structure to hold the SHA-256 context. */

/*********************** FUNCTION DECLARATIONS **********************/

/**
 * @brief Initializes the SHA-256 context.
 * 
 * @param ctx Pointer to the SHA256_CTX structure to be initialized.
 */
void sha256_init(SHA256_CTX *ctx);

/**
 * @brief Updates the SHA-256 hashing context with the given data.
 * 
 * @param ctx Pointer to the SHA256_CTX structure representing the current context.
 * @param data Pointer to the input data to be hashed.
 * @param len Length of the input data in bytes.
 */
void sha256_update(SHA256_CTX *ctx, const uint8_t data[], size_t len);

/**
 * @brief Finalizes the SHA-256 hashing process and retrieves the hash value.
 * 
 * @param ctx Pointer to the SHA256_CTX structure representing the current context.
 * @param hash Buffer to store the resulting hash value.
 */
void sha256_final(SHA256_CTX *ctx, uint8_t hash[]);

/**
 * @brief Computes the SHA-256 hash of the input text.
 * 
 * @param text Pointer to the input text to be hashed.
 * @param buf Buffer to store the resulting hash value.
 * @param length Length of the input text in bytes.
 */
void sha256(uint8_t *text, uint8_t *buf, size_t length);

#endif // SHA256_H
