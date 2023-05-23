#include "shell.h"
/**
 * int_checker - checks if shell is interactive mode
 * @ifn: address to the shell
 * Return: 1 if  interactive mode else 0 otherwise
 */
int int_checker(info_t *ifn)
{
	return (isatty(STDIN_FILENO) && ifn->file_reader <= 2);
}
/**
 * is_delim - function to check if character is a delimeter
 * @c: the char to check character to check
 * @delim: the delimeter string provided to be checked
 * Return: 1/0 teru or false respectively
 */
int is_delim(char c, char *delim)
{
	while (*delim)
		if (*delim++ == c)
			return (1);
	return (0);
}
/**
 *_isalpha - checking of the input is alphabetic character
 *@c: The character to input to be checked
 *Return: 1 if c is alphabetic else 0 otherwise
 */
int _isalpha(int c)
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
		return (1);
	else
		return (0);
}
/**
 *_atoi - convertint function from string to integer
 *@s: the string to be converted into integer
 *Return: numbber from the string if found . Otherwise 0
*/
int _atoi(char *s)
{
	int a, sign = 1, flag = 0, number;
	unsigned int result = 0;

	for (a = 0;  s[a] != '\0' && flag != 2; a++)
	{
		if (s[a] == '-')
			sign *= -1;

		if (s[a] >= '0' && s[a] <= '9')
		{
			flag = 1;
			result *= 10;
			result += (s[a] - '0');
		}
		else if (flag == 1)
			flag = 2;
	}

	if (sign == -1)
		number = -result;
	else
		number = result;

	return (number);
}
