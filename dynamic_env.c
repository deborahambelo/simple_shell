#include "shell.h"

/**
 * allocate_dynamic_environ - Builds the "env_vars" array using dynamic memory
 */
void allocate_dynamic_environ(void)
{
    int env_count = 0;
    char **new_env_vars;

    while (__environ[env_count] != NULL)
        env_count++;

    new_env_vars = alloc_mem(sizeof(char *) * (env_count + 1));
    for (env_count = 0; __environ[env_count] != NULL; env_count++)
        new_env_vars[env_count] = dup_str(__environ[env_count]);

    /* Last element should be NULL */
    new_env_vars[env_count] = NULL;
    /* Assign new memory dynamically allocated */
    __environ = new_env_vars;
}

/**
 * deallocate_dynamic_environ - Frees the memory allocated to hold "env_vars"
 */
void deallocate_dynamic_environ(void)
{
    free_dbp(__environ);
}
