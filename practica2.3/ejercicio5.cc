#include <unistd.h>
#include <stdio.h>
#include <limits.h>
#include <sys/time.h>
#include <sys/resource.h>
#include <string.h>
#include <errno.h>



int main(){
	struct rlimit old_lim;

	if(getrlimit(RLIMIT_NOFILE, &old_lim) == 0){
		char cwd[PATH_MAX];

		if(getcwd(cwd, sizeof(cwd)) != NULL){
			int pid = getpid();

			printf("Process ID (PID) of the calling process: %d\n", pid);
			printf("Process ID (PID) of the parent of the calling process: %d\n", getppid());
			printf("Process Group ID (PGID) of the calling process: %d\n", getpgid(pid));
			printf("Session ID (SID) of the calling process: %d\n", getsid(pid));
			printf("Soft limit of max number of open files per process: %d\n", old_lim.rlim_cur);
			printf("Hard limit of max number of open files per process: %d\n", old_lim.rlim_max);
			printf("Current working directory: %s\n", cwd);
		}else{
			printf("%s\n", strerror(errno));
			//perror("getcwd() error");
			return 1;
		}
	}else{
		printf("%s\n", strerror(errno));
		return 1;
	}	

	return 0;
}
