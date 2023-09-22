#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#include "simple_shell.h"
#include <stddef.h>
#include <string.h>

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
	int status, i = 1, j, k;
	char **args = malloc(sizeof(char *) * 2), *program_name, path[1024];

	if (args == NULL)
	{
		perror("malloc() failed");
		return;
	}
	args[0] = strtok(command, " ");
	while ((args[i] = strtok(NULL, " ")) != NULL)
	{
		i++;
	}
	for (j = 0; j < i; j++)
	{
		if (strlen(args[j]) == 1)
		{
			args[j][0] == '\\';
		} else
		{
			for (k = 0; args[j][k] != '\0'; k++)
			{
				if (args[j][k] == ' ' || args[j][k] == '"'
						|| args[j][k] == '$' || args[j][k] == '\\')
				{
					strncat(args[j], "\\", 1);
				}
			}
		}
	}
#ifndef __linux__
	printf("readlink() is not available on this platform\n");
	return;
#endif
	if (readlink("/proc/self/exe", path, sizeof(path)) < 0)
	{
		perror("readlink() failed");
		return;
	}
	pid = fork();
	if (pid < 0)
	{
		perror("fork() failed");
		free(args);
		return;
	}
	if (pid == 0)
	{
		execve(command, args, environ);
		exit(1);
	}
	waitpid(pid, &status, 0);
	if (status != 0)
	{
		program_name = strrchr(path, '/') + 1;
		printf("%s: No such file or directory\n", program_name);
	}
	free(args);
}
