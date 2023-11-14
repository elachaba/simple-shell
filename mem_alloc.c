#include <stdlib.h>
#include <errno.h>

/**
 * mem_err - handles memory error
 * Let's the system know that the last error that occurred
 * is a memory error
 * 
 * Return: void
*/
void mem_err()
{
    errno = ENOMEM;
    perror(0);
    exit(EXIT_FAILURE);
}

/**
 * guarded_malloc - allocates memory and checks if the malloc
 * executed correctly
 * @size: the size of the memory to allocate
 * 
 * Return: a pointer to the allocated memory space
*/
void *guarded_malloc(size_t size)
{
    void *ret = malloc(size);

    if (!ret)
        mem_err();
    return (ret);
}

/**
 * guarded_realloc - reallocates the memory for a pointer and checks if
 * the realloc executed correctly
 * @ptr: a pointer to the current allocated memory area
 * @size: the size of the new memory area to allocate
 * 
 * Return: a pointer to the new allocated memory area
*/
void *guarded_realloc(void *ptr, size_t size)
{
    void *ret = realloc(ptr, size);

    if(!ret)
        mem_err();
    return (ret);
}