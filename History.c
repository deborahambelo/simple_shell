#include "shell.h"

/* Global variables */
static int no_init_history;
static list_t *history_head;
static list_t *last_cmd;

/**
 * get_history_addrss - this program return the address oof history head
 *
 * Return: it returns address of history head
*/
list_t **get_history_addrss()
{
	if (no_init_history == 1)
	{
		history_head = NULL;
		last_cmd = NULL;
		no_init_history = 0;
	}

	return (&history_head);
}

/**
 * get_last_cmd_addrss - Return the address oof history head
 *
 * Return: Address of last entered command
*/
list_t **get_last_cmd_addrss()
{
	if (no_init_history == 1)
	{
		history_head = NULL;
		last_cmd = NULL;
		no_init_history = 0;
	}

	return (&last_cmd);
}

/**
 * _history - this program prints the all the commands entered by the user
 *
 * Return: it returns 1 on success
*/
int _history(void)
{
	list_t *curr;
	char *str_num;
	int i, length;
	int count = *get_history_lines_count() % 4096;

	for (current = *get_history_addrss(); current != NULL; current= current->next)
	{
		str_num = num_to_str(count++);
		length = _print_str(str_num);
		for (i = length; i < 7; i++) /* 5 per number, 2 aditional */
			_print_str(" ");
		_print_str(current->str);
		_puts("\n");
		free(str_num);
	}

	return (1);
}

/**
 * handle_history - this program adds a command to the history
 * @buff: parameter for user's input
*/
void handle_history(char *buffer)
{
	/* Only adds a command if is different from the previous one */
	if (last_cmd == NULL || buffer[0] != ' ' || comp_nstrings(last_cmd->str, buffer) != 0)
		last_cmd = add_node_end(get_history_addrss(), buffer);
}

/**
 * free_history - this program frees the memory used by history list
*/
void free_history(void)
{
	free_list(*get_history_addrss());
}
