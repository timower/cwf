#include <string.h>
#include <stdlib.h>

#include "request.h"

int parse_request(const char* buffer, int bufferlen, request_t* req) {
	//TODO: don't reparse whole request when requesting more bytes
	int i = 0;
	const char * pos = buffer;

	if (bufferlen < 10){ // need at least 10 bytes
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

	if (pos - buffer + 5 > bufferlen || i == 511) {
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

	if (pos - buffer > bufferlen || i == 15) {
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
	if (pos - buffer >= bufferlen || i == 15) {
		return 0; //need more data
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
		while(pos[i] != '\r' && pos[i] != '\n' && i < 512) {
			value[i] = pos[i];
			i++;
		}
		value[i] = '\0';
		if (pos[i] == '\r')
			i++;
		
		
		pos += i+1;
		set_header(&(req->header), key, value);
	}
	if (pos - buffer >= bufferlen) {
		 return 0;
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
			return 0;
		}
		buffer_t body = {0};
		init_buffer(&body, length);
		set_buffer(&body, pos, length);
		body.buffer[length] = 0; // for printing?????
		req->body = body;
	}
	//done!!
	return 1;
}