#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>

int main() {
   
   int set_se = setuid(2);
   if(set_se == -1){
   	perror("Error: setuid(2) ha generado un error");
   	printf("Error: %s\n", strerror(errno));
   }
   return 1;
}
