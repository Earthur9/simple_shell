#include "shell.h"

/**
 * main - Entry point for the simple shell program
 *
 * Return: Always 0
 */
int main(void)
{
	char input[MAX_INPUT_SIZE];
	size_t len;
	char *token, *next_token;

	while (1)
	{
		displayPrompt();

		/* Read user input */
		if (fgets(input, MAX_INPUT_SIZE, stdin) == NULL)
		{
			printf("\n");
			break;
		}

		len = strlen(input);

		if (len > 0 && input[len - 1] == '\n')
		{
			input[len - 1] = '\0';
		}

		token = strtok(input, " \t");

		if (token == NULL)
		{
			continue; /* Skip empty input lines */
		}

		next_token = strtok(NULL, " \t");

		if (next_token != NULL)
		{
			fprintf(stderr, "Error: Command should be a single word\n");
			continue;
		}

		executeCommand(token);
	}

	return (0);
}

