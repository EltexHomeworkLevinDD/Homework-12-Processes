/*
3) Реализовать аналог командного интерпретатора bash. При запуске 
программы пользователю предлагается ввести имя программы и опции 
запуска программы. Программа порождает процесс и в нем выполняет 
введенную программу с заданными опциями, ждет завершения 
дочернего процесса. Снова возвращается к вводу следующей 
программы. Выход из интерпретатора по команде exit. 
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>

int main(){

    //  showdir [keys] [args]
    //      
    //      -s alpha/version --sort-alpha --sort-version
    //      -c number_of_entries

    //  tog [keys] [args]
    //      -c "message" --> txt file create
    //      -s show_file --> txt_file show
    
    return 0;
}