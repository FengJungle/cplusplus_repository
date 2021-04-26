#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <pthread.h>

void* callback(void* arg)
{
    printf("子线程: %ld\n", pthread_self());

    return NULL;
}

int main(int argc, char* argv[])
{
    pthread_t tid;
    pthread_create(&tid, NULL, callback, NULL);

    printf("主线程: %ld\n", pthread_self());

    // 线程分离
    pthread_detach(tid);

    pthread_exit(NULL);

    return 0;
}
