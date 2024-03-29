#include "shell.h"

/**
 * current_env - will print the current environment
 * @info: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 * Return: Always 0
 */

int _myHistory_(info_t *info)
{
	print_list_str_(info-> env);
	return (0);
}

/**
 * get_env - will get the value of an environ variable
 * @info: Structure containing potential arguments. Used to maintain
 * @name: env var name
 *
 * Return: the value
 */

char *get_env(info_t *info, const char *name)
{
	list_t *node = info-> env;
	char *p;

	while (node)
	{
		p = starts_with_haystack(node-> str, name);
		if (p && *p)
			return (p);
		node = node-> next;
	}
	return (NULL);
}

/**
 * setenv_variables - will Initialize a new environment variable,
 *             or modify an existing one
 *  @info: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 *  Return: Always 0
 */

int setenv_variables(info_t *info)
{
	if (info-> argc != 3)
	{
		print_inputs("Incorrect number of arguements\n");
		return (1);
	}
	if (_set_env(info, info-> argv[1], info-> argv[2]))
		return (0);
	return (1);
}

/**
 * _rm_setenv - Remove an environment variable
 * @info: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 *  Return: Always 0
 */
int _rm_setenv(info_t *info)
{
	int r;

	if (info->argc == 1)
	{
		print_inputs("Too few arguements.\n");
		return (1);
	}
	for (r = 1; r <= info->argc; r++)
		_un_setenv(info, info->argv[r]);

	return (0);
}

/**
 * display_env_list - will populate env linked list
 * @info: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 * Return: Always 0
 */

int display_env_list(info_t *info)
{
	list_t *node = NULL;
	size_t p;

	for (p = 0; environ[p]; p++)
		add_node_end_list(&node, environ[p], 0);
	info-> env = node;
	return (0);
}
