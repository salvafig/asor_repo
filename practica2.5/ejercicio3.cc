#include <sys/socket.h>
#include <netdb.h>
#include <sys/types.h>
#include <string.h>
#include <iostream>
#include <errno.h>
#include <time.h>


/* ./ejercicio3 hostserv portserv command */
int main(int argc, char **argv){
	struct addrinfo hints;
	struct addrinfo *res;
	int sd;
	char buffer[80];
	struct sockaddr_storage serv;
	socklen_t serv_len = sizeof(struct sockaddr_storage);
	
	memset(&hints, 0, sizeof(struct addrinfo));
	
	hints.ai_family = AF_UNSPEC;
	hints.ai_socktype = SOCK_DGRAM;
	hints.ai_flags = AI_PASSIVE;
	
	int rc = getaddrinfo(argv[1], argv[2], &hints, &res);
	
	if(rc != 0){
		fprintf(stderr, "getaddrinfo: %s\n", strerror(errno));
		return 1;
	}
	
	
	/*memset(&serv, 0, serv_len);
	
	serv = (struct sockaddr *) res->ai_addr;
	serv_len = res->ai_addrlen;*/
	
	sd = socket(res->ai_family, res->ai_socktype, res->ai_protocol);
	
	if(sd == -1){
		fprintf(stderr, "socket: %s\n", strerror(errno));
		return 1;
	}
	
	connect(sd, (struct sockaddr *) res->ai_addr, res->ai_addrlen);
	
	sendto(sd, argv[3], strlen(argv[3]), 0, (struct sockaddr *) res->ai_addr, res->ai_addrlen);
	
	int bytes = recvfrom(sd, buffer, 79, 0, (struct sockaddr *) &serv, serv_len);
	
	if(bytes == -1){
		fprintf(stderr, "recvfrom: %s\n", strerror(errno));
		//¿Hace falta cerrar el fichero del socket aqui?
		return 1;
	}
	
	buffer[bytes] = '\0';
	
	std::cout << buffer << std::endl;
	
	
	freeaddrinfo(res);
	close(fd); //Cerrar fichero del socket
	

	return 0;
}
