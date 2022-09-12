#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

char *env_init[] = {"USER=unknown", "PATH=/tmp", NULL};

int main()
{
    pid_t pid;
    if((pid = fork())<0){
        printf("fork error\n");
    }else if(pid==0){
        if(execle("/bin/echo","echo", "myarg1","MY ARG2",(char*)0,env_init)<0)
            printf("execle error\n");
    }
    if(waitpid(pid,NULL,0)<0)
        printf("wait error\n");
    
    if((pid = fork())<0){
        printf("fork error");
    }else if(pid==0){
        if(execlp("echo","echo", "only one arg", (char*)0)<0)
            printf("execlp error");
    }
    exit(0);
}