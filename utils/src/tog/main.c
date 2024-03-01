#include <stdlib.h>
#include "showdir.h"

int main(int argc, char* argv[]){
    printf("Количество аргументов: %d\n", argc);
    printf("Аргументы командной строки:\n");
    for (int i = 0; i < argc; i++) {
        printf("argv[%d]: %s\n", i, argv[i]);
    }

    return 0;
}