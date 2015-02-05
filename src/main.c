#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h> 
#include <sys/socket.h>
#include <netinet/in.h>
#include "cwf.h"

int main(int argc, char* argv[]){
	if (argc < 2) {
		puts("need port");
		return -1;
	}
	int port = atoi(argv[1]);
	CWF_start(port);
	return 0;
}