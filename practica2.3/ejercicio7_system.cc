#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <stdlib.h>


int main(int argc, char **argv){
	char command[] = " ";
	int ret;

	for(int i = 1; i < argc; i++){
		if(i == 1){
			strcpy(command, argv[i]);
		}else{
			strcat(command, argv[i]);
		}	
		strcat(command, " ");	
	}	

	ret = system(command);
	if(ret == -1){
		printf("%s\n", strerror(errno));
		return 1;
	}

	printf("El comando terminó de ejecutarse\n");
	
	return 0;
}
