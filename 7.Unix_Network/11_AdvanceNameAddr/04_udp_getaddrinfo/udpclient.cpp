#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>

#include <stdlib.h>
#include <stdio.h>

#include <iostream>
using namespace std;

#include "unp.h"

#define SERV_PORT 7678

void dg_cli(FILE *fp, int sockfd, const sockaddr *pservaddr, socklen_t servlen)
{
    int n;
    char sendline[MAXLINE], recvline[MAXLINE + 1];
    while (fgets(sendline, MAXLINE, fp))
    {
        sendto(sockfd, sendline, MAXLINE, 0, pservaddr, servlen);
        n = recvfrom(sockfd, recvline, MAXLINE, 0, NULL, NULL);
        recvline[n] = 0;
        fputs(recvline, stdout);
    }
}

int main(int argc, char *argv[])
{
    int sockfd;
    int n;
    socklen_t salen;
    struct sockaddr* sa;    

    // if (argc != 3)
    // {
    //     cout << "use: client <IPAdress>" << endl;
    //     return -1;
    // }

    sockfd = udp_client("127.0.0.1", "7678", (void**)&sa, &salen);
    dg_cli(stdin, sockfd, (sockaddr *)sa, salen);
    exit(0);
}