#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include <pthread.h>
#include <semaphore.h>

/*

场景：使用条件变量实现生产者和消费者模型，其中
1. 生产者有5个，往链表头部添加节点
2. 消费者有5个，删除链表头部的节点

*/

// 互斥锁
pthread_mutex_t mutex;

// 生产者信号量
sem_t sem_producer;

// 消费者信号量
sem_t sem_consumer;

// 定义链表
typedef struct _Node
{
    int number;
    struct _Node *next;
} Node;

// 头结点
Node *head = NULL;

// 记录节点个数
int num = 0;

// 消费者
void *func_consumer(void *arg)
{
    while (1)
    {
        sem_wait(&sem_consumer);
        pthread_mutex_lock(&mutex);

        Node *tmp = head;
        printf("消费者, id:%ld, number: %d\n", pthread_self(), tmp->number);
        head = head->next;
        free(tmp);
        tmp = NULL;
        num--;

        pthread_mutex_unlock(&mutex);
        sem_post(&sem_producer);
        sleep(rand() % 3);
    }

    return NULL;
}

// 生产者
void *func_producer(void *arg)
{
    while (1)
    {
        sem_wait(&sem_producer);
        pthread_mutex_lock(&mutex);
        // 创建新节点
        Node *node = (Node *)malloc(sizeof(Node));
        node->number = ++num;//rand() % 1000;
        node->next = head;
        head = node;
        printf("生产者，id:%ld, number: %d\n", pthread_self(), node->number);
       
        pthread_mutex_unlock(&mutex);
        sem_post(&sem_consumer);

        sleep(rand() % 3);
    }

    return NULL;
}

int main(int argc, char *argv[])
{
    // 初始化
    pthread_mutex_init(&mutex, NULL);
    // 消费者开始时不能消费，应该初始化为0，消费者线程启动就阻塞了
    sem_init(&sem_consumer, 0, 0);
    // 生产者
    sem_init(&sem_producer, 0, 5); // 资源总数为5

    // 创建5个生产者线程和5个消费者线程
    pthread_t t_producer[5];
    pthread_t t_consumer[5];
    for (int i = 0; i < 5; i++)
    {
        pthread_create(&t_producer[i], NULL, func_producer, NULL);
    }
    for (int i = 0; i < 5; i++)
    {
        pthread_create(&t_consumer[i], NULL, func_consumer, NULL);
    }

    // 线程回收
    for (int i = 0; i < 5; i++)
    {
        pthread_join(t_producer[i], NULL);
        pthread_join(t_consumer[i], NULL);
    }

    // 销毁
    pthread_mutex_destroy(&mutex);
    sem_destroy(&sem_producer);
    sem_destroy(&sem_consumer);

    return 0;
}