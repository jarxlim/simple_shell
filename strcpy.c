#include "main.h"
/**
 *_strncpy - function to copy a string
 *@dest: the destination pointer to the copy
 *@src: the source pointer to the string
 *@n: the amount of chars to be copied
 *Return: the string of copy string
 */
char *_strncpy(char *dest, char *src, int n)
{
	int a, b;
	char *copy = dest;

	a = 0;
	while (src[a] != '\0' && a < n - 1)
	{
		dest[a] = src[a];
		a++;
	}
	if (a < n)
	{
		b = a;
		while (b < n)
		{
			dest[b] = '\0';
			b++;
		}
	}
	return (copy);
}
/**
 *_strncat - concatenating function of two strings
 *@dest: the first string
 *@src: the second string
 *@n: the amount of bytes to use
 *Return: the concatenated string
 */
char *_strncat(char *dest, char *src, int n)
{
	int a, b;
	char *concat = dest;

	a = 0;
	b = 0;
	while (dest[a] != '\0')
		a++;
	while (src[b] != '\0' && b < n)
	{
		dest[a] = src[b];
		a++;
		b++;
	}
	if (b < n)
		dest[a] = '\0';
	return (concat);
}
/**
 *_strchr -function find the character in a string
 *@s: the string to check in
 *@c: the character to be checkd
 *Return: character found in s
 */
char *_strchr(char *s, char c)
{
	do {
		if (*s == c)
			return (s);
	} while (*s++ != '\0');

	return (NULL);
}
