#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdlib.h>
#include <stdio.h>
#define BUF_SZ 4096

int main(int argc, char* argv[])
{
    int shm_id;
    shm_id = shmget(IPC_PRIVATE, BUF_SZ, 0666);
    if(shm_id < 0)
    {
        perror("shmget");
        exit(1);
    }
    printf("successfully created segment %d\n", shm_id);

    // 
    system("ipcs -m");
    exit(0);
}