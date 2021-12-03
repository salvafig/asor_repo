#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>



int main(int argc, char **argv){
	int p_h[2];
	int h_p[2];
	pid_t pid;
	

	if(pipe(p_h) == -1 || pipe(h_p) == -1){
		fprintf(stderr, "%s\n", strerror(errno));
		return 1;
	}

	pid = fork();

	switch(pid){
		case -1:
			fprintf(stderr, "%s\n", strerror(errno));
			exit(1);
		case 0:
			/* Proceso Hijo */
			int bytes_pipe_input;
			char buffer_pipe_input[20];

			close(h_p[0]);
			close(p_h[1]);

			for(int i = 0; i < 10; i++){
				bytes_pipe_input = read(p_h[0], buffer_pipe_input, sizeof(buffer_pipe_input));
				if(bytes_pipe_input == -1){
					fprintf(stderr, "%s\n", strerror(errno));
					return 1;
				}
				
				printf("Hijo lee: %s\n", bytes_pipe_input);
				//write(1, bytes_pipe_input, strlen(bytes_pipe_input));
				sleep(1);
				if(i < 9){
					write(h_p[1], "l", 1);
				}else{
					write(h_p[1], "q", 1);
				}
			}
		default: 
			/* Proceso Padre */
			bool stop = false;
			int bytes_standard_input;
			char buffer_standard_input[20];
			char flag[1];
			

			close(p_h[0]);
			close(h_p[1]);

			while(!stop){
				printf("Padre escribe: ");
				bytes_standard_input = read(0, buffer_standard_input, sizeof(buffer_standard_input));
				if(bytes_standard_input == -1){
					fprintf(stderr, "%s\n", strerror(errno));
					return 1;
				}

				write(p_h[1], buffer_standard_input, strlen(buffer_standard_input));
				
				if(read(h_p[0], flag, 1) == -1){
					fprintf(stderr, "%s\n", strerror(errno));
					return 1;
				}

				stop = strcmp(flag, "q") == 0;
				
			}
			
	}
	

	return 0;
}
