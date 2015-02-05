#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h> 
#include <sys/socket.h>
#include <netinet/in.h>

#include "cwf.h"

int read_request(int sockfd, request_t* req) {
	int buf_len = 256;
	int len;
	char* buffer = malloc(buf_len);
	int total_len = 0;
	//loop:
	while(1) {
		len = read(sockfd, buffer+total_len, buf_len-total_len-1);
		if (len <= 0) {
			return -1;
		}
		if(len != buf_len-total_len-1) { //read all available data:
			int r = parse_request(buffer, total_len+len, req);
			if (r == 1) { //check if we need more data:
				//DEBUG/
				free(buffer);
				return 1; //no, done
			} else if (r < 0) {
				return -1;
			}
			else {
				//DEBUG:
				puts("need more data");
			}
		}

		if(total_len+len > buf_len - 10) {
			buf_len *= 2;
			buffer = realloc(buffer, buf_len);
		}
		total_len += len;
	}

}

int parse_request(const char* buffer, int bufferlen, request_t* req) {
	//TODO: don't reparse whole request when requesting more bytes
	int i = 0;
	const char * pos = buffer;

	if (bufferlen < 10){ // need at least 10 bytes
		puts("0");
		return 0;
	}

	//request-line:
	char method[16];
	while(buffer[i] != ' ' && i < 16) {
		method[i] = buffer[i];
		i++;
	}
	method[i] = '\0';
	pos +=  i+1; //absorb space
	if (pos - buffer > bufferlen || i == 15) {
		puts("1"); return 0; //need more data
	}

	i = 0;
	char URI[512];
	while(pos[i] != ' ' && i < 512) {
		URI[i] = pos[i];
		i++;
	}
	URI[i] = '\0';
	pos += i+1;

	if (pos - buffer + 5 > bufferlen || i == 511) {
		puts("2"); return 0; //need more data
	}
	
	if(memcmp(pos, "HTTP/", 5) != 0){
		return -1;
	}

	pos += 5;
	
	char major[16];
	i = 0;
	while(pos[i] != '.' && i < 16) {
		major[i] = pos[i];
		i++;
	}
	major[i] = '\0';
	pos += i+1;

	if (pos - buffer > bufferlen || i == 15) {
		puts("3"); return 0; //need more data
	}

	char minor[16];
	i = 0;
	while(pos[i] != '\n' && i < 16) { //might absorb \r
		minor[i] = pos[i];
		i++;
	}
	minor[i] = '\0';
	pos += i+1;
	if (pos - buffer >= bufferlen || i == 15) {
		puts("4"); return 0; //need more data
	}

	strcpy(req->method, method);
	strcpy(req->path, URI);
	req->version_major = atoi(major);
	req->version_minor = atoi(minor);

	//headers:
	while(pos[0] != '\n' && pos[0] != '\r' && pos - buffer < bufferlen) {
		char key[32];
		i = 0;
		while(pos[i] != ':' && i < 32) {
			key[i] = pos[i];
			i++;
		}
		key[i] = '\0';
		pos += i+1;

		char* value = malloc(512);
		i = 0;
		while(pos[i] == ' ' || pos[i] == '\t') {
			i++;
		}
		pos += i;
		i = 0;
		while(pos[i] != '\n' && i < 512) {
			value[i] = pos[i];
			i++;
		}
		value[i] = '\0';
		
		pos += i+1;
		set_header(&(req->header), key, value);
	}
	if (pos - buffer >= bufferlen) {
		puts("5"); return 0;
	}

	if (pos[0] == '\r')
		pos++;
	if(pos[0] != '\n')
		return -1;
	pos++; //absorb /n
	//contents:
	char* cl = get_header(&(req->header), "Content-Length");
	if(cl) {
		int length = atoi(cl);
		if(bufferlen-(pos-buffer) < length) {
			puts("6");
			return 0;
		}
		char* body = malloc(length+1);
		for(i = 0; i < length; i++) {
			body[i] = pos[i];
		}
		req->body = body;
	}
	//done!!
	return 1;
}

int CWF_start(int port) {

	//setup listen socket
	int sockfd, newsockfd;
	socklen_t clilen;
	struct sockaddr_in serv_addr, cli_addr;
	int buflen = 0;
    
    //create socket
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) {
        puts("ERROR opening socket");
        return -1;
    }

    //setup addr struct
    bzero((char *) &serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = INADDR_ANY;
    serv_addr.sin_port = htons(port);

    //reuseaddr:
    int optval = 1;
	if (setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &optval, sizeof(optval)) < 0){
		puts("ERROR setting reuseaddr");
		return -1;
	}

    //bind socket to address and start listening (queue of 10)
    if (bind(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0){
            puts("ERROR on binding");
            return -1;
    }

    listen(sockfd, 10);

	while (1) {
		//accept 1 client
		clilen = sizeof(cli_addr);

		newsockfd = accept(sockfd, (struct sockaddr *) &cli_addr, &clilen);
		if (newsockfd < 0) {
	        puts("ERROR on accept");
	        return -1;
		}

		//TODO: thread/fork/???
		request_t req = {0};
		header_t zero = {0};
		req.header = zero;
		if (read_request(newsockfd, &req) < 0) {
			puts("error reading request");
		}

		//print:
		printf("method: %s\npath: %s\nversion: %d.%d\n",
			req.method, req.path, req.version_major, req.version_minor);
		print_header(&(req.header));
		if (req.body)
			printf("\nbody\n %s\n", req.body);
		//call routes based on request(and respond)

		//close connection gracefully
		free_header(&(req.header));
		if(req.body)
			free(req.body);
		close(newsockfd);
	}
	close(sockfd);
}