#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int
main(int argc, char **argv)
{
  int i;

  if(argc < 2 && argc > 3){
    fprintf(2, "usage: sleep time...\n");
    exit();
  }
  sleep(atoi(argv[2]));
  exit();
}
