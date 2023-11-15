#include "shell.h"

/**
 * display_list - Print the lists
 * @lst: Linked list with format linked_list_t
 * Return: Number of nodes in the linked list
 */
size_t display_list(const list_t *lst)
{
	unsigned int node_count = 0;

	while (lst != NULL)
	{
		if (lst->str)
		{
			_print_str(number_to_string(lst->len));
			_print_str(" ");
			_print_str(lst->str);
			_print_str("\n");
		}
		else
			_print_str("[0] (nil)\n");
		lst = lst->next;
		node_count++;
	}
	return (node_count);
}

/**
 * append_end - Add a new node at the end of the linked list
 * @first_node: Pointer to the first node
 * @data: Content of the string for the new node
 * Return: Pointer to the new end node
 */
list_t *append_end(list_t **first_node, const char *str)
{
	list_t *new_end_node, *temp;

	new_end_node = malloc(sizeof(list_t));

	if (new_end_node == NULL)
		return (NULL);

	new_end_node->str = duplicate_string(str);
	new_end_node->len = get_string_length(str);
	new_end_node->next = NULL;

	if (*first_node == NULL)
	{
		*first_node = new_end_node;
		return (*first_node);
	}
	temp = *first_node;
	while (temp->next != NULL)
		temp = temp->next;
	temp->next = new_end_node;
	return (new_end_node);
}

/**
 * release_list - Function that frees a linked list
 * @first_node: Pointer to the first node
 * Return: Void -> Frees the linked list
 */
void release_list(list_t *first_node)
{
	if (first_node == NULL)
		return;
	release_list(first_node->next);
	free(first_node->str);
	free(first_node);
}
