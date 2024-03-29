#include "shell.h"

/**
 * copy_string - will copy a string
 * @dest: the destination
 * @src: the source
 * Return: pointer to destination
 */

char *copy_string(char *dest, char *src)
{
	int C = 0;

	if (dest == src || src == 0)
		return (dest);
	while (src[C])
	{
		dest[C] = src[C];
		C++;
	}
	dest[C] = 0;
	return (dest);
}

/**
 * duplicate_string - will duplicate a string
 * @str: the string to duplicate
 * Return: pointer to the duplicated string
 */

char *duplicate_string(const char *str)
{
	int length = 0;
	char *ret;

	if (str == NULL)
		return (NULL);
	while (*str++)
		length++;
	ret = malloc(sizeof(char) * (length + 1));
	if (!ret)
		return (NULL);
	for (length++; length--;)
		ret[length] = *--str;
	return (ret);
}

/**
 *prints_input_string - will print an input string
 *@str: the string to be printed
 * Return: Nothing
 */

void prints_input_string(char *str)
{
	int i = 0;

	if (!str)
		return;
	while (str[i] != '\0')
	{
		_putchar(str[i]);
		i++;
	}
}

/**
 * _putchar - will write the character c to stdout
 * @c: The character to print
 * Return: On success 1.
 * On error, -1 is returned, and errno is set appropriately.
 */

int _putchar(char c)
{
	static int i;
	static char buf[WRITE_BUF_SIZE];

	if (c == BUF_FLUSH || i >= WRITE_BUF_SIZE)
	{
		write(1, buf, i);
		i = 0;
	}
	if (c != BUF_FLUSH)
		buf[i++] = c;
	return (1);
}
