#include "shell.h"

/*
 * main - program that handles command lines with arguments
 *
 * Return: It returns 0
 */

int main(void)
{
	char *com = NULL;
	char *com_cpy = NULL;
	char *token = NULL;
	char *delim = " \n";
	size_t n = 0;
	int argc = 0;
	int j = 0;
	char **argv = NULL;

	printf("$ ");
	if (getline (&com, &n, stdin) == -1)
		return (-1);

	com_cpy = strdup(com);

	token = strtok(com, delim);

	while (token)
	{
		token = strtok(NULL, delim);
		argc = argc + 1;
	}

	printf("%d\n", argc);

	argv = malloc(sizeof(char *) * argc);

	token = strtok(com_cpy, delim);

	while (token)
	{
		argv[j] = token;
		token = strtok(NULL, delim);
		j++;
	}
	argv[j] = NULL;

	for (int j = 0; argv[j]; j++)
		printf("%s\n", argv[j]);

	free(com), free(com_cpy), free(argv);

	return (0);
}
