#include "shell.h"

/**
 * _getenv - this program returns a pointer to a environment variable value
 * @name: parameter environment variable name
 *
 * Return: it returns pointer to environment variable value
*/

char *_getenv(char *name)
{
	int j;

	for (j = 0; __environ[j] != NULL; j++)
		if (comp_nstrings(__environ[j], name, get_string_length(name)) == 0)
			return (&__environ[j][get_string_length(name) + 1]);

	return (NULL);
}
