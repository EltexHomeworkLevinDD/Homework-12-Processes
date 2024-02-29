#include "cmd_process.h"

void process_command(char *command, char **args, int num_args);
int identify_command(char* str, char** command, int* cmd_size, char **args, int* num_args){
    struct dirent** binary_list = NULL;
    int entries_count = scandir(COMMANDS_BINARY_DIR, &binary_list, NULL, alphasort);
    if (entries_count == -1) {
        perror("scandir binary directory");
        exit(EXIT_FAILURE);
    }

    char* token = (char*)0;
    int flag_cmd_found = 0;
    int index = -1;
    while (token != NULL){
        index++;
        token = strtok(str, " ");
        if (index == 0){
            for (int i = 2; i < entries_count; i++){
                // if (strcmp(token[0], binary_list[i]->d_name) == 0)
                // {   *
                //     *command = malloc(strlen(token)+1)
                // }
            }
        }else{
            // this is key
            if (token[0] == '-'){

            }
        }
    }

    // // Разбиваем строку на токены, разделитель - пробел
    // char** str_tokens;
    // int str_tokens_size = 0;
    // int j = -1;
    // while ( (str_tokens[j] = strtok(str, " ")) != NULL){
    //     j++;
    //     str_tokens_size++;
    // }

    // // Ищем соответствующий бинарник
    // char binary_name[256] = "";
    // for (int i = 2; i < entries_count; i++){
    //     //if (binary_list[i]->d_type == DT_UNKNOWN)
    //         if (strcmp(str_tokens[0], binary_list[i]->d_name) == 0){
    //             if (strncpy(binary_name, binary_list[i]->d_name, 256) == NULL){
    //                 perror("Srcpy binary scandir name to binary name\n");
    //                 exit(EXIT_FAILURE);
    //             } 
    //             break;
    //         }
    // }

    // Освобождаем
    for (int i = 0; i < entries_count; i++){
        free(binary_list[i]);
    }
    free(binary_list);

    exit(0);
}
