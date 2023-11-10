#ifndef DPDKCAP_PARSE_H
#define DPDKCAP_PARSE_H

/**
 * @brief Parses the configuration from a file descriptor and calls the callback function
 *
 * This function approximates the following regular expressions:
 * s/#.*$//;
 * /^\s*([^\s:=])+(?:[\s:=])+(.*)\s*$/
 *
 * @param fd File descriptor of the configuration file
 * @param size Size of the configuration file
 * @param cb Callback function for handling key-value pairs
 * @param cbd User data for callback
 * @return 0 on success, -1 on failure
 */
int parse_config(int fd, ssize_t size, void (*cb)(char *, char *, void *),
				 void *);

#endif
