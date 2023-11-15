#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <limits.h>

#include "readcmd.h"
#include "mem_alloc.h"
#include "frees.h"
#include "parsing_tools.h"

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
	char *buffer;

	buffer = guarded_malloc(buf_size * sizeof(char));

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

		if (fgets(buffer, buf_size, stdin) == NULL)
			return (buffer);

	} while (1);

}

/**
 * split_in_words - Split the string in words, according
 * to the simple shell grammar
 * @line: the line to split
 *
 * Return: a list of strings containing the words in @line
*/
static char **split_in_words(char *line)
{
	char **tab = NULL, *delimiters = " \t&><|", *token, *del_str;
	size_t l = 0;

	while (*line != '\0')
	{
		if (strchr(delimiters, *line) != NULL)
		{
			del_str = guarded_malloc(2 * sizeof(char));
			del_str[0] = *line;
			del_str[1] = '\0';
		}
		tab = guarded_realloc(tab, (l + 1) * sizeof(char *));
		tab[l++] = strdup(token);
		line++;
		else
		{
			token = strtok(line, delimiters);
			if (token)
			{
				tab = guarded_realloc(tab, (l + 1) * sizeof(char *));
				tab[l++] = strdup(token);
				line = NULL;
			}
			else
				break;
		}
	}

	tab = guarded_realloc(tab, (l + 1) * sizeof(char *));
	tab[l] = NULL;
	return (tab);
}

/**
 * parse_special -
 * @s: the cmdline structure that holds the information
 * @w: the current word being read
 * @words: the list of words in the command line
 * @seq: the sequemce of commands to execute
 * @idx: in the list of words
 * @cmd_len: the length of the current command
 * @seq_len: the number of commands currently parsed
 */

void parse_special(struct cmdline *s, char *w, char **words, char ***seq, int *idx, size_t cmd_len, size_t *seq_len) {
    switch (w[0])
    {
        case '<':
            parse_in(s, words, *idx);
            s->in = words[(*idx)++];
            break;
        case '>':
            /* Tricky : the word can only be ">" */
            parse_out(s, words, *idx);
            s->out = words[(*idx)++];
            break;
        case '&':
            parse_bg(s, words, *idx, cmd_len);
            s->bg = 1;
            break;
        case '|':
            parse_pipe(s, words, *idx, cmd_len);
            update_seq(seq, seq_len);

            cmd = guarded_malloc(sizeof(char *));
            cmd[0] = 0;
            cmd_len = 0;
            break;
    }
}
/**
 * parsecmd - parses the commands passed in the command line
 * @pline:  the line read from the stdin
 *
 * Return: the information about the commands
 */
struct cmdline *parsecmd(char **pline)
{
	char *line = *pline, char **cmd, **words, char ***seq, *w;
	struct cmdline *s;
	int i = 0;
	size_t cmd_len = 0 seq_len = 0;

	if (!line)
	{
		if (s)
		{
			freecmd(s);
			free(s);
		}
		return (NULL);
	}
	cmd = guarded_malloc(sizeof(char *));
	cmd[0] = NULL;
	seq = guarded_malloc(sizeof(char **));
	seq[0] = NULL;
	words = split_in_words(line);
	init_cmdline(s);
	while ((w = words[i++]) != 0)
	{
		if (strchr("<>|&", w[0]))
			parse_special(s, w, words, seq, &i, cmd_len, &seq_len);
		else
			update_cmd(cmd, &cmd_len);
	}
	if (cmd_len != 0)
		update_seq(seq, *seq_len);
	else if (seq_len != 0)
	{
		s->err = "misplaced pipe";
		i--;
	}
	else
		free(cmd);
	free(words);
	s->seq = seq;
	return (s);
}
