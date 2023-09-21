#include "shell.h"
#include <unistd.h>

/**
 * execute_command - This function handles the execution of commands.
 *			If the command is "/bin/ls," it executes the ls command
 *			in the current directory; otherwise, it executes other
 *			commands in separate processes.
 * @command: Command to be executed.
 */

void execute_command(char *command)
{
	pid_t pid = fork();

	if (pid == -1)
	{
		perror("fork");
	} else if (pid == 0)
	{
		char *args[2];

		args[0] = command;
		args[1] = NULL;

		if (execve(command, args, environ) == -1)
		{
			perror("execve");
			exit(EXIT_FAILURE);
		}
	} else
	{
		int status;

		wait(&status);

		if (WIFEXITED(status))
		{
			printf("#cisfun$ ");
		} else if (WIFSIGNALED(status))
		{
			printf("./shell: Terminated by signal %d\n", WTERMSIG(status));
			printf("#cisfun$ ");
		}
	}
}

/**
 * execute_ls - This function is responsible for executing
 *		the "/bin/ls" command, listing the contents of the current directory.
 */

void execute_ls(void)
{
	pid_t pid = fork();

	if (pid == -1)
	{
		perror("fork");
	} else if (pid == 0)
	{
		execlp("ls", "ls", (char *)NULL);
		perror("execlp");
		exit(EXIT_FAILURE);
	} else
	{
		int status;

		wait(&status);
	}
}

/**
 * execute_other_command - This function handles the execution of all
 *				other commands, executing them as separate processes.
 * @command: command to be executed.
 */

void execute_other_command(char *command)
{
	pid_t pid = fork();
	char **args;

	if (pid == -1)
	{
		perror("fork");
	} else if (pid == 0)
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
	} else
	{
		int status;

		wait(&status);

		if (WIFEXITED(status))
		{
			printf("Command exited with status %d\n", WEXITSTATUS(status));
		} else if (WIFSIGNALED(status))
		{
			printf("Command terminated by signal %d\n", WTERMSIG(status));
		}
	}
}
