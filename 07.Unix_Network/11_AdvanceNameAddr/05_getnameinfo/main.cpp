#include <netdb.h>
#include <netinet/in.h>
#include <string.h>

#include <iostream>
using namespace std;

int main(int argc, char *argv[])
{
    struct addrinfo hints;
    struct addrinfo *res;
    struct addrinfo *ressave;
    int n;
    int sockfd;

    char hostBuf[256];
    char servBuf[128];
    memset(hostBuf, 0, sizeof(hostBuf));
    memset(servBuf, 0, sizeof(servBuf));

    memset(&hints, 0, sizeof(hints));
    hints.ai_family = AF_UNSPEC;
    hints.ai_flags = AI_CANONNAME;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_protocol = IPPROTO_TCP;

    n = getaddrinfo("www.baidu.com", "80", &hints, &res);
    if (n != 0)
    {
        cout << "getaddrinfo failed with error: " << gai_strerror(n) << endl;
        return -1;
    }

    ressave = res;

    do
    {
        // getnameinfo
        n = getnameinfo(
            res->ai_addr,
            res->ai_addrlen,
            hostBuf,
            sizeof(hostBuf),
            servBuf,
            sizeof(servBuf),
            NI_NOFQDN);

        cout << hostBuf << "\t" << servBuf << endl;
    } while ((res = res->ai_next) != NULL);

    freeaddrinfo(ressave);

    return 0;
}