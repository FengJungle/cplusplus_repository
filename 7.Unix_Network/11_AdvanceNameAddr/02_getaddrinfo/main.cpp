/*

int getaddrinfo(
    const char* hostname,     // host name of a string of address (IPv4 or IPv6)
    const char* service,      // service name or string of port number
    const struct addrinfo* hints, // NULL or pointer to addrinfo struct
                                  // caller can set the hints ai_flags, ai_family, ai_socktype, ai_protocol
    struct addrinfo** result       // return a pointer to a list of addrinfo struct
);

*/

/*

// Structure to contain information about address of a service provider.  
struct addrinfo
{
  int ai_flags;			    // Input flags.  
  int ai_family;		    // Protocol family for socket. 
  int ai_socktype;		    // Socket type.  
  int ai_protocol;		    // Protocol for socket.  
  socklen_t ai_addrlen;		// Length of socket address.  
  struct sockaddr *ai_addr;	// Socket address for socket.  
  char *ai_canonname;		// Canonical name for service location. 
  struct addrinfo *ai_next;	// Pointer to next in list.  
};

*/
#include <iostream>
using namespace std;

#include <netdb.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <string.h>

void printAddressInfo(const struct addrinfo *addr)
{
    char str[INET6_ADDRSTRLEN]; // 46
    short port;

    cout << "family:";
    switch (addr->ai_family)
    {
    case AF_INET:
    {
        cout << "IPv4\n";
        struct sockaddr_in *in;
        in = (struct sockaddr_in *)(addr->ai_addr);
        port = ntohs(in->sin_port);
        inet_ntop(AF_INET, &in->sin_addr, str, sizeof(str));
        break;
    }
    case AF_INET6:
    {
        cout << "IPv6\n";
        struct sockaddr_in6 *in6;
        in6 = (struct sockaddr_in6 *)(addr->ai_addr);
        port = ntohs(in6->sin6_port);
        inet_ntop(AF_INET6, &in6->sin6_addr, str, sizeof(str));
        break;
    }
    default:
        cout << "Unknown\n";
        break;
    }

    cout << "ai_socktype:";
    switch (addr->ai_socktype)
    {
    case SOCK_STREAM:
        cout << "stream\n";
        break;
    case SOCK_DGRAM:
        cout << "dgram\n";
        break;
    case SOCK_RAW:
        cout << "raw" << endl;
        break;
    defaul:
        cout << "others" << endl;
        break;
    }

    cout << "ptotocal:";
    switch (addr->ai_protocol)
    {
    case IPPROTO_TCP:
        cout << "tcp" << endl;
        break;
    case IPPROTO_UDP:
        cout << "udp" << endl;
        break;
    case IPPROTO_SCTP:
        cout << "sctp" << endl;
        break;
    default:
        cout << "others" << endl;
        break;
    }

    cout << "address:" << str << endl;
    cout<<"port:"<<port<<endl;
    cout << "canonical name: " << addr->ai_canonname << endl;
    cout << endl;
}

int main(int argc, char *argv[])
{
    int n;
    struct addrinfo* res;
    struct addrinfo* ressave;
    struct addrinfo hint;
    char* serv;

    if(argc < 2)
    {
        cout << "Usage:./getaddrinfo hostname [service name of port name]\n";
    }

    if(argc == 2)
    {
        serv = NULL;
    }
    else{
        serv = argv[2];
    }

    memset(&hint, 0, sizeof(addrinfo));
    hint.ai_family = AF_UNSPEC;

    // error occurred!
    if ((n = getaddrinfo(argv[1], serv, &hint, &res)) != 0)
    {
        if (argc > 2)
        {
            cout << "Cannot get information for " << argv[1] << ":" << serv;
            cout << " error: " << gai_strerror(n) << endl;
        }
        else
        {
            cout << "Cannot get information for " << argv[1];
            cout << " error: " << gai_strerror(n) << endl;
        }
    }
    ressave = res;
    while (res != NULL)
    {
        printAddressInfo(res);
        res = res->ai_next;
    }

    freeaddrinfo(ressave);

    return 0;
}