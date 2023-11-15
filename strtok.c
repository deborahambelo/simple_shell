#include "shell.h"

/* GLOBAL VAR TKN_PTR */
static char *TKN_PTR = "";
static int NO_INIT_TKN_PTR = 1;

/* helper function prototype */
int is_delimiter_char(char b, char *delimiter);

/**
 * _strtok - program that divides a string into tokens
 * @str: parameter for string to be divided
 * @delimiter: parameter for delimiter to str will be divided
 * Return: it returns token in string
*/

char *_strtok(char *str, char *delimiter)
{
	char *position;
	char *tokenStart = NULL;

	if (NO_INIT_TKN_PTR == 1)
	{
		TKN_PTR = NULL;
		NO_INIT_TKN_PTR = 0;
	}

	if ((str == NULL && TKN_PTR == NULL) || (str != NULL && str[0] == '\0'))
		return (NULL);

	if (str != NULL)
		TKN_PTR = str;

	for (position = TKN_PTR; *position != '\0'; position++)
	{
		if (!is_delimiter_char(*position, delimiter))
		{
			tokenStart = position;
			while (*position != '\0' && !is_delimiter_char(*position, delimiter))
				position++;

			TKN_PTR = position + 1;
			if (*position == '\0')
				TKN_PTR = position;
			*position = '\0';

			return (tokenStart);
		}
	}

	return (NULL);
}

/**
 * is_delimiter_char - program that evaluates if a char is a delimiter or not
 * @b: parameter for char to evaluate
 * @delimiter: parameter for set of chars as delimiters
 * Return: it returns 1 if b is a delimiter and 0 if not
*/
int is_delimiter_char(char b, char *delimiter)
{
	while (*delimiter != '\0')
	{
		if (b == *delimiter)
			return (1);
		delimiter++;
	}

	return (0);
}
