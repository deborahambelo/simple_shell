#include "shell.h"

/**
 * Getenviron - this program returns a pointer to a environment variable value
 * @identity: parameter environment variable name
 *
 * Return: it returns pointer to environment variable value
*/

char *Getenviron(char *identity)
{
	int j;

	for (j = 0; __environ[j] != NULL; j++)
		if (comp_nstrings(__environ[j], identity, get_string_length(identity)) == 0)
			return (&__environ[j][get_string_length(identity) + 1]);

	return (NULL);
}
