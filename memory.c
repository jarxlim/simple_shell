#include "main.h"
/**
 **_memset - function to fill memory with a constant byte provided
 *@s: the pointer to the memory to fill
 *@b: charachter to fill
 *@n: the amount of times to be filled in the memory
 *Return: memory address of the string filled
 */
char *_memset(char *s, char b, unsigned int n)
{
	unsigned int a;

	for (a = 0; a < n; a++)
		s[a] = b;
	return (s);
}
/**
 * ffree - function free a pointer of string
 * @point: pointer to string to free
 */
void ffree(char **point)
{
	char **i = point;

	if (!point)
		return;
	while (*point)
		free(*point++);
	free(i);
}
/**
 * _realloc - function to reallocate a block of memory
 * @ptr: pointer to previous memory block allocated
 * @old_size: size of previous block in bytes
 * @new_size: size of new block in bytes
 * Return: new pointer allocated
 */
void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size)
{
	char *h;

	if (!ptr)
		return (malloc(new_size));
	if (!new_size)
		return (free(ptr), NULL);
	if (new_size == old_size)
		return (ptr);

	h = malloc(new_size);
	if (!h)
		return (NULL);

	old_size = old_size < new_size ? old_size : new_size;
	while (old_size--)
		h[old_size] = ((char *)ptr)[old_size];
	free(ptr);
	return (h);
}
