#include "unp.h"
#include "string.h"
#include <stdlib.h>
#include <iostream>
#include "errno.h"
using namespace std;

#include <sys/un.h>

#define SERV_PORT 9871

void str_echo(int sockfd)
{
    ssize_t n;
    char line[MAXLINE];
    for (;;)
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

int main(int argc, char *argv[])
{
    int listenfd, connfd;
    pid_t childpid;
    socklen_t clilen;

    // Unix protocol
    struct sockaddr_un cliaddr, servaddr;

    // AF_LOCAL
    listenfd = socket(AF_LOCAL, SOCK_STREAM, 0);
    unlink(UNIXSTR_PATH);

    memset(&servaddr, 0, sizeof(servaddr));
    servaddr.sun_family = AF_LOCAL;
    strcpy(servaddr.sun_path, UNIXSTR_PATH);

    // bind a local protocol (address, port) to listenfd
    if (0 != bind(listenfd, (sockaddr *)&servaddr, sizeof(servaddr)))
    {
        cout << "bind failed with errno : " << errno << endl;
        return -1;
    }

    if (-1 == listen(listenfd, 5))
    {
        cout << "listen failed with errno:0x%x" << errno << endl;
        return -1;
    }

    Signal(SIGCHLD, sig_chld);

    for (;;)
    {
        clilen = sizeof(cliaddr);
        if ((connfd = accept(listenfd, (sockaddr *)&cliaddr, &clilen)) < 0)
        {
            if (errno == EINTR)
            {
                continue;
            }
            else
            {
                cout << "accept failed with errno:" << errno << endl;
            }
        }
        // fork return 0: child process
        if ((childpid = fork()) == 0)
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