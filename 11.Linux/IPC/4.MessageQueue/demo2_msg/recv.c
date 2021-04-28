#include <unistd.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

typedef struct{
    char name[20];
    int age;
}Person;

typedef struct{
    long type;    // 首4字节是一个整数!!
    Person person;
}Msg;

void printMsg(Msg* msg)
{
    printf("{ tpye = %ld, name = %s, age = %d }\n",
           msg->type, msg->person.name, msg->person.age);
}

int main(int argc, char* argv[])
{
    if(argc < 2)
    {
        printf("usage %s <type>\n", argv[0]);
        return -1;
    }
    // 获取 ipc 内核对象 id
    int id = msgget(0x8889, 0);

    // 要获取的消息类型
    long type = atol(argv[1]);

    Msg msg;
    int res;

    while(1)
    {
        // 以非阻塞的方式接收类型为 type 的消息, 接收完后该条消息从队列中删除
        res = msgrcv(id, &msg, sizeof(Msg), type, IPC_NOWAIT);

        // 如果消息接收完毕就退出，否则报错并退出
        if(res < 0)
        {
            if(errno == ENOMSG)
            {
                printf("no msg!\n");
                break;
            }
        }
        printMsg(&msg);
    }

    return 0;
}