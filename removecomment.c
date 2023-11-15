#include "shell.h"

/**
 * rmvcom - removes a comment from the input string
 * @input: User's input
 *
 * Return: pointer to string without comments
 */
char *rmvcom(char *input)
{
	char *without_comments = input;

	if (*input == '#')
	{
		*input = '\n';
		*(input + 1) = '\0';
	}
	while (input && *input)
	{
		if (*input == '#' && *(input - 1) == ' ')
		{
			*(input - 1) = '\n';
			*input = '\0';
			break;
		}
		input++;
	}
	return (without_comments);
}
