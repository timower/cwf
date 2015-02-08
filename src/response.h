#ifndef RESPONSE_H
#define RESPONSE_H

#include "header.h"
#include "buffer.h"

typedef struct response {
	int version_major;
	int version_minor;
	int status_code;
	char * reason_phrase;
	header_t header;
	buffer_t body;
} response_t;

char* gen_response(response_t* res, int* len);
#endif