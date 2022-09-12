#include <stdio.h>
#include <sys/stat.h>
#include <fcntl.h>

#define RWRWRW (S_IRUSR|S_IWUSR|S_IRGRP|S_IWGRP|S_IROTH|S_IWOTH)

int main()
{
    umask(0);
    if(creat("foo", RWRWRW) < 0)
        printf("create error1\n");
    umask(S_IRGRP|S_IWGRP|S_IROTH|S_IWOTH);
    if (creat("bar", RWRWRW)<0)
        printf("create error2\n");
    return 0;
}