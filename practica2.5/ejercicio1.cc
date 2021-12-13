#include <sys/socket.h>
#include <netdb.h>
#include <sys/types.h>
#include <string.h>
#include <iostream>
#include <errno.h>


/* ./ejercicio1 hostname */
int main(int argc, char **argv){
	struct addrinfo hints;
	struct addrinfo *res;
	
	memset(&hints, 0, sizeof(struct addrinfo));
	
	hints.ai_family = AF_UNSPEC;
	//hints.ai_socktype = 0;
	hints.ai_flags = AI_PASSIVE;
	
	int rc = getaddrinfo(argv[1], NULL, &hints, &res);
	
	if(rc != 0){
		fprintf(stderr, "getaddrinfo: %s\n", strerror(errno));
		/*std::cout << "getaddrinfo: "
			<< strerror(rc)
			<< std::endl;*/
		return 1;
	}
	
	struct addrinfo *i;
	
	for(i = res; i != NULL; i = i->ai_next){
		char host[NI_MAXHOST];
		char serv[NI_MAXSERV];
		
		int rc = getnameinfo(i->ai_addr, i->ai_addrlen, host, NI_MAXHOST,
					serv, NI_MAXSERV, NI_NUMERICHOST);
		
		if(rc != 0){
			fprintf(stderr, "getnameinfo: %s\n", strerror(errno));
			return 1;
		}
					
		std::cout << host << " " << i->ai_family << " " << i->ai_socktype << std::endl;
		
	}
	
	freeaddrinfo(res);
	

	return 0;
}
