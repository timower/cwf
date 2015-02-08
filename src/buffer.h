#ifndef BUFFER_H
#define BUFFER_H

typedef struct buffer {
	int size;
	int pos;
	int orig_size;
	char* buffer;
} buffer_t;

int init_buffer(buffer_t* buffer, int size);
int clear_buffer(buffer_t* buffer);
int set_buffer(buffer_t* buffer, const char* source, int len);
int append_buffer(buffer_t* buffer ,const char* source, int len);
int append_bufferStr(buffer_t* buffer, const char* source);
void free_buffer(buffer_t* buffer);

#endif