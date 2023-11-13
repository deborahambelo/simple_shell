#include "shell.h"

/**
 * find_character - Find a character in a string
 * @str: The string to search
 * @ch: The character to find
 *
 * Return: A pointer to the first occurrence of the character in the string,
 *         or NULL if the character is not found.
 */
char *find_character(const char *str, int ch)
{
    size_t i = 0;

    while (str[i])
    {
        if (str[i] == ch)
            return ((char *)&str[i]);
        i++;
    }

    if (ch == '\0')
        return ((char *)(&str[i]));

    return (NULL);
}

/**
 * concatenate_strings - Concatenate two strings
 * @dest: The destination string
 * @src: The source string
 *
 * Return: A pointer to the resulting string.
 */
char *concatenate_strings(char *dest, const char *src)
{
    return (concatenate_strings_n(dest, src, -1));
}

/**
 * concatenate_strings_n - Concatenate first n characters of src to dest string
 * @dest: The destination string
 * @src: The source string
 * @n: The number of characters of src to concatenate to dest
 *
 * Return: A pointer to the resulting string.
 */
char *concatenate_strings_n(char *dest, const char *src, size_t n)
{
    size_t i = get_string_length(dest);
    size_t j = 0;

    while (src[j] && j < n)
        dest[i++] = src[j++];

    dest[i] = '\0';

    return (dest);
}
