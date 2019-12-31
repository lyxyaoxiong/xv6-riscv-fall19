#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int findPrime(int r_fd);

int
main(int argc, char **argv)
{
  if(argc > 1){
    fprintf(2, "usage: primes...\n");
    exit();
  }
  int fds[2];
  int fds_i[2];
  pipe(fds);
  pipe(fds_i);
  int pid = fork();
  if (pid != 0){
    int n = 35 - 2;
    int buf[n];
    for(int i = 2; i <= 35; i++){
      buf[i-2] = i;
    }
    write(fds[1], buf, n);
    // if (read(fds_i[0], buf, 1) == 0)
    //   printf("error when waiting for pipe closure\n");
    // read(fds_i[0], buf, 1);
    // printf("parent received: %d\n", buf[0]);
    if (read(fds_i[0], buf, 0) == 0)
      printf("error when waiting for pipe closure\n");

    printf("parent closing fd\n");
    close(fds_i[0]);
    printf("parent closing middle\n");
    close(fds[1]);
    printf("parent finished.\n");
  } else{
    sleep(30);
    findPrime(fds[0]);
    printf("child closing fd\n");
    // int tmpBuf[] = {0};
    // write(fds_i[1], tmpBuf, 0);
    close(fds_i[1]);
    printf("child closing middle\n");
    close(fds[0]);
    printf("child finished.\n");
  }

  exit();
}

int findPrime(int r_fd){
  int buf[1];
  if (read(r_fd, buf, 1) != 1)
    return 0;
  printf("%d\n", buf[0]);
  return 0;
  // int prime = buf[0];
  // printf("prime %d", prime);
  // int fds[2];
  // pipe(fds);
  // int pid = fork();
  // if (pid != 0) {
  //   while (read(r_fd, buf, 1) == 1) {
  //     if (buf[0] % prime) {
  //       write(fds[1], buf[0], 1);
  //     }
  //   }
  //   close(fds[1]);
  // } else {
  //   findPrime(fds[0]);
  //   close(fds[0]);
  // }
  // return 0;
}
