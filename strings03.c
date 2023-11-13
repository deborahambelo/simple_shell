#include "shell.h"

/**
 * get_string_length - returns the length of a string
 * @str: input string
 * Return: length of the string
 */
int get_string_length(const char *str)
{
	int length = 0;

	if (str == NULL)
		return 0;

	while (str[length])
		length++;

	return length;
}

/**
 * duplicate_string - copy a string using dynamic memory allocation
 * @str: input string
 * Return: pointer to the copied string
 */
char *duplicate_string(const char *str)
{
	char *copy;
	size_t length;
	size_t i;

	length = get_string_length(str);
	copy = (char *)malloc(sizeof(char) * (length + 1));
	if (!copy)
		return NULL;

	for (i = 0; i < length; i++)
		copy[i] = str[i];

	copy[i] = '\0';

	return copy;
}

/**
 * comp_nstrings - compare if two strings are equal up to n characters
 * @str1: first string
 * @str2: second string
 * @n: number of characters to compare
 * Return: 0 if strings are equal, non-zero otherwise
 */
int comp_nstrings(const char *str1, const char *str2, size_t n)
{
	size_t i;

	for (i = 0; i < n && str1[i] && str2[i]; i++)
	{
		if ((unsigned char)str1[i] != (unsigned char)str2[i])
			return (unsigned char)str1[i] - (unsigned char)str2[i];
	}

	if (i == n)
		return 0;

	return (unsigned char)str1[i] - (unsigned char)str2[i];
}

/**
 * compare_strings - compare if two strings are equal
 * @str1: first string
 * @str2: second string
 * Return: 0 if strings are equal, non-zero otherwise
 */
int compare_strings(const char *str1, const char *str2)
{
	return comp_nstrings(str1, str2, (size_t)-1);
}

/**
 * number_to_string - Convert a number to string format
 * @num: Number to be converted
 *
 * Return: Pointer to string representation of "num"
 */
char *number_to_string(int num)
{
	int reversed_num = 0;
	int i, digits = 0;
	char *str_num = NULL;

	if (num == 0)
		digits = 1;
	else
	{
		while (num > 0)
		{
			digits++;
			reversed_num *= 10;
			reversed_num += num % 10;
			num /= 10;
		}
	}

	str_num = malloc(sizeof(char) * (digits + 1));
	if (str_num == NULL)
		err_dispatch("Error: Couldn't allocate memory for number conversion");

	for (i = 0; i < digits; i++)
	{
		str_num[i] = (reversed_num % 10) + '0';
		reversed_num /= 10;
	}
	str_num[i] = '\0';

	return str_num;
}
