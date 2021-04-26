#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#include <pthread.h>

#define MAX 50

// 全局共享资源
int money = 0;

// 互斥锁
pthread_mutex_t mutex;

void *thread_func_A(void *args)
{
    for (int i = 0; i < MAX; i++)
    {
        // 获取锁
        pthread_mutex_lock(&mutex);
        int cur = money;
        //usleep(20);
        cur++;
        money = cur;
        printf("线程A, money = %d\n", money);
        // 释放锁
        pthread_mutex_unlock(&mutex);
    }
    return NULL;
}
void *thread_func_B(void *args)
{
    for (int i = 0; i < MAX; i++)
    {
        // 获取锁
        pthread_mutex_lock(&mutex);
        int cur = money;
       // usleep(10);
        cur++;
        money = cur;
        printf("线程B, money = %d\n", money);
        // 释放锁
        pthread_mutex_unlock(&mutex);
    }
    return NULL;
}
int main(int argc, char* argv[])
{
    // 初始化mutex
    pthread_mutex_init(&mutex, NULL);
    pthread_t tid_A, tid_B;
    pthread_create(&tid_A, NULL, thread_func_A, NULL);
    pthread_create(&tid_B, NULL, thread_func_B, NULL);

    pthread_join(tid_A,NULL);
    pthread_join(tid_B,NULL);

    // 销毁锁
    pthread_mutex_destroy(&mutex);

    return 0;
}