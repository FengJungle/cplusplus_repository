#include <sys/mman.h>
#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

int main(int argc, char* argv[])
{
    // 1. 打开一个磁盘文件
    int fd = open("./file.txt", O_RDWR);
    printf("fd = %d\n", fd);
    
    // 2. 创建内存映射区 
    void* ptr = mmap(NULL, 4000, PROT_READ|PROT_WRITE, MAP_SHARED, fd, 0);
    if(ptr == MAP_FAILED)
    {
        printf("mmap failed!\n");
        return -1;
    }

    // 3. fork a child process
    pid_t pid = fork();
    if(pid > 0)
    {
        // parent process: write data
        const char* str = "I am your father, this is written to you!";
        memcpy(ptr, str, strlen(str) + 1);
    }
    else if(pid == 0) // child process
    {
        usleep(1000);
        printf("Father said:%s\n", (char*)ptr);
    }

    // 4. Release mmap
    munmap(ptr, 4000);

    return 0;
}