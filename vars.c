#include "shell.h"

/**
 * is_separated - will test if current char in buffer is a chain delimeter
 * @info: the parameter struct
 * @buf: the char buffer
 * @p: address of current position in buf
 * Return: 1 if chain delimeter, 0 otherwise
 */

/// @brief
/// @param info
/// @param buf
/// @param p
/// @return
int is_separated(info_t *info, char *buf, size_t *p)
{
	size_t j = *p;

	if (buf[j] == '|' && buf[j + 1] == '|')
	{
		buf[j] = 0;
		j++;
		info-> cmd_buf_type = CMD_OR;
	}
	else if (buf[j] == '&' && buf[j + 1] == '&')
	{
		buf[j] = 0;
		j++;
		info-> cmd_buf_type = CMD_AND;
	}
	else if (buf[j] == ';')
	{
		buf[j] = 0;
		info-> cmd_buf_type = CMD_CHAIN;
	}
	else
		return (0);
	*p = j;
	return (1);
}

/**
 * verify_chain - will check we should continue chaining based on last status
 * @info: the parameter struct
 * @buf: the char buffer
 * @p: address of current position in buf
 * @i: starting position in buf
 * @len: length of buf
 * Return: Void
 */

/// @brief
/// @param info
/// @param buf
/// @param p
/// @param i
/// @param len
void verify_chain(info_t *info, char *buf, size_t *p, size_t i, size_t len)
{
	size_t j = *p;

	if (info-> cmd_buf_type == CMD_AND)
	{
		if (info-> status)
		{
			buf[i] = 0;
			j = len;
		}
	}
	if (info-> cmd_buf_type == CMD_OR)
	{
		if (!info-> status)
		{
			buf[i] = 0;
			j = len;
		}
	}
	*p = j;
}

/**
 * substitue_alias - will substitute an aliases in the tokenized string
 * @info: the parameter struct
 * Return: 1 if replaced, 0 otherwise
 */

/// @brief
/// @param info
/// @return
int substitue_alias(info_t *info)
{
	int s;
	list_t *node;
	char *p;

	for (s = 0; s < 10; s++)
	{
		node = node_starts_with_prefix(info-> alias, info-> argv[0], '=');
		if (!node)
			return (0);
		free(info-> argv[0]);
		p = find_char_in_string(node-> str, '=');
		if (!p)
			return (0);
		p = duplicate_string(p + 1);
		if (!p)
			return (0);
		info-> argv[0] = p;
	}
	return (1);
}

/**
 * get_new_vars - will replace vars in the tokenized string
 * @info: the parameter struct
 * Return: 1 if replaced, 0 otherwise
 */

/// @brief
/// @param info
/// @return
int get_new_vars(info_t *info)
{
	int i = 0;
	list_t *node;

	for (i = 0; info->argv[i]; i++)
	{
		if (info->argv[i][0] != '$' || !info->argv[i][1])
			continue;

		if (!_compare_strang(info->argv[i], "$?"))
		{
			change_string(&(info->argv[i]),
						   duplicate_string(convert_number_(info->status, 10, 0)));
			continue;
		}
		if (!_compare_strang(info->argv[i], "$$"))
		{
			change_string(&(info->argv[i]),
						   duplicate_string(convert_number_(getpid(), 10, 0)));
			continue;
		}
		node = node_starts_with_prefix(info->env, &info->argv[i][1], '=');
		if (node)
		{
			change_string(&(info->argv[i]),
						   duplicate_string(find_char_in_string(node->str, '=') + 1));
			continue;
		}
		change_string(&info->argv[i], duplicate_string(""));
	}
	return (0);
}

/**
 * change_string - will change a string
 * @old: address of old string
 * @new: new string
 * Return: 1 if replaced, 0 otherwise
 */

/// @brief
/// @param old
/// @param
/// @return
int change_string(char **old, char *new)
{
	free(*old);
	*old = new;
	return (1);
}

