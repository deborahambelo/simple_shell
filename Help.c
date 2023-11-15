#include "shell.h"
#define BUFF_SIZE 32

/**
 * rd_ln - program to  print line of fd
 * @fd: parameter for file descriptor
 * @ln: parameter for line of text
 * Return: execution of read_line that returns 1 if success
 */

int rd_ln(const int fd, char **ln)
{
	int			bytesReader;
	char		*t_meta;
	char		buffer[BUFF_SIZE + 1];
	static char	*str[4864];

	if (fd < 0 || BUFF_SIZE <= 0 || ln == NULL || read(fd, buffer, 0) < 0)
		return (-1);
	while ((bytesReader = read(fd, buffer, BUFF_SIZE)) > 0)
	{
		buffer[bytesReader] = '\0';
		if (!str[fd])
			str[fd] = duplicate_string(buffer);
		else
		{
			tmp = f_strjoin(str[fd], buffer);
			free(str[fd]);
			str[fd] = tmp;
		}
		if (find_character(str[fd], '\n'))
			break;
	}
	if (str[fd] == NULL && bytesReader == 0)
		return (-1);
	return (f_read_line(str, ln, fd));
}

/**
 * f_read_line - program to read line from fd
 * @str: parameter for grip of documment
 * @fd: parameter for file descriptor
 * @ln: parameter for line of text
 * Return: it returns 1 if success
 */

int	f_read_line(char **str, char **ln, int fd)
{
	char	*tmp;
	int		count;

	count = 0;
	while (str[fd][count] != '\0' && str[fd][count] != '\n')
		count++;
	*line = f_strsub(str[fd], 0, count);
	if (str[fd][count] == '\n')
	{
		tmp = duplicate_string(&str[fd][count + 1]);
		free(str[fd]);
		str[fd] = tmp;
		if (str[fd][0] == '\0')
			delete_string_array(&str[fd]);
	}
	else
		delete_string_array(&str[fd]);
	return (1);
}

/**
 * _help - program for  functions that simulate help command
 * @command: parameter for array of strings to execute
 * Return: It returs 0 if is positive, min for 1, -1 if is error
 */

int _help(char **command)
{

	int fd, i = 1, result = -1;
	char *line = NULL;

	while (command[i])
	{
		fd = open(command[i], O_RDONLY);
		if (fd != -1)
		{
			result = 0;
			while (rd_ln(fd, &line) == 1)
			{
				puts(line);
				free(line);
			}
			close(fd);
		}
		i++;
	}

	return (result);
}
