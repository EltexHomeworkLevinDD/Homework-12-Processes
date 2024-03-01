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
    printf("Введите команду: ");
    fgets(input, sizeof(input), stdin);
    input[strlen(input)-1] = '\0';

    CommandInfo cmd_info = parse_command(input);
    if (exec_command(&cmd_info) == 0){
        perror("Binary file not found!\n");
        exit(EXIT_FAILURE);
    }

    printf("Sucsess!\n");
    //  showdir [keys] [args]
    //      
    //      -s alpha/version --sort-alpha --sort-version
    //      -c number_of_entries

    //  tog [keys] [args]
    //      -c "message" --> txt file create
    //      -s show_file --> txt_file show
    
    return 0;
}