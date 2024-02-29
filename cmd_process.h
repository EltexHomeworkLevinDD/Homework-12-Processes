#ifndef CMD_PROCESS
#define CMD_PROCESS

#ifndef _DEFAULT_SOURCE
#define _DEFAULT_SOURCE
#endif
#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <string.h>
#include <malloc.h>

#define COMMAND_MAX_SIZE 256 // with '\0'
#define ARGS_MAX_SIZE 32 // with '\0'
#define EXIT_COMMAND_NOT_FOUND 2

#define COMMANDS_SOURCE_DIR "./commands/src"
#define COMMANDS_BINARY_DIR "./commands/bin"

void process_command(char *command, char **args, int num_args);
int identify_command(char* str, char** command, int cmd_size, char **args, int* num_args);

#endif