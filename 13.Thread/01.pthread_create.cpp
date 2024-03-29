#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <pthread.h>

/*

// 注意加上选项 -lpthread

Compile: g++ 01.pthread_create.cpp -lpthread -o app

*/

void* callback(void* arg)
{
    for(int i = 0;i<5;++i)
    {
        printf("子线程:i = %d\n", i);
    }
    printf("子线程 %ld\n", pthread_self());

    return NULL;
}

int main(int argc, char* argv[])
{
    pthread_t tid;
    pthread_create(&tid, NULL, callback, NULL);
    // 1. 主线程主动sleep，让出时间片
    sleep(1); 
    printf("主线程: %ld\n", pthread_self());

    return 0;
}
