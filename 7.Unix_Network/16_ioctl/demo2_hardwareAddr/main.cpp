#include "../common/unp.h"
#include <net/if_arp.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ioctl.h>
#include <netdb.h>
#include <sys/utsname.h>

char** my_addrs(int& addrtype)
{
    /*
        // Description of data base entry for a single host.
        struct hostent
        {
            char *h_name;			// Official name of host.  
            char **h_aliases;		// Alias list.  
            int h_addrtype;		// Host address type.  
            int h_length;			// Length of address.  
            char **h_addr_list;		// List of addresses from name server.  
        #ifdef __USE_MISC
            # define	h_addr	h_addr_list[0] // Address, for backward compatibility.
        #endif
        };
    */
    struct hostent* hptr;

    /*
        //  Structure describing the system and machine. 
        struct utsname
        {
            // Name of the implementation of the operating system. 
            char sysname[_UTSNAME_SYSNAME_LENGTH];
            // Name of this node on the network. 
            char nodename[_UTSNAME_NODENAME_LENGTH];
            // Current release level of this implementation. 
            char release[_UTSNAME_RELEASE_LENGTH];
            // Current version level of this release.  
            char version[_UTSNAME_VERSION_LENGTH];
            // Name of the hardware type the system is running on.
            char machine[_UTSNAME_MACHINE_LENGTH];
            // Name of the domain of this node on the network. 
            char domainname[_UTSNAME_DOMAIN_LENGTH];
        };
    */
    struct utsname myname;
    
    printf("%d: enter\n", __LINE__);
    // uname: get host name
    if(uname(&myname)<0)
    {
        printf("%d: return NULL\n", __LINE__);
        return NULL;
    }
    printf("myname.sysname:%s\n", myname.sysname);
    printf("myname.nodename:%s\n", myname.nodename);
    printf("myname.release:%s\n", myname.release);
    printf("myname.version:%s\n", myname.version);
    printf("myname.machine:%s\n", myname.machine);
    printf("myname.domainname:%s\n", myname.domainname);

    if((hptr = gethostbyname(myname.nodename)) == NULL)
    {
        printf("%d: return NULL\n", __LINE__);
        return NULL;
    }
    printf("host h_name:%s\n",hptr->h_name);
    printf("host h_addrtype:%d\n",hptr->h_addrtype);

    addrtype = hptr->h_addrtype;
    return hptr->h_addr_list;
}

int main(int argc, char* argv[])
{
    int family, sockfd;
    char str[INET6_ADDRSTRLEN];

    char** pptr;
    unsigned char* ptr;

    /* ARP ioctl request.
        struct arpreq
        {
            struct sockaddr arp_pa;		// Protocol address.  
            struct sockaddr arp_ha;		// Hardware address.  
            int arp_flags;			    // Flags.  
            struct sockaddr arp_netmask;	// Netmask (only for proxy arps).
            char arp_dev[16];
        };
    */
    struct arpreq arpreq;
    struct sockaddr_in* sin;
    
    pptr = my_addrs(family);
    printf("hehe");
    while (1)
    {
        printf("%s: ", inet_ntop(family, *pptr, str, sizeof(str)));
        switch (family)
        {
        case AF_INET:
            sockfd = socket(AF_INET, SOCK_DGRAM, 0);
            sin = (struct sockaddr_in *)&arpreq.arp_pa;
            memset(&sin, 0, sizeof(struct sockaddr_in));
            sin->sin_family = AF_INET;
            memcpy(&sin->sin_addr, *pptr, sizeof(struct in_addr));

            /* get ARP table entry		*/
            ioctl(sockfd, SIOCGARP, &arpreq);
            ptr = (unsigned char *)(&arpreq.arp_ha.sa_data[0]);
            printf("%x:%x:%x:%x:%x:%x\n", *ptr, *(ptr + 1), *(ptr + 2),
                   *(ptr + 3), *(ptr + 4), *(ptr + 5));
            break;
        default:
            printf("unsupported address family: %d\n", family);
        }
    }
    exit(0);
}