#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

static void charatatime(char *);

int main() {
  pid_t pid;

  if ((pid = fork()) < 0) {
    printf("fork error\n");
  } else if (pid == 0) {
    //WAIT_PARENT();
    charatatime("output from child\n");
  } else {
    charatatime("output from parent\n");
    //TELL_CHILD(pid);
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

//???