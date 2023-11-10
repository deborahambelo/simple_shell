#include "shell.h"

/**
* main - Entry point for the simple shell.
*
* Return: Always 0.
*/

int main(void)
{
    size_t buffer_size = 0;
    char *buffer = NULL;
    ssize_t read;

    while (1)
    {
        handleCommand(&buffer, &buffer_size, &read);
        if (read == -1)
        {
            printf("\n");
            break;
        }

        executeCommand(buffer);
    }

    free(buffer);
    return 0;
}
