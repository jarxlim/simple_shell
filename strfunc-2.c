#include "shell.h"
/**
 * _strcpy - string copt function
 * @dest: the destination
 * @src: source of the string to be copied
 * Return: pointer to destination
 */
char *_strcpy(char *dest, char *src)
{
	int a = 0;

	if (dest == src || src == 0)
	{
		return (dest);
	}
	for (a = 0; src[a]; a++)
	{
		dest[a] = src[a];
	}
	dest[a] = 0;
	return (dest);
}
/**
 * _strdup - function to duplivate string
 * @string: the given string to duplicate
 * Return: pointer to the string
 */
char *_strdup(const char *string)
{
	int len = 0;
	char *tel;

	if (string == NULL)
	{
		return (NULL);
	}
	while (*string++)
	{
		len++;
	}
	tel = malloc(sizeof(char) * (len + 1));
	if (!tel)
	{
		return (NULL);
	}
	for (len++; len--;)
	{
		tel[len] = *--string;
	}
	return (tel);
}
/**
 *_putstr - prints string function
 *@string: input string to be used
 */
void _putstr(char *string)
{
	int index = 0;

	if (!string)
		return;
	for (index = 0; string[index] != '\0'; index++)
	{
		_putchar(string[index]);
	}
}
/**
 * _putchar - prints the char stdout
 * @chr: charactert to use
 * Return: On success 1. On error, -1 is returned.
 */
int _putchar(char chr)
{
	static int index;
	static char buffer[BUFF_W_SIZE];

	if (chr == BUFFER_FLUSH || index >= BUFF_W_SIZE)
	{
		write(1, buffer, index);
		index = 0;
	}
	if (chr != BUFFER_FLUSH)
		buffer[index++] = chr;
	return (1);
}
