#include "shell.h"

/**
 * env - this program prints the environment variables to stdout
*/
void env(void)
{
	int i;
	char **env = __environ;

	for (i = 0; env[i]; i++)
	{
		write(STDOUT_FILENO, env[i], _strleng(env[i]));
		write(STDOUT_FILENO, "\n", 1);
	}

	ExitcodeProSet(0);
}

/**
 * _setenv - program that sets, adds an environment variable
 * @name: parameter for name for the new env variable
 * @value: parameter for value for the new env variable
 *
 * Return: it returns 1 on success, -1 on error
 */
int _setenv(char *name, char *value)
{
	int env_index, new_var_len;

	if (validate_env_name(name) == -1)
		return (-1);

	env_index = get_env_index(name);
	if (env_index == -1)
	{/* var doen't exist, SO CREATE IT */
		int env_count = 0;
		int previous_size, updated_size;

		while (__environ[env_count] != NULL)
			env_count++;

		previous_size = sizeof(char *) * (env_count);
		updated_size = sizeof(char *) * (env_count + 2);
		__environ = _realloc(__environ, previous_size, updated_size);
		if (__environ == NULL)
			dispatch_error("Error while _reallocating memory for new env var");

		/* The new value will be stored at index env_count */
		env_index = env_count;
		/* last value For the new env var needs to be NULL */
		__environ[env_count + 1] = NULL;
	}
	else
	{
		/* var exists, so overwrite it's value */
		free(__environ[env_index]);
	}

	new_var_len = _strleng(name) + _strleng(value) + 2;
	/* store the env var either if it exists or it needs to be overwritten */
	__environ[env_index] = allocate_memory(sizeof(char) * new_var_len);
	bounded_strcpy(__environ[env_index], name);
	concatenate_strings(__environ[env_index], "=");
	concatenate_strings(__environ[env_index], value);

	ExitcodeProSet(0);
	return (1);
}

/**
 * _unsetenv - program that removes an evironment variable
 * @name: parameter for  name for the new env variable
 *
 * Return: it returns 1 on success, -1 on error
 */
int _unsetenv(char *name)
{
	int env_index, i;

	env_index = get_env_index(name);
	if (env_index >= 0)
	{/* var exists, We can unset it */
		free(__environ[env_index]);

		for (i = env_index; __environ[i] != NULL; i++)
			__environ[i] = __environ[i + 1];

		ExitcodeProSet(0);
		return (1);
	}

	/* Var doesn't exist, we can print error or do nothing */
	ExitcodeProSet(0); /* Indicates that no error ocurred */

	return (1);
}

/**
 * _cd - program that changes the current directory of the process
 * @path: parameter for path to which change the working directory
 *
 * Return: it returns 1 on success, -1 on error
*/
int _cd(char *path)
{
	char buffer[1024];
	char *oldpwd;
	char *_path = path;

	if (_strcmp(path, "-") == 0)
		path = _getenv("OLDPWD");

	if (path == NULL)
	{
		print_builtin_error("cd: OLDPWD not set", "");
		return (-1);
	}
	/* Needed to avoid reading on freed memory */
	path = duplicate_string(path);
	/* store this dir in case of update */
	oldpwd = getcwd(buff, 1024);
	if (oldpwd == NULL)
	{
		free(path);
		print_builtin_error("cd: couldn't get current dir", "");
		return (-1);
	}
	/* Try to change the current dir */
	if (chdir(path) == -1)
	{
		free(path);
		print_builtin_error("cd: can't change cd to ", _path);
		ExitcodeProSet(1);
		return (-1);
	}
	/* Update env variables */
	_setenv("OLDPWD", oldpwd);
	_setenv("PWD", path);
	free(path);
	ExitcodeProSet(0);
	return (1);
}

/**
 * _alias - proram that sets an alias command
 * @commands: parameter for list of commands
 *
 * Return: t returns -1 on error, 0 otherwise
*/
int _alias(char **commands)
{
	int status = 0;
	list_t *curr;
	list_t *out_head = NULL;
	list_t **alias_addrs = get_alias_head();

	/* the alias args starts from position 1 */
	if (commands[1] == NULL)
	{ /* This means to list all the aliases */
		for (curr = *alias_addrs; curr != NULL; curr = curr->next)
		{
			_puts(curr->str);
			_puts("\n");
		}
		ExitcodeProSet(0);
		return (1);
	}
	/* List aliases and sets the aliases that have the form name=value */
	status = handle_alias_args(commands, &out_head);
	/* print listed alias */
	for (curr = out_head; curr != NULL; curr = curr->next)
	{
		_puts(curr->str);
		_puts("\n");
	}
	/* free list */
	free_list(out_head);
	return (status);
}
