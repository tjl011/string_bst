CC = gcc
CFLAGS = -g -Wall -Wextra

.PHONY: all

all = string_bst_test

OBJS = string_bst.o string_bst_test.o

string_bst_test: $(OBJS)
	$(CC) -o string_bst_test $(OBJS)

string_bst.o: string_bst.c string_bst.h
	$(CC) $(CFLAGS) -c string_bst.c -o string_bst.o

string_bst_test.o: string_bst_test.c string_bst.h
	$(CC) $(CFLAGS) -c string_bst_test.c -o string_bst_test.o

.PHONY: clean

clean:
	rm -f *.o $(all)