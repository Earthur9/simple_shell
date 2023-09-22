#ifndef SIMPLE_SHELL_H
#define SIMPLE_SHELL_H

#define PROMPT "$ "
#include <libgen.h>

extern int argc;
extern char **argv;
extern char **environ;

void execute_command(char *command);
void parse_command_line_arguments(int argc, char **argv);
int get_argc(void);
char **get_argv(void);

#endif
