#include "shell.h"

/**
 * _shell - prints the shell 
 * @ifn: input parameter
 * @agv:  array of arguments from the main function
 * Return: 0 on success , 1 on failure
 */
int _shell(info_t *ifn, char **agv)
{
	ssize_t a = 0;
	int blt  = 0;

	while (a != -1 && blt != -2)
	{
		_format(ifn);
		if (int_checker(ifn))
		{
			_putstr("myshell$ ");
		}
		printchar(BUFFER_FLUSH);
		a = line_check(ifn);
		if (a != -1)
		{
			_initiate(ifn, agv);
			blt = builtin_checker(ifn);
			if (blt == -1)
				cmd_finder(ifn);
		}
		else if (int_checker(ifn))
			_putchar('\n');
		free_info(ifn, 0);
	}
	print_hist(ifn);
	free_info(ifn, 1);
	if (!int_checker(ifn) && ifn->stats)
		exit(ifn->stats);
	if (blt == -2)
	{
		if (ifn->num_err == -1)
			exit(ifn->stats);
		exit(ifn->num_err);
	}
	return (blt);
}

/**
 * find_builtin - function to find the built_in command
 * @info: the info struct for parameter and input
 *
 * Return: -1, 0 ,-2 depending builtin not found,
 */
int builtin_checker(info_t *ifn)
{
	int a, blt = -1;
	built_t blt_tbl[] = {
		{"exit", get_exit},
		{"alias", get_alias},
		{"env", _envron},
		{"cd", _cmd},
		{"help", _help},
		{"history", _history},
		{"setenv", my_setenv},
		{"unsetenv", my_unsetenv},
		{NULL, NULL}
	};

	for (a = 0; blt_tbl[a].type; a++)
		if (_strcmp(ifn->argv[0], blt_tbl[a].type) == 0)
		{
			ifn->count_line++;
			blt = blt_tbl[a].func(ifn);
			break;
		}
	return (blt);
}

/**
 * find_cmd - function to find the command in the path
 * @info: info struct for paramenters and input
 *
 */
void cmd_finder(info_t *ifn)
{
	char *path = NULL;
	int a, b;

	ifn->path = ifn->argv[0];
	if (ifn->count_fline == 1)
	{
		ifn->count_line++;
		ifn->count_fline = 0;
	}
	for (a = 0, b = 0; ifn->arv[a]; a++)
		if (!is_delim(ifn->arv[a], " \t\n"))
			b++;
	if (!b)
		return;

	path = path_finder(ifn, _getenv(ifn, "PATH="), ifn->argv[0]);
	if (path)
	{
		ifn->path = path;
		fork_cmd(ifn);
	}
	else
	{
		if ((int_checker(ifn) || _getenv(ifn, "PATH=")
			|| ifn->argv[0][0] == '/') &&  check_cmd(ifn, ifn->argv[0]))
			fork_cmd(ifn);
		else if (*(ifn->arv) != '\n')
		{
			ifn->stats = 127;
			error_printer(ifn, "not found\n");
		}
	}
}

/**
 * fork_cmd - function to make the child process for the command
 * @info: info struct for inputs and parameters
 *
 * Return: void
 */
void fork_cmd(info_t *ifn)
{
	pid_t child_pid;

	child_pid = fork();
	if (child_pid == -1)
	{
		perror("Error(fork failed):");
		return;
	}
	if (child_pid == 0)
	{
		if (execve(ifn->path, ifn->argv, gt_env(ifn)) == -1)
		{
			free_info(ifn, 1);
			if (errno == EACCES)
				exit(126);
			exit(1);
		}
	}
	else
	{
		wait(&(ifn->stats));
		if (WIFEXITED(ifn->stats))
		{
			ifn->stats = WEXITSTATUS(ifn->stats);
			if (ifn->stats == 126)
				error_printer(ifn, "Permission denied\n");
		}
	}
}
