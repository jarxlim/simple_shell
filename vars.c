#include "shell.h"
/**
 * chain_test - tests for current char in buff
 * @ents: the parameter
 * @buff: the buffer
 * @c: addressin buffer
 * Return: 1 if is delimeter, 0 otherwise
 */
int chain_test(set_t *ents, char *buff, size_t *c)
{
	size_t a = *c;

	if (buff[a] == '|' && buff[a + 1] == '|')
	{
		buff[a] = 0;
		a++;
		ents->commands_type = COMMANDS_OR;
	}
	else if (buff[a] == '&' && buff[a + 1] == '&')
	{
		buff[a] = 0;
		a++;
		ents->commands_type = COMMANDS_AND;
	}
	else if (buff[a] == ';')
	{
		buff[a] = 0;
		ents->commands_type = COMMANDS_CHAIN;
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
 * @ents: th object of pinfo for  parameter
 * @buff: the char buffer
 * @c: current position in buff address
 * @j:buffer starting position
 * @size: length of buf
 */
void c_checker(set_t *ents, char *buff, size_t *c, size_t j, size_t size)
{
	size_t p = *c;

	if (ents->commands_type == COMMANDS_AND)
	{
		if (ents->stats)
		{
			buff[j] = 0;
			p = size;
		}
	}
	if (ents->commands_type == COMMANDS_OR)
	{
		if (!ents->stats)
		{
			buff[j] = 0;
			p = size;
		}
	}

	*c = p;
}

/**
 * change_alias - replaces alias in strings
 * @ents: the parameter
 * Return: 1 if success, 0 otherwise
 */
int change_alias(set_t *ents)
{
	int b;
	list_t *nodes;
	char *str;

	for (b = 0; b < 10; b++)
	{
		nodes = node_list(ents->_alias, ents->argv[0], '=');
		if (!nodes)
		{
			return (0);
		}
		free(ents->argv[0]);
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
		ents->argv[0] = str;
	}
	return (1);
}
/**
 * change_v - replaces vars in a string
 * @ents: arguments
  * Return: 1 if success, 0 otherwise
 */
int change_v(set_t *ents)
{
	int h = 0;
	list_t *nodes;

	for (h = 0; ents->argv[h]; h++)
	{
		if (ents->argv[h][0] != '$' || !ents->argv[h][1])
			continue;

		if (!_strcmp(ents->argv[h], "$?"))
		{
			change_str(&(ents->argv[h]),
				_strdup(num_converter(ents->stats, 10, 0)));
			continue;
		}
		if (!_strcmp(ents->argv[h], "$$"))
		{
			change_str(&(ents->argv[h]),
				_strdup(num_converter(getpid(), 10, 0)));
			continue;
		}
		nodes = node_list(ents->envp, &ents->argv[h][1], '=');
		if (nodes)
		{
			change_str(&(ents->argv[h]),
				_strdup(_strchr(nodes->str, '=') + 1));
			continue;
		}
		change_str(&ents->argv[h], _strdup(""));
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
