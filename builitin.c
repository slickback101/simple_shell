#include "shell.h"

/**
 * exits_shell - exits the shell
 * @info: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 *  Return: will exit with a given exit status
 *         (0) if info.argv[0] != "exit"
 */

/// @brief
/// @param info
/// @return
int _myhelp_(info_t *info)
{
	int exitscheck;

	if (info->argv[1]) /* If there is an exit argument */
	{
		exitscheck = convert_int(info->argv[1]);
		if (exitscheck == -1)
		{
			info-> status = 2;
			print_error(info, "Illegal number: ");
			print_inputs(info-> argv[1]);
			write_to_char('\n');
			return (1);
		}
		info-> err_num = convert_int(info-> argv[1]);
		return (-2);
	}
	info-> err_num = -1;
	return (-2);
}

/**
 * _change_dir - will change the current directory of the process
 * @info: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 *  Return: Always 0
 */

/// @brief
/// @param info
/// @return
int _change_dir(info_t *info)
{
	char *s, *dir, buffer[1024];
	int chdir_ret;

	s = getcwd(buffer, 1024);
	if (!s)
		prints_input_string("TODO: >>getcwd failure emsg here<<\n");
	if (!info-> argv[1])
	{
		dir = get_env(info, "HOME=");
		if (!dir)
			chdir_ret = chdir((dir = get_env(info, "PWD=")) ? dir : "/");
		else
			chdir_ret = chdir(dir);
	}
	else if (_compare_strang(info->argv[1], "-") == 0)
	{
		if (!get_env(info, "OLDPWD="))
		{
			prints_input_string(s);
			_putchar('\n');
			return (1);
		}
		prints_input_string(get_env(info, "OLDPWD=")), _putchar('\n');
		chdir_ret = chdir((dir = get_env(info, "OLDPWD=")) ? dir : "/");
	}
	else
		chdir_ret = chdir(info->argv[1]);
	if (chdir_ret == -1)
	{
		print_error(info, "can't cd to ");
		print_inputs(info->argv[1]), write_to_char('\n');
	}
	else
	{
		_set_env(info, "OLDPWD", get_env(info, "PWD="));
		_set_env(info, "PWD", getcwd(buffer, 1024));
	}
	return (0);
}

/**
 * change_dir_help - wll change the current directory of the process
 * @info: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 *  Return: Always 0
 */

/// @brief
/// @param info
/// @return
int change_dir_help(info_t *info)
{
	char **arg_array;

	arg_array = info-> argv;
	prints_input_string("help call works. Function not yet implemented \n");
	if (0)
		prints_input_string(*arg_array);
		
	return (0);
}
