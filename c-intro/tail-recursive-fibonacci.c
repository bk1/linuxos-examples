#include <stdio.h>


unsigned long long fib(unsigned int n);
unsigned long long fib_internal(unsigned int n, unsigned long long x, unsigned long long y);

int main(int argc, char *argv[]) {
  int i;
  unsigned int n;
  for (n = 0; n < 30; n++) {
    unsigned long long f = fib(n);
    printf("n=%10u f=%30llu\n", n, f);
  }
  for (i = 0, n = 0; i < 1000 && n >= 0; i++, n = 2*n+1) {
    unsigned long long f = fib(n);
    printf("i=%4d n=%10u f=%30llu\n", i, n, f);
  }
  return 0;
}

unsigned long long fib(unsigned int n) {
  return fib_internal(n, 1, 1);
}

unsigned long long fib_internal(unsigned int n, unsigned long long x, unsigned long long y) {
  if (n <= 1) {
    return y;
  } else {
    return fib_internal(n - 1, y, x+y);
  }
}

