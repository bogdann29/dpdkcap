#ifndef DPDKCAP_STATISTICS_H
#define DPDKCAP_STATISTICS_H

#include "core_write.h"
#include "core_capture.h"

/**
 * @brief Structure to hold the statistics data.
 */
struct stats_data
{
	struct rte_ring *ring;								  /**< Pointer to the ring data structure. */
	struct core_write_stats **cores_stats_write_list;	  /**< Pointer to the list of core write statistics. */
	struct core_capture_stats **cores_stats_capture_list; /**< Pointer to the list of core capture statistics. */
	bool volatile *stop_condition;						  /**< Pointer to the list of core capture statistics. */
	unsigned int num_cores;								  /**< Number of cores. */
	unsigned int *port_list;							  /**< Pointer to the list of ports. */
	unsigned int port_list_size;						  /**< Size of the port list. */
	unsigned int queue_per_port;						  /**< Number of queues per port. */
	char *log_file;										  /**< Pointer to the log file. */
};

/**
 * @brief Starts displaying the statistics based on the provided data.
 * 
 * @param data Pointer to the statistics data.
 */
void start_stats_display(struct stats_data *data);

#endif
