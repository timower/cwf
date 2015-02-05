OBJS := src/header.o \
		src/cwf.o \
		src/main.o
all: $(OBJS)
	gcc -o server $(OBJS)

.PHONY: clean
clean:
	rm -f server
	rm -f ${OBJS}