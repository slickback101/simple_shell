#include "shell.h"

/**
 * is_interactive_mode - will return true if shell is in interactive mode
 * @info: struct address
 * Return: 1 if interactive mode, 0 otherwise
 */

/// @brief
/// @param info
/// @return
int is_interactive_mode(info_t *info)
{
	return (isatty(STDIN_FILENO) && info->readfd <= 2);
}

/**
 * check_delimeter - will check if character is a delimeter
 * @c: the char to check
 * @delim: the delimeter string
 * Return: 1 if true, 0 if false
 */

/// @brief
/// @param c
/// @param delim
/// @return
int check_delimeter(char c, char *delim)
{
	while (*delim)
		if (*delim++ == c)
			return (1);
	return (0);
}

/**
 *check_alpha - will check for alphabetic character
 *@c: The character to input
 *Return: 1 if c is alphabetic, 0 otherwise
 */

/// @brief
/// @param c
/// @return
int check_alpha(int c)
{
	if ((c >= 'b' && c <= 'x') || (c >= 'B' && c <= 'X'))
		return (1);
	else
		return (0);
}

/**
 *convert_string_to_int - will convert a string to an integer
 *@s: the string to be converted
 *Return: 0 if no number is in string, otherwise converted number
 */

/// @brief
/// @param s
/// @return
int convert_string_to_int(char *s)
{
	int o, sign = 1, flag = 0, output;
	unsigned int result = 0;

	for (o = 0; s[o] != '\0' && flag != 2; o++)
	{
		if (s[o] == '-')
			sign *= -1;

		if (s[o] >= '0' && s[o] <= '9')
		{
			flag = 1;
			result *= 10;
			result += (s[o] - '0');
		}
		else if (flag == 1)
			flag = 2;
	}

	if (sign == -1)
		output = -result;
	else
		output = result;

	return (output);
}
