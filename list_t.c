#include "main.h"
/**
 * list_len -function to return the length of linked list
 * @h: pointer to first node in tyhe list
 * Return: size of linked list
 */
size_t list_len(const list_t *h)
{
	size_t i = 0;

	while (h)
	{
		h = h->next;
		i++;
	}
	return (i);
}
/**
 * list_to_strings - functtion to return an array of strings of the list
 * @head: pointer to first node of the list
 * Return: array of strings in the list
 */
char **list_to_strings(list_t *head)
{
	list_t *node = head;
	size_t a = list_len(head), b;
	char **string;
	char *str;

	if (!head || !a)
		return (NULL);
	string = malloc(sizeof(char *) * (a + 1));
	if (!string)
		return (NULL);
	for (a = 0; node; node = node->next, a++)
	{
		str = malloc(_strlen(node->str) + 1);
		if (!str)
		{
			for (b = 0; b < a; b++)
				free(string[b]);
			free(string);
			return (NULL);
		}

		str = _strcpy(str, node->str);
		string[a] = str;
	}
	string[a] = NULL;
	return (string);
}
/**
 * print_list - function to print all elements of a list_t linked list
 * @head: pointer to first node of the list
 * Return: size of the list
 */
size_t print_list(const list_t *head)
{
	size_t a = 0;

	while (head)
	{
		_puts(convert_number(head->num, 10, 0));
		_putchar(':');
		_putchar(' ');
		_puts(head->str ? head->str : "(nil)");
		_puts("\n");
		head = head->next;
		a++;
	}
	return (a);
}
/**
 * node_starts_with - function to return node in lthee list whose string
 * @node: pointer to the head of list
 * @prefix: string t compare
 * @c: the next char that follows the prefix matched
 * Return:found nodes or null
 */
list_t *node_starts_with(list_t *node, char *prefix, char c)
{
	char *d = NULL;

	while (node)
	{
		d = starts_with(node->str, prefix);
		if (d && ((c == -1) || (*d == c)))
			return (node);
		node = node->next;
	}
	return (NULL);
}
/**
 * get_node_index -function to get the index of a node
 * @head: pointer to list head
 * @node: pointer to the node
 * Return: index of node if found or -1 when not found
 */
ssize_t get_node_index(list_t *head, list_t *node)
{
	size_t a = 0;

	while (head)
	{
		if (head == node)
			return (a);
		head = head->next;
		a++;
	}
	return (-1);
}
