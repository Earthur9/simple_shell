#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>
#include <ctype.h>

#define MAX_INPUT_SIZE 1024

int main(void);
void run_shell(void);
void parse_input(char *input, char *command, int *command_length);
void execute_command(char *command);

#endif
