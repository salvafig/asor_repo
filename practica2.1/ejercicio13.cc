#include <string.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/time.h>




int main(){
	struct timeval start;
	struct timeval end;

	gettimeofday(&start, NULL);
	
	for(int i = 0; i < 1000000; i++){
	
	}
	
	gettimeofday(&end, NULL);
	
	unsigned long start_microseconds = 1000000*start.tv_sec + start.tv_usec;
	unsigned long end_microseconds = 1000000*end.tv_sec + end.tv_usec;
	
	printf("Time spent in the loop: %ld microsec\n", end_microseconds - start_microseconds);

        return 1;
}
