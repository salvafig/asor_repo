#include <string.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/time.h>
#include <time.h>




int main(){
	struct timeval tv;
	struct tm *today;

	gettimeofday(&tv, NULL);

	today = localtime(&tv.tv_sec);
	printf("Year %d\n", today->tm_year + 1900); 
}
