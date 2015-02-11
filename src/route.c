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

int route_compare(char* route, char* path, route_params_t* params) {
	puts("comparing");
	int len1 = strlen(route);
	int len2 = strlen(path);
	printf("len1: %d, len2: %d\n", len1, len2);
	int i;
	int j = 0;
	int in_expr = 0;
	int params_i = 0;
	char* buffer;
	int buffer_i = 0;
	for (i = 0; i < len2 && j < len1; i++) {
		if (!in_expr) {
			if (route[j] == '%') {
				buffer = malloc(512); //TODO: length?
				buffer[0] = path[i];
				buffer_i = 1;
				in_expr = 1;
			}
			else if(route[j] != path[i]) {
				printf("no match: %d, %d\n", i, j);
				return 0;
			}
			j++;
		} else {
			if (path[i] == '/') {
				buffer[buffer_i] = '\0';
				params->params[params_i] = buffer;
				params_i++;
				in_expr = 0;
				j++;
			} else {
				buffer[buffer_i] = path[i];
				buffer_i++;
			}
		}
	}
	printf("len1: %d, len2: %d\n", j, i);
	if(i != len2 || j != len1) {
		return 0;
	}
	return 1;
}

route_func get_route(app_t* ap, char* path, request_t* req) {
	int i;
	 //TODO :fix null
	for(i = 0; i < 10; i++) {
		route_params_t rp = {0};
		if(ap->paths[i]) {
			if (route_compare(ap->paths[i], path, &rp)){
				req->rp = rp;
				return ap->routes[i];
			}
		}
	}
	return NULL;
}