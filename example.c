#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void command_ls(int num_args, char **args) {
    // Ваш код для обработки команды ls
    printf("Executing 'ls' command with %d arguments:\n", num_args);
    for (int i = 0; i < num_args; ++i) {
        printf("- %s\n", args[i]);
    }
}

void command_echo(int num_args, char **args) {
    // Ваш код для обработки команды echo
    printf("Executing 'echo' command with %d arguments:\n", num_args);
    for (int i = 0; i < num_args; ++i) {
        printf("- %s\n", args[i]);
    }
}

// Функция для выполнения соответствующего действия в зависимости от команды
void process_command(char *command, char **args, int num_args) {
    if (strcmp(command, "ls") == 0) {
        command_ls(num_args, args);
    } else if (strcmp(command, "echo") == 0) {
        command_echo(num_args, args);
    } else {
        printf("Unknown command: %s\n", command);
    }
}

int main() {
    char input[100];
    
    while (1) {
        printf("Enter command: ");
        fgets(input, sizeof(input), stdin);
        
        // Удаление символа новой строки, добавленного функцией fgets
        input[strcspn(input, "\n")] = 0;

        char *command = strtok(input, " ");
        char *args[10]; // Массив аргументов, допустим 10 аргументов

        // Получение аргументов
        int num_args = 0;
        char *arg = strtok(NULL, " ");
        while (arg != NULL) {
            args[num_args++] = arg;
            arg = strtok(NULL, " ");
        }

        // Обработка команды
        process_command(command, args, num_args);
    }

    return 0;
}

В этом примере добавлены две простые команды: ls и echo. Каждая команда имеет 
свою собственную функцию обработки (command_ls и command_echo соответственно). 
Когда пользователь вводит команду, программа проверяет, какая команда была 
введена, и вызывает соответствующую функцию обработки.

Enter command: ls -l -a
Executing 'ls' command with 2 arguments:
- -l
- -a
Enter command: echo Hello World!
Executing 'echo' command with 2 arguments:
- Hello
- World!
Enter command: unknown
Unknown command: unknown
Enter command:
