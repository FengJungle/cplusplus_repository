#include "string.h"
#include <stdlib.h>

#include <iostream>
using namespace std;

#include "errno.h"
#include <netinet/in.h>
#include <unistd.h>

#include <sys/wait.h>
#include <signal.h>
typedef void SigFunc(int);
SigFunc* Signal(int signo, SigFunc* func)
{
    struct sigaction act,oldact;
    act.sa_handler = func;
    sigemptyset(&act.sa_mask);
    act.sa_flags = 0;

	if (signo == SIGALRM)
	{
#ifdef SA_INTERRUPT
		act.sa_flags |= SA_INTERRUPT;
#endif
	}
	else
	{
#ifdef SA_RESTART
		act.sa_flags |= SA_RESTART;
#endif
	}

    // sigaction: the interface to process signal
	// return 0 - success;  -1 - error 
	if (sigaction(signo, &act, &oldact) < 0)
	{
		return SIG_ERR;
	}
	return oldact.sa_handler;
}

void sig_chld(int signo)
{
    pid_t pid;
    int stat;

    while ((pid = waitpid(-1, &stat, WNOHANG)) > 0)
    {
        cout << "child process " << pid << " terminate!" << endl;
    }
    return;
}


#define SERV_PORT 9942

void process_time(int connect_socket)
{
    char recv_buf[64] = {0};
    char send_buf[64] = {0};
    ssize_t ret = 0;
    while(1)
    {
        // read tcp
        ret = read(connect_socket, recv_buf, 64);
        // 1. error happend
        if(ret < 0)
        {
            cout << "read failed with errno: " << errno << endl;
            continue;
        }
        // 2. read EOF, close socket
        if(ret == 0)
        {
            cout << "read EOF,return" << endl;
            return;
        }

        // parse read_buf and calculate
        cout << "Client: " << recv_buf;
        if(memcmp(recv_buf, "time", strlen("time")) == 0)
        {
            memset(recv_buf, 0, 64);
            memset(send_buf, 0, 64);

            // struct tm time_ptr = {0};
            time_t time_ptr;
            time(&time_ptr);
            char* ptr = NULL;
            ptr = asctime(gmtime(&time_ptr));
            memcpy(send_buf, ptr, 64);
            ret = write(connect_socket, send_buf, 64);
            if(ret < 0)
            {
                cout << "write failed with errno: " << errno << endl;
                continue;
            }
        }        
    }
}


int main(int argc, char* argv[])
{
    int listen_socket;
    int connect_socket;
    pid_t childpid;
    socklen_t client_socket_len;
    struct sockaddr_in client_addr, server_addr;

    // listen_socket
    listen_socket = socket(AF_INET, SOCK_STREAM, 0);

    memset(&server_addr, 0,sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    server_addr.sin_port = htons(SERV_PORT);

    // bind
    if(0 != bind(listen_socket, (sockaddr*)&server_addr, sizeof(server_addr)))
    {
        cout << "bind failed with errno: " << errno << endl;
        return -1;
    }

    // listen
    if(-1 == listen(listen_socket, 5))
    {
        cout << "listen failed with errno: " << errno << endl;
    }

    Signal(SIGCHLD,sig_chld);

    while(1)
    {
        connect_socket = accept(listen_socket, (sockaddr *)&client_addr, &client_socket_len);

        // if accept failed, return -1
        if (-1 == connect_socket)
        {
            if (errno == EINTR)
            {
                continue;
            }
            else
            {
                cout << "accept failed with errno: " << errno << endl;
            }
        }

        // fork return = 0: return to new-created child process
        //             > 0: return to caller process or parent process
        //             < 0: failed to create child process
        if((childpid = fork())==0)
        {
            // child process close listen socket
            close(listen_socket);

            // child process processes new tcp request
            process_time(connect_socket);

            /* terminate child process by calling exit(0)
            *
            *  (1). the connect_socket will be closed, which leads to send FIN to client, 
            *  (2). and server will receive a ACK from client.
            *  (3). thus, the connection is totally terminated.
            *  (4). child process will send a SIGCHLD to parent process.
            *
            */
            exit(0);
        }
        close(connect_socket);
    }


    return 0;
}