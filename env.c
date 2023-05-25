#include "shell.h"
/**
 * _envron - print the current environmental vars
 * @ents: param to holed the arguments
 * Return: Always 0
 */
int _envron(set_t *ents)
{
	list_printer(ents->envp);
	return (0);
}
/**
 * _getenv - get the value of environment vars
 * @ents: param containing aruments
 * @env_name: env name
 * Return: the value
 *
 */
char *_getenv(set_t *ents, const char *env_name)
{
	list_t *nodes = ents->envp;
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
 * my_setenv - initialize a new environment variable,
 * @ents: param with arguments
 *  Return: returns 0 on success
 */
int my_setenv(set_t *ents)
{
	if (ents->argc != 3)
	{
		_prints("Incorrect number of arguements\n");
		return (1);
	}
	if (_setenv(ents, ents->argv[1], ents->argv[2]))
	{
		return (0);
	}
	return (1);
}
/**
 * my_unsetenv - remove an environment variable
 * @ents: param contain the argments
 *  Return: Always 0
 */
int my_unsetenv(set_t *ents)
{
	int j;

	if (ents->argc == 1)
	{
		_prints("Too few arguements.\n");
		return (1);
	}
	for (j = 1; j <= ents->argc; j++)
	{
		_unsetenv(ents, ents->argv[j]);
	}
	return (0);
}
/**
 * env_lister - define environmental list
 * @ents: contains argument
 * Return: return 0 on success
 */
int env_lister(set_t *ents)
{
	size_t index;
	list_t *nodes = NULL;

	for (index = 0; environ[index]; index++)
		append_node(&nodes, environ[index], 0);
	ents->envp = nodes;
	return (0);
}
