#include <string.h>
#include <unistd.h>
#include <stdio.h>
#include <time.h>




int main(){
	time_t segundos;
     
	segundos = time(NULL);
	printf("Time in seconds since Epoch= %ld\n", segundos);

        return 1;
}
