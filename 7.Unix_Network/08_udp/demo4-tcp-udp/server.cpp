#include <netinet/in.h>
#include <unistd.h>

#include <string.h>
#include <stdlib.h>
#include <errno.h>

#include <iostream>
using namespace std;

#define SERV_PORT 7678
#define SERV_PORT_2 7679
#define MAXLINE 256

/*
* This demo simply realize a udp server.
* It offers a iterative server, not like concurrent server in TCP,
* there is no fork. A singer server process handles all clients.
*
* In fact, there is a FIFO for udp socket recv buffer.
*/

void dg_echo(int sockfd, sockaddr *pcliaddr, socklen_t clilen)
{
    int n;
    socklen_t len;
    char msg[MAXLINE];

    while (1)
    {
        len = clilen;
        n = recvfrom(sockfd, msg, MAXLINE, 0, pcliaddr, &len);
        sendto(sockfd, msg, n, 0, pcliaddr, len);
    }
}

void str_echo(int sockfd)
{
    ssize_t n;
    char line[MAXLINE];
    for (;;)
    {
        // it will be blocked by read
        // when server receive a FIN, read return 0
        if ((n = read(sockfd, line, MAXLINE)) == 0)
        {
            cout << "n = 0!!!" << endl;
            return;
        }
        cout << "receive from tcp client: " << line << endl;
        n = write(sockfd, line, sizeof(line));
        memset(line, 0, MAXLINE);
    }
}

#include <signal.h>
typedef void Sigfunc(int);

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
* version 2: a while loop, use waitpid
*/
void sig_chld(int signo)
{
    pid_t pid;
    int stat;

    // -1: wait for the first terminated child process
    // WHNOHANG: do not blocked when there are child processes which are in running state
    // use a loop
    while ((pid = waitpid(-1, &stat, WNOHANG)) > 0)
    {
        cout << "child " << pid << " terminated" << endl;
    }
    return;
}

int main(int argc, char *argv[])
{
    int listenfd, connfd, udpfd, nready, maxfdp1;
    char mesg[MAXLINE];
    pid_t childpid;
    fd_set rset;
    ssize_t n;
    socklen_t len;
    const int on = 1;
    struct sockaddr_in servaddr, cliaddr;

    // create listenfd for tcp
    listenfd = socket(AF_INET, SOCK_STREAM, 0);

    memset(&servaddr, 0, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(SERV_PORT);
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);

    setsockopt(listenfd, SOL_SOCKET, SO_REUSEADDR, &on, sizeof(on));
    bind(listenfd, (sockaddr *)&servaddr, sizeof(servaddr));

    listen(listenfd, 5);

    // create udp socket
    udpfd = socket(AF_INET, SOCK_DGRAM, 0);

    memset(&servaddr, 0, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servaddr.sin_port = htons(SERV_PORT_2);

    bind(udpfd, (sockaddr *)&servaddr, sizeof(servaddr));

    Signal(SIGCHLD, sig_chld);

    FD_ZERO(&rset);
    maxfdp1 = max(listenfd, udpfd) + 1;
    while (1)
    {
        FD_SET(listenfd, &rset);
        FD_SET(udpfd, &rset);
        if ((nready = select(maxfdp1, &rset, NULL, NULL, NULL)) < 0)
        {
            if (errno == EINTR)
            {
                continue;
            }
            else
            {
                cout << "select failed with errno: " << errno << endl;
                return -1;
            }
        }
        if (FD_ISSET(listenfd, &rset))
        {
            cout << "tcp connect" << endl;
            len = sizeof(cliaddr);
            connfd = accept(listenfd, (sockaddr *)&cliaddr, &len);
            if ((childpid = fork()) == 0)
            {
                close(listenfd);
                str_echo(connfd);
                exit(0);
            }
            close(connfd);
        }
        if (FD_ISSET(udpfd, &rset))
        {
            cout<<"udp data is coming..."<<endl;
            len = sizeof(cliaddr);
            n = recvfrom(udpfd, mesg, MAXLINE, 0, (sockaddr *)&cliaddr, &len);
            sendto(udpfd, mesg, n, 0, (sockaddr *)&cliaddr, len);
        }
    }
}