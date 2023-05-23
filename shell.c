#include "shell.h"

/**
 * main - entry point
 * @arg: argument number
 * @agv: argument array
 * Return: 0 if successs, 1 if unsuccessful
 */
int main(int argm, char **agv)
{
	int filename = 2;
	info_t ifn[] = { INIT_F };

	asm ("mov %1, %0\n\t"
		"add $3, %0"
		: "=r" (filename)
		: "r" (filename));

	if (argm == 2)
	{
		filename = open(agv[1], O_RDONLY);
		if (filename == -1)
		{
			if (errno == EACCES)
			{
				exit(126);
			}
			if (errno == ENOENT)
			{
				_prints(agv[0]);
				_prints(": 0: Can't open ");
				_prints(agv[1]);
				printchar('\n');
				printchar(BUFFER_FLUSH);
				exit(127);
			}
			return (EXIT_FAILURE);
		}
		ifn->file_reader = filename;
	}
	env_lister(ifn);
	hist_read(ifn);
	hsh(ifn, agv);
	return (EXIT_SUCCESS);
}
