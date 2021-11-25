#include <signal.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

bool delete_process = true;
bool usr_interrupted = false;

void handler(int senial){
	delete_process = false;
	usr_interrupted = true;

	return;
}


/* ejercicio13 seconds */
int main(int argc, char **argv){
	struct sigaction sa;
	sigset_t mask, old_mask;

	sa.sa_handler = handler;
	sa.sa_flags = SA_RESTART;
	sigaction(SIGUSR1, &sa, NULL);

	sigemptyset(&mask);
	sigaddset(&mask, SIGUSR1);

	sigprocmask(SIG_BLOCK, &mask, &old_mask);
	int i = 0;
	sleep(atoi(argv[1]));
	while(!usr_interrupted){
		sleep(1);
		sigsuspend(&old_mask);
		i++;
	}
	sigprocmask(SIG_UNBLOCK, &mask, NULL);

	//sleep(argv[1])

	if(delete_process){
		unlink(argv[0]);
	}
	
	return 0;
}
