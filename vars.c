#include "main.h"
/**
 * is_chain - function that tests if current char in buff
 * @info: the parameter structure calleed info
 * @buf: the char buffer as arguments
 * @p: address of current rep in buf
 * Return: 1 if chain is delimeter, 0 otherwise
 */
int is_chain(info_t *info, char *buf, size_t *p)
{
	size_t a = *p;

	if (buf[a] == '|' && buf[a + 1] == '|')
	{
		buf[a] = 0;
		a++;
		info->cmd_buf_type = CMD_OR;
	}
	else if (buf[a] == '&' && buf[a + 1] == '&')
	{
		buf[a] = 0;
		a++;
		info->cmd_buf_type = CMD_AND;
	}
	else if (buf[a] == ';')
	{
		buf[a] = 0;
		info->cmd_buf_type = CMD_CHAIN;
	}
	else
		return (0);
	*p = a;
	return (1);
}
/**
 * check_chain - function to check in we can still chain steings
 * @info: the parameter struct
 * @buf: the char buffer
 * @p: address of current position in buf
 * @i: starting position in buf
 * @len: length of buf
 */
void check_chain(info_t *info, char *buf, size_t *p, size_t i, size_t len)
{
	size_t h = *p;

	if (info->cmd_buf_type == CMD_AND)
	{
		if (info->status)
		{
			buf[i] = 0;
			h = len;
		}
	}
	if (info->cmd_buf_type == CMD_OR)
	{
		if (!info->status)
		{
			buf[i] = 0;
			h = len;
		}
	}

	*p = h;
}

/**
 * replace_alias - function to replaces aliases in string
 * @info: the parameter struct
 * Return: 1 if replaced, 0 otherwise
 */
int replace_alias(info_t *info)
{
	int b;
	list_t *node;
	char *str;

	for (b = 0; b < 10; b++)
	{
		node = node_starts_with(info->alias, info->argv[0], '=');
		if (!node)
			return (0);
		free(info->argv[0]);
		str = _strchr(node->str, '=');
		if (!str)
			return (0);
		str = _strdup(str + 1);
		if (!str)
			return (0);
		info->argv[0] = str;
	}
	return (1);
}
/**
 * replace_vars - function to replaces vars string
 * @info: the parameter struct for arguments
  * Return: 1 if replaced, 0 otherwise
 */
int replace_vars(info_t *info)
{
	int h = 0;
	list_t *node;

	for (h = 0; info->argv[h]; h++)
	{
		if (info->argv[h][0] != '$' || !info->argv[h][1])
			continue;

		if (!_strcmp(info->argv[h], "$?"))
		{
			replace_string(&(info->argv[h]),
				_strdup(convert_number(info->status, 10, 0)));
			continue;
		}
		if (!_strcmp(info->argv[h], "$$"))
		{
			replace_string(&(info->argv[h]),
				_strdup(convert_number(getpid(), 10, 0)));
			continue;
		}
		node = node_starts_with(info->env, &info->argv[h][1], '=');
		if (node)
		{
			replace_string(&(info->argv[h]),
				_strdup(_strchr(node->str, '=') + 1));
			continue;
		}
		replace_string(&info->argv[h], _strdup(""));
	}
	return (0);
}
/**
 * replace_string - function to replace the string
 * @old: old string to be replaced
 * @new: new string to replace
 * Return: 1 if replaced or 0
 */
int replace_string(char **old, char *new)
{
	free(*old);
	*old = new;
	return (1);
}
