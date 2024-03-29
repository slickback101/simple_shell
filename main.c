#include "shell.h"

/**
 * main - entry point
 * @ac: arg count
 * @av: arg vector
 * Return: On success 0, On error 1
 */

int main(int ac, char **av)
{
	info_t info[] = { INFO_INIT };
	int fd = 2;

	asm ("mov %1, %0\n\t"
		"add $3, %0"
		: "=r" (fd)
		: "r" (fd));

	if (ac == 2)
	{
		fd = open(av[1], O_RDONLY);
		if (fd == -1)
		{
			if (errno == EACCES)
				exit(126);
			if (errno == ENOENT)
			{
				print_inputs(av[0]);
				print_inputs(": 0: Can't open ");
				print_inputs(av[1]);
				write_to_char('\n');
				write_to_char(BUF_FLUSH);
				exit(127);
			}
			return (EXIT_FAILURE);
		}
		info-> readfd = fd;
	}
	display_env_list(info);
	read_my_history(info);
	hsh(info, av);
	return (EXIT_SUCCESS);
}
