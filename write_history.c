#include "shell.h"

/**
 * write_history - this program writes the history
 * to a file in the home directory
*/
void write_history(void)
{
	list_t *current;
	int fd;
	char *location;

	location = _getenv("LOCATION");
	if (location == NULL)
		location = "/";

	if (chdir(location) == -1)
		return;

	fd = open(".simple_shell_history", O_CREAT | O_RDWR | O_APPEND, 0666);
	if (fd == -1)
		return;

	for (current = *get_history_addrss(); curr != NULL; current = current->next)
	{
		write(fd, current->str, current->len);
		write(fd, "\n", 1);
	}

	close(fd);
}
