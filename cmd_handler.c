#include "shell.h"
/**
 * parse_input - Buidls strings as arguments
 * @str_input: Command input given by the user
 * @delimiter: String od chars indicating the delimiters
 *
 * Return: Array of strings
*/
char **parse_input(char *input, char *delimiter)
{
    int i, args_count = 0;
    char **args;
    char *token, *tkn_ptr;
    char *str_copy;

    if (input == NULL)
        err_dispatch("Error while parsing the command\n");

    args_count = count_args(input, delimiter);
    args = alloc_mem(sizeof(char *) * (args_count + 1));
    str_copy = dup_str(input);
    tkn_ptr = str_copy;
    for (i = 0; i < args_count; i++)
    {
        token = splitString(tkn_ptr, delimiter);
        if (token == NULL)
            break;
        tkn_ptr = NULL;
        args[i] = dup_str(token);
    }
    args[i] = NULL;

    free(str_copy);

    return (args);
}
/**
 * count_args - Counts the number of arguments in a command string
 * @str_input: Command as a string
 * @delimiter: Delimiter by wich to separate the args
 *
 * Return: Number of arguments present in str_input
*/
int count_args(char *input, char *delimiter)
{
    char *tkn, *tkn_ptr;
    int count = 0;
    char *str_copy = dup_str(input);

    tkn_ptr = str_copy;
    while ((tkn = splitString(tkn_ptr, delimiter)) != NULL)
    {
        count++;
        tkn_ptr = NULL;
    }

    free(str_copy);

    return (count);
}
/**
 * pathhandler - Checks if the command to execute could be found in PATH's dirs
 * @commands: Array of strings containing the command and args
 * Return: flag 0 if is succes; -1 if is error
*/
int pathhandler(char **commands)
{
    char *path_dirs, *path;
    char *tkn, *tkn_ptr;
    char *str_copy;
    int flag = 127;

    if (
        commands == NULL || commands[0] == NULL ||
        commands[0][0] == '\0' || commands[0][0] == '/'
    )
        return (127);

    if (access(commands[0], F_OK) == 0)
        return (0);

    path_dirs = Getenviron("PATH");
    if (path_dirs == NULL)
        return (127);

    str_copy = dup_str(path_dirs);
    tkn_ptr = str_copy;
    while (1)
    {
        tkn = splitString(tkn_ptr, ":");
        if (tkn == NULL)
            break;
        tkn_ptr = NULL;
        path = get_path(tkn, commands[0]);
        if (access(path, F_OK) != -1)
        {
            free(commands[0]);
            commands[0] = path;
            flag = 0;
            break;
        }
        free(path);
    }
    free(str_copy);
    return (flag);
}
/**
 * get_path - representing a full path to file
 * @dir: String indicating directory path
 * @filename: Name of the file we are looking for
 *
 * Return: String as a full path to "filename"
*/
char *get_path(char *dir, char *filename)
{
    int dir_len = get_string_length(dir);
    int filename_len = get_string_length(filename);
    char *path;

    path = alloc_mem(sizeof(char *) * (dir_len + filename_len + 2));

    _strcpy(path, dir);
    concatenate_strings(path, "/");
    concatenate_strings_n(path, filename, filename_len + 1);

    return (path);
}
