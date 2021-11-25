#include <unistd.h>
#include <stdio.h>
#include <signal.h>
#include <stdlib.h>

int n_sigint = 0;
int n_sigtstp = 0;

void handler(int senial){
	if(senial == SIGINT){
		n_sigint++;
	}else if(senial == SIGTSTP){
		n_sigtstp++;
	}

	return;
}


int main(int argc, char **argv){
	struct sigaction sa;

	sa.sa_handler = handler;
	sa.sa_flags = SA_RESTART;

	sigaction(SIGINT, &sa, NULL);
	sigaction(SIGTSTP, &sa, NULL);

	while((n_sigint + n_sigtstp) < 10){
		

	}

	printf("Number of SIGINT signals: %d\n", n_sigint);
	printf("Number of SIGTSTP signals: %d\n", n_sigtstp);
	

	return 0;
}
