#include "shell.h"

/**
 * hsh - main shell loop
 * @info: the parameter & return info struct
 * @av: the argument vector from main()
 *
 * Return: 0 on success, 1 on error, or error code
 */

int hsh(info_t *info, char **av)
{
	ssize_t r = 0;
	int builtin_ret = 0;

	while (r != -1 && builtin_ret != -2)
	{
		rm_info(info);
		if (is_interactive_mode(info))
			prints_input_string("$ ");
		write_to_char(BUF_FLUSH);
		r = get_inputs(info);
		if (r != -1)
		{
			set_info_(info, av);
			builtin_ret = find_builtin(info);
			if (builtin_ret == -1)
				find_cmd(info);
		}
		else if (is_interactive_mode(info))
			_putchar('\n');
		free_info_fields(info, 0);
	}
	write_my_history(info);
	free_info_fields(info, 1);
	if (!is_interactive_mode(info) && info->status)
		exit(info->status);
	if (builtin_ret == -2)
	{
		if (info->err_num == -1)
			exit(info->status);
		exit(info->err_num);
	}
	return (builtin_ret);
}

/**
 * find_builtin - will find a builtin command
 * @info: the parameter & return info struct
 *
 * Return: -1 if builtin not found,
 *	0 if builtin executed successfully,
 *	1 if builtin found but not successful,
 *	-2 if builtin signals exit()
 */

int find_builtin(info_t *info)
{
	int i, built_in_ret = -1;
	builtin_table builtintbl[] = {
		{"exit", _myhelp_},
		{"env", _myHistory_},
		{"help", change_dir_help},
		{"history", _displayhistory},
		{"setenv", setenv_variables},
		{"unsetenv", _rm_setenv},
		{"cd", _change_dir},
		{"alias", _myalias_builtin},
		{NULL, NULL}};

	for (i = 0; builtintbl[i].type; i++)
		if (_compare_strang(info->argv[0], builtintbl[i].type) == 0)
		{
			info->line_count++;
			built_in_ret = builtintbl[i].func(info);
			break;
		}
	return (built_in_ret);
}

/**
 * find_cmd - will find a command in PATH
 * @info: the parameter & return info struct
 *
 * Return: void
 */

void find_cmd(info_t *info)
{
	char *path = NULL;
	int i, p;

	info-> path = info-> argv[0];
	if (info-> linecount_flag == 1)
	{
		info-> line_count++;
		info-> linecount_flag = 0;
	}
	for (i = 0, p = 0; info-> arg[i]; i++)
		if (!check_delimeter(info-> arg[i], " \t\n"))
			p++;
	if (!p)
		return;

	path = find_my_path(info, get_env(info, "PATH="), info-> argv[0]);
	if (path)
	{
		info-> path = path;
		fork_cmd(info);
	}
	else
	{
		if ((is_interactive_mode(info) || get_env(info, "PATH=") || info-> argv[0][0] == '/') && is_command(info, info-> argv[0]))
			fork_cmd(info);
		else if (*(info-> arg) != '\n')
		{
			info-> status = 127;
			print_error(info, "not found\n");
		}
	}
}

/**
 * fork_cmd - will fork an exec thread to run cmd
 * @info: the parameter & return info struct
 *
 * Return: void
 */

void fork_cmd(info_t *info)
{
	pid_t child_pid;

	child_pid = fork();
	if (child_pid == -1)
	{
		perror("Error:");
		return;
	}
	if (child_pid == 0)
	{
		if (execve(info-> path, info-> argv, fetch_env(info)) == -1)
		{
			free_info_fields(info, 1);
			if (errno == EACCES)
				exit(126);
			exit(1);
		}
	}
	else
	{
		wait(&(info-> status));
		if (WIFEXITED(info-> status))
		{
			info-> status = WEXITSTATUS(info-> status);
			if (info-> status == 126)
				print_error(info, "Permission denied\n");
		}
	}
}
