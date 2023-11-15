#include "shell.h"

/**
 * validate_env_name - this program validates a env var name
 * @name: parameter for string to be validated
 *
 * Return: it returns 0 on success but -1 on error
*/
int validate_env_name(char *name)
{
	if (name == NULL)
	{
		print_builtin_error("setenv: Needs 2 args", "");
		return (-1);
	}

	if (!is_valid_env_var_name(name))
	{
		print_builtin_error("setenv: Invalid name ", name);
		return (-1);
	}

	return (0);
}

/**
 * is_valid_env_var_name - this program checks if the env name is valid
 * @name: parameter for string to be checked
 *
 * Return: it returns 1 if is valid, 0 otherwise
*/
int is_valid_env_var_name(char *name)
{
	int i;
	/* Verify that name is a valid env_var name (without "=") */
	for (i = 0; name[i] != '\0'; i++)
		if (name[i] == '=')
			return (0);

	return (1);
}

/**
 * get_env_index - this program check if a env
 * variable exists and returns the index
 * @name: parameter for name to be searched
 *
 * Return: it returns index of the env var, -1 on error
*/
int get_env_index(char *name)
{
	int i;
	int length = get_string_length(name);

	for (i = 0; __environ[i] != NULL; i++)
		if (comp_nstrings(__environ[i], name, length) == 0)
			return (i);

	return (-1);
}
