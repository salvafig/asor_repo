#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <string.h>

/* ejercicio4 argument */
int main(int argc, char **argv){
	const char *pathname = "pipe_name";
	int pipe_fd;

	if((pipe_fd = open(pathname, O_WRONLY)) == -1){
		fprintf(stderr, "%s\n", strerror(errno));
		return 1;
	}else{
		write(pipe_fd, argv[1], strlen(argv[1]));
	}
	
	/*if(mkfifo(pathname, S_IRWXU | S_IRWXG) != -1){
		printf("Pipe opened.\n");
		if((pipe_fd = open(pathname, O_WRONLY)) == -1){
			fprintf(stderr, "%s\n", strerror(errno));
			return 1;
		}else{
			write(pipe_fd, argv[1], strlen(argv[1]));
		}
		
	}else{
		printf("Could not open pipe.\n");
		fprintf(stderr, "%s\n", strerror(errno));
		return 1;
	}*/


	return 0;
}
