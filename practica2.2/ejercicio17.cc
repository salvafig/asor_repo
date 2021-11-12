#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/sysmacros.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>
#include <dirent.h>

int main(int argc, char **argv){
  DIR *directorio = opendir(argv[1]);
  struct dirent *curr;
  struct stat informacion;
  
  entrada = readdir(directorio);
  while(entrada != NULL){
    char *path = malloc(strlen(argv[1])*sizeof(char) + strlen(entrada->d_name) + 3));
    strcpy(path, argv[1]);
    strcat(path, "/");
    strcat(path, entrada->d_name);
    resultado = stat(path, &informacion);
    
    if(S_ISREG(informacion.st_mode)){
      printf("%s \n", entrada->d_name);
    }else if(S_ISDIR(informacion.st_mode)){
      printf("%s/ \n", entrada->d_name);
    }else if(S_ISLNK(info.st_mode)){
      char *nombre = malloc(informacion.st_size + 1);
      readlink(path, nombre, informacion.st_size + 1);
      printf("%s->%s \n", entrada->d_name, nombre);
      free(nombre);
    }else if(resultado == 0 && informacion.st_mode & S_IXUSR){
      printf("%s* \n", entrada->d_name);
    }
    
    free(path);
    entrada = readdir(directorio);
  }
  
  closedir(directorio);

  return 0;
}
