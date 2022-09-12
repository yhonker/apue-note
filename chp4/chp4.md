## chp4 文件和目录

### 4.1 stat() 获取文件有关的信息结构系列函数（存于struct stat结构中）
```C++
int stat(const char *restrict pathname, struct stat *restrict buf);

int fstat(int fd, struct stat* buf);

int lstat(const char *restrict pathname, struct stat *restrict buf);

int fstatat(int fd, const char *restrict pathname, struct stat *restrict buf, int flag);
```

### 4.2 struct stat结构解析
```C++
struct stat {
    mode_t　　　　　　　 st_mode;　　 /* file type & mode (permissions) */
    ino_t　　　　　　　　st_ino;　　　 /* i-node number (serial number) */
    dev_t　　　　　　　　st_dev;　　　 /* device number (file system) */
    dev_t　　　　　　　　st_rdev;　　 /* device number for special files */
    nlink_t　　　　　　　st_nlink;　　/* number of links */
    uid_t　　　　　　　　st_uid;　　　 /* user ID of owner */
    gid_t　　　　　　　　st_gid;　　　 /* group ID of owner */
    off_t　　　　　　　　st_size;　　 /* size in bytes, for regular files */
    struct timespec　　 st_atime;　　/* time of last access */
    struct timespec　　 st_mtime;　　/* time of last modification */
    struct timespec　　 st_ctime;　　/* time of last file status change */
    blksize_t　　　　　　st_blksize;　/* best I/O block size */
    blkcnt_t　　　　　　 st_blocks;　 /* number of disk blocks allocated */
};
```

#### (mode_t)st_mode成员
文件类型位(7种)

|  文件类型   | 判别宏  |
|  ----  | ----  |
| 普通文件  | S_ISREC() |
| 目录文件  | S_ISDIR() |
| 块特殊文件  | S_ISBLK() |
| 字符特殊文件  | S_ISCHR() |
| 管道或FIFO  | S_ISFIFO() |
| 套接字  | S_ISSOCK() |
| 符号链接  | S_ISLINK() |


文件权限位（9种）
|  常量   | 含义  |
|  ----  | ----  |
| S_IRUSR  | 用户读 |
| S_IWUSR  | 用户写 |
| S_IXUSR  | 用户执行 |
| S_IRGRP  | 组读 |
| S_IRGWP  | 组写 |
| S_IRGXP  | 组执行 |
| S_IROTH  | 其他读 |
| S_IWOTH  | 其他写 |
| S_IXOTH  | 其他执行 |


执行时设置ID权限位（2种）
|  常量   | 含义  |
|  ----  | ----  |
| S_ISUID  | 执行时设置用户ID |
| S_ISGID  | 执行时设置组ID |


其他权限位
粘着位

#### st_uid和st_gid成员

st_uid指定文件用户ID
\
st_gid指定文件组ID

#### st_size成员
文件长度

#### st_nlink成员
链接记数

#### st_mtim st_atim st_ctim成员


### 4.3 access() 按进程实际用户ID组ID测试访问权限系列函数
```C++
int access(const char *pathname, int mode);

int faccessat(int fd, const char *pathname, int mode, int flag);
```
|  mode   | 含义  |
|  ----  | ----  |
| R_OK  | 测试读权限 |
| W_OK  | 测试写权限 |
| X_OK  | 测试执行权限 |

```C++
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
```

### 4.4 umask() 为进程设置文件模式创建屏蔽字
```C++
mode_t umask(mode_t cmask); #返回之前的文件模式创建屏蔽字

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
```
|  屏蔽位（8进制）   | 含义  |
|  ----  | ----  |
| 0400  | 用户读 |
| 0200  | 用户写 |
| 0100  | 用户执行 |
| 0040  | 组读 |
| 0020  | 组写 |
| 0010  | 组执行 |
| 0004  | 其他读 |
| 0002  | 其他写 |
| 0001  | 其他执行 |

exp：027 阻止同组成员写你的文件以及其他用户读、写或执行你的文件

### 4.5 chmod() 更改现有文件的访问权限
```C++
int chmod(const char *pathname, mode_t mode);

int fchmod(int fd, mode_t mode);
```
|  mode   | 说明  |
|  ----  | ----  |
| S_ISUID  | 执行时设置用户ID |
| S_ISGID  | 执行时设置组ID |
| S_ISVTX  | 黏着位|
| S_IRUSR  | 用户读 |
| S_IWUSR  | 用户写 |
| S_IXUSR  | 用户执行 |
| S_IRGRP  | 组读 |
| S_IRGWP  | 组写 |
| S_IRGXP  | 组执行 |
| S_IROTH  | 其他读 |
| S_IWOTH  | 其他写 |
| S_IXOTH  | 其他执行 |

```C++
#include <stdio.h>
#include <sys/stat.h>

int main()
{
    struct stat statbuf;
    if(stat("foo", &statbuf) < 0)
        printf("stat error\n");
    if(chmod("foo", (statbuf.st_mode & ~S_IXGRP) | S_ISGID) < 0)
        printf("chmod error\n");
    // if(chmod("bar", 0777) < 0 )
    if(chmod("bar", S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH) < 0 )
        printf("chmod error for bar\n");
    return 0;
}
```

### 4.6 chown() 更改文件的用户ID和组ID
```C++
int chown(const char *pathname, uid_t owner, gid_t group);

```

### 4.7 文件系统


### 4.8 link() 链接操作系列函数
```C++
int link(const char *existingpath, const char *newpath);

int unlink(const char *pathname);
```

#### rename() 文件和目录重命名
```C++
int rename(const char *oldname, const char *newname);

```

### 4.9 symlink() readlink() 创建和读取链接
```C++
int symlink(const char *actualpath, const char *sympath);

ssize_t readlink(const char *restrict pathname, char *restrict buf,

size_t bufsize);
```
#### 4.10 mkdir() rmdir() 创建删除目录
```C++
int mkdir(const char *pathname, mode_t mode);

int rmdir(const char *pathname);
```

#### 4.11 目录操作相关函数
```C++
DIR *opendir(const char *pathname);

DIR *fdopendir(int fd);

struct dirent *readdir(DIR *dp);

void rewinddir(DIR *dp);

int closedir(DIR *dp);

long telldir(DIR *dp);

void seekdir(DIR *dp, long loc);
```

#### 4.12 chdir() 改变进程的工作目录
```C++
int chdir(const char *pathname);

int fchdir(int fd);
```
#### 4.13 获得工作目录完整路径
```C++
char *getcwd(char *buf, size_t size);
```
