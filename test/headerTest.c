#include <string.h>
#include <stdlib.h>

#include "../src/header.h"
#include "CuTest.h"

void testHeaderNULL(CuTest* tc) {
	header_t header = {0};

	CuAssertTrue(tc, get_header(&header, "Host") == NULL);
	CuAssertTrue(tc, get_header(&header, "Content-Type") == NULL);
	CuAssertTrue(tc, get_header(&header, "LOLQSDF") == NULL);
}

void testHeader(CuTest* tc) {
	header_t header = {0};
	char * fail = strdup("fail");
	CuAssertTrue(tc, set_header(&header, "Host", strdup("test1")) == 0);
	CuAssertTrue(tc, set_header(&header, "Content", fail) == -1);
	free(fail);
	CuAssertStrEquals(tc, "test1", get_header(&header, "host"));
	free_header(&header);
	CuAssertTrue(tc, get_header(&header, "Host") == NULL);
}

CuSuite* headerGetSuite() {
	CuSuite* suite = CuSuiteNew();
    SUITE_ADD_TEST(suite, testHeaderNULL);
    SUITE_ADD_TEST(suite, testHeader);
    return suite;
}