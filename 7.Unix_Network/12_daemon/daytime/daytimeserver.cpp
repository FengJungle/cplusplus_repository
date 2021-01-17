#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <netdb.h>
#include <unistd.h>

#include <time.h>

#include <iostream>
using namespace std;

#define SERV_PORT   9871
#define BUFFER_SIZE 1024

int tcp_listen(const char* host, const char* serv, socklen_t* addrlenp)
{
	int listenfd;
	int n;
	const int on = 1;
	struct addrinfo hints;
	struct addrinfo *res;
	struct addrinfo *ressave;

	memset(&hints, 0, sizeof(hints));
	// server: passive receive
	hints.ai_flags = AI_PASSIVE;
	hints.ai_family = AF_UNSPEC;
	hints.ai_socktype = SOCK_STREAM;

	if((n = getaddrinfo(host, serv, &hints, &res)) != 0)
	{
		cout << "tcp_listen failed " << gai_strerror(n) << endl;
	}

	ressave = res;
	do
	{
		listenfd = socket(res->ai_family, res->ai_socktype, res->ai_protocol);
		if(listenfd < 0)
		{
			continue;
		}
		setsockopt(listenfd, SOL_SOCKET, SO_REUSEADDR, &on, sizeof(on));
		if(bind(listenfd, res->ai_addr, res->ai_addrlen) == 0)
		{
			// success
			break;
		}
		close(listenfd);
	} while ((res = res->ai_next) != NULL);
	
	if(res == NULL)
	{
		cout << "tcp_listen failed" << endl;
	}

	listen(listenfd, 5);

	if(addrlenp)
	{
		*addrlenp = res->ai_addrlen;
	}

	freeaddrinfo(ressave);
	return listenfd;
}

void daytime_pro(int sockfd)
{
    ssize_t n;
    char buff[BUFFER_SIZE];
    time_t ticks;
    for(;;)
    {
        n = read(sockfd, buff, BUFFER_SIZE);
        buff[n-1]= 0;
        if (strcmp(buff, "daytime") == 0)
        {
            memset(buff, 0, BUFFER_SIZE);
            ticks = time(NULL);
            snprintf(buff, sizeof(buff), "%24s\r\n", ctime(&ticks));
            n = write(sockfd, buff, strlen(buff));
            memset(buff, 0, BUFFER_SIZE);
        }
    }
}

int main(int argc, char* argv[])
{
    int listenfd, connfd;
    pid_t childpid;
    socklen_t clilen;
    socklen_t addrlen;
    struct sockaddr_in *cliaddr, servaddr;

    // listenfd = socket(AF_INET, SOCK_STREAM, 0);
    listenfd = tcp_listen(NULL, "9871", &addrlen);

    cliaddr = (struct sockaddr_in*)malloc(addrlen);

    for(;;)
    {
        clilen = addrlen;//sizeof(cliaddr);
        connfd = accept(listenfd, (sockaddr*)&cliaddr, &clilen);
        // fork return 0: child process
        if((childpid = fork()) == 0)
        {
            // child process close listening socket
            close(listenfd);
            // child process processes the request
            daytime_pro(connfd);

            /* terminate child process by calling exit(0)
            *
            *  (1). the fd connfd will be closed, which leads to send FIN to client, 
            *  (2). and server will receive a ACK from client.
            *  (3). thus, the connection is totally terminated.
            *  (4). child process will send a SIGCHLD to parent process.
            *
            */
            exit(0);
        }
        close(connfd);
    }


    return 0;
}