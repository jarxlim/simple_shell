#include "main.h"

/**
 * _erratoi -function to  convert a string to an integer
 * @s: the string to be converted
 * Return: 0 for success and -1 for failure
 */
int _erratoi(char *s)
{
	int a = 0;
	unsigned long int output = 0;

	if (*s == '+')
		s++;
	for (a = 0;  s[a] != '\0'; a++)
	{
		if (s[a] >= '0' && s[a] <= '9')
		{
			output *= 10;
			output += (s[a] - '0');
			if (output > INT_MAX)
				return (-1);
		}
		else
			return (-1);
	}
	return (output);
}

/**
 * print_error -function to print an error message
 * @info: info struct
 * @estr: string containing type if error
 * Return: 0for success and -1 for error
 */
void print_error(info_t *info, char *estr)
{
	_eputs(info->fname);
	_eputs(": ");
	print_d(info->line_count, STDERR_FILENO);
	_eputs(": ");
	_eputs(info->argv[0]);
	_eputs(": ");
	_eputs(estr);
}

/**
 * print_d - function to print a decimal number
 * @input: number to be prit=nted
 * @fd: the filede to write to
 *
 * Return: number of characters printed
 */
int print_d(int input, int fd)
{
	int (*__putchar)(char) = _putchar;
	int a, counter = 0;
	unsigned int _abs, current;

	if (fd == STDERR_FILENO)
		__putchar = _eputchar;
	if (input < 0)
	{
		_abs = -input;
		__putchar('-');
		counter++;
	}
	else
		_abs = input;
	current = _abs;
	for (a = 1000000000; a > 1; a /= 10)
	{
		if (_abs / a)
		{
			__putchar('0' + current / a);
			counter++;
		}
		current %= a;
	}
	__putchar('0' + current);
	counter++;
	return (counter);
}

/**
 * convert_number - converter function from one base to another
 * @num: number to be converted
 * @base: base to coonvert to
 * @flags: argument flags to implement
 *
 * Return: string
 */
char *convert_number(long int num, int base, int flags)
{
	static char *array, buffer[50];
	char *point, sign = 0;
	unsigned long number = num;

	if (!(flags & CONVERT_UNSIGNED) && num < 0)
	{
		number = -num;
		sign = '-';

	}
	array = flags & CONVERT_LOWERCASE ? "0123456789abcdef" : "0123456789ABCDEF";
	point = &buffer[49];
	*point = '\0';

	do	{
		*--point = array[number % base];
		number /= base;
	} while (number != 0);

	if (sign)
		*--point = sign;
	return (point);
}

/**
 * remove_comments - function to replace first
 * apperance of '#' with '\0' as removing comms
 * @buffer: address of the string tobe modified
 *
 * Return: Always 0;
 */
void remove_comments(char *buffer)
{
	int a;

	for (a = 0; buffer[a] != '\0'; a++)
		if (buffer[a] == '#' && (!a || buffer[a - 1] == ' '))
		{
			buffer[a] = '\0';
			break;
		}
}
