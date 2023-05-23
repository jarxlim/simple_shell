#include "shell.h"
/**
 *_strncpy - copy a string
 *@dest: destination pointer for the copy
 *@src: the source pointer
 *@amt: amount of chars to be copied
 *Return: the copied string
 */
char *_strncpy(char *dest, char *src, int amt)
{
	int a, b;
	char *copy = dest;

	a = 0;
	while (src[a] != '\0' && a < amt - 1)
	{
		dest[a] = src[a];
		a++;
	}
	if (a < amt)
	{
		b = a;
		while (b < amt)
		{
			dest[b] = '\0';
			b++;
		}
	}
	return (copy);
}
/**
 *_strncat - concatenates of two strings
 *@s1: the first string
 *@s2: the second string
 *@amt: amount of bytes to use
 *Return: the concatenated string
 */
char *_strncat(char *s1, char *s2, int amt)
{
	int a, b;
	char *concat = s1;

	a = 0;
	b = 0;
	while (a = 0; s1[a] != '\0'; a++)
	{
		a++;
	}
	while (s2[b] != '\0' && b < amt)
	{
		s1[a] = s2[b];
		a++;
		b++;
	}
	if (b < amt)
	{
		s1[a] = '\0';
	}
	return (concat);
}
/**
 *_strchr -finds the character in a string
 *@str: string to check in
 *@chr: character to be checked
 *Return: character
 */
char *_strchr(char *str, char chr)
{
	do {
		if (*str == chr)
		{
			return (str);
		}
	} while (*str++ != '\0');

	return (NULL);
}
