#include <fcntl.h>
#include <string.h>
#include <errno.h>
#include <stdio.h>
#include <sys/stat.h>


/* ./ejercicio5 */
int main(int argc, char **argv){

	//int fd = open("file_practica2.2_ejercicio5", O_CREAT, 0645);
	int fd = open("file_practica2.2_ejercicio5", O_CREAT, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH | S_IXOTH);
	if(fd == -1){
		fprintf(stderr, "open: %s\n", strerror(errno));
		return 1;
	}

	return 0;
}
