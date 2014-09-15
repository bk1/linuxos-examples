#include <stdio.h>

#define LIMIT 1000000

unsigned long long fib(unsigned int n);

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
  static unsigned long long values[LIMIT] = { 0 };
  if (n <= 1) {
    return 1;
  } else if (n >= LIMIT) {
    return fib(n-1) + fib(n-2);
  } else {
    unsigned long long v = values[n];
    if (v == 0) {
      v = fib(n-1) + fib(n-2);
      values[n] = v;
    }
    return v;
  }
}

