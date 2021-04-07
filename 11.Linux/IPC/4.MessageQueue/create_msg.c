#include <sys/msg.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[])
{
    int qid;

    // typedef __key_t key_t;
    key_t key;
    key = 113;

    // create a msg queue with mode 0666 (read and write)
    qid = msgget(key, IPC_CREAT | 0666);
    if(qid < 0)
    {
        perror("msgget");
        exit(1);
    }
    printf("created queue id: %d\n", qid);

    // -q: check the status of msg queue
    system("ipcs -q");

    // delete msg queue and clear all msg
    if(msgctl(qid, IPC_RMID, NULL) < 0)
    {
        perror("msgctl");
        exit(1);
    }
    system("ipcs -q");

    exit(0);
}
