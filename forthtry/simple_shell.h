#ifndef SIMPLE_SHELL_H
#define SIMPLE_SHELL_H

#define PROMPT "$ "
#include <libgen.h>

extern char **environ;

void execute_command(char *command);
char *find_executable(char *command);
void tokenize_command(char *command, char ***args, int *arg_count);
void escape_special_characters(char **args, int arg_count);
void execute_command_internal(char *path, char **args);


#endif
