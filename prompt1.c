#include "main.h"

/**
 * main - Sehll  main entry
 * @ac: argument number
 * @av: arguments array
 * Return: 0 Always as successs, 1 as error
 */
int main(int ac, char **av)
{
	info_t info[] = { INFO_INIT };
	int fdm = 2;

	asm ("mov %1, %0\n\t"
		"add $3, %0"
		: "=r" (fdm)
		: "r" (fdm));

	if (ac == 2)
	{
		fdm = open(av[1], O_RDONLY);
		if (fdm == -1)
		{
			if (errno == EACCES)
				exit(126);
			if (errno == ENOENT)
			{
				_eputs(av[0]);
				_eputs(": 0: Can't open ");
				_eputs(av[1]);
				_eputchar('\n');
				_eputchar(BUF_FLUSH);
				exit(127);
			}
			return (EXIT_FAILURE);
		}
		info->readfd = fdm;
	}
	populate_env_list(info);
	read_history(info);
	hsh(info, av);
	return (EXIT_SUCCESS);
}
