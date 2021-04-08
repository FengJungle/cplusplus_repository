#include <sys/msg.h>
#include <sys/ipc.h>
#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>

#define BUF_SZ 4096

struct msg
{
    long msg_types;
    char msg_buf[511];
};


int main(int argc, char* argv[])
{
    long int qid;
    int len;
    struct msg pmsg;
    if(argc != 2)
    {
        perror("USAGE: read_msg <queue ID>");
        exit(1);
    }
    
    // get msg queue id
    qid = atoi(argv[1]);

    // read msg from msg_queue
    len = msgrcv(qid, &pmsg, BUF_SZ, 0, 0);
    if(len > 0)
    {
        pmsg.msg_buf[len] = '\0';
        printf("reading queue id: %5ld\n", qid);

        printf("message type: %5ld\n", pmsg.msg_types);
        printf("message length: %d bytes\n", len);
        printf("message text:%s\n", pmsg.msg_buf);
    }
    else if(len == 0)
    {
        printf("have no message from queue %ld\n", qid);
    }
    else
    {
        perror("msgrcv");
        exit(1);
    }
    system("ipcs -q");

    // remove msg queue
    if(msgctl(qid, IPC_RMID, NULL) < 0)
    {
        perror("msgctl");
        exit(1);
    }
    exit(0);
}