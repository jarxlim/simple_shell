#include "main.h"

/**
 * _myhistory - function to show the history of the command we run
 * @info: struct info for potetal paraments
 * Return: always 0 as success
 */
int _myhistory(info_t *info)
{
	print_list(info->history);
	return (0);
}

/**
 * unset_alias - function to unset alliass to the string
 * @info: parameter struct info for inputs
 * @str: the string alias to be set
 *
 * Return: Always 0 on success, 1 on error
 */
int unset_alias(info_t *info, char *str)
{
	char *point, a;
	int reset;

	point = _strchr(str, '=');
	if (!point)
		return (1);
	a = *point;
	*point = 0;
	reset = delete_node_at_index(&(info->alias),
		get_node_index(info->alias, node_starts_with(info->alias, str, -1)));
	*point = a;
	return (reset);
}

/**
 * set_alias - function to set all alias to string
 * @info: struct info for paramenters
 * @str: the strinf for alisa
 * Return: 0 for success, 1 for failure
 */
int set_alias(info_t *info, char *str)
{
	char *point;

	point = _strchr(str, '=');
	if (!point)
		return (1);
	if (!*++point)
		return (unset_alias(info, str));

	unset_alias(info, str);
	return (add_node_end(&(info->alias), str, 0) == NULL);
}

/**
 * print_alias - function to print all alias string
 * @node: the pointer to the node of alias stack
 * Return: 0 for success, 1 for failure
 */
int print_alias(list_t *node)
{
	char *point = NULL, *c = NULL;

	if (node)
	{
		point = _strchr(node->str, '=');
		for (c = node->str; c <= point; c++)
			_putchar(*c);
		_putchar('\'');
		_puts(point + 1);
		_puts("'\n");
		return (0);
	}
	return (1);
}

/**
 * _myalias - function to check the details for alias (man alias)
 * @info: Struct info for details
 *  Return: 0 for success
 */
int _myalias(info_t *info)
{
	int a = 0;
	char *point = NULL;
	list_t *node = NULL;

	if (info->argc == 1)
	{
		node = info->alias;
		while (node)
		{
			print_alias(node);
			node = node->next;
		}
		return (0);
	}
	for (a = 1; info->argv[a]; a++)
	{
		point = _strchr(info->argv[a], '=');
		if (point)
			set_alias(info, info->argv[a]);
		else
			print_alias(node_starts_with(info->alias, info->argv[a], '='));
	}
	return (0);
}
