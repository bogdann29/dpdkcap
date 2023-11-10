
/**
 * @brief Retrieves the stopper flag for a specified socket
 *
 * @param socket Socket ID
 * @return Pointer to the stopper flag, or NULL if not found
 */
volatile bool *get_stopper_for_socket(int socket);

/**
 * @brief Stops all sockets by setting the should_stop flag to true
 */
void stop_all_sockets();

/**
 * @brief Gets the core ID for a given socket
 *
 * @param socket Socket ID
 * @return Core ID associated with the socket, or -1 if not found
 */
int get_core_on_socket(int socket);