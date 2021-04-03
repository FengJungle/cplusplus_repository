#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#include <sys/un.h>
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
        cout<<"send:"<<sendline<<endl;
        sendto(sockfd, sendline, MAXLINE, 0, pservaddr, servlen);
        n = recvfrom(sockfd, recvline, MAXLINE, 0, NULL, NULL);
        recvline[n] = 0;
        cout<<"recv:"<<recvline<<endl;
        fputs(recvline, stdout);
    }
}

int main(int argc, char *argv[])
{
    int sockfd;
    
    struct sockaddr_un servaddr;    

    sockfd = socket(AF_LOCAL, SOCK_DGRAM, 0);
    memset(&servaddr, 0, sizeof(servaddr));
    servaddr.sun_family = AF_LOCAL;
    strcpy(servaddr.sun_path, UNIXSTR_PATH);
    connect(sockfd, (sockaddr*)&servaddr, sizeof(servaddr));
    dg_cli(stdin, sockfd, (sockaddr *)&servaddr, sizeof(servaddr));
    exit(0);
}