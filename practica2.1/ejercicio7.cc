#include <string.h>
#include <unistd.h>
#include <stdio.h>



int main(){
	printf("Maximum number of links:  %ld\n", pathconf("/", _PC_LINK_MAX));
	printf("Maximum length of a relative pathname: %ld\n", pathconf("/", _PC_PATH_MAX));
	printf("Maximum length of a filename:  %ld\n", pathconf("/", _PC_NAME_MAX));

	return 1;
}
