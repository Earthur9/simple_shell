#include "execute.h"
#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

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

	/* Fork a child process to execute the command */
	pid = fork();
	if (pid < 0)
	{
		perror("fork() failed");
		return;
	}

	/* Child process */
	if (pid == 0)
	{
		/* Execute the command */
		execl("/bin/sh", "/bin/sh", "-c", command, NULL);

		/* If execl() fails, exit the child process */
		exit(1);
	}

	/* Parent process */
	waitpid(pid, &status, 0);

	/* Check the exit status of the child process */
	if (status != 0)
	{
		printf("%s: command failed\n", command);
	}
}

