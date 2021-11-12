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
  int archivo = open(argv[1], O_CREAT | O_RDWR, 00777);
  struct flock lock;
  lock.l_type = F_UNLCK;
  lock.l_whence = SEEK_SET;
  lock.l_start = 0;
  lock.l_len = 0;
  lock.l_pid = getpid();
  int status = fcntl(archivo, F_GETLK, &lock);
  
  if(lock.l_type != F_UNLCK){
    close(archivo);
    return 1;
  }else{
    lock.l_type = F_WRLCK;
    lock.l_whence = SEEK_SET;
    lock.l_start = 0;
    lock.l_len = 0;
    lock.l_pid = getpid();
    
    time_t tiempo = time(NULL);
    struct tm *tm = localtime(&tiempo);
  
    fcntl(archivo, F_GETLK, &lock);
    
    char* buffer_hora;
    strcpy(buffer_hora, tm->tm_hour);
    buffer_hora = strcat(buffer_hora, " ");
    buffer_hora = strcat(buffer_hora, tm->tm_min);
    
    write(archivo, &buffer_hora, strlen(buffer_hora));
    sleep(30);
    
    lock.l_type = F_WRLCK;
    lock.l_whence = SEEK_SET;
    lock.l_start = 0;
    lock.l_len = 0;
    lock.l_pid = getpid();
    fcntl(archivo, F_GETLK, &lock);
    close(archivo);
  }


  return 0;
}
