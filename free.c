#include "shell.h"

/**
 * bfree - function to make pointer set to NULL
 * @pointer: pointer to be set to NULLL
 * Return: 0 for failure and 1 for success
 */
int bfree(void **pointer)
{
	if (pointer && *pointer)
	{
		free(*pointer);
		*pointer = NULL;
		return (1);
	}
	return (0);
}
