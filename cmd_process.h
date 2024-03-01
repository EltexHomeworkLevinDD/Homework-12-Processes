#ifndef CMD_PROCESS
#define CMD_PROCESS

/*
Ограниения:
- Утилита может быть только одна

- У команды может не быть ключей
- У одного ключа может быть только одно значение
- У ключа может не быть значения

- У утилиты может быть несколько аргументов 
- У утилиты не может не быть аргументов 
- У утилиты может не быть ключей

Пример команды:
"[util][space]-[key][space][value][space]-[key][space][value]"
*/

#ifndef _DEFAULT_SOURCE
#define _DEFAULT_SOURCE
#endif
#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <sys/wait.h>

#define MAX_UTIL_LEN 128 // with '\0'
#define MAX_ARG_LEN 32  // with '\0'
#define MAX_ARGS    10

#define UTIL_SOURCE_DIR "utils/src"
#define UTIL_BINARY_DIR "utils/bin"

// Определение структуры для хранения информации о команде
// Ссылается на строку, из которой был создан, не удаляйте ёё
typedef struct {
    char *util;             // Указатель на строку, содержащую команду
    char *keys[MAX_ARGS];   // Массив указателей на строки, содержащие ключи
    char *values[MAX_ARGS]; // Массив указателей на строки, содержащие значения ключей
    int num_keys;           // Количество ключей
    char *args[MAX_ARGS];   // Массив указателей на строки, содержащие аргументы команды
    int num_args;           // Количество аргументов
} CommandInfo;              // Имя структуры

CommandInfo parse_command(const char *command);
int exec_command(CommandInfo* cmd_info);

#endif