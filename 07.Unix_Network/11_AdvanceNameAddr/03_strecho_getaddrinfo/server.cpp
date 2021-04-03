#include "unp.h"
#include "string.h"
#include <stdlib.h>
#include <iostream>
#include "errno.h"
using namespace std;

#define SERV_PORT 9871

void str_echo(int sockfd)
{
    ssize_t n;
    char line[MAXLINE];
    for(;;)
    {
        // it will be blocked by read
        // when server receive a FIN, read return 0
        if ((n = read(sockfd, line, MAXLINE)) == 0)
        {
            cout << "n = 0!!!" << endl;
            return;
        }
        n = write(sockfd, line, sizeof(line));
        memset(line, 0, MAXLINE);
    }
}

int main(int argc, char* argv[])
{
    int listenfd, connfd;
    pid_t childpid;
    socklen_t clilen;
    socklen_t addrlen;
    struct sockaddr_in *cliaddr, servaddr;

    // listenfd = socket(AF_INET, SOCK_STREAM, 0);
    listenfd = tcp_listen(NULL, "9871", &addrlen);

    cliaddr = (struct sockaddr_in*)malloc(addrlen);

    for(;;)
    {
        clilen = addrlen;//sizeof(cliaddr);
        connfd = accept(listenfd, (sockaddr*)&cliaddr, &clilen);
        // fork return 0: child process
        if((childpid = fork()) == 0)
        {
            // child process close listening socket
            close(listenfd);
            // child process processes the request
            str_echo(connfd);

            /* terminate child process by calling exit(0)
            *
            *  (1). the fd connfd will be closed, which leads to send FIN to client, 
            *  (2). and server will receive a ACK from client.
            *  (3). thus, the connection is totally terminated.
            *  (4). child process will send a SIGCHLD to parent process.
            *
            */
            exit(0);
        }
        close(connfd);
    }


    return 0;
}