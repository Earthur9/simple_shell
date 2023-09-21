#ifndef SIMPLE_SHELL_H
#define SIMPLE_SHELL_H

#define PROMPT "simple_shell> "
extern char **environ;
void execute_command(char *command);

#endif
