#include <sys/utsname.h>
#include <string.h>
#include <stdio.h>

int main(){
	struct utsname uts;
	int sys_error = uname(&uts);
	printf("Sysname:  %s\n", uts.sysname);
	printf("Nodename: %s\n", uts.nodename);
	printf("Release:  %s\n", uts.release);
	printf("Version:  %s\n", uts.version);
	printf("Machine:  %s\n", uts.machine);
	printf("Domaine Name:  %s\n", uts.domainname);
}
