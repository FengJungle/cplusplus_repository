#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>

#define MAXLINE 64

char* sock_ntop(const struct sockaddr*, socklen_t addrlen);

ssize_t writen(int fd, const void* vptr, size_t n);
ssize_t readn(int fd, void* vptr, size_t n);
ssize_t readline(int fd, void* vptr, size_t maxlen);

#include <signal.h>
typedef void Sigfunc(int);
Sigfunc* Signal(int signo, Sigfunc* func);

void sig_chld(int signo);


