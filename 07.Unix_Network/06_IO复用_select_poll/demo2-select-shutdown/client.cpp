#include "unp.h"
#include <iostream>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
using namespace std;

#define SERV_PORT 9875

void str_cli(FILE *fp, int sockfd)
{
    int stdin_eof = 0;

    int maxfdpl;
    fd_set read_set;

    FD_ZERO(&read_set);

    int ret = 0;
    char sendline[MAXLINE], recvline[MAXLINE];
    char sendbackline[MAXLINE];

    while (1)
    {
        if (stdin_eof == 0)
        {
            // fileno: get file descriptor of fp
            FD_SET(fileno(fp), &read_set);
        }
        FD_SET(sockfd, &read_set);

        // remember +1
        maxfdpl = max(fileno(fp), sockfd) + 1;
        select(maxfdpl, &read_set, NULL, NULL, 0);

        // check if socket is readable
        if (FD_ISSET(sockfd, &read_set))
        {
            ret = read(sockfd, recvline, MAXLINE);
            // 1. error happend
            if (ret < 0)
            {
                //cout << "read failed with errno: " << errno << endl;
                continue;
            }
            // 2. read EOF, close socket
            if (ret == 0)
            {
                // normal termination
                if (stdin_eof == 1)
                {
                    return;
                }
                else
                {
                    cout << "server terminated prematurely" << endl;
                }
            }
            memset(sendbackline, 0, MAXLINE);
            memcpy(sendbackline, "Server: ", sizeof("Server: ") + 1);
            strcat(sendbackline, recvline);
            fputs(sendbackline, stdout);
        }

        // check if input is readable
        if (FD_ISSET(fileno(fp), &read_set))
        {
            if (fgets(sendline, MAXLINE, fp) == NULL)
            {
                stdin_eof = 1;
                // no data to send, send FIN to server
                // do not call close(), close() will close the socket totally, but there may be input data from server,
                // if call close(), client cannot receive it.
                shutdown(sockfd, SHUT_WR);
                FD_CLR(fileno(fp), &read_set);
                continue;
            }
            writen(sockfd, sendline, strlen(sendline));
        }
    }
}

int main(int argc, char *argv[])
{
    int sockfd;
    struct sockaddr_in servaddr;

    if (argc != 2)
    {
        cout << "usage: tcpcli<IPaddress>" << endl;
        return -1;
    }
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    memset(&servaddr, 0, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(SERV_PORT);
    inet_pton(AF_INET, argv[1], &servaddr.sin_addr);
    connect(sockfd, (sockaddr *)&servaddr, sizeof(servaddr));
    str_cli(stdin, sockfd);

    /*
    *  (1). client close socket, will send a FIN to server, and client is entering FIN-WAIT-1 state
    *  (2). server tcp will send back a ACK, then client tcp goes into FIN-WAIT-2 state
    *  (3). when client tcp receive a FIN from server tcp, it goes into TIME-WAIT state
    */
    close(sockfd);
    exit(0);
}