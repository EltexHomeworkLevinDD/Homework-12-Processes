#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdlib.h>
#include <sys/wait.h>

/*
Реализовать программу, которая порождает процесс1 и процесс2, ждет 
завершения дочерних процессов. Процесс1 в свою очередь порождает 
процесс3 и процесс4 и ждет их завершения. Процесс2 порождает 
процесс5 и ждет его завершения. Все процессы выводят на экран свой 
pid, ppid. 
*/

int main(){
    printf("Process 0 ppid: %d\n", getppid());
    printf("Process 0 pid: %d\n", getpid());

    pid_t p0_child1_pid;
    int p0_child1_status;

    // --> Process 0
    p0_child1_pid = fork();
    if (p0_child1_pid == 0)
    {
        // --> Process 1
        printf("\tProcess 1 ppid: %d\n", getppid());
        printf("\tProcess 1 pid: %d\n", getpid());
        pid_t p1_child1_pid;
        int p1_child1_status;
        p1_child1_pid = fork();
        if (p1_child1_pid == 0)
        {
            // --> Process 3
            printf("\t\tProcess 3 ppid: %d\n", getppid());
            printf("\t\tProcess 3 pid: %d\n", getpid());
            exit(0);
            // Process 3 <--
        }
        // --> Process 1
        else
        {
            pid_t p1_child2_pid;
            int p1_child2_status;
            p1_child2_pid = fork();
            if (p1_child2_pid == 0)
            {
                // --> Process 4
                printf("\t\tProcess 4 ppid: %d\n", getppid());
                printf("\t\tProcess 4 pid: %d\n", getpid());
                exit(0);
                // Process 4 <--
            }
            // Process 1 <--
            else
            {
                waitpid(p1_child1_pid, &p1_child1_status, 0);
                waitpid(p1_child2_pid, &p1_child2_status, 0);
                exit(0);
            }
        }
    }
    else
    {
        // --> Process 0
        pid_t p0_child2_pid;
        int p0_child2_status;
        p0_child2_pid = fork();
        if (p0_child2_pid == 0)
        {
            // --> Process 2
            printf("\tProcess 2 ppid: %d\n", getppid());
            printf("\tProcess 2 pid: %d\n", getpid());
            pid_t p2_child_pid;
            int p2_child_status;
            p2_child_pid = fork();
            if (p2_child_pid == 0)
            {
                // --> Process 5
                printf("\t\tProcess 5 ppid: %d\n", getppid());
                printf("\t\tProcess 5 pid: %d\n", getpid());
                exit(0);
                // Process 5 <--
            }
            // Process 2 <--
            else
            {
                waitpid(p2_child_pid, &p2_child_status, 0);
                exit(0);
            }
        }
        // Process 0 <--
        else
        {
            waitpid(p0_child1_pid, &p0_child1_status, 0);
            waitpid(p0_child2_pid, &p0_child2_status, 0);
            exit(0);
        }
    }

    return 0;
}