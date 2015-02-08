#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "route.h"

app_t* new_app() {
	app_t* n = calloc(1, sizeof(app_t));
	return n;
}

void set_route(app_t* ap, char* path, route_func f){
	int i;
	for(i = 0; i < 10; i++) {
		if(ap->routes[i] == NULL)
			break;
	}
	if (i == 10)
		return;
	ap->routes[i] = f;
	ap->paths[i] = path;

}
route_func get_route(app_t* ap, char* path) {
	int i;
	for(i = 0; i < 10; i++) {
		if(ap->paths[i] && strcmp(ap->paths[i], path) == 0) {
			return ap->routes[i];
		}
	}
	return NULL;
}