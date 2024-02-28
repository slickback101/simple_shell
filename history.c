#include "shell.h"

/**
 * get_my_history_file - Will get file history
 * @info: parameter struct
 *
 * Return: allocated string of file history
 */

/// @brief
/// @param info
/// @return
char *get_my_history_file(info_t *info)
{
	char *buf, *dir;

	dir = get_env(info, "HOME=");
	if (!dir)
		return (NULL);
	buf = malloc(sizeof(char) * (strlen_length(dir) + strlen_length(HIST_FILE) + 2));
	if (!buf)
		return (NULL);
	buf[0] = 0;
	copy_string(buf, dir);
	concat_two_strings(buf, "/");
	concat_two_strings(buf, HIST_FILE);
	return (buf);
}

/**
 * write_my_history - creates a file, or appends to an existing file
 * @info: the parameter struct
 *
 * Return: 1 on success, else -1
 */

/// @brief
/// @param info
/// @return
int write_my_history(info_t *info)
{
	ssize_t fd;
	char *filename = get_my_history_file(info);
	list_t *node = NULL;

	if (!filename)
		return (-1);

	fd = open(filename, O_CREAT | O_TRUNC | O_RDWR, 0644);
	free(filename);
	if (fd == -1)
		return (-1);
	for (node = info->history; node; node = node->next)
	{
		prints_an_input_string(node->str, fd);
		write_char_fd('\n', fd);
	}
	write_char_fd(BUF_FLUSH, fd);
	close(fd);
	return (1);
}

/**
 * read_my_history - read history from file
 * @info: the parameter struct
 *
 * Return: histcount on success, 0 otherwise
 */

/// @brief
/// @param info
/// @return
int read_my_history(info_t *info)
{
	int e, last = 0, linecount = 0;
	ssize_t fd, rdlen, fsize = 0;
	struct stat st;
	char *buf = NULL, *filename = get_my_history_file(info);

	if (!filename)
		return (0);

	fd = open(filename, O_RDONLY);
	free(filename);
	if (fd == -1)
		return (0);
	if (!fstat(fd, &st))
		fsize = st.st_size;
	if (fsize < 2)
		return (0);
	buf = malloc(sizeof(char) * (fsize + 1));
	if (!buf)
		return (0);
	rdlen = read(fd, buf, fsize);
	buf[fsize] = 0;
	if (rdlen <= 0)
		return (free(buf), 0);
	close(fd);
	for (e = 0; e < fsize; e++)
		if (buf[e] == '\n')
		{
			buf[e] = 0;
			build_my_history_list(info, buf + last, linecount++);
			last = e + 1;
		}
	if (last != e)
		build_my_history_list(info, buf + last, linecount++);
	free(buf);
	info->histcount = linecount;
	while (info->histcount-- >= HIST_MAX)
		rm_node_at_index(&(info->history), 0);
	renumber_my_history(info);
	return (info->histcount);
}

/**
 * build_my_history_list - will add entry to a history linked list
 * @info: Structure containing potential arguments. Used to maintain
 * @buf: buffer
 * @linecount: the history linecount, histcount
 *
 * Return: Always 0
 */

/// @brief
/// @param info
/// @param buf
/// @param linecount
/// @return
int build_my_history_list(info_t *info, char *buf, int linecount)
{
	list_t *node = NULL;

	if (info->history)
		node = info->history;
	add_node_end_list(&node, buf, linecount);

	if (!info->history)
		info->history = node;
	return (0);
}

/**
 * renumber_my_history - will renumber history linked list, after changes
 * @info: Structure containing potential arguments. Used to maintain
 *
 * Return: the new histcount
 */

/// @brief
/// @param info
/// @return
int renumber_my_history(info_t *info)
{
	list_t *node = info->history;
	int i = 0;

	while (node)
	{
		node->num = i++;
		node = node->next;
	}
	return (info->histcount = i);
}
