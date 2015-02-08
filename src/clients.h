#ifndef CLIENTS_H
#define CLIENTS_H

#include "buffer.h"

typedef struct client {
	int socket;
	buffer_t buffer;
} client_t;

void free_client(client_t* client);
void init_clients();
client_t* new_client();
client_t* find_client(int socket);
#endif