#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <string.h>


int main(int argc, char **argv){
	const char *pathname = "pipe_name";
	
	if(mkfifo(pathname, S_IRWXU | S_IRWXG) != -1){
		printf("Pipe created.\n");
	}else{
		printf("Could not create pipe.\n");
		fprintf(stderr, "%s\n", strerror(errno));
		return 1;
	}


	return 0;
}
