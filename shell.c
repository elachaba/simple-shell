#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

#define MAX_COMMAND_LENGTH 100


/**
 * main - the main function, it runs the shell
 * prints a prompt and waits for input to execute the command
 * handles errors in case the command is not found
 * Return: 0 if it succeeds
 */
int main()
{
	char cmd[MAX_COMMAND_LENGTH];
	size_t cmd_len;
	int status;
	pid_t pid;

	while (1) {
		printf("($) ");
		if (fgets(cmd, sizeof(cmd), stdin) == NULL)
			break;
		cmd_len= strlen(cmd);
		if (cmd_len > 0 && cmd[cmd_len - 1] == '\n')
			cmd[cmd_len - 1] = '\0';
		pid = fork();
		if (pid == -1)
		{
			perror("Fork failed");
			exit(1);
		}
		else if (pid == 0) 
		{
			if (execlp(cmd, cmd, NULL) == -1)
			{
				printf("Command not found: %s\n", cmd);
				exit(EXIT_FAILURE);
			}
		}
		else
			waitpid(pid, &status, 0);
	}
	return (EXIT_SUCCESS);}
