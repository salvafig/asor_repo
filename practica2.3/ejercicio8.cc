#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <stdlib.h>
#include <sys/types.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>




int main(int argc, char **argv){
	pid_t pid;

	pid = fork();

	switch(pid){
		case -1:
			printf("%s\n", strerror(errno));
			exit(1);
		case 0:	
			int in, out, out_error;
			char* command_arguments[argc - 1];

			in = open("/dev/null", O_RDONLY);
			out = open("/tmp/daemon.out", O_WRONLY | O_TRUNC | O_CREAT, S_IRUSR | S_IWGRP | S_IWUSR);
			out_error = open("/tmp/daemon.err", O_WRONLY | O_TRUNC | O_CREAT, S_IRUSR | S_IWGRP | S_IWUSR);

			dup2(in, 0);
			dup2(out, 1);
			dup2(out_error, 2);	

			close(in);
			close(out);
			close(out_error);

			for(int i = 0; i < argc - 1; i++){
				command_arguments[i] = argv[i + 1];
			}

			command_arguments[argc - 1] = NULL;
	
			if(execvp(argv[1], command_arguments) < 0){
				fprintf(stderr, "%s\n", strerror(errno));				
				//printf("%s\n", strerror(errno));
				break;
			}
			break;
		default:
			int status;

			wait(&status);
			break;
	}
	
	return 0;
}
