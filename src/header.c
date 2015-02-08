#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "header.h"

int set_header(header_t* header, const char* field, char* value) {
	int i;
    for (i = 0; i < HEADER_LENGTH; i++) {
        if(strcasecmp(header_fields[i], field) == 0) {
            break;
        }
    }
    if (i == HEADER_LENGTH) {
        return -1;
    }
    header->values[i] = value;
    return 0;
}

char* get_header(header_t* header, const char* field) {
	int i;
    for (i = 0; i < HEADER_LENGTH; i++) {
        if(strcasecmp(header_fields[i], field) == 0) {
            break;
        }
    }
    if (i == HEADER_LENGTH) {
        return NULL;
    }
    return header->values[i];
}

int free_header(header_t* header) {
	int i;
    for (i = 0; i < HEADER_LENGTH; i++) {
    	if(header->values[i]){
    		free(header->values[i]);
            header->values[i] = NULL;
        }
    }
    return 0;
}

void print_header(header_t* header) {
	int i;
    for (i = 0; i < HEADER_LENGTH; i++) {
    	if(header->values[i])
    		printf("%s: %s\n", header_fields[i], header->values[i]);
    }
}

void sprint_header(char* buf, header_t* header) {
    int i;
    char* pos = buf;
    for (i = 0; i < HEADER_LENGTH; i++) {
        if(header->values[i]){
            pos += sprintf(pos, "%s: %s\r\n", header_fields[i], header->values[i]);
        }
    }
}