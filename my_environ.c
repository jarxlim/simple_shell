#include "main.h"
/**
 * _myenv - function to print the current env
 * @info: Structure contains the arguments
 * Return: Always 0
 */
int _myenv(info_t *info)
{
	print_list_str(info->env);
	return (0);
}
/**
 * _getenv - function to get the value of envs
 * @info: Structure containing aruments
 * @string_name: env name to get
 * Return: the value of env we get
 */
char *_getenv(info_t *info, const char *string_name)
{
	list_t *node = info->env;
	char *h;

	while (node)
	{
		h = starts_with(node->str, string_name);
		if (h && *h)
			return (h);
		node = node->next;
	}
	return (NULL);
}
/**
 * _mysetenv -functin to initialize a new environment variable,
 *             or modify an existing one
 * @info: Struct cntaining arguments
 *  Return: 0 as success
 */
int _mysetenv(info_t *info)
{
	if (info->argc != 3)
	{
		_eputs("Incorrect number of arguements\n");
		return (1);
	}
	if (_setenv(info, info->argv[1], info->argv[2]))
		return (0);
	return (1);
}
/**
 * _myunsetenv -fnct to remove an environment variable
 * @info: Structure contain the argments
 *  Return: Always 0
 */
int _myunsetenv(info_t *info)
{
	int j;

	if (info->argc == 1)
	{
		_eputs("Too few arguements.\n");
		return (1);
	}
	for (j = 1; j <= info->argc; j++)
		_unsetenv(info, info->argv[j]);

	return (0);
}
/**
 * populate_env_list - function to populate environmental list
 * @info: Struct containing argument
 * Return: 0 as success
 */
int populate_env_list(info_t *info)
{
	size_t a;
	list_t *node = NULL;

	for (a = 0; environ[a]; a++)
		add_node_end(&node, environ[a], 0);
	info->env = node;
	return (0);
}
