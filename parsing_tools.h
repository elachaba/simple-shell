#ifndef PARS_TOOLS
#define PARS_TOOLS

void update_cmd(char **cmd, size_t *cmd_len);
void update_seq(char ***seq, size_t *seq_len);
void parse_in(struct cmdline *s, char **words, int idx);
void parse_out(struct cmdline *s, char **words, int idx);
void parse_bg(struct cmdline *l, char **words, int idx, size_t cmd_len);
void parse_pipe(struct cmdline *l, char **words, int idx, size_t cmd_len);