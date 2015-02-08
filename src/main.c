#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h> 
#include <sys/socket.h>
#include <netinet/in.h>

#include "cwf.h"
#include "request.h"
#include "response.h"
#include "buffer.h"

void basic_route(request_t* req, response_t* res) {
	append_bufferStr(&(res->body), "<h1>hello, world</h1>");
	append_bufferStr(&(res->body), "<br/>test");
	
}

int main(int argc, char* argv[]){
	if (argc < 2) {
		puts("need port");
		return -1;
	}
	int port = atoi(argv[1]);

	app_t* a = new_app();
	set_route(a, "/", basic_route);
	set_route(a, "/lol", basic_route);
	
	CWF_start(a, port);
	free(a);

	return 0;
}