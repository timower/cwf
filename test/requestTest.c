#include <string.h>
#include <stdlib.h>

#include "../src/cwf.h"
#include "CuTest.h"

void testRequest(CuTest* ct) {
	const char buf1[] = "GET / HTTP/1.1\r\nHost: test1\r\nContent-Type: text/plain\r\n\r\n";
	request_t req = {0};
	CuAssertTrue(ct, parse_request(buf1, strlen(buf1), &req) == 1);
	CuAssertStrEquals(ct, "test1", get_header(&(req.header), "host"));
	CuAssertStrEquals(ct, "text/plain", get_header(&(req.header), "Content-Type"));
	free_header(&(req.header));
}

void testRequestBody(CuTest* ct) {
	const char buf1[] = "GET / HTTP/1.1\r\nHost: test1\r\nContent-Type: text/plain\r\nContent-Length: 4\r\n\r\ntest";
	request_t req = {0};
	CuAssertTrue(ct, parse_request(buf1, strlen(buf1), &req) == 1);
	CuAssertStrEquals(ct, "test1", get_header(&(req.header), "host"));
	CuAssertStrEquals(ct, "4", get_header(&(req.header), "Content-Length"));
	CuAssertStrEquals(ct, "test", req.body);
	free_header(&(req.header));
	if(req.body)
		free(req.body);
}

void testRequestZero(CuTest* ct) {
	const char buf1[] = "GET / HTTP/1.1\r\n";
	request_t req = {0};
	CuAssertTrue(ct, parse_request(buf1, strlen(buf1), &req) == 0);
}
void testRequestZero2(CuTest* ct) {
	const char buf1[] = "GET / HTTP/1.1\r\nHost: test1\r\nConte";
	request_t req = {0};
	CuAssertTrue(ct, parse_request(buf1, strlen(buf1), &req) == 0);
}
void testRequestZero3(CuTest* ct) {
	const char buf1[] = "GET /qdsqqsdqff";
	request_t req = {0};
	CuAssertTrue(ct, parse_request(buf1, strlen(buf1), &req) == 0);
}
CuSuite* requestGetSuite() {
	CuSuite* suite = CuSuiteNew();
    SUITE_ADD_TEST(suite, testRequest);
    SUITE_ADD_TEST(suite, testRequestBody);
    SUITE_ADD_TEST(suite, testRequestZero);
    SUITE_ADD_TEST(suite, testRequestZero2);
    SUITE_ADD_TEST(suite, testRequestZero3);
    return suite;
}