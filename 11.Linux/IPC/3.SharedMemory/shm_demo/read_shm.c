#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <unistd.h>

int main(int argc, char* atgv[])
{
    int shm_id = 65594;
    char* readBuf;

    if((readBuf = shmat(shm_id, 0, 0)) < 0)
    {
        perror("shmat");
        exit(1);
    }
    printf("attached shm successfully!\n");

    char data[10] = {0};
    for(int i = 0; i<5; i++)
    {
        printf("0x%x\t", readBuf[i]);
    }
    printf("\n read shm successfully!\n");

    if(shmdt(readBuf) < 0)
    {
        perror("shmdt");
        exit(1);
    }
    printf("detached shm successfully!\n");

    exit(0);
}