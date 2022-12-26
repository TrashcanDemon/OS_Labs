#include <sys/stat.h>
#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include <time.h>

int main()
{
    char name[]="/tmp/fifo.file";
    int fifo;
    time_t tme;
    pid_t pid;
    
    while (1)
    {
        sleep(3);
        fifo = open(name, O_RDONLY);
        read(fifo, &tme, sizeof(tme));
        read(fifo, &pid, sizeof(pid));
        close(fifo);
        printf("%i:  %s\n", pid, ctime(&tme));
        sleep(2);
    }
    
    return 0;
}