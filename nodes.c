#include "main.h"
/**
 * add_node -function add a nodes at head
 * @head:pointer to the head of the list
 * @str: str field of nod
 * @num: node index
 * Return: size of list
 */
list_t *add_node(list_t **head, const char *str, int num)
{
	list_t *new_head;

	if (!head)
		return (NULL);
	new_head = malloc(sizeof(list_t));
	if (!new_head)
		return (NULL);
	_memset((void *)new_head, 0, sizeof(list_t));
	new_head->num = num;
	if (str)
	{
		new_head->str = _strdup(str);
		if (!new_head->str)
		{
			free(new_head);
			return (NULL);
		}
	}
	new_head->next = *head;
	*head = new_head;
	return (new_head);
}
/**
 * add_node_end - function add node to the end of the list
 * @head: pinter to head of the list
 * @str: str field of node
 * @num: index to put the value of the node
 * Return: new size of the list
 */
list_t *add_node_end(list_t **head, const char *str, int num)
{
	list_t *new, *node;

	if (!head)
		return (NULL);

	node = *head;
	new = malloc(sizeof(list_t));
	if (!new)
		return (NULL);
	_memset((void *)new, 0, sizeof(list_t));
	new->num = num;
	if (str)
	{
		new->str = _strdup(str);
		if (!new->str)
		{
			free(new);
			return (NULL);
		}
	}
	if (node)
	{
		while (node->next)
			node = node->next;
		node->next = new;
	}
	else
		*head = new;
	return (new);
}

/**
 * print_list_str - function to print str element list only
 * @h: pointer to the head
 * Return: nnumber of element printed
 */
size_t print_list_str(const list_t *h)
{
	size_t j = 0;

	while (h)
	{
		_puts(h->str ? h->str : "(nil)");
		_puts("\n");
		h = h->next;
		j++;
	}
	return (j);
}
/**
 * delete_node_at_index - functionnto delete the node at a given index
 * @head: pointer to the head
 * @index: index to delete
 * Return: 1 for success or 0 for failure
 */
int delete_node_at_index(list_t **head, unsigned int index)
{
	list_t *node, *previous;
	unsigned int a = 0;

	if (!head || !*head)
		return (0);

	if (!index)
	{
		node = *head;
		*head = (*head)->next;
		free(node->str);
		free(node);
		return (1);
	}
	node = *head;
	while (node)
	{
		if (a == index)
		{
			previous->next = node->next;
			free(node->str);
			free(node);
			return (1);
		}
		a++;
		previous = node;
		node = node->next;
	}
	return (0);
}
/**
 * free_list - function to free all nodes of list
 * @head_ptr: pointer to the head
 */
void free_list(list_t **head_ptr)
{
	list_t *node, *follow, *head;

	if (!head_ptr || !*head_ptr)
		return;
	head = *head_ptr;
	node = head;
	while (node)
	{
		follow = node->next;
		free(node->str);
		free(node);
		node = follow;
	}
	*head_ptr = NULL;
}
