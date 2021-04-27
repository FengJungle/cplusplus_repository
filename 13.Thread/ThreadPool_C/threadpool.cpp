
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <unistd.h>
#include "threadpool.h"

const int NUMBER = 2;

// 任务结构体
typedef struct _Task
{
	// 函数指针
	void(*function)(void* arg);
	// 参数
	void* arg;
}Task;

// 线程池结构体
typedef struct _ThreadPool
{
	// 任务队列
	Task* taskqueue;
	// 任务队列容量
	int queueCapacity;
	// 当前任务个数
	int queueSize;
	// 队首 --> 取数据
	int queueFront;
	// 队尾 --> 放数据
	int queueRear;

	// 管理者线程ID
	pthread_t managerID;
	// 工作线程ID
	pthread_t *threadIDs;
	// 工作线程数量范围
	int minNum;
	int maxNum;
	// 当前忙的线程数
	int busyNum;
	// 当前存活的线程
	int liveNum;
	// 要杀死的线程个数
	int exitNum;

	// 同步：锁整个线程池
	pthread_mutex_t mutexPool;
	// 同步：busyNum，这个参数经常被访问
	pthread_mutex_t mutexBusy;

	// 是不是要销毁线程池，销毁为1，不销毁为0
	int shutdown;

	// 生产者消费者模型，需要条件变量来阻塞
	// 任务队列是不是满了
	pthread_cond_t notFull;
	// 任务队列是不是空了
	pthread_cond_t notEmpty;

}ThreadPool;

ThreadPool* threadPoolCreate(
	int min,
	int max,
	int queueSize
)
{
	ThreadPool*pool = (ThreadPool*)malloc(sizeof(ThreadPool));
	do {
		if (NULL == pool)
		{
			printf("malloc threadpool fail...\n");
			break;
		}

		pool->threadIDs = (pthread_t*)malloc(sizeof(pthread_t)*max);
		if (NULL == pool->threadIDs)
		{
			printf("malloc threadIDs fail...\n");
			break;
		}
		memset(pool->threadIDs, 0, sizeof(pthread_t)*max);

		pool->maxNum = max;
		pool->minNum = min;
		pool->busyNum = 0;
		pool->exitNum = 0;
		pool->liveNum = min;

		if ((pthread_mutex_init(&pool->mutexBusy, NULL)) != 0 ||
			(pthread_mutex_init(&pool->mutexPool, NULL)) != 0 ||
			(pthread_cond_init(&pool->notEmpty, NULL)) != 0 ||
			(pthread_cond_init(&pool->notFull, NULL)) != 0)
		{
			printf("init mutex or cond fail...\n");
			break;
		}

		pool->taskqueue = (Task*)malloc(sizeof(Task)*queueSize);
		pool->queueCapacity = queueSize;
		pool->queueFront = 0;
		pool->queueRear = 0;
		pool->queueSize = 0;

		pool->shutdown = 0;

		// 创建线程
		pthread_create(&pool->managerID, NULL, manager, pool);
		for (int i = 0; i < pool->maxNum; i++)
		{
			pthread_create(&pool->threadIDs[i], NULL, worker, pool);
		}
		return pool;
	} while (0);

	// 释放资源
	if (pool && pool->threadIDs) free(pool->threadIDs);
	if (pool && pool->taskqueue) free(pool->taskqueue);
	if (pool) free(pool);

	return NULL;
}

void* worker(void* arg)
{
	ThreadPool* pool = (ThreadPool*)arg;
	while (1)
	{
		pthread_mutex_lock(&pool->mutexPool);
		// 当前队列是否为空
		while (pool->queueSize == 0 && !pool->shutdown)
		{
			// 阻塞工作线程
			pthread_cond_wait(&pool->notEmpty, &pool->mutexPool);

			// 判断是不是要销毁线程
			if (pool->exitNum > 0)
			{
				pool->exitNum--;
				if (pool->liveNum > pool->minNum)
				{
					pool->liveNum--;
					pthread_mutex_unlock(&pool->mutexPool);
					threadExit(pool);
				}
			}
		}

		// 判断当前线程池是不是被关闭了
		if (pool->shutdown)
		{
			pthread_mutex_unlock(&pool->mutexPool);
			threadExit(pool);
		}

		// 从任务队列中取出一个任务
		Task task;
		task.function = pool->taskqueue[pool->queueFront].function;
		task.arg = pool->taskqueue[pool->queueFront].arg;

		// 移动头节点
		pool->queueFront = (pool->queueFront + 1) % pool->queueCapacity;
		pool->queueSize--;

		pthread_mutex_unlock(&pool->mutexPool);

		// 唤醒生产者
		pthread_cond_signal(&pool->notFull);

		printf("thread %ld start working...\n", pthread_self());
		// 维护busyNum
		pthread_mutex_lock(&pool->mutexBusy);
		pool->busyNum++;
		pthread_mutex_unlock(&pool->mutexBusy);

		// 开始执行线程
		task.function(task.arg);
		free(task.arg);
		task.arg = NULL;

		// 维护busyNum
		pthread_mutex_lock(&pool->mutexBusy);
		pool->busyNum--;
		pthread_mutex_unlock(&pool->mutexBusy);
		printf("thread %ld finish working...\n", pthread_self());
	}
	return NULL;
}

void* manager(void* arg)
{
	ThreadPool* pool = (ThreadPool*)arg;

	while (!pool->shutdown)
	{
		// 每隔3s检测一次
		sleep(3);

		// 取出线程池中的任务的数量和当前线程的数量
		pthread_mutex_lock(&pool->mutexPool);
		int queueSize = pool->queueSize;
		int liveNum = pool->liveNum;
		pthread_mutex_unlock(&pool->mutexPool);

		// 取出忙的线程的数量
		pthread_mutex_lock(&pool->mutexBusy);
		int busyNum = pool->busyNum;
		pthread_mutex_unlock(&pool->mutexBusy);

		printf("queueSize = %d, liveNum = %d\n", queueSize, liveNum);
		// 添加线程
		// 任务的个数 > 存活的线程数 && 存活的线程数 < 最大线程数
		if (queueSize > liveNum && liveNum < pool->maxNum)
		{
			pthread_mutex_lock(&pool->mutexPool);
			int counter = 0;
			// NUMBER: 一次性最多添加NUMBER个线程
			for (int i = 0; i < pool->maxNum && counter < NUMBER && pool->liveNum < pool->maxNum; ++i)
			{
				// 找到空闲位置存储线程id
				if (pool->threadIDs[i] == 0)
				{
					printf("create new thread...\n");
					pthread_create(&pool->threadIDs[i], NULL, worker, pool);
					counter++;
					pool->liveNum++;
				}
			}
			pthread_mutex_unlock(&pool->mutexPool);
		}

		// 销毁线程
		// 指定一个规则：忙的线程*2 < 存活的线程数 && 存活的线程数 > 最小线程数
		if (busyNum * 2 < liveNum && liveNum > pool->minNum)
		{
			pthread_mutex_lock(&pool->mutexPool);
			// 一次最多销毁NUMBER个线程
			pool->exitNum = NUMBER;
			pthread_mutex_unlock(&pool->mutexPool);

			// 让工作的线程自杀
			for (int i = 0; i < NUMBER; ++i)
			{
				// 唤醒线程
				pthread_cond_signal(&pool->notEmpty);
			}
		}
	}

	return NULL;
}

void threadExit(ThreadPool* pool)
{
	pthread_t tid = pthread_self();
	for (int i = 0; i < pool->maxNum; i++)
	{
		if (pool->threadIDs[i] == tid)
		{
			pool->threadIDs[i] == 0;
			printf("threadExit() called, %ld exiting...\n", tid);
			break;
		}
	}
	pthread_exit(NULL);
}

void threadPoolAdd(ThreadPool* pool, void(*func)(void*), void* arg)
{
	pthread_mutex_lock(&pool->mutexPool);

	// 如果线程池还继续使用，但是线程池已经满了，那么需要阻塞生产者
	while (pool->queueSize == pool->queueCapacity && !pool->shutdown)
	{
		// 阻塞生产者线程
		pthread_cond_wait(&pool->notFull, &pool->mutexPool);
	}
	if (pool->shutdown)
	{
		pthread_mutex_unlock(&pool->mutexPool);
		return;
	}

	// 队列尾部添加任务
	pool->taskqueue[pool->queueRear].function = func;
	pool->taskqueue[pool->queueRear].arg = arg;
	pool->queueRear = (pool->queueRear + 1) % pool->queueCapacity;
	pool->queueSize++;

	// 唤醒阻塞在条件变量上的工作线程(消费者)
	pthread_cond_signal(&pool->notEmpty);

	pthread_mutex_unlock(&pool->mutexPool);
}
// 获取当前线程池中工作的线程个数
int threadpoolBusyNum(ThreadPool* pool)
{
	pthread_mutex_lock(&pool->mutexBusy);
	int busyNum = pool->busyNum;
	pthread_mutex_unlock(&pool->mutexBusy);
	return busyNum;
}

// 获取当前线程池中或者的线程的个数
int threadpoolAliveNum(ThreadPool* pool)
{
	pthread_mutex_lock(&pool->mutexPool);
	int aliveNum = pool->liveNum;
	pthread_mutex_unlock(&pool->mutexPool);
	return aliveNum;
}

int threadPoolDestroy(ThreadPool* pool)
{
	if (pool == NULL)
	{
		return -1;
	}
	// 关闭线程池
	pool->shutdown = 1;
	// 阻塞回收管理者线程
	pthread_join(pool->managerID, NULL);
	printf("after pthread_join\n");
	// 唤醒阻塞的消费者线程
	for (int i = 0; i < pool->liveNum; ++i)
	{
		pthread_cond_signal(&pool->notEmpty);
	}
	printf("strat to free...\n");
	// 释放内存
	if (pool->taskqueue)
	{
		free(pool->taskqueue);
	}
	if (pool->threadIDs)
	{
		free(pool->threadIDs);
	}
	pthread_mutex_destroy(&pool->mutexBusy);
	pthread_mutex_destroy(&pool->mutexPool);
	pthread_cond_destroy(&pool->notEmpty);
	pthread_cond_destroy(&pool->notFull);
	free(pool);
	pool = NULL;
}
