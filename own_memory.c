#include "shell.h"

/**
 * _realloc - program that reallocates a memory block
 * @data_ptr: Parameter that pointer to the memory to be reallocated
 * @previous_size: parameter for the size in bytes
 * of the actual allocated memory
 * @updated_size: parameter for the size in bytes for the new allocated memory
 *
 * Return:it returns pointer to the newly allocated memory
 */

void *_realloc(void *data_ptr, unsigned int previous_size,
		unsigned int updated_size)
{
	int boundary, j;
	void *pointer;

	if (previous_size == updated_size)
		return (data_ptr);

	if (data_ptr == NULL)
		return (malloc(updated_size));

	if (updated_size == 0)
	{
		free(data_ptr);
		return (NULL);
	}

	pointer = malloc(updated_size);

	if (previous_size > updated_size)
		boundary = updated_size;
	else
		boundary = previous_size;

	for (j = 0; j < boundary; j++)
		((char *)pointer)[j] = ((char *)data_ptr)[j];

	free(data_ptr);

	return (pointer);
}
