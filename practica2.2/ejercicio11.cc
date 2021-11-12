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
  struct stat informacion;
  int info_stat = stat(argv[1], &informacion);
  
  mode_t modo = informacion.st_mode;
  
  if(S_ISREG(modo)){
    char* hard_link = malloc(sizeof(char)*(5 + strlen(argv[1])));
    char* sym_link = malloc(sizeof(char)*(5 + strlen(argv[1])));
    strcpy(hard_link, argv[1]);
    hard_link = strcat(hard_link, ".hard");
    strcpy(sym_link, argv[1]);
    sym_link = strcat(sym_link, ".sym");
    
    link(argv[1], hard_link);
    symlink(argv[1], sym_link);
    printf("Es un archivo regular");
  }else{
    printf("No es un archivo regular");
  }


  return 0;
}
