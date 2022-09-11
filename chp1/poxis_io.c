#include <unistd.h>
#include <stdio.h>
#define BUFFSIZE 4096

/*
    无缓冲IO，自定义BUFFSIZE
    ssize_t read(int fd,void*buf,size_t count)
    ssize_t write(int fd,void*buf,size_t count)
*/

int main()
{
    int n;
    char buf[BUFFSIZE];

    while((n =  read(STDIN_FILENO, buf, BUFFSIZE))){
        if(write(STDOUT_FILENO, buf, n) != n)
        printf("write error\n");
    }
    
    if(n<0)
        printf("read error\n");

}