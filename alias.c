#include "shell.h"
/**
 * _history - function to show the history of the command we run
 * @ifn: struct from info_t tpe for potetal paraments
 * Return: always 0 as success
 */
int _history(info_t *ifn)
{
	_lister(ifn->hist);
	return (0);
}

/**
 * reset_alias - function to unset alliass to the string
 * @ifn: structure from info_t type parameter
 * @str: the string used be set
 * Return: Always 0 when successfull, 1 when failsr
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
 * alias_setter - function used to set all alias to string
 * @ifn: for paramenters
 * @str: the string to use
 * Return: 0 when successfull, 1 when fails
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
 * w_alias - function for writing all alias
 * @nodes: nodes of alias stack
 * Return: 0 when successfull, 1 when fails
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
 * get_alias - function to check the details for alias
 * @ifn: object of info_t structure to be used
 *  Return: 0 when successfull
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
