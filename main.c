#include "shell.h"

/**
 * _shell - prints the shell
 * @ents: input parameter
 * @agv:  array of arguments from the main function
 * Return: 0 on success , 1 on failure
 */
int _shell(set_t *ents, char **agv)
{
	ssize_t a = 0;
	int blt  = 0;

	while (a != -1 && blt != -2)
	{
		_format(ents);
		if (int_checker(ents))
		{
			_putstr("myshell$ ");
		}
		printchar(BUFFER_FLUSH);
		a = line_check(ents);
		if (a != -1)
		{
			_initiate(ents, agv);
			blt = builtin_checker(ents);
			if (blt == -1)
				cmd_finder(ents);
		}
		else if (int_checker(ents))
			_putchar('\n');
		free_info(ents, 0);
	}
	print_hist(ents);
	free_info(ents, 1);
	if (!int_checker(ents) && ents->stats)
		exit(ents->stats);
	if (blt == -2)
	{
		if (ents->num_err == -1)
			exit(ents->stats);
		exit(ents->num_err);
	}
	return (blt);
}
/**
 * builtin_checker - find the built_in command
 * @ents: parameter and input
 * Return: -1, 0 ,-2 depending builtin not found,
 */
int builtin_checker(set_t *ents)
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
		if (_strcmp(ents->argv[0], blt_tbl[a].type) == 0)
		{
			ents->count_line++;
			blt = blt_tbl[a].func(ents);
			break;
		}
	return (blt);
}

/**
 * cmd_finder - find the command in the path
 * @ents: paramenters and input
 *
 */
void cmd_finder(set_t *ents)
{
	char *path = NULL;
	int a, b;

	ents->path = ents->argv[0];
	if (ents->count_fline == 1)
	{
		ents->count_line++;
		ents->count_fline = 0;
	}
	for (a = 0, b = 0; ents->arv[a]; a++)
		if (!is_delim(ents->arv[a], " \t\n"))
			b++;
	if (!b)
		return;

	path = path_finder(ents, _getenv(ents, "PATH="), ents->argv[0]);
	if (path)
	{
		ents->path = path;
		fork_cmd(ents);
	}
	else
	{
		if ((int_checker(ents) || _getenv(ents, "PATH=")
			|| ents->argv[0][0] == '/') &&  check_cmd(ents, ents->argv[0]))
			fork_cmd(ents);
		else if (*(ents->arv) != '\n')
		{
			ents->stats = 127;
			error_printer(ents, "not found\n");
		}
	}
}
/**
 * fork_cmd - make the child process for the command
 * @ents: Oject of Pinfo struct for inputs and parameters
 * Return: void
 */
void fork_cmd(set_t *ents)
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
		if (execve(ents->path, ents->argv, gt_env(ents)) == -1)
		{
			free_info(ents, 1);
			if (errno == EACCES)
				exit(126);
			exit(1);
		}
	}
	else
	{
		wait(&(ents->stats));
		if (WIFEXITED(ents->stats))
		{
			ents->stats = WEXITSTATUS(ents->stats);
			if (ents->stats == 126)
				error_printer(ents, "Permission denied\n");
		}
	}
}
