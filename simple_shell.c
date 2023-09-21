#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#include "simple_shell.h"
#include <string.h>

/**
 * main - The entry point for the simple shell program.
 *
 * This function displays the shell prompt and waits for the user to type a
 * command. Once the user has typed a command, the function executes the
 * command and then displays the prompt again.
 *
 * The function terminates when the user types the `exit` command.
 *
 * Return: 0 on success, or 1 on failure.
 */

int main(void)
{
	char line[100];

	while (1)
	{
		/* Display the prompt */
		printf(PROMPT);

		/* Read a line from the user */
		fgets(line, sizeof(line), stdin);

		/* Check for the end of file condition (Ctrl+D) */
		if (feof(stdin))
		{
			break;
		}

		/* Remove the trailing newline character */
		line[strlen(line) - 1] = '\0';

		/* Execute the command */
		execute_command(line);
	}

	return (0);
}

