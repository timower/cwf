#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h> 
#include <sys/socket.h>
#include <netinet/in.h>

const char* header_fields[] = {
	"content-type",
	"content-length",
	"host"
};
#define HEADER_LENGTH (sizeof(header_fields)/sizeof(char*))

typedef struct header {
	char* values[HEADER_LENGTH];
} header_t;

typedef struct request {
	int version_major;
	int version_minor;
	char path[512];
	char method[16]; //TODO: make enum
	header_t header;
	char* body;
} request_t;

void error(const char *msg)
{
    perror(msg);
    exit(1);
}

int set_header(header_t* header, const char* field, char* value) {
	int i;
    for (i = 0; i < HEADER_LENGTH; i++) {
        if(strcasecmp(header_fields[i], field) == 0) {
            break;
        }
    }
    if (i == HEADER_LENGTH) {
        return -1;
    }
    header->values[i] = value;
    printf("set %s to %s\n", field, value);
    return 0;
}

char* get_header(header_t* header, const char* field) {
	int i;
    for (i = 0; i < HEADER_LENGTH; i++) {
        if(strcasecmp(header_fields[i], field) == 0) {
            break;
        }
    }
    if (i == HEADER_LENGTH) {
        return NULL;
    }
    return header->values[i];
}

int free_header(header_t* header) {
	int i;
    for (i = 0; i < HEADER_LENGTH; i++) {
    	if(header->values[i])
    		free(header->values[i]);
    }
    return 0;
}

void print_header(header_t* header) {
	int i;
    for (i = 0; i < HEADER_LENGTH; i++) {
    	if(header->values[i])
    		printf("%s: %s\n", header_fields[i], header->values[i]);
    }
}

int read_request(int sockfd, request_t* req) {
	//TODO:
	//read max amount of bytes(read while len == cur_len)
	//parse current header
	//check if done
	//repeat
	int buf_len = 256;
	int len;
	char* buffer = malloc(buf_len);
	int total_len = 0;
	//loop:
	while(1) {
		len = read(sockfd, buffer+total_len, buf_len-total_len-1);
		if(len != buf_len-total_len-1) { //read all available data:
			int r = parse_request(buffer, total_len, req);
			if (r == 1) { //check if we need more data:
				free(buffer);
				return 1; //no, done
			} else if (r < 0) {
				error("ERROR parsing request");
			}
			else {
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

	if (bufferlen < 10) // need at least 10 bytes
		return 0;

	//request-line:
	char method[16];
	while(buffer[i] != ' ' && i < 16) {
		method[i] = buffer[i];
		i++;
	}
	method[i] = '\0';
	pos +=  i+1; //absorb space

	if (buffer - pos > bufferlen || i == 15) {
		return 0; //need more data
	}

	i = 0;
	char URI[512];
	while(pos[i] != ' ' && i < 512) {
		URI[i] = pos[i];
		i++;
	}
	URI[i] = '\0';
	pos += i+1;

	if (buffer - pos + 5 > bufferlen || i == 511) {
		return 0; //need more data
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

	if (buffer - pos > bufferlen || i == 15) {
		return 0; //need more data
	}

	char minor[16];
	i = 0;
	while(pos[i] != '\n' && i < 16) { //might absorb \r
		minor[i] = pos[i];
		i++;
	}
	minor[i] = '\0';
	pos += i+1;
	if (buffer - pos > bufferlen || i == 15) {
		return 0; //need more data
	}

	strcpy(req->method, method);
	strcpy(req->path, URI);
	req->version_major = atoi(major);
	req->version_minor = atoi(minor);

	//headers:
	while(pos[0] != '\n' && pos[0] != '\r' && buffer - pos < bufferlen) {
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
		while(pos[i] != '\n' && i < 512) {
			value[i] = pos[i];
			i++;
		}
		value[i] = '\0';
		pos += i+1;
		set_header(&(req->header), key, value);

		//puts(key);
		//puts(value);

	}
	//contents:

	return 1;
}

int main(int argc, char* argv[]) {

	//setup listen socket
	int sockfd, newsockfd, portno;
	socklen_t clilen;
	struct sockaddr_in serv_addr, cli_addr;
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
		//parse request
		request_t req = {0};
		read_request(newsockfd, &req);
		printf("method: %s\npath: %s\nversion: %d.%d\n",
			req.method, req.path, req.version_major, req.version_minor);
		print_header(&(req.header));
		//call routes based on request(and respond)
		//close connection gracefully
		free_header(&(req.header));
		close(newsockfd);
		//repeat
	}
	//cleanup
	close(sockfd);
}
