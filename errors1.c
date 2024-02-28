#include "shell.h"

/**
 * convert_int - will convert a string to an integer
 * @s: the string to be converted
 * Return: 0 if no numbers in string, converted number otherwise
 *       -1 on error
 */

/// @brief
/// @param s
/// @return
int convert_int(char *s)
{
	int i = 0;
	unsigned long int result = 0;

	if (*s == '+')
		s++;
	for (i = 0; s[i] != '\0'; i++)
	{
		if (s[i] >= '0' && s[i] <= '9')
		{
			result *= 10;
			result += (s[i] - '0');
			if (result > INT_MAX)
				return (-1);
		}
		else
			return (-1);
	}
	return (result);
}

/**
 * print_error - Will print an error message
 * @info: the parameter & return info struct
 * @estr: string containing specified error type
 * Return: 0 if no numbers in string, converted number otherwise
 *        -1 on error
 */

/// @brief
/// @param info
/// @param estr
void print_error(info_t *info, char *estr)
{
	print_inputs(info->fname);
	print_inputs(": ");
	print_decimal(info->line_count, STDERR_FILENO);
	print_inputs(": ");
	print_inputs(info-> argv[0]);
	print_inputs(": ");
	print_inputs(estr);
}

/**
 * print_decimal - function will print a  decimal (integer) number (base 10)
 * @input: the input
 * @fd: the filedescriptor to write to
 *
 * Return: number of characters printed
 */

/// @brief
/// @param input
/// @param fd
/// @return
int print_decimal(int input, int fd)
{
	int (*__putchar)(char) = _putchar;
	int d, count = 0;
	unsigned int _abs_, current;

	if (fd == STDERR_FILENO)
		__putchar = write_to_char;
	if (input < 0)
	{
		_abs_ = -input;
		__putchar('-');
		count++;
	}
	else
		_abs_ = input;
	current = _abs_;
	for (d = 1000000000; d > 1; d /= 10)
	{
		if (_abs_ / d)
		{
			__putchar('0' + current / d);
			count++;
		}
		current %= d;
	}
	__putchar('0' + current);
	count++;

	return (count);
}

/**
 * convert_number_ - converter function, a clone of itoa
 * @num: number
 * @base: base
 * @flags: argument flags
 *
 * Return: string
 */

/// @brief
/// @param num
/// @param base
/// @param flags
/// @return
char *convert_number_(long int num, int base, int flags)
{
	static char *array;
	static char buffer[50];
	char sign = 0;
	char *ptr;
	unsigned long n = num;

	if (!(flags & CONVERT_UNSIGNED) && num < 0)
	{
		n = -num;
		sign = '-';
	}
	array = flags & CONVERT_LOWERCASE ? "0123456789abcdef" : "0123456789ABCDEF";
	ptr = &buffer[49];
	*ptr = '\0';

	do {
		*--ptr = array[n % base];
		n /= base;
	} while (n != 0);

	if (sign)
		*--ptr = sign;
	return (ptr);
}

/**
 * delete_comments - function will replace first instance of '#' with '\0'
 * @buf: address of the string to modify
 *
 * Return: Always 0;
 */

/// @brief
/// @param buf
void delete_comments(char *buf)
{
	int d;

	for (d = 0; buf[d] != '\0'; d++)
		if (buf[d] == '#' && (!d || buf[d - 1] == ' '))
		{
			buf[d] = '\0';
			break;
		}
}
