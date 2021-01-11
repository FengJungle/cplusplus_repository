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
#define DNG 20000
#define DGLEN 1400

void dg_cli(FILE *fp, int sockfd, const sockaddr *pservaddr, socklen_t servlen)
{
    int i;
    char sendline[MAXLINE];
    for (i = 0; i < DNG; i++)
    {
        // cout << "i = " << i << endl;
        sendto(sockfd, sendline, DGLEN, 0, pservaddr, servlen);
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