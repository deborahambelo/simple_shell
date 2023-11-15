#include "shell.h"

/**
 * bounded_strncpy - this progrm copies a string
 * @dest: this is the parameter string to which
 * chars are going to be copied
 * @src: this is parameter string to be copied
 * @n: this is the number of chars to copy from src
 * Return: it returns pointer to dest
 */

char *bounded_strncpy(char *dest, char *src, int n)
{
	int count = 0;
	char *start = dest;

	while (*src != '\0' && count < n)
	{
		*(start++) = *(src++);
		count++;
	}

	while (count < n)
	{
		*(start++) = '\0';
		count++;
	}

	return (dest);
}
