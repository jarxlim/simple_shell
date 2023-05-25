#include "shell.h"
/**
 *_prints - prints an input string
  * @string: the string to be inputted
  */
void _prints(char *string)
{
	int ac = 0;

	if (!string)
	{
		return;
	}
	for (ac = 0; string[ac] != '\0'; ac++)
	{
		printchar(string[ac]);
	}
}
/**
 * printchar - prints the character
 * @chr: character to be printed
 * Return: return on success 1.
 */
int printchar(char chr)
{
	static char buffer[BUFF_W_SIZE];
	static int ac;

	if (chr == BUFFER_FLUSH || ac >= BUFF_W_SIZE)
	{
		write(STDERR_FILENO, buffer, ac);
	ac = 0;
	}
	if (chr != BUFFER_FLUSH)
	{
		buffer[ac++] = chr;
	}
	return (1);
}
/**
 * _pchar - writs the character
 * @chr: char to be printsd
 * @file_desc: file_descriptor
 * Return: return 1 if success
 */
int _pchar(char chr, int file_desc)
{
	static char buffer[BUFF_W_SIZE];
	static int ac;

	if (chr == BUFFER_FLUSH || ac >= BUFF_W_SIZE)
	{
		write(file_desc, buffer, ac);
		ac = 0;
	}
	if (chr != BUFFER_FLUSH)
	{
		buffer[ac++] = chr;
	}
	return (1);
}
/**
 *_printsf - prints an input stringing
 * @string: input string to be used
 * @filename: file_descriptor
  * Return: the number of chars printed
 */
int _printsf(char *string, int filename)
{
	int ac = 0;

	if (!string)
	{
		return (0);
	}
	while (*string)
	{
		ac = ac +  _pchar(*string++, filename);
	}
	return (ac);
}
