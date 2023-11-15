#include <stdlib.h>
#include <errno.h>

/**
 * memory_error - informs the system that a memory
 * error occurred and exits
 */
void memory_error(void)
{
	errno = ENOMEM;
	perror(0);
	exit(EXIT_FAILURE);
}


/**
 * xmalloc - allocates memory and checks if the return
 * of malloc is not null
 * @size: the size of the memory area to allocate
 *
 * Return: a pointer to the allocated area
 */

void *xmalloc(size_t size)
{
	void *ptr = malloc(size);

	if (!ptr)
		memory_error();

	return (ptr);
}

/**
 * xrealloc - reallocates memory for a pointer and
 * checks if the return value of realloc is null
 * @ptr: the pointer to reallocate
 * @size: the size of the new allocation
 *
 * Return: a pointer to the new allocated memory
 */

void *xrealloc(void *ptr, size_t size)
{
	void *p = realloc(ptr, size);

	if (!p)
		memory_error();

	return (ptr);
}

