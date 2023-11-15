#include "shell.h"

static int not_init_alias_head = 1;
static list_t *alias_head;

/**
 * get_alias_head - this program returns alias_head pointer
 *
 * Return: it returns pointer to alias head var
*/
list_t **get_alias_head()
{
	if (not_init_alias_head == 1)
	{
		alias_head = NULL;
		not_init_alias_head = 0;
	}
	return (&alias_head);
}

/**
 * is_set_alias - this program checks if the alias input is meant to set an alias
 * @mem_alias_pair: parameter for string as alias arg input
 *
 * Return: it returns 1 for true, 0 otherwise
*/
int is_set_alias(char *mem_alias_pair)
{
	int i;

	/* Check for the '=' sign */
	/* the '=' sign shouldn't at indx 0 */
	for (i = 1; mem_alias_pair[i] != '\0'; i++)
		if (mem_alias_pair[i] == '=')
			return (1);

	return (0);
}

/**
 * set_alias - this program adds, updates aliases
 * @mem_alias_pair: parameter for string in the form name=value
*/
void set_alias(char *mem_alias_pair)
{
	char tem_buffer[250];
	int first_eq, last_eq;
	list_t *current;
	list_t **alias_addrs = get_alias_head();

	/* Find first '=' sign */
	for (first_eq = 1; mem_alias_pair[first_eq] != '\0'; first_eq++)
		if (mem_alias_pair[first_eq] == '=')
			break;

	/* Copy the text before '=' */
	strncpy(tem_buffer, mem_alias_pair, first_eq);
	tem_buffer[first_eq] = '\0';
	/* Append = and ' symbols */
	concatenate_strings(tem_buffer, "='");

	/* Find last eq in case of putting '=' secuentially */
	for (last_eq = first_eq; mem_alias_pair[last_eq] != '\0'; last_eq++)
		if (mem_alias_pair[last_eq] != '=')
			break;

	/* Copy the second part of the alias */
	concatenate_strings(tem_buffer, &mem_alias_pair[last_eq]);
	concatenate_strings(tem_buffer, "'");

	/* Add alias to the global list */
	for (current = *mem_alias_addrs; current != NULL; current = current->next)
		if (comp_nstrings(current->str, mem_alias_pair, first_eq) == 0 &&
				(current->str)[first_eq] == '=')
		{ /* Update already existing alias */
			free(current->str);
			current->str = duplicate_string(tem_buffer);
			return;
		}

	/* Add new alias to the list */
	add_node_end(alias_addrs, tem_buffer);
}

/**
 * handle_alias_args - this program evaluates alias
 * input command and decides what to do
 * @commands: parameter for arrays of commands
 * @out_addrs: parameter for pointer to out's head node
 *
 * Return: it returns -1 if error happens but 0 if otherwise
*/
int handle_alias_args(char **commands, list_t **out_addrs)
{
	int i, length, was_alias;
	int status = 0;
	list_t *current;
	list_t **alias_addrs = get_alias_head();

	ExitcodeProSet(0);
	for (i = 1; commands[i] != NULL; i++)
	{
		was_alias = 0;
		length = get_string_length(commands[i]);
		/* Check that if user is trying to print an alias */
		for (current = *alias_addrs; current != NULL; current = current->next)
		{
			if (comp_nstrings(current->str, commands[i], length) == 0 && (current->str)[length] == '=')
			{ /* Means to list an alias */
				was_alias = 1;
				add_node_end(out_addrs, current->str);
				break;
			}
		}
		if (was_alias)
			continue;
		/* Here, user is trying to set an alias or print an unexistent one */
		if (is_set_alias(commands[i]))
			set_alias(commands[i]); /* Validate that the set format is fine */
		else /* Print errors */
		{
			status = -1;
			ExitcodeProSet(1);
			_print_str("alias: ");
			_print_str(commands[i]);
			_print_str(" not found\n");
		}
	}

	return (status);
}

/**
 * handle_aliases - program that handle alias replacement
 * @commands: paramaeter for arrays of commands
*/
void handle_aliases(char **commands)
{
	list_t *current;
	list_t **alias_addrs = get_alias_head();
	int cmd_len = get_string_length(commands[0]);
	char *str;
	char tem_buffer[250];
	int i, alias_len = 0;

	if (commands[0] == NULL)
		return;

	/* Initialize buffer */
	for (i = 0; i < 250; i++)
		tem_buffer[i] = '\0';

	/* Search if a command is an alias */
	for (current = *alias_addrs; current != NULL; current = current->next)
	{
		str = current->str;
		if (comp_nstrings(commands[0], str, cmd_len) == 0 && str[cmd_len] == '=')
		{ /* the command is an alias */
			alias_len = get_string_length(&str[cmd_len + 2]); /* +2 beacause of "='" chars */
			strncpy(tem_buffer, &str[cmd_len + 2], alias_len - 1);
			tem_buffer[alias_len] = '\0';
			/* Free and then update the command */
			free(commands[0]);
			commands[0] = duplicate_string(tem_buffer);
			break;
		}
	}
}
