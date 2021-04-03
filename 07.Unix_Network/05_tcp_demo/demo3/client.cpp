#include <iostream>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
using namespace std;

#include <netinet/in.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <errno.h>

#define SERV_PORT 9942


int main(int argc, char* argv[])
{
    int con_socket;
    struct sockaddr_in server_addr;
    int ret = 0;

    con_socket = socket(AF_INET, SOCK_STREAM, 0);
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(SERV_PORT);
    inet_pton(AF_INET, "127.0.0.1", &server_addr.sin_addr);
    connect(con_socket, (sockaddr*)&server_addr, sizeof(server_addr));
    while (1)
    {
        char send_buf[64] = {0};
        char recv_buf[64] = {0};
        ssize_t ret = 0;
        while (fgets(send_buf, 64, stdin) != NULL)
        {
            if (memcmp(send_buf, "time", strlen("time")) == 0)
            {
                ret = write(con_socket, send_buf, 64);
                if (ret < 0)
                {
                    cout << "write failed with errno: " << errno << endl;
                    continue;
                }
                cout << "Client: " << send_buf;
                ret = read(con_socket, recv_buf, 64);
                // 1. error happend
                if (ret < 0)
                {
                    cout << "read failed with errno: " << errno << endl;
                    continue;
                }
                // 2. read EOF, close socket
                if (ret == 0)
                {
                    cout << "read EOF,return" << endl;
                    return -1;
                }

                cout<<"Server: "<<recv_buf;
            }
            memset(send_buf, 0, 64);
        }
    }
    close(con_socket);
    exit(0);
}