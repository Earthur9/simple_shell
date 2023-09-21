#include "shell.h"

/**
 * parse_input - the parser logic.
 * @input: input from user.
 * @command: command from input.
 * @command_length: Length of comand.
 */

void parse_input(char *input, char *command, int *command_length)
{
	int i;

	*command_length = 0;

	for (i = 0; input[i] != '\0'; i++)
	{
		if (isalnum(input[i]))
		{
			command[(*command_length)++] = input[i];
		}
		else if (isspace(input[i]))
		{
			command[*command_length] = '\0';
			return;
		}
		else
		{
			*command_length = 0;
			return;
		}
	}
	command[*command_length] = '\0';
}

