#include <fcntl.h>
#include <errno.h>
#include <string.h>
#include <stdio.h>
#include <sys/stat.h>


/* ./ejercicio7 */
int main(int argc, char **argv){
	int fd;

	umask(0021);

	if((fd == open("file_practica2.2_ejercicio7", O_CREAT, 0645) == -1)){
		fprintf(stderr, "open: %s\n", strerror(errno));
		return 1;
	}

	return 0;
}
