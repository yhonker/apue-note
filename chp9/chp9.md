## chp 9 进程关系

### 9.1 终端登录
```bash
init --> fork() --> init --> exec() --> getty() --> exec() --> login()
``` 
#### 9.2 网络登录
```C++
init --> fork() --> exec() --> inetd(监听TCP请求) --> fork() --> inetd --> exec() --> telnetd -->exec() --> login() --> shell
```

#### 9.3 进程组
```C++
//获取和设置进程组ID
pid_t getpgrp(void);

pid_t getpgid(void);

int setpgid(pid_t pid, pid_t pgid);
```

#### 9.4 会话
```C++
//创建新会话，调用进程为首进程
pid_t setsid(void);
//获取pid进程的会话首进程组ID
pid_t getsid(pid_t pid);
```

#### 9.5 函数tcgetpgrp tcsetpgrp tcgetsid
```C++
//返回前台进程组ID
pid_t tcgetpgrp(int fd);
//设置前台进程组ID为 pgrpid
int tcsetpgrp(int fd, pid_t pgrpid);
//给出控制tty文件描述符，返回首进程组ID
pid_t tcgetsid(int fd);
```