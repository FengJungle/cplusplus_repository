#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main()
{
    int fd[2];
    char str[256];

    /* Create a one-way communication channel (pipe).
     * If successful, two file descriptors are stored in PIPEDES;
     * bytes written on PIPEDES[1] can be read from PIPEDES[0].
     * Returns 0 if successful, -1 if not.  
    */
    if(pipe(fd) < 0)
    {
        perror("pipe");
        exit(1);
    }

    // fd[0] is used for read
    // fd[1] is used for write

    write(fd[1], "create the pipe successfully!\n", 31);

    read(fd[0], str, sizeof(str));
    
    printf("%s", str);
    printf(" pipe file descriptors are %d, %d \n", fd[0], fd[1]);
    close(fd[0]);
    close(fd[1]);
    return 0;
}