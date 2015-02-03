#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h> 
#include <sys/socket.h>
#include <netinet/in.h>

typedef struct header {
	//general:
	char* Cache_Control;
	char* Connection;
	char* Date;
	char* Pragma;
	char* Trailer;
	char* Transfer_Encoding;
	char* Upgrade;
	char* Via;
	char* Warning;
	//request:
	char* Accept;
	char* Accept_Charset;
	char* Accept_Encoding;
	char* Accept_Language;
	char* Authorization;
	char* Expect;
	char* From;
	char* Host;
	char* If_Match;
	char* If_Modified_Since;
	char* If_None_Match;
	char* If_Range;
	char* If_Unmodified_Since;
	char* Max_Forwards;
	char* Proxy_Authorization;
	char* Range;
	char* Referer;
	char* TE;
	char* User_Agent;
	//response:
	char* Allow;
	char* Content_Encoding;
	char* Content_Language;
	int Content_Length;
	char* Content_Location;
	char* Content_MD5;
	char* Content_Range;
	char* Content_Type;
	char* Expires;
	char* Last_Modified;
	char* extension_header;
} header_t;

typedef struct request {
	int version_major;
	int version_minor;
	char * path;
	char * method; //TODO: make enum
	header_t header;
	char* body;
} request_t;

void error(const char *msg)
{
    perror(msg);
    exit(1);
}

char* read_request(int sockfd) {
	char * buffer = malloc(256);
	bzero(buffer, 256);
	int buf_size = 256;
	int len;
	int pos = 0;
	//TODO: loop
	while(1){
		len = read(sockfd, buffer+pos, buf_size-1-pos);
		if (len < 0)
			error("ERORR reading from socket");
		int strl = strlen(buffer);
		if(memcmp(buffer+strl-2, "\n\n", 2) == 0 || memcmp(buffer+strl-4, "\r\n\r\n", 4) == 0 || len == 0) {
			buffer[strl] = 0;
			return buffer;
		}
		if(len > buf_size-4) {
			buf_size *= 2;
			buffer = realloc(buffer, buf_size);
		}
		pos = len;
	}
}

int parse_request(char* buffer, request_t* req) {
	int i = 0;
	char *pos = buffer;
	char method[16];
	while(buffer[i] != ' ') {
		method[i] = buffer[i];
		i++;
	}
	method[i] = '\0';
	pos = buffer + i+1; //absorb space
	i = 0;
	char URI[512];
	while(pos[i] != ' ') {
		URI[i] = pos[i];
		i++;
	}
	URI[i] = '\0';

	pos += i+1;
	
	if(memcmp(pos, "HTTP/", 5) != 0){
		return -1;
	}

	pos += 5;
	char major[16];
	i = 0;
	while(pos[i] != 0) {
		major[i] = pos[i];
		i++;
	}
	major[i] = '\0';
	pos += i+1;

	char minor[16];
	i = 0;
	while(pos[i] != 0) {
		minor[i] = pos[i];
		i++;
	}
	minor[i] = '\0';
	pos += i+1;

	
	return 0;
}

int main(int argc, char* argv[]) {

	//setup listen socket
	int sockfd, newsockfd, portno;
	socklen_t clilen;
	struct sockaddr_in serv_addr, cli_addr;
	char* buffer;
	int buflen = 0;

	//get port
	if (argc < 2) {
        fprintf(stderr,"ERROR, no port provided\n");
        exit(1);
    }
	portno = atoi(argv[1]);
    
    //create socket
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) 
        error("ERROR opening socket");

    //setup addr struct
    bzero((char *) &serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = INADDR_ANY;
    serv_addr.sin_port = htons(portno);

    //reuseaddr:
    int optval = 1;
	if (setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &optval, sizeof(optval)) < 0)
		error("ERROR setting reuseaddr");

    //bind socket to address and start listening (queue of 10)
    if (bind(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0)
            error("ERROR on binding");
    listen(sockfd, 10);

	while (1) {
		//accept 1 client
		clilen = sizeof(cli_addr);
		newsockfd = accept(sockfd, (struct sockaddr *) &cli_addr, &clilen);
		if (newsockfd < 0) 
	        error("ERROR on accept");
		//read request	(ignoring keep-alive)
		buffer = read_request(newsockfd);
		//print request
     	printf("strlen: %d\n", strlen(buffer));
		printf("request:\n%sEOR\n", buffer);
		//parse request
		
		request_t req = {0};
		parse_request(buffer, &req);
		//call routes based on request(and respond)
		//close connection gracefully
		close(newsockfd);
		free(buffer);
		//repeat
	}
	//cleanup
	close(sockfd);
}
