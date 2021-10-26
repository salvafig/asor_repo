#include <string.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>



int main(){
        printf("The real user ID is:  %d\n", getuid());
        printf("The effective user ID is: %d\n", geteuid());

        return 1;
}
