#include "shell.h"

/**
 * gt_env - get the copy of environmental cms
 * @ents: arguments
 * Return: copy of the environ
 */
char **gt_env(set_t *ents)
{
	if (!ents->environ || ents->change_env)
	{
		ents->environ = list_string(ents->envp);
		ents->change_env = 0;
	}
	return (ents->environ);
}

/**
 * _unsetenv - remove environment variable
 * @ents: param
 * @var: the string env var property
 * Return: 0 as success
 */
int _unsetenv(set_t *ents, char *var)
{
	list_t *nodes = ents->envp;
	size_t a = 0;
	char *k;

	if (!nodes || !var)
		return (0);

	while (nodes)
	{
		k = _leet(nodes->str, var);
		if (k && *k == '=')
		{
			ents->change_env = detach_node(&(ents->envp), a);
			a = 0;
			nodes = ents->envp;
			continue;
		}
		nodes = nodes->next;
		a++;
	}
	return (ents->change_env);
}

/**
 * _setenv - adds a new environment variable
 * @ents: param
 * @var: the string paramm
 * @val: the env value
 *  Return: 0 as success
 */
int _setenv(set_t *ents, char *var, char *val)
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
	nodes = ents->envp;
	while (nodes)
	{
		k = _leet(nodes->str, var);
		if (k && *k == '=')
		{
			free(nodes->str);
			nodes->str = buffer;
			ents->change_env = 1;
			return (0);
		}
		nodes = nodes->next;
	}
	append_node(&(ents->envp), buffer, 0);
	free(buffer);
	ents->change_env = 1;
	return (0);
}
