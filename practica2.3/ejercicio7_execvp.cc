#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <stdlib.h>


int main(int argc, char **argv){
	char* command_arguments[argc - 1];

	for(int i = 0; i < argc - 1; i++){
		command_arguments[i] = argv[i + 1];
	}
	

	if(execvp(argv[1], command_arguments) < 0){
		printf("%s\n", strerror(errno));
		return 1;
	}

	printf("El comando terminó de ejecutarse\n");
	
	return 0;
}
