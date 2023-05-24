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
			blt = find_builtin(info);
			if (builtin == -1)
				find_cmd(info);
		}
		else if (interactive(info))
			_putchar('\n');
		free_info(info, 0);
	}
	write_history(info);
	free_info(info, 1);
	if (!interactive(info) && info->status)
		exit(info->status);
	if (builtin == -2)
	{
		if (info->err_num == -1)
			exit(info->status);
		exit(info->err_num);
	}
	return (builtin);
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
		{"exit", _exit},
		{"alias", get_alias},
		{"env", _envron},
		{"cd", _cmd},
		{"help", _help},
		{"history", _history},
		{"setenv", _mysetenv},
		{"unsetenv", _myunsetenv},
		{NULL, NULL}
	};

	for (a = 0; builtintbl[a].type; a++)
		if (_strcmp(info->argv[0], builtintbl[a].type) == 0)
		{
			info->line_count++;
			builtin = builtintbl[a].func(info);
			break;
		}
	return (builtin);
}

/**
 * find_cmd - function to find the command in the path
 * @info: info struct for paramenters and input
 *
 */
void find_cmd(info_t *info)
{
	char *path = NULL;
	int a, b;

	info->path = info->argv[0];
	if (info->linecount_flag == 1)
	{
		info->line_count++;
		info->linecount_flag = 0;
	}
	for (a = 0, b = 0; info->arg[a]; a++)
		if (!is_delim(info->arg[a], " \t\n"))
			b++;
	if (!b)
		return;

	path = find_path(info, _getenv(info, "PATH="), info->argv[0]);
	if (path)
	{
		info->path = path;
		fork_cmd(info);
	}
	else
	{
		if ((interactive(info) || _getenv(info, "PATH=")
			|| info->argv[0][0] == '/') && is_cmd(info, info->argv[0]))
			fork_cmd(info);
		else if (*(info->arg) != '\n')
		{
			info->status = 127;
			print_error(info, "not found\n");
		}
	}
}

/**
 * fork_cmd - function to make the child process for the command
 * @info: info struct for inputs and parameters
 *
 * Return: void
 */
void fork_cmd(info_t *info)
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
		if (execve(info->path, info->argv, get_environ(info)) == -1)
		{
			free_info(info, 1);
			if (errno == EACCES)
				exit(126);
			exit(1);
		}
	}
	else
	{
		wait(&(info->status));
		if (WIFEXITED(info->status))
		{
			info->status = WEXITSTATUS(info->status);
			if (info->status == 126)
				print_error(info, "Permission denied\n");
		}
	}
}
