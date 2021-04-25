/*

最简单的epoll使用范例：监听标准输入，并将数据回显到终端

*/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/epoll.h>

#ifndef MAX_LEN
#define MAX_LEN 256
#endif

#define EPOLL_SIZE 1000

int main(int argc, char* argv[])
{
    int fd = 0;
    int len = 0;
    int nfds = 0;
    int index = 0;
    char buf[MAX_LEN] = {0};
    struct epoll_event ev;
    struct epoll_event events[EPOLL_SIZE];

    // 1. create an epoll object
    if ((fd = epoll_create(EPOLL_SIZE)) < 0)
    {
        perror("create epoll error!");
        return -1;
    }

    // 2. add a file descriptor which you cared about
    ev.data.fd = STDIN_FILENO;
    ev.events = EPOLLIN | EPOLLET;
    if(epoll_ctl(fd, EPOLL_CTL_ADD, ev.data.fd, &ev) == -1)
    {
        printf("epoll_ctl error!");
        return -1;
    }

    // 3. begin to listen the file descriptor
    while(1)
    {
        nfds = epoll_wait(fd, events, 1000, -1);
        if(nfds == -1)
        {
            perror("epoll_wait error!");
            continue;
        }
        for (int i = 0; i < nfds; i++)
        {
            if(events[i].events == EPOLLIN)
            {
                len = read(events[i].data.fd, buf, sizeof(buf));
                buf[len] = '\0';
                printf("buf = %s\n", buf);
            }
        }
    }
    exit(0);
}