# 1. C++线程相关函数
## 1.1. 创建子线程
注意两点：
* 1. 包含头文件 pthread.h
* 2. 编译时加上选项 -lpthread
```
g++ 01_pthread_create.cpp -lpthread -o app
```
```
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <pthread.h>

void* callback(void* arg)
{
    for(int i = 0;i<5;++i)
    {
        printf("子线程:i = %d\n", i);
    }
    printf("子线程 %ld\n", pthread_self());

    return NULL;
}

int main(int argc, char* argv[])
{
    pthread_t tid;
    pthread_create(&tid, NULL, callback, NULL);
    for(int i = 0;i<5;i++)
    {
        printf("主线程: i = %d\n", i);
    }
    printf("主线程: %ld\n", pthread_self());

    return 0;
}
```
运行上述程序，结果如下：
```
主线程: i = 0
主线程: i = 1
主线程: i = 2
主线程: i = 3
主线程: i = 4
主线程: 139975713027840
```
可以看到只输出了主线程的执行情况，而子线程的打印并未输出，甚至子线程根本没有执行！

这是因为**子线程在尚未抢到时间片的时候，主线程已经执行结束了**，于是主线程退出，释放了线程所在进程的地址空间，子线程也就被销毁了。
* 解决办法
- 1. 主线程sleep：主线程sleep，即挂起，则让出时间片，子线程会得到时间片执行。
- 2. 线程退出函数pthread_exit

## 1.2. 线程退出函数pthread_exit
线程退出函数是让某一个线程退出而不影响其他线程运行。该函数主要是在主线程中使用。一般而言，子线程退出并不会影响进程的地址空间，即并不会影响主线程。
```
void* callback(void* arg)
{
    for(int i = 0;i<5;++i)
    {
        printf("子线程:i = %d\n", i);
    }
    printf("子线程 %ld\n", pthread_self());

    return NULL;
}

int main(int argc, char* argv[])
{
    pthread_t tid;
    pthread_create(&tid, NULL, callback, NULL);
    // 1. 主线程主动sleep，让出时间片
    // sleep(1); 
    printf("主线程: %ld\n", pthread_self());

    pthread_exit(NULL);

    return 0;
}
```
执行结果如下：
```
主线程: 140553199572736
子线程:i = 0
子线程:i = 1
子线程:i = 2
子线程:i = 3
子线程:i = 4
子线程 140553191237376
```
## 1.3. 线程回收
线程和进程一样，子线程退出的时候其内核资源主要由主线程回收，线程库中提供的线程回收函叫做**pthread_join()**，这个函数是一个**阻塞函数**，如果还有子线程在运行，调用该函数就会阻塞，子线程退出函数解除阻塞进行资源的回收，函数被调用一次，只能回收一个子线程，如果有多个子线程则需要循环进行回收。
另外通过线程回收函数还可以获取到子线程退出时传递出来的数据，函数原型如下:
```
#include <pthread.h>
// 这是一个阻塞函数, 子线程在运行这个函数就阻塞
// 子线程退出, 函数解除阻塞, 回收对应的子线程资源, 类似于回收进程使用的函数 wait()
int pthread_join(pthread_t thread, void **retval);
```
我们尝试使用一下该函数。示例代码如下：
```
struct Test
{
    int num;
    int age;
};

void* callback(void* arg)
{
    printf("子线程: %ld\n", pthread_self());

    struct Test t;
    t.age = 10;
    t.num = 99;

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
```
执行结果如下：
```
主线程: 140074601146112
子线程: 140074592810752
t.age = 32613, t.num = -1470580992
```
可见，传出的参数并不正确！
上述代码中**子线程中的t是局部变量，存储在栈空间**。当子线程退出以后，栈空间被回收。因此，可以使用全局变量或者堆内存来作为传回的参数。
当然，也可以使用**主线程的栈空间**。
```
struct Test
{
    int num;
    int age;
};

// 修改为全局变量
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
```
运行上述代码，即可获得正确的返回值。
## 1.4. 线程分离pthread_detach
在某些情况下，程序中的主线程有属于自己的业务处理流程，如果让主线程负责子线程的资源回收，调用 pthread_join() 只要子线程不退出主线程就会一直被阻塞，主要线程的任务也就不能被执行了。

在线程库函数中为我们提供了线程分离函数 pthread_detach()，调用这个函数之后指定的子线程就可以和主线程分离，当子线程退出的时候，其占用的内核资源就被系统的其他进程接管并回收了。线程分离之后在主线程中使用 pthread_join() 就回收不到子线程资源了。
```
void* callback(void* arg)
{
    printf("子线程: %ld\n", pthread_self());

    return NULL;
}

int main(int argc, char* argv[])
{
    pthread_t tid;
    pthread_create(&tid, NULL, callback, NULL);

    printf("主线程: %ld\n", pthread_self());

    // 线程分离
    pthread_detach(tid);

    pthread_exit(NULL);

    return 0;
}

```
## 1.5. 其他线程函数
## 1.5.1. 线程取消pthread_cancel
线程取消的意思就是在某些特定情况下在一个线程中杀死另一个线程。使用这个函数杀死一个线程需要分两步：
- 1. 在线程 A 中调用线程取消函数 pthread_cancel，指定杀死线程 B，这时候线程 B 是死不了的
- 2. 在线程 B 中进程一次系统调用（从用户区切换到内核区），否则线程 B 可以一直运行。
```
#include <pthread.h>
// 参数是子线程的线程ID
int pthread_cancel(pthread_t thread);
```
在下面的示例代码中，主线程调用线程取消函数，**只要在子线程中进行了系统调用**，当子线程执行到这个位置就挂掉了:
```
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <pthread.h>

// 子线程的处理代码
void* working(void* arg)
{
    int j=0;
    for(int i=0; i<9; ++i)
    {
        j++;
    }
    // 这个函数会调用系统函数, 因此这是个间接的系统调用
    printf("我是子线程, 线程ID: %ld\n", pthread_self());
    for(int i=0; i<9; ++i)
    {
        printf(" child i: %d\n", i);
    }

    return NULL;
}

int main()
{
    // 1. 创建一个子线程
    pthread_t tid;
    pthread_create(&tid, NULL, working, NULL);

    printf("子线程创建成功, 线程ID: %ld\n", tid);
    // 2. 子线程不会执行下边的代码, 主线程执行
    printf("我是主线程, 线程ID: %ld\n", pthread_self());
    for(int i=0; i<3; ++i)
    {
        printf("i = %d\n", i);
    }

    // 杀死子线程, 如果子线程中做系统调用, 子线程就结束了
    pthread_cancel(tid);

    // 让主线程自己退出即可
    pthread_exit(NULL);
    
    return 0;
}
```
上述代码运行结果：
```
子线程创建成功, 线程ID: 140626545895168
我是主线程, 线程ID: 140626554230528
i = 0
i = 1
i = 2
```
# 2. 线程同步
假设有 4 个线程 A、B、C、D，当前一个线程 A 对内存中的共享资源进行访问的时候，其他线程 B, C, D 都不可以对这块内存进行操作，直到线程 A 对这块内存访问完毕为止，B，C，D 中的一个才能访问这块内存，剩余的两个需要继续阻塞等待，以此类推，直至所有的线程都对这块内存操作完毕。 线程对内存的这种访问方式就称之为线程同步，通过对概念的介绍，我们可以了解到**所谓的同步并不是多个线程同时对内存进行访问，而是按照先后顺序依次进行的**。
## 2.1. 为什么要同步
比如代码06.multi_thread_error.cpp，线程A和B各自对money计数增加50次，理论上最后money的值应该是100，但是实际结果在大部分情况下都小于100.

可以看出虽然每个线程内部循环了 50 次每次数一个数，但是最终没有数到 100，通过输出的结果可以看到，有些数字被重复数了多次，其原因就是没有对线程进行同步处理，造成了数据的混乱。  

两个线程在数数的时候需要分时复用 CPU 时间片，并且测试程序中调用了 sleep() 导致线程的 CPU 时间片没用完就被迫挂起了，这样就能让 CPU 的上下文切换（保存当前状态，下一次继续运行的时候需要加载保存的状态）更加频繁，更容易再现数据混乱的这个现象。  

CPU 对应寄存器、一级缓存、二级缓存、三级缓存是独占的，用于存储处理的数据和线程的状态信息，数据被 CPU 处理完成需要再次被写入到物理内存中，物理内存数据也可以通过文件 IO 操作写入到磁盘中。

在测试程序中两个线程共用全局变量 money 当线程变成运行态之后开始数数，从物理内存加载数据，让后将数据放到 CPU 进行运算，最后将结果更新到物理内存中。如果数数的两个线程都可以顺利完成这个流程，那么得到的结果肯定是正确的。

如果线程 A 执行这个过程期间就失去了 CPU 时间片，线程 A 被挂起了最新的数据没能更新到物理内存。线程 B 变成运行态之后从物理内存读数据，很显然它没有拿到最新数据，只能基于旧的数据往后数，然后失去 CPU 时间片挂起。线程 A 得到 CPU 时间片变成运行态，第一件事儿就是将上次没更新到内存的数据更新到内存，但是这样会导致线程 B 已经更新到内存的数据被覆盖，活儿白干了，最终导致有些数据会被重复数很多次。
