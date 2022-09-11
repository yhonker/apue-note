#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
int main()
{
    pid_t pid;
    if((pid = fork())<0)
        printf("fork error\n");
    else if(pid == 0){
        if(execl("/home/hos/workspace/apue/chp8/testjb", "testjb","myarg1", "MY ARG2", (char*)0)<0)
            printf("execl error\n");
    }
    if(waitpid(pid,NULL,0)<0)
        printf("wait error\n");
    exit(0);
}