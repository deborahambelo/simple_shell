#include "shell.h"
/**
 *is_empty_command - Check if no command was entered
 * @commands: Array of commands
 *
 * Return: 1 if no command was entered (just spaces and ENTER), 0 otherwise
 */
int is_empty_command(char **commands)
{
	if (commands[0] == NULL || compare_strings(commands[0], "\n") == 0)
		return (1);
	return (0);
}
