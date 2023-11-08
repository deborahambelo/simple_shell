#ifndef shell_h
#define shell_h

#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <stddef.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>

void executeCommand(char *buffer, char **tokenized_buf);
void handleCommand(char **buffer, size_t *buffer_size, ssize_t *read);

#endif
