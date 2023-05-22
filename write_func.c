#include "main.h"
/**
 *_eputs -function to print input string
  * @str: the string to be printed
  */
void _eputs(char *str)
{
	int ac = 0;

	if (!str)
		return;
	while (str[ac] != '\0')
	{
		_eputchar(str[ac]);
		ac++;
	}
}
/**
 * _eputchar - function to write the character
 * @c: The character to be printed
 * Return: On success 1.
 */
int _eputchar(char c)
{
	static int ac;
	static char buffer[WRITE_BUF_SIZE];

	if (c == BUF_FLUSH || ac >= WRITE_BUF_SIZE)
	{
		write(2, buffer, ac);
	ac = 0;
	}
	if (c != BUF_FLUSH)
		buffer[ac++] = c;
	return (1);
}
/**
 * _putfd - function to write the character
 * @c: The character to be printsd
 * @fd: The file_descriptor
 * Return: On success 1.
 */
int _putfd(char c, int fd)
{
	static int ac;
	static char buffer[WRITE_BUF_SIZE];

	if (c == BUF_FLUSH || ac >= WRITE_BUF_SIZE)
	{
		write(fd, buffer, ac);
		ac = 0;
	}
	if (c != BUF_FLUSH)
		buffer[ac++] = c;
	return (1);
}
/**
 *_putsfd - function that prints an input string
 * @str: the input string to be printed
 * @fdm: the file_descriptor
  * Return: the number of chars printed
 */
int _putsfd(char *str, int fdm)
{
	int ac = 0;

	if (!str)
		return (0);
	while (*str)
	{
		ac += _putfd(*str++, fdm);
	}
	return (ac);
}
