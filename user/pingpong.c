#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int
main(int argc, char **argv)
{
  if(argc > 1){
    fprintf(2, "usage: pingpong...\n");
    exit();
  }
  
  int n = 1;
  char buf[10];
  int fds[2];
  if (pipe(fds) != 0)
    fprintf(2, "error in opening a pipe...\n");
  if (fork() != 0)
  {
    char byte_sent[] = {"0"};
    printf("parent process writing one byte to child process...");
    write(fds[1], byte_sent, n);
    sleep(30);
    printf("parent process waiting for response...");
    if (n != read(fds[0], buf, n))
      fprintf(2, "error when parent process is waiting for response...");
    printf("parent process received %c, expected %c", buf[0], byte_sent[0]);
  } else
  {
    if (n != read(fds[0], buf, n))
      fprintf(2, "error when child process is waiting for response...");
    printf("child process received %c", buf[0]);
    sleep(30);
    printf("child process writing one byte to parent process...");
    write(fds[1], buf[0], n);
  }

  exit();
}
