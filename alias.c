#include "shell.h"
/**
 * _history - history of the command we run
 * @ents: set_t paraments
 * Return: always 0 as success
 */
int _history(set_t *ents)
{
	_lister(ents->hist);
	return (0);
}

/**
 * reset_alias - unset alliass to the string
 * @ents: set_t type parameter
 * @str: string used be set
 * Return: Always 0 when successfull, 1 when failsr
 */
int reset_alias(set_t *ents, char *str)
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
	reset = detach_node(&(ents->_alias),
		find_node(ents->_alias, node_list(ents->_alias, str, -1)));
	*point = a;
	return (reset);
}
/**
 * alias_setter - set all alias to string
 * @ents: for paramenters
 * @str: the string to use
 * Return: 0 when successfull, 1 when fails
 */
int alias_setter(set_t *ents, char *str)
{
	char *point;

	point = _strchr(str, '=');
	if (!point)
	{
		return (1);
	}
	if (!*++point)
	{
		return (reset_alias(ents, str));
	}
	reset_alias(ents, str);
	return (append_node(&(ents->_alias), str, 0) == NULL);
}
/**
 * w_alias - for writing all alias
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
 * get_alias - check the details for alias
 * @ents: set_t structure to be used
 *  Return: 0 when successfull
 */
int get_alias(set_t *ents)
{
	int a = 0;
	char *point = NULL;
	list_t *nodes = NULL;

	if (ents->argc == 1)
	{
		nodes = ents->_alias;
		while (nodes)
		{
			w_alias(nodes);
			nodes = nodes->next;
		}
		return (0);
	}
	for (a = 1; ents->argv[a]; a++)
	{
		point = _strchr(ents->argv[a], '=');
		if (point)
			alias_setter(ents, ents->argv[a]);
		else
			w_alias(node_list(ents->_alias, ents->argv[a], '='));
	}
	return (0);
}
