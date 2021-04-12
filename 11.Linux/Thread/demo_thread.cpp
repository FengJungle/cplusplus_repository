#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

void* func1(void* para)
{
    printf("enter func1\n");

    pid_t pid = getpid();
    printf("%4d: pid = %d\n", __LINE__, pid);

    pthread_t tid = pthread_self();
    printf("%4d: tid = %d\n", __LINE__, tid);

    int para1 = *((int*)(para));
    printf("para = %d\n", para1);

    // exit a thread
    int ret = 16;
    pthread_exit(&ret);

    printf("exit func1\n"); // will not run here
    return nullptr;
}

int main(int argc, char* argv[])
{
    pthread_t tid;
    pthread_t mtid;
    pid_t pid;
    
    pid = getpid();

    int err1 = pthread_create(&mtid, nullptr, func1, &argc);

    int *ret1 = new int();

    printf("err1 = %d\n", err1);
    printf("%4d:pid = %d\n", __LINE__, pid);
    printf("%4d:tid = %d\n", __LINE__, mtid);
    pthread_join(mtid, (void**)&ret1);

    printf("ret1 = %d\n", *ret1);


    return 0;
}