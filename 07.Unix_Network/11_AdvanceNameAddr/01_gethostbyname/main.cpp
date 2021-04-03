
#include <iostream>
using namespace std;

#include <netdb.h>
#include <arpa/inet.h>


int main(int argc, char *argv[])
{
    char *ptr;
    char **pptr;
    struct hostent *hptr;
    char str[INET_ADDRSTRLEN]; // 16

    while (--argc > 0)
    {
        ptr = *++argv;
        if ((hptr = gethostbyname(ptr)) == NULL)
        {
            cout << "gethostbyname failed with error: " << hstrerror(h_errno) << endl;
            continue;
        }
        cout << "official hostname: " << hptr->h_name << endl;

        for (pptr = hptr->h_aliases; *pptr != NULL; ++pptr)
        {
            cout << "\talials: " << *pptr << endl;
        }

        switch (hptr->h_addrtype)
        {
        case AF_INET:
            pptr = hptr->h_addr_list;
            for (; *pptr != NULL; ++pptr)
            {
                cout << "address : " << inet_ntop(hptr->h_addrtype, *pptr, str, sizeof(str)) << endl;
            }
            break;
        default:
            cout << "unknown address type" << endl;
            break;
        }
    }
    return 0;
}