#include "unpifi.h"
#include <stdlib.h>
#include <sys/ioctl.h>
#include <errno.h>

#include <iostream>
using namespace std;

struct ifi_info *get_ifi_info(int family, int doaliases)
{
    struct ifi_info *ifi;
    struct ifi_info *ifihead;
    struct ifi_info **ifipnext;

    int sockfd;
    int len;
    int lastlen;
    int flags;
    int myflags;
    char *ptr;
    char *buf;
    char lastname[IFNAMSIZ];
    char *cptr;

    struct ifconf ifc;
    struct ifreq *ifr;
    struct ifreq ifrcopy;
    struct sockaddr_in *sinptr;

    // create a socket (UDP)
    sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    lastlen = 0;

    // 100 * sizeof()
    len `--= 100 * sizeof(struct ifreq);
    while (1)
    {
        buf = (char *)malloc(len);
        ifc.ifc_len = len;
        ifc.ifc_ifcu.ifcu_buf = buf;
        if (ioctl(sockfd, SIOCGIFCONF, &ifc) < 0)
        {
            if (errno != EINVAL || lastlen != 0)
            {
                cout << "ioctl error" << endl;
            }
        }
        else
        {
            if (ifc.ifc_len == lastlen)
            {
                // success, len has not changed, that means the buffer is enough
                break;
            }
            // save the length to lastlen
            lastlen = ifc.ifc_len;
        }

        // after each loop, len will be added 10*sizeof(ifreq)
        len += 10 * sizeof(struct ifreq);
        free(buf);
    }
    ifihead = NULL;
    ifipnext = &ifihead;
    lastname[0] = 0;

    for (ptr = buf; ptr < buf + ifc.ifc_len;)
    {
        ifr = (struct ifreq *)ptr;
#ifdef HAVE_SOCKADDR_SA_LEN
        len = max(sizeof(struct sockaddr), ifr->ifr_addr.sa_len);
#else
        switch (ifr->ifr_ifru.ifru_addr.sa_family)
        {
#ifdef IPV6
        case AF_INET6:
            len = sizeof(struct sockaddr_in6);
            break;
#endif
        case AF_INET:
        default:
            len = sizeof(struct sockaddr);
            break;
        }
#endif

        // for next one in buffer
        ptr += sizeof(ifr->ifr_ifrn.ifrn_name) + len;
        
    }
}