/*
    测试access()
*/

#include <stdio.h>
#include <unistd.h>
int main(int argc, char *argv[])
{
    printf("argc num: %d\n", argc);

    if(argc != 2)
        printf("error1\n");
    if(access(argv[1], R_OK) < 0)
        printf("error2\n");
    else
        printf("read access OK\n");
    if (open(argv[1], O_RDONLY) < 0)
        printf("open error\n");
    else
        printf("open OK\n");
    return 0;
}