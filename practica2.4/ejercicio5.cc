#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/select.h>



int main(int argc, char **argv){
	const char *pathname1 = "pipe_name_5";
	const char *pathname2 = "pipe_name";
	int fd_1;
	int fd_2;
	int fd_highest;
	char buffer[256];
	fd_set rfds;

	while(1){
		fd_1 = open(pathname1, O_NONBLOCK);
		fd_2 = open(pathname2, O_NONBLOCK);
		fd_highest = fd_1;
		if(fd_1 < fd_2){
			fd_highest = fd_2;
		}
		
		FD_ZERO(&rfds);
		FD_SET(fd_1, &rfds);
		FD_SET(fd_2, &rfds);

		select(fd_highest+1, &rfds, 0, 0, 0);

		if(FD_ISSET(fd_1, &rfds)){
			int bytes = read(fd_1, buffer, 255);
			if(bytes == 0){
				close(fd_1);			
			}
			printf("Tuberia: %s, Datos: %s\n", pathname1, buffer);
		}else if(FD_ISSET(fd_2, &rfds)){
			int bytes = read(fd_2, buffer, 255);
			if(bytes == 0){
				close(fd_2);			
			}
			printf("Tuberia: %s, Datos: %s\n", pathname2, buffer);
		}
	}



		

	return 0;
}
