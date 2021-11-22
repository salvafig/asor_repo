#include <sched.h>
#include <stdio.h>
#include <string.h>

int main(){
	char sched_policy[50];
	int max_priority;
  struct sched_param param;
	int policy;

	switch(policy = sched_getscheduler(0)) {		
		case SCHED_OTHER:
			strcpy(sched_policy,"SCHED_OTHER");
			break;
	      	case SCHED_FIFO:
			strcpy(sched_policy,"SCHED_FIFO");
			break;
	      	case SCHED_RR:
			strcpy(sched_policy,"SCHED_RR");
			break;
		case SCHED_BATCH:
			strcpy(sched_policy,"SCHED_BATCH");
			break;
		case SCHED_IDLE:
			strcpy(sched_policy,"SCHED_IDLE");
			break;
	      	default:
			strcpy(sched_policy,"Unknown scheduling priority");
			break;
	   }
	
	sched_getparam(0, &param);

	printf("Scheduling policy of the calling process: %s\n", sched_policy);
	printf("Scheduling priority of the calling process: %d\n", param.sched_priority);
	printf("Max Scheduling priority of the calling process' policy: %d\n", sched_get_priority_max(policy));
	printf("Min Scheduling priority of the calling process' policy: %d\n", sched_get_priority_min(policy));

	return 0;

}
