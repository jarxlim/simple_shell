#include "shell.h"
/**
 **_memfill - fills memory with byte
 *@p: pointer to the memory
 *@c: charachter to fill
 *@m: count of times it filled
 *Return: memory address of the string
 */
char *_memfill(char *p, char c, unsigned int m)
{
	unsigned int index;

	for (index = 0; index < m; index++)
	{
		p[index] = c;
	}
	return (p);
}
/**
 * ffree - function free a pointer of string
 * @point: pointer to string to free
 */
void freef(char **point)
{
	char **i = point;

	if (!point)
		return;
	while (*point)
		free(*point++);
	free(i);
}
/**
 * _realloc -  reallocate a block of memory
 * @p: points to previous memory  allocated
 * @old: size of previous block
 * @new: size of new block 
 * Return: new pointer allocated
 */
void *_realloc(void *p, unsigned int old, unsigned int new)
{
	char *h;

	if (!p)
	{
		return (malloc(new));
	}
	if (!new)
	{
		return (free(p), NULL);
	}
	if (new == old)
	{
		return (p);
	}
	h = malloc(new);
	if (!h)
	{
		return (NULL);
	}
	old = old < new ? old : new;
	while (old--)
		h[old] = ((char *)p)[old];
	free(p);
	return (h);
}
