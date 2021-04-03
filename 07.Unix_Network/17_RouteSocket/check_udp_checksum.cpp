#include <netinet/udp.h>
#include <sys/sysctl.h>
#include <sys/types.h>
#include <sys/param.h>
#include <arpa/inet.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>

void test_get_release_version()
{
    char *releasename = NULL;
    size_t len;
    int mib[2];
    mib[0] = CTL_KERN;
    mib[1] = KERN_OSRELEASE;

    if (0 != sysctl(mib, 2, NULL, &len, NULL, 0))
    {
        printf("errno is %d\n", errno);
    }
    printf("len = %d\n", len);
    releasename = (char *)malloc(len);
    if (NULL == releasename)
    {
        printf("errno is %d\n", errno);
    }
    if (0 != sysctl(mib, 2, releasename, &len, NULL, 0))
    {
        printf("error is %d\n", errno);
    }
    printf("len = %d\n", len);
    printf("hw_model:%s\n", releasename);
    if (NULL != releasename)
    {
        free(releasename);
        releasename = NULL;
    }
}

/*
    sysctl函数可以读写很多系统参量，诸如文件系统、虚拟内存、网络等信息.
    例如函数的参数设成{CTL_NET, AF_INET, IPPROTO_UDP, UDPCTL_CHECKSUM}就可以读写UDP校验和有关的设置
*/

int  main(int argc, char* argv[])
{
    int mib[4];
    int val;
    size_t len;

    mib[0] = CTL_NET; // sub-system
    mib[1] = AF_INET;
    mib[2] = IPPROTO_UDP;
    mib[3] = UDPCTL_CHECKSUM; // NET_NF_CONNTRACK_CHECKSUM

    len = sizeof(val);
    sysctl(mib, 4, &val, &len, NULL, 0);
    printf("udp checksum flag: %d\n", val);

    test_get_release_version();

    exit(0);
}