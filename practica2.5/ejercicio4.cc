#include <sys/socket.h>
#include <netdb.h>
#include <sys/types.h>
#include <string.h>
#include <iostream>
#include <errno.h>
#include <time.h>
#include <sys/select.h>


/* ./ejercicio4 hostname portname */
int main(int argc, char **argv){
	struct addrinfo hints;
	struct addrinfo *res;
	fd_set rfds;
	
	memset(&hints, 0, sizeof(struct addrinfo));
	
	hints.ai_family = AF_UNSPEC;
	hints.ai_socktype = SOCK_DGRAM;
	hints.ai_flags = AI_PASSIVE;
	
	int rc = getaddrinfo(argv[1], argv[2], &hints, &res);
	
	if(rc != 0){
		fprintf(stderr, "getaddrinfo: %s\n", strerror(errno));
		return 1;
	}
	
	int sd = socket(res->ai_family, res->ai_socktype, res->ai_protocol);
	bind(sd, res->ai_addr, res->ai_addrlen);
	
	while(1){
		char buffer[80];
		struct sockaddr_storage client;
		socklent_t client_len = sizeof(struct sockaddr_storage);
		char host[NI_MAXHOST];
		char serv[NI_MAXSERV];
		
		
		FD_ZERO(&rfds);
		FD_SET(sd, &rfds);
		FD_SET(0, &rfds);
		
		select(sd + 1, &rfds, 0, 0, 0);
		
		if(FD_ISSET(0, &rfds)){
			int bytes = read(0, buffer, 79);
			
			if(bytes == -1){
				fprintf(stderr, "read: %s\n", strerror(errno));
				return 1;		
			}
			
			buffer[bytes] = '\0';
			
			std::cout << bytes << "bytes de terminal" << std::endl;
			
			time_t now;
			struct tm *timeinfo;
			
			if(strcmp(buffer, 't') == 0){
				char buffer_time[9];
				time(&now);
				timeinfo = localtime(&now);
				sprintf(buffer_time, "%d:%d:%d", timeinfo->tm_hour, timeinfo->tm_min, timeinfo->tm_sec);
				std:: cout << buffer_time << std::endl;
			}else if(strcmp(buffer, 'd') == 0){
				char buffer_date[11];
				time(&now);
				timeinfo = localtime(&now);
				sprintf(buffer_date, "%d-%d-%d", timeinfo->tm_year + 1900, timeinfo->tm_mon + 1, timeinfo->tm_mday);
				std:: cout << buffer_date << std::endl;
			}else if(strcmp(buffer, 'q') == 0){
				std::cout << "Saliendo..."<< std::endl;
				break;
			}else{
				std::cout << "Comando "<< buffer << " no soportado"  << std::endl;
			}
			
		}else if(FD_ISSET(sd, &rfds)){
			int bytes = recvfrom(sd, buffer, 79, 0, (struct sockaddr*) client, &client_len);
		
			if(bytes == -1){
				fprintf(stderr, "recvfrom: %s\n", strerror(errno));
				return 1;		
			}
			
			buffer[bytes] = '\0';
			
			int rc = getnameinfo((struct sockaddr*) &client, client_len, host, NI_MAXHOST,
						serv, NI_MAXSERV, NI_NUMERICHOST);
			
			if(rc != 0){
				fprintf(stderr, "getnameinfo: %s\n", strerror(errno));
				return 1;
			}
			
			std::cout << bytes << "bytes de "<< host << serv  << std::endl;
			
			time_t now;
			struct tm *timeinfo;
			
			if(strcmp(buffer, 't') == 0){
				char buffer_time[9];
				time(&now);
				timeinfo = localtime(&now);
				sprintf(buffer_time, "%d:%d:%d", timeinfo->tm_hour, timeinfo->tm_min, timeinfo->tm_sec);
				sendto(sd, buffer_time, strlen(buffer_time), 0, (struct sockaddr*) &client, client_len);
			}else if(strcmp(buffer, 'd') == 0){
				char buffer_date[11];
				time(&now);
				timeinfo = localtime(&now);
				sprintf(buffer_date, "%d-%d-%d", timeinfo->tm_year + 1900, timeinfo->tm_mon + 1, timeinfo->tm_mday);
				sendto(sd, buffer_date, strlen(buffer_date), 0, (struct sockaddr*) &client, client_len);
			}else if(strcmp(buffer, 'q') == 0){
				std::cout << "Saliendo..."<< std::endl;
				break;
			}else{
				std::cout << "Comando "<< buffer << " no soportado"  << std::endl;
			}
		}

		
	}																																																												

	freeaddrinfo(res);
	

	return 0;
}
