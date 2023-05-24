#include "shell.h"

/**
 * get_environ - function to get the copy of environmental cms
 * @info: Struct info for arguments
 * Return: copy of the environ
 */
char **gt_env(info_t *ifn)
{
	if (!ifn->environ || ifn->change_env)
	{
		ifn->environ = list_string(ifn->envp);
		ifn->change_env = 0;
	}
	return (ifn->environ);
}

/**
 * _unsetenv - function to remove environment variable
 * @info: Structure halding args
 * @var: the string env var property
 *
 * Return: 0 as success
 */
int _unsetenv(info_t *ifn, char *var)
{
	list_t *nodes = ifn->envp;
	size_t a = 0;
	char *k;

	if (!nodes || !var)
		return (0);

	while (nodes)
	{
		k = _leet(nodes->str, var);
		if (k && *k == '=')
		{
			ifn->change_env = detach_node(&(ifn->envp), a);
			a = 0;
			nodes = ifn->envp;
			continue;
		}
		nodes = nodes->next;
		a++;
	}
	return (ifn->change_env);
}

/**
 * _setenv - fnction to add a new environment variable
 * @info: Struct holding args
 * @var: the string enviroonmental variable
 * @value: the string environmental variables value
 *  Return: 0 as success
 */
int _setenv(info_t *ifn, char *var, char *val)
{
	char *buffer = NULL, *k;
	list_t *nodes;

	if (!var || !val)
		return (0);

	buffer = malloc(_strlen(var) + _strlen(val) + 2);
	if (!buffer)
		return (1);
	_strcpy(buffer, var);
	_strcat(buffer, "=");
	_strcat(buffer, val);
	nodes = ifn->envp;
	while (nodes)
	{
		k = _leet(nodes->str, var);
		if (k && *k == '=')
		{
			free(nodes->str);
			nodes->str = buffer;
			ifn->change_env = 1;
			return (0);
		}
		nodes = nodes->next;
	}
	append_node(&(ifn->envp), buffer, 0);
	free(buffer);
	ifn->change_env = 1;
	return (0);
}
