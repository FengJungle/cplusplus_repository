#include "unp.h"
#include <sys/time.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <errno.h>

#include <iostream>
using namespace std;

#define SERV_PORT 9875

void str_cli(FILE* fp, int sockfd)
{
    pid_t pid;
    char sendline[MAXLINE];
    char recvline[MAXLINE];

    // child process: server -> stdout

    if((pid = fork()) == 0)
    {
        while(readline(sockfd, recvline, MAXLINE)>0)
        {
            fputs(recvline, stdout);
        }
        // in case parent still running
        kill(getppid(), SIGTERM);
        exit(0);
    }

    // parent process: stdin -> server
    while(fgets(sendline, MAXLINE, fp) != NULL)
    {
        cout << sendline << endl;
        write(sockfd, sendline, strlen(sendline));
    }
    // EOF on stdin, send FIN
    shutdown(sockfd, SHUT_WR);
    pause();
    return;
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