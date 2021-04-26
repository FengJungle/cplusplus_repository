#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <pthread.h>

struct Test
{
    int num;
    int age;
};

struct Test t
{
    .num = 99,
    .age = 10, 
};

void* callback(void* arg)
{
    printf("子线程: %ld\n", pthread_self());

    // struct Test t;
    // t.age = 10;
    // t.num = 99;

    // 通过pthread_exit传回子线程的返回参数
    pthread_exit(&t);

    return NULL;
}

int main(int argc, char* argv[])
{
    pthread_t tid;
    pthread_create(&tid, NULL, callback, NULL);

    printf("主线程: %ld\n", pthread_self());

    void *ptr;
    pthread_join(tid, &ptr);

    struct Test* t = (struct Test*)ptr;
    printf("t.age = %d, t.num = %d\n", t->age, t->num);

    return 0;
}
