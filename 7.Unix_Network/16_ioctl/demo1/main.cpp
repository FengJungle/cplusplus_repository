#include "common/unpifi.h"

#include <string.h>
#include <iostream>
using namespace std;

int main(int argc, char *argv[])
{
    struct ifi_info *ifi;
    struct ifi_info *ifihead;

    struct sockaddr *sa;
    u_char *ptr;
    int i;
    int family;
    int doaliases;

    if (argc != 3)
    {
        cout << "usage: prifinfo <inet4|inet6> <doaliases>" << endl;
        return -1;
    }

    if (strcmp(argv[1], "inet4") == 0)
    {
        family = AF_INET;
    }
#ifdef IPV6
    else if (strcmp(argv[1], "inet6") == 0)
    {
        family = AF_INET6;
    }
#endif
    else
    {
        cout << "invalid <address-family>" << endl;
    }

    doaliases = atoi(argv[2]);

    for (ifihead = ifi = get_ifi_info(family, doaliases); ifi != NULL; ifi = ifi->ifi_next)
    {
        printf("%s: <", ifi->ifi_name);
        if (ifi->ifi_flags & IFF_UP)
            printf("UP ");
        if (ifi->ifi_flags & IFF_BROADCAST)
            printf("BCAST ");
        if (ifi->ifi_flags & IFF_MULTICAST)
            printf("MCAST ");
        if (ifi->ifi_flags & IFF_LOOPBACK)
            printf("LOOP ");
        if (ifi->ifi_flags & IFF_POINTOPOINT)
            printf("P2P ");
        printf(">\n");

        if ((i = ifi->ifi_hlen) > 0)
        {
            ptr = ifi->ifi_haddr;
            do
            {
                printf("%s%x", (i == ifi->ifi_hlen) ? " " : ":", *ptr++);
            } while (--i > 0);
            printf("\n");
        }
        if ((sa = ifi->ifi_addr) != NULL)
        {
            printf(" IP addr: %s\n", sock_ntop_host(sa, sizeof(*sa)));
        }
        if ((sa = ifi->ifi_brdaddr) != NULL)
        {
            printf(" broadcast addr: %s\n", sock_ntop_host(sa, sizeof(*sa)));
        }
        if ((sa = ifi->ifi_dstaddr) != NULL)
        {
            printf(" destination addr: %s\n", sock_ntop_host(sa, sizeof(*sa)));
        }
    }
    free_ifi_info(ifihead);
    exit(0);
}