#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <sys/wait.h>
#include <time.h>
#include <sys/stat.h>
#include <fcntl.h>

int main(){
    pid_t pid;
    int status;
    time_t t;
    char name[] = "/tmp/fifo";
    int fifo;
    if((mknod(name, S_IRWXU, 0)) == -1)
    {
        printf("MkNod Error: %d", errno);
        exit(1);
    }

    switch(pid = fork())
    {
    default:
        fifo = open(name, O_WRONLY);

        time(&t);
        write(fifo, &t, sizeof(t));

        close(fifo);
        wait(&status);
        break;
    case 0:
        fifo = open(name, O_RDONLY);
        
        read(fifo, &t, sizeof(t));
        printf("[PARENT]: %s", ctime(&t));

        usleep(5000000);
        time(&t);
        printf("[CHILD]: %s", ctime(&t));

        close(fifo);
        unlink(name);
        exit(0);
        break;
    case -1:
        printf("Fork Error: %d", errno);
        exit(1);
        break;
    }
    return(0);
}