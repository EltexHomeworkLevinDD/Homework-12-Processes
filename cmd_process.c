#include "cmd_process.h"

CommandInfo parse_command(const char *command) {
    CommandInfo cmd_info;
    cmd_info.num_keys = 0; // Инициализируем количество ключей
    cmd_info.num_args = 0; // Инициализируем количество аргументов
    memset(cmd_info.keys, 0, sizeof(cmd_info.keys)); // Заполняем массив ключей нулями
    memset(cmd_info.values, 0, sizeof(cmd_info.values)); // Заполняем массив значений ключей нулями
    memset(cmd_info.args, 0, sizeof(cmd_info.args)); // Заполняем массив аргументов нулями

    // Парсинг команды
    cmd_info.util = strtok((char *)command, " "); // Извлекаем первый токен - util
    
    // Парсинг ключей и их значений
    char *token = strtok(NULL, " ");                // Получаем следующий токен после команды
    while (token != NULL && token[0] == '-') {      // Пока есть токен и он начинается с символа '-'
        cmd_info.keys[cmd_info.num_keys] = token;   // Записываем токен как ключ
        token = strtok(NULL, " ");                  // Получаем следующий токен
    if (token != NULL && token[0] != '-') {         // Если следующий токен не начинается с '-'
            cmd_info.values[cmd_info.num_keys] = token; // Записываем его как значение для ключа
            cmd_info.num_keys++;                    // Увеличиваем счетчик ключей
            token = strtok(NULL, " ");              // Получаем следующий токен
        }
    }

    // Парсинг аргументов
    while (token != NULL) {         // Пока есть следующий токен
        cmd_info.args[cmd_info.num_args] = token; // Записываем токен как аргумент
        cmd_info.num_args++;        // Увеличиваем счетчик аргументов
        token = strtok(NULL, " ");  // Получаем следующий токен
    }

    return cmd_info; // Возвращаем структуру CommandInfo с информацией о команде
}

/*
return 0 if error (util not found), 1 if true
*/
int exec_command(CommandInfo* cmd_info){
    // Проверка на имя утилиты

    // Получию список имеющихся утилит
    struct dirent** utils = NULL;
    int entries_count = scandir(UTIL_BINARY_DIR, &utils, NULL, alphasort);
    if (entries_count == -1) {
        perror("scandir binary directory");
        exit(EXIT_FAILURE);
    }

    int util_found = 0;
    for (int i = 2; i < entries_count; i++){ 
        if (utils[i]->d_type == DT_REG){
            if (strcmp((*cmd_info).util, utils[i]->d_name) == 0){
                util_found = 1;
            }
        }
    }

    // Освобождаем
    for (int i = 0; i < entries_count; i++){
        free(utils[i]);
    }
    free(utils); utils = NULL;

    // 
    if (!util_found){
        //printf("The '%s' command was not found\n", (*cmd_info).util);
        return 0;
    }

    // Создаем массив аргументов для передачи в новый процесс
    char *args[MAX_ARGS * 2 + cmd_info->num_args + 1];
    // *2 -- Каждый ключ может иметь свое значение, учитаваем
    // +1 -- Для хранения NULL в конце
    args[0] = cmd_info->util;       // Первый аргумент - команда
    int arg_index = 1;

    // Добавляем ключи и их значения
    for (int i = 0; i < cmd_info->num_keys; i++) {
        args[arg_index++] = cmd_info->keys[i];
        if (cmd_info->values[i] != NULL) {
            args[arg_index++] = cmd_info->values[i];
        }
    }

    // Добавляем ключи и их значения
    // Добавляем аргументы
    for (int i = 0; i < cmd_info->num_args; i++) {
        args[arg_index++] = cmd_info->args[i];
    }

    args[arg_index] = NULL; // Последний элемент массива аргументов должен быть NULL

    // PATH_MAX + '/' + UTIL_BINARY_DIR + '/' + util_name
    // PATH_MAX includes NULL
    char full_util_pathname[PATH_MAX + strlen(UTIL_BINARY_DIR) + MAX_UTIL_LEN + 2];
    if (getcwd(full_util_pathname, sizeof(PATH_MAX)) == NULL) {
        perror("getcwd to full_util_pathname PATH_MAX size bytes");
        exit(EXIT_FAILURE);
    }

    int len = strlen(full_util_pathname);
    strcat(full_util_pathname, "/");
    strcat(full_util_pathname, UTIL_BINARY_DIR);
    strcat(full_util_pathname, "/");
    strcat(full_util_pathname, cmd_info->util);

    pid_t cpid = fork();
    int cstatus;
    switch (cpid)
    {
    case -1:
        perror("fork");
        exit(EXIT_FAILURE);
        break;
    case 0:
        execv(full_util_pathname, args);

        perror("execv");
        exit(EXIT_FAILURE);
        break;
    default:
        waitpid(cpid, &cstatus, NULL);
        return 1;
        break;
    }
}