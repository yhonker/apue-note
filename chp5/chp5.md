## chp5 标准IO

#### 5.1 fwide() 设置流的定向
```C++
int fwide(FILE *fp, int mode);
```

#### 5.2 setbuf() setvbuf() 更改流缓冲类型
```C++
void setbuf(FILE *restrict fp, char *restrict buf);

int setvbuf(FILE *restrict fp, char *restrict buf, int mode, size_t size);
```
|  mode   | 说明  |
|  ----  | ----  |
| _IOFBF  | 全缓冲 |
| _IOLBF  | 行缓冲 |
| _IONBF  | 不带缓冲 |

#### 5.3 冲洗流
```C++
int fflush(FILE *fp);
```
#### 5.4 fopen() fclose() 打开关闭一个标准I/O流
```C++
FILE *fopen(const char *restrict pathname, const char *restrict type);

FILE *freopen(const char *restrict pathname, const char *restrict type, FILE *restrict fp);

FILE *fdopen(int fd, const char *type);

int fclose(FILE *fp);
```
|  type   | 说明  |
|  ----  | ----  |
| r或rb  | 为读而打开 |
| w或wb  | 把文件截至0长，或为写而创建 |
| a或ab  | 追加：为在文件尾写而打开，或为写而创建 |
| r+或r+b或rb+  | 为读和写而打开 |
| w+或w+b或wb+  | 把文件截至0长，或为读和写而创建 |
| a+或a+b或ab+  | 为在文件尾读和写而打开或创建 |

#### 5.5 一次读和写一个字符IO
```C++
int getc(FILE *fp);

int fgetc(FILE *fp);

int getchar(void);

int putc(int c, FILE *fp);

int fputc(int c, FILE *fp);

int putchar(int c);
```
#### 5.6 一次读和写一行IO
```C++
char *fgets(char *restrict buf, int n，FILE *restrict fp);

char *gets(char *buf);

int fputs(const char *restrict str, FILE *restrict fp);

int puts(const char *str);
```

#### 5.7 二进制IO
```C++
size_t fread(void *restrict ptr, size_t size, size_t nobj, FILE *restrict fp);

size_t fwrite(const void *restrict ptr, size_t size, size_t nobj, FILE *restrict fp);

exp1:
    float data[10];
    if (fwrite(&data[2], sizeof(float), 4, fp) != 4)
    err_sys("fwrite error");

exp2:
    struct {
        short count;
        long　　total;
        char　　name[NAMESIZE];
    } item;
    if (fwrite(&item, sizeof(item), 1, fp) != 1)
    err_sys("fwrite error");


```

#### 5.8 定位流
```C++
long ftell(FILE *fp);

int fseek(FILE *fp, long offset, int whence);

void rewind(FILE *fp);
```
|  whence   | 含义  |
|  ----  | ----  |
| SEEK_SET  | 从文件的起始位置开始 |
| SEEK_CUR  | 从当前文件位置开始 |
| SEEK_END | 从文件的尾端开始 |

#### 5.9 格式化IO
```C++
int printf(const char *restrict format, ...);

int fprintf(FILE *restrict fp, const char *restrict format, ...);

int dprintf(int fd, const char *restrict format, ...);

int sprintf(char *restrict buf, const char *restrict format, ...);

int snprintf(char *restrict buf, size_t n, const char *restrict format, ...);

int scanf(const char *restrict format, ...);

int fscanf(FILE *restrict fp, const char *restrict format, ...);

int sscanf(const char *restrict buf, const char *restrict format, ...);
```

#### 5.10 fileno() 获取与流对应的文件描述符
```C++
int fileno(FILE *fp);
```

#### 5.11 内存流
