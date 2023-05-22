#include "main.h"
/**
 * input_buf -funct to  buffer chained commands
 * @info: parameter structure info
 * @buf: pointeer of buffer
 * @len: length of the buffer
 * Return: bytes found
 */
ssize_t input_buf(info_t *info, char **buf, size_t *len)
{
	ssize_t a = 0;
	size_t length = 0;

	if (!*len) /* if nothing left in the buffer, fill it */
	{
		/*bfree((void **)info->cmd_buf);*/
		free(*buf);
		*buf = NULL;
		signal(SIGINT, sigintHandler);
#if USE_GETLINE
		a = getline(buf, &length, stdin);
#else
		a = _getline(info, buf, &length);
#endif
		if (a > 0)
		{
			if ((*buf)[a - 1] == '\n')
			{
				(*buf)[a - 1] = '\0';
				a--;
			}
			info->linecount_flag = 1;
			remove_comments(*buf);
			build_history_list(info, *buf, info->histcount++);
			{
				*len = a;
				info->cmd_buf = buf;
			}
		}
	}
	return (a);
}

/**
 * get_input - function to get linefrom the newline
 * @info: parameter struct info for arguments
 * Return: bytes found
 */
ssize_t get_input(info_t *info)
{
	static char *buffer;
	static size_t a, b, length;
	ssize_t r = 0;
	char **buf_p = &(info->arg), *p;

	_putchar(BUF_FLUSH);
	r = input_buf(info, &buffer, &length);
	if (r == -1)
		return (-1);
	if (length)
	{
		b = a;
		p = buffer + a;

		check_chain(info, buffer, &b, a, length);
		while (b < length)
		{
			if (is_chain(info, buffer, &b))
				break;
			b++;
		}

		a = b + 1;
		if (a >= length)
		{
			a = length = 0;
			info->cmd_buf_type = CMD_NORM;
		}

		*buf_p = p;
		return (_strlen(p));
	}

	*buf_p = buffer;
	return (r);
}
/**
 * read_buf - function to read a buffer
 * @info: parameter struct called info
 * @buf: buffer inputed
 * @i: size of input buff
 * Return: length of the buffer
 */
ssize_t read_buf(info_t *info, char *buf, size_t *i)
{
	ssize_t a = 0;

	if (*i)
		return (0);
	a = read(info->readfd, buf, READ_BUF_SIZE);
	if (a >= 0)
		*i = a;
	return (a);
}
/**
 * _getline - function to get next line of input fron standard input
 * @info: parameter struct for arguments
 * @ptr: pointer to buffer
 * @length: size of ptr if not NULL
 * Return: size of the line
 */
int _getline(info_t *info, char **ptr, size_t *length)
{
	size_t k;
	static char buf[READ_BUF_SIZE];
	static size_t a, leng;
	char *p = NULL, *c, *new_p = NULL;
	ssize_t hh = 0, sh = 0;

	p = *ptr;
	if (p && length)
		sh = *length;
	if (a == leng)
		a = leng = 0;

	hh = read_buf(info, buf, &leng);
	if (hh == -1 || (hh == 0 && leng == 0))
		return (-1);

	c = _strchr(buf + a, '\n');
	k = c ? 1 + (unsigned int)(c - buf) : leng;
	new_p = _realloc(p, sh, sh ? sh + k : k + 1);
	if (!new_p)
		return (p ? free(p), -1 : -1);

	if (sh)
		_strncat(new_p, buf + a, k - a);
	else
		_strncpy(new_p, buf + a, k - a + 1);

	sh += k - a;
	a = k;
	p = new_p;

	if (length)
		*length = sh;
	*ptr = p;
	return (sh);
}
/**
 * sigintHandler - handle blocks ctrl-C
 * @sig_num: the signal number
*/
void sigintHandler(__attribute__((unused))int sig_num)
{
	_puts("\n");
	_puts("$ ");
	_putchar(BUF_FLUSH);
}
