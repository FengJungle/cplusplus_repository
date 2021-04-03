#include "unproute.h"
#include <unistd.h>
#include <arpa/inet.h>
#include <net/route.h>

#define BUFLEN (sizeof(struct rt_msghdr)+512)
#define SEQ 9999

int main(int argc, char* argv[])
{
    int sockfd;
    char* buf;
    pid_t pid'
    ssize_t n;
    struct rt_msghdr* rtm;
    struct sockaddr* sa;
    struct sockaddr* rtl_info[RTAX_MAX];
    struct sockaddr_in* sin;
}