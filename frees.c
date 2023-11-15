#include <stdlib.h>
#include "readcmd.h"

/**
 * freecmd - frees the ressources of a cmdline struct
 * @s: the cmdline pointer to free
 * Return: void
 * */
void freecmd(struct cmdline *s)
{
    if (s->in) free(s->in);
    if (s->out) free(s->out);
    if (s->seq) freeseq(s->seq);
}
