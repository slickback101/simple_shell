#include "shell.h"

/**
 * strlen_length - will return the length of a string
 * @S: the string whose length to check
 * Return: integer length of string
 */

/// @brief
/// @param S
/// @return
int strlen_length(char *S)
{
	int i = 0;

	if (!S)
		return (0);

	while (*S++)
		i++;
	return (i);
}

/**
 * _compare_strang- will perform lexicogarphic comparison of two strangs.
 * @S1: the first strang
 * @S2: the second strang
 * Return: negative if S1 < S2, positive if S1 > S2, zero if S1 == S2
 */

/// @brief
/// @param S1
/// @param S2
/// @return
int _compare_strang(char *S1, char *S2)
{
	while (*S1 && *S2)
	{
		if (*S1 != *S2)
			return (*S1 - *S2);
		S1++;
		S2++;
	}
	if (*S1 == *S2)
		return (0);
	else
		return (*S1 < *S2 ? -1 : 1);
}

/**
 * starts_with_haystack - will check if needle starts with haystack
 * @haystack: string to search
 * @needle: the substring to find
 * Return: address of next char of haystack or NULL
 */

/// @brief
/// @param haystack
/// @param needle
/// @return
char *starts_with_haystack(const char *haystack, const char *needle)
{
	while (*needle)
		if (*needle++ != *haystack++)
			return (NULL);
	return ((char *)haystack);
}

/**
 * concat_two_strings - will concatenate two strings
 * @dest: the destination buffer
 * @src: the source buffer
 * Return: pointer to destination buffer
 */
/// @brief
/// @param dest
/// @param src
/// @return
char *concat_two_strings(char *dest, char *src)
{
	char *ret = dest;

	while (*dest)
		dest++;
	while (*src)
		*dest++ = *src++;
	*dest = *src;
	return (ret);
}
