#include <stdio.h>


int fac(int n, int *result_ptr);
int fac_intern(int n, int *result_ptr);

int main(int argc, char *argv[]) {
  int i;
  int n;
  for (n = -1; n < 20; n++) {
    int f;
    int r = fac(n, &f);
    printf("r=%02d n=%10d f=%10d\n", r, n, f);
  }
  for (i = 0, n = 0; i < 1000; i++, n = 2*n+1) {
    int f;
    int r = fac(n, &f);
    printf("i=%4d r=%02d n=%10d f=%10d\n", i, r, n, f);
    if (n < 0) {
      break;
    }
  }
  return 0;
}

int fac(int n, int *result_ptr) {
  *result_ptr = 1;
  return fac_intern(n, result_ptr);
}

int fac_intern(int n, int *result_ptr) {
  if (n < 0) {
    *result_ptr = 0;
    return -1;
  } else if (*result_ptr == 0) {
    return 0;
  } else if (n <= 1) {
    return 0;
  } else {
    *result_ptr *= n;
    return fac_intern(n - 1, result_ptr);
  }
}

