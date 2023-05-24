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
			ifn->stats = 2;
			error_printer(ifn, "Invalid number: ");
			_prints(ifn->argv[1]);
			_printchar('\n');
			return (1);
		}
		ifn->num_err = _strtoint(ifn->argv[1]);
		return (-2);
	}
	ifn->num_err = -1;
	return (-2);
}

/**
 * _mycd - change the directory using chdir function
 * @info: struct info to hold parameter protptypes
 *  Return: 0 as success
 */
int _cmd(info_t *ifn)
{
	char *p, *directory, buffer[1024];
	int changedir;

	p = getcwd(buffer, 1024);
	if (!p)
		_putstr("TODO: >>getcwd failure msg here<<\n");
	if (!info->argv[1])
	{
		directory = _getenv(ifn, "HOME=");
		if (!directory)
			changedir = chdir((directory = _getenv(info, "PWD=")) ? directory : "/");
		else
			changedir = chdir(directory);
	}
	else if (_strcmp(ifn->argv[1], "-") == 0)
	{
		if (!_getenv(ifn, "OLDPWD="))
		{
			_putstr(p);
			_putchar('\n');
			return (1);
		}
		_putstr(_getenv(ifn, "OLDPWD=")), _putchar('\n');
		changedir = chdir((directory = _getenv(ifn, "OLDPWD=")) ? directory : "/");
	}
	else
		changedir = chdir(ifn->argv[1]);
	if (changedir == -1)
	{
		error_printer(ifn, "can't cd to ");
		_prints(ifn->argv[1]), printchar('\n');
	}
	else
	{
		_setenv(ifn, "OLDPWD", _getenv(ifn, "PWD="));
		_setenv(ifn, "PWD", getcwd(buffer, 1024));
	}
	return (0);
}

/**
 * _myhelp - change the current directory
 * @info: the parameters of info_t
 *  Return: Always 0
 */
int _help(info_t *ifn)
{
	char **st_args;

	st_args = ifn->argv;
	_putstr("help call works. Function not yet implemented \n");
	if (0)
	{
		_putstr(*st_args);
	}
	return (0);
}
