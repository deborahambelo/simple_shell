#include "shell.h"

int executeEnvars(char **args);
int executeOtherSet(char **args);

/**
 * processBuiltins - Executes the shell's built-in functions if the command is one
 * @args: User's input parsed as an array of commands
 *
 * Return: 1 if the command is a built-in, 0 otherwise
*/
int processBuiltins(char **args)
{
    if (args[0] == NULL)
        return 0;

    if (executeEnvars(args))
        return 1;

    if (executeOtherSet(args))
        return 1;

    return 0;
}

/**
 * executeEnvars - Checks if a command is a built-in related to environment variables
 * @args: Array of commands
 *
 * Return: 1 if the command is a built-in, 0 otherwise
*/
int executeEnvars(char **args)
{
    if (compare_strings(args[0], "env") == 0)
    {
        if (args[1] != NULL)
            return 0;

        env();
        return 1;
    }

    if (compare_strings(args[0], "setenv") == 0)
    {
        if (args[1] == NULL || args[2] == NULL || args[3] != NULL)
            return 1;

        setEnvironmentVariable(args[1], args[2]);
        return 1;
    }

    if (compare_strings(args[0], "unsetenv") == 0)
    {
        if (args[1] == NULL || args[2] != NULL)
            return 1;

        unsetEnvironmentVariable(args[1]);
        return 1;
    }

    return 0;
}

/**
 * executeOtherSet - Checks if a command is another type of built-in
 * @args: Array of commands
 *
 * Return: 1 if the command is a built-in, 0 otherwise
*/
int executeOtherSet(char **args)
{
    if (compare_strings(args[0], "cd") == 0)
    {
        char *path = args[1];

        if (args[1] == NULL)
            path = getEnvironmentVariable("HOME");

        if (path == NULL)
            path = "/";

        changeDirectory(path);
        return 1;
    }

    if (compare_strings(args[0], "alias") == 0)
    {
        handleAlias(args);
        return 1;
    }

    if (compare_strings(args[0], "help") == 0)
    {
        displayHelp(args);
        return 1;
    }

    if (compare_strings(args[0], "history") == 0)
    {
        if (args[1] != NULL)
        {
            printBuiltinError("history: No arguments allowed", "");
            return 1;
        }

        /* displayHistory(); */
        /* return 1; */
    }

    return 0;
}
