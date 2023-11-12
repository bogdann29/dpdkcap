
#include "timestamp.h"

/**
 * Offset of the dynamic timestamp field in the mbuf.
 */
static int timestamp_dynfield_offset = -1;

/**
 * Flag representing the presence of the timestamp dynamic field in the mbuf.
 */
static uint64_t timestamp_dynfield_flag = 0;

/**
 * @brief Retrieves a pointer to the timestamp field in the given mbuf.
 *
 * @param mbuf Pointer to the rte_mbuf structure.
 * @return A pointer to the timestamp field, or NULL if not found.
 */
inline uint64_t *timestamp_field(struct rte_mbuf *mbuf)
{
	return RTE_MBUF_DYNFIELD(mbuf, timestamp_dynfield_offset,
							 rte_mbuf_timestamp_t *);
}

/**
 * @brief Registers the timestamp dynamic field in the mbuf.
 *
 */
void register_timestamp_dynfield()
{
	rte_mbuf_dyn_rx_timestamp_register(&timestamp_dynfield_offset,
									   &timestamp_dynfield_flag);
	if (timestamp_dynfield_offset < 0)
	{
		printf("ERROR: Failed to register timestamp field\n");
		rte_exit(1, "dynfield register failed");
	}
}
