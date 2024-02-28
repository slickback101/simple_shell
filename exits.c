#include "shell.h"

/**
 **copy_string - Will copy a string
 *@dest: the destination string to be copied to
 *@src: the source string
 *@n: the amount of characters to be copied
 *Return: the concatenated string
 */

/// @brief
/// @param dest
/// @param src
/// @param n
/// @return
char *copy_str(char *dest, char *src, int n)
{
	int c, s;
	char *s = dest;

	c = 0;
	while (src[c] != '\0' && c < n - 1)
	{
		dest[c] = src[c];
		c++;
	}
	if (c < n)
	{
		s = c;
		while (s < n)
		{
			dest[s] = '\0';
			s++;
		}
	}
	return (s);
}

/**
 **concat_string - Will concatenate two strings
 *@dest: the first string
 *@src: the second string
 *@n: the amount of bytes to be maximally used
 *Return: the concatenated string
 */

/// @brief
/// @param dest
/// @param src
/// @param n
/// @return
char *concat_string(char *dest, char *src, int n)
{
	int i, j;
	char *s = dest;

	i = 0;
	j = 0;
	while (dest[i] != '\0')
		i++;
	while (src[j] != '\0' && j < n)
	{
		dest[i] = src[j];
		i++;
		j++;
	}
	if (j < n)
		dest[i] = '\0';
	return (s);
}

/**
 **find_char_in_string - locates a character in a string
 *@s: the string to be parsed
 *@c: the character to look for
 *Return: (s) a pointer to the memory area s
 */

/// @brief
/// @param s
/// @param c
/// @return
char *find_char_in_string(char *s, char c)
{
	do {
		if (*s == c)
			return (s);
	} while (*s++ != '\0');

	return (NULL);
}
