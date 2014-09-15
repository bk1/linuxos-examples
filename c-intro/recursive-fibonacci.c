#include <stdio.h>


int fib(int n);

int main(int argc, char *argv[]) {
  int i;
  int n;
  for (n = 0; n < 30; n++) {
    int f = fib(n);
    printf("n=%10d f=%10d\n", n, f);
  }
  for (i = 0, n = 0; i < 1000 && n >= 0; i++, n = 2*n+1) {
    int f = fib(n);
    printf("i=%4d n=%10d f=%10d\n", i, n, f);
  }
  return 0;
}

int fib(int n) {
  if (n <= 1) {
    return 1;
  } else {
    return fib(n-1) + fib(n-2);
  }
}

