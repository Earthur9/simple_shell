#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#include "simple_shell.h"
#include <string.h>

/**
 * main - The entry point for the simple shell program.
 * @argc: Argument count.
 * @argv: Argument vector.
 *
 * This function displays the shell prompt and waits for the user to type a
 * command. Once the user has typed a command, the function executes the
 * command and then displays the prompt again.
 *
 * The function terminates when the user types the `exit` command.
 *
 * Return: 0 on success, or 1 on failure.
 */

int main(int argc, char **argv)
{
	char line[100];

	argc = argc;
	argv = argv;

	while (1)
	{
		printf(PROMPT);
		fgets(line, sizeof(line), stdin);

		if (feof(stdin))
		{
			break;
		}

		line[strlen(line) - 1] = '\0';

		execute_command(line);
	}
	return (0);
}

