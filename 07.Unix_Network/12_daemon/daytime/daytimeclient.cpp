#include <iostream>
using namespace std;

#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <unistd.h>

#define SERV_PORT   9871
#define BUFFER_SIZE 1024

int tcp_connect(const char *host, const char *serv)
{
	int sockfd;
	int n;

	struct addrinfo hints;
	struct addrinfo *res;
	struct addrinfo *ressave;

	memset(&hints, 0, sizeof(hints));
	hints.ai_family = AF_UNSPEC;
	hints.ai_socktype = SOCK_STREAM;

	if ((n = getaddrinfo(host, serv, &hints, &res)) != 0)
	{
		cout << "error: tcp_connect failed!" << endl;
		return -1;
	}

	ressave = res;
	do
	{
		sockfd = socket(res->ai_family, res->ai_socktype, res->ai_protocol);
		if (sockfd < 0)
		{
			continue;
		}
		if (connect(sockfd, (sockaddr *)(res->ai_addr), res->ai_addrlen) == 0)
		{
			// success
			break;
		}
		close(sockfd);
	} while ((res = res->ai_next) != NULL);

	if (res == NULL)
	{
		cout << "tcp_connect failed" << endl;
		return -1;
	}
	freeaddrinfo(ressave);
	return sockfd;
}

void str_cli(FILE* fp, int sockfd)
{
    char recvline[BUFFER_SIZE + 1];
    char sendline[BUFFER_SIZE];
    int n;
    while (fgets(sendline, BUFFER_SIZE, fp) != NULL)
    {
        // if(strcmp(sendline, "daytime") == 0)
        {
            send(sockfd, sendline, strlen(sendline), 0);
            if((n = read(sockfd, recvline, BUFFER_SIZE)) > 0)
            {
                recvline[n] = 0;
                cout << recvline;
            }
        }
    }
    
    // while ((n = read(sockfd, recvline, BUFFER_SIZE)) > 0)
    // {
    //     recvline[n] = 0;
    //     cout << "recv: " << recvline << endl;
    // }
}

int main(int argc, char* argv[])
{
    int sockfd;
    sockfd = tcp_connect("127.0.0.1","9871");
    str_cli(stdin, sockfd);

    /*
    *  (1). client close socket, will send a FIN to server, and client is entering FIN-WAIT-1 state
    *  (2). server tcp will send back a ACK, then client tcp goes into FIN-WAIT-2 state
    *  (3). when client tcp receive a FIN from server tcp, it goes into TIME-WAIT state
    */
    close(sockfd);
    exit(0);
}