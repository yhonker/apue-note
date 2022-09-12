## chp6 系统数据文件和信息

### 6.1 /etc/passwd文件

#### struct passwd 结构
```C++
struct passwd{
    char *pw_name; //用户名
    char *pw_passwd;    //加密口令
    uid_t pw_uid;   //数值用户ID
    git_t pw_gid;   //数值组ID
    char *pw_gecos; //注释字段
    char *pw_dir;   //初始工作目录
    char *pw_shell; //初始shell
    char *pw_class; //用户访问类
    time_t pw_change;   //下次更改口令时间
    time_t pw_expire;   //账户有效期时间
}
```
#### getpwuid() getpwnam() 给出用户登录名或数值用户ID后，查看口令文件相关项
```C++
struct passwd *getpwuid(uid_t uid);

struct passwd *getpwnam(const char *name);
```

#### getpwent() 查看整个口令文件
```C++
struct passwd *getpwent(void);

void setpwent(void);

void endpwent(void);
```

### 6.2 /etc/shadow文件
#### struct spwd结构
```C++
struct spwd{
    char *sp_namp;  //用户登录名
    char *sp_pwdp;  //加密口令
    int sp_lstchg;  
    int sp_min; 
    int sp_max;
    int sp_warn;
    int sp_inact;
    int sp_expire;
    unsigned int sp_flag;
}
```

#### 访问shadow文件函数
```C++
struct spwd *getspnam(const char *name);

struct spwd *getspent(void);

void setspent(void);

void endspent(void);
```

### 6.3 /etc/group文件
#### struct group 结构
```C++
struct group{
    char *gr_name;  //组名
    char *gr_passwd;    //加密口令
    int gr_gid; //数值组ID
    char **gr_mem;  //指向各用户名指针的数组
}
```

#### 访问group文件函数
```C++
struct group *getgrgid(gid_t gid);

struct group *getgrnam(const char *name);

struct group *getgrent(void);

void setgrent(void);

void endgrent(void);
```

### 6.4 附属组ID 
#### 获取进程附属组ID，login设置组ID
```C++
int getgroups(int gidsetsize, gid_t grouplist[]);

int setgroups(int ngroups, const gid_t grouplist[]);

int initgroups(const char *username, gid_t basegid);
```

### 6.5 其他数据文件
|  数据文件   | 结构  | 访问函数  |
|  ----  | ----  | ----  |
| /etc/hosts  | hostent | getnameinfo getaddrinfo |
| /etc/networks  | netent | getnetbyname  getnetbyaddr | 
| /etc/protocols  | protoent | getnameinfo  getaddrinfo |
| /etc/services  | servent | getservbyname getservbyport | 


### 6.6 系统标识
#### 获取主机和操作系统有关的信息
```C++
int uname(struct utsname *name);

struct utsname {
    char sysname[ ]; /* name of the operating system */
    char nodename[ ]; /* name of this node */
    char release[ ]; /* current release of operating system*/
    char version[ ]; /* current version of this release */
    char machine[ ]; /* name of hardware type */
};

//获取TCP/IP网络上主机的名字
int gethostname(char *name, i n t namelen);

```

### 6.7 时间和日期例程
#### time() 返回系统秒（日历时间）
```C++
time_t time(time_t *calptr);

int clock_gettime(clockid_t clock_id, struct timespec *tsp);

int clock_getres(clockid_t clock_id, struct timespec *tsp);

int gettimeofday(struct timeval *restrict tp, void *restrict tzp);

//对特定的时钟设置时间
int clock_settime(clockid_t clock_id, const struct timespec *tsp);
```
|  clock_id   |   | 说明  |
|  ----  | ----  | ----  |
| CLOCK_REALTIME  | 实时系统时间 |
| CLOCK_MONOTONIC  | 不带负跳数的实时系统时间 | 
| CLOCK_PROCESS_CPUTIME_ID  | 调用进程的CPU时间 | 
| CLOCK_THREAD_CPUTIME_ID  | 调用线程的CPU时间 | 

#### localtime() 日历转换成分解时间
```C++
struct tm *gmtime(const time_t *calptr);

struct tm *localtime(const time_t *calptr);

//分解时间数据结构
struct　 tm {　　　　 /* a broken-down time */
    int　　tm_sec;　　　 /* seconds after the minute: [0 - 60] */
    int　　tm_min;　　　 /* minutes after the hour: [0 - 59] */
    int　　tm_hour;　　 /* hours after midnight: [0 - 23] */
    int　　tm_mday;　　 /* day of the month: [1 - 31] */
    int　　tm_mon;　　　 /* months since January: [0 - 11] */
    int　　tm_year;　　 /* years since 1900 */
    int　　tm_wday;　　 /* days since Sunday: [0 - 6] */
    int　　tm_yday;　　 /* days since January 1: [0 - 365] */
    int　　tm_isdst;　　/* daylight saving time flag: <0, 0, >0 */
};
```
#### mktime 分解时间转换成日历时间
```C++
time_t mktime(struct tm *tmptr);
```

#### 格式化时间字符串输出
```C++
size_t strftime(char *restrict buf, size_t maxsize,\
const char *restrict format,const struct tm *restrict tmptr);

size_t strftime_l(char *restrict buf, size_t maxsize,\
const char *restrict format,const struct tm *restrict tmptr, locale_t locale);

//exp
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main()
{
    time_t t;
    struct tm *tmp;
    char buf1[16];
    char buf2[64];

    time(&t);
    tmp = localtime(&t);
    if(strftime(buf1, 16, "time and date: %r, %a %b %d, %Y", tmp) == 0)
        printf("buffer length 16 is too small\n");
    else
        printf("%s\n", buf1);
    if(strftime(buf2, 64, "time and date: %r, %a %b %d, %Y", tmp) == 0)
        printf("buffer length 64 is too small\n");
    else
        printf("%s\n", buf2);
    exit(0);
}
```

#### strptime() 字符串转换成分解时间
```C++
char *strptime(const char *restrict buf, const char *restrict format,\
struct tm *restrict tmptr);
```