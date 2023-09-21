#include "shell.h"
/**
 * main - logic of main.
 * @argc: argument count.
 * @argv: argument vector.
 *
 * Return: exit_success.
 */

int main(int argc, char *argv[])
{
	if (argc == 1)
	{
		run_shell();
	} else if (argc == 2)
	{
		fprintf(stderr, "Non-interactive mode is not yet implemented.\n");
		return (EXIT_FAILURE);
	}


	fprintf(stderr, "Usage: %s [command_file]\n", argv[0]);

	return (EXIT_SUCCESS);
}
