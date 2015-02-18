OBJS := src/header.o \
		src/route.o \
		src/request.o \
		src/response.o \
		src/buffer.o \
		src/clients.o \
		src/cwf.o

MAIN := src/main.o

TESTS :=	test/allTests.o \
			test/headerTest.o \
			test/requestTest.o \
			test/CuTest.o
CFLAGS := -ggdb -Wall

all: server

server: $(OBJS) $(MAIN)
	gcc -ggdb -o server $(OBJS) $(MAIN)

test: runTest
	./runTest

runTest: server $(TESTS)
	gcc -o runTest $(OBJS) $(TESTS)

.PHONY: clean
clean:
	rm -f server
	rm -f runTest
	rm -f ${OBJS}
	rm -f ${TESTS}
