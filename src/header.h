#ifndef HEADER_H
#define HEADER_H

#define HEADER_LENGTH (sizeof(header_fields)/sizeof(char*))

static const char* header_fields[] = {
	"Cache-Control",
	"Connection",
	"Date",
	"Pragma",
	"Trailer",
	"Transfer-Encoding",
	"Upgrade",
	"Via",
	"Warning",
	"Accept",
	"Accept-Charset",
	"Accept-Encoding",
	"Accept-Language",
	"Authorization",
	"Expect",
	"From",
	"Host",
	"If-Match",
	"If-Modified-Since",
	"If-None-Match",
	"If-Range",
	"If-Unmodified-Since",
	"Max-Forwards",
	"Proxy-Authorization",
	"Range",
	"Referer",
	"TE",
	"User-Agent",
	"Allow",
	"Content-Encoding",
	"Content-Language",
	"Content-Length",
	"Content-Location",
	"Content-MD5",
	"Content-Range",
	"Content-Type",
	"Expires",
	"Last-Modified",
	"extension-header",
	"Accept-Ranges",
	"Age",
	"ETag",
	"Location",
	"Proxy-Authenticate",
	"Retry-After",
	"Server",
	"Vary",
	"WWW-Authenticate"
};

typedef struct header {
	char* values[HEADER_LENGTH];
} header_t;

int set_header(header_t* header, const char* field, char* value);
char* get_header(header_t* header, const char* field);
int free_header(header_t* header);
void print_header(header_t* header);
void sprint_header(char* buf, header_t* header);
#endif
