#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>
#include <stdlib.h>
#define MAXLINE 4096

/*
    char *fgets(char *s, int size, FILE *stream);
    int execlp(const char* file,const char* arg,...);
    pid_t waitpid (pid_t pid, int* statusp, int options); https://blog.csdn.net/weixin_45227610/article/details/122841209
*/

int main(void)
{
    char buf[MAXLINE];
    pid_t pid;
    int status;

    printf("%%");
    while(fgets(buf, MAXLINE, stdin) != NULL){
        buf[strlen(buf) - 1] = 0;
        
        if((pid == fork()) < 0)
            printf("fork error\n");
        else if(pid == 0){ //child
            execlp(buf, buf, (char*)0);
            printf("couldn't execute: %s\n", buf);
            exit(127);
        }

        // parent
        if((pid = waitpid(pid, &status, 0)) < 0)
            printf("waitpid error\n");
        printf("%% ");
    }

    exit(0);
}