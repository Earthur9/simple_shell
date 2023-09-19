#include "shell.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

/**
 * displayPrompt - Displays the shell prompt
 */
void displayPrompt(void)
{
	printf("simple_shell> ");
	fflush(stdout);
}

/**
 * executeCommand - Executes a given command
 * @command: The command to execute
 *
 * Return: 0 on success, 1 on failure
 */
int executeCommand(char *command)
{
	/* Fork a child process */
	pid_t pid = fork();

	if (pid < 0)
	{
		perror("fork");
		return (1);
	}
	else if (pid == 0)
	{
		/* Child process */
		/* Execute the command using execvp */
		if (execlp(command, command, (char *)NULL) == -1)
		{
			fprintf(stderr, "Error: Command not found\n");
			exit(EXIT_FAILURE);
		}
	}
	else
	{
		/* Parent process */
		int status;

		waitpid(pid, &status, 0);

		if (WIFEXITED(status) && WEXITSTATUS(status) != 0)
		{
			fprintf(stderr, "Error: Command exited with non-zero status\n");
			return (1);
		}
	}

	return (0);
}

