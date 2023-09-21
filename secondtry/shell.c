#include "shell.h"
/**
 * run_shell - The shell logic.
 */

void run_shell(void)
{
	char input[MAX_INPUT_SIZE];
	char command[MAX_INPUT_SIZE];
	int command_length;

	while (1)
	{
		printf("($) ");

		if (fgets(input, sizeof(input), stdin) == NULL)
		{
			printf("\n");
			break;
		}

		if (input[strlen(input) - 1] == '\n')
		{
			input[strlen(input) - 1] = '\0';
		}

		parse_input(input, command, &command_length);

		if (command_length > 0)
		{
			execute_command(command);
		}
		else
		{
			printf("Invalid command format. Please enter a single-word command.\n");
		}
	}
}

