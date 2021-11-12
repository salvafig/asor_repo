#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int main(){
  mode_t modo1 = umask(027)
  const char path[]="/pruebaEjercicio7.txt";
  int archivo = open(path, O_CREAT | O_RDONLY, 0777);
  mode_t modo2 = umask(modo1)
  
  return 0;
}
