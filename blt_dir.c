#include "shell.h"

/**
 * get_exit - function to help us to exit the shell
 * @ifn: object from inf0_t sctruct
 *  Return: 1 when successull and -2 for failure
 */
int get_exit(info_t *ifn)
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
			printchar('\n');
			return (1);
		}
		ifn->num_err = _strtoint(ifn->argv[1]);
		return (-2);
	}
	ifn->num_err = -1;
	return (-2);
}
/**
 * _cmd - function to change the directory using chdir function
 * @ifn: struct with tyoe info_t to hold parameter protptypes
 *  Return: returns 0 when successull
 */
int _cmd(info_t *ifn)
{
	char *p, *directory, buffer[1024];
	int changedir;

	p = getcwd(buffer, 1024);
	if (!p)
		_putstr("TODO: >>getcwd failure msg here<<\n");
	if (!ifn->argv[1])
	{
		directory = _getenv(ifn, "HOME=");
		if (!directory)
			changedir = chdir((directory = _getenv(ifn, "PWD=")) ? directory : "/");
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
 * _help - functionn to change the current directory
 * @ifn: the parameters of info_t
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
