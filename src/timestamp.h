#ifndef DPDKCAP_TIMESTAMP_H
#define DPDKCAP_TIMESTAMP_H

#include <sys/time.h>

#include <rte_mbuf.h>
#include <rte_mbuf_dyn.h>
#include <rte_time.h>

#define DATE_TEMPLATE "yyyy-mm-ddThh:mm:ssZ+03:00"

/**
 * @file timestamp.h
 * @brief Definition functions for registering and retrieving timestamps
 *
 */

/**
 * @brief Retrieves a pointer to the timestamp field in the given mbuf.
 *
 * @param mbuf Pointer to the rte_mbuf structure.
 * @return A pointer to the timestamp field, or NULL if not found.
 */
uint64_t *timestamp_field(struct rte_mbuf *mbuf);

/**
 * @brief Registers the timestamp dynamic field in the mbuf.
 *
 */
void register_timestamp_dynfield();

/**
 * @brief Get the current ISO time string 
 * 
 * @return char* 
 */
char* get_cur_ISO_time();

/**
 * @brief Get the current ISO time string
 *
 * @return char*
 */
char *get_cur_ISO_time();

#endif
