#include "shell.h"

/**
 * rm_info - initializes info_t struct
 * @info: struct address
 */

/// @brief
/// @param info
void rm_info(info_t *info)
{
	info-> arg = NULL;
	info-> argv = NULL;
	info-> path = NULL;
	info-> argc = 0;
}

/**
 * set_info - Will initialize info_t struct
 * @info: struct address
 * @av: argument vector
 */

/// @brief
/// @param info
/// @param av
void set_info_(info_t *info, char **av)
{
	int i = 0;

	info-> fname = av[0];
	if (info-> arg)
	{
		info-> argv = split_string_words(info-> arg, " \t");
		if (!info-> argv)
		{

			info-> argv = malloc(sizeof(char *) * 2);
			if (info-> argv)
			{
				info-> argv[0] = duplicate_string(info-> arg);
				info-> argv[1] = NULL;
			}
		}
		for (i = 0; info-> argv && info-> argv[i]; i++)
			;
		info-> argc = i;

		substitue_alias(info);
		get_new_vars(info);
	}
}

/**
 * free_info_fields- frees info_t struct fields
 * @info: struct address
 * @all: true if freeing all fields
 */

/// @brief
/// @param info
/// @param all
void free_info_fields(info_t *info, int all)
{
	ffree(info-> argv);
	info-> argv = NULL;
	info-> path = NULL;
	if (all)
	{
		if (!info->cmd_buf)
			free(info->arg);
		if (info->env)
			free_all_node_list(&(info->env));
		if (info->history)
			free_all_node_list(&(info->history));
		if (info->alias)
			free_all_node_list(&(info->alias));
		ffree(info->environ);
		info->environ = NULL;
		bfree((void **)info->cmd_buf);
		if (info->readfd > 2)
			close(info->readfd);
		_putchar(BUF_FLUSH);
	}
}
