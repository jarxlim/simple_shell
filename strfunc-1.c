#include "shell.h"
/**
 * _strlen - return the length of a string
 * @string: string to use
 * Return: length of string in integer
 */
int _strlen(char *string)
{
	int length = 0;

	if (!string)
	{
		return (0);
	}
	while (*string++)
	{
		length++;
	}
	return (length);
}
/**
 * _strcmp - function to make string compare
 * @string1: the first strng
 * @string2: the second strng
 * Return: negative, positive  or zore
 */
int _strcmp(char *string1, char *string2)
{
	while (*string1 && *string2)
	{
		if (*string1 != *string2)
			return (*string1 - *string2);
		string1++;
		string2++;
	}
	if (*string1 == *string2)
		return (0);
	else
		return (*string1 < *string2 ? -1 : 1);
}
/**
 * _leet - checks if needle starts with haystack
 * @haystacks: string to check
 * @needles: the substring to check
 * Return: next char of haystack or NULL
 */
char *_leet(const char *haystacks, const char *needles)
{
	while (*needles)
	{
		if (*needles++ != *haystacks++)
			return (NULL);
	}
	return ((char *)haystacks);
}
/**
 * _strcat - concatenates string variables
 * @s1: first string param
 * @s2: The second string param
 * Return: concatenated string
 */
char *_strcat(char *s1, char *s2)
{
	char *concat = s1;

	while (*s1)
	{
		s1++;
	}
	while (*s2)
	{
		*s1++ = *s2++;
	}
	*s1 = *s2;
	return (concat);
}
