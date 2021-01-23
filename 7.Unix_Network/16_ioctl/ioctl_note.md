网络程序中（一般是服务器程序）ioctl常用于在程序启动时获得主机上所有接口的信息：
接口的地址，接口是否支持广播、是否支持多播等。

`
#include <unistd.h>

// fd: ioctl函数影响由fd参数指向的打开的文件
// 第三个参数是一个指针，指针的类型依赖于request
int ioctl(int fd, int request, .../* void* arg */);
`


我们可以把和网络有关的请求分为6类：
(1) 套接口操作
(2) 文件操作
(3) 接口操作
(4) ARP高速缓存操作
(5) 路由表操作
(6) 流系统

1. 套接口操作
有三种ioctl请求是明确真毒套接口的，他们都要求ioctl的第三个参数是一个指向整数的指针

SIOCATMASK 如果套接口的读指针当前在带外标志上，则通过第3个参数指向的整数返回一个非零值，否则返回零。
SIOCSPGRP  通过第三个参数指向的整数返回为接收来自这个套接口的SIGIO或SIGURG信号而设置的进程ID
           或进程组ID。
SIOCGPGRP  用第三个参数指向的整数设置进程ID或进程组ID以接收这个套接口的SIGIO或SIGURG信号

2. 文件操作

适用于套接口的请求

FIONBIO    套接口的非阻塞标志会根据ioctl的第三个参数指向的值是否为零而清除或设置。
FIOASYNC   这个标志根据ioctl的第三个参数指向的值是否为零决定清除或接收套接口上的异步IO信号SIGIO
FIONREAD   在ioctl的第三个参数指向的整数里返回套接口接收缓冲区中当前的字节数。这种功能在文件、管道和终端上都能用
FIOSETOWN  在套接口上等价于SIOCSPGRP
FIOGETOWN  在套接口上等价于SIOCGPGRP

3. 接口配置

很多处理网络接口的程序的第一步是从内核获取系统中配置的所有接口。这是通过SIOCGIFCONF请求来实现的。它使用了ifconf结构，ifconf又用了ifreq结构

4. 路由表操作

有两种ioctl请求用来操作路由表:
        SIOCADDRT  向路由表中加一项
        SIOCDELRT  从路由表中删除一项
这两个请求要求ioctl的第三个参数必须是一个指向rtentry结构的指针。只有超级用户才能发出足这些请求。
