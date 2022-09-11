## chp7 进程环境

### 7.1 进程终止

#### exit() _exit() _Exit() 
```C++
_exit和_Exit立即进入内核，exit则先执行一些清理处理，然后返回内核
void exit(int status);

void _Exit(int status);

void _exit(int status);

status:退出（终止）状态

exit(1) 等价 return 1
```

#### atexit() 进程调用atexit注册exit后处理函数（最多注册32个）
```C++
int atexit(void (*func)(void));

//exp
#include <stdio.h>
#include <stdlib.h>

static void my_exit1(void);

static void my_exit2(void);

int main(void)
{
    if(atexit(my_exit2) != 0)
        printf("can't register my_exit2\n");
    
    if(atexit(my_exit1) != 0)
        printf("can't register my_exit1\n");
    if(atexit(my_exit1) != 0)
        printf("can't register my_exit1\n");

    printf("main is done\n");
    return(0);
}

static void my_exit1(void)
{
    printf("first exit handler\n");
}

static void my_exit2(void)
{
    printf("second exit handler\n");
}
```

### 7.2 命令行参数
#### 调用exec的进程可将命令行参数传递给该新程序
```C++
#include <stdio.h>
#include <stlib.h>

int main()
{
    int i;
    for(i=0; i<argc; i++)
        printf("argv[%d]: %s\n", i, argv[i]);
    exit(0);    
}
```
### 7.3 环境表
#### environ 环境指针
```C++
extern char **environ;
```

### 7.4 C程序的存储空间布局
```C++
1. 正文段: CPU执行的机器指令部分
2. 初始化数据段: 数据段 例如C程序中任何函数之外的声明 int maxcount = 99; 
3. 未初始化数据段（bss段）: 例如函数外的声明 long sum[1000];
4. 栈: 自变量和每次函数调用时所需保存的信息都存放在此段中。
5. 堆: 用于动态存储分配

``` 
|  典型存储空间安排   |   | 
|  ----  | ----  | 
| (高地址)命令行参数和环境变量 | 
| 栈  | 
| mem |
| mem |
| mem |
| mem |
| 堆 |
| 未初始化的数据(bss) |
| 初始化的数据 |
| (低地址)正文段 |


### 7.5 存储空间分配
#### 存储空间动态分配和释放函数
```C++
void *malloc(size_t size); //分配指定字节数的存储区，未初始化

void *calloc(size_t nobj, size_t size); //为指定数量指定长度的对象分配存储空间，每一位初始化为0

void *realloc(void *ptr, size_t newsize);   //增加或减少以前分配区的长度

void free(void *ptr); //释放空间送至可用存储区池
```

### 7.9 环境变量

#### getenv() 取环境变量值
```C++
char *getenv(const char *name);

```

#### 设置环境变量
```C++
int putenv(char *str);

int setenv(const char *name, const char *value, int rewrite);

int unsetenv(const char *name);
```

### 7.10 函数setjmp和longjmp
#### 非局部goto
```C++
int setjmp(jmp_buf env);

void longjmp(jmp_buf env, int val);

env: 其中存放在调用 longjmp 时能用来恢复栈状态的所有信息

//exp
#include <stdio.h>
#include <setjmp.h>
#include <stdlib.h>

static void f1(int, int, int, int);
static void f2(void);

static jmp_buf jmpbuffer;
static int globval;

int main()
{
    int autoval;
    register int regival;
    volatile int volaval;
    static int statval;

    globval = 1; autoval = 2; regival = 3; volaval =4; statval = 5;

    if(setjmp(jmpbuffer) != 0){
        printf("after longjmp:\n");
        printf("globval = %d, autoval = %d, regikval = %d, volaval = %d, statval = %d\n", globval, autoval, regival, volaval, statval);
        exit(0);
    }
    globval = 95; autoval = 96; regival = 97; volaval = 98;
    statval = 99;
    f1(autoval, regival, volaval, statval);
    exit(0);
}

static void f1(int i, int j, int k, int l)
{
    printf("in f1():\n");
    printf("globval = %d, autoval = %d, regikval = %d, volaval = %d, statval = %d\n", globval, i, j, k, l);
    f2();
}

static void f2(void)
{
    longjmp(jmpbuffer, 1);
}
```


### 7.11 函数getrlimit和setrlimit

#### getrlimit() setrlimit() 查询和更改资源限制
```C++
int getrlimit(int resource, struct rlimit *rlptr);

int setrlimit(int resource, const struct rlimit *rlptr);
```