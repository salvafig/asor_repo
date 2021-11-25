#include <signal.h>
#include <stdio.h>
#include <unistd.h>

#define SLEEP_SECS 30


int main(int argc, char **argv){
	sigset_t blk_set;
	sigset_t pend_set;

	sigemptyset(&blk_set);
	sigaddset(&blk_set, SIGINT);
	sigaddset(&blk_set, SIGTSTP);

	sigprocmask(SIG_BLOCK, &blk_set, NULL);

	/* Inicio código protegido */	

	sleep(SLEEP_SECS);

	sigpending(&pend_set);
	if(sigismember(&pend_set, SIGINT) == 1){
		printf("Señal SIGINT recibida!\n");
	}else{
		sigdelset(&blk_set, SIGINT);
	}

	if(sigismember(&pend_set, SIGTSTP) == 1){
		printf("Señal SIGTSTP recibida!\n");
	}else{
		sigdelset(&pend_set, SIGTSTP);
	}
  
  /* Fin código protegido */

	sigprocmask(SIG_UNBLOCK, &blk_set, NULL);

	printf("Fin del Programa\n");


	return 0;
}
