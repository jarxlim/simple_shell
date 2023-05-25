#include "shell.h"

/**
 * get_exit - help us to exit the shell
 * @ents: parram
 * Return: 1 on successull and -2 for failure
 */
int get_exit(set_t *ents)
{
	int exitfinder;

	if (ents->argv[1])
	{
		exitfinder = _strtoint(ents->argv[1]);
		if (exitfinder == -1)
		{
			ents->stats = 2;
			error_printer(ents, "Invalid number: ");
			_prints(ents->argv[1]);
			printchar('\n');
			return (1);
		}
		ents->num_err = _strtoint(ents->argv[1]);
		return (-2);
	}
	ents->num_err = -1;
	return (-2);
}
/**
 * _cmd - change the directory using chdir function
 * @ents: set_t parameter protptypes
 *  Return: returns 0 on successull
 */
int _cmd(set_t *ents)
{
	char *p, *directory, buffer[1024];
	int changedir;

	p = getcwd(buffer, 1024);
	if (!p)
		_putstr("TODO: >>getcwd failure msg here<<\n");
	if (!ents->argv[1])
	{
		directory = _getenv(ents, "HOME=");
		if (!directory)
			changedir = chdir((directory = _getenv(ents, "PWD=")) ? directory : "/");
		else
			changedir = chdir(directory);
	}
	else if (_strcmp(ents->argv[1], "-") == 0)
	{
		if (!_getenv(ents, "OLDPWD="))
		{
			_putstr(p);
			_putchar('\n');
			return (1);
		}
		_putstr(_getenv(ents, "OLDPWD=")), _putchar('\n');
		changedir = chdir((directory = _getenv(ents, "OLDPWD=")) ? directory : "/");
	}
	else
		changedir = chdir(ents->argv[1]);
	if (changedir == -1)
	{
		error_printer(ents, "can't cd to ");
		_prints(ents->argv[1]), printchar('\n');
	}
	else
	{
		_setenv(ents, "OLDPWD", _getenv(ents, "PWD="));
		_setenv(ents, "PWD", getcwd(buffer, 1024));
	}
	return (0);
}

/**
 * _help - change the current directory
 * @ents: parameters of set_t
 *  Return: Always 0
 */
int _help(set_t *ents)
{
	char **st_args;

	st_args = ents->argv;
	_putstr("help call works. Function not yet implemented \n");
	if (0)
	{
		_putstr(*st_args);
	}
	return (0);
}
