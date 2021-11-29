#include <unistd.h> 
#include <stdio.h> 
#include <errno.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>


/* ./ejercicio1 comando1 argumento1 | comando2 argumento2 */
int main(int argc, char **argv){
	pid_t pid;
	int fd[2];
	
	if(pipe(fd) == -1){
		fprintf(stderr, "%s\n", strerror(errno));
	}

	pid = fork();

	switch(pid){
		case -1:
			fprintf(stderr, "%s\n", strerror(errno));
			exit(1);
		case 0:
			/*Proceso Hijo*/	
			close(fd[1]);
			dup2(fd[0], 0);
			close(fd[0]);	
			
			execlp(argv[3], argv[3], argv[4], NULL);
		default:
			/*Proceso Padre*/

			close(fd[0]);
			dup2(fd[1], 1);
			close(fd[1]);
			
			execlp(argv[1], argv[1], argv[2], NULL);
	}
	
	return 0;
}
