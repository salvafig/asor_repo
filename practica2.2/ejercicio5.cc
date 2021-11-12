#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int main(){
  const char path[]="/pruebaEjercicio5.txt";
  int archivo = open(path, O_CREAT, 645);
  
  return 0;
}
