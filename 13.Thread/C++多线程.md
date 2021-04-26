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

## 2.2. 同步方式

对于多个线程访问共享资源出现数据混乱的问题，需要进行线程同步。常用的线程同步方式有四种：**互斥锁**、**读写锁**、**条件变量**、**信号量**。所谓的共享资源就是多个线程共同访问的变量，这些变量通常为**全局数据区变量或者堆区变量**，这些变量对应的共享资源也被称之为临界资源。

# 3. 互斥锁
## 3.1. 互斥锁函数

互斥锁是线程同步最常用的一种方式，通过互斥锁可以锁定一个代码块，被锁定的这个代码块，所有的线程只能顺序执行 (不能并行处理)，这样多线程访问共享资源数据混乱的问题就可以被解决了，**需要付出的代价就是执行效率的降低**，因为默认临界区多个线程是可以并行处理的，现在只能**串行处理**。

在 Linux 中互斥锁的类型为 pthread_mutex_t，创建一个这种类型的变量就得到了一把互斥锁：
```
pthread_mutex_t  mutex;
```
在创建的锁对象中保存了当前这把锁的状态信息：锁定还是打开，如果是锁定状态还记录了给这把锁加锁的线程信息（线程 ID）。一个互斥锁变量只能被一个线程锁定，被锁定之后其他线程再对互斥锁变量加锁就会被阻塞，直到这把互斥锁被解锁，被阻塞的线程才能被解除阻塞。一般情况下，每一个共享资源对应一个把互斥锁，锁的个数和线程的个数无关。
```
// 1. 初始化一个互斥锁
int pthread_mutex_init(pthread_mutex_t *restrict mutex,
           const pthread_mutexattr_t *restrict attr);

// 2. 销毁一个互斥锁
int pthread_destroy(pthread_mutex_t*);

// 3. 加锁，如果获取锁失败，则函数阻塞
// 修改互斥锁的状态, 将其设定为锁定状态, 这个状态被写入到参数 mutex 中
int pthread_mutex_lock(pthread_mutex_t *mutex);

// 4. 释放锁
int pthread_mutex_unlock(pthread_mutex_t *mutex);

// 5. 尝试加锁，如果获取锁失败，则不阻塞，函数直接返回
int pthread_mutex_trylock(pthread_mutex_t *mutex);
```
## 3.2. 互斥锁的使用
见代码07.pthead_mutex.cpp

## 3.3. 死锁
当多个线程访问共享资源，需要加锁，如果锁使用不当，就会造成死锁这种现象。如果线程死锁造成的后果是：所有的线程都被阻塞，并且线程的阻塞是无法解开的（因为可以解锁的线程也被阻塞了）。
造成死锁有以下几种场景：
* 1. 加锁后忘记释放锁
* 2. 函数内加锁后，由于某个判断条件退出函数，而无法执行释放锁的操作
* 3. 重复加锁，在第二次加锁将造成死锁
一种隐藏比较深的场景如下：函数B首先加锁，然后调用了函数A，然而在函数A中也进行了加锁，于是重复加锁导致在函数A中阻塞，造成死锁！
```
void funcA()
{
    pthread_mutex_lock(&mutex);
    ......
    pthread_mutex_unlock(&mutex);
}

void funcB()
{
    pthread_mutex_lock(&mutex);
    ...
    funcA();

    pthread_mutex_unlock(&mutex);
}
```
* 4. 在程序中有多个共享资源，随意加锁容易导致死锁，比如：
线程A要访问共享资源X，于是加锁mutex1；
线程B要访问共享资源Y，于是加锁mutex2；
此时线程A想要访问共享资源Y，线程B想要访问共享资源X，但想要访问的共享资源都被对方锁住，且自己也会阻塞在获取对方锁的函数pthead_mutex_lock()。于是造成死锁。

### 多线程中如何避免死锁
- 1. 避免多次锁定，多检查
- 2. 对共享资源访问完毕之后，一定要解锁，或者在加锁的使用 trylock
- 3. 如果程序中有多把锁，可以**控制对锁的访问顺序** (顺序访问共享资源，但在有些情况下是做不到的)，另外也可以在**对其他互斥锁做加锁操作之前，先释放当前线程拥有的互斥锁**。
- 4. 项目程序中可以引入一些专门用于死锁检测的模块

# 4. 读写锁
# 4.1. 读写锁函数
注意，**读写锁是一把锁**，而不是两把锁！

读写锁是互斥锁的升级版，在做读操作的时候可以提高程序的执行效率，如果所有的线程都是做读操作, 那么读是并行的，但是使用互斥锁，读操作也是串行的。  
读写锁是一把锁，锁的类型为 pthread_rwlock_t，有了类型之后就可以创建一把互斥锁了： 
```
pthread_rwlock_t rwlock;
```
之所以称其为读写锁，是因为这把锁既可以锁定读操作，也可以锁定写操作。为了方便理解，可以大致认为在这把锁中记录了这些信息：

* 锁的状态：锁定 / 打开
* 锁定的是什么操作：读操作 / 写操作，**使用读写锁锁定了读操作，需要先解锁才能去锁定写操作**，反之亦然。
* 哪个线程将这把锁锁上了

读写锁的使用方式也互斥锁的使用方式是完全相同的：找共享资源，确定临界区，在临界区的开始位置加锁（读锁 / 写锁），临界区的结束位置解锁。

因为通过一把读写锁可以锁定读或者写操作，下面介绍一下关于读写锁的特点：

* 使用读写锁的读锁锁定了临界区，线程对临界区的访问是**并行**的，读锁是**共享**的。
* 使用读写锁的写锁锁定了临界区，线程对临界区的访问是**串行**的，写锁是**独占**的。
* 使用读写锁分别对两个临界区加了读锁和写锁，两个线程要同时访问者两个临界区，访问写锁临界区的线程继续运行，访问读锁临界区的线程阻塞，因为**写锁比读锁的优先级高**。

如果说程序中所有的线程都对共享资源做写操作，使用读写锁没有优势，和互斥锁是一样的，如果说程序中所有的线程都对共享资源有写也有读操作，并且对共享资源读的操作越多，读写锁更有优势。

# 4.2. 读写锁函数
* 初始化与销毁
```
#include <pthread.h>
pthread_rwlock_t rwlock;

// 初始化读写锁
int pthread_rwlock_init(pthread_rwlock_t *restrict rwlock,
           const pthread_rwlockattr_t *restrict attr);
// 释放读写锁占用的系统资源
int pthread_rwlock_destroy(pthread_rwlock_t *rwlock);
```

* 读操作加锁
```
// 在程序中对读写锁加读锁, 锁定的是读操作
int pthread_rwlock_rdlock(pthread_rwlock_t *rwlock);
```
调用这个函数，如果读写锁是打开的，那么加锁成功；**如果读写锁已经锁定了读操作，调用这个函数依然可以加锁成功，因为读锁是共享的**；如果读写锁已经锁定了写操作，调用这个函数的线程会被阻塞。

* 读操作尝试加锁，失败后不阻塞
```
// 这个函数可以有效的避免死锁
// 如果加读锁失败, 不会阻塞当前线程, 直接返回错误号
int pthread_rwlock_tryrdlock(pthread_rwlock_t *rwlock);
```
调用这个函数，如果读写锁是打开的，那么加锁成功；**如果读写锁已经锁定了读操作，调用这个函数依然可以加锁成功，因为读锁是共享的**；如果读写锁已经锁定了写操作，调用这个函数加锁失败，**对应的线程不会被阻塞，可以在程序中对函数返回值进行判断**，添加加锁失败之后的处理动作。

* 写操作加锁
```
// 在程序中对读写锁加写锁, 锁定的是写操作
int pthread_rwlock_wrlock(pthread_rwlock_t *rwlock);
```
调用这个函数，如果读写锁是打开的，那么加锁成功；如果读写锁已经**锁定了读操作或者锁定了写操作**，调用这个函数的线程会被阻塞。

* 写操作尝试加锁
```
// 这个函数可以有效的避免死锁
// 如果加写锁失败, 不会阻塞当前线程, 直接返回错误号
int pthread_rwlock_trywrlock(pthread_rwlock_t *rwlock);
```
调用这个函数，如果读写锁是打开的，那么加锁成功；如果读写锁已经锁定了读操作或者锁定了写操作，调用这个函数加锁失败，但是线程不会阻塞，可以在程序中对函数返回值进行判断，添加加锁失败之后的处理动作。

* 释放锁
```
// 解锁, 不管锁定了读还是写都可用解锁
int pthread_rwlock_unlock(pthread_rwlock_t *rwlock);
```

## 4.3. 读写锁代码示例
见08.pthread_rwlock.cpp

# 5. 条件变量
条件变量的重要应用场景：**生产者和消费者**！！
## 5.1. 条件变量函数

严格意义上来说，**条件变量的主要作用不是处理线程同步，而是进行线程的阻塞**。如果在多线程程序中只使用条件变量无法实现线程的同步，**必须要配合互斥锁来使用**。虽然条件变量和互斥锁都能阻塞线程，但是二者的效果是不一样的，二者的区别如下：

假设有 A-Z 26 个线程，这 26 个线程共同访问同一把互斥锁，如果线程 A 加锁成功，那么其余 B-Z 线程访问互斥锁都阻塞，所有的线程只能顺序访问临界区。  
条件变量只有在满足指定条件下才会阻塞线程，如果条件不满足，多个线程可以同时进入临界区，同时读写临界资源，这种情况下还是会出现共享资源中数据的混乱。


一般情况下条件变量用于处理生产者和消费者模型，并且和互斥锁配合使用。条件变量类型对应的类型为 pthread_cond_t，这样就可以定义一个条件变量类型的变量了：
```
pthread_cond_t cond;
```
被条件变量阻塞的线程的线程信息会被记录到这个变量中，以便在解除阻塞的时候使用 

### 条件变量的初始化与销毁
```
#include <pthread.h>
pthread_cond_t cond;

// 初始化
int pthread_cond_init(pthread_cond_t *restrict cond, const pthread_condattr_t *restrict attr);
// 销毁释放资源        
int pthread_cond_destroy(pthread_cond_t *cond);
```

### pthread_cond_wait
```
// 线程阻塞函数, 哪个线程调用这个函数, 哪个线程就会被阻塞
int pthread_cond_wait(pthread_cond_t *restrict cond, pthread_mutex_t *restrict mutex);
```
通过函数原型可以看出，该函数在阻塞线程的时候，需要一个互斥锁参数，这个**互斥锁主要功能是进行线程同步**，让线程顺序进入临界区，避免出现共享资源的数据混乱。该函数会对这个互斥锁做以下几件事情：

- 1. 在阻塞线程时候，如果线程已经对互斥锁 mutex 上锁，那么会将这把锁打开，这样做是为了避免死锁
- 2. 当线程解除阻塞的时候，函数内部会帮助这个线程再次将这个 mutex 互斥锁锁上，继续向下访问临界区

### pthread_cond_timedwait
```
// 表示的时间是从1971.1.1到某个时间点的时间, 总长度使用秒/纳秒表示
struct timespec {
	time_t tv_sec;      /* Seconds */
	long   tv_nsec;     /* Nanoseconds [0 .. 999999999] */
};

// 将线程阻塞一定的时间长度, 时间到达之后, 线程就解除阻塞了
int pthread_cond_timedwait(pthread_cond_t *restrict cond,
           pthread_mutex_t *restrict mutex, const struct timespec *restrict abstime);
```
这个函数的前两个参数和 pthread_cond_wait 函数是一样的，第三个参数表示线程阻塞的时长，但是需要额外注意一点：struct timespec 这个结构体中记录的时间是**从1971.1.1到某个时间点的时间**，总长度使用秒/纳秒表示。因此赋值方式相对要麻烦一点：
```
time_t mytim = time(NULL);	// 1970.1.1 0:0:0 到当前的总秒数
struct timespec tmsp;
tmsp.tv_nsec = 0;
tmsp.tv_sec = time(NULL) + 100;	// 线程阻塞100s
```

### 唤醒阻塞在某条件变量上的线程
```
// 唤醒阻塞在条件变量上的线程, 至少有一个被解除阻塞
int pthread_cond_signal(pthread_cond_t *cond);

// 唤醒阻塞在条件变量上的线程, 被阻塞的线程全部解除阻塞
int pthread_cond_broadcast(pthread_cond_t *cond);
```
调用上面两个函数中的任意一个，都可以换线被 pthread_cond_wait 或者 pthread_cond_timedwait 阻塞的线程，区别就在于 pthread_cond_signal 是唤醒至少一个被阻塞的线程（总个数不定），pthread_cond_broadcast 是唤醒所有被阻塞的线程。

如果没有线程阻塞，则该函数不会有任何作用。

## 5.2. 生产者与消费者
见代码09.pthread_cond_t.cpp

# 6. 信号量
## 6.1. 信号量函数

信号量用在多线程**多任务同步**的，一个线程完成了某一个动作就通过信号量告诉别的线程，别的线程再进行某些动作。信号量不一定是锁定某一个资源，而是流程上的概念，比如：有 A，B 两个线程，B 线程要等 A 线程完成某一任务以后再进行自己下面的步骤，这个任务并不一定是锁定某一资源，还可以是进行一些计算或者数据处理之类。

信号量（信号灯）与互斥锁和条件变量的主要不同在于” 灯” 的概念，灯亮则意味着资源可用，灯灭则意味着不可用。**信号量主要阻塞线程，不能完全保证线程安全**，如果要保证线程安全，需要信号量和互斥锁一起使用。

**信号量和条件变量一样用于处理生产者和消费者模型，用于阻塞生产者线程或者消费者线程的运行**。信号的类型为 sem_t 对应的头文件为 <semaphore.h>

### 信号量初始化和销毁
```
#include <semaphore.h>

// 初始化信号量/信号灯
int sem_init(sem_t *sem, int pshared, unsigned int value);

// 资源释放, 线程销毁之后调用这个函数即可
// 参数 sem 就是 sem_init() 的第一个参数            
int sem_destroy(sem_t *sem);
```

**参数**:  
* sem：信号量变量地址
* pshared：  
    0：线程同步  
    非 0：进程同步  
* value：初始化当前信号量拥有的资源数（>=0），如果资源数为 0，线程就会被阻塞了。

### sem_wait(sem_t* sem)
```
// 参数 sem 就是 sem_init() 的第一个参数  
// 函数被调用sem中的资源就会被消耗1个, 资源数-1
int sem_wait(sem_t *sem);
```
当线程调用这个函数，并且 sem 中的资源数 >0，线程不会阻塞，线程会占用 sem 中的一个资源，因此资源数 - 1，直到 sem 中的资源数减为 0 时，资源被耗尽，因此线程也就被阻塞了。

### sem_trywait
```
// 参数 sem 就是 sem_init() 的第一个参数  
// 函数被调用sem中的资源就会被消耗1个, 资源数-1
int sem_trywait(sem_t *sem);
```

当线程调用这个函数，并且 sem 中的资源数 >0，线程不会阻塞，线程会占用 sem 中的一个资源，因此资源数 - 1，直到 sem 中的资源数减为 0 时，资源被耗尽，**但是线程不会被阻塞，直接返回错误号**，因此可以在程序中添加判断分支，用于处理获取资源失败之后的情况。

### sem_timedwait
```
// 表示的时间是从1971.1.1到某个时间点的时间, 总长度使用秒/纳秒表示
struct timespec {
	time_t tv_sec;      /* Seconds */
	long   tv_nsec;     /* Nanoseconds [0 .. 999999999] */
};

// 调用该函数线程获取sem中的一个资源，当资源数为0时，线程阻塞，在阻塞abs_timeout对应的时长之后，解除阻塞。
// abs_timeout: 阻塞的时间长度, 单位是s, 是从1970.1.1开始计算的
int sem_timedwait(sem_t *sem, const struct timespec *abs_timeout);
```

该函数的参数 abs_timeout 和 pthread_cond_timedwait 的最后一个参数是一样的，使用方法不再过多赘述。当线程调用这个函数，并且 sem 中的资源数 >0，线程不会阻塞，线程会占用 sem 中的一个资源，因此资源数 - 1，直到 sem 中的资源数减为 0 时，资源被耗尽，线程被阻塞，**当阻塞指定的时长之后，线程解除阻塞**。

### sem_post
```
// 调用该函数给sem中的资源数+1
int sem_post(sem_t *sem);
```

调用该函数会将 sem 中的资源数 +1，如果有线程在调用 sem_wait、sem_trywait、sem_timedwait 时因为 sem 中的资源数为 0 被阻塞了，这时这些线程会解除阻塞，获取到资源之后继续向下运行。

### sem_getvalue
```
// 查看信号量 sem 中的整形数的当前值, 这个值会被写入到sval指针对应的内存中
// sval是一个传出参数
int sem_getvalue(sem_t *sem, int *sval);
```
通过这个函数可以查看 sem 中现在拥有的资源个数，通过第二个参数 sval 将数据传出，也就是说第二个参数的作用和返回值是一样的。