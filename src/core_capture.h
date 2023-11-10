#ifndef DPDKCAP_CORE_CAPTURE_H
#define DPDKCAP_CORE_CAPTURE_H

#include <stdint.h>

#define DPDKCAP_CAPTURE_BURST_SIZE 256

/* Core configuration structures */
/**
 * @struct core_capture_config
 * @brief Configuration for core capturing traffic
 */
struct core_capture_config
{
	struct rte_ring *ring;			  /**< Ring buffer for storing captured packets */
	bool volatile *stop_condition;	  /**< Pointer to stop condition flag */
	struct core_capture_stats *stats; /**< Pointer to statistics structure */
	uint8_t port;					  /**< Port to capture traffic from */
	uint8_t queue;					  /**< Queue to capture traffic from */
};

/* Statistics structure */
/**
 * @struct core_capture_stats
 * @brief Statistics for core capturing traffic
 */
struct core_capture_stats
{
	int core_id;			 /**< Core ID of the capturing task */
	uint64_t packets;		 /**< Packets successfully enqueued */
	uint64_t missed_packets; /**< Packets core could not enqueue */
};

/* Launches a capture task */
/**
 * @brief Capture the traffic from the given port/queue tuple
 * @param config The capture configuration
 * @return 0 on success, -1 on failure
 */
int capture_core(const struct core_capture_config *config);

#endif
