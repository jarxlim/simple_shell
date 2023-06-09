#include "shell.h"
/**
 * _buffcmd - to buffer chain commands
 * @ents: parameter
 * @buff: ptr to the buffer
 * @size: size of the buffer
 * Return: 0 on success
 */
ssize_t _buffcmd(set_t *ents, char **buff, size_t *size)
{
	ssize_t a = 0;
	size_t length = 0;

	if (!*size)
	{
		free(*buff);
		*buff = NULL;
		signal(SIGINT, ctrlc_handler);
#if USE_GETLINE
		a = getline(buff, &length, stdin);
#else
		a = _getline(ents, buff, &length);
#endif
		if (a > 0)
		{
			if ((*buff)[a - 1] == '\n')
			{
				(*buff)[a - 1] = '\0';
				a--;
			}
			ents->count_fline = 1;
			comment_deleter(*buff);
			append_list(ents, *buff, ents->hist_size++);
			{
				*size = a;
				ents->buffer_cmd = buff;
			}
		}
	}
	return (a);
}

/**
 * line_check - gets line from a newline
 * @ents: parameter arguments
 * Return: 0 on success
 */
ssize_t line_check(set_t *ents)
{
	static char *buffer;
	static size_t a, b, length;
	ssize_t r = 0;
	char **buff = &(ents->arv), *p;

	_putchar(BUFFER_FLUSH);
	r = _buffcmd(ents, &buffer, &length);
	if (r == -1)
	{
		return (-1);
	}
	if (length)
	{
		b = a;
		p = buffer + a;

		c_checker(ents, buffer, &b, a, length);
		while (b < length)
		{
			if (chain_test(ents, buffer, &b))
				break;
			b++;
		}

		a = b + 1;
		if (a >= length)
		{
			a = length = 0;
			ents->commands_type = COMMANDS_NORM;
		}

		*buff = p;
		return (_strlen(p));
	}

	*buff = buffer;
	return (r);
}
/**
 * buff_reader - reads a buffer
 * @ents: parameter
 * @buff: buffer inputed
 * @j: size of buff
 * Return: size of the buffer
 */
ssize_t buff_reader(set_t *ents, char *buff, size_t *j)
{
	ssize_t a = 0;

	if (*j)
	{
		return (0);
	}
	a = read(ents->file_reader, buff, BUFF_R_SIZE);
	if (a >= 0)
	{
		*j = a;
	}
	return (a);
}
/**
 * _getline - get the next line of input from a std input
 * @ents: paramete arguments
 * @p: pointer to the buffer
 * @length: size
 * Return: length of the line
 */
int _getline(set_t *ents, char **p, size_t *length)
{
	size_t k;
	static char buff[BUFF_R_SIZE];
	static size_t a, leng;
	char *s = NULL, *c, *new_p = NULL;
	ssize_t hh = 0, sh = 0;

	s = *p;
	if (s && length)
	{
		sh = *length;
	}
	if (a == leng)
	{
		a = leng = 0;
	}
	hh = buff_reader(ents, buff, &leng);
	if (hh == -1 || (hh == 0 && leng == 0))
	{
		return (-1);
	}
	c = _strchr(buff + a, '\n');
	k = c ? 1 + (unsigned int)(c - buff) : leng;
	new_p = _realloc(s, sh, sh ? sh + k : k + 1);
	if (!new_p)
	{
		return (s ? free(s), -1 : -1);
	}
	if (sh)
		_strncat(new_p, buff + a, k - a);
	else
		_strncpy(new_p, buff + a, k - a + 1);

	sh += k - a;
	a = k;
	s = new_p;

	if (length)
		*length = sh;
	*p = s;
	return (sh);
}
/**
 * ctrlc_handler - handles ctrl-C
 * @signal_no: the signal number
*/
void ctrlc_handler(__attribute__((unused))int signal_no)
{
	_putstr("\n");
	_putstr("myshell$ ");
	_putchar(BUFFER_FLUSH);
}
