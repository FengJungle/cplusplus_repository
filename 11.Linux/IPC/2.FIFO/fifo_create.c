#include <sys/types.h>
#include <sys/stat.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>

#define FILE_NAME "fifo1"

int main(int argc, char* argv[])
{
    // default right: read and write, but no execute right
    mode_t mode = 666;

    // Create a new FIFO named PATH, with permission bits MODE
    if((mkfifo(FILE_NAME, mode))<0)
    {
        perror("failed to mkfifo!");
        exit(1);
    }
    else
    {
        printf("Successfully create a FIFO name is %s\n", FILE_NAME);
    }

    // try to create a second fifo with the same file name 
    // return EEXIST
    if((mkfifo(FILE_NAME, mode))<0)
    {
        perror("failed to mkfifo!");
        exit(1);
    }
    else
    {
        printf("Successfully create a second FIFO name is %s\n", FILE_NAME);
    }

    return 0;
}