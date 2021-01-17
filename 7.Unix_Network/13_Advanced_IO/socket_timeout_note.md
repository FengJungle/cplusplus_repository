1. 套接口超时
有3种方法给套接口上的IO操作设置超时：
（1）调用alarm，在到达指定时间时产生SIGALARM信号
```
static void connect_alarm(int signo)
{
    return;
}
int conect_timeo(int sockfd, const SA*saptr, socklen_t salen, int nsec)
{
    Sigfunc* sigfunc;
    int n;

    // 为SIGALRM建立信号处理程序
    sigfunc = Signal(SIGALRM, connect_alarm);

    // 设置报警时钟，设定为用户指定的时间nsec
    alarm(nsec);

    // 如果connect被中断（EINTR），则设定为ETIMEDOUT
    if( n = connect(sockfd, (sockaddr*)saptr, salen) < 0)
    {
        close(sockfd);
        if(errno == EINTR)
        {
            errno = ETIMEDOUT;
        }
    }
    alarm(0);
    Signal(SIGALRM, sigfunc);
    return n;
}
```
（2）使用select阻塞在等待的IO上，select的最后一个入口参数可设定超时时间
```
int readable_timeo(int fd, int sec)
{
    fd_set rset;
    struct timeval tv;
    FD_ZERO(&rset);
    FD_SET(fd, &rset);

    tv.tv_sec = sec;
    tv.tv_usec = 0;

    // select最后一个参数设定超时时间
    // 返回值代表可读的套接字个数
    return (select(fd+1, &rset, NULL, NULL, &tv));
}

void dg_cli(FILE* fp, int sockfd, const sockaddr* pservaddr, socklen_t servlen)
{
    int n;
    char sendline[MAXLINE];
    char readline[MAXLINE+1];

    while(fgets(sendline, MAXLINE, fp)!= NULL)
    {
        sendto(sockfd, sendline, strlen(sendline), 0, pservaddr, servlen);
        if(readable_timeo(sockfd, 5) == 0)
        {
            cout<<"socket timeout"<<endl;
        }
        else
        {
            n = recvfrom(sockfd, recvline, MAXLINE, 0, NULL, NULL);
            recvline[n] = 0;
            fputs(recvline, stdout);
        }
    }
}
```
（3）使用setsockopt函数，设定SO_RECVTIMO和SO_SNDTIMEO套接口选项
```
struct timeval tv;
tv.tv_sec = user_set_sec;
tv.tv_usec = user_set_usec;
setsockopt(sockfd, SOL_SOCKET, SO_RCVTIMEO, &tv, sizeof(tv));
```
