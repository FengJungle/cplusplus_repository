#include <netinet/in.h>
#include <stdlib.h>
#include <string.h>

#include <iostream>
using namespace std;

#define SERV_PORT 7678
#define MAXLINE 256

static int count;
static void recvfrom_int(int)
{
    cout << "received " << count << " datagrams " << endl;
    exit(0);
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


void dg_echo(int sockfd, sockaddr* pcliaddr, socklen_t clilen)
{
    socklen_t len;
    char msg[MAXLINE];

    Signal(SIGINT, recvfrom_int);

    while(1)
    {
        len = clilen;
        recvfrom(sockfd, msg, MAXLINE, 0, pcliaddr, &len);
        count++;
    }
}

int main(int argc, char* argv[])
{
    int sockfd;
    struct sockaddr_in servaddr, cliaddr;

    sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    
    memset(&servaddr, 0, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servaddr.sin_port = htons(SERV_PORT);

    bind(sockfd, (sockaddr*)&servaddr, sizeof(servaddr));

    dg_echo(sockfd, (sockaddr*)&cliaddr, sizeof(cliaddr));

}