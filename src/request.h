#ifndef REQUEST_H
#define REQUEST_H

#include "header.h"
#include "buffer.h"

typedef struct request {
	int version_major;
	int version_minor;
	char path[512];
	char method[16]; //TODO: make enum
	header_t header;
	buffer_t body;
} request_t;

int parse_request(const char* buffer, int bufferlen, request_t* req);
#endif