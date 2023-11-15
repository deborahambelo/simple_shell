#include "shell.h"

/**
 * _print_str - Program that prints a string to stdout
 * @str: parameter for string to be printed
 *
 * Return: it returns a number of chars printed
*/

int _print_str(char *str)
{
	int len = _strlen(str);

	write(STDOUT_FILENO, str, len);

	return (len);
}
