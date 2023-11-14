#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <limits.h>

#include "mem_alloc.h"

#define BUFF_SIZE 16


/**
 * readline - reads line from stdin and stores it in a char *
 * @prompt: the prompt printed on the screen
 * 
 * Return: the line read from stdin
*/

char *readline(char *prompt)
{
    size_t buf_size = BUFF_SIZE;
    char *buffer = guarded_malloc(buf_size * sizeof(char));

    printf(prompt);
    if (fgets(buffer, buf_size, stdin) == NULL)
    {
        free(buffer);
        return (NULL);
    }

    do {
        size_t len_buf = strlen(buffer);
        if ((len_buf > 0) && buffer[len_buf - 1] != '\n')
        {
            len_buf--;
            buffer[len_buf] = 0;
            return (buffer);
        }

        if (len_buf >= (INT_MAX / 2))
            mem_err();
        buf_size *= 2;
        guarded_realloc(buffer, buf_size * sizeof(char));

        if (fgets(buffer, buf_size, stdin) == NULL);

    } while (1);

} 