#include <netinet/tcp.h>
#include <arpa/inet.h>

#include <iostream>
using namespace std;

#include <stdio.h>
#include <stdlib.h>

#include <unistd.h>

// Union: the possible returned value by getsocketopt()
union val
{
    int i_val;
    long l_val;
    char c_val[10];
    struct linger linger_val;
    struct timeval timeval_val;
} val;

static char ret_str[128];
// the following 4 functions are used to output returned value according to val type
static char *sock_str_flag(union val *ptr, int len)
{
    if (len != sizeof(int))
    {
        snprintf(ret_str, sizeof(ret_str), "size (%d) not sizeof(int)", len);
    }
    else
    {
        snprintf(ret_str, sizeof(ret_str), "%s", (ptr->l_val == 0) ? "off" : "on");
    }
    return ret_str;
}
static char *sock_str_int(union val *ptr, int len)
{
    if (len != sizeof(int))
    {
        snprintf(ret_str, sizeof(ret_str), "size (%d) not sizeof(int)", len);
    }
    else
    {
        snprintf(ret_str, sizeof(ret_str), "%s", (ptr->i_val == 0) ? "off" : "on");
    }
    return ret_str;
}
static char *sock_str_linger(union val *ptr, int len)
{
    if (len != sizeof(int))
    {
        snprintf(ret_str, sizeof(ret_str), "size (%d) not sizeof(int)", len);
    }
    else
    {
        snprintf(ret_str, sizeof(ret_str), "%s", (ptr->linger_val.l_onoff == 0) ? "off" : "on");
    }
    return ret_str;
}
static char *sock_str_timeval(union val *ptr, int len)
{
    if (len != sizeof(int))
    {
        snprintf(ret_str, sizeof(ret_str), "size (%d) not sizeof(int)", len);
    }
    else
    {
        // snprintf(ret_str, sizeof(ret_str), "%s", (ptr->time_val. == 0) ? "off" : "on");
    }
    return ret_str;
}

struct sock_opts
{
    char *opt_str;
    int opt_level;
    int opt_name;
    char *(*opt_val_str)(union val *, int);
} sock_opts[] =
    {
        "SO_BROADCAST", SOL_SOCKET, SO_BROADCAST, sock_str_flag,
        "SO_DEBUG",     SOL_SOCKET, SO_DEBUG,     sock_str_flag,
        "SO_DONTROUTE", SOL_SOCKET, SO_DONTROUTE, sock_str_flag,
        "SO_ERROR",     SOL_SOCKET, SO_ERROR,     sock_str_int,
        "SO_KEEPALIVE", SOL_SOCKET, SO_KEEPALIVE, sock_str_flag,
        "SO_LINGER",    SOL_SOCKET, SO_LINGER,    sock_str_linger,
        "SO_OOBINLINE", SOL_SOCKET, SO_OOBINLINE, sock_str_flag,
        "SO_RCVBUF",    SOL_SOCKET, SO_RCVBUF,    sock_str_int,
        "SO_SNDBUF",    SOL_SOCKET, SO_SNDBUF,    sock_str_int,
        "SO_RCVLOWAT",  SOL_SOCKET, SO_RCVLOWAT,  sock_str_int,
        "SO_SNDLOWAT",  SOL_SOCKET, SO_SNDLOWAT,  sock_str_int,
        "SO_RCVTIMEO",  SOL_SOCKET, SO_RCVTIMEO,  sock_str_timeval,
        "SO_SNDTIMEO",  SOL_SOCKET, SO_SNDTIMEO,  sock_str_timeval,
        "SO_REUSEADDR", SOL_SOCKET, SO_REUSEADDR, sock_str_flag,
#ifdef SO_REUSEPORT
        "SO_REUSEPORT", SOL_SOCKET, SO_REUSEPORT, sock_str_flag,
#else
        "SO_REUSEPORT", 0, 0, NULL,
#endif
        "SO_TYPE",      SOL_SOCKET, SO_TYPE,      sock_str_int,
        // "SO_USELOOPBACK", SOL_SOCKET, SO_USELOOPBACK, sock_str_flag,
        "IP_TOS",       IPPROTO_IP, IP_TOS,       sock_str_int,
        "IP_TTL",       IPPROTO_IP, IP_TTL,       sock_str_int,
        "TCP_MAXSEG",   IPPROTO_TCP, TCP_MAXSEG,  sock_str_int,
        "TCP_NODELAY",  IPPROTO_TCP, TCP_NODELAY, sock_str_flag,
        NULL,           0,           0,           NULL
    };

int main(int argc, char *argv[])
{
    int fd, len;
    struct sock_opts *ptr;

    fd = socket(AF_INET, SOCK_STREAM, 0);
    for (ptr = sock_opts; ptr->opt_str != NULL; ptr++)
    {
        cout << ptr->opt_str;
        if (ptr->opt_val_str == NULL)
        {
            cout << " undefined" << endl;
        }
        else
        {
            len = sizeof(val);
            if (-1 == getsockopt(fd, ptr->opt_level, ptr->opt_name, &val, (socklen_t *)&len))
            {
                cout << "getsockopt error" << endl;
                continue;
            }
            else
            {
                cout << " default = " << ptr->opt_val_str(&val, len) << endl;
            }
        }
    }
    exit(0);
}