#include <signal.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

bool delete_process = true;
bool usr_interrupted = false;

void handler(int senial){
	if(senial == SIGUSR1){
		delete_process = false;
	}
	usr_interrupted = true;

	return;
}


/* ejercicio13 seconds */
int main(int argc, char **argv){
	struct sigaction sa;
	sigset_t mask, old_mask;
	
	alarm(atoi(argv[1]));

	sa.sa_handler = handler;
	sa.sa_flags = SA_RESTART;
	sigaction(SIGUSR1, &sa, NULL);
	sigaction(SIGALRM, &sa, NULL);

	sigemptyset(&mask);
	sigaddset(&mask, SIGUSR1);
	sigaddset(&mask, SIGALRM);
	

	sigprocmask(SIG_BLOCK, &mask, &old_mask);
	while(!usr_interrupted){
		sigsuspend(&old_mask);
	}
	sigprocmask(SIG_UNBLOCK, &mask, NULL);


	if(delete_process){
		printf("SI se ha realizado el borrado del propio ejecutable\n");
		unlink(argv[0]);
	}else{
		printf("NO se ha realizado el borrado del propio ejecutable\n");
	}
	
	return 0;
}
