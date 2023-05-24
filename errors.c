#include "shell.h"

/**
 * _strtoint - convert string to an integer
 * @s: string to be converted
 * Return: 0 on success and -1 for failure
 */
int _strtoint(char *s)
{
	int a = 0;
	unsigned long int output = 0;

	if (*s == '+')
	{	
		s++;
	}
	for (a = 0;  s[a] != '\0'; a++)
	{
		if (s[a] >= '0' && s[a] <= '9')
		{
			output *= 10;
			output += (s[a] - '0');
			if (output > INT_MAX)
			{
				return (-1);
			}
		}
		else
			return (-1);
	}
	return (output);
}

/**
 * print_error - print an error message
 * @info: param
 * @estr: string containing error
 * Return: 0for success and -1 for error
 */
void error_printer(info_t *ifn, char *err_str)
{
	_prints(ifn->file_name);
	_prints(": ");
	write_dec(ifn->count_line, STDERR_FILENO);
	_prints(": ");
	_prints(ifn->argv[0]);
	_prints(": ");
	_prints(err_str);
}

/**
 * print_d - print a decimal number
 * @input: number to be used
 * @fd: the file use
 *
 * Return: number of chars
 */
int write_dec(int entr, int fdx)
{
	int (*__putchar)(char) = _putchar;
	int a, counter = 0;
	unsigned int _abs, current;

	if (fdx == STDERR_FILENO)
		__putchar = printchar;
	if (entr < 0)
	{
		_abs = -entr;
		__putchar('-');
		counter++;
	}
	else
		_abs = entr;
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
 * num_converter - converter from one base to another
 * @num: the number to be converted
 * @base: base to coonvert to
 * @flag: argument flags to implement
 * Return: strings
 */
char *num_converter(long int num, int base, int flag)
{
	static char *array, buffer[50];
	char *point, sign = 0;
	unsigned long number = num;

	if (!(flag & UNSIGN_CONVERTER) && num < 0)
	{
		number = -num;
		sign = '-';

	}
	array = flag & LOWER_CONVERTER ? "0123456789abcdef" : "0123456789ABCDEF";
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
 * comment_deleter - function to replace first
 * @buffer: address of the string tobe modified
 * Return: Always 0;
 */
void comment_deleter(char *buffer)
{
	int a;

	for (a = 0; buffer[a] != '\0'; a++)
	{
		if (buffer[a] == '#' && (!a || buffer[a - 1] == ' '))
		{
			buffer[a] = '\0';
			break;
		}
	}
}
