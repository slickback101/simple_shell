#include "shell.h"

/**
 * list_len - will determine the length of linked list
 * @n: pointer to first node
 *
 * Return: size of list
 */

/// @brief
/// @param n
/// @return
size_t _list_len(const list_t *n)
{
	size_t l = 0;

	while (n)
	{
		n = n-> next;
		l++;
	}
	return (l);
}

/**
 * list_to_strings - will return an array of strings of the list-> str
 * @first: pointer to first node
 *
 * Return: array of strings
 */

/// @brief
/// @param first
/// @return
char **list_to_strings_(list_t *first)
{
	list_t *node = first;
	size_t i = _list_len(first), j;
	char **strs;
	char *str;

	if (!first || !i)
		return (NULL);
	strs = malloc(sizeof(char *) * (i + 1));
	if (!strs)
		return (NULL);
	for (i = 0; node; node = node-> next, i++)
	{
		str = malloc(strlen_length(node-> str) + 1);
		if (!str)
		{
			for (j = 0; j < i; j++)
				free(strs[j]);
			free(strs);
			return (NULL);
		}

		str = copy_string(str, node-> str);
		strs[i] = str;
	}
	strs[i] = NULL;
	return (strs);
}

/**
 * my_print_list - Will print all elements of a list_t linked list
 * @h: pointer to first node
 *
 * Return: size of list
 */

/// @brief
/// @param h
/// @return
size_t my_print_list(const list_t *h)
{
	size_t i = 0;

	while (h)
	{
		prints_input_string(convert_number_(h->num, 10, 0));
		_putchar(':');
		_putchar(' ');
		prints_input_string(h->str ? h->str : "(nil)");
		prints_input_string("\n");
		h = h->next;
		i++;
	}
	return (i);
}

/**
 * node_starts_with_prefix - will return node whose string starts with prefix
 * @node: pointer to list head
 * @prefix: string to match
 * @ch: the next character after prefix to match
 *
 * Return: match node or null
 */

/// @brief
/// @param node
/// @param prefix
/// @param ch
/// @return
list_t *node_starts_with_prefix(list_t *node, char *prefix, char ch)
{
	char *p = NULL;

	while (node)
	{
		p = starts_with_haystack(node->str, prefix);
		if (p && ((ch == -1) || (*p == ch)))
			return (node);
		node = node-> next;
	}
	return (NULL);
}

/**
 * get_node_at_index - will get the index of a node
 * @h: pointer to list head
 * @node: pointer to the node
 *
 * Return: index of node or -1
 */

/// @brief
/// @param h
/// @param node
/// @return
ssize_t get_node_at_index(list_t *h, list_t *node)
{
	size_t i = 0;

	while (h)
	{
		if (h == node)
			return (i);
		h = h-> next;
		i++;
	}
	return (-1);
}
