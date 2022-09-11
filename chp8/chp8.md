## chp8 进程控制

### 8.1 进程标识
#### 返回进程标识符函数
```C++
pid_t getpid(void); //调用进程的进程ID

pid_t getppid(void); //调用进程的父进程ID

uid_t getuid(void); //调用进程的实际用户ID

uid_t geteuid(void); //调用进程的有效用户ID

gid_t getgid(void); //调用进程的实际组ID

gid_t getegid(void); //调用进程的有效组ID
```

### 8.2 函数fork 
#### fork() 创建一个新进程 新子进程copy父进程资源
```C++
pid_t fork(void); //父进程返回子进程id 子进程返回0

//exp
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int globvar = 6;

char buf[] = "a write to stdout\n";

int main()
{
    int var;
    pid_t pid;

    var = 88;
    if(write(STDOUT_FILENO, buf, sizeof(buf)-1) != sizeof(buf)-1)
        printf("write error");
    printf("before fork\n");

    if((pid = fork())<0){
        printf("fork error\n");
    }else if(pid == 0){
        globvar++;
        var++;
    }else{
        sleep(2);
    }
    
    printf("pid = %ld, glob = %d, var = %d\n", (long)getpid(), globvar, var);
    exit(0);

}
```

### 8.3 函数vfork
#### vfork() 
```C++
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>

int globvar = 6; 
int main(void)
{
    int var; 
    pid_t pid;
    var = 88;
    printf("before vfork\n"); 
    if ((pid = vfork()) < 0) {
        perror("vfork error");
    } 
    else if (pid == 0) { 
        globvar++;
        var++;
        _exit(0); 
    }
 
    printf("pid = %ld, glob = %d, var = %d\n", (long)getpid(), globvar,var);
    exit(0);
}

```
### 8.4 wait和waitpid
#### wait() waitpid() 等待子进程终止函数
```C++
pid_t wait(int *statloc);

pid_t waitpid(pid_t pid, int *statloc, int options);

#include <sys/wait.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

void pr_exit(int status){

    if(WIFEXITED(status))
        printf("normal termination, exit status = %d\n", WEXITSTATUS(status));
    else if(WIFSIGNALED(status))
        printf("abnormal termination, signal number=%d%s\n", WTERMSIG(status),
#ifdef WCOREDUMP
                WCOREDUMP(status) ? "(core file generated)" : "");
#else 
        "");
#endif
    else if(WIFSTOPPED(status))
        printf("child stopped, signal number=%d\n", WSTOPSIG(status));

}

void main()
{
    pid_t pid;
    int status;

    if(pid=fork()<0)
        printf("fork error\n");
    else if(pid==0)
        exit(7);
    
    if(wait(&status) != pid)
        printf("wait error\n");
    pr_exit(status);

    if(pid=fork()<0)
        printf("fork error\n");
    else if(pid==0)
        abort();
    
    if(wait(&status) != pid)
        printf("wait error\n");
    pr_exit(status);

    if(pid=fork()<0)
        printf("fork error\n");
    else if(pid==0)
        status /= 0;
    
    if(wait(&status) != pid)
        printf("wait error\n");
    pr_exit(status);

}

//？？有bug不显示
```
#### waitid() 可获得造成子进程状态改变的有关信号详细信息
```C++
int waitid(idtype, id_t id, siginfo_t *infop, int options);
```
### 8.5 函数wait3和wait4
#### wait3() wait4() 可返回终止进程及其子进程的资源状况
```C++
pid_t wait3(int *statloc, int options, struct rusage *rusage);

pid_t wait4(pid_t pid, int *statloc, int options, struct rusage *rusage);
```

### 8.6 竞争条件
```C++
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

static void charatatime(char *);

int main() {
  pid_t pid;

  if ((pid = fork()) < 0) {
    //err_sys("fork error");
  } else if (pid == 0) {
    charatatime("output from child\n");
  } else {
    charatatime("output from parent\n");
  }
  exit(0);
}

static void charatatime(char *str) {
  char *ptr;
  int c;

  setbuf(stdout, NULL);  /* 设置 stdout 为无缓冲 */
  for (ptr = str; (c = *ptr++) != 0;) {
    putc(c, stdout);
  }
}

//??? 有bug

```
```bash
hos@hos-VirtualBox:~/workspace/apue/chp8$ ./a.out 
output from parent
hos@hos-VirtualBox:~/workspace/apue/chp8$ output from child
```

### 8.7 函数exec
#### exec() 用磁盘上的一个新程序替换当前进程的正文段，数据段，堆和栈段。
```C++
int execl(const char *pathname, const char *arg0, ... /* (char *)0 */ );

int execv(const char *pathname, char *const argv[]);

int execle(const char *pathname, const char *arg0, ...

/* (char *)0, char *const envp[] */ );

int execve(const char *pathname, char *const argv[], char *const envp[]);

int execlp(const char *filename, const char *arg0, ... /* (char *)0 */ );

int execvp(const char *filename, char *const argv[]);

int fexecve(int fd, char *const argv[], char *const envp[]);
```
```C++
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
```
### 8.8 更改用户ID和更改组ID
#### 
```C++
//设置实际用户和组ID与有效用户和组ID
int setuid(uid_t uid);

int setgid(gid_t gid);

//交换实际用户ID和有效用户ID的值
int setreuid(uid_t ruid, uid_t euid);

int setregid(gid_t rgid, gid_t egid);

//但只更改有效用户ID和有效组ID
int seteuid(uid_t uid);

int setegid(gid_t gid);
```

### 8.9 解释器文件
```C++
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

//有bug
```