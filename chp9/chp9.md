## chp 9 进程关系

### 9.1 终端登录
```bash
init --> fork() --> init --> exec() --> getty() --> exec() --> login()
``` 