#include "shell.h"

/**
 * _myhistory - function to show the history of the command we run
 * @info: struct info for potetal paraments
 * Return: always 0 as success
 */
int _history(info_t *info)
{
	_lister(ifn->hist);
	return (0);
}

/**
 * unset_alias - unset alliass to the string
 * @info: parameter 
 * @str: the strin used be set
 *
 * Return: Always 0 on success, 1 on error
 */
int reset_alias(info_t *ifn, char *str)
{
	char *point, a;
	int reset;

	point = _strchr(str, '=');
	if (!point)
	{
		return (1);
	}
	a = *point;
	*point = 0;
	reset = detach_node(&(ifn->_alias),
		find_node(ifn->_alias, node_list(ifn->_alias, str, -1)));
	*point = a;
	return (reset);
}

/**
 * set_alias - set all alias to string
 * @info: for paramenters
 * @str: the string to use
 * Return: 0on success, 1 for failure
 */
int alias_setter(info_t *ifn, char *str)
{
	char *point;

	point = _strchr(str, '=');
	if (!point)
	{
		return (1);
	}
	if (!*++point)
	{
		return (reset_alias(ifn, str));
	}
	reset_alias(ifn, str);
	return (append_node(&(ifn->_alias), str, 0) == NULL);
}

/**
 * print_alias - print all alias 
 * @node:node of alias stack
 * Return: 0 on success, 1 for failure
 */
int w_alias(list_t *nodes)
{
	char *point = NULL, *c = NULL;

	if (nodes)
	{
		point = _strchr(nodes->str, '=');
		for (c = nodes->str; c <= point; c++)
			_putchar(*c);
		_putchar('\'');
		_putstr(point + 1);
		_putstr("'\n");
		return (0);
	}
	return (1);
}

/**
 * _myalias - check the details for alias 
 * @info:params
 *  Return: 0on success
 */
int get_alias(info_t *ifn)
{
	int a = 0;
	char *point = NULL;
	list_t *nodes = NULL;

	if (ifn->argc == 1)
	{
		nodes = ifn->_alias;
		while (nodes)
		{
			w_alias(nodes);
			nodes = nodes->next;
		}
		return (0);
	}
	for (a = 1; ifn->argv[a]; a++)
	{
		point = _strchr(ifn->argv[a], '=');
		if (point)
			alias_setter(ifn, ifn->argv[a]);
		else
			w_alias(node_list(ifn->_alias, ifn->argv[a], '='));
	}
	return (0);
}
