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

#include <netdb.h>
// getaddrinfo
struct addrinfo* host_serv(const char* host, const char* serv, int family, int socktype);


int tcp_connect(const char* host, const char* serv);
int tcp_listen(const char* host, const char* serv, socklen_t* addrlenp);

int udp_client(const char* host, const char* serv, void** saptr, socklen_t* lenp);
int udp_connect(const char* host, const char* serv);
int udp_server(const char* host, const char* serv, socklen_t* addrlenp);

#define UNIXSTR_PATH "/tmp/unix.str"
