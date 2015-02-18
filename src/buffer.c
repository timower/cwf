#include <stdlib.h>
#include <string.h>

#include "buffer.h"

static int grow_buffer(buffer_t* buffer, int size) {
	if(buffer->size * 2 < size) {
		buffer->size += size;
	}
	buffer->size *= 2;
	char * newptr = realloc(buffer->buffer, buffer->size);
	if(newptr == NULL) {
		free(buffer->buffer);
		return 0;
	}
	buffer->buffer = newptr;
	return 1;

}

int init_buffer(buffer_t* buffer, int size) {
	buffer->buffer = malloc(size);
	if(buffer->buffer == NULL) {
		return 0;
	}
	buffer->size = size;
	buffer->pos = 0;
	buffer->orig_size = size;
	return 1;
}

int clear_buffer(buffer_t* buffer){
	char * newptr = realloc(buffer->buffer, buffer->orig_size);
	if(newptr == NULL) {
		free(buffer->buffer);
		return 0;
	}
	buffer->buffer = newptr;
	buffer->pos = 0;
	return 1;
}

int set_buffer(buffer_t* buffer, const char* source, int len) {
	if(buffer->size < len) {
		if(!grow_buffer(buffer, len)){
			return 0;
		}
	}
	memcpy(buffer->buffer, source, len);
	buffer->pos = len;
	return 1;
}

int append_buffer(buffer_t* buffer, const char* source, int len) {
	if(buffer->pos + len > buffer->size) {
		if(!grow_buffer(buffer, buffer->pos + len)){
			return 0;
		}
	}
	memcpy(buffer->buffer + buffer->pos, source, len);
	buffer->pos += len;
	return 1;
}

int append_bufferStr(buffer_t* buffer, const char* source) {
	return append_buffer(buffer, source, strlen(source));
}

void free_buffer(buffer_t* buffer) {
	if(buffer && buffer->buffer)
		free(buffer->buffer);
}

