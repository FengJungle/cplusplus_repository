#include "unp.h"
#include "string.h"
#include <stdlib.h>
#include <iostream>
#include "errno.h"
using namespace std;

#define SERV_PORT 9875

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
            cout << "recv:" << line << endl;
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
    struct sockaddr_in cliaddr, servaddr;

    listenfd = socket(AF_INET, SOCK_STREAM, 0);

    memset(&servaddr, 0, sizeof(servaddr));
    servaddr.sin_family= AF_INET;
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servaddr.sin_port = htons(SERV_PORT);
    
    // bind a local protocol (address, port) to listenfd
    if(0 != bind(listenfd, (sockaddr*)&servaddr, sizeof(servaddr)))
    {
        cout << "bind failed with errno : " << errno << endl;
        return -1;
    }

    if( -1 == listen(listenfd, 5))
    {
        cout<<"listen failed with errno:0x%x"<<errno<<endl;
        return -1;
    }

    // must call wait_pid
    Signal(SIGCHLD, sig_chld);

    for(;;)
    {
        clilen = sizeof(cliaddr);

        // When accept is blocked, when it returns, there may be an EINTR error returned by system call.
        // In order to process an interrupted accept, we need to do like this:
        if ((connfd = accept(listenfd, (sockaddr *)&cliaddr, &clilen)) < 0)
        {
            // If system return EINTR, restart the system call accept.
            if(errno == EINTR)
            {
                continue;
            }
            else
            {
                cout << "accept error!" << endl;
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