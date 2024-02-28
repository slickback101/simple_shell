#include "shell.h"

/**
 **_ismemset - will fill the memory with a constant byte
 *@s: the pointer to the memory area
 *@b: the byte to fill *s with
 *@n: the amount of bytes to be filled
 *Return: (s) a pointer to the memory area s
 */

/// @brief
/// @param s
/// @param b
/// @param n
/// @return
char *_ismemset(char *s, char b, unsigned int n)
{
	unsigned int m;

	for (m = 0; m < n; m++)
		s[m] = b;
	return (s);
}

/**
 * ffree - will free a string of strings
 * @pp: the string of strings
 */

/// @brief
/// @param pp
void ffree(char **pp)
{
	char **a = pp;

	if (!pp)
		return;
	while (*pp)
		free(*pp++);
	free(a);
}

/**
 * _realloc - will reallocate a block of memory
 * @ptr: pointer to previous malloc'ated block
 * @old_size: the byte size of previous block
 * @new_size: the byte size of new block
 *
 * Return: pointer to da ol'block nameen.
 */

/// @brief
/// @param ptr
/// @param old_size
/// @param new_size
/// @return
void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size)
{
	char *r;

	if (!ptr)
		return (malloc(new_size));
	if (!new_size)
		return (free(ptr), NULL);
	if (new_size == old_size)
		return (ptr);

	r = malloc(new_size);
	if (!r)
		return (NULL);

	old_size = old_size < new_size ? old_size : new_size;
	while (old_size--)
		r[old_size] = ((char *)ptr)[old_size];
	free(ptr);
	return (r);
}
