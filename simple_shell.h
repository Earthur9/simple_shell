#ifndef SIMPLE_SHELL_H
#define SIMPLE_SHELL_H

#define PROMPT "$ "
#include <libgen.h>

extern char **environ;

void execute_command(char *command);

#endif
