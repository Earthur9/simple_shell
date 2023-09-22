#include "shell.h"

/**
 * _getenv - get environmental variable that matches input string
 * @input: input string
 * @environ: local environmental variables
 * Return: string of environmental variable
 */
char *_getenv(char *input, char **environ)
{
	register int i = 0;
	char *t, *right;

	while (environ[i])
	{
		t = _strtok(environ[i], "=");
		if (_strcmp(t, input) == 0)
		{
			right = _strtok(NULL, "=");
			return (right);
		}
		i++;
	}
	return (NULL);
}
