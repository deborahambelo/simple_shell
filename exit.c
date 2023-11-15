#include "shell.h"

/**
 * check_exit_cmd - Checks if the user entered the exit command
 * @user_input: User's input
 * @cmds_list: Array of parsed commands
 * @user_cmds: User's input parsed as an array of commands
 *
 * Return: 0 if the command is NOT exit, -1 if the exit status was illegal
*/
int check_exit_cmd(char *user_input, char **cmds_list, char **user_cmds)
{
    int exit_status;

    /* Command is NOT exit */
    if (user_cmds[0] == NULL || compare_strings(user_cmds[0], "exit") != 0)
        return 0;

    /* Command is exit */
    if (user_cmds[1] == NULL)
    {
        write_history();
        release_memory(user_input, cmds_list, user_cmds, F_BUFF | F_CMDS);
        if (*get_process_exit_code() == 127)
            exit(2);
        exit(0);
    }

    exit_status = calcstatus(user_cmds[1]);

    /* Command is exit status */
    if (exit_status >= 0)
    {
        write_history();
        release_memory(user_input, cmds_list, user_cmds, F_BUFF | F_CMDS);
        exit(exit_status);
    }

    /* The exit status passed was illegal */
    print_builtin_error("exit: Illegal number: ", user_cmds[1]);
    return -1;
}

/**
 * calcstatus - Calculates the exit status as a number
 * @input_buffer: User's input
 *
 * Return: Exit status as a number, -1 on error
*/
int calcstatus(char *input_buffer)
{
    int i;
    int status = 0;

    for (i = 0; input_buffer[i] != '\0'; i++)
    {
        if (input_buffer[i] == '\n')
            return status;

        if (input_buffer[i] < '0' || input_buffer[i] > '9')
            return -1;

        status *= 10;
        status += input_buffer[i] - '0';
    }

    return status;
}
