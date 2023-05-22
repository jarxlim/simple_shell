#include "main.h"

/**
 * get_environ - function to get the copy of environmental cms
 * @info: Struct info for arguments
 * Return: copy of the environ
 */
char **get_environ(info_t *info)
{
	if (!info->environ || info->env_changed)
	{
		info->environ = list_to_strings(info->env);
		info->env_changed = 0;
	}
	return (info->environ);
}

/**
 * _unsetenv - function to remove environment variable
 * @info: Structure halding args
 * @var: the string env var property
 *
 * Return: 0 as success
 */
int _unsetenv(info_t *info, char *var)
{
	list_t *nodes = info->env;
	size_t a = 0;
	char *k;

	if (!nodes || !var)
		return (0);

	while (nodes)
	{
		k = starts_with(nodes->str, var);
		if (k && *k == '=')
		{
			info->env_changed = delete_node_at_index(&(info->env), a);
			a = 0;
			nodes = info->env;
			continue;
		}
		nodes = nodes->next;
		a++;
	}
	return (info->env_changed);
}

/**
 * _setenv - fnction to add a new environment variable
 * @info: Struct holding args
 * @var: the string enviroonmental variable
 * @value: the string environmental variables value
 *  Return: 0 as success
 */
int _setenv(info_t *info, char *var, char *value)
{
	char *buffer = NULL, *k;
	list_t *nodes;

	if (!var || !value)
		return (0);

	buffer = malloc(_strlen(var) + _strlen(value) + 2);
	if (!buffer)
		return (1);
	_strcpy(buffer, var);
	_strcat(buffer, "=");
	_strcat(buffer, value);
	nodes = info->env;
	while (nodes)
	{
		k = starts_with(nodes->str, var);
		if (k && *k == '=')
		{
			free(nodes->str);
			nodes->str = buffer;
			info->env_changed = 1;
			return (0);
		}
		nodes = nodes->next;
	}
	add_node_end(&(info->env), buffer, 0);
	free(buffer);
	info->env_changed = 1;
	return (0);
}
