#ifndef __STDC_WANT_LIB_EXT1__
#define __STDC_WANT_LIB_EXT1__ 1
#endif

#include "utils.h"
#include <stdio.h>
#include <stdint.h>
#include <string.h>

const char *bytes_unit[] = {"B", "KB", "MB", "GB", "TB"};
const char *nb_unit[] = {"k", "M", "G"};

char result[50];

/**
 * @brief Converts bytes to a human-readable format.
 *
 * @param bytes The number of bytes to be formatted.
 * @return A string representing the formatted bytes.
 */
char *bytes_format(uint64_t bytes)
{
	int i;
	double converted_bytes = bytes;
	for (i = 0; i < 4 && bytes >= 1024; i++, bytes /= 1024)
	{
		converted_bytes = bytes / 1024.0;
	}

	sprintf(result, "%.2f %s", converted_bytes, bytes_unit[i]);
	return result;
}

/**
 * @brief Formats an unsigned long integer to a human-readable format.
 *
 * @param nb The number to be formatted.
 * @return A string representing the formatted unsigned long integer.
 */
char *ul_format(uint64_t nb)
{
	int i;
	double converted_nb = nb;
	for (i = 0; i < 4 && nb >= 1000; i++, nb /= 1000)
	{
		converted_nb = nb / 1000.0;
	}
	if (i > 0)
		sprintf(result, "%.2f%s", converted_nb, nb_unit[i - 1]);
	else
		sprintf(result, "%d", (int)converted_nb);
	return result;
}

/**
 * @brief Replaces occurrences of a substring with another substring in a given string.
 *
 * @param src The source string in which to perform the replacement.
 * @param find The substring to be replaced.
 * @param replace The substring to replace 'find' with.
 * @return A pointer to the first occurrence of the 'find' substring in the 'src' string, or NULL if not found.s
 */
char *str_replace(const char *src, const char *find, const char *replace)
{
	int find_len, replace_len, src_left_length;
	char *pos = strstr(src, find);
	if (pos)
	{
		find_len = strlen(find);
		replace_len = strlen(replace);
		src_left_length = strlen(pos + find_len) + 1;

		memmove(pos + replace_len, pos + find_len, src_left_length);
		memmove(pos, replace, replace_len);
	}
	return pos;
}

/**
 * @brief Print information about the program's completion
 * 
 * @param reason reason for termination 
 */
void print_finish_log(char* reason) {
	FILE* f = fopen(FINISH_LOG_FILE_NAME, "w+");
	char* tm = get_cur_ISO_time();
	fprintf(f, "reason: %s\ntime: %s\n", reason, tm);
	fclose(f);
	free(tm);
}
