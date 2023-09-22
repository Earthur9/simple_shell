#include "shell.h"

/**
 * countArgs - counts the number of arguments
 * @args: input array of strings
 * Return: number of strings
 */
int countArgs(char **args)
{
	register int i = 0;

	while (args[i])
		i++;
	return (i);
}

/**
 * _atoi - change string to an integer
 * @s: input string
 * Return: -1 if it's not a valid number,
 * else the converted number
 */
int _atoi(char *s)
{
	register int i = 0;
	unsigned long num = 0;

	while (s[i])
	{
		if (s[i] >= '0' && s[i] <= '9')
			num = num * 10 + s[i] - '0';
		else
			return (-1);
		i++;
	}
	if (num > INT_MAX)
	{
		return (-1);
	}
	return (num);
}

#include "shell.h"

/**
 * checkPath - Check if a command exists in the PATH and update fullPath.
 * @build: Input build
 */
void checkPath(config *build)
{
	char *path_env = _getenv("PATH");
	char *token, *path, *command;
	char **path_tokens;
	struct stat st;
	int i;

	if (!path_env)
	{
		perror("Error: PATH environment variable not found.");
		exit(EXIT_FAILURE);
	}

	path_tokens = tokenize_path(path_env);

	for (i = 0; path_tokens[i]; i++)
	{
		path = _strcat(path_tokens[i], "/");
		command = _strcat(path, build->args[0]);

		if (stat(command, &st) == 0)
		{
			build->fullPath = command;
			free(path_tokens);
			return;
		}

		free(path);
		free(command);
	}

	free(path_tokens);
	build->fullPath = build->args[0];
}
