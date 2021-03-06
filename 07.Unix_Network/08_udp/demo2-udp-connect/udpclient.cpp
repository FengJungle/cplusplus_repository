#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#include <unistd.h>

#include <stdlib.h>
#include <stdio.h>

#include <iostream>
using namespace std;

#define SERV_PORT 7678
#define MAXLINE 256

void dg_cli(FILE *fp, int sockfd, const sockaddr *pservaddr, socklen_t servlen)
{
    int n;
    char sendline[MAXLINE], recvline[MAXLINE + 1];

    connect(sockfd, (sockaddr*)pservaddr, servlen);

    while (fgets(sendline, MAXLINE, fp))
    {
        /*
        * 1. do not call sendto, because each time call sendto, a socket connect will be executed, 
        *    and kernel will copy a socket structure (including IP and port)
        * 2. call write() instead.
        */
        write(sockfd, sendline, strlen(sendline));
        // sendto(sockfd, sendline, MAXLINE, 0, pservaddr, servlen);
        
        /*
        * Similarly, do not calll recvfrom, call read instead.
        */
        // n = recvfrom(sockfd, recvline, MAXLINE, 0, NULL, NULL);
        n = read(sockfd, recvline, MAXLINE);        
        recvline[n] = 0;
        fputs(recvline, stdout);
    }
}

int main(int argc, char *argv[])
{
    int sockfd;
    struct sockaddr_in servaddr;

    if (argc != 2)
    {
        //cout << "use: client <IPAdress>" << endl;
        // return -1;
    }

    memset(&servaddr, 0, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(SERV_PORT);
    // inet_pton(AF_INET, argv[1], &servaddr.sin_addr);
    inet_pton(AF_INET, "127.0.0.1", &servaddr.sin_addr);

    sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    dg_cli(stdin, sockfd, (sockaddr *)&servaddr, sizeof(servaddr));
    exit(0);
}