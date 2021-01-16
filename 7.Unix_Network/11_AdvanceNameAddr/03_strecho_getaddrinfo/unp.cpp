#include "unp.h"
#include <string.h>
#include "errno.h"
#include "unistd.h"
#include "stdio.h"
#include "sys/stat.h"

#include <iostream>
using namespace std;

char *sock_ntop(const struct sockaddr *sa, socklen_t salen)
{
	char portstr[7];
	static char str[128];
	switch (sa->sa_family)
	{
	case AF_INET:
	{
		struct sockaddr_in *sin = (struct sockaddr_in *)sa;
		if (inet_ntop(AF_INET, &sin->sin_addr, str, sizeof(str)) == NULL)
		{
			return NULL;
		}
		if (ntohs(sin->sin_port) != 0)
		{
			snprintf(portstr, sizeof(portstr), ".%d", ntohs(sin->sin_port));
			strcat(str, portstr);
		}
		return str;
	}

	default:
		break;
	}
}

ssize_t readn(int fd, void *vptr, size_t n)
{

	size_t nleft;
	size_t nread;
	char *ptr;

	ptr = (char *)vptr;
	nleft = n;
	while (nleft > 0)
	{
		if ((nread == read(fd, ptr, nleft)) < 0)
		{
			if (errno == EINTR)
				nread = 0;
			else
				return -1;
		}
		else if (nread == 0)
			break;
		nleft -= nread;
		ptr += nread;
	}
	return n - nleft;
}

ssize_t writen(int fd, const void *vptr, size_t n)
{
	size_t nleft;
	size_t nwritten;
	const char *ptr;

	ptr = (const char *)vptr;
	nleft = n;
	while (nleft > 0)
	{
		if ((nwritten == write(fd, ptr, nleft)) <= 0)
		{
			if (errno == EINTR)
				nwritten = 0;
			else
				return -1;
		}
		nleft -= nwritten;
		ptr += nwritten;
	}
	return n;
}

static ssize_t my_read(int fd, char *ptr)
{
	static int read_cnt = 0;
	static char *read_ptr;
	static char read_buf[MAXLINE];
	if (read_cnt <= 0)
	{
	again:
		if ((read_cnt = read(fd, read_buf, sizeof(read_buf))) < 0)
		{
			if (errno == EINTR)
			{
				goto again;
			}
			return -1;
		}
		else if (read_cnt == 0)
		{
			return 0;
		}
		read_ptr = read_buf;
	}
	read_cnt--;
	*ptr = *read_ptr++;
	return 1;
}

ssize_t readline(int fd, void *vptr, size_t maxlen)
{
	ssize_t n, rc;
	char c, *ptr;

	ptr = (char *)vptr;
	for (n = 1; n < maxlen; n++)
	{
		if ((rc == my_read(fd, &c)) == 1)
		{
			*ptr++ = c;
			if (c == '\n')
			{
				break;
			}
			else if (rc == 0)
			{
				if (n == 1)
				{
					return 0;
				}
				else
				{
					break;
				}
			}
		}
		else
		{
			return -1;
		}
	}
	*ptr = 0;
	return n;
}

Sigfunc *Signal(int signo, Sigfunc *func)
{
	// act: the method to process the coming signal
	// oldact: the old method to process signal
	struct sigaction act, oldact;

	// function pointer
	act.sa_handler = func;
	sigemptyset(&act.sa_mask);
	act.sa_flags = 0;

	if (signo == SIGALRM)
	{
#ifdef SA_INTERRUPT
		act.sa_flags |= SA_INTERRUPT;
#endif
	}
	else
	{
#ifdef SA_RESTART
		act.sa_flags |= SA_RESTART;
#endif
	}
	// sigaction: the interface to process signal
	// return 0 - success;  -1 - error 
	if (sigaction(signo, &act, &oldact) < 0)
	{
		return SIG_ERR;
	}
	return oldact.sa_handler;
}

#include <sys/wait.h>

/*
* version 1: use wait to process the terminatd child process, but it cannot prevent child process becoming a zombie when 
* multiple child process terminated at the same time
*/
void sig_chld_1(int signo)
{
    pid_t pid;
    int stat;

	// call wait() to fetch the PID and the terminated-state of the child process
	// return PID
	// stat: the terminated-state of the child process
    pid = wait(&stat);
    cout << "child " << pid << " terminated" << endl;
    return ;
}

/*
* version 2: a while loop, use waitpid
*/
void sig_chld(int signo)
{
	pid_t pid;
	int stat;

	// -1: wait for the first terminated child process
	// WHNOHANG: do not blocked when there are child processes which are in running state
	// use a loop 
	while((pid = waitpid(-1, &stat, WNOHANG)) > 0)
	{
		cout << "child " << pid << " terminated" << endl;
	}
	return;
}

struct addrinfo* host_serv(const char* host, const char* serv, int family, int socktype)
{
    int n;
    struct addrinfo hints, *res;

	memset(&hints, 0, sizeof(hints));
	hints.ai_flags = AI_CANONNAME;
	hints.ai_family = family;
	hints.ai_socktype = socktype;

	if((n == getaddrinfo(host, serv, &hints, &res)) != 0)
	{
		return NULL;
	}
	return res;
}

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