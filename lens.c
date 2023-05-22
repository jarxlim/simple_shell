#include "main.h"
/**
 * _strlen -functionn to return the length of a string
 * @string: the string inputed to use
 * Return: length of string in integer
 */
int _strlen(char *string)
{
	int length = 0;

	if (!string)
		return (0);

	while (*string++)
		length++;
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
 * starts_with -function to check if needle starts with haystack
 * @histack: string to search
 * @needle: the substring to find
 * Return: address of next char of haystack or NULL
 */
char *starts_with(const char *histack, const char *needle)
{
	while (*needle)
		if (*needle++ != *histack++)
			return (NULL);
	return ((char *)histack);
}
/**
 * _strcat -function to  concatenate string variables
 * @dest: first string
 * @src: The second strind
 * Return: concatenated string
 */
char *_strcat(char *dest, char *src)
{
	char *cat = dest;

	while (*dest)
		dest++;
	while (*src)
		*dest++ = *src++;
	*dest = *src;
	return (cat);
}
