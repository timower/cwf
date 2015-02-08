#include <stdio.h>

#include "CuTest.h"

CuSuite* headerGetSuite();
CuSuite* requestGetSuite();

int RunAllTests(void)
{
	CuString *output = CuStringNew();
	CuSuite* suite = CuSuiteNew();

	CuSuiteAddSuite(suite, headerGetSuite());
	CuSuiteAddSuite(suite, requestGetSuite());

	CuSuiteRun(suite);
	CuSuiteSummary(suite, output);
	CuSuiteDetails(suite, output);
	printf("%s\n", output->buffer);
	return suite->failCount;
}

int main(void)
{
	return RunAllTests() ? -1: 0;
	
}
