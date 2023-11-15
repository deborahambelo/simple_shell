#include "shell.h"

static int COUNT_LINES;

/**
 * adjust_COUNTLINE - this program counts the lines in a previo
*/
void adjust_COUNTLINE(void)
{
	char current_direct[512];
	char rd_buffer[1024];
	int j, folder, character_rd;
	char *location;

	COUNT_LINES = 0;

	if (getcwd(current_direct, 512) == NULL)
		return;

	location = _getenv("LOCATION");
	if (location == NULL)
		location = "";

	if (chdir(location) == -1)
		return;

	folder = open(".simple_shell_history", O_RDONLY);
	if (folder == -1)
		return;

	while ((character_rd = read(fd, rd_buffer, 1024)) != -1)
	{
		if (character_rd == 0)
			break;

		for (j = 0; j < character_rd; j++)
			if (rd_buffer[j] == '\n')
				COUNT_LINES++;
	}

	chdir(current_direct);
}

/**
 * Get_HISLINES_CNT - this program returns the history file line count
 * Return: it returns pointer to lines count
*/
int *Get_HISLINES_CNT()
{
	return (&COUNT_LINES);
}
