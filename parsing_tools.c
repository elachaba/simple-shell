#include <stdlib.h>
#include "mem_alloc.h"
#include "readcmd.h"


/**
 * update_cmd - updates the command with the read word
 * @cmd: the current command
 * @cmd_len: the current length of the command
 */
void update_cmd(char **cmd, size_t *cmd_len)
{
    cmd = guarded_realloc(cmd, (*cmd_len + 2) * sizeof(char *));
    cmd[(*cmd_len)++] = w;
    cmd[*cmd_len] = 0;
}

/**
 * update_seq - adds a new command to the sequence of commands
 * @seq: the sequence to update
 * @seq_len: the length of the sequence
 */
void update_seq(char ***seq, size_t *seq_len)
{
    seq = guarded_realloc(seq, (*seq_len + 2) * sizeof(char **));
    seq[(*seq_len)++] = cmd;
    seq[*seq_len] = 0;
}

/**
 * parse_in - handles the case when we read a input redirection symbol
 * @s: the information about the command line
 * @words: the list of words read from the stdin
 * @idx: the index of the current word being read
 */
void parse_in(struct cmdline *s, char **words, int idx) {
    /* Tricky : the word can only be "<" */
    if (s->in)
        s->err = "only one input file supported";
    if (words[idx] == 0)
        s->err = "filename missing for input redirection";
    switch (words[idx][0])
    {
        case '<':
            case '>':
            case '&':
            case '|':
                s->err = "incorrect filename for input redirection";
                break;
        }
}

/**
 * parse_out - handles the case when we read an output redirection symbol
 * @s: the information about the command line
 * @words: the list of the words read on the command line
 * @idx: the index of the current word being read
 */
void parse_out(struct cmdline *s, char **words, int idx)
{
    if (s->out)
        s->err = "only one output file supported";
    if (words[idx] == 0)
        s->err = "filename missing for output redirection";
    switch (words[idx][0])
    {
        case '<':
        case '>':
        case '&':
        case '|':
            s->err = "incorrect filename for output redirection";
            break;
    }
}

/**
 * parse_bg - handles the case when we read an output redirection symbol
 * @s: the information about the command line
 * @words: the list of the words read on the command line
 * @idx: the index of the current word being read
 * @cmd_len: the current length of the command being constructed
 */
void parse_bg(struct cmdline *l, char **words, int idx, size_t cmd_len)
{

    if (cmd_len == 0 || words[idx] != 0) {
        s->err = "misplaced ampersand";
    }
    if (s->bg == 1) {
        s->err = "only one ampersand supported";
    }
}

/**
 * parse_pipe - handles the case when we read an output redirection symbol
 * @s: the information about the command line
 * @words: the list of the words read on the command line
 * @idx: the index of the current word being read
 * @cmd_len: the current length of the command being constructed
 */
void parse_pipe(struct cmdline *s, char **words, int idx, size_t cmd_len)
{
    /* Tricky : the word can only be "|" */
    if (cmd_len == 0) {
        s->err = "misplaced pipe";
        goto error;
    }
    if (words[i] == 0) {
        s->err = "second command missing for pipe redirection";
        goto error;
    }
    switch(words[i][0])
    {
        case '<':
        case '>':
        case '&':
        case '|':
            s->err = "incorrect pipe usage";
            break;
    }
}

