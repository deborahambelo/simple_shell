#include "shell.h"

static char *firstArg;

void handleSigint(int sigNum);
char *getFirstArg();
int handleArg(int argc, char **argv, int *execFile);


/**
 * handleArg - Check the number of arguments passed to main
 * @argc: Number of arguments
 * @argv: Array of arguments as strings
 * @execFile: Integer used to check if the user wants to execute commands from a file
 *
 * Return: File descriptor to file
*/
int handleArg(int argc, char **argv, int *execFile)
{
	int fileDesc = STDIN_FILENO;
	char *errorMessage = "Error: more than one argument\n";

	if (argc > 2)
	{
		write(STDERR_FILENO, errorMessage, get_string_length(errorMessage));
		exit(1);
	}

	if (argc == 2)
	{
		*execFile = 1;
	}

	if (fileDesc == -1)
	{
		perror(argv[0]);
		exit(1);
	}

	return (fileDesc);
}

/**
 * main - Entry point
 * @argc: Number of arguments
 * @argv: Array of arguments as strings
 * Return: 0 on success
*/
int main(int argc, char **argv)
{
	int bytesRead, execFile = 0;
	char *buffer = NULL;
	size_t bufferLength = 0;
	int fileDesc;

	firstArg = argv[0];
	signal(SIGINT, handleSigint);
	fileDesc = handleArg(argc, argv, &execFile);

	/*update_count_lines();*/

	while (1)
	{
		/* Print console symbol only if it is interactive*/
		if (isatty(STDIN_FILENO) == 1 && execFile == 0)
			write(STDOUT_FILENO, "$ ", 2);

		bytesRead = getline(&buffer, &bufferLength, stdin);
		if (bytesRead == EOF)
		{
			free(buffer);
			exit(*exitcode());
		}

		buffer = rmvcom(buffer);
		splitString(buffer, "\n");
		semi_op(buffer, bytesRead, argv[0]);

	}
	/* Free buffer memory */
	free(buffer);
	if (execFile)
		close(fileDesc);
	return (*ExitcodePro());
}



/**
 * handleSigint - Avoids the current process from finishing
 * @sigNum: Signal number
*/
void handleSigint(int __attribute__((unused))sigNum)
{
	write(STDIN_FILENO, "\n$ ", 3);
}

/**
 * getFirstArg - Returns the first argument passed to main
 *
 * Return: Pointer to the first arg passed to main
*/
char *getFirstArg(void)
{
	return (firstArg);
}
