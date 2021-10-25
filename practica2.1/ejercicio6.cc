#include <string.h>
#include <unistd.h>
#include <stdio.h>



int main(){
	printf("Maximum length of the arguments:  %ld\n", sysconf(_SC_ARG_MAX));
	printf("Maximum number of simultaneous processes per user ID: %ld\n", sysconf(_SC_CHILD_MAX));
	printf("Maximum number of files:  %ld\n", sysconf(_SC_OPEN_MAX));

	return 1;
}
