#include "shell.h"
/**
 * _envron - function to print the current environmental vars
 * @ifn: Object of struct oinfo to holed the arguments
 * Return: Always 0 when successfull
 */
int _envron(info_t *ifn)
{
	list_printer(ifn->envp);
	return (0);
}
/**
 * _getenv - function to get the value of environmental vars
 * @ifn: structure containing aruments
 * @env_name: env name
 * Return: the value of environmental variableet number
 *
 */
char *_getenv(info_t *ifn, const char *env_name)
{
	list_t *nodes = ifn->envp;
	char *c;

	while (nodes)
	{
		c = _leet(nodes->str, env_name);
		if (c && *c)
		{
			return (c);
		}
		nodes = nodes->next;
	}
	return (NULL);
}
/**
 * my_setenv -functin to initialize a new environment variable,
 * @ifn: object of pinfo struct cntaining arguments
 *  Return: returns 0 when successfull
 */
int my_setenv(info_t *ifn)
{
	if (ifn->argc != 3)
	{
		_prints("Incorrect number of arguements\n");
		return (1);
	}
	if (_setenv(ifn, ifn->argv[1], ifn->argv[2]))
	{
		return (0);
	}
	return (1);
}
/**
 * my_unsetenv -fnct to remove an environment variable
 * @ifn: Structure contain the argments
 *  Return: Always 0
 */
int my_unsetenv(info_t *ifn)
{
	int j;

	if (ifn->argc == 1)
	{
		_prints("Too few arguements.\n");
		return (1);
	}
	for (j = 1; j <= ifn->argc; j++)
	{
		_unsetenv(ifn, ifn->argv[j]);
	}
	return (0);
}
/**
 * env_lister - define environmental list
 * @ifn: contains argument
 * Return: return 0 on success
 */
int env_lister(info_t *ifn)
{
	size_t index;
	list_t *nodes = NULL;

	for (index = 0; environ[index]; index++)
		append_node(&nodes, environ[index], 0);
	ifn->envp = nodes;
	return (0);
}
