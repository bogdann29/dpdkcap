/**
 * @file core_write.h
 * @brief Contains structures and function prototypes for writing core
 */

#ifndef DPDKCAP_CORE_WRITE_H
#define DPDKCAP_CORE_WRITE_H

#include <stdbool.h>
#include <stdint.h>
#include "tasks.h"

#define DPDKCAP_OUTPUT_FILENAME_LENGTH 100
#define DPDKCAP_WRITE_BURST_SIZE 256

/**
 * @struct core_write_config
 * @brief Writing core configuration
 */
struct core_write_config
{
	struct rte_ring *ring;			/**< Pointer to the ring */
	bool volatile *stop_condition;	/**< Pointer to the stop condition flag */
	struct core_write_stats *stats; /**< Pointer to the statistics structure */
	struct taskdir *taskdir;		/**< Pointer to the task directory structure */
};

/**
 * @struct core_write_stats
 * @brief Statistics structure
 */
struct core_write_stats
{
	int core_id;									  /**< Core ID */
	char output_file[DPDKCAP_OUTPUT_FILENAME_LENGTH]; /**< Output file name */
	uint64_t current_file_packets;					  /**< Number of packets in the current file */
	uint64_t current_file_bytes;					  /**< Number of bytes in the current file */
	uint64_t current_file_compressed_bytes;			  /**< Number of compressed bytes in the current file */
	uint64_t packets;								  /**< Total number of packets */
	uint64_t bytes;									  /**< Total number of bytes */
	uint64_t compressed_bytes;						  /**< Total number of compressed bytes */
};

/**
 * @brief Write the packets from the write ring into a pcap compressed file
 *
 * @param config Pointer to the core_write_config structure
 * @return 0 on success, -1 on failure
 */
int write_core(const struct core_write_config *config);

#endif