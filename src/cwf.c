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
#include "clients.h"

int CWF_start(app_t* ap, int port) {
	fd_set orig_set, read_set;
	int max_fd, nready;
	int i;
	int sockfd, newsockfd;
	socklen_t clilen;
	struct sockaddr_in serv_addr, cli_addr;
	int buflen = 0;
	char buffer[1024];
    
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

    //setup fd_sets:
    FD_ZERO(&orig_set);
    FD_ZERO(&read_set);

    FD_SET(sockfd, &orig_set);
    max_fd = sockfd;

    //setup clients:
    init_clients();

	while (1) {
		memcpy(&read_set, &orig_set, sizeof(orig_set));
		puts("selecting...");
		nready = select(max_fd+1, &read_set, NULL, NULL, NULL); // wait for socket ready
		if (nready == -1) {
			puts("ERROR select");
			return -1;
		}
		for(i = 0; i <= max_fd && nready > 0; i++) {
			if (FD_ISSET(i, &read_set)) {
				nready--;
				if (i == sockfd) {
					puts("new client available");
					clilen = sizeof(cli_addr);
					newsockfd = accept(sockfd, (struct sockaddr *) &cli_addr, &clilen);
					if (newsockfd < 0) {
						puts("ERROR accepting");
						return -1;
					}
					FD_SET(newsockfd, &orig_set);

					client_t* nclient = new_client();
					nclient->socket = newsockfd;
					init_buffer(&(nclient->buffer), 512);

					if (newsockfd > max_fd)
						max_fd = newsockfd;
				} else {
					client_t* client = find_client(i);
					if(client == NULL) {
						puts("ERROR finding client!!");
						return -1;
					}
					
					int n = read(i, buffer, sizeof(buffer)); //TODO: fix buffer
					if (n <= 0) {
						puts("ERROR on read");
						close(i);
						FD_CLR(i, &orig_set);
						free_client(client);
						continue;
					}
					append_buffer(&(client->buffer), buffer, n);

					request_t req = {0};
					int ret = parse_request(client->buffer.buffer, client->buffer.pos, &req);
					if (ret < 0){
						puts("ERROR parsing buffer");
						close(i);
						FD_CLR(i, &orig_set);
						free_client(client);
						free_buffer(&(req.body));
						continue;
					} else if(ret == 0) {
						continue;
					}
					//print:

					printf("method: %s path: %s version: %d.%d\n",
						req.method, req.path, req.version_major, req.version_minor);
					response_t res = {0};
					res.version_major = 1;
					res.version_minor = 1;
					res.status_code = 200;
					res.reason_phrase = "OK";
					init_buffer(&(res.body), 512);
					//TODO:
					set_header(&(res.header), "Content-Type", strdup("text/html"));

					route_func f = get_route(ap, req.path); //latency?

					if (f) {
						f(&req, &res);
					}else{
						puts("404");
						res.status_code = 404;
						res.reason_phrase = "not found";

						char msg[] = "404 not found";
						append_bufferStr(&(res.body), msg);
					}

					if(res.body.buffer) {
						char length[16];
						sprintf(length, "%d", res.body.pos);
						set_header(&(res.header), "Content-Length", strdup(length));
					}
					//send response:
					int len;
					char* buff = gen_response(&res, &len);
					if (write(newsockfd, buff, len) < 0)
						puts("error responding");
					free(buff);

					char* con = get_header(&(req.header), "connection");
					if(!con || !(strcasecmp(con, "keep-alive") == 0)) {
						puts("not keep alive");
						close(i);
						FD_CLR(i, &orig_set);
						free_client(client);
					} else {
						clear_buffer(&(client->buffer));
					}


					//free:
					free_header(&(res.header));
					free_buffer(&(res.body));
					//close connection gracefully
					free_header(&(req.header));
					free_buffer(&(req.body));
					;
					//reset buffer:
					
					//puts(buffer);
				}
			}
		}
	}
	close(sockfd);
}