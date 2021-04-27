#ifndef __THREADPOOL_H__
#define __THREADPOOL_H__

typedef struct _ThreadPool ThreadPool;

// �����̳߳ز���ʼ����������õ��̳߳�ʵ��
ThreadPool* threadPoolCreate(
	int min,      
	int max, 
	int queueSize
);

// �����̳߳�
int threadPoolDestroy(ThreadPool* pool);

// ���̳߳��������
void threadPoolAdd(ThreadPool* pool, void(*func)(void*), void* arg);

// ��ȡ��ǰ�̳߳��й������̸߳���
int threadpoolBusyNum(ThreadPool* pool);

// ��ȡ��ǰ�̳߳��л��ߵ��̵߳ĸ���
int threadpoolAliveNum(ThreadPool* pool);

//
void* worker(void* arg);
void* manager(void* arg);
void threadExit(ThreadPool* pool);

#endif // __THREADPOOL_H__