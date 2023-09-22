#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>
#include "simple_shell.h"

/**
 * tokenize_command - Tokenizes a command into arguments.
 *
 * @command: The command to tokenize.
 * @args: A pointer to the argument array to fill.
 * @arg_count: A pointer to store the number of arguments.
 *
 * This function tokenizes the input command into individual arguments,
 * using space as the delimiter. It fills the args array and stores
 * the number of arguments in arg_count.
 */

void tokenize_command(char *command, char ***args, int *arg_count)
{
	int i = 0;
	char *token = strtok(command, " ");

	while (token != NULL)
	{
		(*args)[i++] = token;
		token = strtok(NULL, " ");
	}
	(*args)[i] = NULL;
	*arg_count = i;
}

/**
 * escape_special_characters - Escapes special characters in arguments.
 *
 * @args: The array of arguments to escape.
 * @arg_count: The number of arguments in the array.
 *
 * This function escapes special characters ('$','"',' ', and '\') in each
 * argument by adding a backslash before them.
 */

void escape_special_characters(char **args, int arg_count)
{
	int i, j;

	for (i = 0; i < arg_count; i++)
	{
		for (j = 0; args[i][j] != '\0'; j++)
		{
			if (args[i][j] == ' ' || args[i][j] == '"' ||
					args[i][j] == '$' || args[i][j] == '\\')
			{
				args[i][j] = '\\';
			}
		}
	}
}

/**
 * execute_command_internal - Executes a command internally.
 *
 * @path: The path to the executable.
 * @args: The arguments for the command.
 */
void execute_command_internal(char *path, char **args)
{
	execve(path, args, environ);
	perror("execve() failed");
	exit(1);
}

