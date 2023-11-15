#include "shell.h"

/**
 * alloc_mem - Manages memory allocation
 * @bytes: Number representing the size in bytes to allocate
 *
 * Return: Pointer to the newly allocated memory
*/
void *alloc_mem(unsigned int bytes)
{
	char *new_mem = malloc(bytes);

	if (new_mem == NULL)
		err_dispatch("Error while allocating memory\n");

	return (new_mem);
}

/**
 * dup_str - Duplicates a given string
 * @s: String to duplicate
 *
 * Return: Pointer to the address of the newly duplicated string
*/
char *dup_str(char *s)
{
	char *str_copy = duplicate_string(s);

	if (str_copy == NULL)
		err_dispatch("Error while making copy of string");

	return (str_copy);
}

/**
 * free_dbp - Frees the memory pointed to by a double pointer
 * @dp: Double pointer
*/
void free_dbp(char **dp)
{
	int i;

	if (dp == NULL)
		return;

	for (i = 0; dp[i]; i++)
		free(dp[i]);

	free(dp);
}

/**
 * release_memory - Frees allocated memory
 * @buffer: Main buffer
 * @cmds_list: List of commands
 * @cmd_args: Command as an array of arguments
 * @flags: Number indicating which memory to free
*/
void release_memory(char *buffer, char **cmds_list, char **cmd_args, int flags)
{
	if (flags & F_BUFF)
		free(buffer);
	if (flags & F_CMD_L)
		free_dbp(cmds_list);
	if (flags & F_CMDS)
		free_dbp(cmd_args);

	free_list(*(get_alias_head()));
	free_history();
}
