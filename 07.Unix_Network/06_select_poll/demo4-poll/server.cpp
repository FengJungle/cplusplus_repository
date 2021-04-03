#include "unp.h"
#include "string.h"
#include <stdlib.h>
#include <iostream>
using namespace std;

#include "errno.h"

// poll
#include <poll.h>

// OPEN_MAX
#include <limits.h>

#include <time.h>

#define SERV_PORT 9870

int main(int argc, char *argv[])
{
    int listenfd, connfd, sockfd;

    int i;

    ssize_t n;
    char line[MAXLINE];

    // the maximum index of the array client
    int maxi;

    // the number of the total readable descriptors
    int nready;

    // FengJungle; I cannot find the definitions of OPEN_MAX
    // struct pollfd client[OPEN_MAX];
    struct pollfd client[256];

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

    client[0].fd = listenfd;
    client[0].events = POLLRDNORM;
    for (i = 1; i < 256; i++)
    {
        client[i].fd = -1;
    }
    maxi = 0;

    for (;;)
    {
        // nready: the number of the total readable descriptors
        nready = poll(client, maxi + 1, -1);

        // check if there is new connection
        if (client[0].revents & POLLRDNORM)
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
            cout << "new client" << endl;

            for (i = 1; i < 256; i++)
            {
                if (client[i].fd < 0)
                {
                    client[i].fd = connfd;
                    break;
                }
            }
            if (i == 256)
            {
                cout << "ERROR: too many clients!" << endl;
                return -1;
            }
            client[i].events = POLLRDNORM;
            if (i > maxi)
            {
                maxi = i;
            }
            if (--nready <= 0)
            {
                continue;
            }
        }

        // check all clients data
        for (i = 1; i <= maxi; i++)
        {
            sockfd = client[i].fd;
            if (sockfd < 0)
            {
                continue;
            }

            if (client[i].revents & (POLLRDNORM | POLLERR))
            {
                // it will be blocked by read
                // when server receive a FIN, read return 0
                n = read(sockfd, line, MAXLINE);
                if (n == 0)
                {
                    cout << "n = 0!!!" << endl;
                    close(sockfd);
                    client[i].fd = -1;
                }
                else if (n < 0)
                {
                    if (errno == ECONNRESET)
                    {
                        close(sockfd);
                        client[i].fd = -1;
                    }
                    else
                    {
                        cout << "read failed with errno: " << errno << endl;
                    }
                }
                else
                {
                    cout << "client: " << line << endl;
                    write(sockfd, line, sizeof(line));
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