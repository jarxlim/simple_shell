#include "shell.h"

/**
 * _exit - to exit the shell
 * @ifn: the parameter
 *  Return: 1 for success and -2 for failure
 */
int _exit(info_t *ifn)
{
	int exitfinder;

	if (ifn->argv[1])
	{
		exitfinder = _strtoint(ifn->argv[1]);
		if (exitfinder == -1)
		{
			info->status = 2;
			print_error(info, "Invalid number: ");
			_eputs(info->argv[1]);
			_eputchar('\n');
			return (1);
		}
		info->err_num = _erratoi(info->argv[1]);
		return (-2);
	}
	info->err_num = -1;
	return (-2);
}

/**
 * _mycd - function to change the directory using chdir function
 *
 * @info: struct info to hold parameter protptypes
 *  Return: 0 as success
 */
int _mycd(info_t *info)
{
	char *p, *directory, buffer[1024];
	int changedir;

	p = getcwd(buffer, 1024);
	if (!p)
		_puts("TODO: >>getcwd failure emsg here<<\n");
	if (!info->argv[1])
	{
		directory = _getenv(info, "HOME=");
		if (!directory)
			changedir = chdir((directory = _getenv(info, "PWD=")) ? directory : "/");
		else
			changedir = chdir(directory);
	}
	else if (_strcmp(info->argv[1], "-") == 0)
	{
		if (!_getenv(info, "OLDPWD="))
		{
			_puts(p);
			_putchar('\n');
			return (1);
		}
		_puts(_getenv(info, "OLDPWD=")), _putchar('\n');
		changedir = chdir((directory = _getenv(info, "OLDPWD=")) ? directory : "/");
	}
	else
		changedir = chdir(info->argv[1]);
	if (changedir == -1)
	{
		print_error(info, "can't cd to ");
		_eputs(info->argv[1]), _eputchar('\n');
	}
	else
	{
		_setenv(info, "OLDPWD", _getenv(info, "PWD="));
		_setenv(info, "PWD", getcwd(buffer, 1024));
	}
	return (0);
}

/**
 * _myhelp - function to change the current directory
 * @info: struct to hold the parameters of info_t
 *  Return: Always 0
 */
int _myhelp(info_t *info)
{
	char **st_args;

	st_args = info->argv;
	_puts("help call works. Function not yet implemented \n");
	if (0)
		_puts(*st_args);
	return (0);
}
