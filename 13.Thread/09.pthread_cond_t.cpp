#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include <pthread.h>

/*

场景：使用条件变量实现生产者和消费者模型，其中
1. 生产者有5个，往链表头部添加节点
2. 消费者有5个，删除链表头部的节点

*/

// 条件变量
pthread_cond_t cond;

// 互斥锁变量
pthread_mutex_t mutex;

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
        pthread_mutex_lock(&mutex);
        while(head == NULL)
        // if(head == NULL) // 使用if会crash
        {
            // 任务队列, 也就是链表中已经没有节点可以消费了
            // 消费者线程需要阻塞
            // 线程加互斥锁成功, 但是线程阻塞在这行代码上, 锁还没解开
            // 其他线程在访问这把锁的时候也会阻塞, 生产者也会阻塞 ==> 死锁
            // 这函数会自动将线程拥有的锁解开
            pthread_cond_wait(&cond, &mutex);
        }
        Node *tmp = head;
        printf("消费者, id:%ld, number: %d\n", pthread_self(), tmp->number);
        head = head->next;
        free(tmp);
        tmp = NULL;
        num--;
        pthread_mutex_unlock(&mutex);
        sleep(rand() % 3);
    }

    return NULL;
}

// 生产者:生产者可以一直生产，没有上限
void *func_producer(void *arg)
{
    while (1)
    {
        pthread_mutex_lock(&mutex);
        // 创建新节点
        Node *node = (Node *)malloc(sizeof(Node));
        node->number = ++num;//rand() % 1000;
        node->next = head;
        head = node;
        printf("生产者，id:%ld, number: %d\n", pthread_self(), node->number);
        pthread_mutex_unlock(&mutex);
        
        // 唤醒阻塞在条件变量上的线程
        pthread_cond_signal(&cond);

        sleep(rand() % 3);
    }

    return NULL;
}

int main(int argc, char *argv[])
{
    // 初始化
    pthread_cond_init(&cond, NULL);
    pthread_mutex_init(&mutex, NULL);

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
    pthread_cond_destroy(&cond);

    return 0;
}