#include <sys/types.h>
#include <sys/stat.h>
#include <errno.h>
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <limits.h>

#define BUFSZ PIPE_BUF  // 4096

int main(int argc, char* argv[])
{
    int fd;
    int n, i;
    char buf[BUFSZ];
    time_t tp;
    printf("PID: %d\n", getpid());
    
    // open fifo with write-only
    if((fd = open("fifo1", O_WRONLY))<0)
    {
        perror("open");
        exit(1);
    }

    // for-loop: write data to fifo
    for(i = 0;i<10;i++)
    {
        // get system time
        time(&tp);

        // pid and time
        n = sprintf(buf, "write_fifo %d sends %d", getpid(), ctime(&tp));
        printf("Send msg:%s\n", buf);

        // write into fifo
        if(write(fd, buf, n+1)<0)
        {
            perror("write");
            close(fd);
            exit(1);
        }
        sleep(3);
    }
    close(fd);
    exit(0);
}
