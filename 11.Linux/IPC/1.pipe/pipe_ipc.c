#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <limits.h>

int main(int argc, char* argv[])
{
    int fd[2];
    char buf[256];
    pid_t pid;
    ssize_t len;

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

    // create a child process
    if( (pid = fork())<0)
    {
        perror("failed to fork");
        exit(1);
    }
    else if(pid > 0) // parent process
    {
        // parent close read fd
        close(fd[0]);
        write(fd[1], "Hello my son!\n", 14);
        exit(0);
    }
    else // child process
    {
        // child close write fd
        close(fd[1]);
        len = read(fd[0], buf, 256);
        if(len < 0)
        {
            perror("process failed when read a pipe!");
            exit(1);
        }

        // #define	STDIN_FILENO	0	/* Standard input.  */
        // #define	STDOUT_FILENO	1	/* Standard output.  */
        // #define	STDERR_FILENO	2	/* Standard error output.  */
        write(STDOUT_FILENO, buf, len);
        exit(0);
    }
    return 0;
}