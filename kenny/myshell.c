#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>
#include <ctype.h>

#define MAX_INPUT_SIZE 1024

/**
 * parse_input - Parse user input into a single-word command
 * @input: The user input string
 * @command: A buffer to store the parsed command
 * @command_length: A pointer to store the length of the parsed command
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

/**
 * execute_command - Execute a single-word command
 * @command: The single-word command to execute
 */
void execute_command(char *command)
{
	pid_t pid = fork();
	char **args;

	if (pid == -1)
	{
		perror("fork");
	}
	else if (pid == 0)
	{
		args = malloc(2 * sizeof(char *));
		if (args == NULL)
		{
			perror("malloc");
			exit(EXIT_FAILURE);
		}
		args[0] = command;
		args[1] = NULL;

		if (execve(command, args, NULL) == -1)
		{
			perror("execve");
			exit(EXIT_FAILURE);
		}
	}
	else
	{
		int status;

		wait(&status);

		if (WIFEXITED(status))
		{
			printf("Command exited with status %d\n", WEXITSTATUS(status));
		}
		else if (WIFSIGNALED(status))
		{
			printf("Command terminated by signal %d\n", WTERMSIG(status));
		}
	}
}

/**
 * main - Entry point of the simple shell program
 *
 * Return: 0 on success, non-zero on failure
 * This function reads user input, parses it into a single-word command, and
 * executes the command as a child process.
 */
int main(void)
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

	return (0);
}
