#include "shell.h"

/**
* main - A simple UNIX command line interpreter (shell).
*
* Return: Always 0.
*/
int main(void)
{
	size_t buffer_size = 0;
	char *buffer = NULL;
	ssize_t read;
	char *tokenized_buf[buffer_size];

	while (1)
	{
		handleCommand(&buffer, &buffer_size, &read);
		if (read == -1)
		{
			printf("\n");
			break;
		}
		executeCommand(buffer, tokenized_buf);
		free(buffer);
		buffer = NULL;
	}
	return (0);
}
/**
 * handleCommand - Handles user input and command execution in the shell.
 * @buffer: Pointer to a character array for storing user-entered commands.
 * @buffer_size: Pointer to the size of the buffer for memory allocation.
 * @read: Pointer to the number of characters read from user input.
 */
void handleCommand(char **buffer, size_t *buffer_size, ssize_t *read)
{
	write(1, "#cisfun$ ", 9);
	*read = getline(buffer, buffer_size, stdin);

	if (*read == -1)
	{
		return;
	}
	(*buffer)[*read - 1] = '\0';
}
/**
 * executeCommand - Tokenizes and executes a user-entered shell command.
 * @buffer: The user-entered command line stored as a string.
 * @tokenized_buf: An array the tokenized components
 */
void executeCommand(char *buffer, char **tokenized_buf)
{
	char *token;
	int i = 0;
	int status;

	token = strtok(buffer, " \t\n");
	while (token)
	{
		tokenized_buf[i++] = token;
		token = strtok(NULL, " \t\n");
	}
	tokenized_buf[i] = NULL;
	pid_t child_pid = fork();

	if (child_pid == 0)
	{
		if (execve(tokenized_buf[0], tokenized_buf, NULL) == -1)
		{
			perror(tokenized_buf[0]);
			exit(EXIT_FAILURE);
		}
	}
	else
	{
		wait(&status);
	}
}
