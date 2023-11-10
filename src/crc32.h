#include <stdint.h>

#include <sys/cdefs.h>

#include <sys/param.h>

uint32_t
calculate_crc32c(uint32_t crc32c,
                 const unsigned char *buffer,
                 unsigned int length);