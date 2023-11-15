#include <stdlib.h>
#include <string.h>
#include "xalloc.c"


#define READ_CHAR (*(*cur_buf)++ = *(*cur)++)

/**
 * readword - identifis a word in a string
 * @curr: the word being read
 * @curr_buffer: the buffer to write the word in
 * Return: void
 */
static void readword(char **curr, char **curr_buffer)
{
	char *c;

	while (1)
	{
		c = **curr;
		switch (c)
		{
			case '\0':
			case '\t':
			case ' ':
			case '>':
			case '<':
			case '|':
			case '&':
				**curr_buffer = '\0';
				return;
			default:
				READ_CHAR;
				break;
		}
	}
}
/**
 * _strtok - splits a string into words. We ingonre any repeated delimitters
 * @str: the input string
 *
 * Return: a list of words in the string
 */
char **_strtok(char *str)
{
	char *curr = str, *curr_buff, *w, **tab = NULL, c;
	char *buffer = xmalloc(strlen(line) + 1), *str_c = xmalloc(2 * sizeof(char));
	char *white_space = " \t", delimiters = "><|";
	size_t l = 0;

	str_c[1] = '\0';
	while ((c = *curr) != 0)
	{
		w = 0;
		if (strchr(white_space, c) != NULL)
			curr++;
		else if (strchr(delimiters, c) != NULL)
		{
			str_c[0] = c;
			w = str_c;
			curr++;
		}
		else
		{
			curr_buff = buffer;
			readword(&curr, &curr_buff);
			w = strdup(buffer);
		}
		if (w)
		{
			tab = xrealloc(tab, (l + 1) * sizeof(char *));
			tab[l++] = w;
		}
	}
	tab = xrealloc(tab, (l + 1) * sizeof(char *));
	tab[l++] = 0;
	free(buffer);
	return (tab);
}
