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

// int main(){
//     pid_t c1pid, c2pid;
//     int s1, s2;
//     printf("Parent pid = %d\n", getpid());

//     c1pid = fork();
//     if (c1pid == 0){ // Child 1
//         printf("\tChild 1 pid = %6d ppid = %d\n", getpid(), getppid());
//         exit(1);
//     }
//     else { // Parent
//         c2pid = fork();
//         if (c2pid == 0){ // Child 2
//             printf("\tChild 2 pid = %6d ppid = %d\n", getpid(), getppid());
//             exit(2);
//         }
//     }

//     wait(&s1);
//     wait(&s2);

//     return 0;
// }