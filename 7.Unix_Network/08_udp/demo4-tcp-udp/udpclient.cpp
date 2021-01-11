#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>

#include <stdlib.h>
#include <stdio.h>

#include <iostream>
using namespace std;

#define SERV_PORT 7678
#define SERV_PORT_2 7679
#define MAXLINE 256

void dg_cli(FILE *fp, int sockfd, const sockaddr *pservaddr, socklen_t servlen)
{
    cout<<"enter dg_cli"<<endl;
    int n;
    char sendline[MAXLINE], recvline[MAXLINE + 1];
    while (fgets(sendline, MAXLINE, fp))
    {
        cout<<"udp client :"<<sendline<<endl;
        sendto(sockfd, sendline, MAXLINE, 0, pservaddr, servlen);
        n = recvfrom(sockfd, recvline, MAXLINE, 0, NULL, NULL);
        recvline[n] = 0;
        cout<<"server: "<<recvline<<endl;
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
    servaddr.sin_port = htons(SERV_PORT_2);
    // inet_pton(AF_INET, argv[1], &servaddr.sin_addr);
    inet_pton(AF_INET, "127.0.0.1", &servaddr.sin_addr);

    sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    dg_cli(stdin, sockfd, (sockaddr *)&servaddr, sizeof(servaddr));
    exit(0);
}