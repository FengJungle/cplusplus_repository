#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>

#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#include <iostream>
using namespace std;

#define SERV_PORT 7678
#define MAXLINE 256

void str_cli(FILE* fp, int sockfd)
{
    char sendline[MAXLINE], recvline[MAXLINE];
    char sendbackline[MAXLINE];
    while(fgets(sendline, MAXLINE, fp) != NULL)
    {
        write(sockfd, sendline, strlen(sendline));
        read(sockfd, recvline, MAXLINE);
        memset(sendbackline, 0, MAXLINE);
        memcpy(sendbackline, "Server: ", sizeof("Server: ") + 1);
        strcat(sendbackline, recvline);
        fputs(sendbackline, stdout);
    }
}

int main(int argc, char* argv[])
{
    int sockfd;
    struct sockaddr_in servaddr;

    // if(argc != 2)
    // {
    //     cout<<"usage: tcpcli<IPaddress>"<<endl;
    //     return -1;
    // }
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    memset(&servaddr, 0, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(SERV_PORT);
    inet_pton(AF_INET, "127.0.0.1", &servaddr.sin_addr);
    connect(sockfd, (sockaddr*)&servaddr, sizeof(servaddr));
    str_cli(stdin, sockfd);

    /*
    *  (1). client close socket, will send a FIN to server, and client is entering FIN-WAIT-1 state
    *  (2). server tcp will send back a ACK, then client tcp goes into FIN-WAIT-2 state
    *  (3). when client tcp receive a FIN from server tcp, it goes into TIME-WAIT state
    */
    close(sockfd);
    exit(0);
}