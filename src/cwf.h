#ifndef CWF_H
#define CWF_H

#include "header.h"

typedef struct request {
	int version_major;
	int version_minor;
	char path[512];
	char method[16]; //TODO: make enum
	header_t header;
	char* body;
} request_t;

int read_request(int sockfd, request_t* req);
int parse_request(const char* buffer, int bufferlen, request_t* req);
int CWF_start(int port);
#endif