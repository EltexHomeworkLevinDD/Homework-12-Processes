#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_CMD_LEN 128
#define MAX_ARGS 10
#define MAX_ARG_LEN 32

/*
Можно возвращать структуры из функций return. Но вернётся копия. 
*/

// Определение структуры для хранения информации о команде
typedef struct {
    char *command;          // Указатель на строку, содержащую команду
    char *keys[MAX_ARGS];   // Массив указателей на строки, содержащие ключи
    char *values[MAX_ARGS]; // Массив указателей на строки, содержащие значения ключей
    int num_keys;           // Количество ключей
    char *args[MAX_ARGS];   // Массив указателей на строки, содержащие аргументы команды
    int num_args;           // Количество аргументов
} CommandInfo;              // Имя структуры


// Функция для парсинга введенной строки команды
CommandInfo parse_command(const char *input) {
    CommandInfo cmd_info;
    cmd_info.num_keys = 0; // Инициализируем количество ключей
    cmd_info.num_args = 0; // Инициализируем количество аргументов

    // Парсинг команды
    cmd_info.command = strtok((char *)input, " "); // Извлекаем первый токен - команду
    
    // Парсинг ключей и их значений
    char *token = strtok(NULL, " "); // Получаем следующий токен после команды
    while (token != NULL && token[0] == '-') { // Пока есть токен и он начинается с символа '-'
        cmd_info.keys[cmd_info.num_keys] = token; // Записываем токен как ключ
        token = strtok(NULL, " "); // Получаем следующий токен
        if (token != NULL && token[0] != '-') { // Если следующий токен не начинается с '-'
            cmd_info.values[cmd_info.num_keys] = token; // Записываем его как значение для ключа
            cmd_info.num_keys++; // Увеличиваем счетчик ключей
            token = strtok(NULL, " "); // Получаем следующий токен
        }
    }

    // Парсинг аргументов
    while (token != NULL) { // Пока есть следующий токен
        cmd_info.args[cmd_info.num_args] = token; // Записываем токен как аргумент
        cmd_info.num_args++; // Увеличиваем счетчик аргументов
        token = strtok(NULL, " "); // Получаем следующий токен
    }

    return cmd_info; // Возвращаем структуру CommandInfo с информацией о команде
}

int main() {
    char input[MAX_CMD_LEN]; // Объявление переменной для хранения введенной команды
    printf("Введите команду: ");
    fgets(input, sizeof(input), stdin); // Получение ввода от пользователя

    // Удаление символа новой строки из введенной строки
    input[strlen(input)-1] = '\0'; // Замена символа новой строки на нулевой символ

    CommandInfo cmd_info = parse_command(input); // Вызов функции для парсинга введенной команды

    input[0] = '0'; // Изменение первого символа введенной строки (это действие выглядит непонятным и может быть ненужным)

    printf("Команда: %s\n", cmd_info.command); // Вывод команды
    printf("Ключи и их значения:\n");
    for (int i = 0; i < cmd_info.num_keys; i++) { // Вывод ключей и их значений
        printf("%s -> %s\n", cmd_info.keys[i], cmd_info.values[i]);
    }
    printf("Аргументы:\n");
    for (int i = 0; i < cmd_info.num_args; i++) { // Вывод аргументов
        printf("%s\n", cmd_info.args[i]);
    }

    return 0; // Возвращаем ноль, чтобы показать успешное выполнение программы
}

