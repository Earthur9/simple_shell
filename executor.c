#include "shell.h"

/**
 * execute_command - Command execution logic.
 * @command: command from input.
 */

void execute_command(char *command)
{
	pid_t pid = fork();
	char **args;

	if (pid == -1)
	{
		perror("fork");
	}
	else if (pid == 0)
	{
		args = malloc(2 * sizeof(char *));
		if (args == NULL)
		{
			perror("malloc");
			exit(EXIT_FAILURE);
		}
		args[0] = command;
		args[1] = NULL;

		if (execve(command, args, NULL) == -1)
		{
			perror("execve");
			exit(EXIT_FAILURE);
		}
	}
	else
	{
		int status;

		wait(&status);

		if (WIFEXITED(status))
		{
			printf("Command exited with status %d\n", WEXITSTATUS(status));
		}
		else if (WIFSIGNALED(status))
		{
			printf("Command terminated by signal %d\n", WTERMSIG(status));
		}
	}
}

