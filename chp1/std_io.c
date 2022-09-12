#include <stdio.h>
#include <stdlib.h>
/*
    带缓冲IO
    int getc(FILE *stream)
    int putc(int char, FILE *stream)
*/


int main()
{
    int c;
    while((c = getc(stdin)) != EOF){
        if(putc(c, stdout) == EOF)
            printf("output error\n");
    }

    
    if (ferror(stdin))
        printf("input errpr\n");
    
    exit(0);
        
}