#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/sysmacros.h>
#include <time.h>

int main(int argc, char **argv){
  struct stat informacion;
  int info_stat = stat(argv[1], &informacion);
  
  printf("Major: %li\n", (long) major(informacion.st_dev));
  printf("Minor: %li\n", (long) minor(informacion.st_dev));
  printf("Inodo: %li\n", (long) informacion.st_ino);
  printf("Tipo de archivo: %i\n", informacion.st_mode);
  printf("Último Acceso: %s\n", ctime(informacion.st_atime));


  return 0;
}
