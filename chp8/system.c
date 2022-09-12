#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main()
{
    int status;
    if((status = system("date"))<0)
        printf("syste() error\n");
    // pr_exit(status);

    if((status = system("nosuchcommand"))<0)
        printf("syste() error\n");
    // pr_exit(status);

    if((status = system("who; exit 44"))<0)
        printf("syste() error\n");
    // pr_exit(status);
    exit(0);
}