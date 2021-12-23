#include <sys/socket.h>
#include <netdb.h>
#include <sys/types.h>
#include <string.h>
#include <iostream>
#include <errno.h>

/* ./ejercicio7 hostname portname */
int main(int argc, char **argv){
	struct addrinfo hints;
	struct addrinfo *res;
	
	memset(&hints, 0, sizeof(struct addrinfo));
	
	hints.ai_family = AF_UNSPEC;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_flags = 0;
	
	int rc = getaddrinfo(argv[1], argv[2], &hints, &res);
	
	if(rc != 0){
		fprintf(stderr, "getaddrinfo: %s\n", strerror(errno));
		return 1;
	}
	
	int sd = socket(res->ai_family, res->ai_socktype, res->ai_protocol);
	int sd_conn = connect(sd, (struct sockaddr *) res->ai_addr, res->ai_addrlen);
	
	if(sd_conn == -1){
		fprintf(stderr, "connection: %s\n", strerror(errno));
		close(sd);
		return 1;
	}
	
	
	while(1){
		char buffer[80];
		
		std:: cin >> buffer;
		
		if(strcmp(buffer, 'Q')){
			break;
		}
		
		send(sd, buffer, strlen(buffer), 0);
		int bytes = recv(sd, buffer, 79, 0);
		
		if(bytes == -1){
			fprintf(stderr, "recv: %s\n", strerror(errno));
			close(sd);
			return 1;
		}
		
		buffer[bytes] = '\0';
		
		std::cout << buffer << std::endl;
		
	}
	
	close(sd);
	freeaddrinfo(res);
	

	return 0;
}
