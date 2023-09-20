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
	/** Initialize the command buffer and length */
	int i;
	*command_length = 0;

	/** Iterate through the input and extract a single-word command */
	for (i = 0; input[i] != '\0'; i++)
	{
		if (isalnum(input[i]))
		{
			/** If the character is alphanumeric, add it to the command */
			command[(*command_length)++] = input[i];
		}
		else if (isspace(input[i]))
		{
			/** If there's a space, terminate the command and ignore the rest */
			command[*command_length] = '\0';
			return;
		}
		else
		{
			/** If there's a special character, it's not a valid command */
			*command_length = 0;
			return;
		}
	}

	/** Null-terminate the command */
	command[*command_length] = '\0';
}

/**
 * execute_command - Execute a single-word command
 * @command: The single-word command to execute
 */
void execute_command(char *command)
{	/** Fork a child process */
	pid_t pid = fork();
	char **args;

	if (pid == -1)
	{
		perror("fork");
	}
	else if (pid == 0)
	{	/** This is the child process */
		args = malloc(2 * sizeof(char *));
		if (args == NULL)
		{
			perror("malloc");
			exit(EXIT_FAILURE);
		}
		args[0] = command;
		args[1] = NULL;

		/** Execute the command */
		if (execve(command, args, NULL) == -1)
		{
			perror("execve");
			exit(EXIT_FAILURE);
		}
	}
	else
	{	/** This is the parent process */
		int status;

		wait(&status);

		if (WIFEXITED(status))
		{	/** Command exited normally */
			printf("Command exited with status %d\n", WEXITSTATUS(status));
		}
		else if (WIFSIGNALED(status))
		{	/** Command was terminated by a signal */
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
		/** Display the prompt */
		printf("($) ");

		/** Read a command from the user */
		if (fgets(input, sizeof(input), stdin) == NULL)
		{
			/** Handle "end of file" condition (Ctrl+D) */
			printf("\n");
			break;
		}

		/** Remove newline character if present */
		if (input[strlen(input) - 1] == '\n')
		{
			input[strlen(input) - 1] = '\0';
		}

		/** Parse the input to get a single-word command */
		parse_input(input, command, &command_length);

		/** Check if it's a valid command */
		if (command_length > 0)
		{
			/** Execute the command */
			execute_command(command);
		}
		else
		{
			/** Invalid input, display an error message */
			printf("Invalid command format. Please enter a single-word command.\n");
		}
	}

	return (0);
}
