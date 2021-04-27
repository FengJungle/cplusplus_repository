
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <unistd.h>
#include "threadpool.h"

const int NUMBER = 2;

// ����ṹ��
typedef struct _Task
{
	// ����ָ��
	void(*function)(void* arg);
	// ����
	void* arg;
}Task;

// �̳߳ؽṹ��
typedef struct _ThreadPool
{
	// �������
	Task* taskqueue;
	// �����������
	int queueCapacity;
	// ��ǰ�������
	int queueSize;
	// ���� --> ȡ����
	int queueFront;
	// ��β --> ������
	int queueRear;

	// �������߳�ID
	pthread_t managerID;
	// �����߳�ID
	pthread_t *threadIDs;
	// �����߳�������Χ
	int minNum;
	int maxNum;
	// ��ǰæ���߳���
	int busyNum;
	// ��ǰ�����߳�
	int liveNum;
	// Ҫɱ�����̸߳���
	int exitNum;

	// ͬ�����������̳߳�
	pthread_mutex_t mutexPool;
	// ͬ����busyNum�������������������
	pthread_mutex_t mutexBusy;

	// �ǲ���Ҫ�����̳߳أ�����Ϊ1��������Ϊ0
	int shutdown;

	// ������������ģ�ͣ���Ҫ��������������
	// ��������ǲ�������
	pthread_cond_t notFull;
	// ��������ǲ��ǿ���
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

		// �����߳�
		pthread_create(&pool->managerID, NULL, manager, pool);
		for (int i = 0; i < pool->maxNum; i++)
		{
			pthread_create(&pool->threadIDs[i], NULL, worker, pool);
		}
		return pool;
	} while (0);

	// �ͷ���Դ
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
		// ��ǰ�����Ƿ�Ϊ��
		while (pool->queueSize == 0 && !pool->shutdown)
		{
			// ���������߳�
			pthread_cond_wait(&pool->notEmpty, &pool->mutexPool);

			// �ж��ǲ���Ҫ�����߳�
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

		// �жϵ�ǰ�̳߳��ǲ��Ǳ��ر���
		if (pool->shutdown)
		{
			pthread_mutex_unlock(&pool->mutexPool);
			threadExit(pool);
		}

		// �����������ȡ��һ������
		Task task;
		task.function = pool->taskqueue[pool->queueFront].function;
		task.arg = pool->taskqueue[pool->queueFront].arg;

		// �ƶ�ͷ�ڵ�
		pool->queueFront = (pool->queueFront + 1) % pool->queueCapacity;
		pool->queueSize--;

		pthread_mutex_unlock(&pool->mutexPool);

		// ����������
		pthread_cond_signal(&pool->notFull);

		printf("thread %ld start working...\n", pthread_self());
		// ά��busyNum
		pthread_mutex_lock(&pool->mutexBusy);
		pool->busyNum++;
		pthread_mutex_unlock(&pool->mutexBusy);

		// ��ʼִ���߳�
		task.function(task.arg);
		free(task.arg);
		task.arg = NULL;

		// ά��busyNum
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
		// ÿ��3s���һ��
		sleep(3);

		// ȡ���̳߳��е�����������͵�ǰ�̵߳�����
		pthread_mutex_lock(&pool->mutexPool);
		int queueSize = pool->queueSize;
		int liveNum = pool->liveNum;
		pthread_mutex_unlock(&pool->mutexPool);

		// ȡ��æ���̵߳�����
		pthread_mutex_lock(&pool->mutexBusy);
		int busyNum = pool->busyNum;
		pthread_mutex_unlock(&pool->mutexBusy);

		printf("queueSize = %d, liveNum = %d\n", queueSize, liveNum);
		// ����߳�
		// ����ĸ��� > �����߳��� && �����߳��� < ����߳���
		if (queueSize > liveNum && liveNum < pool->maxNum)
		{
			pthread_mutex_lock(&pool->mutexPool);
			int counter = 0;
			// NUMBER: һ����������NUMBER���߳�
			for (int i = 0; i < pool->maxNum && counter < NUMBER && pool->liveNum < pool->maxNum; ++i)
			{
				// �ҵ�����λ�ô洢�߳�id
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

		// �����߳�
		// ָ��һ������æ���߳�*2 < �����߳��� && �����߳��� > ��С�߳���
		if (busyNum * 2 < liveNum && liveNum > pool->minNum)
		{
			pthread_mutex_lock(&pool->mutexPool);
			// һ���������NUMBER���߳�
			pool->exitNum = NUMBER;
			pthread_mutex_unlock(&pool->mutexPool);

			// �ù������߳���ɱ
			for (int i = 0; i < NUMBER; ++i)
			{
				// �����߳�
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

	// ����̳߳ػ�����ʹ�ã������̳߳��Ѿ����ˣ���ô��Ҫ����������
	while (pool->queueSize == pool->queueCapacity && !pool->shutdown)
	{
		// �����������߳�
		pthread_cond_wait(&pool->notFull, &pool->mutexPool);
	}
	if (pool->shutdown)
	{
		pthread_mutex_unlock(&pool->mutexPool);
		return;
	}

	// ����β���������
	pool->taskqueue[pool->queueRear].function = func;
	pool->taskqueue[pool->queueRear].arg = arg;
	pool->queueRear = (pool->queueRear + 1) % pool->queueCapacity;
	pool->queueSize++;

	// �������������������ϵĹ����߳�(������)
	pthread_cond_signal(&pool->notEmpty);

	pthread_mutex_unlock(&pool->mutexPool);
}
// ��ȡ��ǰ�̳߳��й������̸߳���
int threadpoolBusyNum(ThreadPool* pool)
{
	pthread_mutex_lock(&pool->mutexBusy);
	int busyNum = pool->busyNum;
	pthread_mutex_unlock(&pool->mutexBusy);
	return busyNum;
}

// ��ȡ��ǰ�̳߳��л��ߵ��̵߳ĸ���
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
	// �ر��̳߳�
	pool->shutdown = 1;
	// �������չ������߳�
	pthread_join(pool->managerID, NULL);
	printf("after pthread_join\n");
	// �����������������߳�
	for (int i = 0; i < pool->liveNum; ++i)
	{
		pthread_cond_signal(&pool->notEmpty);
	}
	printf("strat to free...\n");
	// �ͷ��ڴ�
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
