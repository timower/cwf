#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "response.h"

char* gen_response(response_t* res, int* len) {
	char status[64];
	sprintf(status, "HTTP/%d.%d %d %s\r\n", res->version_major, res->version_minor, res->status_code, res->reason_phrase);
	char header[1024];
	sprint_header(header, &(res->header));
	int lent;
	lent = strlen(status) + strlen(header) + res->body.pos + 3;

	char * buf = malloc(lent);
	*len = sprintf(buf, "%s%s\r\n", status, header);
	if (res->body.buffer){
		memcpy(buf+(*len), res->body.buffer, res->body.pos);
		*len += res->body.pos;
	}
	return buf;
}