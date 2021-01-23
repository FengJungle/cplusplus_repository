#ifndef _UNP_IFI_H_
#define _UNP_IFI_H_

#include "unp.h"
#include <net/if.h>

// same as IFNAMSIZ in <net/if.h>
#define IFI_NAME 16

// allow for 64-bit EUI-64 in future
#define IFI_HADDR 8

struct ifi_info
{
    // interface name, null ternimated
    char ifi_name[IFI_NAME];
    // hardware address
    u_char ifi_haddr[IFI_HADDR];
    // bytes in hardware address: 0,6,8
    u_short ifi_hlen;
    // IFF_xxx constants from <net/if.h>
    short ifi_flags;
    // our own IFI_xxx flags;
    short ifi_myflags;
    // primary address
    struct sockaddr* ifi_addr;
    // broadcast address
    struct sockaddr* ifi_brdaddr;
    // destination address
    struct sockaddr* ifi_dstaddr;
    // next of these structures
    struct ifi_info* ifi_next;
};

// ifi_addr is an alias
#define IFI_ALIAS 1

struct ifi_info* get_ifi_info(int ,int);
struct ifi_info *Get_ifi_info(int, int);
void free_ifi_info(struct ifi_info*);

#endif