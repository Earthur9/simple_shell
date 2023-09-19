#ifndef SHELL_H
#define SHELL_H

#define MAX_INPUT_SIZE 1024
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stddef.h>


void displayPrompt();
int executeCommand(char *command);

#endif 
