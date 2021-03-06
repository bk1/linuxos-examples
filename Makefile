# automatically generated makefile by ./scripts/create-make

CFLAGS=-Wall -g -O2 -std=gnu99 -I. -I./include -L./lib

LIBS=-lcitsky -lm -lpthread


all: polymorphie/polymorphical-simpson polymorphie/polymorphical-shapes processes/thread-example processes/thread-mutex processes/cstart-simpson processes/simpson processes/pipe processes/fork+named-pipe processes/thread-factorial processes/stack processes/forktest processes/demoexec c-intro/iterative-caching-fibonacci c-intro/hello2 c-intro/hello c-intro/bad-float c-intro/variables-example c-intro/strlen-example c-intro/recursive-caching-fibonacci c-intro/static-example c-intro/tail-recursive-factorial c-intro/iterative-factorial c-intro/tail-recursive-factorial-by-reference c-intro/tail-recursive-fibonacci c-intro/calculation c-intro/recursive-factorial c-intro/print-squares c-intro/iterative-factorial-by-reference c-intro/iterative-fibonacci c-intro/recursive-fibonacci c-intro/bad-int test/array-list-test test/cyclic-int-buffer-run test/cyclic-int-buffer-test memory/malloc-gross-net-sizes memory/malloc-and-free memory/malloc-first-fit-check io+fs/lowlevel-record-storage

clean:
	rm -f  polymorphie/polymorphical-simpson polymorphie/polymorphical-shapes processes/thread-example processes/thread-mutex processes/cstart-simpson processes/simpson processes/pipe processes/fork+named-pipe processes/thread-factorial processes/stack processes/forktest processes/demoexec c-intro/iterative-caching-fibonacci c-intro/hello2 c-intro/hello c-intro/bad-float c-intro/variables-example c-intro/strlen-example c-intro/recursive-caching-fibonacci c-intro/static-example c-intro/tail-recursive-factorial c-intro/iterative-factorial c-intro/tail-recursive-factorial-by-reference c-intro/tail-recursive-fibonacci c-intro/calculation c-intro/recursive-factorial c-intro/print-squares c-intro/iterative-factorial-by-reference c-intro/iterative-fibonacci c-intro/recursive-fibonacci c-intro/bad-int test/array-list-test test/cyclic-int-buffer-run test/cyclic-int-buffer-test memory/malloc-gross-net-sizes memory/malloc-and-free memory/malloc-first-fit-check io+fs/lowlevel-record-storage lib/array-list.o lib/cyclic-int-buffer.o

polymorphie/polymorphical-simpson: polymorphie/polymorphical-simpson.c lib/libcitsky.a
	gcc $(CFLAGS) polymorphie/polymorphical-simpson.c $(LIBS) -o polymorphie/polymorphical-simpson

polymorphie/polymorphical-shapes: polymorphie/polymorphical-shapes.c lib/libcitsky.a
	gcc $(CFLAGS) polymorphie/polymorphical-shapes.c $(LIBS) -o polymorphie/polymorphical-shapes

processes/thread-example: processes/thread-example.c lib/libcitsky.a
	gcc $(CFLAGS) processes/thread-example.c $(LIBS) -o processes/thread-example

processes/thread-mutex: processes/thread-mutex.c lib/libcitsky.a
	gcc $(CFLAGS) processes/thread-mutex.c $(LIBS) -o processes/thread-mutex

processes/cstart-simpson: processes/cstart-simpson.c lib/libcitsky.a
	gcc $(CFLAGS) processes/cstart-simpson.c $(LIBS) -o processes/cstart-simpson

processes/simpson: processes/simpson.c lib/libcitsky.a
	gcc $(CFLAGS) processes/simpson.c $(LIBS) -o processes/simpson

processes/pipe: processes/pipe.c lib/libcitsky.a
	gcc $(CFLAGS) processes/pipe.c $(LIBS) -o processes/pipe

processes/fork+named-pipe: processes/fork+named-pipe.c lib/libcitsky.a
	gcc $(CFLAGS) processes/fork+named-pipe.c $(LIBS) -o processes/fork+named-pipe

processes/thread-factorial: processes/thread-factorial.c lib/libcitsky.a
	gcc $(CFLAGS) processes/thread-factorial.c $(LIBS) -o processes/thread-factorial

processes/stack: processes/stack.c lib/libcitsky.a
	gcc $(CFLAGS) processes/stack.c $(LIBS) -o processes/stack

processes/forktest: processes/forktest.c lib/libcitsky.a
	gcc $(CFLAGS) processes/forktest.c $(LIBS) -o processes/forktest

processes/demoexec: processes/demoexec.c lib/libcitsky.a
	gcc $(CFLAGS) processes/demoexec.c $(LIBS) -o processes/demoexec

c-intro/iterative-caching-fibonacci: c-intro/iterative-caching-fibonacci.c lib/libcitsky.a
	gcc $(CFLAGS) c-intro/iterative-caching-fibonacci.c $(LIBS) -o c-intro/iterative-caching-fibonacci

c-intro/hello2: c-intro/hello2.c lib/libcitsky.a
	gcc $(CFLAGS) c-intro/hello2.c $(LIBS) -o c-intro/hello2

c-intro/hello: c-intro/hello.c lib/libcitsky.a
	gcc $(CFLAGS) c-intro/hello.c $(LIBS) -o c-intro/hello

c-intro/bad-float: c-intro/bad-float.c lib/libcitsky.a
	gcc $(CFLAGS) c-intro/bad-float.c $(LIBS) -o c-intro/bad-float

c-intro/variables-example: c-intro/variables-example.c lib/libcitsky.a
	gcc $(CFLAGS) c-intro/variables-example.c $(LIBS) -o c-intro/variables-example

c-intro/strlen-example: c-intro/strlen-example.c lib/libcitsky.a
	gcc $(CFLAGS) c-intro/strlen-example.c $(LIBS) -o c-intro/strlen-example

c-intro/recursive-caching-fibonacci: c-intro/recursive-caching-fibonacci.c lib/libcitsky.a
	gcc $(CFLAGS) c-intro/recursive-caching-fibonacci.c $(LIBS) -o c-intro/recursive-caching-fibonacci

c-intro/static-example: c-intro/static-example.c lib/libcitsky.a
	gcc $(CFLAGS) c-intro/static-example.c $(LIBS) -o c-intro/static-example

c-intro/tail-recursive-factorial: c-intro/tail-recursive-factorial.c lib/libcitsky.a
	gcc $(CFLAGS) c-intro/tail-recursive-factorial.c $(LIBS) -o c-intro/tail-recursive-factorial

c-intro/iterative-factorial: c-intro/iterative-factorial.c lib/libcitsky.a
	gcc $(CFLAGS) c-intro/iterative-factorial.c $(LIBS) -o c-intro/iterative-factorial

c-intro/tail-recursive-factorial-by-reference: c-intro/tail-recursive-factorial-by-reference.c lib/libcitsky.a
	gcc $(CFLAGS) c-intro/tail-recursive-factorial-by-reference.c $(LIBS) -o c-intro/tail-recursive-factorial-by-reference

c-intro/tail-recursive-fibonacci: c-intro/tail-recursive-fibonacci.c lib/libcitsky.a
	gcc $(CFLAGS) c-intro/tail-recursive-fibonacci.c $(LIBS) -o c-intro/tail-recursive-fibonacci

c-intro/calculation: c-intro/calculation.c lib/libcitsky.a
	gcc $(CFLAGS) c-intro/calculation.c $(LIBS) -o c-intro/calculation

c-intro/recursive-factorial: c-intro/recursive-factorial.c lib/libcitsky.a
	gcc $(CFLAGS) c-intro/recursive-factorial.c $(LIBS) -o c-intro/recursive-factorial

c-intro/print-squares: c-intro/print-squares.c lib/libcitsky.a
	gcc $(CFLAGS) c-intro/print-squares.c $(LIBS) -o c-intro/print-squares

c-intro/iterative-factorial-by-reference: c-intro/iterative-factorial-by-reference.c lib/libcitsky.a
	gcc $(CFLAGS) c-intro/iterative-factorial-by-reference.c $(LIBS) -o c-intro/iterative-factorial-by-reference

c-intro/iterative-fibonacci: c-intro/iterative-fibonacci.c lib/libcitsky.a
	gcc $(CFLAGS) c-intro/iterative-fibonacci.c $(LIBS) -o c-intro/iterative-fibonacci

c-intro/recursive-fibonacci: c-intro/recursive-fibonacci.c lib/libcitsky.a
	gcc $(CFLAGS) c-intro/recursive-fibonacci.c $(LIBS) -o c-intro/recursive-fibonacci

c-intro/bad-int: c-intro/bad-int.c lib/libcitsky.a
	gcc $(CFLAGS) c-intro/bad-int.c $(LIBS) -o c-intro/bad-int

test/array-list-test: test/array-list-test.c lib/libcitsky.a
	gcc $(CFLAGS) test/array-list-test.c $(LIBS) -L/usr/local/lib -lcunit -o test/array-list-test

test/cyclic-int-buffer-run: test/cyclic-int-buffer-run.c lib/libcitsky.a
	gcc $(CFLAGS) test/cyclic-int-buffer-run.c $(LIBS) -L/usr/local/lib -lcunit -o test/cyclic-int-buffer-run

test/cyclic-int-buffer-test: test/cyclic-int-buffer-test.c lib/libcitsky.a
	gcc $(CFLAGS) test/cyclic-int-buffer-test.c $(LIBS) -L/usr/local/lib -lcunit -o test/cyclic-int-buffer-test

memory/malloc-gross-net-sizes: memory/malloc-gross-net-sizes.c lib/libcitsky.a
	gcc $(CFLAGS) memory/malloc-gross-net-sizes.c $(LIBS) -o memory/malloc-gross-net-sizes

memory/malloc-and-free: memory/malloc-and-free.c lib/libcitsky.a
	gcc $(CFLAGS) memory/malloc-and-free.c $(LIBS) -o memory/malloc-and-free

memory/malloc-first-fit-check: memory/malloc-first-fit-check.c lib/libcitsky.a
	gcc $(CFLAGS) memory/malloc-first-fit-check.c $(LIBS) -o memory/malloc-first-fit-check

io+fs/lowlevel-record-storage: io+fs/lowlevel-record-storage.c lib/libcitsky.a
	gcc $(CFLAGS) io+fs/lowlevel-record-storage.c $(LIBS) -o io+fs/lowlevel-record-storage

lib/array-list.o: lib/array-list.c
	gcc -c $(CFLAGS) lib/array-list.c -o lib/array-list.o

lib/cyclic-int-buffer.o: lib/cyclic-int-buffer.c
	gcc -c $(CFLAGS) lib/cyclic-int-buffer.c -o lib/cyclic-int-buffer.o



lib/libcitsky.a: lib/array-list.o lib/cyclic-int-buffer.o
	ar crs lib/libcitsky.a lib/array-list.o lib/cyclic-int-buffer.o
