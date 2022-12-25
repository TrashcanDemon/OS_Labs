#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <sys/wait.h>
#include <time.h>

int main(){
    pid_t pid;
    int fd[2];
    int status;
    time_t t;
    pipe(fd);
       
    switch(pid = fork()){
    default:
        close(fd[0]);

        time(&t);
        write(fd[1], &t, sizeof(t));

        wait(&status);
        break;
    case 0:
        close(fd[1]);

        read(fd[0], &t, sizeof(t));
        printf("[PARENT]: %s", ctime(&t));

        usleep(5000000);
        time(&t);
        printf("[CHILD]: %s", ctime(&t));

        exit(0);
        break;
    case -1:
        printf("Fork Error: %d", errno);
        exit(1);
        break;
    }
    return 0;
}