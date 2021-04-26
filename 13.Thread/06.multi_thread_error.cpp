#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#include <pthread.h>

#define MAX 50

// 全局共享资源
int money = 0;

void *thread_func_A(void *args)
{
    for (int i = 0; i < MAX; i++)
    {
        int cur = money;
        usleep(20);
        cur++;
        money = cur;
        printf("线程A, money = %d\n", money);
    }
    return NULL;
}
void *thread_func_B(void *args)
{
    for (int i = 0; i < MAX; i++)
    {
        int cur = money;
        usleep(10);
        cur++;
        money = cur;
        printf("线程B, money = %d\n", money);
    }
    return NULL;
}
int main(int argc, char* argv[])
{
    pthread_t tid_A, tid_B;
    pthread_create(&tid_A, NULL, thread_func_A, NULL);
    pthread_create(&tid_B, NULL, thread_func_B, NULL);

    pthread_join(tid_A,NULL);
    pthread_join(tid_B,NULL);

    return 0;
}