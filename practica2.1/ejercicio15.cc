#include <string.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/time.h>
#include <time.h>




int main(){
	char date_and_time[200];
	struct timeval tv;
	struct tm *today;

	gettimeofday(&tv, NULL);

	today = localtime(&tv.tv_sec);
	if (strftime(date_and_time, sizeof(date_and_time), "%c", today) != 0) {
		 printf("Date and time: \"%s\"\n", date_and_time);
           }
           
        return 1;

}
