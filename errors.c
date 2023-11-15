#include "shell.h"

/**
 * err_dispatch - Dispatches an error
 * @message: Error message to print
*/
void err_dispatch(char *message)
{
    perror(message);
    exit(errno);
}

/**
 * print_builtin_err - Prints error for built-in function
 * @error_msg: Error message
 * @argument: Argument passed to built-in
*/
void pbuiltin_err(char *error_msg, char *argument)
{
    int msg_len = get_string_length(error_msg);
    char *first_av = getFirstArg();

    write(STDERR_FILENO, first_av, get_string_length(first_av));
    write(STDERR_FILENO, ": 1: ", 5);
    write(STDERR_FILENO, error_msg, msg_len);
    write(STDERR_FILENO, argument, get_string_length(argument));
    write(STDERR_FILENO, "\n", 1);
    ExitcodeProSet(2);
}
