#include "shell.h"

/**
 * _strcpy - this program copies the string src to dest
 * @dest: this is the parameter for destination pointer
 * @src: this is the parameter for string source
 *
 * Return: it returns pointer to destination
 */
char *_strcpy(char *dest, char *src)
{
	char *memory_address;

	memory_address = dest;

	while (*src != '\0')
	{
		*memory_address = *src;
		memory_address++;
		src++;
	}

	*memory_address = '\0';

	return (dest);
}
