#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <stdlib.h>
#include <limits.h>
#include <sys/time.h>
#include <sys/resource.h>



int main(){
	pid_t pid;

	pid = fork();

	switch(pid){
		case -1:
			printf("%s\n", strerror(errno));
			exit(1);
		case 0:
			pid_t sid;
			sid = setsid();
			struct rlimit old_lim;
			if(chdir("/tmp") == -1){
				printf("%s\n", strerror(errno));
			}

			if(getrlimit(RLIMIT_NOFILE, &old_lim) == 0){
				char cwd[PATH_MAX];

				if(getcwd(cwd, sizeof(cwd)) != NULL){
					int pid_hijo = getpid();

					printf("Process ID (PID) of the calling process: %d\n", pid_hijo);
					printf("Process ID (PID) of the parent of the calling process: %d\n", getppid());
					printf("Process Group ID (PGID) of the calling process: %d\n", getpgid(pid_hijo));
					printf("Session ID (SID) of the calling process: %d\n", getsid(pid_hijo));
					printf("Soft limit of max number of open files per process: %d\n", old_lim.rlim_cur);
					printf("Hard limit of max number of open files per process: %d\n", old_lim.rlim_max);
					printf("Current working directory: %s\n", cwd);
				}else{
					printf("%s\n", strerror(errno));
					break;
				}
			}else{
				printf("%s\n", strerror(errno));
				break;
			}	

	
			//sleep(3);				
			//printf("Hijo\n");
			
			break;
		default:
			sleep(3);
			//printf("Padre\n");
			break;
	}
	
	return 0;
}
