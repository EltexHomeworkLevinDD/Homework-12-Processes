#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "cmd_process.h"

int ident(char* command, char** util, char*** args, int *num_args){
    char* token = (char*)0;
    int flag_cmd_found = 0;
    int index = -1;
    while (token != NULL){
        index++;
        token = strtok(command, " ");
        if (index == 0){
            if (strcmp(token, "showdir") == 0){
                *util = malloc(COMMAND_MAX_SIZE);
                strncpy(*util, token, COMMAND_MAX_SIZE);
            }
            else{
                return 2;
            }
        }else{
            // this is key
            if (token[0] == '-'){

            }
        }
    }
    return 0;
}

int main(){

    char command[COMMAND_MAX_SIZE];
    if (fgets(command, COMMAND_MAX_SIZE-1, stdin) == NULL){
        perror("fgets \n");
        exit(1);
    }
    command[strlen(command)-1] = '\0';

    printf("'%s'\n", command);

    char* util;
    char** args;
    int num_args;

    if (ident(command, &util, &args, &num_args) == 2)
        exit(1);

    printf("'%s'\n", util);

    free(util);
    

    return 0;
}