#include <netinet/in.h>
#include <string.h>
#include <sys/un.h>
#include <stdlib.h>
#include "unp.h"
#include <iostream>
using namespace std;

#define SERV_PORT 7678
// #define MAXLINE 256

/*
* This demo simply realize a udp server.
* It offers a iterative server, not like concurrent server in TCP,
* there is no fork. A singer server process handles all clients.
*
* In fact, there is a FIFO for udp socket recv buffer.
*/

void dg_echo(int sockfd, sockaddr* pcliaddr, socklen_t clilen)
{
    int n;
    socklen_t len;
    char msg[MAXLINE];

    while(1)
    {
        len = clilen;
        n = recvfrom(sockfd, msg, MAXLINE, 0, pcliaddr, &len);
        cout<<msg<<endl;
        sendto(sockfd, msg, n, 0, pcliaddr, len);
    }
}

int main(int argc, char* argv[])
{
    int sockfd;
    struct sockaddr_un servaddr, cliaddr;
    
    sockfd = socket(AF_LOCAL, SOCK_DGRAM, 0);
    unlink(UNIXSTR_PATH);

    memset(&servaddr, 0, sizeof(servaddr));
    servaddr.sun_family = AF_LOCAL;
    strcpy(servaddr.sun_path, UNIXSTR_PATH);

    bind(sockfd, (sockaddr*)&servaddr, sizeof(servaddr));

    dg_echo(sockfd, (sockaddr*)&cliaddr, sizeof(cliaddr));
}