#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <limits.h>
#include <fcntl.h>

#define BUF_SZ PIPE_BUF

int main(int argc, char* argv[])
{
    int fd;
    int len;
    char buf[BUF_SZ];
    mode_t mode = 0x666;
    // open fifo
    if((fd = open("fifo1", O_RDONLY))<0)
    {
        perror("open");
        exit(1);
    }
    while((len = read(fd, buf, BUF_SZ))>0)
    {
        printf("read_fifo read: %s\n", buf);
    }
    close(fd);
    exit(0);
}