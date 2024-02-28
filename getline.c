#include "shell.h"
#include <stdlib.h>

/**
 * input_buffer - will buffer a chained commands
 * @info: parameter of struct
 * @buf: address of buffer
 * @len: address of len var
 * Return: bytes read
 */

/// @brief
/// @param info
/// @param buf
/// @param len
/// @return
ssize_t input_buffer(info_t *info, char **buf, size_t *len)
{
	ssize_t b = 0;
	size_t len_p = 0;

	if (!*len)
	{
		free(*buf);
		*buf = NULL;
		signal(SIGINT, sig_int_Handlers);
#if USE_GETLINE
		b = getline(buf, &len_p, stdin);
#else
		b = _get_next_line(info, buf, &len_p);
#endif
		if (b > 0)
		{
			if ((*buf)[b - 1] == '\n')
			{
				(*buf)[b - 1] = '\0'; /* this will remove trailing newline */
				b--;
			}
			info-> linecount_flag = 1;
			delete_comments(*buf);
			build_my_history_list(info, *buf, info-> histcount += 1);
			{
				*len = b;
				info-> cmd_buf = buf;
			}
		}
	}
	return (b);
}

/**
 * get_inputs - This will get a line minus the newline
 * @info: parameter struct
 * Return: bytes read
 */

/// @brief
/// @param info
/// @return
ssize_t get_inputs(info_t *info)
{
	static char *buf;
	static size_t i, g, len;
	ssize_t s = 0;
	char **buf_p = &(info-> arg), *p;

	_putchar(BUF_FLUSH);
	s = input_buffer(info, &buf, &len);
	if (s == -1) /* EOF */
		return (-1);
	if (len)
	{
		g = i;
		p = buf + i;

		verify_chain(info, buf, &g, i, len);
		while (g < len)
		{
			if (is_separated(info, buf, &g))
				break;
			g++;
		}

		i = g + 1;
		if (i >= len)
		{
			i = len = 0;
			info->cmd_buf_type = CMD_NORM;
		}

		*buf_p = p;
		return (strlen_length(p));
	}

	*buf_p = buf;
	return (s);
}

/**
 * read_buffers - will read a buffer
 * @info: parameter struct
 * @buf: buffer
 * @i: size
 * Return: r
 */

/// @brief
/// @param info
/// @param buf
/// @param i
/// @return
ssize_t read_buffers(info_t *info, char *buf, size_t *i)
{
	ssize_t r = 0;

	if (*i)
		return (0);
	r = read(info->readfd, buf, READ_BUF_SIZE);
	if (r >= 0)
		*i = r;
	return (r);
}

/**
 * _get_next_line - will get  the next line of a input from STDIN
 * @info: parameter struct
 * @ptr: the address of pointer to buffer, preallocated or NULL
 * @length: size of preallocated ptr buffer if not NULL
 *
 * Return: s
 */

/// @brief
/// @param info
/// @param ptr
/// @param length
/// @return
int _get_next_line(info_t *info, char **ptr, size_t *length)
{
	static char buf[READ_BUF_SIZE];
	static size_t i, len;
	size_t k;
	ssize_t r = 0, s = 0;
	char *p = NULL, *new_p = NULL, *c;

	p = *ptr;
	if (p && length)
		s = *length;
	if (i == len)
		i = len = 0;

	r = read_buffers(info, buf, &len);
	if (r == -1 || (r == 0 && len == 0))
		return (-1);

	c = find_char_in_string(buf + i, '\n');
	k = c ? 1 + (unsigned int)(c - buf) : len;
	new_p = _realloc(p, s, s ? s + k : k + 1);
	if (!new_p) /* MALLOC FAILURE! */
		return (p ? free(p), -1 : -1);

	if (s)
		concat_string(new_p, buf + i, k - i);
	else
		copy_str(new_p, buf + i, k - i + 1);

	s += k - i;
	i = k;
	p = new_p;

	if (length)
		*length = s;
	*ptr = p;
	return (s);
}

/**
 * sig_int_Handlers- blocks ctrl-C
 * @sig_num: the signal number
 *
 * Return: void
 */

/// @brief
/// @param sig_num
void sig_int_Handlers(__attribute__((unused)) int sig_num)
{
	prints_input_string("\n");
	prints_input_string("$ ");
	_putchar(BUF_FLUSH);
}
