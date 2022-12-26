#include <sys/stat.h>
#include <unistd.h>
#include <signal.h>
#include <stdio.h>
#include <fcntl.h>
#include <time.h>

void eXit(int);

int main()
{
    char name[]="/tmp/fifo.file";
    int fifo;
    time_t tme;
    pid_t pid = getpid();

    if((mkfifo(name, S_IRWXU))==-1)
    {
        printf("didn't make fifo.file\n\n");
        return 1;
    }

    struct sigaction sigT;
    sigT.sa_handler = eXit;
    sigaction(SIGTSTP, &sigT, NULL);

    while (1)
    {
        time(&tme);
        fifo = open(name, O_WRONLY);
        write(fifo, &tme, sizeof(tme));
        write(fifo, &pid, sizeof(pid));
        close(fifo);
        sleep(5);
    }
    
    return 0;
}

void eXit(int n)
{
    char name[]="/tmp/fifo.file";
    unlink(name);
    pid_t pig = getpid();
    printf("\n");
    kill(pig, 13);
}