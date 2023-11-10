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
    char *token;
    int status;
    pid_t child_pid;
    int i;
    char **tokenized_buf;

    int token_count = 0;
    char *temp = strdup(buffer);
    token = strtok(temp, " \t\n");
    while (token)
    {
        token_count++;
        token = strtok(NULL, " \t\n");
    }
    free(temp);

    tokenized_buf = malloc((token_count + 1) * sizeof(char *));
    if (tokenized_buf == NULL)
    {
        perror("malloc");
        exit(EXIT_FAILURE);
    }

    i = 0;
    token = strtok(buffer, " \t\n");
    while (token)
    {
        tokenized_buf[i++] = token;
        token = strtok(NULL, " \t\n");
    }
    tokenized_buf[i] = NULL;

    child_pid = fork();

    if (child_pid == -1)
    {
        perror("fork");
        exit(EXIT_FAILURE);
    }

    if (child_pid == 0)
    {
        if (execve(tokenized_buf[0], tokenized_buf, NULL) == -1)
        {
            perror("./shell");
            exit(EXIT_FAILURE);
        }
    }
    else
    {
        waitpid(child_pid, &status, 0);
    }

    free(tokenized_buf);
}
