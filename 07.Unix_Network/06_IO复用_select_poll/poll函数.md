# poll函数
使用select函数可以处理socket多连接的问题使用POLL也可以实现同样的功能，且调用方式更加简单。原型是：
```
struct pollfd {  
    int fd;        //文件描述符  
    short events;  //要求查询的事件掩码  
    short revents; //返回的事件掩码  
};  

int poll(struct pollfd *ufds, unsigned int nfds, int timeout);  
```
#### 参数ufds
poll函数使用pollfd类型的结构来监控一组文件句柄，ufds是要监控的文件句柄集合
#### 参数nfds
nfds是监控的文件句柄数量
#### 参数timeout
timeout是等待的毫秒数，这段时间内无论I/O是否准备好，poll都会返回。
- timeout为INFTIM：表示无限等待
- timeout为0：表示调用后立即返回
- timeout > 0：表示调用后等待指定的毫秒数

#### 执行结果
- 0：表示超时前没有任何事件发生
- -1：表示失败；
- 成功则返回结构体中revents不为0的文件描述符个数。

## pollfd结构监控的事件类型
```
#define POLLIN 0x0001  
#define POLLPRI 0x0002  
#define POLLOUT 0x0004  
#define POLLERR 0x0008  
#define POLLHUP 0x0010  
#define POLLNVAL 0x0020  
    
#define POLLRDNORM 0x0040  
#define POLLRDBAND 0x0080  
#define POLLWRNORM 0x0100  
#define POLLWRBAND 0x0200  
#define POLLMSG 0x0400  
#define POLLREMOVE 0x1000  
#define POLLRDHUP 0x2000  
```

如上是events事件掩码的值域，POLLIN|POLLPRI类似于select的读事件，POLLOUT|POLLWRBAND类似于select的写事件。当events属性为POLLIN|POLLOUT，表示监控是否可读或可写。在poll返回时，即可通过检查revents变量对应的标志位与events是否相同，比如revents中POLLIN事件标志位被设置，则表示文件描述符可以被读取。代码段示例：
```
int sockfd;				//套接字句柄
struct pollfd pollfds;
int timeout;
 
timeout = 5000;
pollfds.fd = sockfd;				//设置监控sockfd
pollfds.events = POLLIN|POLLPRI;			//设置监控的事件
 
for(;;){
	switch(poll(&pollfds,1,timeout)){		//开始监控
	case -1:					//函数调用出错
		printf("poll error \r\n");
	break;
	case 0:
		printf("time out \r\n");
	break;
	default:					//得到数据返回
		printf("sockfd have some event \r\n");
		printf("event value is 0x%x",pollfds.revents);
	break;
	}
} 

```