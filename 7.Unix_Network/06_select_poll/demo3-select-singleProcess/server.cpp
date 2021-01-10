#include "unp.h"
#include "string.h"
#include <stdlib.h>
#include <iostream>
#include "errno.h"
using namespace std;

#define SERV_PORT 9870

int main(int argc, char *argv[])
{
    int listenfd, connfd, sockfd;

    // the first parameter of select
    int maxfd;
    fd_set rset, allset;

    int i;

    ssize_t n;
    char line[MAXLINE];

    // the maximum index of the array client
    int maxi;

    // the number of the total readable descriptors
    int nready;

    int client[FD_SETSIZE]; // 1024

    pid_t childpid;
    socklen_t clilen;
    struct sockaddr_in cliaddr, servaddr;

    listenfd = socket(AF_INET, SOCK_STREAM, 0);

    memset(&servaddr, 0, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servaddr.sin_port = htons(SERV_PORT);

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

    maxfd = listenfd;
    maxi = -1;

    for (i = 0; i < FD_SETSIZE; i++)
    {
        client[i] = -1;
    }

    FD_ZERO(&allset);
    FD_SET(listenfd, &allset);

    for (;;)
    {
        // assignment
        rset = allset;

        // nready: the number of the total readable descriptors
        nready = select(maxfd + 1, &rset, NULL, NULL, NULL);
        // check if there is new connection
        if (FD_ISSET(listenfd, &rset))
        {
            clilen = sizeof(cliaddr);
            // When accept is blocked, when it returns, there may be an EINTR error returned by system call.
            // In order to process an interrupted accept, we need to do like this:
            if ((connfd = accept(listenfd, (sockaddr *)&cliaddr, &clilen)) < 0)
            {
                // If system return EINTR, restart the system call accept.
                if (errno == EINTR)
                {
                    continue;
                }
                else
                {
                    cout << "accept error!" << endl;
                }
            }
            cout<<"new client"<<endl;

            // save descriptor
            for (i = 0; i < FD_SETSIZE; i++)
            {
                if (client[i] < 0)
                {
                    client[i] = connfd;
                    break;
                }
            }

            if (i == FD_SETSIZE)
            {
                cout << "ERROR: too many clients!" << endl;
                return -1;
            }

            FD_SET(connfd, &allset);
            if (connfd > maxfd)
            {
                maxfd = connfd;
            }

            if (i > maxi)
            {
                maxi = i;
            }

            if (--nready <= 0)
            {
                // no more readable descriptors
                continue;
            }
        }

        // check all clients data
        for (i = 0; i <= maxi; i++)
        {
            sockfd = client[i];
            if (sockfd < 0)
            {
                continue;
            }

            if (FD_ISSET(sockfd, &rset))
            {
                // it will be blocked by read
                // when server receive a FIN, read return 0
                if (read(sockfd, line, MAXLINE) == 0)
                {
                    cout << "n = 0!!!" << endl;
                    close(sockfd);
                    FD_CLR(sockfd, &allset);
                    client[i] = -1;
                }
                else
                {
                    cout<<"client: "<<line<<endl;
                    n = write(sockfd, line, sizeof(line));
                    memset(line, 0, MAXLINE);
                }
                if (--nready <= 0)
                {
                    break;
                }
            }
        }
    }

    return 0;
}