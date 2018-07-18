CC = gcc
CFLAGS = -IInclude
PYTHON = python

MODULE_OBJS = 		 						\
	Modules/python.o						\
	Modules/main.o

OBJECT_OBJS = 								\
	Objects/obmalloc.o					\
	Objects/object.o


all: $(MODULE_OBJS) $(OBJECT_OBJS)
	$(CC) $^ -o $(PYTHON)

.c.o:
	$(CC) -c $(CFLAGS) -o $@ $<

clean:
	find . -name '*.o' -exec rm -f {} ';'
	rm -f $(PYTHON)

.PHONY: all clean