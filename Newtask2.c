#include "shell.h"

/*
 * execute_command - program that handles command lines with arguments
 * cmd: parameter
 * Return: It returns 0
 */

void execute_command(const char *cmd)
{
	pid_t child_pid = fork();

	if (child_pid == -1)
	{

		printf("Error forking process. \n");
		exit(EXIT_FAILURE);
	}
	else if (child_pid == 0)
	{
		char *args[128];
		int arg_count = 0;

		char *token = strtok((char *)cmd, " ");
		while (token != NULL)
		{
			args[arg_count++] = token;
			token = strtok(NULL, " ");
		}
		args[arg_count] = NULL;

		execvp(args[0], args);
		perror("Error executing command. \n");
		exit(EXIT_FAILURE);
	}
	else
	{
		wait(NULL);
	}
}
