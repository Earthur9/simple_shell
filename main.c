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
	char *token, *args[MAX_ARG_COUNT];
	int arg_count = 0;

	while (1)
	{
		displayPrompt();
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
		} while (token != NULL)
		{
			args[arg_count] = token;
			arg_count++;

			if (arg_count >= MAX_ARG_COUNT - 1)
			{
				fprintf(stderr, "Error: Too many arguments\n");
				break;
			}
			token = strtok(NULL, " \t");
		}
		args[arg_count] = NULL;
		executeCommand(args[0], args);
	}
	return (0);
}

