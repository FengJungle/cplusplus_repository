#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <unistd.h>

int main(int argc, char* argv[])
{
    int shm_id= 65594;
    char* shm_buf;

    if((shm_buf = shmat(shm_id, 0, 0)) < 0)
    {
        perror("shmat");
        exit(1);
    }
    printf("successfully attched shm!\n");

    memset(shm_buf, 0x69, 5*sizeof(0x69));

    if(shmdt(shm_buf) < 0)
    {
        perror("shmdt");
        exit(1);
    }
    printf("detached shm successfully!\n");

    exit(0);
}