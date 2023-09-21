#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#include "simple_shell.h"
#include <stddef.h>


/**
 * execute_command - Executes a command.
 *
 * @command: The command to be executed.
 *
 * This function forks a child process and executes the given command in the
 * child process. The parent process waits for the child process to finish
 * executing before returning.
 *
 * If the command is not found, the function prints an
 * error message and returns.
 */

void execute_command(char *command)
{
	pid_t pid;
	int status;
	char **args = malloc(sizeof(char *) * 2);

	if (args == NULL)
	{
		perror("malloc() failed");
		return;
	}
	args[0] = command;
	args[1] = NULL;

	/* Fork a child process to execute the command */
	pid = fork();
	if (pid < 0)
	{
		perror("fork() failed");
		free(args);
		return;
	}

	/* Child process */
	if (pid == 0)
	{
		/* Execute the command */
		execve(command, args, environ);

		/* If execve() fails, exit the child process */
		exit(1);
	}

	/* Parent process */
	waitpid(pid, &status, 0);

	/* Check the exit status of the child process */
	if (status != 0)
	{
		printf("%s: command failed\n", command);
	}
	free(args);
}

