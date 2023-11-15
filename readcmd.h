#ifndef _READCMD
#define _READCMD

/**
 * cmdline - stores the information about the command
 * @seq - the list of commands to execute
 * @in: the input of file if provided, if not NULL
 * @out: the output file if provided, if not NULL
 * @bg: 1 if the command needs to be run in the background
 * err: the error that occurred parsing the command
 */
struct cmdline
{
	char ***seq;
	char *in;
	char *out;
	int bg;
	const char *err;
}

char *readline(char *prompt);
struct cmdline *parsecmd(char **pline);

#endif
