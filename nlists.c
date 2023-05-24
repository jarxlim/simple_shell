#include "shell.h"
/**
 * prepend_node -function add a nodes at head
 * @head:pointer to the head of the list
 * @string: str field of nod
 * @numbers: node index
 * Return: size of list
 */
list_t *prepend_node(list_t **head, const char *string, int numbers)
{
	list_t *new_head;

	if (!head)
		return (NULL);
	new_head = malloc(sizeof(list_t));
	if (!new_head)
		return (NULL);
	_memfill((void *)new_head, 0, sizeof(list_t));
	new_head->numbers = numbers;
	if (string)
	{
		new_head->str = _strdup(string);
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
 * append_node - adds node to the end list
 * @head: p0inter to the head
 * @string: string input of node
 * @numbers: the value of the node
 * Return: the new size of list
 */
list_t *append_node(list_t **head, const char *string, int numbers)
{
	list_t *new_node, *nodes;

	if (!head)
	{
		return (NULL);
	}

	nodes = *head;
	new_node = malloc(sizeof(list_t));
	if (!new_node)
	{
		return (NULL);
	}
	_memfill((void *)new_node, 0, sizeof(list_t));
	new_node->numbers = numbers;

	if (string)
	{
		new_node->str = _strdup(string);
		if (!new_node->str)
		{
			free(new_node);
			return (NULL);
		}
	}
	if (nodes)
	{
		while (nodes->next)
			nodes = nodes->next;
		nodes->next = new_node;
	}
	else
		*head = new_node;
	return (new_node);
}

/**
 * print_list_string - print string element list only
 * @p: pointer
 * Return: element printed
 */
size_t list_printer(const list_t *p)
{
	size_t j = 0;

	while (p)
	{
		_putstr(p->str ? p->str : "(nil)");
		_putstr("\n");
		p = p->next;
		j++;
	}
	return (j);
}
/**
 * detach_node - functionnto delete the node at a given index
 * @head: pointer to the head
 * @ind: index to delete
 * Return: 1 for success or 0 for failure
 */
int detach_node(list_t **head, unsigned int ind)
{
        list_t *nodes, *prev;
        unsigned int a = 0;

        if (!head || !*head)
        {
                return (0);
        }
        if (!ind)
        {
                nodes = *head;
                *head = (*head)->next;
                free(nodes->str);
                free(nodes);
                return (1);
        }
        nodes = *head;
        while (nodes)
        {
                if (a == ind)
                {
                        prev->next = nodes->next;
                        free(nodes->str);
                        free(nodes);
                        return (1);
                }
                a++;
                prev = nodes;
                nodes = nodes->next;
        }
        return (0);
}

/**
 * free_list - function to free all nodes of list
 * @head_ptr: pointer to the head
 */
void free_list(list_t **head_ptr)
{
	list_t *nodes, *follow, *head;

	if (!head_ptr || !*head_ptr)
		return;
	head = *head_ptr;
	nodes = head;
	while (nodes)
	{
		follow = nodes->next;
		free(nodes->str);
		free(nodes);
		nodes = follow;
	}
	*head_ptr = NULL;
}
