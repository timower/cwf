#ifndef ROUTE_H
#define ROUTE_H
#include "request.h"
#include "response.h"

typedef void (*route_func)(request_t*, response_t*);

//TODO: non limited routes
typedef struct app {
	route_func routes[10];
	char* paths[10];

} app_t;

app_t* new_app();
void set_route(app_t*, char*, route_func);
route_func get_route(app_t*, char*);
#endif