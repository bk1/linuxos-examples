#include <stdio.h>

#define LIMIT 10000000

unsigned long long fib(unsigned int n);
unsigned long long fib_internal(unsigned int n);

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
  static unsigned long long cache[LIMIT] = { 1, 1, 0 };
  static unsigned int max_entry = 1;
  if (n < 0) {
    return 0;
  } else if (n <= max_entry) {
    return cache[n];
  } else {
    unsigned int i;
    unsigned long long x = cache[max_entry - 1];
    unsigned long long y = cache[max_entry];
    for (i = max_entry + 1; i <= n; i++) {
      unsigned long long z = y;
      y = x + y;
      x = z;
      if (i < LIMIT) {
        max_entry = i;
        cache[i] = y;
      }
    }
    return y;
  }
}

