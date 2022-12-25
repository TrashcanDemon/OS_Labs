#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <sys/wait.h>

void exitParent();
void exitChild();
void sig_int_handler(int sg);
void sig_term_handler(int sg);

int main(){
    printf("PID: %6d, PPID: %6d\n", getpid(), getppid());
    struct sigaction sigTer;
    struct sigaction sigOut;
    sigTer.sa_handler = sig_term_handler;

    pid_t pid = fork();

    switch (pid)
    {
    default:
        atexit(exitParent);
        sigaction(SIGTERM, &sigTer, &sigOut);
        signal(SIGINT, &sig_int_handler);
        printf("[PARENT] PID: %4d, PPID: %4d\n", getpid(), getppid());
        usleep(1000000);
        break;
    case 0:
        atexit(exitChild);
        printf("[CHILD] PID: %4d, PPID: %4d\n", getpid(), getppid());
        usleep(500000);
        break;
    case -1:
        printf("Fork Error: %d", errno);
        exit(1);
        break;
    }

    return 0;
}

void exitParent(){
    printf("\033[0;31m[PARENT]: Exit.\033[0m\n");
}

void exitChild(){
    printf("\033[0;31m[CHILD]: Exit.\033[0m\n");
}

void sig_int_handler(int sg){
    printf("\n\033[1;20m[CHILD]: SIGINT(%d)\033[0m\n", sg);
}

void sig_term_handler(int sg){
    printf("\n\033[1;20m[CHILD]: SIGTERM(%d)\033[0m\n", sg);
}