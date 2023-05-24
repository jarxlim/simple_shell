#include "shell.h"
/**
 * chain_test - tests for current char in buff
 * @ifn: the parameter
 * @buff: the buffer
 * @c: addressin buffer
 * Return: 1 if is delimeter, 0 otherwise
 */
int chain_test(info_t *ifn, char *buff, size_t *c)
{
	size_t a = *c;

	if (buff[a] == '|' && buff[a + 1] == '|')
	{
		buff[a] = 0;
		a++;
		ifn->commands_type = COMMANDS_OR;
	}
	else if (buff[a] == '&' && buff[a + 1] == '&')
	{
		buff[a] = 0;
		a++;
		ifn->commands_type = COMMANDS_AND;
	}
	else if (buff[a] == ';')
	{
		buff[a] = 0;
		ifn->commands_type = COMMANDS_CHAIN;
	}
	else
	{
		return (0);
	}
	*c = a;
	return (1);
}
/**
 * c_checker - checks for chain strings
 * @ifn: th object of pinfo for  parameter
 * @buff: the char buffer
 * @c: current position in buff address
 * @j:buffer starting position
 * @size: length of buf
 */
void c_checker(info_t *ifn, char *buff, size_t *c, size_t j, size_t size)
{
	size_t p = *c;

	if (ifn->commands_type == COMMANDS_AND)
	{
		if (ifn->stats)
		{
			buff[j] = 0;
			p = size;
		}
	}
	if (ifn->commands_type == COMMANDS_OR)
	{
		if (!ifn->stats)
		{
			buff[j] = 0;
			p = size;
		}
	}

	*c = p;
}

/**
 * change_alias - replaces alias in strings
 * @ifn: the parameter
 * Return: 1 if success, 0 otherwise
 */
int change_alias(info_t *ifn)
{
	int b;
	list_t *nodes;
	char *str;

	for (b = 0; b < 10; b++)
	{
		nodes = node_list(ifn->_alias, ifn->argv[0], '=');
		if (!nodes)
		{
			return (0);
		}
		free(ifn->argv[0]);
		str = _strchr(nodes->str, '=');
		if (!str)
		{
			return (0);
		}
		str = _strdup(str + 1);
		if (!str)
		{
			return (0);
		}
		ifn->argv[0] = str;
	}
	return (1);
}
/**
 * change_v - replaces vars in a string
 * @ifn: arguments
  * Return: 1 if success, 0 otherwise
 */
int change_v(info_t *ifn)
{
	int h = 0;
	list_t *nodes;

	for (h = 0; ifn->argv[h]; h++)
	{
		if (ifn->argv[h][0] != '$' || !ifn->argv[h][1])
			continue;

		if (!_strcmp(ifn->argv[h], "$?"))
		{
			change_str(&(ifn->argv[h]),
				_strdup(num_converter(ifn->stats, 10, 0)));
			continue;
		}
		if (!_strcmp(ifn->argv[h], "$$"))
		{
			change_str(&(ifn->argv[h]),
				_strdup(num_converter(getpid(), 10, 0)));
			continue;
		}
		nodes = node_list(ifn->envp, &ifn->argv[h][1], '=');
		if (nodes)
		{
			change_str(&(ifn->argv[h]),
				_strdup(_strchr(nodes->str, '=') + 1));
			continue;
		}
		change_str(&ifn->argv[h], _strdup(""));
	}
	return (0);
}
/**
 * change_str - replaces the string
 * @str1: old string to be replaced
 * @str2: new string to replace
 * Return: 1 if successful or 0
 */
int change_str(char **str1, char *str2)
{
	free(*str1);
	*str1 = str2;
	return (1);
}
