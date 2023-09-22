#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>
#include "simple_shell.h"

/**
 * find_executable - Search for an executable in the PATH directories.
 * @command: the command.
 * Return: the full path to the executable if found, or NULL if not found.
 */
char *find_executable(char *command)
{
	char *path, *path_copy, *dir, *executable_path;

	path = getenv("PATH");
	if (path == NULL)
	{
		perror("getenv() failed");
		return (NULL);
	}
	path_copy = strdup(path);
	if (path_copy == NULL)
	{
		perror("strdup() failed");
		return (NULL);
	}
	dir = strtok(path_copy, ":");
	while (dir != NULL)
	{
		executable_path = malloc(strlen(dir) + strlen(command) + 2);
		if (executable_path == NULL)
		{
			perror("malloc() failed");
			free(path_copy);
			return (NULL);
		}
		sprintf(executable_path, "%s/%s", dir, command);
		if (access(executable_path, X_OK) == 0)
		{
			free(path_copy);
			return (executable_path);
		}
		free(executable_path);
		dir = strtok(NULL, ":");
	}
	free(path_copy);
	return (NULL);
}


/**
 * execute_command - Executes a command.
 *
 * @command: The command to be executed.
 *
 * This function tokenizes the input command, escapes special characters,
 * and then forks a child process to execute the command. The parent process
 * waits for the child process to finish executing before returning.
 *
 * If the command is not found, an error message is printed.
 */

void execute_command(char *command)
{
	char **args = malloc(sizeof(char *) * 2), path[1024], *program_name;
	int arg_count, status;
	pid_t pid;

	if (args == NULL)
	{
		perror("malloc() failed");
		return;
	}
	tokenize_command(command, &args, &arg_count);
	escape_special_characters(args, arg_count);

#ifndef __linux__
	printf("readlink() is not available on this platform\n");
	return;
#endif
	if (readlink("/proc/self/exe", path, sizeof(path)) < 0)
	{
		perror("readlink() failed");
		free(args);
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
		execute_command_internal(path, args);
	}
	waitpid(pid, &status, 0);
	if (status != 0)
	{
		program_name = strrchr(path, '/') + 1;
		printf("%s: No such file or directory\n", program_name);
	}
	free(args);
}
