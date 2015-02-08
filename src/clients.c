#include <stdlib.h>
#include <string.h>
#include "clients.h"

client_t** clients;
int nclients = 10;

void free_client(client_t* client) {
	int j;
	for(j = 0; j < nclients; j++) {
		if(clients[j] && clients[j]->socket == client->socket){
			break;
		}
	}
	if(clients[j]->buffer.buffer) {
		free_buffer(&(clients[j]->buffer));
	}
	free(clients[j]);
	clients[j] = NULL;

}

void init_clients() {
	clients = calloc(nclients, sizeof(client_t*));
}

client_t* new_client() {
	int j;
	for(j = 0; j < nclients; j++) {
		if(clients[j] == NULL)
			break;
	}
	if(j == nclients){
		clients = realloc(clients, nclients * 2 * sizeof(client_t*));
		memset(clients+nclients, 0, (2*nclients) - nclients);
		nclients *= 2;
	}
	client_t* client = calloc(1, sizeof(client_t));
	clients[j] = client;
	return client;
}

client_t* find_client(int socket) {
	int j;
	for(j = 0; j < nclients; j++) {
		if(clients[j] && clients[j]->socket == socket){
			break;
		}
	}
	if(j == nclients) {
		return NULL;
	}
	return clients[j];
}