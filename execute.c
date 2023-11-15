#include "shell.h"

/**
 * handleCommand - Handle user input and display prompt.
 *
 * @buffer: Pointer to the input buffer.
 * @buffer_size: Pointer to the buffer size.
 * @read: Pointer to the result of getline.
 */
void handleCommand(char **buffer, size_t *buffer_size, ssize_t *read)
{
    write(1, "#cisfun$ ", 9);
    *read = getline(buffer, buffer_size, stdin);

    if (*read == -1)
    {
        return;
    }

    (*buffer)[*read - 1] = '\0';
}

/**
 * executeCommand - Execute a command with arguments.
 *
 * @buffer: The command input.
 */
void executeCommand(char *buffer)
{
    int status;
    pid_t child_pid;

    child_pid = fork();

    if (child_pid == -1)
    {
        perror("fork");
        exit(EXIT_FAILURE);
    }

    if (child_pid == 0)
    {
        
        if (execlp("sh", "sh", "-c", buffer, (char *)NULL) == -1)
        {
            perror("./shell");
            exit(EXIT_FAILURE);
        }
    }
    else
    {
        waitpid(child_pid, &status, 0);
    }
}
       
