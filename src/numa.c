
#include <rte_lcore.h>
#include <rte_memory.h>
#include <rte_malloc.h>

#define MAX_LSOCKS 20

struct lsock
{
	int socket_id;			   /**< Socket ID */
	volatile bool should_stop; /**< Flag indicating whether the socket should stop */
};

struct lsock *lsocks[MAX_LSOCKS]; /**< Array of pointers to lsock structures */

/**
 * @brief Retrieves the stopper flag for a specified socket
 *
 * @param socket Socket ID
 * @return Pointer to the stopper flag, or NULL if not found
 */
volatile bool *get_stopper_for_socket(int socket)
{
	int i;
	for (i = 0; i < MAX_LSOCKS; i++)
	{
		if (!(lsocks[i] == NULL))
		{
			if (lsocks[i]->socket_id == socket)
			{
				return &lsocks[i]->should_stop;
			}
			else
			{
				continue;
			}
		}
		// need to summon a new one
		lsocks[i] =
			rte_zmalloc_socket("STOPPER", sizeof(struct lsock), 0,
							   socket);
		lsocks[i]->socket_id = socket;
		return &lsocks[i]->should_stop;
	}
	return NULL;
}

/**
 * @brief Stops all sockets by setting the should_stop flag to true
 */
void stop_all_sockets()
{
	int i;
	for (i = 0; i < MAX_LSOCKS; i++)
	{
		if (!(lsocks[i] == NULL))
		{
			lsocks[i]->should_stop = true;
		}
	}
}

/**
 * @brief Gets the core ID for a given socket
 *
 * @param socket Socket ID
 * @return Core ID associated with the socket, or -1 if not found
 */
int get_core_on_socket(int socket)
{
	unsigned core;

	RTE_LCORE_FOREACH_WORKER(core)
	{
		enum rte_lcore_state_t status = rte_eal_get_lcore_state(core);
		if ((status == WAIT) &&
			((socket == SOCKET_ID_ANY) || (rte_lcore_to_socket_id(core) == socket)))
		{
			return core;
		}
	}
	return -1;
}
