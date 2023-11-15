#include "shell.h"

/**
 * process_VariableReplace - program that handles dollar character '$'
 * @c_md: parameter for array of commands
*/

void process_VariableReplace(char **c_md)
{
	int j;
	char *environment_value;

	if (c_md[0] == NULL)
		return;

	/* command args and replace the needed ones using PATH, and $$, $? */
	for (j = 1; c_md[i] != NULL; i++)
	{
		if (c_md[j][0] != '$')
			continue;
		/*  arg starts with '$' */

		if (compare_strings(&c_md[j][1], "?") == 0)
		{
			free(c_md[j]);
			c_md[j] = number_to_string(*ExitcodePro());
			return;
		}

		if (compare_strings(&c_md[j][1], "$") == 0)
		{
			free(c_md[j]);
			c_md[j] = number_to_string(getpid());
			return;
		}

		environment_value = Getenviron(&c_md[j][1]);
		if (environment_value != NULL)
		{
			free(c_md[j]);
			c_md[j] = dup_str(environment_value);
		}
	}


}
