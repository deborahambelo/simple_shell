#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include "shell.h"
#define MAX_INPUT_SIZE 1024
#define MAX_ARG_SIZE 100

void replace_variable(char *input, const char *variable, const char *replacement) {
    char buffer[MAX_INPUT_SIZE];
    char *pos;

    while ((pos = strstr(input, variable)) != NULL) {
        strncpy(buffer, input, pos - input);
        buffer[pos - input] = '\0';
        strcat(buffer, replacement);
        strcat(buffer, pos + strlen(variable));
        strcpy(input, buffer);
    }
}

int main() {
    char input[MAX_INPUT_SIZE];
    char *args[MAX_ARG_SIZE];
    char *token;
    int status;
    pid_t pid;
    char cwd[1024];
    int last_status = 0;

    while (1) {
        printf("$ ");
        fgets(input, sizeof(input), stdin);
        input[strcspn(input, "\n")] = 0; // Remove newline character

        // Replace $$ with process ID
        char pid_str[10];
        sprintf(pid_str, "%d", getpid());
        replace_variable(input, "$$", pid_str);

        // Replace $? with last command status
        char status_str[10];
        sprintf(status_str, "%d", last_status);
        replace_variable(input, "$?", status_str);

        // Tokenize the input
        int i = 0;
        token = strtok(input, " ");
        while (token != NULL) {
            args[i++] = token;
            token = strtok(NULL, " ");
        }
        args[i] = NULL;

        if (args[0] == NULL) {
            continue;
        }

        if (strcmp(args[0], "exit") == 0) {
            break;
        }

        pid = fork();
        if (pid == 0) {
            // Child process
            if (execvp(args[0], args) == -1) {
                perror("Error executing command");
            }
            exit(EXIT_FAILURE);
        } else if (pid < 0) {
            // Fork failed
            perror("Error forking");
        } else {
            // Parent process
            do {
                waitpid(pid, &status, WUNTRACED);
            } while (!WIFEXITED(status) && !WIFSIGNALED(status));

            if (WIFEXITED(status)) {
                last_status = WEXITSTATUS(status);
            }
        }
    }

    return 0;
}
