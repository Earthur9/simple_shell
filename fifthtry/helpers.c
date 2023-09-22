#include "shell.h"
#include <string.h>

char **tokenize_path(char *path);

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
 * @:command Input build
 */
char *checkPath(char *command)
{
	char *path_env = _getenv("PATH"), *path, *full_tokens;
	char **path_tokens = tokenize_path(path_env);
	int i;

	for (i = 0; path_tokens[i] != NULL; i++)
	{
		path = path_tokens[i];
		full_path = malloc(strlen(path) + strlen(command) + 2);
		strcat(full_path, path);
		strcat(full_path, "/");
		strcat(full_path, command);

		if (access(full_path, F_OK) == 0)
		{
			return full_path;
		}
		free(full_path);
	}
	return (NULL);
}

char **tokenize_path(char *path)
{
	char **tokens = malloc(sizeof(char *) * 100), *token;
	int i = 0;

	token = strtok(path, ":");
	while (token != NULL)
	{
		tokens[i] = token;
		i++;
		token = strtok(NULL, ":");
	}
	tokens[i] = NULL;
	return (tokens);
}
