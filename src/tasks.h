#ifndef DPDKCAP_TASKS_H
#define DPDKCAP_TASKS_H

#include <sys/types.h>
#include <sys/stat.h>

#include <rte_bpf.h>
#include <rte_errno.h>
#include <pcap/pcap.h>
#include <pcap/bpf.h>

#define DPDKCAP_MAX_PATH_LEN 1024
#define DPDKCAP_MAX_FILE_LEN 256

#define DPDKCAP_MAX_BPF_LEN 1024

#define DPDKCAP_MAX_TASKS_PER_DIR 16

#define DPDKCAP_OUTPUT_TEMPLATE_TOKEN_FILECOUNT "\%FCOUNT"
#define DPDKCAP_OUTPUT_TEMPLATE_TOKEN_CORE_ID "\%COREID"
#define DPDKCAP_OUTPUT_TEMPLATE_DEFAULT "output_" DPDKCAP_OUTPUT_TEMPLATE_TOKEN_CORE_ID

#define DPDKCAP_OUTPUT_TEMPLATE_LENGTH 2 * DPDKCAP_OUTPUT_FILENAME_LENGTH

/**
 * @brief Enumeration representing the possible states of a task.
 *
 */
enum task_state_t
{
	TASK_UNUSED,
	TASK_INACTIVE,
	TASK_ACTIVE,
};

/**
 * @brief Structure representing a task.
 *
 */
struct task
{
	enum task_state_t task_state; /**< State of the task. */
	time_t task_seen;			  /**< Time when the task was last seen. */

	char task_filename[DPDKCAP_MAX_FILE_LEN]; /**< Filename associated with the task. */
	time_t task_mtime;						  /**< Time of the last modification of the file. */
	size_t task_size;						  /**< Size of the file. */

	char output_template[DPDKCAP_MAX_PATH_LEN]; /**< Output template for the task. */
	int output_rotate_seconds;					/**< Rotation time in seconds. Time after which it is necessary to change the output file */
	size_t output_rotate_size;					/**< Rotation size for output. Size after reaching which you need to change the output file */

	char output_filename[DPDKCAP_MAX_PATH_LEN]; /**< Output filename. */
	void *output_buffer;						/**< Buffer for output data. */
	struct timeval output_tstamp;				/**< Timestamp for output. */
	size_t output_size;							/**< Size of the output file. */
	int output_count;							/**< Count of output files. */

	char bpf_str[DPDKCAP_MAX_BPF_LEN]; /**< BPF filter string. */
	struct rte_bpf *bpf;			   /**< BPF filter. */
	int snaplen;					   /**< Packet snapshot length. */
	int compression;				   /**< Compression flag. */
	int sampling;					   /**< Sampling flag. */
};

/**
 * @brief Structure representing a directory of tasks.
 *
 */
struct taskdir
{
	time_t lastscan; /**< Time of the last scan. */
	int interval;	 /**< Interval for scanning. */

	char dirname[DPDKCAP_MAX_PATH_LEN]; /**< Name of the directory. */

	struct task tasks[DPDKCAP_MAX_TASKS_PER_DIR]; /**< Array of tasks within the directory. */
};

/**
 * @brief Scans a directory by file descriptor and invokes a callback for each entry.
 *
 * @param dirfd The file descriptor of the directory to scan.
 * @param cb The callback function to invoke for each entry.
 * @param cbd An additional user-defined argument to be passed to the callback function.
 */
void scan_by_fd(int dirfd, void (*cb)(char *, int, struct stat *, void *),
				void *cbd);

/**
 * @brief Scans a directory by name and invokes a callback for each entry.
 *
 * @param dirname The name of the directory to scan.
 * @param cb The callback function to invoke for each entry.
 * @param cbd An additional user-defined argument to be passed to the callback function.
 */
void scan_by_name(char *dirname, void (*cb)(char *, int, struct stat *, void *),
				  void *cbd);

/**
 * @brief Checks and scans a task directory based on the specified parameters.
 *
 * @param td Pointer to the task directory structure.
 * @param now Current time value for checking and scanning.
 */
void check_scan_taskdir(struct taskdir *td, int now);

#endif
