#include "shell.h"

/**
* main - Entry point for the simple shell.
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
	}
	free(buffer);
	return (0);
}

/**
* handleCommand - Handle user input and display prompt.
*
* @buffer: Pointer to the input buffer.
* @buffer_size: Pointer to the buffer size.
* @read: Pointer to the result of getline.
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
* executeCommand - Execute a command with arguments.
*
* @buffer: The command input.
* @tokenized_buf: Array of command tokens.
*/
void executeCommand(char *buffer, char **tokenized_buf)
{
	char *token;
	int status;
	int i = 0;

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
			perror("ERROR with execve function");
			exit(EXIT_FAILURE);
		}
	}
	else
	{
		wait(&status);
	}
}
