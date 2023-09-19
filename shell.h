#ifndef SHELL_H
#define SHELL_H
#define MAX_ARG_COUNT 64
#define MAX_INPUT_SIZE 1024
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stddef.h>


void displayPrompt(void);
int executeCommand(char *command, char *args[]);

#endif
