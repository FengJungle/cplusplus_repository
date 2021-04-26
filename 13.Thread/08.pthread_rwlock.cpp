#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include <pthread.h>


/*

8个线程操作同一个全局变量，3个线程不定时写同一个全局资源，5个线程不定时读同一个全局资源

读的线程比较多，写的线程比较少，因此可以使用读写锁

*/

// 全局资源
int num = 0;

// 声明读操作次数和写操作次数
#define WRITE_MAX 20
#define READ_MAX  10

// 读写锁
pthread_rwlock_t rwlock;

// 写操作的线程函数
void* writeNum(void* arg)
{
    for(int i = 0;i<WRITE_MAX;i++)
    {
        pthread_rwlock_wrlock(&rwlock);
        num += 1;
        printf("     num = %d, tid = %ld\n", num, pthread_self());
        pthread_rwlock_unlock(&rwlock);
        usleep(rand()%25);
    }
    return NULL;
}

// 读操作的线程函数
void* readNum(void* args)
{
    for(int i = 0;i<READ_MAX;i++)
    {
        pthread_rwlock_rdlock(&rwlock);
        printf("读操作,  num = %d, tid = %ld\n", num, pthread_self());
        pthread_rwlock_unlock(&rwlock);
        usleep(rand()%10);
    }
    return NULL;
}

int main(int argc, char* argv[])
{
    // 初始化读写锁
    pthread_rwlock_init(&rwlock, NULL);

    pthread_t read_tid[5];
    pthread_t write_tid[3];
    for(int i = 0;i<5;i++)
    {
        pthread_create(&read_tid[i], NULL, readNum, NULL);
    }
    for(int i = 0;i<3;i++)
    {
        pthread_create(&write_tid[i], NULL, writeNum, NULL);
    }

    // 线程回收
    for(int i = 0;i<5;i++)
    {
        pthread_join(read_tid[i], NULL);
    }
    for(int i = 0;i<3;i++)
    {
        pthread_join(write_tid[i], NULL);
    }

    // 销毁读写锁
    pthread_rwlock_destroy(&rwlock);

    return 0;
}