/*
3) Реализовать аналог командного интерпретатора bash. При запуске 
программы пользователю предлагается ввести имя программы и опции 
запуска программы. Программа порождает процесс и в нем выполняет 
введенную программу с заданными опциями, ждет завершения 
дочернего процесса. Снова возвращается к вводу следующей 
программы. Выход из интерпретатора по команде exit. 
*/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "cmd_process.h"

#define MAX_CMD_LEN 1024
#define CMD_EXIT "exit"

int main(){

    char input[MAX_CMD_LEN]; 
    CommandInfo cmd_info;

    int flag = 1;
    while (flag == 1){
        printf("kekw_interpretator >: ");
        fgets(input, sizeof(input), stdin);
        input[strlen(input)-1] = '\0';

        if (strcmp(input, "exit") == 0){
            flag = 0;
            break;
        }

        cmd_info = parse_command(input);
        if (exec_command(&cmd_info) == 0){
            perror("Binary file not found!\n");
            exit(EXIT_FAILURE);
        }
    }
    
    return 0;
}