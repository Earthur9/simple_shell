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
extern char **environ;

int main(int argc, char *argv[]);
void run_shell(void);
void parse_input(char *input, char *command, int *command_length);
void execute_command(char *command);
void execute_other_command(char *command);
void execute_ls(void);
void initialize_shell(void);
void process_input(char *input, char *command, int *command_length);
void execute_input(char *command);

#endif
