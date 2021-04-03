#include <netinet/in.h>
#include <string.h>

#include <stdlib.h>
#include "unp.h"

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
        sendto(sockfd, msg, n, 0, pcliaddr, len);
    }
}

int main(int argc, char* argv[])
{
    int sockfd;
    struct sockaddr_in* cliaddr;
    socklen_t addrlen;

    // sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    
    // memset(&servaddr, 0, sizeof(servaddr));
    // servaddr.sin_family = AF_INET;
    // servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    // servaddr.sin_port = htons(SERV_PORT);

    // bind(sockfd, (sockaddr*)&servaddr, sizeof(servaddr));

    // use getaddrinfo
    sockfd = udp_server(NULL, "7678", &addrlen);

    cliaddr = (struct sockaddr_in *)malloc(addrlen);

    dg_echo(sockfd, (sockaddr *)cliaddr, sizeof(cliaddr));
}