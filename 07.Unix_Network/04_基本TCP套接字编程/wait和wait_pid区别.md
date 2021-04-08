# 1. 背景
wait和waitpid函数是用来处理僵死进程的。zombie的作用是维护子程序的信息，以便父程序在以后能够调用它。这些信息包括：进行ID，终止状态、资源利用率（CPU利用率、内存使用等等）。但是操作系统限制了某一时刻能同时存在的进程的最大数目，虽然说它们不占有CPU，不占有内存，但是当下次产生新进程的时候，就会产生未知的错误。因此，有效的处理僵死进程，是有必要的一些事。这个时候，就用到了wait和waitpid两个函数。

# 2. wait和waitpid的作用
返回已经终止的子进程的进程ID号，并清除僵死进程。

# 3. 函数原型
```
#include <sys/wait.h>

pid_t wait(int * statloc);
pid_t waitpid(pid_t pid,int *statloc,int options);

// 成功返回进程ID,出错返回0或者-1。
```
# 4. wait和wait_pid区别
* wait会令调用者阻塞直至某个子进程终止；
* waitpid则可以通过设置一个选项来设置为非阻塞，另外waitpid并不是等待第一个结束的进程而是等待参数中pid指定的进程。
  
### waitpid的option常量
- WNOHANG   waitpid将不阻塞如果指定的pid并未结束
- WUNTRACED 如果子进程进入暂停执行情况则马上返回，但结束状态不予以理会。
  
### wait_pid中pid的含义
* pid==-1 等待任何一个子进程，此时waitpid的作用与wait相同
* pid >0   等待进程ID与pid值相同的子进程
* pid==0   等待与调用者进程组ID相同的任意子进程
* pid<-1   等待进程组ID与pid绝对值相等的任意子进程

### waitpid提供了wait所没有的三个特性
- 1. waitpid使我们可以等待指定的进程
- 2. waitpid提供了一个无阻塞的wait
- 3. waitpid支持工作控制
　　 