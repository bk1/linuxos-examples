#include <stdio.h>


int fac(int n);

int main(int argc, char *argv[]) {
  int i;
  int n;
  for (n = 0; n < 20; n++) {
    int f = fac(n);
    printf("n=%10d f=%10d\n", n, f);
  }
  for (i = 0, n = 0; i < 1000; i++, n = 2*n+1) {
    int f = fac(n);
    printf("i=%4d n=%10d f=%10d\n", i, n, f);
  }
  return 0;
}

int fac(int n) {
  if (n <= 1) {
    return 1;
  } else {
    return n * fac(n-1);
  }
}

