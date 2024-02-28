#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdlib.h>
#include <sys/wait.h>

/*
Реализовать программу, которая порождает процесс. Родительский 
процесс и дочерний выводят на экран свой pid, ppid. Затем родительский 
ждет завершения дочернего и выводит его статус завершения.
*/

int main(){
    pid_t child_pid;
    int child_status;

    child_pid = fork();
    if (child_pid == 0){
        printf("child pid: %d\n", getpid());
        exit(0);
    }else{
        printf("parent pid: %d\n", getpid());
        wait(&child_status);
        printf("child process exit status: %d\n", WEXITSTATUS(child_status));
    }

    return 0;
}