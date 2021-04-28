#include <stdio.h>
#include <sys/shm.h>
#include <string.h>

int main(int argc, char* argv[])
{
    // 1. 创建共享内存, 大小为4k
    int shm_id = shmget(1000, 4096, IPC_CREAT|0664);
    if(shm_id == -1)
    {
        printf("shmget error!\n");
        return -1;
    }

    // 2. 当前进程和共享内存关联
    void* ptr = shmat(shm_id, NULL, 0);
    if(ptr ==(void*)-1)
    {
        printf("shmat error!\n");
        return -1;
    }

    // 3. 写共享内存
    const char* p = "Good morning my friend!\n";
    memcpy(ptr, p, strlen(p)+1);

    // 阻塞程序
    printf("按任意键继续, 删除共享内存\n");
    getchar();

    // 4. 和共享内存解除关联
    shmdt(ptr);

    // 5. 删除共享内存
    shmctl(shm_id, IPC_RMID, NULL);
    printf("共享内存已经被删除...\n");


    return 0;
}