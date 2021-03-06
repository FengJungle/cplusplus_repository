
select函数允许进程指示内核等待多个事件中的任何一个发生，并只在有一个或多个事件发生或经历一段指定的时间后才唤醒它。
```
#include <sys/select.h>
#include <sys/time.h>

int select(int maxfdp1, fd_set *readset, fd_set *writeset, fd_set *exceptset, const struct timeval *timeout);
```
select函数的中间三个参数，如果我们对某个条件不感兴趣，可以把它设置为空指针。

其中：
##### 参数1：maxfdp1
指定待测试的描述符的个数。它的值是待测试的最大描述符+1.

##### 参数2：timeout
timeout告知内核等待所指定描述符中的任何一个就绪可花多长时间。
```
struct timeval{
    long tv_sec;  // seconds
    long tv_usec; // microseconds
}
```
该参数有3中可能：  
- 1. 永远等待下去：仅在有一个描述符准备好IO时才返回。此时该参数设置为NULL；
- 2. 等待一段固定时间：在有一个描述符准备好IO时返回，但不超过指定的秒和微秒；
- 3. 根本不等待：检查描述符后立即返回，这称为**轮询**，为此，该参数中的值设定为0.

##### 参数3：exceptset
支持的异常条件有两个：
- 1. 某个套接字的带外数据的到达
- 2. 某个已置为分组模式的伪终端存在可从其主端读取的控制状态信息。

##### 一个套接字准备好读的条件
满足下列4个条件中的任何一个时，一个套接字准备好读：
- 1. 该套接字接收缓冲区中的数据字节数大于等于套接字低水位标记的当前大小。对这样的套接字执行读操作不会阻塞，并将返回一个大于0的值（也就是返回准备好读入的数据）；
- 2. 该套接字的读半部关闭，也就是接收了FIN的TCP连接。对这样的套接字的读操作将不阻塞，并返回0，即返回EOF；
- 3. 该套接字是一个**监听套接字**，并且已完成连接数不为0.对这样的套接字accept通常不会阻塞；
- 4. 其上有一个套接字错误待处理。对这样的套接字的读操作将不会阻塞并返回-1，同时把errno设置成确切的错误条件。

##### 一个套接字准备好写的条件
满足下列4个条件中的任何一个，一个套接字准备好写：
- 1. 该套接字发送缓冲区中的可用空间字节数大于等于套接字发送缓冲区低水位标记的当前大小，并且或者该套接字已连接，或者该套接字不需要连接(UDP)。
- 2. 该连接的写半部关闭，即发送了FIN的TCP连接。对这样的套接字的写操作将产生SIGPIPE信号；
- 3. 使用非阻塞式connect的套接字建立连接，或者connect已经以失败告终；
- 4. 其上有一个套接字错误待处理。对这样的套接字的写操作将不阻塞并返回-1，同时把errno设置成确切的错误条件。

注意：一个套接字上发生错误时，它将由select标记为既可读又可写。