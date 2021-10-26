#include <string.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <pwd.h>



int main(){
	struct passwd *pws;
	
	pws = getpwuid(getuid());
	printf("The real user ID is: %d\n", getuid());
        printf("(Real user) Nombre de usuario:  %s\n", pws->pw_name);
        printf("(Real user) Directorio Home: %s\n", pws->pw_dir);
        printf("(Real user) Descripción de usuario: %s\n", pws->pw_gecos);
        
	pws = getpwuid(geteuid());
	printf("The real user ID is: %d\n", geteuid());
        printf("(Effective user) Nombre de usuario:  %s\n", pws->pw_name);
        printf("(Effective user) Directorio Home: %s\n", pws->pw_dir);
        printf("(Effective user) Descripción de usuario: %s\n", pws->pw_gecos);

        return 1;
}
