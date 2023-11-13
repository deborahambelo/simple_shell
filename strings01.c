#include "shell.h"

/**
 * string_concat - concatenates two strings
 * @str1: first string
 * @str2: second string
 * Return: concatenated string
 */
char *string_concat(char const *str1, char const *str2)
{
	size_t	len;
	char *result;

	if (!str1 || !str2)
		return (NULL);
	len = get_string_length(str1) + get_string_length(str2);
	result = malloc(len + 1);
	if (result == NULL)
		return (NULL);
	result[0] = '\0';
	concatenate_strings(result, str1);
	concatenate_strings(result, str2);
	result[len] = '\0';
	return (result);
}

/**
 * string_subtract - extracts a substring from a string
 * @str: string
 * @start: starting index
 * @length: length of the substring
 * Return: extracted substring
 */
char *string_subtract(char const *str, unsigned int start, size_t length)
{
	size_t	i;
	char *substring;

	substring = (char *)malloc(length + 1);
	if (str == NULL || substring == NULL)
		return (NULL);
	i = 0;
	while (length-- && str[start + i])
	{
		substring[i] = str[start + i];
		i++;
	}
	substring[i] = '\0';
	return (substring);
}

/**
 * free_memory - frees an array
 * @array: array of strings
 * Return: void
 */
void free_memory(void **array)
{
	if (array)
	{
		free(*array);
		*array = NULL;
	}
}

/**
 * delete_string_array - deletes an array of strings
 * @array: array of strings
 * Return: void
 */
void delete_string_array(char **array)
{
	free_memory((void **)array);
}
