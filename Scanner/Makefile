CC = gcc
CFLAGS = -Wall

all: scanner

scanner: lex.yy.c main.c
	$(CC) $(CFLAGS) -o scanner_test lex.yy.c main.c

lex.yy.c: scanner.flex
	flex scanner.flex

clean:
	rm -f scanner_test lex.yy.c *.o
	rm -rf scanner_test.dSYM

test: scanner
	./scanner_test ../test/valid_test_01.mus
	./scanner_test ../test/invalid_test_01.mus

.PHONY: all clean test 