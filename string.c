#include "main.h"
/**
 * _strcpy - string copt function
 * @dest: the destination pointer of the copy of the string
 * @src: the source of the string to be copied
 * Return: pointer to destinationn pointer  of the copied string
 */
char *_strcpy(char *dest, char *src)
{
	int a = 0;

	if (dest == src || src == 0)
		return (dest);
	while (src[a])
	{
		dest[a] = src[a];
		a++;
	}
	dest[a] = 0;
	return (dest);
}
/**
 * _strdup -string duplicating function
 * @str: the given string to duplicate
 * Return: pointer to the duplicated string
 */
char *_strdup(const char *str)
{
	int len = 0;
	char *tel;

	if (str == NULL)
		return (NULL);
	while (*str++)
		len++;
	tel = malloc(sizeof(char) * (len + 1));
	if (!tel)
		return (NULL);
	for (len++; len--;)
		tel[len] = *--str;
	return (tel);
}
/**
 *_puts - printing function of the string
 *@str: input string to be printed
 */
void _puts(char *str)
{
	int p = 0;

	if (!str)
		return;
	while (str[p] != '\0')
	{
		_putchar(str[p]);
		p++;
	}
}
/**
 * _putchar - function to write the character c to stdout
 * @c: The character enterd to print/write
 * Return: On success 1. On error, -1 is returned.
 */
int _putchar(char c)
{
	static int p;
	static char buffer[WRITE_BUF_SIZE];

	if (c == BUF_FLUSH || p >= WRITE_BUF_SIZE)
	{
		write(1, buffer, p);
		p = 0;
	}
	if (c != BUF_FLUSH)
		buffer[p++] = c;
	return (1);
}
