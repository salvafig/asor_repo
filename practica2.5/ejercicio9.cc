#include <sys/socket.h>
#include <netdb.h>
#include <sys/types.h>
#include <string.h>
#include <iostream>
#include <errno.h>
#include <unistd.h>
#include <signal.h>


void haz_conn(int client_sd){
	char buffer[80];
	
	while(1){
			int bytes = recv(client_sd, buffer, 79, 0);
			
			if(bytes == -1){
				fprintf(stderr, "recv: %s\n", strerror(errno));
				return 1;	
			}else if(bytes == 0){
				close(client_sd);
				break;
			}
			
			buffer[bytes] = '\0';
			send(client_sd, buffer, bytes, 0);
			
		}
	
}


/* ./ejercicio9 hostname portname */
int main(int argc, char **argv){
	struct addrinfo hints;
	struct addrinfo *res;
	struct sigaction sa;
	
	sa.sa_handler = SIG_IGN; //to ignore this signal
	sa.sa_flags = SA_RESTART; // Provide behavior compatible with BSD signal semantics by making certain system calls restartable across signals.
	
	sigaction(SIGCHLD, &sa, NULL);
	
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
	bind(sd, (struct sockaddr *) res->ai_addr, res->ai_addrlen);
	listen(sd, 5);
	
	while(1){
		struct sockaddr_storage client;
		socklent_t client_len = sizeof(struct sockaddr_storage);
		char host[NI_MAXHOST];
		char serv[NI_MAXSERV];
		
		int client_sd = accept(sd, (struct sockaddr *) &client, &client_len);
		
		int rc = getnameinfo((struct sockaddr*) &client, client_len, host, NI_MAXHOST,
					serv, NI_MAXSERV, NI_NUMERICHOST);
		
		if(rc != 0){
			fprintf(stderr, "getnameinfo: %s\n", strerror(errno));
			return 1;
		}
		
		std::cout << "Conexión desde "<< host << " " << serv  << std::endl;
		
		pid_t pid = fork()
		switch(pid){
			case -1:
				fprintf(stderr, "fork: %s\n", strerror(errno));
				return 1;
			case 0:
					//Proceso hijo
				haz_conn(client_sd);
				return 0;
			case 1:
					//Proceso padre
				break;
			
		}
		
		close(client_sd); //¿Es necesario cerrar aquí el fichero referente al socket del cliente?
		std::cout << "Conexión terminada" << std::endl;
		
	}																																																												

	freeaddrinfo(res);
	

	return 0;
}
