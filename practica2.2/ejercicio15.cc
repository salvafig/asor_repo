#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <iostream>


/* ./ejercicio15 file_name */
int main(int argc, char **argv){
	int fd;
	int lock;
	time_t t;
	struct tm *tm;

	if((fd == open(argv[1], O_CREAT | O_RDWR)) == -1){
		fprintf(stderr, "open: %s\n", strerror(errno));
		return 1;
	}

	lock = lockf(fd, F_TLOCK, 0);

	if(lock == -1){
		fprintf(stderr, "lockf_1: %s\n", strerror(errno));
		return 1;
	}

	//Mostrar Hora Actual
	t = time(NULL);
	tm = localtime(&t);
	printf("%d:%d:%d\n", tm->tm_hour, tm->tm_min, tm->tm_sec);

	sleep(10);
	if(lockf(fd, F_ULOCK, 0) == -1){
		fprintf(stderr, "lockf_2: %s\n", strerror(errno));
		return 1;
	}

	sleep(10);
	
	return 0;
}
