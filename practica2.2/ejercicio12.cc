#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/sysmacros.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>

int main(int argc, char **argv){
  int archivo1 = open(argv[1], O_CREAT | O_RDWR, 00777);
  int archivo2 = dup2(archivo1, 1);
  dup2(archivo2, archivo1);

  return 0;
}
