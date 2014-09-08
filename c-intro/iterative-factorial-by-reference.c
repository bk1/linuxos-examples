#include <stdio.h>


int fac(int *result_ptr, int n);

int main(int argc, char *argv[]) {
  int i;
  int n;
  for (n = 0; n < 20; n++) {
    int f;
    int result = fac(&f, n);
    printf("r=%2d n=%10d f=%10d\n", result, n, f);
  }
  for (i = 0, n = 0; i < 1000; i++, n = 2*n+1) {
    int f;
    int result = fac(&f, n);
    printf("i=%4d r=%2d n=%10d f=%10d\n", i, result, n, f);
  }
  return 0;
}

int fac(int *result_ptr, int n) {
  *result_ptr = 1;
  if (n < 0) {
    return -1;
  }
  int i;
  for (i = 2; i <= n; i++) {
    *result_ptr *= i;
  }
  return 0;
}

