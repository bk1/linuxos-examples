# automatically generated makefile by ../scripts/create-make

CFLAGS=-Wall -g -O2 -std=gnu99 -I. -I./include -L./lib

LIBS=-lcitsky


all: iterative-caching-fibonacci hello2 hello bad-float variables-example strlen-example recursive-caching-fibonacci static-example tail-recursive-factorial iterative-factorial tail-recursive-factorial-by-reference tail-recursive-fibonacci calculation recursive-factorial print-squares iterative-factorial-by-reference iterative-fibonacci recursive-fibonacci bad-int test/array-list-test

clean:
	rm -f  iterative-caching-fibonacci hello2 hello bad-float variables-example strlen-example recursive-caching-fibonacci static-example tail-recursive-factorial iterative-factorial tail-recursive-factorial-by-reference tail-recursive-fibonacci calculation recursive-factorial print-squares iterative-factorial-by-reference iterative-fibonacci recursive-fibonacci bad-int test/array-list-test lib/array-list.o

iterative-caching-fibonacci: iterative-caching-fibonacci.c lib/libcitsky.a
	gcc $(CFLAGS) iterative-caching-fibonacci.c $(LIBS) -o iterative-caching-fibonacci

hello2: hello2.c lib/libcitsky.a
	gcc $(CFLAGS) hello2.c $(LIBS) -o hello2

hello: hello.c lib/libcitsky.a
	gcc $(CFLAGS) hello.c $(LIBS) -o hello

bad-float: bad-float.c lib/libcitsky.a
	gcc $(CFLAGS) bad-float.c $(LIBS) -o bad-float

variables-example: variables-example.c lib/libcitsky.a
	gcc $(CFLAGS) variables-example.c $(LIBS) -o variables-example

strlen-example: strlen-example.c lib/libcitsky.a
	gcc $(CFLAGS) strlen-example.c $(LIBS) -o strlen-example

recursive-caching-fibonacci: recursive-caching-fibonacci.c lib/libcitsky.a
	gcc $(CFLAGS) recursive-caching-fibonacci.c $(LIBS) -o recursive-caching-fibonacci

static-example: static-example.c lib/libcitsky.a
	gcc $(CFLAGS) static-example.c $(LIBS) -o static-example

tail-recursive-factorial: tail-recursive-factorial.c lib/libcitsky.a
	gcc $(CFLAGS) tail-recursive-factorial.c $(LIBS) -o tail-recursive-factorial

iterative-factorial: iterative-factorial.c lib/libcitsky.a
	gcc $(CFLAGS) iterative-factorial.c $(LIBS) -o iterative-factorial

tail-recursive-factorial-by-reference: tail-recursive-factorial-by-reference.c lib/libcitsky.a
	gcc $(CFLAGS) tail-recursive-factorial-by-reference.c $(LIBS) -o tail-recursive-factorial-by-reference

tail-recursive-fibonacci: tail-recursive-fibonacci.c lib/libcitsky.a
	gcc $(CFLAGS) tail-recursive-fibonacci.c $(LIBS) -o tail-recursive-fibonacci

calculation: calculation.c lib/libcitsky.a
	gcc $(CFLAGS) calculation.c $(LIBS) -o calculation

recursive-factorial: recursive-factorial.c lib/libcitsky.a
	gcc $(CFLAGS) recursive-factorial.c $(LIBS) -o recursive-factorial

print-squares: print-squares.c lib/libcitsky.a
	gcc $(CFLAGS) print-squares.c $(LIBS) -o print-squares

iterative-factorial-by-reference: iterative-factorial-by-reference.c lib/libcitsky.a
	gcc $(CFLAGS) iterative-factorial-by-reference.c $(LIBS) -o iterative-factorial-by-reference

iterative-fibonacci: iterative-fibonacci.c lib/libcitsky.a
	gcc $(CFLAGS) iterative-fibonacci.c $(LIBS) -o iterative-fibonacci

recursive-fibonacci: recursive-fibonacci.c lib/libcitsky.a
	gcc $(CFLAGS) recursive-fibonacci.c $(LIBS) -o recursive-fibonacci

bad-int: bad-int.c lib/libcitsky.a
	gcc $(CFLAGS) bad-int.c $(LIBS) -o bad-int

test/array-list-test: test/array-list-test.c lib/libcitsky.a
	gcc $(CFLAGS) test/array-list-test.c $(LIBS) -L/usr/local/lib -lcunit -o test/array-list-test

lib/array-list.o: lib/array-list.c
	gcc -c $(CFLAGS) lib/array-list.c -o lib/array-list.o



lib/libcitsky.a: lib/array-list.o
	ar crs lib/libcitsky.a lib/array-list.o
