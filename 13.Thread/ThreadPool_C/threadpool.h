#ifndef __THREADPOOL_H__
#define __THREADPOOL_H__

typedef struct _ThreadPool ThreadPool;

// 创建线程池并初始化：创建后得到线程池实例
ThreadPool* threadPoolCreate(
	int min,      
	int max, 
	int queueSize
);

// 销毁线程池
int threadPoolDestroy(ThreadPool* pool);

// 给线程池添加任务
void threadPoolAdd(ThreadPool* pool, void(*func)(void*), void* arg);

// 获取当前线程池中工作的线程个数
int threadpoolBusyNum(ThreadPool* pool);

// 获取当前线程池中或者的线程的个数
int threadpoolAliveNum(ThreadPool* pool);

//
void* worker(void* arg);
void* manager(void* arg);
void threadExit(ThreadPool* pool);

#endif // __THREADPOOL_H__