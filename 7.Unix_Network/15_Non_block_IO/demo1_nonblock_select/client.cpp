#include "unp.h"
#include <sys/time.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <errno.h>

#include <iostream>
using namespace std;

#define SERV_PORT 9875

char* gf_time()
{
    struct timeval tv;
    static char str[30];
    char* ptr;

    if(gettimeofday(&tv, NULL)<0)
    {
        cout<<"gettimeofday error"<<endl;
    }
    ptr = ctime(&tv.tv_sec);
    strcpy(str, &ptr[11]);

    snprintf(str+8, sizeof(str)-8, ".%06ld", tv.tv_usec);
    return str;    
}


void str_cli(FILE *fp, int sockfd)
{
    int maxfdp1;
    int val;
    int stdineof;
    ssize_t n;
    ssize_t nwritten;

    fd_set rset;
    fd_set wset;

    char to[MAXLINE];
    char fr[MAXLINE];
    char *toiptr;
    char *tooptr;
    char *friptr;
    char *froptr;

    // fcntl: set sockfd, STDIN, STDOUT to non-block


    /* Values for the second argument to `fcntl'.  
        F_DUPFD		0	 Duplicate file descriptor.  
        F_GETFD		1	 Get file descriptor flags.  
        F_SETFD		2	 Set file descriptor flags.  
        F_GETFL		3	 Get file status flags.  
        F_SETFL		4	 Set file status flags.  
    */
   
    val = fcntl(sockfd, F_GETFL, 0);
    fcntl(sockfd, F_SETFL, val | O_NONBLOCK);
    val = fcntl(STDIN_FILENO, F_SETFL, 0);
    fcntl(STDIN_FILENO, F_GETFL, val | O_NONBLOCK);
    val = fcntl(STDOUT_FILENO, F_GETFL, 0);
    fcntl(STDOUT_FILENO, F_SETFL, val | O_NONBLOCK);

    // initial buffer pointers
    toiptr = tooptr = to;
    friptr = froptr = fr;
    stdineof = 0;

    maxfdp1 = max(max(STDIN_FILENO, STDOUT_FILENO), sockfd) + 1;

    for (;;)
    {
        FD_ZERO(&rset);
        FD_ZERO(&wset);
        if (stdineof == 0 && toiptr < &to[MAXLINE])
        {
            FD_SET(STDIN_FILENO, &rset);
        }
        if (friptr < &fr[MAXLINE])
        {
            FD_SET(sockfd, &rset);
        }
        if (tooptr != toiptr)
        {
            FD_SET(sockfd, &wset);
        }
        if (froptr != friptr)
        {
            FD_SET(STDOUT_FILENO, &wset);
        }

        select(maxfdp1, &rset, &wset, NULL, NULL);

        if (FD_ISSET(STDIN_FILENO, &rset))
        {
            if ((n = read(STDIN_FILENO, toiptr, &to[MAXLINE] - toiptr)) < 0)
            {
                if (errno != EWOULDBLOCK)
                {
                    cout << "read error on stdin" << endl;
                }
            }
            else if (n == 0)
            {
                // read return 0, terminate stdin
                fprintf(stderr, "%s: EOF on stdin\n", gf_time());
                stdineof = 1;
                // there is no data to be sent
                if (tooptr == toiptr)
                {
                    // send FIN to server
                    shutdown(sockfd, SHUT_WR);
                }
            }
            else
            {
                // read data, update toiptr
                fprintf(stderr, "%s: read %d bytes from stdin\n", gf_time(), n);
                toiptr += n;
                FD_SET(sockfd, &wset);
            }
        }
        if (FD_ISSET(sockfd, &rset))
        {
            if ((n = read(sockfd, friptr, &fr[MAXLINE] - friptr)) < 0)
            {
                if (errno != EWOULDBLOCK)
                {
                    cout << "read error on socket" << endl;
                }
            }
            else if (n == 0)
            {
                fprintf(stderr, "%s: EOF on socket\n", gf_time());
                if (stdineof)
                {
                    // normal terminatin
                    return;
                }
                else
                {
                    cout << "server terminated prematually" << endl;
                    return;
                }
            }
            else
            {
                fprintf(stderr, "%s:read %d bytes from socket\n");
                friptr += n;
                FD_SET(STDOUT_FILENO, &wset);
            }
        }

        if (FD_ISSET(STDOUT_FILENO, &wset) && ((n = friptr - froptr) > 0))
        {
            if ((nwritten = write(STDOUT_FILENO, froptr, n)) < 0)
            {
                if (errno != EWOULDBLOCK)
                {
                    cout << "write error to stdout" << endl;
                }
            }
            else
            {
                fprintf(stderr, "%s:write %d bytes to stdout\n", gf_time(), nwritten);
                froptr += nwritten;
                if (froptr == friptr)
                {
                    froptr = friptr = fr;
                }
            }
        }

        if (FD_ISSET(sockfd, &wset) && ((n = toiptr - tooptr) > 0))
        {
            if ((nwritten = write(sockfd, tooptr, n))<0)
                {
                    if (errno != EWOULDBLOCK)
                    {
                        cout << "write error to socket" << endl;
                    }
                }
            else
            {
                fprintf(stderr, "%s:wrote %d bytes to socket\n", gf_time, nwritten);
                tooptr += nwritten;
                if (tooptr == toiptr)
                {
                    tooptr = toiptr = to;
                    if (stdineof)
                    {
                        shutdown(sockfd, SHUT_WR);
                    }
                }
            }
        }
    }
}

int main(int argc, char *argv[])
{
    int sockfd;
    struct sockaddr_in servaddr;

    if (argc != 2)
    {
        cout << "usage: tcpcli<IPaddress>" << endl;
        return -1;
    }
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    memset(&servaddr, 0, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(SERV_PORT);
    inet_pton(AF_INET, argv[1], &servaddr.sin_addr);
    connect(sockfd, (sockaddr *)&servaddr, sizeof(servaddr));
    str_cli(stdin, sockfd);

    /*
    *  (1). client close socket, will send a FIN to server, and client is entering FIN-WAIT-1 state
    *  (2). server tcp will send back a ACK, then client tcp goes into FIN-WAIT-2 state
    *  (3). when client tcp receive a FIN from server tcp, it goes into TIME-WAIT state
    */
    close(sockfd);
    exit(0);
}